const percent = (done, total) => total ? Math.round(done / total * 10000) / 100 : 0;

export function calculate(days, solved, reviews, plan) {
  const owners = new Map();
  for (const d of days) for (const p of d.problems) {
    if (!owners.has(p.key)) owners.set(p.key, d.id);
  }
  const result = days.map(d => {
    const problems = d.problems.map(p => ({ ...p,
      platform: p.key.split(':')[0], problemId: p.key.split(':').slice(1).join(':'),
      solved: solved.has(p.key), countsAsNew: owners.get(p.key) === d.id,
    }));
    const requiredProblems = problems.filter(p => !p.extra);
    const candidates = (d.additional?.candidates || []).map(p => ({ ...p, solved: solved.has(p.key) }));
    const additional = { required: d.additional?.required ?? Math.max(0, d.target - requiredProblems.length),
      candidates, solved: candidates.filter(p => p.solved).length };
    additional.credited = Math.min(additional.solved, additional.required);
    additional.complete = additional.solved >= additional.required;
    const requiredSolved = requiredProblems.filter(p => p.solved && p.countsAsNew).length;
    const newSolved = requiredSolved + additional.credited;
    const attempts = reviews.filter(r => r.week === d.week && r.day === d.day);
    // A copied record with another id cannot manufacture another review of the same problem that day.
    const reviewSolved = new Set(attempts.filter(r => r.result === 'accepted').map(r => r.key)).size;
    const total = d.target + d.reviewTarget;
    const done = Math.min(newSolved, d.target) + Math.min(reviewSolved, d.reviewTarget);
    const manualComplete = new RegExp(`^- \\[x\\] W${d.week}-D${d.day}:`, 'm').test(plan);
    // A day without objective tasks requires its existing manual checklist.
    const complete = total ? newSolved >= d.target && reviewSolved >= d.reviewTarget && requiredProblems.every(p => p.solved) && additional.complete : manualComplete;
    return { ...d, problems, additional, requiredSolved, newSolved, reviewAttempts: attempts.length, reviewSolved,
      done, total, percent: total ? percent(done, total) : (complete ? 100 : 0),
      complete, manualComplete, completionBasis: total ? 'objective' : 'manual' };
  });
  const summarize = ds => {
    const done = ds.reduce((s,d) => s + d.done, 0);
    const total = ds.reduce((s,d) => s + d.total, 0);
    const completedDays = ds.filter(d => d.complete).length;
    return { done, total, percent: percent(done, total), completedDays, totalDays: ds.length,
      complete: ds.every(d => d.complete) };
  };
  const weeks = [...new Set(days.map(d => d.week))].map(week => ({ week,
    ...summarize(result.filter(d => d.week === week)) }));
  return { days: result, weeks, overall: { ...summarize(result),
    completedWeeks: weeks.filter(w => w.complete).length, totalWeeks: weeks.length } };
}
