# 12주 C++ 코딩테스트 집중 커리큘럼

> 시작일: ____-__-__ · 종료 예정일: ____-__-__  
> 기준: 이전 「코테 준비 계획 세우기」의 12주 집중 계획 · 작성일: 2026-09-14

## 내 출발점과 목표

C++ 기본 문법을 공부했고, OOP·상속·SOLID와 스택 등 자료구조 직접 구현을 병행하는 단계에 맞춘 계획이다. 문법 입문을 다시 길게 반복하지 않고, 첫 2주에 STL 활용을 정리한 뒤 알고리즘과 문제 해결로 넘어간다. OOP·자료구조 구현 공부는 별도 개발 학습 시간에 이어간다.

하루 3~5시간, 주 6일 학습과 Day 7 복습을 기준으로 한다. 목표는 낯선 프로그래머스 Lv.2와 LeetCode Medium의 주요 유형을 스스로 분석하고, 일부 Lv.3 문제에 도전하며, 2~3시간 시험에서 문제 선택과 시간 배분을 수행하는 것이다. 목표 난도는 학습 방향이며 달성을 보장하는 수치가 아니다.

이전 계획의 주제 순서를 유지하면서 문제 수를 **신규 208문제 + 재풀이 75회 = 총 283회**로 구체화했다. 새 문제에는 아래 지정 문제와 추가 선택 문제가 모두 포함된다. 해설을 보고 해결한 문제는 신규 시도로 기록하되 독립 해결로 세지 않는다.

## 체크와 문제 선택 방법

- 표의 `[ ]` / `[x]`는 `solutions`와 `records.json`에서 계산한 **자동 진도 상태**다. GitHub Actions가 Day·Week 완료 여부를 갱신한다. 표 안에서는 GitHub 등 일부 뷰어가 체크박스로 렌더링하지 않는다.
- 각 주 아래 별도 `- [ ]` 목록은 **수동 학습 체크리스트**다. 개념 설명·오답 정리·주간 설명처럼 파일만으로 판정할 수 없는 항목은 사용자가 직접 관리하며, 자동화가 덮어쓰지 않는다.
- 하루 완료: 개념 설명 → 목표 수만큼 풀이 시도 → 틀린 이유 기록까지 마친 상태. 모든 문제 정답과는 구별한다.
- 주간 완료: Day 1~7 완료 및 주간 목표를 코드나 말로 설명한 상태. 어렵다면 날짜를 늘리고 미해결은 기록한다.
- **지정 링크를 먼저 풀고**, 각 Day의 [추가 후보 풀](pools.md)에서 지정된 개수를 해결한다. 신규 목표는 필수 144개 + 후보 선택 64개 = 208개다. 이미 해결한 파일은 등록된 문제의 해결 상태로 반영되며, 재풀이는 별도 기록한다.
- 추가 후보는 `pools.json`에 Day별로 고정되어 있다. 필요한 개수만 해결하면 되며 후보 밖의 풀이로 자동 대체하지 않는다. 후보 변경은 데이터 수정 후 `node scripts/render-pools.mjs`로 문서를 갱신하고 테스트한다.
- Week 10~12는 지정 문제만으로 신규 목표를 채운다. 특히 Week 11~12는 문제만 열고 태그·해설·이 문서의 앞 주차 분류를 보지 않는다.
- Week 1~11 Day 7은 **재풀이 6회**: 이번 주 오답 3개 + 7일 이상 지난 오답 3개. Week 1은 이번 주 문제 6개로 대체한다. 오답이 부족하면 가장 오래 걸린 문제를 고른다.
- Week 12 Day 2·4·6은 각각 **재풀이 3회**. 직전 시험 미해결이 3개 미만이면 이전 오답을 더한다.
- 시간이 부족하면 추가 선택 문제부터 줄이고 실제 수를 기록한다. 다음날 10분 회상은 별도 문제 풀이 횟수로 세지 않는다.

## 학습 자료

