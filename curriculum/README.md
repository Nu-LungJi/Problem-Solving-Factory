# 진도 기록 사용법

Windows의 **PSF_START.bat / PSF_UPLOAD.bat**을 사용하면 파일 준비·기록 작성·커밋을 자동화할 수 있습니다.
[설치 경로·사용 순서](windows-workflow.md). 일정은 [schedule.json](schedule.json)의 2026-09-15부터 하루에 한 Day입니다.

## 자동 업로드

BaekjoonHub를 이 저장소에 연결한 뒤 프로그래머스 C++ 정답 풀이가 업로드되면 자동 진도 갱신이 실행됩니다. 플랫폼별 폴더와 언어별 폴더 양쪽을 지원합니다. 기존 풀이 폴더 이름을 바꿀 필요가 없습니다.

지원 조건은 경로에 `프로그래머스` 폴더가 있고, 문제 폴더가 `문제번호.제목`이며, 그 안에 비어 있지 않은 C++ 파일과 같은 문제 URL을 담은 README가 있는 것입니다. 이 형식을 정답 업로드의 근거로 사용하며, 저지에 접속해 정답 여부를 재검증하지 않습니다. 임의로 만든 파일까지 독립 정답으로 인증하는 기능은 아닙니다.

진도표는 별도 `progress` 브랜치의 README에 생성됩니다. 업로드 도구가 쓰는 `main`에는 자동 진도 커밋을 만들지 않습니다. 원본 [12주 계획](plan.md)의 체크는 개념·설명·오답 정리를 포함한 수동 학습 완료이며 그대로 유지합니다. 생성된 진도표의 Day·Week 완료는 아래 객관적 풀이 기준입니다.

## CSES·LeetCode·추가 문제·재풀이

CSES는 `solutions/cses/1068.cpp`, LeetCode는 `solutions/leetcode/two-sum.cpp`처럼 정답 확인 후 코드를 저장하면 자동 감지됩니다. 확장자는 `.cpp`, `.cc`, `.cxx`를 지원합니다. LeetCode는 숫자 번호가 아닌 문제 URL의 slug를 사용합니다. 빈 파일과 심볼릭 링크는 감지하지 않습니다. 이 경로는 정답 풀이 전용이며 작업 중인 코드는 다른 폴더에 두세요. 파일만으로 온라인 저지의 Accepted 여부나 독립 해결 여부를 검증하지 않습니다.

추가 문제는 [Day별 후보 목록](pools.md)의 N개 중 M개만 해결하면 됩니다. `pools.json`에 모든 Day의 후보 ID와 필요 개수가 정의되어 있어 파일 업로드만으로 날짜가 배정됩니다. 재풀이와 자동 감지 경로 밖의 정답 코드는 `records.json`에 기록합니다. 다음은 형식 예시이며 실제로 해결한 뒤 추가하세요.

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
- `week/day`: 실제 기록할 학습일. 필수·후보 문제의 목표 배정은 커리큘럼이 우선합니다. 목록 밖의 기존 신규 기록은 해당 날짜의 참고 풀이로 보존하지만 필수·후보 목표를 대신 채우지 않습니다.
- 기존에 해결한 문제를 재풀이 실패해도 이전 해결 상태는 지우지 않습니다. 재풀이 시도와 정답·힌트 미사용 횟수를 별도로 표시합니다.
- 추가 문제는 두 날짜의 신규 문제로 중복 배정할 수 없습니다. 다음 학습은 `review`로 기록하세요.
- 계획의 지정 문제를 교체하려면 `plan.md`의 해당 문제 링크를 바꿉니다. 수동 기록만 추가하면 원래 문제는 그대로 남습니다.

208은 신규 학습 목표입니다. 등록 문제는 필수 144개 + 후보 110개 = 254개이며 기존 목록 밖 수동 기록이 있으면 추가로 표시합니다. 후보 전체를 풀 필요는 없습니다. 각 Day의 후보 해결 수는 필요 개수까지만 목표에 반영합니다. 자동 업로드된 미배정 문제는 목표에 반영하지 않습니다.

## v2 계산 기준과 데이터

