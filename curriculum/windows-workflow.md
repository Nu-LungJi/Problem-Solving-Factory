# Windows에서 하루 풀이 시작·업로드

저장소 폴더의 **PSF_START.bat**, **PSF_UPLOAD.bat**을 더블클릭합니다. 두 파일은 `scripts`의 보조 프로그램을 사용하므로 저장소 안에 그대로 두세요. Git과 Node.js 22 이상이 필요합니다.

## 날짜

`schedule.json`의 시작일은 **2026-09-15 = Week 1 Day 1**입니다. 컴퓨터의 오늘 날짜를 기준으로 하루에 Day 하나씩 진행합니다. 풀이 완료 여부로 날짜를 미루지 않습니다.

| 날짜 | 커리큘럼 |
|---|---|
| 2026-09-15 | Week 1 Day 1 |
| 2026-09-16 | Week 1 Day 2 |
| 2026-09-21 | Week 1 Day 7 |
| 2026-09-22 | Week 2 Day 1 |
| 2026-12-07 | Week 12 Day 7 |

시작일을 바꾸려면 `curriculum/schedule.json`의 `startDate`를 수정하세요. 일정 밖에서는 자동으로 다른 날짜를 반복하지 않고 진행할 Week와 Day를 입력받습니다. PC 시간대는 한국 시간으로 맞추세요.

## PSF_START

1. 저장소가 깨끗한지 확인하고 `git pull --ff-only`로 최신 커리큘럼과 풀이를 받습니다. 미커밋 변경이나 브랜치 분기가 있으면 중단합니다.
2. 오늘 Week·Day를 표시합니다. Enter는 오늘, `1 1`처럼 입력하면 다른 Day를 엽니다.
3. 필수 문제와 후보 목록을 표시합니다. Enter는 미해결 필수 + 후보 중 아직 필요한 개수를 선택합니다. 후보 기본 선택은 목록 순서이며 `1,2,4`처럼 번호를 입력해 직접 고를 수 있습니다. 이미 해결한 문제도 번호로 선택해 다시 열 수 있습니다.
4. Windows의 문서 폴더 아래 `Rider\Algorithm Project`에 파일을 만듭니다. **기존 파일은 덮어쓰지 않습니다.** 문제 URL과 기본 C++ 틀만 넣으며 풀이를 대신 작성하지 않습니다.
5. Rider의 기존 `.slnx`/`.sln` 프로젝트를 열고 선택한 첫 파일을 엽니다. 기존 프로젝트의 빌드 설정은 수정하지 않습니다. 새 파일을 실행하려면 Rider에서 해당 파일을 빌드 대상으로 지정하세요. 여러 `main`을 동시에 빌드하지 않도록 기존처럼 한 파일을 대상으로 사용합니다.

| 플랫폼 | Rider 작업 파일 | 업로드 경로 |
|---|---|---|
| CSES | `1068.cpp` | `solutions/cses/1068.cpp` |
| LeetCode | `fizz-buzz.cpp` | `solutions/leetcode/fizz-buzz.cpp` |
| 프로그래머스 | `programmers-12925.cpp` | `solutions/programmers/12925.cpp` |

예를 들어 Week 1 Day 1에서 CSES 두 문제를 선택하면 `1068.cpp`, `1083.cpp`가 준비되고 `1068.cpp`를 엽니다. 두 문제는 현재 저장소에 해결 기록이 있으므로 기본 선택은 추가 후보만 제안할 수 있습니다.

진행 중인 세션은 같은 날 다시 START를 실행하면 이어서 엽니다. `new`를 입력하면 다른 선택을 할 수 있습니다. 날짜가 바뀌면 기본은 오늘 Day이고 `resume`을 입력하면 이전 작업을 엽니다. 바뀐 세션은 `.psf/history`에 보관하고 기존 소스 파일도 유지합니다. **UPLOAD는 현재 세션의 선택된 파일만 처리**하므로 이전 작업은 새 Day를 시작하기 전에 업로드하세요.

## PSF_UPLOAD

