import fs from 'node:fs';
import path from 'node:path';
import { pathToFileURL } from 'node:url';
import { build } from './progress.mjs';

const START = '<!-- PSF_PROGRESS_START -->';
const END = '<!-- PSF_PROGRESS_END -->';

const checkbox = value => value ? 'x' : ' ';

export function syncPlanProgress(plan, data) {
  const days = new Map(data.days.map(d => [`${d.week}:${d.day}`, d]));
  const weeks = new Map(data.weeks.map(w => [w.week, w]));
  let weekRows = 0;
  let dayRows = 0;

  const lines = plan.replace(/\r\n/g, '\n').split('\n');
  let currentWeek = null;

  for (let i = 0; i < lines.length; i++) {
    const heading = /^## Week (\d+)\b/.exec(lines[i]);
    if (heading) currentWeek = Number(heading[1]);

    // Top-level 12-week summary table.
    const weekRow = /^\| \[[ x]\] \| (\d{1,2}) \|/.exec(lines[i]);
    if (weekRow && currentWeek === null) {
      const week = Number(weekRow[1]);
      const status = weeks.get(week);
      if (!status) throw new Error(`Week ${week} 진도 데이터가 없습니다.`);
      lines[i] = lines[i].replace(/^\| \[[ x]\] \|/, `| [${checkbox(status.complete)}] |`);
      weekRows++;
      continue;
    }

    // Per-week Day tables. Manual checklist items below the tables are intentionally untouched.
    if (currentWeek !== null) {
      const dayRow = /^\| \[[ x]\] \| ([1-7]) \|/.exec(lines[i]);
      if (dayRow) {
        const day = Number(dayRow[1]);
        const status = days.get(`${currentWeek}:${day}`);
        if (!status) throw new Error(`Week ${currentWeek} Day ${day} 진도 데이터가 없습니다.`);
        lines[i] = lines[i].replace(/^\| \[[ x]\] \|/, `| [${checkbox(status.complete)}] |`);
        dayRows++;
      }
    }
  }

  if (weekRows !== 12 || dayRows !== 84) {
    throw new Error(`커리큘럼 체크 행 수 오류: Week ${weekRows}/12, Day ${dayRows}/84`);
  }

  let result = lines.join('\n');
  const oldGuide = '- 표의 `[ ]`는 원문에서 `[x]`로 바꾸면 된다. 표 안에서는 GitHub 등 일부 뷰어가 체크박스로 렌더링하지 않는다.\n' +
    '- 각 주 아래 별도 `- [ ]` 목록은 표준 Markdown 작업 목록이다. 완료 상태의 기준은 이 목록으로 두고, 표의 상태는 필요할 때 함께 갱신한다. 두 곳은 자동 동기화되지 않는다.';
  const newGuide = '- 표의 `[ ]` / `[x]`는 `solutions`와 `records.json`에서 계산한 **자동 진도 상태**다. GitHub Actions가 Day·Week 완료 여부를 갱신한다. 표 안에서는 GitHub 등 일부 뷰어가 체크박스로 렌더링하지 않는다.\n' +
    '- 각 주 아래 별도 `- [ ]` 목록은 **수동 학습 체크리스트**다. 개념 설명·오답 정리·주간 설명처럼 파일만으로 판정할 수 없는 항목은 사용자가 직접 관리하며, 자동화가 덮어쓰지 않는다.';
  if (result.includes(oldGuide)) result = result.replace(oldGuide, newGuide);

  return result;
}

export function syncMainReadme(readme, data) {
  const block = [
    START,
    '## 현재 진도',
    '',
    `**전체 목표 진도: ${data.overall.done}/${data.overall.total} (${data.overall.percent}%)** · 완료 Day ${data.overall.completedDays}/${data.overall.totalDays} · Week ${data.overall.completedWeeks}/${data.overall.totalWeeks}`,
    '',
    `등록 문제 해결: **${data.accepted}/${data.registered}** · 신규 학습 목표: **${data.target}문제**`,
    '',
    END,
  ].join('\n');

  const normalized = readme.replace(/\r\n/g, '\n');
  const existing = new RegExp(`${START}[\\s\\S]*?${END}`);
  if (existing.test(normalized)) return normalized.replace(existing, block);

  const activity = /\n<a href="https:\/\/github\.com\/[^\n]+\/tree\/progress"><img src="assets\/activity\.svg"/;
  const match = activity.exec(normalized);
  if (match) return normalized.slice(0, match.index) + `\n\n${block}\n` + normalized.slice(match.index + 1);

  return normalized.trimEnd() + `\n\n${block}\n`;
}

export function syncMain(root, repo = process.env.GITHUB_REPOSITORY || 'Nu-LungJi/Problem-Solving-Factory') {
  // Build once from source-of-truth data. Table checkboxes do not feed objective completion,
  // while manual checklist items remain untouched and can still complete manual-only days.
  const { data } = build(root, repo);
  const planPath = path.join(root, 'curriculum', 'plan.md');
  const readmePath = path.join(root, 'README.md');
  const beforePlan = fs.readFileSync(planPath, 'utf8');
  const beforeReadme = fs.readFileSync(readmePath, 'utf8');
  const afterPlan = syncPlanProgress(beforePlan, data);
  const afterReadme = syncMainReadme(beforeReadme, data);

  if (afterPlan !== beforePlan.replace(/\r\n/g, '\n')) fs.writeFileSync(planPath, afterPlan);
  if (afterReadme !== beforeReadme.replace(/\r\n/g, '\n')) fs.writeFileSync(readmePath, afterReadme);

  return {
    data,
    changed: {
      plan: afterPlan !== beforePlan.replace(/\r\n/g, '\n'),
      readme: afterReadme !== beforeReadme.replace(/\r\n/g, '\n'),
    },
  };
}

if (process.argv[1] && import.meta.url === pathToFileURL(path.resolve(process.argv[1])).href) {
  const root = process.cwd();
  const result = syncMain(root);
  console.log(`main 동기화: README ${result.changed.readme ? '갱신' : '변경 없음'}, 커리큘럼 ${result.changed.plan ? '갱신' : '변경 없음'}`);
  console.log(`전체 목표 진도 ${result.data.overall.done}/${result.data.overall.total} (${result.data.overall.percent}%)`);
}
