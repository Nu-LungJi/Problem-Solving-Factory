// Pool metadata is separate from the original required links and manual checklist.
export function attachPools(days, data, keyFromUrl) {
  if (data.schemaVersion !== 1 || !Array.isArray(data.days) || data.days.length !== days.length)
    throw new Error('후보 풀은 모든 Day를 포함해야 합니다.');
  const ids = new Set();
  const used = new Set(days.flatMap(d => d.problems.map(p => p.key)));
  for (const entry of data.days) {
    const day = days.find(d => d.id === entry.id);
    if (!day || ids.has(entry.id) || day.week !== entry.week || day.day !== entry.day)
      throw new Error('후보 풀 Day 매핑 오류');
    ids.add(entry.id);
    const { required, candidates } = entry;
    if (!Number.isInteger(required) || required < 0 || !Array.isArray(candidates) ||
        required !== day.target - day.problems.length || required > candidates.length ||
        (required === 0 && candidates.length !== 0)) throw new Error('후보 풀 목표 오류: ' + entry.id);
    for (const p of candidates) {
      if (!p || typeof p.title !== 'string' || !p.title.trim() ||
          p.key !== keyFromUrl(p.url) || p.key !== `${p.platform}:${p.problemId}` || used.has(p.key))
        throw new Error('후보 문제 중복 또는 메타데이터 오류: ' + p?.key);
      used.add(p.key);
    }
    day.additional = { required, candidates };
  }
  return days;
}
