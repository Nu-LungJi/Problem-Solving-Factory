import test from 'node:test';
import assert from 'node:assert/strict';
import { activityData, activitySvg } from '../scripts/activity.mjs';

const record=(id,options={})=>({id,date:'2026-09-15',week:1,day:1,
  url:'https://cses.fi/problemset/task/1068/',kind:'solve',result:'accepted',usedHint:false,...options});

test('activity calendar contains all 84 dates without inventing any solves',()=>{
  const data=activityData([],'2026-09-15');
  assert.equal(data.days.length,84);
  assert.equal(data.endDate,'2026-12-07');
  assert.equal(data.total,0);
  assert.equal(data.activeDays,0);
  const svg=activitySvg(data);
  assert.equal((svg.match(/data-date=/g)||[]).length,84);
  assert.equal((svg.match(/data-count="0"/g)||[]).length,84);
  assert.doesNotMatch(svg,/<script|foreignObject|https?:\/\/(?!www.w3.org)/);
});

test('activity counts accepted solves, reviews and hints, and deduplicates repeated records',()=>{
  const data=activityData([
    record('first'),record('duplicate',{date:'2026-09-16'}),
    record('failed',{url:'https://cses.fi/problemset/task/1083/',result:'attempted'}),
    record('second',{url:'https://cses.fi/problemset/task/1083/',usedHint:true}),
    record('review',{kind:'review',day:7,date:'2026-09-21',usedHint:true}),
    record('review-copy',{kind:'review',day:7,date:'2026-09-22'}),
    record('next-review',{kind:'review',week:2,day:7,date:'2026-09-28'}),
  ],'2026-09-15');
  assert.equal(data.total,4);
  assert.equal(data.activeDays,3);
  assert.equal(data.hints,2);
  assert.equal(data.days[0].solves,2);
  assert.equal(data.days[6].reviews,1);
  assert.equal(data.days[7].total,0);
  assert.equal(data.days[13].reviews,1);
});

test('activity uses recorded dates, excludes out-of-period events and rejects invalid dates',()=>{
  const data=activityData([record('before',{date:'2026-09-14'}),
    record('same-after',{date:'2026-09-15'}),
    record('late',{date:'2026-12-08',url:'https://cses.fi/problemset/task/1083/'}),
    record('last',{date:'2026-12-07',url:'https://cses.fi/problemset/task/1069/'})],'2026-09-15');
  assert.equal(data.total,1);
  assert.equal(data.days.at(-1).total,1);
  assert.throws(()=>activityData([record('bad',{date:'2026-02-30'})],'2026-09-15'),/날짜/);
});

test('SVG is deterministic and shows per-date level, counts and accessible description',()=>{
  const records=Array.from({length:5},(_,i)=>record('id-'+i,{url:`https://cses.fi/problemset/task/${1068+i}/`,usedHint:i<2}));
  const data=activityData(records,'2026-09-15');
  const svg=activitySvg(data);
  assert.equal(svg,activitySvg(activityData(records,'2026-09-15')));
  assert.match(svg,/class="l3" data-date="2026-09-15" data-count="5"/);
  assert.match(svg,/정답 5회 · 활동 1일/);
  assert.match(svg,/힌트 사용 2회/);
  assert.match(svg,/prefers-color-scheme:dark/);
});
