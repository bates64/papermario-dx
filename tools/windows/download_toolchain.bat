@echo off

set "CANONICAL_URL=https://github.com/bates64/papermario-dx.git"
set "S3_BASE=https://fsn1.your-objectstorage.com/starhaven/papermario-dx"

:: Ensure .dx directory exists
if not exist "%DX_DIR%" mkdir "%DX_DIR%"

set "HAVE_JJ=0"
if exist ".jj" (
    where jj >nul 2>nul
    if not errorlevel 1 set "HAVE_JJ=1"
)
set "HAVE_GIT=0"
where git >nul 2>nul
if not errorlevel 1 set "HAVE_GIT=1"

:: Toolchains are only published for commits on dx's main branch. Since
:: users branch away from main, walking back from the current commit alone
:: would just walk through their own commits, none of which are published.
:: Fetching main and taking the merge-base finds the point where their
:: history actually meets dx's, wherever they've branched from. From there,
:: list up to 20 commits to try - a commit's build can be missing if CI
:: failed for it.
set "CANDIDATES_FILE=%DX_DIR%\candidates.txt"
if exist "%CANDIDATES_FILE%" del "%CANDIDATES_FILE%"
if "%HAVE_JJ%"=="1" (
    rem jj can only fetch from a named remote, so use whichever one points at dx.
    set "REMOTE="
    for /f "usebackq tokens=1,2" %%A in (`jj git remote list 2^>nul`) do (
        if not defined REMOTE (
            echo %%B | findstr /c:"bates64/papermario-dx" >nul && set "REMOTE=%%A"
        )
    )
    set "REVSET=@"
    if defined REMOTE (
        jj git fetch --quiet --remote "exact:!REMOTE!" --branch main >nul 2>nul
        set "REVSET=fork_point(@ | remote_bookmarks(exact:main, exact:!REMOTE!))"
    )
    jj log --no-graph -r "ancestors(!REVSET!, 20)" -T "commit_id ++ \"\n\"" > "%CANDIDATES_FILE%" 2>nul
) else if "%HAVE_GIT%"=="1" (
    set "CURRENT="
    for /f "usebackq delims=" %%C in (`git rev-parse HEAD 2^>nul`) do set "CURRENT=%%C"
    set "BASE=!CURRENT!"
    git fetch --quiet "%CANONICAL_URL%" main >nul 2>nul
    set "MAIN_HASH="
    for /f "usebackq delims=" %%M in (`git rev-parse FETCH_HEAD 2^>nul`) do set "MAIN_HASH=%%M"
    if defined MAIN_HASH (
        for /f "usebackq delims=" %%B in (`git merge-base "!CURRENT!" "!MAIN_HASH!" 2^>nul`) do set "BASE=%%B"
    )
    if defined BASE git log --format^=%%H -n 20 "!BASE!" > "%CANDIDATES_FILE%" 2>nul
) else (
    echo Error: this needs jj or git to find the toolchain version to download.
    echo Install jj ^(https://jj-vcs.github.io/jj/latest/install-and-setup/^) or git ^(https://git-scm.com/^).
    exit /b 1
)

set "BASE="
if exist "%CANDIDATES_FILE%" set /p BASE=<"%CANDIDATES_FILE%"
if not defined BASE (
    echo Error: could not determine the current commit.
    exit /b 1
)

set "HASH="
set "COMMIT="
for /f "usebackq delims=" %%L in ("%CANDIDATES_FILE%") do (
    if not defined HASH (
        set "CANDIDATE="
        curl -fsL -o "%TEMP%\dx-manifest.txt" "%S3_BASE%/commits/%%L/windows" 2>nul
        if not errorlevel 1 (
            set /p CANDIDATE=<"%TEMP%\dx-manifest.txt"
            if defined CANDIDATE (
                set "HASH=!CANDIDATE!"
                set "COMMIT=%%L"
            )
        )
        del "%TEMP%\dx-manifest.txt" 2>nul
    )
)
del "%CANDIDATES_FILE%"

if not defined HASH (
    echo Error: no published windows toolchain found near commit %BASE%.
    echo The downloadable toolchain requires a build published from dx's main branch.
    exit /b 1
)

:: Check if toolchain needs downloading
set "NEED_DOWNLOAD=0"
if not exist "%TOOLCHAIN_DIR%\bin\ninja.exe" set "NEED_DOWNLOAD=1"
if exist "%DX_DIR%\windows-hash" (
    set /p CURRENT_HASH=<"%DX_DIR%\windows-hash"
    if not "!CURRENT_HASH!"=="%HASH%" set "NEED_DOWNLOAD=1"
) else (
    if exist "%TOOLCHAIN_DIR%" set "NEED_DOWNLOAD=1"
)

if "%NEED_DOWNLOAD%"=="1" (
    echo Downloading toolchain for commit %COMMIT%...

    :: Clean up old toolchain
    if exist "%TOOLCHAIN_DIR%" rmdir /s /q "%TOOLCHAIN_DIR%"
    if exist "%TOOLCHAIN_ZIP%" del "%TOOLCHAIN_ZIP%"

    :: Download from S3
    set "URL=%S3_BASE%/toolchains/%HASH%.zip"
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
            echo msgbox "tar is not available on this system (Windows 7)." ^& vbCrLf ^& vbCrLf ^& "Please manually extract:" ^& vbCrLf ^& "%TOOLCHAIN_ZIP%" ^& vbCrLf ^& vbCrLf ^& "To the following directory:" ^& vbCrLf ^& "%DX_DIR%\windows" ^& vbCrLf ^& vbCrLf ^& "Then run tools\build.bat again.", vbOKOnly, "papermario-dx" > "%TEMP%\dx-notar.vbs"
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

    :: Record the content hash so we can detect updates
    echo %HASH%> "%DX_DIR%\windows-hash"
)
