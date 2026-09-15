import test from 'node:test';
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import os from 'node:os';
import { parsePlan, build, problemKey } from '../scripts/progress.mjs';
import { attachPools } from '../scripts/pools.mjs';

const plan = fs.readFileSync(new URL('../curriculum/plan.md', import.meta.url), 'utf8');
const pools = JSON.parse(fs.readFileSync(new URL('../curriculum/pools.json', import.meta.url), 'utf8'));
function fixture(t) {
  const root = fs.mkdtempSync(path.join(os.tmpdir(), 'curriculum-test-'));
  t.after(() => fs.rmSync(root, { recursive: true, force: true }));
  fs.mkdirSync(path.join(root, 'curriculum'));
  fs.writeFileSync(path.join(root, 'curriculum/plan.md'), plan);
  fs.writeFileSync(path.join(root, 'curriculum/records.json'), '[]');
  fs.writeFileSync(path.join(root, 'curriculum/pools.json'), JSON.stringify(pools));
  return root;
}
function write(root, file, content) {
  fs.mkdirSync(path.dirname(path.join(root, file)), { recursive: true });
  fs.writeFileSync(path.join(root, file), content);
}
test('84 days, correct targets, and all specified links', () => {
  const days = parsePlan(plan);
  assert.equal(days.length,84);
  assert.equal(days.reduce((s,d)=>s+d.target,0),208);
  assert.equal(days.reduce((s,d)=>s+d.reviewTarget,0),75);
  assert.equal(days.flatMap(d=>d.problems).length,144);
});
test('empty repository never marks any problem solved', t => {
  const r = build(fixture(t));
  assert.equal(r.data.accepted,0);
  assert.equal(r.data.registered,254);
  assert.ok(!r.markdown.includes('- [x]'));
});
test('imports language folders, deduplicates, and ignores mismatched README', t => {
  const root=fixture(t);
  for(const prefix of ['C++/','']) {
    const folder=prefix+'프로그래머스/1/42576. 완주하지 못한 선수/';
    write(root,folder+'풀이.cpp','int main() {}');
    write(root,folder+'README.md','[문제 링크](https://school.programmers.co.kr/learn/courses/30/lessons/42576)');
  }
  write(root,'프로그래머스/1/42577.전화번호/풀이.cpp','int main() {}');
  write(root,'프로그래머스/1/42577.전화번호/README.md','https://school.programmers.co.kr/learn/courses/30/lessons/99999');
  const r=build(root);
  assert.equal(r.data.accepted,1);
  assert.match(r.markdown,/\[x\].*완주하지 못한 선수/);
});
test('manual accepted plus repeat attempts; extra problem only assigned once', t => {
  const root=fixture(t);
  write(root,'solutions/a.cpp','int main() {}');
  const common={date:'2026-09-15',week:1,day:1,url:'https://cses.fi/problemset/task/1068/',code:'solutions/a.cpp',usedHint:false};
  const records=[
    {...common,id:'a',kind:'solve',result:'accepted'},
    {...common,id:'b',day:7,kind:'review',result:'attempted'},
    {...common,id:'c',url:'https://cses.fi/problemset/task/1070/',kind:'solve',result:'accepted'}
  ];
  write(root,'curriculum/records.json',JSON.stringify(records));
  const r=build(root);
  assert.equal(r.data.accepted,2);
  assert.equal(r.data.registered,255);
  assert.equal(r.data.reviews.length,1);
  assert.equal(r.data.days[0].problems.filter(p=>p.extra).length,1);
  assert.equal(build(root).markdown,r.markdown);
});
test('rejects duplicate attempt IDs and escaping code paths', t => {
  const root=fixture(t);
  write(root,'solutions/a.cpp','int main() {}');
  const r={id:'a',date:'2026-09-15',week:1,day:1,url:'https://cses.fi/problemset/task/1068/',code:'solutions/a.cpp',usedHint:false,kind:'solve',result:'accepted'};
  write(root,'curriculum/records.json',JSON.stringify([r,r]));
  assert.throws(()=>build(root),/중복/);
  write(root,'curriculum/records.json',JSON.stringify([{...r,code:'../secret.cpp'}]));
  assert.throws(()=>build(root),/상대 경로/);
});
test('problem identity ignores query and fragments',()=>{
  assert.equal(problemKey('https://leetcode.com/problems/two-sum/?x=1#test'),'leetcode:two-sum');
  assert.throws(()=>problemKey('https://example.com/problems/two-sum/'));
});

