@echo off

set "S3_BASE=https://fsn1.your-objectstorage.com/starhaven/papermario-dx"

rem Ensure .dx directory exists
if not exist "%DX_DIR%" mkdir "%DX_DIR%"

set "HAVE_JJ=0"
if exist ".jj" (
    where jj >nul 2>nul
    if not errorlevel 1 set "HAVE_JJ=1"
)
set "HAVE_GIT=0"
where git >nul 2>nul
if not errorlevel 1 set "HAVE_GIT=1"

rem The index lists every commit with published toolchains, with each one's
rem hash, so finding the toolchain needs no fetch and works in shallow clones.
rem The last copy downloaded is kept for building offline.
set "INDEX=%DX_DIR%\index.txt"
curl -fsL -o "%INDEX%.new" "%S3_BASE%/index.txt" 2>nul
if not errorlevel 1 (
    move /y "%INDEX%.new" "%INDEX%" >nul
) else (
    del "%INDEX%.new" 2>nul
)
if not exist "%INDEX%" (
    echo Error: couldn't download the list of published toolchains from %S3_BASE%/index.txt.
    exit /b 1
)
set "PUBLISHED=%DX_DIR%\published.txt"
type nul > "%PUBLISHED%"
for /f "usebackq tokens=1-3" %%A in ("%INDEX%") do (
    if "%%A"=="commit" if "%%C"=="windows" echo %%B>>"%PUBLISHED%"
)

rem The newest published commit in the current history is where it meets dx's,
rem wherever it's branched from. A commit CI failed for isn't in the index, so
rem this finds the one before it.
set "HISTORY=%DX_DIR%\history.txt"
if "%HAVE_JJ%"=="1" (
    jj log --no-graph -r "::@" -T "commit_id ++ \"\n\"" > "%HISTORY%" 2>nul
) else if "%HAVE_GIT%"=="1" (
    git rev-list --topo-order HEAD > "%HISTORY%" 2>nul
) else (
    echo Error: this needs jj or git to find the toolchain version to download.
    echo Install jj ^(https://jj-vcs.github.io/jj/latest/install-and-setup/^) or git ^(https://git-scm.com/^).
    exit /b 1
)
rem Not /x: findstr only finds a line's end before a carriage return, which jj
rem and git don't write. Every line is a whole hash, so /b matches exactly.
set "COMMIT="
for /f "usebackq delims=" %%L in (`findstr /l /b /g:"%PUBLISHED%" "%HISTORY%" 2^>nul`) do (
    if not defined COMMIT set "COMMIT=%%L"
)
del "%HISTORY%" "%PUBLISHED%"

set "LATEST_RELEASE="
for /f "usebackq tokens=1-2" %%A in ("%INDEX%") do (
    if "%%A"=="release" set "LATEST_RELEASE=%%B"
)
set "UPDATING_URL=https://docs.starhaven.dev/papermario-dx/developing/without-diorama64/#updating-dx"
if not defined COMMIT (
    if exist "%TOOLCHAIN_DIR%\bin\ninja.exe" (
        echo Warning: no commit in this history has a published windows toolchain any more, so the installed one is used.
        echo To get a published toolchain again, merge dx's newest release, !LATEST_RELEASE!: !UPDATING_URL!
        exit /b 0
    )
    echo Error: no commit in this history has a published windows toolchain.
    echo dx keeps toolchains for every release, and for each commit on main until 90 days after the next one.
    echo Merge dx's newest release, !LATEST_RELEASE!, then build again: !UPDATING_URL!
    exit /b 1
)
set "HASH="
for /f "usebackq tokens=1-4" %%A in ("%INDEX%") do (
    if "%%A"=="commit" if "%%B"=="%COMMIT%" if "%%C"=="windows" set "HASH=%%D"
)

rem Check if toolchain needs downloading
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

    rem Clean up old toolchain. The sccache server outlives the build and holds
    rem its exe open, which would stop the directory from being deleted.
    if exist "%TOOLCHAIN_DIR%\bin\sccache.exe" "%TOOLCHAIN_DIR%\bin\sccache.exe" --stop-server >nul 2>nul
    if exist "%TOOLCHAIN_DIR%" rmdir /s /q "%TOOLCHAIN_DIR%"
    if exist "%TOOLCHAIN_DIR%" (
        echo Error: could not delete the old toolchain at %TOOLCHAIN_DIR%.
        echo Close any programs using it, such as a running build, and try again.
        exit /b 1
    )
    if exist "%TOOLCHAIN_ZIP%" del "%TOOLCHAIN_ZIP%"

    rem Download from S3
    set "URL=%S3_BASE%/toolchains/%HASH%.zip"
    curl -L -o "%TOOLCHAIN_ZIP%" "!URL!"
    if errorlevel 1 (
        echo Error: failed to download toolchain from !URL!
        exit /b 1
    )

    rem Extract
    echo Extracting toolchain...

    where unzip >nul 2>nul
    if not errorlevel 1 (
        rem mingw/git bash's tar command works differently to windows' builtin one so we're using unzip instead
        unzip -qo "%TOOLCHAIN_ZIP%" -d "%DX_DIR%"
    ) else (
        rem Windows' own tar, named in full: a tar from MSYS2, Cygwin, or Git for
        rem Windows earlier on PATH reads the drive letter in a path as a host.
        if not exist "%SystemRoot%\System32\tar.exe" (
            echo msgbox "tar is not available on this system (Windows 7)." ^& vbCrLf ^& vbCrLf ^& "Please manually extract:" ^& vbCrLf ^& "%TOOLCHAIN_ZIP%" ^& vbCrLf ^& vbCrLf ^& "To the following directory:" ^& vbCrLf ^& "%DX_DIR%\windows" ^& vbCrLf ^& vbCrLf ^& "Then run tools\build.bat again.", vbOKOnly, "papermario-dx" > "%TEMP%\dx-notar.vbs"
            wscript "%TEMP%\dx-notar.vbs"
            del "%TEMP%\dx-notar.vbs"
            exit /b 1
        )
        "%SystemRoot%\System32\tar.exe" -xf "%TOOLCHAIN_ZIP%" -C "%DX_DIR%"
        if errorlevel 1 (
            echo Error: failed to extract toolchain.
            exit /b 1
        )
    )
    rem Antivirus and sync tools briefly hold newly extracted files open, which
    rem makes renaming the directory fail, so retry for a few seconds. ping
    rem waits about a second and, unlike timeout, works without a console.
    for /l %%N in (1,1,10) do (
        if exist "%DX_DIR%\papermario-dx-windows" (
            ren "%DX_DIR%\papermario-dx-windows" windows 2>nul
            if exist "%DX_DIR%\papermario-dx-windows" ping -n 2 127.0.0.1 >nul
        )
    )
    if not exist "%TOOLCHAIN_DIR%" (
        echo Error: could not rename %DX_DIR%\papermario-dx-windows to windows.
        echo Another program, such as antivirus or OneDrive, might be using it. Try again in a minute.
        exit /b 1
    )
    del "%TOOLCHAIN_ZIP%"

    rem Record the content hash so we can detect updates
    echo %HASH%> "%DX_DIR%\windows-hash"
)