1. 저장소 상태를 확인하고 최신 변경을 pull합니다. Rider에서 편집한 파일은 먼저 저장하세요.
2. START에서 선택한 파일 중 변경된 풀이를 표시합니다. 그대로인 초기 템플릿, 빈 파일, 이미 업로드한 동일 내용은 건너뜁니다.
3. 각 문제에 정답 제출 여부를 묻습니다. `y`인 문제만 복사합니다. 힌트·해설 사용 여부도 `y` 또는 `n`으로 입력합니다. 이 값은 파일만으로 알 수 없으므로 직접 확인합니다.
4. 저장소의 같은 경로에 다른 코드가 있으면 갱신 여부를 묻습니다. 원본 Rider 파일은 복사 후에도 남습니다.
5. `curriculum/records.json` 배열에 기록을 추가하고 진도 계산기로 검증합니다. **파일명은 `record.json`이 아니라 `curriculum/records.json`입니다.** 날짜는 실제 업로드 날짜, Week·Day는 START에서 선택한 학습일입니다.
6. 커밋 메시지를 입력합니다. 예: `Day 1 / CSES 1068, 1083 해결`. 선택한 풀이와 기록 파일만 커밋합니다. 한글·따옴표·특수문자는 그대로 메시지에 저장합니다.
7. `GitHub에도 push할까요? [y/N]`에서 `y`를 입력하면 push합니다. Enter는 로컬 커밋까지만 합니다. 나중에 다시 UPLOAD를 실행해 push하거나 직접 `git push`해도 됩니다.

첫 정답 기록 예:

```json
{
  "id": "2026-09-15-cses-1083-first",
  "date": "2026-09-15",
  "week": 1,
  "day": 1,
  "url": "https://cses.fi/problemset/task/1083/",
  "code": "solutions/cses/1083.cpp",
  "kind": "solve",
  "result": "accepted",
  "usedHint": true
}
```

기존 최초 정답 기록이 있으면 중복 추가하지 않고 원래 날짜·힌트 사용 기록을 보존합니다. 코드 수정으로 풀이 횟수를 늘리지 않습니다. 재풀이 Day에는 이전에 해결한 문제 목록을 제시하며 별도 `*-review-*.cpp` 파일을 새로 만듭니다. 원래 정답을 덮어쓰지 않고 `solutions/reviews/week-N-day-N/...`에 저장하며 명시적 `review` 기록을 추가합니다. 같은 Day의 같은 문제 재풀이는 진도에 한 번만 반영됩니다.

## 경로와 오류 처리

- 기본 프로젝트: Windows 문서 폴더의 `Rider\Algorithm Project`. 환경 변수 `PSF_PROJECT`로 다른 경로를 지정할 수 있습니다.
- Rider: PATH의 `rider64.exe`, 다음으로 `Program Files\JetBrains` 설치를 찾습니다. Toolbox나 다른 설치 위치라면 `PSF_RIDER`에 `rider64.exe` 전체 경로를 지정하세요.
- `.psf/`는 PC별 세션 정보이며 Git에서 제외합니다. 이 폴더의 파일을 다른 사람에게서 받아 실행하지 마세요.
- Git 사용자 이름·이메일이 설정되어 있어야 커밋할 수 있습니다. Git 인증은 기존 clone의 설정을 그대로 사용합니다. 별도 토큰을 저장하지 않습니다.
- 커밋 실패 시 소스와 기록 변경은 남겨둡니다. `git status`를 확인해 직접 커밋한 뒤 다시 사용하세요. push 실패는 이미 만들어진 로컬 커밋을 지우지 않습니다.
- 미커밋 변경을 숨기거나 다른 브랜치로 강제 전환하거나 force push하지 않습니다.

검증: `node --test tests/*.test.mjs`. 테스트는 임시 Git 저장소에서 파일 생성·복사·기록·커밋을 검증하며 실제 풀이 저장소에 정답을 추가하지 않습니다.

Rider 실행 방식: [JetBrains 공식 파일 열기 문서](https://www.jetbrains.com/help/rider/Opening_Files_from_Command_Line.html).
