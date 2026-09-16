import test from 'node:test';
import assert from 'node:assert/strict';
import fs from 'node:fs';
import { syncMainReadme, syncPlanProgress } from '../scripts/sync-main.mjs';

const plan = fs.readFileSync(new URL('../curriculum/plan.md', import.meta.url), 'utf8');
const readme = fs.readFileSync(new URL('../README.md', import.meta.url), 'utf8');

function data({ completeWeek1 = false } = {}) {
  const days = [];
  for (let week = 1; week <= 12; week++) {
    for (let day = 1; day <= 7; day++) {
      days.push({ week, day, complete: week === 1 && (completeWeek1 || day <= 2) });
    }
  }
  const weeks = Array.from({ length: 12 }, (_, i) => ({ week: i + 1, complete: i === 0 && completeWeek1 }));
  return {
    accepted: 9,
    registered: 254,
    target: 208,
    days,
    weeks,
    overall: { done: 8, total: 283, percent: 2.83, completedDays: 2, totalDays: 84, completedWeeks: 0, totalWeeks: 12 },
  };
}

test('curriculum table mirrors automatic Day and Week completion without touching manual checklist', () => {
  const synced = syncPlanProgress(plan, data());
  const week1 = synced.slice(synced.indexOf('## Week 1 —'), synced.indexOf('## Week 2 —'));
  assert.match(week1, /^\| \[x\] \| 1 \| 입출력/m);
  assert.match(week1, /^\| \[x\] \| 2 \| vector/m);
  assert.match(week1, /^\| \[ \] \| 3 \| string/m);
  assert.match(synced, /^\| \[ \] \| 1 \| STL·배열·문자열·정렬/m);
  assert.match(week1, /^- \[ \] W01-D1:/m);
  assert.match(synced, /표의 `\[ \]` \/ `\[x\]`는 `solutions`와 `records\.json`에서 계산한 \*\*자동 진도 상태\*\*/);
});

test('weekly summary checks only when all Week completion criteria are met', () => {
  const synced = syncPlanProgress(plan, data({ completeWeek1: true }));
  assert.match(synced, /^\| \[x\] \| 1 \| STL·배열·문자열·정렬/m);
});

test('main README gets one deterministic automatic progress block', () => {
  const once = syncMainReadme(readme, data());
  const twice = syncMainReadme(once, data());
  assert.equal(once, twice);
  assert.equal((once.match(/<!-- PSF_PROGRESS_START -->/g) || []).length, 1);
  assert.match(once, /전체 목표 진도: 8\/283 \(2\.83%\)/);
  assert.match(once, /완료 Day 2\/84 · Week 0\/12/);
  assert.match(once, /등록 문제 해결: \*\*9\/254\*\*/);
});