test('local CSES and LeetCode adapters advance assigned problems only', t => {
  const root = fixture(t);
  write(root, 'solutions/cses/1068.cpp', 'int main() {}');
  write(root, 'solutions/leetcode/valid-anagram.cpp', 'class Solution {};');
  write(root, 'solutions/cses/1068.cc', 'int main() {}');
  write(root, 'solutions/cses/1083.cpp', '   ');
  write(root, 'solutions/cses/999999.cpp', 'int main() {}');
  const { data } = build(root);
  assert.equal(data.schemaVersion, 2);
  assert.equal(data.accepted, 2);
  assert.equal(data.days[0].newSolved, 1);
  assert.equal(data.days[0].complete, false);
  assert.equal(data.overall.done, 2);
  assert.equal(data.days.flatMap(d => d.problems).find(p => p.key === 'leetcode:valid-anagram').solved, true);
});

test('real week fixture reaches Day then Week completion without modifying the plan', t => {
  const root = fixture(t);
  const week = attachPools(parsePlan(plan), structuredClone(pools), problemKey).filter(d => d.week === 1);
  const records = [];
  const record = (d, url, kind, index) => {
    const code = `manual/${kind}-${d.day}-${index}.cpp`;
    write(root, code, 'int main() {}');
    records.push({ id: `${kind}-${d.day}-${index}`, date: '2026-09-15', week: 1,
      day: d.day, url, code, kind, result: 'accepted', usedHint: false });
  };
  for (const d of week) {
    d.problems.forEach((p,i) => record(d, p.url, 'solve', i));
    d.additional.candidates.slice(0, d.additional.required).forEach((p,i) => record(d, p.url, 'solve', i + 10));
  }
  write(root, 'curriculum/records.json', JSON.stringify(records));
  let data = build(root).data;
  assert.equal(data.weeks[0].completedDays, 6);
  assert.equal(data.weeks[0].complete, false);
  assert.equal(data.days[6].reviewSolved, 0);
  for (let i = 0; i < 6; i++) record(week[6], week.flatMap(d => d.problems)[i].url, 'review', i);
  write(root, 'curriculum/records.json', JSON.stringify(records));
  data = build(root).data;
  assert.equal(data.weeks[0].complete, true);
  assert.equal(data.weeks[0].percent, 100);
  assert.equal(data.overall.completedWeeks, 1);
  assert.equal(data.overall.done, 30);
  assert.equal(data.overall.total, 283);
  assert.equal(fs.readFileSync(path.join(root, 'curriculum/plan.md'), 'utf8'), plan);
  assert.deepEqual(build(root).data, data);
});

test('failed reviews do not finish review goals; manual-only day uses original checklist', t => {
  const root = fixture(t);
  write(root, 'manual/review.cpp', 'int main() {}');
  write(root, 'curriculum/records.json', JSON.stringify([{
    id: 'review', date: '2026-09-15', week: 1, day: 7,
    url: 'https://cses.fi/problemset/task/1068/', code: 'manual/review.cpp',
    kind: 'review', result: 'attempted', usedHint: false,
  }]));
  let data = build(root).data;
  assert.equal(data.days[6].reviewAttempts, 1);
  assert.equal(data.days[6].reviewSolved, 0);
  assert.equal(data.days[83].complete, false);
  write(root, 'curriculum/plan.md', plan.replace('- [ ] W12-D7:', '- [x] W12-D7:'));
  data = build(root).data;
  assert.equal(data.days[83].complete, true);
  assert.equal(data.days[83].completionBasis, 'manual');
});

test('rejects invalid dates and competing owners for extra problems', t => {
  const root = fixture(t);
  write(root, 'manual/a.cpp', 'int main() {}');
  const r = {id:'a',date:'2026-02-30',week:1,day:1,url:'https://cses.fi/problemset/task/999999/',
    code:'manual/a.cpp',kind:'solve',result:'accepted',usedHint:false};
  write(root,'curriculum/records.json',JSON.stringify([r]));
  assert.throws(() => build(root), /기록 필드/);
  r.date = '2026-09-15';
  write(root,'curriculum/records.json',JSON.stringify([r, {...r,id:'b',day:2}]));
  assert.throws(() => build(root), /중복 등록/);
});

