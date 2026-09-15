import test from 'node:test';
import assert from 'node:assert/strict';
import fs from 'node:fs';
import os from 'node:os';
import path from 'node:path';
import { build } from '../scripts/progress.mjs';
import { calendarDay, dayOptions, suggestedIndexes, parseSelection, prepareSession, pendingEntries, uploadSolutions, git, inside } from '../scripts/psf.mjs';

const curriculum=new URL('../curriculum/',import.meta.url);
function fixture(t) {
  const base=fs.mkdtempSync(path.join(os.tmpdir(),'psf-workflow-'));
  t.after(()=>{
    assert.ok(path.resolve(base).startsWith(path.resolve(os.tmpdir())+path.sep+'psf-workflow-'));
    fs.rmSync(base,{recursive:true,force:true});
  });
  const root=path.join(base,'Repository with spaces');
  const project=path.join(base,'Algorithm Project');
  fs.mkdirSync(path.join(root,'curriculum'),{recursive:true});
  fs.mkdirSync(project);
  for(const name of ['plan.md','pools.json']) fs.copyFileSync(new URL(name,curriculum),path.join(root,'curriculum',name));
  fs.writeFileSync(path.join(root,'curriculum/records.json'),'[]\n');
  fs.writeFileSync(path.join(root,'.gitignore'),'.psf/\n');
  git(root,['init','-b','main']);
  git(root,['config','user.name','PSF Test']);
  git(root,['config','user.email','psf-test@example.invalid']);
  git(root,['config','commit.gpgsign','false']);
  git(root,['add','.']);
  git(root,['commit','-m','Fixture']);
  return {root,project};
}

test('calendar starts on September 15 and advances daily regardless of completion',()=>{
  const schedule=JSON.parse(fs.readFileSync(new URL('schedule.json',curriculum),'utf8'));
  assert.deepEqual(calendarDay(schedule,'2026-09-15'),{week:1,day:1,index:1});
  assert.deepEqual(calendarDay(schedule,'2026-09-16'),{week:1,day:2,index:2});
  assert.deepEqual(calendarDay(schedule,'2026-09-22'),{week:2,day:1,index:8});
  assert.deepEqual(calendarDay(schedule,'2026-12-07'),{week:12,day:7,index:84});
  assert.equal(calendarDay(schedule,'2026-09-14'),null);
  assert.equal(calendarDay(schedule,'2026-12-08'),null);
  assert.throws(()=>calendarDay(schedule,'2026-02-30'),/날짜/);
});

