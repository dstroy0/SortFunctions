@echo off
setlocal EnableDelayedExpansion

:: ---------------------------------------------------------------
:: SortFunctions Test Suite - Windows Build Script
:: Run from anywhere: tests\run_tests.bat  OR  cd tests && run_tests.bat
:: Requires: g++ (MinGW-w64 or MSYS2) on PATH
:: ---------------------------------------------------------------

set "SCRIPT_DIR=%~dp0"
set "SRC_DIR=%SCRIPT_DIR%..\src"
set "OUT=%SCRIPT_DIR%test_runner.exe"

echo.
echo ================================================================
echo   SortFunctions Library - Test Suite  [Windows]
echo ================================================================
echo.

:: Check compiler is available
where g++ >nul 2>&1
if errorlevel 1 (
    echo  ERROR: g++ not found in PATH.
    echo  Install MinGW-w64 ^(https://www.mingw-w64.org^) or MSYS2
    echo  ^(https://www.msys2.org^) and add g++ to your PATH, then retry.
    echo.
    exit /b 1
)

for /f "tokens=*" %%v in ('g++ --version 2^>^&1 ^| findstr /r "g++"') do (
    echo  Compiler : %%v
)
echo  Source   : %SRC_DIR%\SortFunctions.cpp
echo  Tests    : %SCRIPT_DIR%test_main.cpp
echo  Output   : %OUT%
echo.

:: ---- Step 1: Compile ----
echo [1/2] Compiling...
pushd "%SCRIPT_DIR%"
g++ -std=c++11 -Wall -I. -I..\src test_main.cpp ..\src\SortFunctions.cpp -o test_runner.exe
set "COMPILE_EXIT=!ERRORLEVEL!"
popd

if !COMPILE_EXIT! neq 0 (
    echo.
    echo  [FAIL] Compilation failed. See errors above.
    echo.
    exit /b 1
)
echo        Compilation succeeded.
echo.

:: ---- Step 2: Run ----
echo [2/2] Running tests...
echo.
"%OUT%"
set "TEST_EXIT=!ERRORLEVEL!"
echo.

if !TEST_EXIT! == 0 (
    echo  Build and tests completed successfully.
) else (
    echo  Build succeeded but one or more tests FAILED.
)

del "%SCRIPT_DIR%test_runner.exe" >nul 2>&1
echo.
exit /b !TEST_EXIT!
