import fs from 'node:fs';
import { parsePlan, problemKey } from './progress.mjs';
import { attachPools } from './pools.mjs';
const days = attachPools(parsePlan(fs.readFileSync('curriculum/plan.md','utf8')),
  JSON.parse(fs.readFileSync('curriculum/pools.json','utf8')), problemKey);
let md = '# Day별 추가 문제 후보 풀\n\n';
md += '원본: `pools.json`. `node scripts/render-pools.mjs`로 이 문서를 갱신합니다. 필수 문제와 후보는 서로 중복되지 않으며 각 후보는 한 Day에만 배정됩니다. 추가 목표가 0인 날은 후보가 없습니다.\n\n';
for (const d of days) {
  md += `<a id="${d.id}"></a>\n\n## Week ${d.week} Day ${d.day}\n\n${d.goal}\n\n`;
  md += `후보 ${d.additional.candidates.length}개 중 **${d.additional.required}개 해결** (필수 ${d.problems.length}개 별도, 신규 목표 ${d.target}개).\n\n`;
  for (const p of d.additional.candidates) md += `- [${p.title}](${p.url}) — \`${p.key}\`\n`;
  md += '\n';
}
if (process.argv.includes('--check')) {
  if (fs.readFileSync('curriculum/pools.md','utf8') !== md) throw new Error('pools.md를 다시 생성하세요.');
} else fs.writeFileSync('curriculum/pools.md',md);
