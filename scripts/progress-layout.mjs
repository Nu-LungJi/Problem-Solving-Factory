export function formatProgressMarkdown(input) {
const source=input.replace(/\r\n/g, "\n");
const firstWeek=source.indexOf('\n## Week ');
const intro=source.slice(0,firstWeek);
const tableStart=intro.indexOf('| Week |');
const tables=[...intro.slice(tableStart).matchAll(/\| Week \|[^\n]*\n\|[-|: ]+\n((?:\|[^\n]+\n)+)/g)];
if(tables.length!==2) throw Error('Expected two summary tables');
const rows=t=>t[1].trim().split('\n').map(line=>line.split('|').slice(1,-1).map(s=>s.trim()));
const a=rows(tables[0]),b=rows(tables[1]);
let md=intro.slice(0,tableStart);
md+='| Week | 목표 진도 | 완료 Day | 등록 문제 해결 | 신규 목표 | 재풀이 시도 / 목표 | 상태 |\n';
md+='|:---:|---:|:---:|---:|---:|---:|:---:|\n';
for(const r of a) {
  const other=b.find(s=>s[0]===r[0]);
  if(!other) throw Error('Missing week');
  md+=`| ${r[0]} | ${r[1]} | ${r[2]} | ${other[1]} | ${other[2]} | ${other[3]} | ${r[3]} |\n`;
}
md+='\n등록 문제 해결 수에는 초과로 푼 후보도 포함되며, 목표 진도에는 Day별 목표 개수까지만 반영됩니다.\n\n';
md+='**Day 제목을 누르면 문제 목록을 펼치거나 접을 수 있습니다.** ✅ 해결 · ⬜ 미해결\n';
let dayCount=0,problemCount=0;
const esc=s=>s.replace(/\|/g,'&#124;');
for(const weekMatch of source.slice(firstWeek).matchAll(/\n## Week (\d+)\n([\s\S]*?)(?=\n## Week |$)/g)) {
  const week=+weekMatch[1];
  md+=`\n## Week ${week}\n\n`;
  for(const d of weekMatch[2].matchAll(/### Day (\d+) — 신규 목표 (\d+) \/ 재풀이 목표 (\d+)\n([\s\S]*?)(?=### Day |$)/g)) {
    dayCount++;
    const [,day,newGoal,reviewGoal,body]=d;
    const status=/- \[([ x])\] Day \d+ (.+?) 완료 · 실제 (\d+\/\d+) · 목표 (\d+\/\d+ \([\d.]+%\))/.exec(body);
    if(!status) throw Error('No day status');
    const pool=/추가 후보 (\d+)개 중 (\d+)개 해결 필요 · 현재 (\d+)개 해결 · 목표 반영 (\d+\/\d+)/.exec(body);
    const isManual=status[2]==='수동 목표';
    md+=`<details${week===1 && +day<=2 ? ' open' : ''}>\n<summary><strong>Day ${day}</strong> · ${status[1]==='x'?'✅ 완료':'⬜ 미완료'} · ${status[3]}${isManual?' · 수동 학습':''}</summary>\n\n`;
    md+='| 신규 목표 | 재풀이 목표 | 추가 후보 조건 | 후보 해결 / 목표 반영 |\n|:---:|:---:|:---:|:---:|\n';
    md+=`| ${newGoal}문제 | ${reviewGoal}문제 | ${pool && +pool[2] ? `${pool[1]}개 중 ${pool[2]}개`:'없음'} | ${pool && +pool[2] ? `${pool[3]}개 해결 · ${pool[4]} 반영`:'—'} |\n\n`;
    const problems=[];
    let category='필수';
    const notes=[];
    for(const line of body.split('\n')) {
      if(line.startsWith('추가 후보')) {category='후보';continue;}
      if(!line.trim() || line.startsWith('- [') && line.includes('Day ')) continue;
      const p=/^- \[([ x])\] \[([^\]]+)\]\((https:\/\/[^)]+)\)(.*)$/.exec(line);
      if(!p) {notes.push(line);continue;}
      const [,checked,title,url,tail]=p;
      const host=new URL(url).hostname;
      const platform=host==='cses.fi'?'CSES':host==='leetcode.com'?'LeetCode':host==='school.programmers.co.kr'?'Programmers':host;
      const label=title.replace(/^(CSES|LeetCode|프로그래머스)\s*·\s*/,'');
      const info=tail.replace(/^\s*·\s*/,'').trim();
      problems.push(`| ${checked==='x'?'✅':'⬜'} | ${category} | ${platform} | [${esc(label)}](${url}) | ${esc(info)||'—'} |`);
      problemCount++;
    }
    if(problems.length) {
      md+='| 상태 | 구분 | 플랫폼 | 문제 | 풀이 / 기록 |\n|:---:|:---:|:---:|---|---|\n'+problems.join('\n')+'\n\n';
    }
    if(notes.length) md+=notes.join('\n')+'\n\n';
    md+='</details>\n\n';
  }
}
if(dayCount!==84 || a.length!==12) throw Error('Incomplete progress layout');
const links=s=>[...s.matchAll(/\]\((https:\/\/[^)]+)\)/g)].map(m=>m[1]).sort();
if(JSON.stringify(links(source))!==JSON.stringify(links(md))) throw Error('Progress links changed');
return md;
}
