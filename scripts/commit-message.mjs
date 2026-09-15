const labels = { leetcode:'LeetCode', cses:'CSES', programmers:'Programmers' };

export function formatCommitMessage(session, decisions, englishTitles) {
  if (!Number.isInteger(session.week) || session.week<1 || session.week>12 ||
      !Number.isInteger(session.day) || session.day<1 || session.day>7) throw new Error('커밋 Week/Day 오류');
  const accepted = new Set(decisions.filter(d=>d.accepted===true).map(d=>d.key));
  const groups = new Map(Object.keys(labels).map(k=>[k,[]]));
  for (const key of accepted) {
    const entry=session.entries.find(e=>e.key===key);
    if(!entry) throw new Error('업로드 세션에 없는 문제: '+key);
    const [platform,id]=key.split(':');
    if(!groups.has(platform)) throw new Error('지원하지 않는 커밋 플랫폼: '+platform);
    let name;
    if(platform==='leetcode') name=id;
    else if(platform==='cses') name=(entry.title || id).replace(/^CSES\s*·\s*/i,'');
    else {
      name=englishTitles[key];
      if(typeof name!=='string' || !/^[\x20-\x7e]+$/.test(name) || !name.trim())
        throw new Error(`영문 제목이 없습니다: ${key}. curriculum/english-titles.json에 추가하세요.`);
    }
    // Keep each platform on one segment even if source metadata contains line breaks.
    groups.get(platform).push(name.replace(/[\r\n\\]+/g,' ').trim());
  }
  if(!accepted.size) throw new Error('커밋할 정답 풀이가 없습니다.');
  const parts=[`Solved Week ${session.week} Day ${session.day}`];
  for(const [platform,names] of groups) if(names.length) parts.push(`${labels[platform]}: ${names.join(', ')}`);
  return parts.join(' \\ ');
}
