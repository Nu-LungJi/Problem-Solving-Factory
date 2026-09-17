import fs from 'node:fs';
import path from 'node:path';
import os from 'node:os';
import { createHash, randomUUID } from 'node:crypto';
import { spawnSync } from 'node:child_process';
import { createInterface } from 'node:readline';
import { fileURLToPath, pathToFileURL } from 'node:url';
import { build, problemKey } from './progress.mjs';
import { formatCommitMessage } from './commit-message.mjs';

const hash = content => createHash('sha256').update(content).digest('hex');
const readJson = file => JSON.parse(fs.readFileSync(file, 'utf8').replace(/^\uFEFF/, ''));
const saveJson = (file, value) => {
  fs.mkdirSync(path.dirname(file), { recursive: true });
  const tmp = `${file}.${randomUUID()}.tmp`;
  fs.writeFileSync(tmp, JSON.stringify(value, null, 2) + '\n');
  fs.renameSync(tmp, file);
};
export const localDate = (date = new Date()) => `${date.getFullYear()}-${String(date.getMonth()+1).padStart(2,'0')}-${String(date.getDate()).padStart(2,'0')}`;

export function calendarDay(schedule, date = localDate()) {
  const parse = value => {
    if (!/^\d{4}-\d{2}-\d{2}$/.test(value)) throw new Error('날짜 형식 오류');
    const ms=Date.parse(value+'T00:00:00Z');
    if(!Number.isFinite(ms) || new Date(ms).toISOString().slice(0,10)!==value) throw new Error('날짜 오류');
    return ms;
  };
  if(schedule.daysPerWeek!==7 || schedule.totalWeeks!==12) throw new Error('12주/7일 일정이 필요합니다.');
  const offset=(parse(date)-parse(schedule.startDate))/86400000;
  if(offset<0 || offset>=84) return null;
  return { week:Math.floor(offset/7)+1, day:offset%7+1, index:offset+1 };
}

export function git(root, args) {
  const r = spawnSync('git', ['-C', root, ...args], { encoding: 'utf8', windowsHide: true });
  if (r.error || r.status !== 0) throw new Error(r.error?.message || r.stderr.trim() || r.stdout.trim() || 'git 실패');
  return r.stdout.trim();
}

export function assertClean(root) {
  if (git(root, ['status', '--porcelain']))
    throw new Error('저장소에 커밋하지 않은 변경이 있습니다. 먼저 확인·커밋한 뒤 다시 실행하세요. 자동 덮어쓰기나 stash는 하지 않습니다.');
  if (!git(root, ['branch', '--show-current'])) throw new Error('브랜치에 checkout한 뒤 실행하세요.');
}

// Reject traversal and junction/symlink escapes before reading or writing user files.
export function inside(base, relative) {
  if (typeof relative !== 'string' || path.isAbsolute(relative) || relative.includes('\\') ||
      relative.split('/').some(p => !p || p === '.' || p === '..')) throw new Error('잘못된 상대 경로');
  const root = fs.realpathSync(base);
  let current = root;
  for (const segment of relative.split('/')) {
    current = path.join(current, segment);
    if (fs.existsSync(current) && fs.lstatSync(current).isSymbolicLink()) throw new Error('링크 경로는 허용하지 않습니다: ' + relative);
  }
  return current;
}

function identity(p) {
  const key = problemKey(p.url);
  if (key !== p.key) throw new Error('문제 ID와 URL이 다릅니다.');
  const [platform, problemId] = key.split(':');
  if (!/^(cses|programmers|leetcode)$/.test(platform) || !/^[a-z0-9]+(?:-[a-z0-9]+)*$/.test(problemId))
    throw new Error('지원하지 않는 문제 ID');
  return { platform, problemId };
}

export function dayOptions(data, day) {
  if (day.reviewTarget) {
    const all = data.days.filter(d => d.week < day.week || d.week === day.week && d.day < day.day)
      .flatMap(d => [...d.problems, ...d.additional.candidates]);
    return [...new Map(all.filter(p => data.evidence[p.key]).map(p => [p.key, { ...p, kind:'review' }])).values()];
  }
  return [...day.problems.filter(p => !p.extra).map(p => ({...p, kind:'solve', group:'필수'})),
    ...day.additional.candidates.map(p => ({...p, kind:'solve', group:'후보'}))];
}