test('all 84 pools preserve targets, are unique, and match plan links', () => {
  const days = attachPools(parsePlan(plan), structuredClone(pools), problemKey);
  assert.equal(days.filter(d => d.additional.required > 0).length, 46);
  assert.equal(days.reduce((s,d) => s + d.additional.required, 0), 64);
  assert.equal(days.reduce((s,d) => s + d.additional.candidates.length, 0), 110);
  assert.doesNotMatch(plan, /같은 주제 미풀이 \d+개 추가/);
  for (const d of days.filter(d => d.additional.required)) {
    assert.ok(plan.includes(`[후보 ${d.additional.candidates.length}개 중 ${d.additional.required}개 해결](pools.md#${d.id})`));
  }
  const bad = structuredClone(pools);
  bad.days[0].candidates[0] = bad.days[1].candidates[0];
  assert.throws(() => attachPools(parsePlan(plan), bad, problemKey), /중복/);
  const missing = structuredClone(pools);
  missing.days.pop();
  assert.throws(() => attachPools(parsePlan(plan), missing, problemKey), /모든 Day/);
  const quota = structuredClone(pools);
  quota.days[0].required = 1;
  assert.throws(() => attachPools(parsePlan(plan), quota, problemKey), /목표/);
});

test('N-of-M candidate files advance Day and overall without requiring every candidate', t => {
  const root = fixture(t);
  const candidates = pools.days[0].candidates;
  write(root, 'solutions/cses/1068.cpp', 'int main() {}');
  write(root, 'solutions/cses/1083.cpp', 'int main() {}');
  const solve = (p, ext='cpp') => write(root, `solutions/leetcode/${p.problemId}.${ext}`, 'class Solution {};');
  solve(candidates[0]);
  solve(candidates[0], 'cc');
  let data = build(root).data;
  assert.equal(data.days[0].additional.solved, 1);
  assert.equal(data.days[0].complete, false);
  assert.equal(data.days[0].done, 3);
  solve(candidates[1]);
  data = build(root).data;
  assert.equal(data.days[0].complete, true);
  assert.equal(data.days[0].additional.candidates[2].solved, false);
  assert.equal(data.weeks[0].completedDays, 1);
  assert.equal(data.overall.done, 4);
  assert.match(build(root).markdown, /후보 3개 중 2개 해결 필요 · 현재 2개 해결/);
  solve(candidates[2]);
  data = build(root).data;
  assert.equal(data.days[0].additional.solved, 3);
  assert.equal(data.days[0].additional.credited, 2);
  assert.equal(data.overall.done, 4);
});

test('extra candidates and legacy outside-pool records cannot replace required problems', t => {
  const root = fixture(t);
  for (const p of pools.days[0].candidates)
    write(root, `solutions/leetcode/${p.problemId}.cpp`, 'class Solution {};');
  write(root, 'manual/extra.cpp', 'int main() {}');
  write(root, 'curriculum/records.json', JSON.stringify([{
    id:'legacy',date:'2026-09-15',week:1,day:1,url:'https://cses.fi/problemset/task/1070/',
    code:'manual/extra.cpp',kind:'solve',result:'accepted',usedHint:false,
  }]));
  const { data } = build(root);
  assert.equal(data.days[0].additional.complete, true);
  assert.equal(data.days[0].requiredSolved, 0);
  assert.equal(data.days[0].done, 2);
  assert.equal(data.days[0].complete, false);
  assert.equal(data.days[0].problems.find(p => p.extra).solved, true);
});

test('review record copies cannot inflate review goals', t => {
  const root=fixture(t);
  write(root,'manual/review.cpp','int main() {}');
  const common={date:'2026-09-15',week:1,day:7,url:'https://cses.fi/problemset/task/1068/',
    code:'manual/review.cpp',kind:'review',result:'accepted',usedHint:false};
  write(root,'curriculum/records.json',JSON.stringify(Array.from({length:6},(_,i)=>({...common,id:`copy-${i}`}))));
  const day=build(root).data.days[6];
  assert.equal(day.reviewAttempts,6);
  assert.equal(day.reviewSolved,1);
  assert.equal(day.complete,false);
});
