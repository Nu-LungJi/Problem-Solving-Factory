@echo off
setlocal
chcp 65001 >nul

where node >nul 2>nul
if errorlevel 1 (
  echo Node.js 22 or newer is required. Install Node.js and try again.
  pause
  exit /b 1
)

REM Rider C++ 프로젝트 루트
set "PSF_PROJECT=C:\Users\Yun\Documents\Rider\PSFactory"

echo.
echo Rider 프로젝트:
echo %PSF_PROJECT%
echo.

node "%~dp0scripts\psf.mjs" start

set "PSF_EXIT=%ERRORLEVEL%"
echo.
if not "%PSF_EXIT%"=="0" pause
exit /b %PSF_EXIT%