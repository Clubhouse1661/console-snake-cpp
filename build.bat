@echo off
echo Building Console Snake C++ Game...
echo.

echo Compiling with GCC...
g++ -std=c++17 -o ConsoleSnakeCpp.exe src/*.cpp -luser32 -lkernel32

if %ERRORLEVEL% EQU 0 (
    echo.
    echo Build successful! Executable created: ConsoleSnakeCpp.exe
    echo.
    echo To run the game, use: run_game.bat
) else (
    echo.
    echo Build failed! Please check the error messages above.
)

pause
