@echo off

:: Ensure .dx directory exists
if not exist "%DX_DIR%" mkdir "%DX_DIR%"

:: Get the nearest dx-* tag (current commit or ancestor): prefer jj if this
:: is a jj repo, otherwise fall back to git.
set "HAVE_JJ=0"
if exist ".jj" (
    where jj >nul 2>nul
    if not errorlevel 1 set "HAVE_JJ=1"
)
set "HAVE_GIT=0"
where git >nul 2>nul
if not errorlevel 1 set "HAVE_GIT=1"

if "%HAVE_JJ%"=="0" if "%HAVE_GIT%"=="0" (
    echo Error: this needs jj or git to find the toolchain version to download.
    echo Install jj: https://jj-vcs.github.io/jj/latest/install-and-setup/
    echo Or install git: https://git-scm.com/ ^(or: winget install Git.Git^)
    exit /b 1
)

set "TAG="
set "TAG_HASH="
if "%HAVE_JJ%"=="1" (
    for /f "usebackq delims=" %%T in (`jj log -r "latest(tags(glob:'dx-*') & ::@)" --no-graph -T "self.tags().join('|')" 2^>nul`) do if not defined TAG set "TAG=%%T"
    if defined TAG (
        for /f "usebackq delims=" %%H in (`jj log -r "latest(tags(glob:'dx-*') & ::@)" --no-graph -T "commit_id" 2^>nul`) do set "TAG_HASH=%%H"
    )
) else (
    git describe --tags --abbrev=0 --match dx-* > "%TEMP%\dx-tag.txt" 2>nul
    set /p TAG=<"%TEMP%\dx-tag.txt"
    del "%TEMP%\dx-tag.txt" 2>nul
    if defined TAG (
        :: Get the commit hash the tag points to (detects force-moved tags like dx-nightly)
        git rev-parse "!TAG!^{}" > "%TEMP%\dx-tag-hash.txt" 2>nul
        set /p TAG_HASH=<"%TEMP%\dx-tag-hash.txt"
        del "%TEMP%\dx-tag-hash.txt" 2>nul
    )
)

if not defined TAG (
    echo Error: no dx-* tag found in the commit history.
    echo The Windows build requires a tagged release with a pre-built toolchain.
    exit /b 1
)

:: Check if toolchain needs downloading
set "NEED_DOWNLOAD=0"
if not exist "%TOOLCHAIN_DIR%\bin\ninja.exe" set "NEED_DOWNLOAD=1"
if exist "%DX_DIR%\windows-tag" (
    set /p CURRENT_TAG=<"%DX_DIR%\windows-tag"
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
    
    where unzip >nul 2>nul
    if not errorlevel 1 (
        :: mingw/git bash's tar command works differently to windows' builtin one so we're using unzip instead
        unzip -qo "%TOOLCHAIN_ZIP%" -d "%DX_DIR%"
    ) else (
        :: Using windows' tar command
        where tar >nul 2>nul
        if errorlevel 1 (
            echo msgbox "tar is not available on this system (Windows 7)." ^& vbCrLf ^& vbCrLf ^& "Please manually extract:" ^& vbCrLf ^& "%TOOLCHAIN_ZIP%" ^& vbCrLf ^& vbCrLf ^& "To the following directory:" ^& vbCrLf ^& "%DX_DIR%\windows" ^& vbCrLf ^& vbCrLf ^& "Then run build.bat again.", vbOKOnly, "papermario-dx" > "%TEMP%\dx-notar.vbs"
            wscript "%TEMP%\dx-notar.vbs"
            del "%TEMP%\dx-notar.vbs"
            exit /b 1
        )
        tar -xf "%TOOLCHAIN_ZIP%" -C "%DX_DIR%"
        if errorlevel 1 (
            echo Error: failed to extract toolchain.
            exit /b 1
        )
    )
    ren "%DX_DIR%\papermario-dx-windows" windows
    del "%TOOLCHAIN_ZIP%"

    :: Record the tag commit hash so we can detect updates (including force-moved tags)
    echo %TAG_HASH%> "%DX_DIR%\windows-tag"
)
