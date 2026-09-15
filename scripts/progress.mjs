import fs from 'node:fs';
import path from 'node:path';
import { pathToFileURL } from 'node:url';
import { adapters } from './adapters.mjs';
import { calculate } from './calculate.mjs';
import { attachPools } from './pools.mjs';
import { formatProgressMarkdown } from './progress-layout.mjs';

export function problemKey(url) {
  const u = new URL(url);
  const patterns = {
    'school.programmers.co.kr': ['programmers', /^\/learn\/courses\/30\/lessons\/(\d+)\/?$/],
    'cses.fi': ['cses', /^\/problemset\/task\/(\d+)\/?$/],
    'leetcode.com': ['leetcode', /^\/problems\/([^/]+)\/?$/],
  };
  const rule = patterns[u.hostname];
  const match = rule?.[1].exec(u.pathname);
  if (!match) throw new Error('지원하지 않는 문제 주소: ' + url);
  return rule[0] + ':' + match[1];
}

export function parsePlan(text) {
  const days = [];
  let week = 0;
  for (const line of text.split(/\r?\n/)) {
    const heading = /^## Week (\d+) /.exec(line);
    if (heading) week = Number(heading[1]);
    if (!week || !/^\| \[[ x]\] \| [1-7] \|/.test(line)) continue;
    const cells = line.split('|').slice(1, -1).map(s => s.trim());
    const problems = [...cells[3].matchAll(/\[([^\]]+)\]\((https:\/\/[^)]+)\)/g)]
      .map(m => ({ key: problemKey(m[2]), title: m[1], url: m[2] }));
    days.push({ id: `week-${week}-day-${cells[1]}`, week, day: Number(cells[1]), goal: cells[2],
      target: Number(cells[4]), reviewTarget: Number(cells[5]), problems });
  }
  if (days.length !== 84 || new Set(days.map(d => d.week + ':' + d.day)).size !== 84)
    throw new Error('커리큘럼은 중복 없는 84일이어야 합니다.');
  if (days.some(d => d.week < 1 || d.week > 12 || !Number.isInteger(d.target) || d.target < 0 || !Number.isInteger(d.reviewTarget) || d.reviewTarget < 0))
    throw new Error('일일 목표 수 오류');
  return days;
}

function walk(root, current = '') {
  return fs.readdirSync(path.join(root, current), { withFileTypes: true }).sort((a,b) => a.name.localeCompare(b.name, 'en')).flatMap(e => {
    if (e.isSymbolicLink() || ['.git', '.github', 'node_modules', 'generated', 'tests'].includes(e.name)) return [];
    const rel = path.posix.join(current, e.name);
    return e.isDirectory() ? walk(root, rel) : [rel];
  });
}

function safeFile(root, rel) {
  if (typeof rel !== 'string' || rel.includes('\\') || path.isAbsolute(rel) ||
      rel.split('/').some(p => p === '..' || p === '.' || !p))
    throw new Error('저장소 내부 상대 경로만 허용: ' + rel);
  const absolute = path.resolve(root, rel);
  const realRoot = fs.realpathSync(root);
  const real = fs.realpathSync(absolute);
  if (!real.startsWith(realRoot + path.sep) || !fs.statSync(real).isFile() ||
      !/\.(cpp|cc|cxx)$/i.test(rel) || !fs.readFileSync(real, 'utf8').trim())
    throw new Error('비어 있지 않은 C++ 파일이 필요: ' + rel);
  return rel;
}

