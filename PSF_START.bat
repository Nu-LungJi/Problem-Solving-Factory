@echo off
setlocal
chcp 65001 >nul

where node >nul 2>nul
if errorlevel 1 (
  echo Node.js 22 or newer is required. Install Node.js and try again.
  pause
  exit /b 1
)

REM 오늘 날짜를 YYYY-MM-DD 형식으로 가져오기
for /f %%i in ('powershell -NoProfile -Command "Get-Date -Format yyyy-MM-dd"') do set "TODAY=%%i"

REM 새 프로젝트의 Solved 폴더
set "PROJECT_ROOT=C:\Users\Yun\Documents\Rider\PSFactory
set "PSF_PROJECT=%PROJECT_ROOT%\Solved\%TODAY%"

REM 오늘 날짜 폴더가 없으면 생성
if not exist "%PSF_PROJECT%" (
  mkdir "%PSF_PROJECT%"
)

echo.
echo 오늘 풀이 폴더:
echo %PSF_PROJECT%
echo.

node "%~dp0scripts\psf.mjs" start

set "PSF_EXIT=%ERRORLEVEL%"
echo.
if not "%PSF_EXIT%"=="0" pause
exit /b %PSF_EXIT%