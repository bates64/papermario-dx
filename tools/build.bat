@echo off
setlocal enabledelayedexpansion

set "REPO=bates64/papermario-dx"
set "DX_DIR=%~dp0..\.dx"
set "TOOLCHAIN_DIR=%DX_DIR%\windows"
set "TOOLCHAIN_ZIP=%DX_DIR%\papermario-dx-windows.zip"

call tools/windows/download_toolchain.bat
if errorlevel 1 exit /b 1

for %%I in ("%~dp0..") do set "ROOT=%%~fI"
set "SCCACHE_CONF=%ROOT%\.dx\sccache-config.toml"
set "AWS_SHARED_CREDENTIALS_FILE=%ROOT%\.dx\sccache-credentials"
set "SCCACHE_BASEDIRS=%ROOT%"

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
ninja.exe %*