| 자료 | 직접 링크 | 사용 방법 |
|---|---|---|
| 바킹독 실전 알고리즘 | [공식 저장소](https://github.com/encrypted-def/basic-algo-lecture) · [단원별 문제집](https://github.com/encrypted-def/basic-algo-lecture/blob/master/workbook.md) | 개념과 C++ 구현의 주교재. 실제 저장소 소유자는 encrypted-def이다. |
| tony9402 백준 문제집 | [저장소·유형별 목록](https://github.com/tony9402/baekjoon) | 같은 유형의 추천 문제와 풀이 비교에 사용한다. |
| CSES | [문제 목록](https://cses.fi/problemset/) | 표준입출력 방식 C++ 연습. 아래 개별 링크로 바로 이동한다. |
| 프로그래머스 | [고득점 Kit](https://school.programmers.co.kr/learn/challenges?tab=algorithm_practice_kit) | 국내 코테 문제 및 solution 함수 제출 연습. |
| LeetCode | [LeetCode 75](https://leetcode.com/studyplan/leetcode-75/) | 부족한 유형을 보완한다. 전체 목록 완주는 별도 목표로 추가하지 않는다. |
| NeetCode | [연습 목록](https://neetcode.io/practice) | NeetCode 150의 해당 유형에서 추가 문제를 선택한다. |
| CP-Algorithms | [알고리즘 설명](https://cp-algorithms.com/) | 원리·복잡도·증명이 막힐 때 필요한 항목만 읽는다. |
| TheAlgorithms | [C++ 구현 저장소](https://github.com/TheAlgorithms/C-Plus-Plus) | 직접 구현한 뒤 자료구조·알고리즘 코드를 비교한다. |

백준 이용이 어렵다는 기존 대화의 조건을 반영해, 필수 제출은 CSES·프로그래머스·LeetCode로 구성했다. 백준 관련 GitHub는 개념·선별 목록·코드 참고용이며 그 안의 백준 링크 접속은 이 계획의 선행 조건이 아니다. [tony9402 README](https://github.com/tony9402/baekjoon)에도 서비스 종료 및 저장소 유지 안내가 있다. 대표 자료 페이지와 일부 문제 페이지를 확인했으며, 모든 개별 문제의 로그인·제출 가능 여부까지 검증한 것은 아니다.

## 하루 시간표

| 순서 | 시간 | 목표 |
|---|---:|---|
| 개념·전날 회상 | 40분 | 핵심 아이디어와 복잡도 설명, 전날 실수 확인 |
| 지정 문제 | 100분 | 풀이 구상·구현·반례 확인 |
| 휴식 | 20분 | 화면에서 벗어나기 |
| 추가 문제·재풀이 | 50분 | 목표 수를 채우거나 어려운 지정 문제 계속 풀기 |
| 오답 정리 | 30분 | 실패 원인·다음 복습일·개선한 코드 기록 |

총 4시간 예시다. Week 7~10의 어려운 문제는 한 문제에 60~90분을 써도 된다. 30분간 접근이 전혀 없으면 학습일에만 최소 힌트를 확인하고, 해설을 닫은 뒤 직접 구현한다. 시험일에는 검색·AI·해설 없이 제한시간을 지킨다.

## 주간 목표 한눈에 보기

| 완료 | Week | 핵심 주제 | 주간 목표 | 신규 | 재풀이 |
|---|---|---|---|---:|---:|
| [ ] | 1 | STL·배열·문자열·정렬 | 기본 STL을 검색 없이 사용하고 입력 크기에서 복잡도를 추정한다. | 24 | 6 |
| [ ] | 2 | 스택·큐·덱·해시·힙 | 요구 연산에 맞는 컨테이너를 고르고 연산 비용을 설명한다. | 24 | 6 |
| [ ] | 3 | 완전탐색·재귀·백트래킹 | 탐색 공간 크기를 계산하고 선택·재귀·복구를 구현한다. | 18 | 6 |
| [ ] | 4 | 누적합·투포인터·슬라이딩 윈도우 | 구간 문제를 선형 시간으로 바꾸고 음수 포함 시 조건을 구별한다. | 18 | 6 |
| [ ] | 5 | 이분탐색·그리디 | 단조 판정식을 만들고 그리디 선택의 정당성을 설명한다. | 18 | 6 |
| [ ] | 6 | DFS·BFS·격자 탐색 | 연결 요소와 무가중치 최단거리를 구현하고 방문 시점을 설명한다. | 24 | 6 |
| [ ] | 7 | 트리·DSU·최소 신장 트리 | 트리 순회·집합 병합·Kruskal을 구현하고 용도를 구별한다. | 14 | 6 |
| [ ] | 8 | 최단경로·위상정렬 | 가중치·정점 수·선행 관계를 보고 알고리즘을 선택한다. | 14 | 6 |
| [ ] | 9 | DP 집중 | 상태·점화식·초기값·계산 순서·정답 위치를 먼저 적는다. | 18 | 6 |
| [ ] | 10 | 혼합 패턴·선택 심화 | 핵심 알고리즘을 조합하고 심화 주제의 우선순위를 조절한다. | 12 | 6 |
| [ ] | 11 | 유형을 숨긴 혼합 문제 | 제약에서 후보 알고리즘을 추론하고 풀이 선택 이유를 기록한다. | 12 | 6 |
| [ ] | 12 | 실전 모의고사·약점 보완 | 3회 모의고사를 치르고 실패 원인별 다음 학습 계획을 만든다. | 12 | 9 |
|  | **합계** |  |  | **208** | **75** |

## Week 1 — STL·배열·문자열·정렬

**주간 목표:** 기본 STL을 검색 없이 사용하고 입력 크기에서 복잡도를 추정한다.

**학습 링크:** [바킹독 강의·문제집](https://github.com/encrypted-def/basic-algo-lecture/blob/master/workbook.md) — 0x01, 0x02, 0x03, 0x0E, 0x0F. [tony9402 유형별 보충](https://github.com/tony9402/baekjoon).

| 완료 | Day | Daily 목표 | 지정 문제·실행 내용 | 신규 | 재풀이 |
|---|---|---|---|---:|---:|
| [x] | 1 | 입출력·long long·시간복잡도 정리 | [CSES · Weird Algorithm](https://cses.fi/problemset/task/1068/) · [CSES · Missing Number](https://cses.fi/problemset/task/1083/) · [후보 3개 중 2개 해결](pools.md#week-1-day-1) | 4 | 0 |
| [x] | 2 | vector·배열 순회·최댓값·최솟값 구현 | [CSES · Repetitions](https://cses.fi/problemset/task/1069/) · [CSES · Increasing Array](https://cses.fi/problemset/task/1094/) · [후보 3개 중 2개 해결](pools.md#week-1-day-2) | 4 | 0 |
| [ ] | 3 | string·빈도 배열·문자열 파싱 연습 | [프로그래머스 · 문자열을 정수로 바꾸기](https://school.programmers.co.kr/learn/courses/30/lessons/12925) · [프로그래머스 · 이상한 문자 만들기](https://school.programmers.co.kr/learn/courses/30/lessons/12930) · [후보 3개 중 2개 해결](pools.md#week-1-day-3) | 4 | 0 |
| [ ] | 4 | sort·pair·비교 함수로 정렬 조건 표현 | [프로그래머스 · K번째수](https://school.programmers.co.kr/learn/courses/30/lessons/42748) · [LeetCode · Valid Anagram](https://leetcode.com/problems/valid-anagram/) · [후보 3개 중 2개 해결](pools.md#week-1-day-4) | 4 | 0 |
| [ ] | 5 | 중복 제거·unique·이진 탐색 STL 맛보기 | [CSES · Distinct Numbers](https://cses.fi/problemset/task/1621/) · [프로그래머스 · 제일 작은 수 제거하기](https://school.programmers.co.kr/learn/courses/30/lessons/12935) · [후보 3개 중 2개 해결](pools.md#week-1-day-5) | 4 | 0 |
| [ ] | 6 | 표준입출력과 solution 함수 제출 방식 모두 연습 | [프로그래머스 · 문자열 내림차순으로 배치하기](https://school.programmers.co.kr/learn/courses/30/lessons/12917) · [프로그래머스 · 2016년](https://school.programmers.co.kr/learn/courses/30/lessons/12901) · [후보 3개 중 2개 해결](pools.md#week-1-day-6) | 4 | 0 |
| [ ] | 7 | 오답 6개 재풀이·주간 목표 설명·다음 주 준비 | 이번 주 3개 + 이전 오답 3개를 코드 없이 다시 풀기. Week 1은 이번 주 6개 | 0 | 6 |

**완료 체크리스트**

- [ ] Week 1 주간 목표 달성
- [ ] W01-D1: 입출력·long long·시간복잡도 정리
- [ ] W01-D2: vector·배열 순회·최댓값·최솟값 구현
- [ ] W01-D3: string·빈도 배열·문자열 파싱 연습
- [ ] W01-D4: sort·pair·비교 함수로 정렬 조건 표현
- [ ] W01-D5: 중복 제거·unique·이진 탐색 STL 맛보기
- [ ] W01-D6: 표준입출력과 solution 함수 제출 방식 모두 연습
- [ ] W01-D7: 재풀이 6회와 주간 점검

## Week 2 — 스택·큐·덱·해시·힙

**주간 목표:** 요구 연산에 맞는 컨테이너를 고르고 연산 비용을 설명한다.

**학습 링크:** [바킹독 강의·문제집](https://github.com/encrypted-def/basic-algo-lecture/blob/master/workbook.md) — 0x05, 0x06, 0x07, 0x08, 0x15, 0x16, 0x17. [tony9402 유형별 보충](https://github.com/tony9402/baekjoon).

| 완료 | Day | Daily 목표 | 지정 문제·실행 내용 | 신규 | 재풀이 |
|---|---|---|---|---:|---:|
| [ ] | 1 | 직접 만든 스택과 std::stack 비교·괄호 검사 | [LeetCode · Valid Parentheses](https://leetcode.com/problems/valid-parentheses/) · [프로그래머스 · 올바른 괄호](https://school.programmers.co.kr/learn/courses/30/lessons/12909) · [후보 3개 중 2개 해결](pools.md#week-2-day-1) | 4 | 0 |
| [ ] | 2 | queue로 처리 순서·대기열 모델링 | [프로그래머스 · 기능개발](https://school.programmers.co.kr/learn/courses/30/lessons/42586) · [프로그래머스 · 프로세스](https://school.programmers.co.kr/learn/courses/30/lessons/42587) · [후보 3개 중 2개 해결](pools.md#week-2-day-2) | 4 | 0 |
| [ ] | 3 | deque 양끝 연산·큐를 이용한 순환 처리 | [프로그래머스 · 같은 숫자는 싫어](https://school.programmers.co.kr/learn/courses/30/lessons/12906) · [CSES · Josephus Problem I](https://cses.fi/problemset/task/2162/) · [후보 3개 중 2개 해결](pools.md#week-2-day-3) | 4 | 0 |
| [ ] | 4 | unordered_map 빈도·존재 검사 | [프로그래머스 · 완주하지 못한 선수](https://school.programmers.co.kr/learn/courses/30/lessons/42576) · [프로그래머스 · 전화번호 목록](https://school.programmers.co.kr/learn/courses/30/lessons/42577) · [후보 3개 중 2개 해결](pools.md#week-2-day-4) | 4 | 0 |
| [ ] | 5 | 최소 힙·최대 힙 구현 및 반복 추출 | [프로그래머스 · 더 맵게](https://school.programmers.co.kr/learn/courses/30/lessons/42626) · [LeetCode · Last Stone Weight](https://leetcode.com/problems/last-stone-weight/) · [후보 3개 중 2개 해결](pools.md#week-2-day-5) | 4 | 0 |
| [ ] | 6 | set·map·multiset 차이와 lower_bound | [CSES · Concert Tickets](https://cses.fi/problemset/task/1091/) · [프로그래머스 · 의상](https://school.programmers.co.kr/learn/courses/30/lessons/42578) · [후보 3개 중 2개 해결](pools.md#week-2-day-6) | 4 | 0 |
| [ ] | 7 | 오답 6개 재풀이·주간 목표 설명·다음 주 준비 | 이번 주 3개 + 이전 오답 3개를 코드 없이 다시 풀기. Week 1은 이번 주 6개 | 0 | 6 |

**완료 체크리스트**

- [ ] Week 2 주간 목표 달성
- [ ] W02-D1: 직접 만든 스택과 std::stack 비교·괄호 검사
- [ ] W02-D2: queue로 처리 순서·대기열 모델링
- [ ] W02-D3: deque 양끝 연산·큐를 이용한 순환 처리
- [ ] W02-D4: unordered_map 빈도·존재 검사
- [ ] W02-D5: 최소 힙·최대 힙 구현 및 반복 추출
- [ ] W02-D6: set·map·multiset 차이와 lower_bound
- [ ] W02-D7: 재풀이 6회와 주간 점검

## Week 3 — 완전탐색·재귀·백트래킹

**주간 목표:** 탐색 공간 크기를 계산하고 선택·재귀·복구를 구현한다.

**학습 링크:** [바킹독 강의·문제집](https://github.com/encrypted-def/basic-algo-lecture/blob/master/workbook.md) — 0x0B, 0x0C, Appendix C. [tony9402 유형별 보충](https://github.com/tony9402/baekjoon).

| 완료 | Day | Daily 목표 | 지정 문제·실행 내용 | 신규 | 재풀이 |
|---|---|---|---|---:|---:|
| [ ] | 1 | 중첩 반복문 완전탐색·가능한 연산 수 추정 | [프로그래머스 · 모의고사](https://school.programmers.co.kr/learn/courses/30/lessons/42840) · [프로그래머스 · 카펫](https://school.programmers.co.kr/learn/courses/30/lessons/42842) · [후보 2개 중 1개 해결](pools.md#week-3-day-1) | 3 | 0 |
| [ ] | 2 | 재귀 종료 조건·호출 흐름 그리기 | [CSES · Tower of Hanoi](https://cses.fi/problemset/task/2165/) · [LeetCode · Subsets](https://leetcode.com/problems/subsets/) · [후보 2개 중 1개 해결](pools.md#week-3-day-2) | 3 | 0 |
| [ ] | 3 | next_permutation과 직접 순열 생성 비교 | [CSES · Creating Strings](https://cses.fi/problemset/task/1622/) · [LeetCode · Permutations](https://leetcode.com/problems/permutations/) · [후보 2개 중 1개 해결](pools.md#week-3-day-3) | 3 | 0 |
| [ ] | 4 | 조합 탐색·선택 취소·중복 방지 | [LeetCode · Combinations](https://leetcode.com/problems/combinations/) · [LeetCode · Combination Sum](https://leetcode.com/problems/combination-sum/) · [후보 2개 중 1개 해결](pools.md#week-3-day-4) | 3 | 0 |
| [ ] | 5 | 비트마스크로 부분집합 열거 | [CSES · Apple Division](https://cses.fi/problemset/task/1623/) · [프로그래머스 · 피로도](https://school.programmers.co.kr/learn/courses/30/lessons/87946) · [후보 2개 중 1개 해결](pools.md#week-3-day-5) | 3 | 0 |
| [ ] | 6 | 가지치기 조건 설명·백트래킹 종합 | [CSES · Chessboard and Queens](https://cses.fi/problemset/task/1624/) · [프로그래머스 · 소수 찾기](https://school.programmers.co.kr/learn/courses/30/lessons/42839) · [후보 2개 중 1개 해결](pools.md#week-3-day-6) | 3 | 0 |
| [ ] | 7 | 오답 6개 재풀이·주간 목표 설명·다음 주 준비 | 이번 주 3개 + 이전 오답 3개를 코드 없이 다시 풀기. Week 1은 이번 주 6개 | 0 | 6 |

**완료 체크리스트**

- [ ] Week 3 주간 목표 달성
- [ ] W03-D1: 중첩 반복문 완전탐색·가능한 연산 수 추정
- [ ] W03-D2: 재귀 종료 조건·호출 흐름 그리기
- [ ] W03-D3: next_permutation과 직접 순열 생성 비교
- [ ] W03-D4: 조합 탐색·선택 취소·중복 방지
- [ ] W03-D5: 비트마스크로 부분집합 열거
- [ ] W03-D6: 가지치기 조건 설명·백트래킹 종합
- [ ] W03-D7: 재풀이 6회와 주간 점검

## Week 4 — 누적합·투포인터·슬라이딩 윈도우

**주간 목표:** 구간 문제를 선형 시간으로 바꾸고 음수 포함 시 조건을 구별한다.

**학습 링크:** [바킹독 강의·문제집](https://github.com/encrypted-def/basic-algo-lecture/blob/master/workbook.md) — 0x14; 누적합은 별도 정리. [tony9402 유형별 보충](https://github.com/tony9402/baekjoon).

| 완료 | Day | Daily 목표 | 지정 문제·실행 내용 | 신규 | 재풀이 |
|---|---|---|---|---:|---:|
| [ ] | 1 | 1차원 누적합·반열린 구간·인덱스 검증 | [CSES · Static Range Sum Queries](https://cses.fi/problemset/task/1646/) · [LeetCode · Range Sum Query - Immutable](https://leetcode.com/problems/range-sum-query-immutable/) · [후보 2개 중 1개 해결](pools.md#week-4-day-1) | 3 | 0 |
| [ ] | 2 | 2차원 누적합·포함 배제 공식 도출 | [CSES · Forest Queries](https://cses.fi/problemset/task/1652/) · [LeetCode · Range Sum Query 2D - Immutable](https://leetcode.com/problems/range-sum-query-2d-immutable/) · [후보 2개 중 1개 해결](pools.md#week-4-day-2) | 3 | 0 |
| [ ] | 3 | 정렬 후 양끝 포인터 이동 근거 쓰기 | [CSES · Sum of Two Values](https://cses.fi/problemset/task/1640/) · [CSES · Apartments](https://cses.fi/problemset/task/1084/) · [후보 2개 중 1개 해결](pools.md#week-4-day-3) | 3 | 0 |
| [ ] | 4 | 고정 길이 윈도우 합 갱신 | [LeetCode · Maximum Average Subarray I](https://leetcode.com/problems/maximum-average-subarray-i/) · [프로그래머스 · 숫자의 표현](https://school.programmers.co.kr/learn/courses/30/lessons/12924) · [후보 2개 중 1개 해결](pools.md#week-4-day-4) | 3 | 0 |
| [ ] | 5 | 가변 길이 윈도우·양수 조건 확인 | [CSES · Subarray Sums I](https://cses.fi/problemset/task/1660/) · [LeetCode · Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/) · [후보 2개 중 1개 해결](pools.md#week-4-day-5) | 3 | 0 |
| [ ] | 6 | Kadane 상태 정의·누적합과 해시 결합 | [CSES · Maximum Subarray Sum](https://cses.fi/problemset/task/1643/) · [CSES · Subarray Sums II](https://cses.fi/problemset/task/1661/) · [후보 2개 중 1개 해결](pools.md#week-4-day-6) | 3 | 0 |
| [ ] | 7 | 오답 6개 재풀이·주간 목표 설명·다음 주 준비 | 이번 주 3개 + 이전 오답 3개를 코드 없이 다시 풀기. Week 1은 이번 주 6개 | 0 | 6 |

**완료 체크리스트**

- [ ] Week 4 주간 목표 달성
- [ ] W04-D1: 1차원 누적합·반열린 구간·인덱스 검증
- [ ] W04-D2: 2차원 누적합·포함 배제 공식 도출
- [ ] W04-D3: 정렬 후 양끝 포인터 이동 근거 쓰기
- [ ] W04-D4: 고정 길이 윈도우 합 갱신
- [ ] W04-D5: 가변 길이 윈도우·양수 조건 확인
- [ ] W04-D6: Kadane 상태 정의·누적합과 해시 결합
- [ ] W04-D7: 재풀이 6회와 주간 점검

## Week 5 — 이분탐색·그리디

**주간 목표:** 단조 판정식을 만들고 그리디 선택의 정당성을 설명한다.

**학습 링크:** [바킹독 강의·문제집](https://github.com/encrypted-def/basic-algo-lecture/blob/master/workbook.md) — 0x13, 0x11. [tony9402 유형별 보충](https://github.com/tony9402/baekjoon).

| 완료 | Day | Daily 목표 | 지정 문제·실행 내용 | 신규 | 재풀이 |
|---|---|---|---|---:|---:|
| [ ] | 1 | 이분탐색 경계·lower_bound와 upper_bound 비교 | [LeetCode · Binary Search](https://leetcode.com/problems/binary-search/) · [LeetCode · Search Insert Position](https://leetcode.com/problems/search-insert-position/) · [후보 2개 중 1개 해결](pools.md#week-5-day-1) | 3 | 0 |
| [ ] | 2 | 정답 이분탐색·가능 여부 함수 분리 | [CSES · Factory Machines](https://cses.fi/problemset/task/1620/) · [LeetCode · Koko Eating Bananas](https://leetcode.com/problems/koko-eating-bananas/) · [후보 2개 중 1개 해결](pools.md#week-5-day-2) | 3 | 0 |
| [ ] | 3 | 64비트 범위·최소 가능 답 찾기 | [프로그래머스 · 입국심사](https://school.programmers.co.kr/learn/courses/30/lessons/43238) · [CSES · Array Division](https://cses.fi/problemset/task/1085/) · [후보 2개 중 1개 해결](pools.md#week-5-day-3) | 3 | 0 |
| [ ] | 4 | 정렬·구간 선택·교환 논증 | [CSES · Movie Festival](https://cses.fi/problemset/task/1629/) · [LeetCode · Non-overlapping Intervals](https://leetcode.com/problems/non-overlapping-intervals/) · [후보 2개 중 1개 해결](pools.md#week-5-day-4) | 3 | 0 |
| [ ] | 5 | 작은 선택을 누적하는 근거 설명 | [CSES · Ferris Wheel](https://cses.fi/problemset/task/1090/) · [프로그래머스 · 구명보트](https://school.programmers.co.kr/learn/courses/30/lessons/42885) · [후보 2개 중 1개 해결](pools.md#week-5-day-5) | 3 | 0 |
| [ ] | 6 | 그리디 반례 찾기·다른 전략과 비교 | [CSES · Tasks and Deadlines](https://cses.fi/problemset/task/1630/) · [프로그래머스 · 체육복](https://school.programmers.co.kr/learn/courses/30/lessons/42862) · [후보 2개 중 1개 해결](pools.md#week-5-day-6) | 3 | 0 |
| [ ] | 7 | 오답 6개 재풀이·주간 목표 설명·다음 주 준비 | 이번 주 3개 + 이전 오답 3개를 코드 없이 다시 풀기. Week 1은 이번 주 6개 | 0 | 6 |

**완료 체크리스트**

- [ ] Week 5 주간 목표 달성
- [ ] W05-D1: 이분탐색 경계·lower_bound와 upper_bound 비교
- [ ] W05-D2: 정답 이분탐색·가능 여부 함수 분리
- [ ] W05-D3: 64비트 범위·최소 가능 답 찾기
- [ ] W05-D4: 정렬·구간 선택·교환 논증
- [ ] W05-D5: 작은 선택을 누적하는 근거 설명
- [ ] W05-D6: 그리디 반례 찾기·다른 전략과 비교
- [ ] W05-D7: 재풀이 6회와 주간 점검

## Week 6 — DFS·BFS·격자 탐색

**주간 목표:** 연결 요소와 무가중치 최단거리를 구현하고 방문 시점을 설명한다.

**학습 링크:** [바킹독 강의·문제집](https://github.com/encrypted-def/basic-algo-lecture/blob/master/workbook.md) — 0x09, 0x0A, 0x18. [tony9402 유형별 보충](https://github.com/tony9402/baekjoon).

| 완료 | Day | Daily 목표 | 지정 문제·실행 내용 | 신규 | 재풀이 |
|---|---|---|---|---:|---:|
| [ ] | 1 | 인접 리스트·DFS·반복형 스택 탐색 | [CSES · Building Roads](https://cses.fi/problemset/task/1666/) · [프로그래머스 · 네트워크](https://school.programmers.co.kr/learn/courses/30/lessons/43162) · [후보 3개 중 2개 해결](pools.md#week-6-day-1) | 4 | 0 |
| [ ] | 2 | 격자 좌표·경계 검사·Flood Fill | [CSES · Counting Rooms](https://cses.fi/problemset/task/1192/) · [LeetCode · Number of Islands](https://leetcode.com/problems/number-of-islands/) · [후보 3개 중 2개 해결](pools.md#week-6-day-2) | 4 | 0 |
| [ ] | 3 | BFS 거리 배열·큐에 넣을 때 방문 처리 | [CSES · Message Route](https://cses.fi/problemset/task/1667/) · [프로그래머스 · 게임 맵 최단거리](https://school.programmers.co.kr/learn/courses/30/lessons/1844) · [후보 3개 중 2개 해결](pools.md#week-6-day-3) | 4 | 0 |
| [ ] | 4 | 부모 기록·경로 복원 | [CSES · Labyrinth](https://cses.fi/problemset/task/1193/) · [LeetCode · Shortest Path in Binary Matrix](https://leetcode.com/problems/shortest-path-in-binary-matrix/) · [후보 3개 중 2개 해결](pools.md#week-6-day-4) | 4 | 0 |
| [ ] | 5 | 여러 시작점 BFS·상태를 정점으로 모델링 | [LeetCode · Rotting Oranges](https://leetcode.com/problems/rotting-oranges/) · [프로그래머스 · 단어 변환](https://school.programmers.co.kr/learn/courses/30/lessons/43163) · [후보 3개 중 2개 해결](pools.md#week-6-day-5) | 4 | 0 |
| [ ] | 6 | 이분 그래프·상태 탐색 응용 | [CSES · Building Teams](https://cses.fi/problemset/task/1668/) · [프로그래머스 · 타겟 넘버](https://school.programmers.co.kr/learn/courses/30/lessons/43165) · [후보 3개 중 2개 해결](pools.md#week-6-day-6) | 4 | 0 |
| [ ] | 7 | 오답 6개 재풀이·주간 목표 설명·다음 주 준비 | 이번 주 3개 + 이전 오답 3개를 코드 없이 다시 풀기. Week 1은 이번 주 6개 | 0 | 6 |

**완료 체크리스트**

- [ ] Week 6 주간 목표 달성
- [ ] W06-D1: 인접 리스트·DFS·반복형 스택 탐색
- [ ] W06-D2: 격자 좌표·경계 검사·Flood Fill
- [ ] W06-D3: BFS 거리 배열·큐에 넣을 때 방문 처리
- [ ] W06-D4: 부모 기록·경로 복원
- [ ] W06-D5: 여러 시작점 BFS·상태를 정점으로 모델링
- [ ] W06-D6: 이분 그래프·상태 탐색 응용
- [ ] W06-D7: 재풀이 6회와 주간 점검

## Week 7 — 트리·DSU·최소 신장 트리

**주간 목표:** 트리 순회·집합 병합·Kruskal을 구현하고 용도를 구별한다.

**학습 링크:** [바킹독 강의·문제집](https://github.com/encrypted-def/basic-algo-lecture/blob/master/workbook.md) — 0x19, 0x1B, Appendix D. [tony9402 유형별 보충](https://github.com/tony9402/baekjoon).

| 완료 | Day | Daily 목표 | 지정 문제·실행 내용 | 신규 | 재풀이 |
|---|---|---|---|---:|---:|
| [ ] | 1 | 루트·부모·깊이·트리 순회 | [LeetCode · Maximum Depth of Binary Tree](https://leetcode.com/problems/maximum-depth-of-binary-tree/) · [LeetCode · Invert Binary Tree](https://leetcode.com/problems/invert-binary-tree/) | 2 | 0 |
| [ ] | 2 | 서브트리 집계·후위 순회 | [CSES · Subordinates](https://cses.fi/problemset/task/1674/) · [LeetCode · Balanced Binary Tree](https://leetcode.com/problems/balanced-binary-tree/) | 2 | 0 |
| [ ] | 3 | 트리 지름·두 번 탐색의 원리 | [CSES · Tree Diameter](https://cses.fi/problemset/task/1131/) · [LeetCode · Diameter of Binary Tree](https://leetcode.com/problems/diameter-of-binary-tree/) | 2 | 0 |
| [ ] | 4 | DSU 경로 압축·크기 기준 병합 | [CSES · Road Construction](https://cses.fi/problemset/task/1676/) · [LeetCode · Redundant Connection](https://leetcode.com/problems/redundant-connection/) | 2 | 0 |
| [ ] | 5 | Kruskal·간선 정렬·연결 불가능 처리 | [CSES · Road Reparation](https://cses.fi/problemset/task/1675/) · [프로그래머스 · 섬 연결하기](https://school.programmers.co.kr/learn/courses/30/lessons/42861) · [후보 2개 중 1개 해결](pools.md#week-7-day-5) | 3 | 0 |
| [ ] | 6 | 트리와 일반 그래프의 사이클 차이 | [CSES · Round Trip](https://cses.fi/problemset/task/1669/) · [LeetCode · Validate Binary Search Tree](https://leetcode.com/problems/validate-binary-search-tree/) · [후보 2개 중 1개 해결](pools.md#week-7-day-6) | 3 | 0 |
| [ ] | 7 | 오답 6개 재풀이·주간 목표 설명·다음 주 준비 | 이번 주 3개 + 이전 오답 3개를 코드 없이 다시 풀기. Week 1은 이번 주 6개 | 0 | 6 |

**완료 체크리스트**

- [ ] Week 7 주간 목표 달성
- [ ] W07-D1: 루트·부모·깊이·트리 순회
- [ ] W07-D2: 서브트리 집계·후위 순회
- [ ] W07-D3: 트리 지름·두 번 탐색의 원리
- [ ] W07-D4: DSU 경로 압축·크기 기준 병합
- [ ] W07-D5: Kruskal·간선 정렬·연결 불가능 처리
- [ ] W07-D6: 트리와 일반 그래프의 사이클 차이
- [ ] W07-D7: 재풀이 6회와 주간 점검

## Week 8 — 최단경로·위상정렬

**주간 목표:** 가중치·정점 수·선행 관계를 보고 알고리즘을 선택한다.

**학습 링크:** [바킹독 강의·문제집](https://github.com/encrypted-def/basic-algo-lecture/blob/master/workbook.md) — 0x1A, 0x1C, 0x1D. [tony9402 유형별 보충](https://github.com/tony9402/baekjoon).

선택 기준: 동일한 간선 비용은 BFS, 비음수 가중치는 Dijkstra, 정점 수가 작고 모든 쌍 거리가 필요하면 O(V³) 비용을 검토해 Floyd-Warshall, 선행 관계는 위상정렬을 고려한다.

| 완료 | Day | Daily 목표 | 지정 문제·실행 내용 | 신규 | 재풀이 |
|---|---|---|---|---:|---:|
| [ ] | 1 | Dijkstra·최소 힙·오래된 거리 항목 건너뛰기 | [CSES · Shortest Routes I](https://cses.fi/problemset/task/1671/) · [LeetCode · Network Delay Time](https://leetcode.com/problems/network-delay-time/) | 2 | 0 |
| [ ] | 2 | 거리 long long·도달 불가능·완화 조건 검증 | [프로그래머스 · 배달](https://school.programmers.co.kr/learn/courses/30/lessons/12978) · [LeetCode · Path With Minimum Effort](https://leetcode.com/problems/path-with-minimum-effort/) | 2 | 0 |
| [ ] | 3 | Floyd-Warshall·경유 정점 반복문 순서 | [CSES · Shortest Routes II](https://cses.fi/problemset/task/1672/) · [프로그래머스 · 순위](https://school.programmers.co.kr/learn/courses/30/lessons/49191) | 2 | 0 |
| [ ] | 4 | 진입차수·Kahn 위상정렬·사이클 감지 | [CSES · Course Schedule](https://cses.fi/problemset/task/1679/) · [LeetCode · Course Schedule](https://leetcode.com/problems/course-schedule/) | 2 | 0 |
| [ ] | 5 | 위상정렬 결과와 선행 관계 검증 | [LeetCode · Course Schedule II](https://leetcode.com/problems/course-schedule-ii/) · [LeetCode · Find Eventual Safe States](https://leetcode.com/problems/find-eventual-safe-states/) · [후보 2개 중 1개 해결](pools.md#week-8-day-5) | 3 | 0 |
| [ ] | 6 | 격자 최단거리와 가중치 그래프 혼합 복습 | [프로그래머스 · 가장 먼 노드](https://school.programmers.co.kr/learn/courses/30/lessons/49189) · [CSES · Flight Discount](https://cses.fi/problemset/task/1195/) · [후보 2개 중 1개 해결](pools.md#week-8-day-6) | 3 | 0 |
| [ ] | 7 | 오답 6개 재풀이·주간 목표 설명·다음 주 준비 | 이번 주 3개 + 이전 오답 3개를 코드 없이 다시 풀기. Week 1은 이번 주 6개 | 0 | 6 |

**완료 체크리스트**

- [ ] Week 8 주간 목표 달성
- [ ] W08-D1: Dijkstra·최소 힙·오래된 거리 항목 건너뛰기
- [ ] W08-D2: 거리 long long·도달 불가능·완화 조건 검증
- [ ] W08-D3: Floyd-Warshall·경유 정점 반복문 순서
- [ ] W08-D4: 진입차수·Kahn 위상정렬·사이클 감지
- [ ] W08-D5: 위상정렬 결과와 선행 관계 검증
- [ ] W08-D6: 격자 최단거리와 가중치 그래프 혼합 복습
- [ ] W08-D7: 재풀이 6회와 주간 점검

## Week 9 — DP 집중

**주간 목표:** 상태·점화식·초기값·계산 순서·정답 위치를 먼저 적는다.

**학습 링크:** [바킹독 강의·문제집](https://github.com/encrypted-def/basic-algo-lecture/blob/master/workbook.md) — 0x10. [tony9402 유형별 보충](https://github.com/tony9402/baekjoon).

| 완료 | Day | Daily 목표 | 지정 문제·실행 내용 | 신규 | 재풀이 |
|---|---|---|---|---:|---:|
| [ ] | 1 | 1차원 DP·중복 부분문제 확인 | [CSES · Dice Combinations](https://cses.fi/problemset/task/1633/) · [LeetCode · Climbing Stairs](https://leetcode.com/problems/climbing-stairs/) · [후보 2개 중 1개 해결](pools.md#week-9-day-1) | 3 | 0 |
| [ ] | 2 | 최솟값 DP·불가능 상태·동전 반복 순서 | [CSES · Minimizing Coins](https://cses.fi/problemset/task/1634/) · [CSES · Coin Combinations I](https://cses.fi/problemset/task/1635/) · [후보 2개 중 1개 해결](pools.md#week-9-day-2) | 3 | 0 |
| [ ] | 3 | 2차원·경로 DP·장애물 초기화 | [CSES · Grid Paths I](https://cses.fi/problemset/task/1638/) · [프로그래머스 · 정수 삼각형](https://school.programmers.co.kr/learn/courses/30/lessons/43105) · [후보 2개 중 1개 해결](pools.md#week-9-day-3) | 3 | 0 |
| [ ] | 4 | 0/1 배낭·역순 갱신 이유 | [CSES · Book Shop](https://cses.fi/problemset/task/1158/) · [CSES · Money Sums](https://cses.fi/problemset/task/1745/) · [후보 2개 중 1개 해결](pools.md#week-9-day-4) | 3 | 0 |
| [ ] | 5 | LIS O(N²)·선택과 비선택 상태 | [LeetCode · Longest Increasing Subsequence](https://leetcode.com/problems/longest-increasing-subsequence/) · [LeetCode · House Robber](https://leetcode.com/problems/house-robber/) · [후보 2개 중 1개 해결](pools.md#week-9-day-5) | 3 | 0 |
| [ ] | 6 | 문자열 DP·두 인덱스 상태 | [CSES · Edit Distance](https://cses.fi/problemset/task/1639/) · [LeetCode · Longest Common Subsequence](https://leetcode.com/problems/longest-common-subsequence/) · [후보 2개 중 1개 해결](pools.md#week-9-day-6) | 3 | 0 |
| [ ] | 7 | 오답 6개 재풀이·주간 목표 설명·다음 주 준비 | 이번 주 3개 + 이전 오답 3개를 코드 없이 다시 풀기. Week 1은 이번 주 6개 | 0 | 6 |

**완료 체크리스트**

- [ ] Week 9 주간 목표 달성
- [ ] W09-D1: 1차원 DP·중복 부분문제 확인
- [ ] W09-D2: 최솟값 DP·불가능 상태·동전 반복 순서
- [ ] W09-D3: 2차원·경로 DP·장애물 초기화
- [ ] W09-D4: 0/1 배낭·역순 갱신 이유
- [ ] W09-D5: LIS O(N²)·선택과 비선택 상태
- [ ] W09-D6: 문자열 DP·두 인덱스 상태
- [ ] W09-D7: 재풀이 6회와 주간 점검

## Week 10 — 혼합 패턴·선택 심화

**주간 목표:** 핵심 알고리즘을 조합하고 심화 주제의 우선순위를 조절한다.

**학습 링크:** [바킹독 강의·문제집](https://github.com/encrypted-def/basic-algo-lecture/blob/master/workbook.md) — 0x1F; 앞 주차 복습. [tony9402 유형별 보충](https://github.com/tony9402/baekjoon).

선택 심화: Day 6 이후 여유가 있을 때만 [Segment Tree 개념](https://cp-algorithms.com/data_structures/segment_tree.html)을 읽고 구간합 갱신 예제를 구현한다. 신규 목표에 포함하지 않는다. Trie 학습일의 필수 문제는 유지하며 약점 보완은 목표 외 선택 학습으로 기록한다.

| 완료 | Day | Daily 목표 | 지정 문제·실행 내용 | 신규 | 재풀이 |
|---|---|---|---|---:|---:|
| [ ] | 1 | 누적합·해시 나머지 분류 | [CSES · Subarray Divisibility](https://cses.fi/problemset/task/1662/) · [LeetCode · Subarray Sum Equals K](https://leetcode.com/problems/subarray-sum-equals-k/) | 2 | 0 |
| [ ] | 2 | BFS·복수 상태·방문 배열 차원 결정 | [CSES · Monsters](https://cses.fi/problemset/task/1194/) · [LeetCode · Shortest Path with Alternating Colors](https://leetcode.com/problems/shortest-path-with-alternating-colors/) | 2 | 0 |
| [ ] | 3 | 힙·그리디·이벤트 처리 | [CSES · Room Allocation](https://cses.fi/problemset/task/1164/) · [프로그래머스 · 디스크 컨트롤러](https://school.programmers.co.kr/learn/courses/30/lessons/42627) | 2 | 0 |
| [ ] | 4 | DAG 위상 순서에 DP 적용 | [CSES · Longest Flight Route](https://cses.fi/problemset/task/1680/) · [CSES · Game Routes](https://cses.fi/problemset/task/1681/) | 2 | 0 |
| [ ] | 5 | LIS O(N log N)·좌표 압축 직접 예제 작성 | [CSES · Increasing Subsequence](https://cses.fi/problemset/task/1145/) · [LeetCode · Rank Transform of an Array](https://leetcode.com/problems/rank-transform-of-an-array/) | 2 | 0 |
| [ ] | 6 | Trie 삽입·검색·접두사 검사 | [LeetCode · Implement Trie (Prefix Tree)](https://leetcode.com/problems/implement-trie-prefix-tree/) · [LeetCode · Design Add and Search Words Data Structure](https://leetcode.com/problems/design-add-and-search-words-data-structure/) | 2 | 0 |
| [ ] | 7 | 오답 6개 재풀이·주간 목표 설명·다음 주 준비 | 이번 주 3개 + 이전 오답 3개를 코드 없이 다시 풀기. Week 1은 이번 주 6개 | 0 | 6 |

**완료 체크리스트**

- [ ] Week 10 주간 목표 달성
- [ ] W10-D1: 누적합·해시 나머지 분류
- [ ] W10-D2: BFS·복수 상태·방문 배열 차원 결정
- [ ] W10-D3: 힙·그리디·이벤트 처리
- [ ] W10-D4: DAG 위상 순서에 DP 적용
- [ ] W10-D5: LIS O(N log N)·좌표 압축 직접 예제 작성
- [ ] W10-D6: Trie 삽입·검색·접두사 검사
- [ ] W10-D7: 재풀이 6회와 주간 점검

## Week 11 — 유형을 숨긴 혼합 문제

**주간 목표:** 제약에서 후보 알고리즘을 추론하고 풀이 선택 이유를 기록한다.

**학습 링크:** [바킹독 강의·문제집](https://github.com/encrypted-def/basic-algo-lecture/blob/master/workbook.md) — 해설은 풀이 이후 열기. [tony9402 유형별 보충](https://github.com/tony9402/baekjoon).

| 완료 | Day | Daily 목표 | 지정 문제·실행 내용 | 신규 | 재풀이 |
|---|---|---|---|---:|---:|
| [ ] | 1 | 혼합 세트 A·각 문제 첫 5분 제약 분석 | [프로그래머스 · 신고 결과 받기](https://school.programmers.co.kr/learn/courses/30/lessons/92334) · [프로그래머스 · 크레인 인형뽑기 게임](https://school.programmers.co.kr/learn/courses/30/lessons/64061) | 2 | 0 |
| [ ] | 2 | 혼합 세트 B·후보 2개와 기각 이유 기록 | [프로그래머스 · 주차 요금 계산](https://school.programmers.co.kr/learn/courses/30/lessons/92341) · [프로그래머스 · 오픈채팅방](https://school.programmers.co.kr/learn/courses/30/lessons/42888) | 2 | 0 |
| [ ] | 3 | 혼합 세트 C·30분 뒤 필요할 때 최소 힌트 | [프로그래머스 · 메뉴 리뉴얼](https://school.programmers.co.kr/learn/courses/30/lessons/72411) · [프로그래머스 · 파일명 정렬](https://school.programmers.co.kr/learn/courses/30/lessons/17686) | 2 | 0 |
| [ ] | 4 | 혼합 세트 D·코딩 전 예외 사례 3개 | [프로그래머스 · n진수 게임](https://school.programmers.co.kr/learn/courses/30/lessons/17687) · [프로그래머스 · 압축](https://school.programmers.co.kr/learn/courses/30/lessons/17684) | 2 | 0 |
| [ ] | 5 | 혼합 세트 E·시간 제한 120분 | [프로그래머스 · 순위 검색](https://school.programmers.co.kr/learn/courses/30/lessons/72412) · [프로그래머스 · k진수에서 소수 개수 구하기](https://school.programmers.co.kr/learn/courses/30/lessons/92335) | 2 | 0 |
| [ ] | 6 | 혼합 세트 F·풀이 후 복잡도와 대안 비교 | [프로그래머스 · 문자열 압축](https://school.programmers.co.kr/learn/courses/30/lessons/60057) · [프로그래머스 · 땅따먹기](https://school.programmers.co.kr/learn/courses/30/lessons/12913) | 2 | 0 |
| [ ] | 7 | 오답 6개 재풀이·주간 목표 설명·다음 주 준비 | 이번 주 3개 + 이전 오답 3개를 코드 없이 다시 풀기. Week 1은 이번 주 6개 | 0 | 6 |

**완료 체크리스트**

- [ ] Week 11 주간 목표 달성
- [ ] W11-D1: 혼합 세트 A·각 문제 첫 5분 제약 분석
- [ ] W11-D2: 혼합 세트 B·후보 2개와 기각 이유 기록
- [ ] W11-D3: 혼합 세트 C·30분 뒤 필요할 때 최소 힌트
- [ ] W11-D4: 혼합 세트 D·코딩 전 예외 사례 3개
- [ ] W11-D5: 혼합 세트 E·시간 제한 120분
- [ ] W11-D6: 혼합 세트 F·풀이 후 복잡도와 대안 비교
- [ ] W11-D7: 재풀이 6회와 주간 점검

## Week 12 — 실전 모의고사·약점 보완

**주간 목표:** 3회 모의고사를 치르고 실패 원인별 다음 학습 계획을 만든다.

**학습 링크:** [바킹독 강의·문제집](https://github.com/encrypted-def/basic-algo-lecture/blob/master/workbook.md) — 모의고사 종료 후만 참고. [tony9402 유형별 보충](https://github.com/tony9402/baekjoon).

| 완료 | Day | Daily 목표 | 지정 문제·실행 내용 | 신규 | 재풀이 |
|---|---|---|---|---:|---:|
| [ ] | 1 | 모의고사 A·150분 4문제·쉬운 문제 먼저 | [프로그래머스 · 비밀지도](https://school.programmers.co.kr/learn/courses/30/lessons/17681) · [프로그래머스 · 키패드 누르기](https://school.programmers.co.kr/learn/courses/30/lessons/67256) · [프로그래머스 · 스킬트리](https://school.programmers.co.kr/learn/courses/30/lessons/49993) · [프로그래머스 · 괄호 변환](https://school.programmers.co.kr/learn/courses/30/lessons/60058) | 4 | 0 |
| [ ] | 2 | A 오답 분석·실패 문제 3개 재풀이·새 문제 없음 | 직전 모의고사 문제를 해설 없이 다시 구현하고 실패 원인 분류 | 0 | 3 |
| [ ] | 3 | 모의고사 B·180분 4문제·막히면 다음 문제 | [프로그래머스 · 3진법 뒤집기](https://school.programmers.co.kr/learn/courses/30/lessons/68935) · [프로그래머스 · 삼각 달팽이](https://school.programmers.co.kr/learn/courses/30/lessons/68645) · [프로그래머스 · 큰 수 만들기](https://school.programmers.co.kr/learn/courses/30/lessons/42883) · [프로그래머스 · 보석 쇼핑](https://school.programmers.co.kr/learn/courses/30/lessons/67258) | 4 | 0 |
| [ ] | 4 | B 오답 분석·실패 문제 3개 재풀이·새 문제 없음 | 직전 모의고사 문제를 해설 없이 다시 구현하고 실패 원인 분류 | 0 | 3 |
| [ ] | 5 | 모의고사 C·180분 4문제·마지막 15분 검증 | [프로그래머스 · 영어 끝말잇기](https://school.programmers.co.kr/learn/courses/30/lessons/12981) · [프로그래머스 · 주식가격](https://school.programmers.co.kr/learn/courses/30/lessons/42584) · [프로그래머스 · 기지국 설치](https://school.programmers.co.kr/learn/courses/30/lessons/12979) · [프로그래머스 · 경주로 건설](https://school.programmers.co.kr/learn/courses/30/lessons/67259) | 4 | 0 |
| [ ] | 6 | C 오답 분석·실패 문제 3개 재풀이·새 문제 없음 | 직전 모의고사 문제를 해설 없이 다시 구현하고 실패 원인 분류 | 0 | 3 |
| [ ] | 7 | 최종 성과 점검·다음 4주 계획 작성 | 3회 시험의 독립 정답 수·시간·실패 원인 비교. 약점 2개와 다음 주 문제 선정 | 0 | 0 |

**완료 체크리스트**

- [ ] Week 12 주간 목표 달성
- [ ] W12-D1: 모의고사 A·150분 4문제·쉬운 문제 먼저
- [ ] W12-D2: A 오답 분석·실패 문제 3개 재풀이·새 문제 없음
- [ ] W12-D3: 모의고사 B·180분 4문제·막히면 다음 문제
- [ ] W12-D4: B 오답 분석·실패 문제 3개 재풀이·새 문제 없음
- [ ] W12-D5: 모의고사 C·180분 4문제·마지막 15분 검증
- [ ] W12-D6: C 오답 분석·실패 문제 3개 재풀이·새 문제 없음
- [ ] W12-D7: 최종 점검과 다음 계획

## 풀이 기록표

결과: 독립 정답 / 힌트 후 정답 / 해설 후 정답 / 미해결. 복습 완료는 빈 파일에서 다시 구현하고 핵심 이유를 설명했을 때 표시한다.

| 날짜 | Week-Day | 문제 링크 | 신규/재풀이 | 결과 | 소요 시간 | 시간·공간 복잡도 | 실패 원인·핵심 아이디어 | 다음 복습일 |
|---|---|---|---|---|---:|---|---|---|
|  |  |  |  |  |  |  |  |  |
|  |  |  |  |  |  |  |  |  |
|  |  |  |  |  |  |  |  |  |

실패 원인은 개념 부족 / 발상 실패 / 구현 오류 / 복잡도 판단 / 예외 누락 / 시간 배분 중 하나로 시작하고 구체적으로 적는다. 예: “BFS 방문 처리를 꺼낼 때 해서 중복 삽입이 늘어남”.

- [ ] 오답 A: __________ · 다음날 회상
- [ ] 오답 A: __________ · 7일 후 재풀이
- [ ] 오답 B: __________ · 다음날 회상
- [ ] 오답 B: __________ · 7일 후 재풀이

## 실전 평가와 다음 단계

| 회차 | 제한시간 | 독립 정답/4 | 첫 정답까지 | 미해결 원인 | 다음 행동 |
|---|---:|---|---|---|---|
| Week 12 A | 150분 |  |  |  |  |
| Week 12 B | 180분 |  |  |  |  |
| Week 12 C | 180분 |  |  |  |  |

시험 시작 10분은 전체 문제 확인과 풀이 순서 결정에 쓴다. 한 문제에서 진전 없이 20~30분이 지나면 다른 문제로 이동한다. 마지막 15분에는 최소 입력·중복·오버플로·도달 불가능·인덱스 경계를 확인한다. 이미 풀어 본 시험 문제는 별도 재풀이로 기록하고, 유형 태그는 보지 않는다. 시험 필수 목록의 교체는 plan.md의 명시적 링크 수정으로 관리한다.

- [ ] STL 컨테이너 선택과 주요 연산 비용을 설명한다.
- [ ] DFS/BFS·이분탐색·DSU·Dijkstra를 참고 없이 구현한다.
- [ ] DP 상태·점화식·초기값·순서를 코드 전에 적는다.
- [ ] 신규 시도 수와 독립 해결 수를 구분해 집계한다.
- [ ] 가장 빈번한 실패 원인 2개와 해당 문제 링크를 정리한다.
- [ ] 다음 4주에는 약점 보완 주 3일·혼합 문제 주 2일·모의고사 주 1일·복습 주 1일을 실제 일정에 배치한다.

다음 4주 집중할 약점: __________ / __________  
실제 신규 문제 수: ______ · 실제 재풀이 횟수: ______  
독립 해결이 늘어난 유형: __________ · 더 시간이 필요한 유형: __________