export function suggestedIndexes(day, options) {
  if (day.reviewTarget) return options.slice(0, Math.max(0, day.reviewTarget-day.reviewSolved)).map((_,i)=>i);
  let needed = Math.max(0, day.additional.required-day.additional.credited);
  return options.flatMap((p,i) => !p.solved && (p.group === '필수' || needed-- > 0) ? [i] : []);
}

export function parseSelection(text, count) {
  if (!text.trim()) return [];
  const values = text.trim().split(/[\s,]+/);
  if (values.some(s => !/^\d+$/.test(s) || +s < 1 || +s > count)) throw new Error('목록의 번호를 쉼표로 구분해 입력하세요.');
  return [...new Set(values.map(s=>+s-1))];
}

function addToVcxproj(projectRoot, cppFile) {
  const projects = fs.readdirSync(projectRoot)
    .filter(file => file.endsWith('.vcxproj'));

  if (projects.length !== 1) {
    throw new Error('Rider 프로젝트 루트에 .vcxproj가 정확히 1개 있어야 합니다.');
  }

  const projectFile = path.join(projectRoot, projects[0]);

  let xml = fs.readFileSync(projectFile, 'utf8');

  const relative = path
    .relative(projectRoot, cppFile)
    .replace(/\//g, '\\');

  // 이미 등록돼 있으면 아무것도 안 함
  if (xml.includes(`Include="${relative}"`)) {
    return;
  }

  const entry = `  <ItemGroup>\n    <ClCompile Include="${relative}" />\n  </ItemGroup>\n`;

  const index = xml.lastIndexOf('</Project>');

  if (index === -1) {
    throw new Error('.vcxproj 파일 구조를 읽을 수 없습니다.');
  }

  xml =
    xml.slice(0, index) +
    entry +
    xml.slice(index);

  fs.writeFileSync(projectFile, xml, 'utf8');
}

export function prepareSession(root, project, day, selected, date = localDate(), previous = null) {
  if (!selected.length) throw new Error('선택한 문제가 없습니다.');
  fs.mkdirSync(project, { recursive: true });
  const reuse = previous?.week===day.week && previous?.day===day.day && previous?.project===fs.realpathSync(project);
  const session = { version:1, id:reuse ? previous.id : randomUUID(), date, week:day.week, day:day.day,
    project:fs.realpathSync(project), entries:[] };
  for (const p of selected) {
    const prior = reuse && previous.entries.find(e=>e.key===p.key);
    const { platform, problemId } = identity(p);
    const prefix = platform === 'programmers' ? 'programmers-' : '';
    const dayFolder = `Solved/${date}`;

const fileName = p.kind === 'review'
  ? `${prefix}${problemId}-review-${session.id.slice(0,8)}.cpp`
  : `${prefix}${problemId}.cpp`;

const localFile = prior?.localFile || `${dayFolder}/${fileName}`;
    const dest = p.kind === 'review' ? `solutions/reviews/week-${day.week}-day-${day.day}/${platform}/${problemId}-${session.id}.cpp`
      : `solutions/${platform}/${problemId}.cpp`;
    const file = inside(project, localFile);

const template = `// ${p.url}\n// Week ${day.week} Day ${day.day}\n` +
  (platform === 'cses'
    ? '#include <iostream>\n#include <vector>\n#include <algorithm>\n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n    // TODO: implement your solution.\n    return 0;\n}\n'
    : '// Paste the platform function signature, then implement your solution.\n#include <string>\n#include <vector>\n#include <algorithm>\nusing namespace std;\n\n');

let templateHash =
  prior?.templateHash ||
  (fs.existsSync(file) && hash(fs.readFileSync(file)) === hash(template)
    ? hash(template)
    : null);

if (!fs.existsSync(file)) {
  fs.mkdirSync(path.dirname(file), { recursive: true });
  fs.writeFileSync(file, template, { flag:'wx' });
  templateHash = hash(template);
}

// 새 파일뿐 아니라 기존 초안도 Rider 프로젝트에 등록되어 있는지 보장합니다.
addToVcxproj(project, file);
    session.entries.push({ key:p.key, url:p.url, title:p.title, platform, problemId, kind:p.kind || 'solve',
      localFile, dest, templateHash, uploadedHash:prior?.uploadedHash || null, ...(prior?.recordId ? {recordId:prior.recordId} : {}) });
  }
  const sessionFile = inside(root, '.psf/session.json');
  if (fs.existsSync(sessionFile) && !reuse) {
    const old = readJson(sessionFile);
    saveJson(inside(root, `.psf/history/${randomUUID()}.json`), old);
  }
  saveJson(sessionFile, session);
  return session;
}

// Existing drafts occupy their candidate slot; rerunning START must not create extra candidates.
export function prepareToday(root, project, date = localDate()) {
  const scheduled=calendarDay(readJson(path.join(root,'curriculum/schedule.json')),date);
  if(!scheduled) return {session:null, message:`${date}: 12주 일정 기간 밖입니다.`};
  const data=build(root).data;
  const day=data.days.find(d=>d.week===scheduled.week && d.day===scheduled.day);
  if(!day.total) return {session:null,message:`Week ${day.week} Day ${day.day}: 수동 학습일입니다.`};
  fs.mkdirSync(project,{recursive:true});
  const sessionFile=inside(root,'.psf/session.json');
  const previous=fs.existsSync(sessionFile)?readJson(sessionFile):null;
  const same=previous?.week===day.week && previous?.day===day.day && previous?.project===fs.realpathSync(project);
  const pendingKeys=new Set(same?previous.entries.map(e=>e.key):[]);
  const options=dayOptions(data,day);
  const reviewed=new Set(data.reviews.filter(r=>r.week===day.week && r.day===day.day && r.result==='accepted').map(r=>r.key));
  const remaining=options.filter(p=>day.reviewTarget?!reviewed.has(p.key):!data.evidence[p.key]);
  const existing=p=>{
    const prior=same && previous.entries.find(e=>e.key===p.key);
    if(prior) return fs.existsSync(inside(project,prior.localFile));
    if(p.kind==='review') return false;
    const {platform,problemId}=identity(p);
    const prefix=platform==='programmers'?'programmers-':'';
    return fs.existsSync(inside(project,`Solved/${date}/${prefix}${problemId}.cpp`));
  };
  const required=remaining.filter(p=>p.group==='필수');
  const pool=remaining.filter(p=>p.group!=='필수');
  // Stable order: resume existing work, then choose new candidates in curriculum order.
  const priority=p=>same && pendingKeys.has(p.key) ? previous.entries.findIndex(e=>e.key===p.key) : existing(p)?1000:2000;
  pool.sort((a,b)=>priority(a)-priority(b));
  const chosen = day.reviewTarget
  ? pool.slice(0, Math.max(0, day.reviewTarget - day.reviewSolved))
  : pool;
  for(const p of pool) if(pendingKeys.has(p.key) && !chosen.some(c=>c.key===p.key)) chosen.push(p);
  const selected=[...required,...chosen];
  if(!selected.length) return {session:null,message:`Week ${day.week} Day ${day.day}: 새로 준비할 문제가 없습니다.`};
  const session=prepareSession(root,project,day,selected,date,same?previous:null);
  return {session,message:`${date} · Week ${day.week} Day ${day.day}: ${session.entries.map(e=>e.localFile).join(', ')}`};
}

function validateSession(root, session) {
  if (session.version !== 1 || !Array.isArray(session.entries) || !session.entries.length ||
      !/^[a-f0-9-]{36}$/.test(session.id) || !path.isAbsolute(session.project)) throw new Error('세션 파일 오류');
  const data = build(root).data;
  const day = data.days.find(d => d.week === session.week && d.day === session.day);
  if (!day) throw new Error('세션 Day가 커리큘럼에 없습니다.');
  const allowed = new Set(dayOptions(data,day).map(p=>p.key));
  const unique = new Set();
  for (const entry of session.entries) {
    const ident = identity(entry);
    if (entry.platform !== ident.platform || entry.problemId !== ident.problemId || unique.has(entry.key) ||
        !allowed.has(entry.key) || entry.kind !== (day.reviewTarget ? 'review':'solve')) throw new Error('세션 문제 매핑 오류');
    unique.add(entry.key);
    const expected = entry.kind === 'review' ? `solutions/reviews/week-${day.week}-day-${day.day}/${entry.platform}/${entry.problemId}-${session.id}.cpp`
      : `solutions/${entry.platform}/${entry.problemId}.cpp`;
    if (entry.dest !== expected || !entry.localFile.endsWith('.cpp')) throw new Error('세션 경로 오류');
    inside(session.project,entry.localFile);
    inside(root,entry.dest);
  }
  return session;
}

export function pendingEntries(root, session) {
  validateSession(root,session);
  return session.entries.filter(e => {
    const file = inside(session.project,e.localFile);
    if (!fs.existsSync(file) || !fs.statSync(file).isFile()) return false;
    const code = fs.readFileSync(file);
    return code.toString('utf8').trim() && hash(code) !== e.templateHash && hash(code) !== e.uploadedHash;
  });
}

// accepted decisions are explicit user confirmations, never inferred from a .cpp file.
export function uploadSolutions(root, session, decisions, message, date = localDate()) {
  assertClean(root);
  validateSession(root,session);
  if (!message.trim()) throw new Error('커밋 메시지가 비어 있습니다.');
  const eligible = new Set(pendingEntries(root,session).map(e=>e.key));
  const recordsPath = inside(root,'curriculum/records.json');
  const records = readJson(recordsPath);
  const writes = [];
  const updates = [];
  const seen = new Set();
  for (const decision of decisions) {
    if (decision.accepted !== true || typeof decision.usedHint !== 'boolean' || seen.has(decision.key)) throw new Error('정답·힌트 확인이 필요합니다.');
    seen.add(decision.key);
    const entry = session.entries.find(e=>e.key===decision.key);
    if (!entry || !eligible.has(entry.key)) throw new Error('변경된 풀이만 업로드할 수 있습니다.');
    const code = fs.readFileSync(inside(session.project,entry.localFile));
    const target = inside(root,entry.dest);
    if (fs.existsSync(target) && !fs.readFileSync(target).equals(code) && decision.overwrite !== true)
      throw new Error('기존 저장소 풀이 변경 확인이 필요합니다: '+entry.dest);
    const existing = records.find(r=>r.kind==='solve' && r.result==='accepted' && problemKey(r.url)===entry.key);
    let id = entry.recordId || (entry.kind==='solve' ? `${date}-${entry.platform}-${entry.problemId}-first` : `${date}-${entry.platform}-${entry.problemId}-review-${session.id}`);
    // Preserve earlier attempted records even when they used the conventional first-solve id.
    if (!entry.recordId && !existing && records.some(r=>r.id===id)) id += `-${session.id}`;
    if (!(entry.kind==='solve' && existing) && !records.some(r=>r.id===id)) records.push({
      id, date, week:session.week, day:session.day, url:entry.url, code:entry.dest,
      kind:entry.kind, result:'accepted', usedHint:decision.usedHint,
    });
    writes.push({ file:target, data:code, relative:entry.dest });
    updates.push({entry, uploadedHash:hash(code), recordId:entry.kind==='solve' && existing ? existing.id : id});
  }
  if (!writes.length) throw new Error('정답 확인한 풀이가 없습니다.');
  writes.push({file:recordsPath, data:Buffer.from(JSON.stringify(records,null,2)+'\n'), relative:'curriculum/records.json'});
  const backups = writes.map(w=>({...w, previous:fs.existsSync(w.file)?fs.readFileSync(w.file):null}));
  try {
    for (const w of writes) {
      fs.mkdirSync(path.dirname(w.file),{recursive:true});
      fs.writeFileSync(w.file,w.data);
    }
    build(root); // Same validation as Actions, before staging or committing.
  } catch(error) {
    for (const w of backups) {
      if (w.previous !== null) fs.writeFileSync(w.file,w.previous);
      else if (fs.existsSync(w.file)) fs.unlinkSync(w.file);
    }
    throw error;
  }
  const changed = writes.filter(w=>!backups.find(b=>b.file===w.file).previous?.equals(w.data)).map(w=>w.relative);
  if (changed.length) {
    git(root,['add','--',...changed]);
    // No shell: quotes, Korean, %, &, and other message characters stay literal.
    try { git(root,['commit','-m',message]); }
    catch(error) { throw new Error('파일과 기록은 저장됐지만 커밋이 실패했습니다. 변경을 보존했습니다. git status 확인 후 직접 커밋하세요.\n'+error.message); }
  }
  for (const u of updates) Object.assign(u.entry,{uploadedHash:u.uploadedHash,recordId:u.recordId});
  saveJson(inside(root,'.psf/session.json'),session);
  return { committed:changed.length>0, files:changed, commit:git(root,['rev-parse','HEAD']) };
}

function defaultProject() {
  if (process.env.PSF_PROJECT) return path.resolve(process.env.PSF_PROJECT);
  let docs = path.join(os.homedir(),'Documents');
  if (process.platform==='win32') {
    const r=spawnSync('powershell.exe',['-NoProfile','-Command','[Environment]::GetFolderPath("MyDocuments")'],{encoding:'utf8',windowsHide:true});
    if(r.status===0 && r.stdout.trim()) docs=r.stdout.trim();
  }
  return path.join(docs,'Rider','PSFactory');
}

export function pushUploads(root) {
  try { return git(root,['push']); }
  catch(error) { throw new Error('자동 push에 실패했습니다. 로컬 커밋은 보존되어 있습니다. 연결/권한 확인 후 UPLOAD를 다시 실행하세요.\n'+error.message); }
}

export function commitAndPush(root,session,decisions,date=localDate()) {
  const message=formatCommitMessage(session,decisions,readJson(path.join(root,'curriculum/english-titles.json')));
  const result=uploadSolutions(root,session,decisions,message,date);
  pushUploads(root);
  return {...result,message};
}

function openRider(root, session) {
  const r=spawnSync('powershell.exe',['-NoProfile','-ExecutionPolicy','Bypass','-File',path.join(root,'scripts','open-rider.ps1'),
    '-ProjectDirectory',session.project,'-SourceFile',inside(session.project,session.entries[0].localFile),
    '-SessionFile',inside(root,'.psf/session.json')],{stdio:'inherit',windowsHide:true});
  if(r.error || r.status!==0) throw new Error('파일은 준비됐지만 Rider 실행에 실패했습니다. PSF_RIDER에 Rider 실행 파일 경로를 지정하세요.');
}

export async function main(action, root) {
  const rl=createInterface({input:process.stdin,crlfDelay:Infinity});
  const input=rl[Symbol.asyncIterator]();
  const ask=async text=>{process.stdout.write(text); const r=await input.next(); if(r.done) throw new Error('입력이 취소됐습니다.'); return r.value.trim();};
  const yes=async text=>(await ask(text+' [y/N]: ')).toLowerCase()==='y';
  const hint=async()=>{ while(true) {const a=(await ask('힌트/해설을 사용했나요? [y/n]: ')).toLowerCase(); if(a==='y'||a==='n')return a==='y';} };
  const sync=()=>{assertClean(root); console.log('원격 변경을 가져옵니다 (git pull --ff-only).'); console.log(git(root,['pull','--ff-only']));};
  try {
    if(!['start','upload'].includes(action)) throw new Error('PSF_START.bat 또는 PSF_UPLOAD.bat을 실행하세요.');
    sync();
    const sessionFile=inside(root,'.psf/session.json');
    if(action==='start') {
      const result=prepareToday(root,defaultProject());
      console.log(result.message);
      if(result.session) openRider(root,result.session);
    } else {
      if(!fs.existsSync(sessionFile)) throw new Error('먼저 PSF_START로 Day와 문제를 선택하세요.');
      const session=readJson(sessionFile);
      const pending=pendingEntries(root,session);
      if(!pending.length) {console.log('새로 업로드할 풀이가 없습니다. 빈 템플릿과 이미 업로드한 내용은 제외합니다.'); pushUploads(root); console.log('GitHub 동기화 완료.'); return;}
      const decisions=[];
      for(const e of pending) {
        console.log(`\n${e.localFile} → ${e.dest}\n${e.url}`);
        if(!await yes('이 문제를 정답 제출(Accepted)했나요?')) continue;
        const usedHint=await hint();
        const target=inside(root,e.dest);
        const differs=fs.existsSync(target) && !fs.readFileSync(target).equals(fs.readFileSync(inside(session.project,e.localFile)));
        if(differs && !await yes('저장소의 기존 풀이를 이 코드로 갱신할까요?')) continue;
        decisions.push({key:e.key,accepted:true,usedHint,overwrite:differs});
      }
      if(!decisions.length) {console.log('업로드할 정답을 선택하지 않았습니다.'); return;}
      const result=commitAndPush(root,session,decisions);
      console.log(result.committed ? `커밋 완료: ${result.commit.slice(0,7)}` : '내용이 같아 새 커밋을 만들지 않았습니다.');
      console.log(result.message);
      console.log('GitHub push 완료.');
    }
  } finally {rl.close();}
}

if(process.argv[1] && import.meta.url===pathToFileURL(path.resolve(process.argv[1])).href) {
  const root=path.resolve(path.dirname(fileURLToPath(import.meta.url)),'..');
  main(process.argv[2],root).catch(error=>{console.error('\nPSF: '+error.message); process.exitCode=1;});
}
