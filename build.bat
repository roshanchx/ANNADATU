@echo off
setlocal
if not exist build mkdir build
g++ -std=c++17 -Wall -Wextra -pedantic -Iinclude src\*.cpp -o build\annadatu.exe
if errorlevel 1 (
    echo Build failed. Make sure MinGW-w64 g++ is installed and added to PATH.
    exit /b 1
)
echo Build successful: build\annadatu.exe
endlocal
