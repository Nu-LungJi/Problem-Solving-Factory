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

시작일을 바꾸려면 `curriculum/schedule.json`의 `startDate`를 수정하세요. 일정 밖에서는 안내 후 종료합니다. PC 시간대는 한국 시간으로 맞추세요.

## PSF_START

1. 저장소가 깨끗한지 확인하고 `git pull --ff-only`로 최신 커리큘럼과 풀이를 받습니다. 미커밋 변경이나 브랜치 분기가 있으면 중단합니다.
2. 날짜·문제 선택 질문 없이 **오늘 날짜의 Day**를 바로 준비합니다.
3. 저장소에 정답 코드가 올라가 해결된 문제는 건너뜁니다. 미해결 필수 문제와 후보 중 필요한 개수만 준비합니다. 후보는 기존 작업 파일을 먼저 이어 쓰고, 부족한 개수만 목록 순서로 선택합니다.
4. Windows의 문서 폴더 아래 `Rider\Algorithm Project`에 없는 파일만 만듭니다. **기존 파일은 덮어쓰거나 복제하지 않습니다.** 문제 URL과 기본 C++ 틀만 넣으며 풀이를 대신 작성하지 않습니다.
5. 오늘의 작업 파일을 `.vcxproj`와 `.vcxproj.filters`에 자동 Add합니다. 이미 있는 프로젝트 항목은 다시 추가하지 않습니다. 예전 START로 생성됐지만 Add되지 않은 파일도 등록합니다. 수정 전 프로젝트 파일은 프로젝트 폴더의 `.psf-project-backups`에 백업합니다.
6. Rider 프로젝트를 열고 첫 작업 파일을 엽니다. 새 C++ 항목은 여러 `main`이 함께 링크되지 않도록 `ExcludedFromBuild=true`로 등록합니다. 기존 빌드 대상은 유지되므로 실행할 문제의 빌드 제외 설정만 Rider에서 변경하세요.

성공하면 배치 창은 자동으로 닫힙니다. 수동 학습일 또는 준비할 문제가 없는 날은 안내 후 종료합니다. 파일이 있다는 이유만으로 정답 처리하지는 않습니다.

| 플랫폼 | Rider 작업 파일 | 업로드 경로 |
|---|---|---|
| CSES | `1068.cpp` | `solutions/cses/1068.cpp` |
| LeetCode | `fizz-buzz.cpp` | `solutions/leetcode/fizz-buzz.cpp` |
| 프로그래머스 | `programmers-12925.cpp` | `solutions/programmers/12925.cpp` |

예를 들어 Week 1 Day 1의 CSES 두 문제가 미해결이라면 `1068.cpp`, `1083.cpp`를 준비합니다. 두 문제는 현재 저장소에 해결 기록이 있으므로 건너뛰고 추가 후보 파일을 준비합니다.

같은 날 다시 START를 실행하면 기존 세션과 파일을 재사용합니다. 기존 세션에 추가 후보가 여러 개 있어도 그 파일과 템플릿 식별 정보를 유지합니다. 날짜가 바뀌면 자동으로 오늘 Day를 시작하며 이전 세션은 `.psf/history`에 보관하고 소스도 유지합니다. **UPLOAD는 현재 세션의 작업 파일만 처리**하므로 이전 작업은 새 Day를 시작하기 전에 업로드하세요.

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