export function collect(root, days, records) {
  const solved = new Map();
  const read = rel => {
    const file = path.join(root, rel);
    if (!fs.existsSync(file) || fs.lstatSync(file).isSymbolicLink()) return '';
    return fs.readFileSync(file, 'utf8');
  };
  for (const file of walk(root)) {
    if (!/\.(cpp|cc|cxx)$/i.test(file) || !read(file).trim()) continue;
    for (const adapter of adapters) {
      const event = adapter(file, read);
      if (event && !solved.has(event.key)) solved.set(event.key, { code: safeFile(root, file), evidence: event.evidence });
    }
  }
  if (!Array.isArray(records)) throw new Error('records.json은 배열이어야 합니다.');
  const recordIds = new Set();
  const extraOwners = new Map();
  const assigned = new Map();
  for (const d of days) for (const p of [...d.problems, ...(d.additional?.candidates || [])]) {
    if (!assigned.has(p.key)) assigned.set(p.key, d.week + ':' + d.day);
  }
  const reviews = [];
  for (const r of records) {
    if (typeof r?.id !== 'string' || !r.id.trim() || recordIds.has(r.id)) throw new Error('중복 또는 누락된 기록 id');
    recordIds.add(r.id);
    const day = days.find(d => d.week === r.week && d.day === r.day);
    if (!day) throw new Error('기록의 week/day 오류: ' + r.id);
    if (!['solve', 'review'].includes(r.kind) ||
        !['accepted', 'attempted'].includes(r.result) ||
        typeof r.usedHint !== 'boolean' ||
        !/^\d{4}-\d{2}-\d{2}$/.test(r.date) ||
        Number.isNaN(Date.parse(r.date)) || new Date(r.date).toISOString().slice(0,10) !== r.date) throw new Error('기록 필드 오류: ' + r.id);
    const key = problemKey(r.url);
    const code = safeFile(root, r.code);
    if (r.kind === 'solve' && !assigned.has(key)) {
      const owner = r.week + ':' + r.day;
      if (extraOwners.has(key) && extraOwners.get(key) !== owner)
        throw new Error('추가 문제를 여러 날짜의 신규로 중복 등록할 수 없습니다: ' + key);
      extraOwners.set(key, owner);
      if (!day.problems.some(p => p.key === key))
        day.problems.push({ key, title: key, url: r.url, extra: true });
    }
    if (r.result === 'accepted') solved.set(key, { code, evidence: '사용자 정답 확인' });
    if (r.kind === 'review') reviews.push({ ...r, key });
  }
  return { solved, reviews };
}