- 문제 식별자는 `platform:problemId`이며 CSES·프로그래머스는 번호, LeetCode는 slug입니다. `plan.md`는 필수 문제·주제·목표·수동 체크, `pools.json`은 84개 Day의 추가 후보를 관리합니다. `pools.md`는 데이터에서 생성하는 문서입니다. `progress.json`의 `days`에 두 입력을 합칩니다.
- 각 `pools.json` 항목은 `id`, `week`, `day`, `required`, `candidates`를 가집니다. 각 후보에는 `key`, `platform`, `problemId`, `title`, `url`이 필요합니다. `required`는 신규 목표에서 필수 문제 수를 뺀 값이어야 합니다. 후보와 필수 문제, 다른 Day 후보의 중복은 오류로 처리합니다. 추가 목표가 0인 Day는 빈 후보 배열입니다.
- 같은 문제의 여러 파일·확장자·정답 기록은 신규 한 문제로 집계합니다. 중복 배정된 문제는 첫 날짜만 신규로 계산합니다.
- Day 완료는 필수 문제 전부 해결, 후보 N개 중 M개 해결, 정답 재풀이 목표 충족이 모두 필요합니다. 선택하지 않은 후보는 미해결로 남아도 Day가 완료됩니다. 후보 초과분은 필수 문제나 재풀이 부족분을 대체하지 않습니다.
- 재풀이는 명시적 기록의 `accepted`만 완료 목표에 반영합니다. 같은 Day의 같은 문제는 id·날짜·파일을 바꿔도 1개로 계산하므로 오답 6개는 서로 다른 6문제여야 합니다. `attempted`를 포함한 원본 기록은 보존합니다. 실제로 다시 풀었을 때만 새 id를 만드세요. 파일 수정이나 재업로드만으로 재풀이 횟수는 늘지 않습니다.
- Week는 7일 모두 완료할 때 완료됩니다. 전체 진도율은 날짜별 신규·재풀이 목표에 각각 상한을 적용한 완료 수 / 283입니다. 별도로 완료 Day와 Week 수를 표시합니다.
- Week 12 Day 7은 문제 목표가 없으므로 원본 `- [x] W12-D7:` 체크가 필요합니다. 전체 풀이 진도가 100%여도 이 수동 목표가 남으면 전체 완료는 false입니다.
- `progress.json`의 `schemaVersion: 2`, `days`, `weeks`, `overall`, `reviews`, `evidence`가 계산 결과입니다. README는 같은 결과로 생성합니다. 실행 시간 필드를 넣지 않아 입력이 같으면 결과도 같습니다.
- 각 Day의 `additional`은 `candidates`(문제별 solved), `required`, `solved`(후보 전체 해결 수), `credited`(목표 반영 수), `complete`를 제공합니다. `requiredSolved`는 필수 해결 수, `newSolved`는 필수 해결 수 + 후보 목표 반영 수입니다.
- 새 플랫폼은 `scripts/adapters.mjs`에 파일 → 문제 식별자 어댑터를 추가하고 URL 인식은 `problemKey`에 확장합니다. 계산기는 플랫폼별 처리를 하지 않습니다.
- 자동 진도는 원본 계획의 수동 학습 체크를 덮어쓰지 않습니다. 개념 설명·오답 이유·독립 해결 여부를 파일 존재만으로 완료 처리하지 않습니다.

## Actions 권한과 배포

PR에서는 읽기 권한으로 테스트합니다. main 푸시 또는 main에서 수동 실행 시 테스트 성공 후 게시 작업에만 `contents: write`를 부여합니다. 별도 Git worktree에서 README와 progress.json만 추가하고 변경이 있을 때만 커밋합니다. progress 브랜치 푸시는 재실행을 유발하지 않으며 강제 푸시는 사용하지 않습니다.

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
node scripts/render-pools.mjs --check
node scripts/progress.mjs
```

로컬 결과는 `generated/README.md`입니다. 이 폴더는 Git 커밋에서 제외됩니다.

## 참고

- [BaekjoonHub](https://github.com/BaekjoonHub/BaekjoonHub)
- [GitHub Actions 실행 조건](https://docs.github.com/en/actions/how-tos/write-workflows/choose-when-workflows-run/trigger-a-workflow)
