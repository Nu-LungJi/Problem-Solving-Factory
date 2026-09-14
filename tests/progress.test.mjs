import test from 'node:test';
import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import os from 'node:os';
import { parsePlan, build, problemKey } from '../scripts/progress.mjs';

const plan = fs.readFileSync(new URL('../curriculum/plan.md', import.meta.url), 'utf8');
function fixture(t) {
  const root = fs.mkdtempSync(path.join(os.tmpdir(), 'curriculum-test-'));
  t.after(() => fs.rmSync(root, { recursive: true, force: true }));
  fs.mkdirSync(path.join(root, 'curriculum'));
  fs.writeFileSync(path.join(root, 'curriculum/plan.md'), plan);
  fs.writeFileSync(path.join(root, 'curriculum/records.json'), '[]');
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
  assert.equal(r.data.registered,144);
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
  assert.equal(r.data.registered,145);
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