const escape = s => String(s).replace(/[|]/g, '&#124;').replace(/[\r\n]/g, ' ').replace(/[<>]/g, '');
export function build(root, repo = 'Nu-LungJi/Problem-Solving-Factory') {
  if (!/^[\w.-]+\/[\w.-]+$/.test(repo)) throw new Error('저장소 이름 오류');
  const plan = fs.readFileSync(path.join(root, 'curriculum/plan.md'), 'utf8');
  const days = parsePlan(plan);
  attachPools(days, JSON.parse(fs.readFileSync(path.join(root, 'curriculum/pools.json'), 'utf8')), problemKey);
  const records = JSON.parse(fs.readFileSync(path.join(root, 'curriculum/records.json'), 'utf8'));
  const { solved, reviews } = collect(root, days, records);
  const progress = calculate(days, solved, reviews, plan);
  const planned = new Set(days.flatMap(d => [...d.problems, ...d.additional.candidates].map(p => p.key)));
  const accepted = [...planned].filter(k => solved.has(k)).length;
  const target = days.reduce((s, d) => s + d.target, 0);
  let md = '# 12주 코테 문제 해결 현황\n\n';
  md += '[전체 커리큘럼](https://github.com/' + repo + '/blob/main/curriculum/plan.md) · ';
  md += '[수동 기록 방법](https://github.com/' + repo + '/blob/main/curriculum/README.md)\n\n';
  md += '**등록 문제 해결: ' + accepted + '/' + planned.size + '** · 신규 학습 목표: ' + target + '문제\n\n';
  md += '필수 144문제와 Day별 후보 풀에서 선택하는 64문제를 합쳐 신규 목표는 208문제입니다. 후보를 전부 풀 필요는 없습니다. 후보 밖의 기존 수동 기록은 보존하지만 목표를 대체하지 않습니다. ';
  md += '업로드는 독립 해결·학습 완료의 증명이 아닙니다. BaekjoonHub 형식은 업로드 관례를 신뢰하며 온라인 저지에 재조회하지 않습니다. ';
  md += 'Day·Week 객관적 풀이 목표는 자동 계산하며 개념·오답 정리 체크는 원본 커리큘럼에서 직접 관리합니다.\n\n';
  md += `**전체 목표 진도: ${progress.overall.done}/${progress.overall.total} (${progress.overall.percent}%)** · 완료 Day ${progress.overall.completedDays}/84 · Week ${progress.overall.completedWeeks}/12\n\n`;
  md += '| Week | 자동 목표 진도 | 완료 Day | Week 완료 |\n|---|---:|---:|---|\n';
  for (const w of progress.weeks) md += `| ${w.week} | ${w.done}/${w.total} (${w.percent}%) | ${w.completedDays}/${w.totalDays} | ${w.complete ? '✅' : '미완료'} |\n`;
  md += '\n';
  md += '| Week | 등록 문제 해결/등록 수 | 신규 목표 | 기록된 재풀이 시도/목표 |\n|---|---:|---:|---:|\n';
  for (let w = 1; w <= 12; w++) {
    const ds = days.filter(d => d.week === w);
    const keys = new Set(ds.flatMap(d => [...d.problems, ...d.additional.candidates].map(p => p.key)));
    md += '| ' + w + ' | ' + [...keys].filter(k => solved.has(k)).length + '/' + keys.size +
      ' | ' + ds.reduce((s,d) => s+d.target,0) + ' | ' + reviews.filter(r => r.week === w).length +
      '/' + ds.reduce((s,d) => s+d.reviewTarget,0) + ' |\n';
  }
  for (let w = 1; w <= 12; w++) {
    md += '\n## Week ' + w + '\n\n';
    for (const d of days.filter(d => d.week === w)) {
      md += '### Day ' + d.day + ' — 신규 목표 ' + d.target + ' / 재풀이 목표 ' + d.reviewTarget + '\n\n';
      const status = progress.days.find(s => s.id === d.id);
      md += `- [${status.complete ? 'x' : ' '}] Day ${d.day} ${status.completionBasis === 'manual' ? '수동 목표' : '풀이 목표'} 완료 · ${status.done}/${status.total} (${status.percent}%)\n\n`;
      if (!d.problems.length) md += '신규 지정 문제 없음. 복습·오답·학습 완료는 직접 기록하세요.\n\n';
      for (const p of d.problems) {
        const result = solved.get(p.key);
        md += '- [' + (result ? 'x' : ' ') + '] [' + escape(p.title) + '](' + p.url + ')';
        if (p.extra) md += ' (후보 밖 참고 기록 · 목표 미반영)';
        if (result) md += ' · [C++ 풀이](https://github.com/' + repo + '/blob/main/' +
          result.code.split('/').map(encodeURIComponent).join('/') + ') · ' + result.evidence;
        md += '\n';
      }
      const review = reviews.filter(r => r.week === w && r.day === d.day);
      const pool = status.additional;
      md += `\n추가 후보 ${pool.candidates.length}개 중 ${pool.required}개 해결 필요 · 현재 ${pool.solved}개 해결 · 목표 반영 ${pool.credited}/${pool.required}\n\n`;
      for (const p of pool.candidates) md += `- [${p.solved ? 'x' : ' '}] [${escape(p.title)}](${p.url}) · ${p.key}\n`;
      if (review.length) md += '\n재풀이 기록: ' + review.length + '회, 그중 정답·힌트 미사용 ' +
        review.filter(r => r.result === 'accepted' && !r.usedHint).length + '회.\n';
      md += '\n';
    }
  }
  return { markdown: formatProgressMarkdown(md), data: { schemaVersion: 2, repository: repo, accepted, registered: planned.size,
    target, ...progress, reviews, evidence: Object.fromEntries([...solved].sort(([a],[b]) => a.localeCompare(b, 'en'))) } };
}

if (process.argv[1] && import.meta.url === pathToFileURL(path.resolve(process.argv[1])).href) {
  const root = process.cwd();
  const output = path.resolve(process.argv[2] || 'generated');
  const result = build(root, process.env.GITHUB_REPOSITORY || 'Nu-LungJi/Problem-Solving-Factory');
  fs.mkdirSync(output, { recursive: true });
  fs.writeFileSync(path.join(output, 'README.md'), result.markdown);
  fs.writeFileSync(path.join(output, 'progress.json'), JSON.stringify(result.data, null, 2) + '\n');
  console.log('등록 ' + result.data.registered + ', 해결 ' + result.data.accepted +
    ', 신규 목표 ' + result.data.target);
}
