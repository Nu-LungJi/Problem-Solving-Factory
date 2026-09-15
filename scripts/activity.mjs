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
  const start=dateMs(data.startDate);
  const offset=(new Date(start).getUTCDay()+6)%7;
  const rows=Math.ceil((offset+data.days.length)/7);
  const width=960,x0=136,y0=104,colStep=112,rowStep=36,cellWidth=104,cellHeight=28;
  const height=y0+rows*rowStep+42;
  const level=n=>n===0?0:n===1?1:n<=3?2:n<=5?3:4;
  const short=ms=>new Date(ms).toISOString().slice(5,10).replace('-','.');
  let svg=`<svg xmlns="http://www.w3.org/2000/svg" width="${width}" height="${height}" viewBox="0 0 ${width} ${height}" role="img" aria-labelledby="title description">
<title id="title">12주 풀이 잔디: 정답 ${data.total}회, 활동 ${data.activeDays}일</title>
<desc id="description">${data.startDate}부터 ${data.endDate}까지. 한 행은 월요일부터 일요일 순서입니다. 날짜가 기록된 정답만 집계하며 중복 기록은 제외합니다.</desc>
<style>
text{font-family:Segoe UI,Malgun Gothic,sans-serif;fill:#1f2328;font-size:14px}.muted{fill:#59636e}.heading{font-size:20px;font-weight:600}.bg{fill:#fff}.l0{fill:#eff2f5}.l1{fill:#9be9a8}.l2{fill:#40c463}.l3{fill:#30a14e}.l4{fill:#216e39}.on-fill{fill:#fff}.outside{fill:none;stroke:#d1d9e0;stroke-dasharray:3 3}
@media(prefers-color-scheme:dark){text{fill:#e6edf3}.muted{fill:#9198a1}.bg{fill:#0d1117}.l0{fill:#161b22}.l1{fill:#0e4429}.l2{fill:#006d32}.l3{fill:#26a641}.l4{fill:#39d353}.on-fill{fill:#0d1117}.low-fill{fill:#e6edf3}.outside{stroke:#30363d}}
</style>
<rect class="bg" width="${width}" height="${height}" rx="10"/>
<text class="heading" x="28" y="32">정답 ${data.total}회 · 활동 ${data.activeDays}일</text>
<text class="muted" x="28" y="56">${data.startDate} — ${data.endDate} · 힌트 사용 ${data.hints}회</text>
`;
  ['월','화','수','목','금','토','일'].forEach((label,col)=>{
    svg+=`<text class="weekday" x="${x0+col*colStep+cellWidth/2}" y="89" text-anchor="middle">${label}</text>\n`;
  });
  for(let row=0;row<rows;row++) {
    const monday=start+(row*7-offset)*dayMs;
    svg+=`<text class="muted" x="28" y="${y0+row*rowStep+19}">${short(monday)}–${short(monday+6*dayMs)}</text>\n`;
    for(let col=0;col<7;col++) {
      const d=data.days[row*7+col-offset];
      const x=x0+col*colStep,y=y0+row*rowStep;
      if(!d) {
        svg+=`<rect class="outside" x="${x}" y="${y}" width="${cellWidth}" height="${cellHeight}" rx="4"/>\n`;
        continue;
      }
      const shade=level(d.total);
      svg+=`<rect class="l${shade}" data-date="${d.date}" data-count="${d.total}" data-row="${row}" data-col="${col}" x="${x}" y="${y}" width="${cellWidth}" height="${cellHeight}" rx="4"><title>${d.date}: 신규 ${d.solves}, 재풀이 ${d.reviews}, 힌트 사용 ${d.hints}</title></rect>\n`;
      svg+=`<text class="${shade>=3?'on-fill':shade>0?'low-fill':'muted'}" x="${x+cellWidth/2}" y="${y+19}" text-anchor="middle">${Number(d.date.slice(5,7))}/${Number(d.date.slice(8))}${d.total?' · '+d.total+'회':''}</text>\n`;
    }
  }
  const legendY=height-18;
  svg+=`<text class="muted" x="28" y="${legendY}">날짜별 정답 풀이 수</text>\n`;
  for(const [i,label] of ['0','1','2–3','4–5','6+'].entries()) {
    const x=650+i*54;
    svg+=`<rect class="l${i}" x="${x}" y="${legendY-11}" width="12" height="12" rx="2"/><text class="muted" x="${x+17}" y="${legendY}">${label}</text>\n`;
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
