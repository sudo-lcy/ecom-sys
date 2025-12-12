@echo off
REM Simple build script for Windows (uses g++ or cl)
SET SRC=src\main.cpp
SET OUT=ecommerce.exe

REM Prefer g++ if available
where g++ >nul 2>&1
IF %ERRORLEVEL% == 0 (
    g++ -std=c++17 -O2 -Wall %SRC% -o %OUT%
    IF %ERRORLEVEL% == 0 (
        echo Build succeeded with g++ -> %OUT%
        exit /b 0
    ) ELSE (
        echo g++ build failed
        exit /b 1
    )
)

REM Fallback to MSVC cl (requires Developer Command Prompt)
where cl >nul 2>&1
IF %ERRORLEVEL% == 0 (
    cl /EHsc /Fo:build\ /Fe:%OUT% %SRC%
    IF %ERRORLEVEL% == 0 (
        echo Build succeeded with cl -> %OUT%
        exit /b 0
    ) ELSE (
        echo cl build failed
        exit /b 1
    )
)

echo No supported compiler found (g++ or cl). Install MinGW/MSYS2 or use Visual Studio Developer Tools.
exit /b 2
