import test from 'node:test';
import assert from 'node:assert/strict';
import fs from 'node:fs';
import os from 'node:os';
import path from 'node:path';
import { spawnSync } from 'node:child_process';
import { fileURLToPath } from 'node:url';
import { build, parsePlan } from '../scripts/progress.mjs';
import { formatCommitMessage } from '../scripts/commit-message.mjs';
import { calendarDay, dayOptions, suggestedIndexes, parseSelection, prepareSession, prepareToday, pendingEntries, uploadSolutions, commitAndPush, pushUploads, git, inside } from '../scripts/psf.mjs';

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
  fs.writeFileSync(path.join(project,'Algorithm Project.vcxproj'),'<?xml version="1.0"?><Project></Project>\n');
  for(const name of ['plan.md','pools.json','schedule.json','english-titles.json']) fs.copyFileSync(new URL(name,curriculum),path.join(root,'curriculum',name));
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
  const existingFile=path.join(project,'Solved','2026-09-15','1068.cpp');
  fs.mkdirSync(path.dirname(existingFile),{recursive:true});
  fs.writeFileSync(existingFile,'// my existing work');
  const session=prepareSession(root,project,day,options.slice(0,2),'2026-09-15');
  assert.deepEqual(session.entries.map(e=>e.localFile),['Solved/2026-09-15/1068.cpp','Solved/2026-09-15/1083.cpp']);
  assert.equal(fs.readFileSync(path.join(project,session.entries[0].localFile),'utf8'),'// my existing work');
  assert.match(fs.readFileSync(path.join(project,session.entries[1].localFile),'utf8'),/https:\/\/cses.fi\/problemset\/task\/1083\//);
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
  fs.writeFileSync(path.join(project,session.entries[0].localFile),'int main() {}');
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
  fs.writeFileSync(path.join(project,session.entries[0].localFile),'int main() {}');
  const decision={key:'cses:1068',accepted:true,usedHint:true};
  uploadSolutions(root,session,[decision],'first','2026-09-15');
  fs.writeFileSync(path.join(project,session.entries[0].localFile),'int main() {return 0;}');
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
  fs.writeFileSync(path.join(project,first.entries[0].localFile),'int main() {}');
  uploadSolutions(root,first,[{key:'cses:1068',accepted:true,usedHint:false}],'first','2026-09-15');
  data=build(root).data;
  const review=prepareSession(root,project,data.days[6],dayOptions(data,data.days[6]).slice(0,1),'2026-09-21');
  assert.match(review.entries[0].localFile,/^Solved\/2026-09-21\/1068-review-[a-f0-9]{8}\.cpp$/);
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
  const session=prepareSession(root,project,day,[options[0],options[2]],'2026-09-17');
  assert.equal(session.entries[0].localFile,'Solved/2026-09-17/programmers-12925.cpp');
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

test('automatic START skips solved files, preserves existing drafts and reuses today session',t=>{
  const {root,project}=fixture(t);
  fs.mkdirSync(path.join(root,'solutions/cses'),{recursive:true});
  fs.writeFileSync(path.join(root,'solutions/cses/1068.cpp'),'int main(){}');
  fs.writeFileSync(path.join(root,'solutions/cses/1083.cpp'),'int main(){}');
  git(root,['add','.']);git(root,['commit','-m','Solved CSES']);
  const draft=path.join(project,'Solved','2026-09-15','palindrome-number.cpp');
  fs.mkdirSync(path.dirname(draft),{recursive:true});
  fs.writeFileSync(draft,'// unfinished user draft');
  const first=prepareToday(root,project,'2026-09-15').session;
  assert.equal(fs.existsSync(path.join(project,'Solved','2026-09-15','1068.cpp')),false);
  assert.equal(fs.existsSync(path.join(project,'Solved','2026-09-15','1083.cpp')),false);
  assert.deepEqual(first.entries.map(e=>e.key),['leetcode:palindrome-number','leetcode:fizz-buzz','leetcode:add-digits']);
  const before=first.entries.map(e=>fs.readFileSync(path.join(project,e.localFile)));
  const next=prepareToday(root,project,'2026-09-15').session;
  assert.equal(next.id,first.id);
  assert.deepEqual(next.entries,first.entries);
  assert.equal(fs.existsSync(path.join(project,'Solved','2026-09-15','add-digits.cpp')),true);
  next.entries.forEach((e,i)=>assert.deepEqual(fs.readFileSync(path.join(project,e.localFile)),before[i]));
  assert.deepEqual(pendingEntries(root,next).map(e=>e.key),['leetcode:palindrome-number']);
  const tomorrow=prepareToday(root,project,'2026-09-16').session;
  assert.equal(tomorrow.day,2);
  assert.ok(tomorrow.entries.some(e=>e.localFile==='Solved/2026-09-16/1069.cpp'));
  assert.equal(prepareToday(root,project,'2026-12-08').session,null);
});

test('automatic START keeps previous extra candidate drafts and their template hashes',t=>{
  const {root,project}=fixture(t);
  const data=build(root).data;
  const original=prepareSession(root,project,data.days[0],dayOptions(data,data.days[0]).filter(p=>p.group==='후보'),'2026-09-15');
  const resumed=prepareToday(root,project,'2026-09-15').session;
  assert.equal(resumed.id,original.id);
  for(const entry of original.entries) assert.deepEqual(resumed.entries.find(e=>e.key===entry.key),entry);
  assert.equal(pendingEntries(root,resumed).length,0);
});

test('Rider registration adds all files to vcxproj and filters exactly once', {skip:process.platform!=='win32'},t=>{
  const {root,project}=fixture(t);
  const session=prepareToday(root,project,'2026-09-15').session;
  const vcx=path.join(project,'Algorithm Project.vcxproj');
  fs.writeFileSync(vcx,'<?xml version="1.0"?><Project xmlns="http://schemas.microsoft.com/developer/msbuild/2003"><ItemGroup><ClCompile Include="old.cpp" /></ItemGroup></Project>');
  const run=()=>{
    const result=spawnSync('powershell.exe',['-NoProfile','-ExecutionPolicy','Bypass','-File',
      fileURLToPath(new URL('../scripts/open-rider.ps1',import.meta.url)),
      '-ProjectDirectory',project,'-SourceFile',path.join(project,session.entries[0].localFile),
      '-SessionFile',path.join(root,'.psf/session.json'),'-RegisterOnly'],{encoding:'utf8',windowsHide:true});
    assert.equal(result.status,0,result.stderr);
  };
  run();
  const before=fs.readFileSync(vcx,'utf8');
  for(const entry of session.entries) assert.ok(before.includes(`Include="${entry.localFile}"`));
  assert.ok(before.includes('Include="old.cpp"'));
  assert.equal((before.match(/<ExcludedFromBuild>true<\/ExcludedFromBuild>/g)||[]).length,session.entries.length);
  const filters=fs.readFileSync(vcx+'.filters','utf8');
  run();
  assert.equal(fs.readFileSync(vcx,'utf8'),before);
  assert.equal(fs.readFileSync(vcx+'.filters','utf8'),filters);
  assert.equal(fs.readdirSync(path.join(project,'.psf-project-backups')).length,1);
});

test('automatic commit uses backslashes, platform groups, translations and only confirmed problems',()=>{
  const session={week:3,day:5,entries:[
    {key:'programmers:42748',title:'프로그래머스 · K번째수'},
    {key:'leetcode:richest-customer-wealth'},
    {key:'cses:1068',title:'CSES · Weird Algorithm'},
    {key:'leetcode:running-sum-of-1d-array'},
    {key:'leetcode:unsubmitted'},
  ]};
  const decisions=session.entries.map(e=>({key:e.key,accepted:e.key!=='leetcode:unsubmitted'}));
  decisions.push(decisions[0]);
  assert.equal(formatCommitMessage(session,decisions,{'programmers:42748':'Number K'}),
    'Solved Week 3 Day 5 \\ LeetCode: richest-customer-wealth, running-sum-of-1d-array \\ CSES: Weird Algorithm \\ Programmers: Number K');
  assert.throws(()=>formatCommitMessage(session,decisions,{}),/영문 제목/);
  assert.throws(()=>formatCommitMessage(session,[],{}),/정답/);
});

test('all planned Programmers problems have an English commit title',()=>{
  const titles=JSON.parse(fs.readFileSync(new URL('english-titles.json',curriculum),'utf8'));
  const problems=parsePlan(fs.readFileSync(new URL('plan.md',curriculum),'utf8')).flatMap(d=>d.problems)
    .filter(p=>p.key.startsWith('programmers:'));
  assert.equal(problems.length,56);
  for(const p of problems) assert.match(titles[p.key] || '',/^[A-Za-z0-9][A-Za-z0-9 ,'-]*$/);
});

test('automatic commit is pushed to a local bare remote without a message or push prompt',t=>{
  const {root,project}=fixture(t);
  const remote=path.join(path.dirname(root),'remote.git');
  git(root,['init','--bare',remote]);
  git(root,['remote','add','origin',remote]);
  git(root,['push','--set-upstream','origin','main']);
  const data=build(root).data;
  const session=prepareSession(root,project,data.days[0],dayOptions(data,data.days[0]).slice(0,2));
  for(const e of session.entries) fs.writeFileSync(path.join(project,e.localFile),'int main(){}');
  const result=commitAndPush(root,session,session.entries.map(e=>({key:e.key,accepted:true,usedHint:false})),'2026-09-15');
  assert.equal(result.message,'Solved Week 1 Day 1 \\ CSES: Weird Algorithm, Missing Number');
  assert.equal(git(remote,['rev-parse','refs/heads/main']),result.commit);
  assert.equal(git(remote,['log','main','-1','--format=%B']),result.message);
  assert.equal(git(root,['status','--porcelain']),'');
});

test('failed automatic push preserves the commit and can be retried without new records',t=>{
  const {root,project}=fixture(t);
  const data=build(root).data;
  const session=prepareSession(root,project,data.days[0],dayOptions(data,data.days[0]).slice(0,1));
  fs.writeFileSync(path.join(project,session.entries[0].localFile),'int main(){}');
  assert.throws(()=>commitAndPush(root,session,[{key:'cses:1068',accepted:true,usedHint:false}]),/로컬 커밋은 보존/);
  const head=git(root,['rev-parse','HEAD']);
  assert.equal(pendingEntries(root,session).length,0);
  const remote=path.join(path.dirname(root),'retry.git');
  git(root,['init','--bare',remote]);
  git(root,['remote','add','origin',remote]);
  git(root,['config','branch.main.remote','origin']);
  git(root,['config','branch.main.merge','refs/heads/main']);
  pushUploads(root);
  assert.equal(git(remote,['rev-parse','refs/heads/main']),head);
  assert.equal(JSON.parse(fs.readFileSync(path.join(root,'curriculum/records.json'),'utf8')).length,1);
});
