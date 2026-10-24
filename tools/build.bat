@echo off
setlocal enabledelayedexpansion

set "DX_DIR=%~dp0..\.dx"
set "TOOLCHAIN_DIR=%DX_DIR%\windows"
set "TOOLCHAIN_ZIP=%DX_DIR%\papermario-dx-windows.zip"

call tools/windows/download_toolchain.bat
if errorlevel 1 exit /b 1

for %%I in ("%~dp0..") do set "ROOT=%%~fI"
set "SCCACHE_CONF=%ROOT%\.dx\sccache-config.toml"
set "AWS_SHARED_CREDENTIALS_FILE=%ROOT%\.dx\sccache-credentials"
set "SCCACHE_BASEDIRS=%ROOT%"
set "SCCACHE_SKIP_CACHE_CHECK=1"

rem Set up PATH
set "PATH=%TOOLCHAIN_DIR%\bin;%TOOLCHAIN_DIR%\python;%PATH%"
set "PYTHONUTF8=1"

rem Configure if needed
if not exist build.ninja (
    echo Running configure...
    python.exe tools\build\configure.py
    if errorlevel 1 exit /b 1
)

rem Parallel compiles that find no sccache server all try to start one, and all
rem but one fail, so start it first. It fails harmlessly if one is running.
sccache.exe --start-server >nul 2>nul

rem Build
echo Building...
ninja.exe %*
