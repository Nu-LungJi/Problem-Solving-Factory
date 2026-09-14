import path from 'node:path';

// Each adapter returns a stable platform:problemId, or null for unrelated files.
// Add platform conventions here without changing the progress calculator.
export const adapters = [
  file => {
    const match = /^solutions\/(cses|leetcode)\/([^/]+)\.(cpp|cc|cxx)$/i.exec(file);
    if (!match) return null;
    const platform = match[1].toLowerCase();
    const id = match[2].toLowerCase();
    if (!(platform === 'cses' ? /^\d+$/ : /^[a-z0-9]+(?:-[a-z0-9]+)*$/).test(id)) return null;
    return { key: `${platform}:${id}`, evidence: '정답 확인 후 저장한 로컬 풀이' };
  },
  (file, read) => {
    if (!file.split('/').includes('프로그래머스')) return null;
    const dir = path.posix.dirname(file);
    const id = /^(\d+)\./.exec(path.posix.basename(dir))?.[1];
    if (!id) return null;
    const text = read(path.posix.join(dir, 'README.md'));
    const ids = [...text.matchAll(/https:\/\/school\.programmers\.co\.kr\/learn\/courses\/30\/lessons\/(\d+)(?=[/?#\s)\]]|$)/g)];
    return ids.some(m => m[1] === id)
      ? { key: `programmers:${id}`, evidence: 'BaekjoonHub 형식의 업로드' } : null;
  },
];
