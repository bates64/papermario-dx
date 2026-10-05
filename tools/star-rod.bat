@echo off
setlocal enabledelayedexpansion

set "DX_DIR=%~dp0..\.dx"
set "TOOLCHAIN_DIR=%DX_DIR%\windows"
set "TOOLCHAIN_ZIP=%DX_DIR%\papermario-dx-windows.zip"

call tools/windows/download_toolchain.bat
if errorlevel 1 exit /b 1

"%TOOLCHAIN_DIR%\bin\star-rod.bat" %*