test('START creates named source files without overwriting existing work or recording acceptance',t=>{
  const {root,project}=fixture(t);
  const data=build(root).data;
  const day=data.days[0];
  const options=dayOptions(data,day);
  assert.deepEqual(suggestedIndexes(day,options),[0,1,2,3]);
  fs.writeFileSync(path.join(project,'1068.cpp'),'// my existing work');
  const session=prepareSession(root,project,day,options.slice(0,2),'2026-09-15');
  assert.deepEqual(session.entries.map(e=>e.localFile),['1068.cpp','1083.cpp']);
  assert.equal(fs.readFileSync(path.join(project,'1068.cpp'),'utf8'),'// my existing work');
  assert.match(fs.readFileSync(path.join(project,'1083.cpp'),'utf8'),/https:\/\/cses.fi\/problemset\/task\/1083\//);
  assert.equal(build(root).data.accepted,0);
  assert.equal(git(root,['status','--porcelain']),'');
  assert.deepEqual(pendingEntries(root,session).map(e=>e.key),['cses:1068']);
});

test('UPLOAD copies code, creates the exact record fields, commits literal user message and is idempotent',t=>{
  const {root,project}=fixture(t);
  const data=build(root).data;
  const session=prepareSession(root,project,data.days[0],dayOptions(data,data.days[0]).slice(0,2),'2026-09-15');
  assert.equal(pendingEntries(root,session).length,0);
  for(const e of session.entries) fs.writeFileSync(path.join(project,e.localFile),'int main(){return 0;}\n');
  const message='Day 1 완료 "quotes" & $(literal) %PATH%';
  const result=uploadSolutions(root,session,session.entries.map((e,i)=>({key:e.key,accepted:true,usedHint:i===1})),message,'2026-09-15');
  assert.equal(result.committed,true);
  assert.equal(git(root,['log','-1','--format=%B']),message);
  const records=JSON.parse(fs.readFileSync(path.join(root,'curriculum/records.json'),'utf8'));
  assert.deepEqual(records[1],{id:'2026-09-15-cses-1083-first',date:'2026-09-15',week:1,day:1,
    url:'https://cses.fi/problemset/task/1083/',code:'solutions/cses/1083.cpp',kind:'solve',result:'accepted',usedHint:true});
  assert.equal(fs.readFileSync(path.join(root,'solutions/cses/1083.cpp'),'utf8'),'int main(){return 0;}\n');
  assert.equal(build(root).data.days[0].requiredSolved,2);
  assert.equal(pendingEntries(root,session).length,0);
  assert.equal(git(root,['status','--porcelain']),'');
  assert.throws(()=>uploadSolutions(root,session,[{key:'cses:1068',accepted:true,usedHint:false}],message),/변경된 풀이/);
});

test('UPLOAD refuses unconfirmed solutions, unchanged templates, dirty repository and traversal',t=>{
  const {root,project}=fixture(t);
  const data=build(root).data;
  const session=prepareSession(root,project,data.days[0],dayOptions(data,data.days[0]).slice(0,1));
  const decision={key:'cses:1068',accepted:true,usedHint:false};
  assert.throws(()=>uploadSolutions(root,session,[decision],'message'),/변경된 풀이/);
  fs.writeFileSync(path.join(project,'1068.cpp'),'int main() {}');
  assert.throws(()=>uploadSolutions(root,session,[{...decision,accepted:false}],'message'),/정답/);
  assert.throws(()=>uploadSolutions(root,session,[decision],'  '),/메시지/);
  const bad=structuredClone(session);bad.entries[0].localFile='../outside.cpp';
  assert.throws(()=>pendingEntries(root,bad),/경로/);
  assert.throws(()=>inside(project,'../secret.cpp'),/경로/);
  fs.writeFileSync(path.join(root,'unrelated.txt'),'user work');
  assert.throws(()=>uploadSolutions(root,session,[decision],'message'),/커밋하지 않은/);
  assert.equal(fs.existsSync(path.join(root,'solutions/cses/1068.cpp')),false);
});

test('revision upload requires overwrite approval and preserves first-solve history',t=>{
  const {root,project}=fixture(t);
  const data=build(root).data;
  const session=prepareSession(root,project,data.days[0],dayOptions(data,data.days[0]).slice(0,1));
  fs.writeFileSync(path.join(project,'1068.cpp'),'int main() {}');
  const decision={key:'cses:1068',accepted:true,usedHint:true};
  uploadSolutions(root,session,[decision],'first','2026-09-15');
  fs.writeFileSync(path.join(project,'1068.cpp'),'int main() {return 0;}');
  assert.throws(()=>uploadSolutions(root,session,[decision],'revision'),/변경 확인/);
  uploadSolutions(root,session,[{...decision,usedHint:false,overwrite:true}],'revision','2026-09-16');
  const records=JSON.parse(fs.readFileSync(path.join(root,'curriculum/records.json'),'utf8'));
  assert.equal(records.length,1);
  assert.equal(records[0].usedHint,true);
  assert.equal(records[0].date,'2026-09-15');
});

test('review sessions use separate files and explicit accepted review records',t=>{
  const {root,project}=fixture(t);
  let data=build(root).data;
  const first=prepareSession(root,project,data.days[0],dayOptions(data,data.days[0]).slice(0,1),'2026-09-15');
  fs.writeFileSync(path.join(project,'1068.cpp'),'int main() {}');
  uploadSolutions(root,first,[{key:'cses:1068',accepted:true,usedHint:false}],'first','2026-09-15');
  data=build(root).data;
  const review=prepareSession(root,project,data.days[6],dayOptions(data,data.days[6]).slice(0,1),'2026-09-21');
  assert.notEqual(review.entries[0].localFile,'1068.cpp');
  fs.writeFileSync(path.join(project,review.entries[0].localFile),'int main() {return 0;}');
  uploadSolutions(root,review,[{key:'cses:1068',accepted:true,usedHint:false}],'review','2026-09-21');
  assert.equal(build(root).data.days[6].reviewSolved,1);
  assert.equal(fs.readFileSync(path.join(root,'solutions/cses/1068.cpp'),'utf8'),'int main() {}');
  assert.match(review.entries[0].recordId,/-review-/);
});

test('candidate and Programmers sessions choose stable destination paths',t=>{
  const {root,project}=fixture(t);
  const data=build(root).data;
  const day=data.days[2];
  const options=dayOptions(data,day);
  const session=prepareSession(root,project,day,[options[0],options[2]]);
  assert.equal(session.entries[0].localFile,'programmers-12925.cpp');
  assert.equal(session.entries[0].dest,'solutions/programmers/12925.cpp');
  assert.equal(session.entries[1].dest,'solutions/leetcode/valid-palindrome.cpp');
  for(const e of session.entries) fs.writeFileSync(path.join(project,e.localFile),'// Accepted\nclass Solution {};');
  uploadSolutions(root,session,session.entries.map(e=>({key:e.key,accepted:true,usedHint:false})),'platforms');
  const progress=build(root).data.days[2];
  assert.equal(progress.requiredSolved,1);
  assert.equal(progress.additional.solved,1);
  assert.deepEqual(parseSelection('1, 2 2',3),[0,1]);
  assert.throws(()=>parseSelection('0',3),/번호/);
});
