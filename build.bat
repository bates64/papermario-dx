@echo off
setlocal enabledelayedexpansion

set "REPO=bates64/papermario-dx"
set "TOOLCHAIN_DIR=%~dp0papermario-dx-windows"
set "TOOLCHAIN_ZIP=%~dp0papermario-dx-windows.zip"

:: Check for git
where git >nul 2>nul
if errorlevel 1 (
    echo Error: git is not installed. Install it from https://git-scm.com/ or via: winget install Git.Git
    exit /b 1
)

:: Get the nearest dx-* tag (current commit or ancestor)
git describe --tags --abbrev=0 --match dx-* > "%TEMP%\dx-tag.txt" 2>nul
set /p TAG=<"%TEMP%\dx-tag.txt"
del "%TEMP%\dx-tag.txt" 2>nul
if not defined TAG (
    echo Error: no dx-* tag found in the commit history.
    echo The Windows build requires a tagged release with a pre-built toolchain.
    exit /b 1
)

:: Get the commit hash the tag points to (detects force-moved tags like dx-nightly)
git rev-parse "%TAG%^{}" > "%TEMP%\dx-tag-hash.txt" 2>nul
set /p TAG_HASH=<"%TEMP%\dx-tag-hash.txt"
del "%TEMP%\dx-tag-hash.txt" 2>nul

:: Check if toolchain needs downloading
set "NEED_DOWNLOAD=0"
if not exist "%TOOLCHAIN_DIR%\bin\ninja.exe" set "NEED_DOWNLOAD=1"
if exist "%TOOLCHAIN_DIR%\.tag" (
    set /p CURRENT_TAG=<"%TOOLCHAIN_DIR%\.tag"
    if not "!CURRENT_TAG!"=="%TAG_HASH%" set "NEED_DOWNLOAD=1"
) else (
    if exist "%TOOLCHAIN_DIR%" set "NEED_DOWNLOAD=1"
)

if "%NEED_DOWNLOAD%"=="1" (
    echo Downloading toolchain for %TAG%...

    :: Clean up old toolchain
    if exist "%TOOLCHAIN_DIR%" rmdir /s /q "%TOOLCHAIN_DIR%"
    if exist "%TOOLCHAIN_ZIP%" del "%TOOLCHAIN_ZIP%"

    :: Download from GitHub release
    set "URL=https://github.com/%REPO%/releases/download/%TAG%/papermario-dx-windows.zip"
    curl -L -o "%TOOLCHAIN_ZIP%" "!URL!"
    if errorlevel 1 (
        echo Error: failed to download toolchain from !URL!
        exit /b 1
    )

    :: Extract
    echo Extracting toolchain...
    tar -xf "%TOOLCHAIN_ZIP%" -C "%~dp0."
    if errorlevel 1 (
        echo Error: failed to extract toolchain.
        exit /b 1
    )
    del "%TOOLCHAIN_ZIP%"

    :: Record the tag commit hash so we can detect updates (including force-moved tags)
    echo %TAG_HASH%> "%TOOLCHAIN_DIR%\.tag"
)

:: Set up PATH
set "PATH=%TOOLCHAIN_DIR%\bin;%TOOLCHAIN_DIR%\python;%PATH%"
set "PYTHONUTF8=1"

:: Configure if needed
if not exist build.ninja (
    echo Running configure...
    python.exe tools\build\configure.py
    if errorlevel 1 exit /b 1
)

:: Build
echo Building...
ninja.exe
