@echo off
setlocal
chcp 65001 >nul
where node >nul 2>nul
if errorlevel 1 (
  echo Node.js 22 or newer is required. Install Node.js and try again.
  pause
  exit /b 1
)
node "%~dp0scripts\psf.mjs" start
set "PSF_EXIT=%ERRORLEVEL%"
echo.
pause
exit /b %PSF_EXIT%
