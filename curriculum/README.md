# 진도 기록 사용법

## 자동 업로드

BaekjoonHub를 이 저장소에 연결한 뒤 프로그래머스 C++ 정답 풀이가 업로드되면 자동 진도 갱신이 실행됩니다. 플랫폼별 폴더와 언어별 폴더 양쪽을 지원합니다. 기존 풀이 폴더 이름을 바꿀 필요가 없습니다.

지원 조건은 경로에 `프로그래머스` 폴더가 있고, 문제 폴더가 `문제번호.제목`이며, 그 안에 비어 있지 않은 C++ 파일과 같은 문제 URL을 담은 README가 있는 것입니다. 이 형식을 정답 업로드의 근거로 사용하며, 저지에 접속해 정답 여부를 재검증하지 않습니다. 임의로 만든 파일까지 독립 정답으로 인증하는 기능은 아닙니다.

진도표는 별도 `progress` 브랜치의 README에 생성됩니다. 업로드 도구가 쓰는 `main`에는 자동 진도 커밋을 만들지 않습니다. 원본 [12주 계획](plan.md)의 Day·Week 체크는 직접 유지합니다.

## CSES·LeetCode·추가 문제·재풀이

CSES와 LeetCode는 현재 자동 수집하지 않습니다. 정답 확인 후 코드를 저장하고 `records.json`에 기록을 추가하면 집계됩니다. 다음은 형식 예시이며 실제로 해결한 뒤 추가하세요.

```json
[
  {
    "id": "2026-09-15-cses-1068-first",
    "date": "2026-09-15",
    "week": 1,
    "day": 1,
    "url": "https://cses.fi/problemset/task/1068/",
    "code": "solutions/cses/1068.cpp",
    "kind": "solve",
    "result": "accepted",
    "usedHint": false
  }
]
```

- `code`: 저장소 안에 실제로 저장한 비어 있지 않은 C++ 파일의 상대 경로. 구분자는 `/`입니다.
- `kind`: 처음 풀이는 `solve`, 재풀이는 `review`.
- `result`: 정답 확인은 `accepted`, 아직 해결 못한 시도는 `attempted`.
- `usedHint`: 힌트·해설을 사용했으면 `true`. 업로드만으로는 이 값을 알 수 없습니다.
- `id`: 각 실제 학습 시도마다 고유하게 작성합니다. 같은 코드를 다시 풀었어도 새로운 기록을 남깁니다.
- `week/day`: 실제 기록할 학습일. 지정 목록에 없는 신규 문제는 이 날짜의 추가 문제로 등록됩니다.
- 기존에 해결한 문제를 재풀이 실패해도 이전 해결 상태는 지우지 않습니다. 재풀이 시도와 정답·힌트 미사용 횟수를 별도로 표시합니다.
- 추가 문제는 두 날짜의 신규 문제로 중복 배정할 수 없습니다. 다음 학습은 `review`로 기록하세요.
- 계획의 지정 문제를 교체하려면 `plan.md`의 해당 문제 링크를 바꿉니다. 수동 기록만 추가하면 원래 문제는 그대로 남습니다.

208은 학습 목표, 등록 문제 수는 지정 문제 144개와 추가로 선택한 문제 수입니다. 선택하지 않은 문제를 해결률 분모에 몰래 포함하지 않습니다. 자동 업로드된 미배정 문제는 지정/추가 문제 집계에 포함되지 않으므로 위 형식으로 날짜에 등록하세요.

## 첫 실행과 점검

1. 이 구성을 main에 반영합니다.
2. GitHub의 Actions에서 **Update curriculum progress** 실행 결과를 확인합니다.
3. 저장소 메인 README의 **자동 진도표**를 엽니다. 첫 실행 전에는 progress 브랜치가 없습니다.
4. 프로그래머스에서 C++ 문제를 정답 제출하고 코드와 문제 README가 올라오는지 확인합니다.
5. 다음 Actions 실행 후 해당 문제의 체크와 풀이 링크가 생기는지 확인합니다.

별도 개인 토큰을 코드에 넣을 필요는 없습니다. 워크플로는 GitHub가 제공하는 저장소 토큰으로 progress 브랜치만 갱신합니다. 조직 정책·브랜치 보호로 쓰기가 거부되면 Actions 실행 로그에서 권한 설정을 확인하세요.

로컬 확인(Node.js 22 이상):

```text
node --test tests/progress.test.mjs
node scripts/progress.mjs
```

로컬 결과는 `generated/README.md`입니다. 이 폴더는 Git 커밋에서 제외됩니다.

## 참고

- [BaekjoonHub](https://github.com/BaekjoonHub/BaekjoonHub)
- [GitHub Actions 실행 조건](https://docs.github.com/en/actions/how-tos/write-workflows/choose-when-workflows-run/trigger-a-workflow)
