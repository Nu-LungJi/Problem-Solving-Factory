import fs from 'node:fs';
import path from 'node:path';
import { pathToFileURL } from 'node:url';
import { build, problemKey } from './progress.mjs';

const dayMs=86400000;
function dateMs(date) {
  if(typeof date!=='string' || !/^\d{4}-\d{2}-\d{2}$/.test(date)) throw new Error('활동 날짜 형식 오류');
  const value=Date.parse(date+'T00:00:00Z');
  if(!Number.isFinite(value) || new Date(value).toISOString().slice(0,10)!==date) throw new Error('활동 날짜 오류');
  return value;
}

export function activityData(records,startDate) {
  const start=dateMs(startDate);
  const days=Array.from({length:84},(_,i)=>({date:new Date(start+i*dayMs).toISOString().slice(0,10),solves:0,reviews:0,hints:0,total:0}));
  const seen=new Set();
  // First accepted solve per problem, and one accepted review per curriculum Day/problem.
  const ordered=[...records].sort((a,b)=>String(a.date).localeCompare(String(b.date)));
  for(const r of ordered) {
    if(r.result!=='accepted') continue;
    if(!['solve','review'].includes(r.kind) || typeof r.usedHint!=='boolean') throw new Error('활동 기록 필드 오류');
    const when=dateMs(r.date);
    const key=problemKey(r.url);
    const event=r.kind==='solve'?`solve:${key}`:`review:${r.week}:${r.day}:${key}`;
    if(seen.has(event))continue;
    seen.add(event);
    const day=days[(when-start)/dayMs];
    if(!day)continue;
    day[r.kind==='solve'?'solves':'reviews']++;
    day.hints+=Number(r.usedHint);
    day.total++;
  }
  return {startDate,endDate:days.at(-1).date,days,total:days.reduce((s,d)=>s+d.total,0),
    activeDays:days.filter(d=>d.total>0).length,hints:days.reduce((s,d)=>s+d.hints,0)};
}

export function activitySvg(data) {
  const offset=new Date(dateMs(data.startDate)).getUTCDay();
  const level=n=>n===0?0:n===1?1:n<=3?2:n<=5?3:4;
  const x0=72,y0=78,step=32,size=26;
  let svg=`<svg xmlns="http://www.w3.org/2000/svg" width="560" height="340" viewBox="0 0 560 340" role="img" aria-labelledby="title description">
<title id="title">12주 풀이 잔디: 정답 ${data.total}회, 활동 ${data.activeDays}일</title>
<desc id="description">${data.startDate}부터 ${data.endDate}까지. 날짜가 기록된 정답만 집계. 신규 풀이와 재풀이를 포함하며 중복 기록은 제외합니다.</desc>
<style>
text{font-family:Segoe UI,Malgun Gothic,sans-serif;fill:#1f2328;font-size:12px}.muted{fill:#59636e}.heading{font-size:16px;font-weight:600}.bg{fill:#fff}.l0{fill:#eff2f5}.l1{fill:#9be9a8}.l2{fill:#40c463}.l3{fill:#30a14e}.l4{fill:#216e39}
@media(prefers-color-scheme:dark){text{fill:#e6edf3}.muted{fill:#9198a1}.bg{fill:#0d1117}.l0{fill:#161b22}.l1{fill:#0e4429}.l2{fill:#006d32}.l3{fill:#26a641}.l4{fill:#39d353}}
</style>
<rect class="bg" width="560" height="340" rx="10"/>
<text class="heading" x="24" y="28">정답 ${data.total}회 · 활동 ${data.activeDays}일</text>
<text class="muted" x="24" y="49">${data.startDate} — ${data.endDate} · 힌트 사용 ${data.hints}회</text>
`;
  const months=new Set();
  for(let i=0;i<data.days.length;i++) {
    const d=data.days[i],slot=i+offset,col=Math.floor(slot/7),row=slot%7;
    const month=d.date.slice(0,7);
    if(!months.has(month)) {
      months.add(month);
      svg+=`<text class="muted" x="${x0+col*step}" y="69">${Number(d.date.slice(5,7))}월</text>\n`;
    }
    svg+=`<rect class="l${level(d.total)}" data-date="${d.date}" data-count="${d.total}" x="${x0+col*step}" y="${y0+row*step}" width="${size}" height="${size}" rx="4"><title>${d.date}: 신규 ${d.solves}, 재풀이 ${d.reviews}, 힌트 사용 ${d.hints}</title></rect>\n`;
  }
  for(const [row,label] of [[1,'월'],[3,'수'],[5,'금']])svg+=`<text class="muted" x="44" y="${y0+row*step+18}">${label}</text>\n`;
  svg+='<text class="muted" x="72" y="322">날짜별 정답 풀이 수</text>\n';
  for(const [i,label] of ['0','1','2–3','4–5','6+'].entries()) {
    const x=268+i*44;
    svg+=`<rect class="l${i}" x="${x}" y="308" width="12" height="12" rx="2"/><text class="muted" x="${x+16}" y="319">${label}</text>\n`;
  }
  return svg+'</svg>\n';
}

export function buildActivity(root) {
  build(root);
  const schedule=JSON.parse(fs.readFileSync(path.join(root,'curriculum/schedule.json'),'utf8'));
  const records=JSON.parse(fs.readFileSync(path.join(root,'curriculum/records.json'),'utf8'));
  return activitySvg(activityData(records,schedule.startDate));
}

if(process.argv[1] && import.meta.url===pathToFileURL(path.resolve(process.argv[1])).href) {
  const output=path.resolve(process.argv[2] || 'assets/activity.svg');
  const svg=buildActivity(process.cwd());
  fs.mkdirSync(path.dirname(output),{recursive:true});
  fs.writeFileSync(output,svg);
  console.log('Activity image: '+output);
}
