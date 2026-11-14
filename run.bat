@echo off
setlocal
if not exist build\annadatu.exe call build.bat
if errorlevel 1 exit /b 1
build\annadatu.exe
endlocal
