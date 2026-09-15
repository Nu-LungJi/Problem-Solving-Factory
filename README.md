# Problem-Solving-Factory

C++ 코딩테스트 풀이와 12주 학습 기록을 관리합니다.

- [12주 커리큘럼 — Week·Day 목표와 완료 체크](curriculum/plan.md)
- [자동 진도표](https://github.com/Nu-LungJi/Problem-Solving-Factory/tree/progress)
- [추가 문제·CSES·LeetCode·재풀이 기록 방법](curriculum/README.md)
- [수동 학습 기록](curriculum/records.json)

프로그래머스 풀이 코드는 [BaekjoonHub](https://github.com/BaekjoonHub/BaekjoonHub)로 업로드합니다.
업로드 뒤 문제별 체크와 풀이 링크는 별도 progress 브랜치에서 갱신됩니다.
자동 진도표는 첫 Actions 실행이 성공한 뒤 열립니다.

학습량은 신규 208문제와 재풀이 75회입니다. 지정 문제 144개 외에 추가 선택 문제를 등록해 목표를 채웁니다.
v2는 프로그래머스 업로드와 `solutions/cses/<문제번호>.cpp`,
`solutions/leetcode/<slug>.cpp`를 감지해 문제 → Day → Week → 전체 진도를 계산합니다.
정답 확인을 마친 코드만 이 경로에 저장하세요. 재풀이는 별도 기록이 필요합니다.
오답 정리·개념 학습·힌트 사용은 직접 기록합니다.

진도표의 `progress.json`은 자동 계산 결과의 기준 파일입니다.
로컬에서는 `node --test tests/*.test.mjs`로 검사하고 `node scripts/progress.mjs`로
`generated/README.md`와 `generated/progress.json`을 생성할 수 있습니다.
