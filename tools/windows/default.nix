{
  pkgs,
  nixpkgs-binutils-2_39,
  mipsCrossGcc,
  baseRom,
  src,
}:

let
  mingw = pkgs.pkgsCross.mingwW64;
  mingwStdenv = mingw.stdenv;

  # Extract source, patches, and version from the nixpkgs binutils derivation.
  binutilsPkg = (import nixpkgs-binutils-2_39 { system = "x86_64-linux"; }).binutils-unwrapped;

  # Extract source, patches, and version from the nixpkgs GCC derivation.
  gccPkg = pkgs.gcc.cc;

  mips-binutils-windows = import ./binutils.nix {
    stdenv = mingwStdenv;
    buildCC = pkgs.stdenv.cc;
    binutilsSrc = binutilsPkg.src;
    binutilsPatches = binutilsPkg.patches;
    binutilsVersion = binutilsPkg.version;
    inherit (pkgs) texinfo bison flex;
    zlib = mingw.zlib;
  };

  mips-gcc-windows = import ./gcc.nix {
    stdenv = mingwStdenv;
    buildCC = pkgs.stdenv.cc;
    gccSrc = gccPkg.src;
    gccPatches = gccPkg.patches;
    gccVersion = gccPkg.version;
    inherit mips-binutils-windows;
    gmpSrc = pkgs.gmp.src;
    mpfrSrc = pkgs.mpfr.src;
    mpcSrc = pkgs.libmpc.src;
    islSrc = pkgs.isl.src;
    inherit mipsCrossGcc;
    inherit (pkgs) texinfo bison flex;
    zlib = mingw.zlib;
  };

  mips-toolchain = pkgs.symlinkJoin {
    name = "mips-toolchain-windows";
    paths = [ mips-binutils-windows mips-gcc-windows ];
  };

  python-windows = pkgs.callPackage ./python.nix {};
  ninja-windows = pkgs.callPackage ./ninja.nix {};
  ccache-windows = pkgs.callPackage ./ccache.nix {};
  n64crc-windows = import ./n64crc.nix { stdenv = mingwStdenv; };
  busybox-windows = pkgs.callPackage ./busybox.nix {};

  pigment64-windows = mingw.callPackage ../pigment64.nix {};
  crunch64-windows = mingw.callPackage ../crunch64.nix {};

  # MIPS glibc headers from the native cross-compiler, needed for string.h etc.
  mipsGlibcDev = mipsCrossGcc.libc.dev;

  requirements = ../../requirements.txt;

  # Download all Python build dependencies for offline installation (Linux, used by wineRom).
  pythonDeps = pkgs.stdenvNoCC.mkDerivation {
    name = "papermario-python-deps";
    outputHashMode = "recursive";
    outputHashAlgo = "sha256";
    outputHash = "sha256-ifJYeWSK11nY8ATT0ZD/XvhpFAetiwNMPsrW+STjJRg=";
    nativeBuildInputs = [ pkgs.python3 pkgs.python3Packages.pip pkgs.cacert ];
    buildCommand = ''
      export SSL_CERT_FILE=${pkgs.cacert}/etc/ssl/certs/ca-bundle.crt
      pip download -r ${requirements} setuptools wheel -d $out
    '';
  };

  # Download Windows-compatible wheels for pre-installation into the toolchain.
  # Some packages (e.g. ninja_syntax) only have sdists on PyPI, so we can't use
  # --platform win_amd64 --only-binary=:all: for everything. Instead we build
  # all wheels first (which creates universal wheels from sdists), then replace
  # any Linux-specific wheels with their Windows counterparts.
  pythonDepsWindows = pkgs.stdenvNoCC.mkDerivation {
    name = "papermario-python-deps-windows";
    outputHashMode = "recursive";
    outputHashAlgo = "sha256";
    outputHash = "sha256-zrMEwffdltfh51U5xF4DI+mJpMnNwA7YMV2b19Ya+CM=";
    nativeBuildInputs = [
      pkgs.python3
      pkgs.python3Packages.pip
      pkgs.python3Packages.setuptools
      pkgs.python3Packages.wheel
      pkgs.cacert
    ];
    buildCommand = ''
      export SSL_CERT_FILE=${pkgs.cacert}/etc/ssl/certs/ca-bundle.crt
      export HOME=$(mktemp -d)
      mkdir -p $out

      # Build wheels for all packages including transitive dependencies.
      # Pure Python sdist-only packages (e.g. ninja_syntax) become py3-none-any wheels.
      pip wheel -r ${requirements} setuptools -w /tmp/all-wheels --quiet

      for whl in /tmp/all-wheels/*.whl; do
        name=$(basename "$whl")
        if echo "$name" | grep -qE '(linux|manylinux|macosx)'; then
          # Platform-specific wheel: download Windows version instead
          pkg=$(echo "$name" | sed 's/-[0-9].*//')
          pip download \
            --platform win_amd64 --python-version 3.13 --implementation cp --abi cp313 \
            --only-binary=:all: --no-deps \
            "$pkg" -d $out --quiet
        else
          cp "$whl" $out/
        fi
      done
    '';
  };

  # Build the ROM using wine-wrapped Windows tools with native Linux
  # Python and ninja. Produces the ROM as output for comparison.
  wineRom = pkgs.runCommand "papermario-wine-rom" {
    nativeBuildInputs = [
      pkgs.wineWow64Packages.stable
      pkgs.python3
      pkgs.python3Packages.pip
      pkgs.python3Packages.virtualenv
      pkgs.ninja
      pkgs.gcc
      pkgs.git
      pkgs.libyaml
      pkgs.iconv
      pkgs.unzip
    ];
    HOME = "/build/home";
    WINEPREFIX = "/build/wine";
    WINEDEBUG = "-all";
    TERM = "dumb";
  } ''
    mkdir -p $HOME $WINEPREFIX

    # Unpack the toolchain zip
    unzip ${zip}/papermario-dx-windows.zip
    toolchain=$(pwd)/papermario-dx-windows

    # Create wine wrapper scripts for each Windows .exe tool.
    # ninja invokes these as regular commands; the wrappers transparently
    # call wine to run the actual Windows binaries.
    mkdir -p wrappers
    for exe in $toolchain/bin/mips-linux-gnu-*.exe \
               $toolchain/bin/pigment64.exe \
               $toolchain/bin/crunch64.exe; do
      name=$(basename "$exe" .exe)
      cat > wrappers/$name << WRAPPER
    #!/bin/sh
    exec wine "$exe" "\$@"
    WRAPPER
      chmod +x wrappers/$name
    done

    export PATH=$(pwd)/wrappers:$PATH

    # Set up the source tree (make writable + scripts executable)
    cp -r --no-preserve=mode ${src} build
    chmod -R u+w build
    find build -name '*.py' -exec chmod +x {} +
    cd build
    git init --quiet
    cp ${baseRom} ver/us/baserom.z64

    # Patch shebangs so scripts can find python3 in the nix sandbox
    patchShebangs --build tools/

    # Install Python packages from cached wheels
    virtualenv venv --quiet
    source venv/bin/activate
    pip install --no-index --find-links=${pythonDeps} -r requirements.txt --quiet

    # The ld wrapper uses wine; set PAPERMARIO_LD to use it
    export PAPERMARIO_LD="mips-linux-gnu-ld"

    # Configure
    python3 tools/build/configure.py --no-ccache

    # Build
    ninja

    mkdir -p $out
    cp ver/us/build/papermario.z64 $out/
  '';

  zip = pkgs.runCommand "papermario-dx-windows-toolchain" {
    nativeBuildInputs = [ pkgs.zip pkgs.unzip ];
  } ''
    dir=papermario-dx-windows
    mkdir -p $dir/bin $dir/python

    # MIPS cross-compiler
    cp -rL ${mips-toolchain}/bin/* $dir/bin/
    cp -rL ${mips-toolchain}/libexec $dir/
    # GCC built-in headers (stddef.h, stdarg.h, etc.)
    cp -rL ${mips-gcc-windows}/lib $dir/
    # Binutils in GCC's standard search path (<prefix>/mips-linux-gnu/bin/)
    mkdir -p $dir/mips-linux-gnu/bin
    for tool in ${mips-binutils-windows}/bin/mips-linux-gnu-*.exe; do
      name=$(basename "$tool" | sed 's/^mips-linux-gnu-//')
      cp -L "$tool" $dir/mips-linux-gnu/bin/$name
    done
    # MIPS glibc headers (string.h, stdio.h, etc.) in the sysroot
    mkdir -p $dir/mips-linux-gnu/sys-include
    cp -rL ${mipsGlibcDev}/include/* $dir/mips-linux-gnu/sys-include/

    # Rust tools
    cp ${pigment64-windows}/bin/pigment64.exe $dir/bin/
    cp ${crunch64-windows}/bin/crunch64.exe $dir/bin/

    # busybox (Unix utilities: cp, etc.)
    cp ${busybox-windows}/bin/busybox.exe $dir/bin/
    cp ${busybox-windows}/bin/busybox.exe $dir/bin/cp.exe

    # ninja
    cp ${ninja-windows}/bin/ninja.exe $dir/bin/

    # ccache
    cp ${ccache-windows}/bin/ccache.exe $dir/bin/

    # n64crc (pre-built so Windows users don't need a host C compiler)
    cp ${n64crc-windows}/bin/n64crc.exe $dir/bin/

    # Embeddable Python with pre-installed packages
    cp -rL ${python-windows}/* $dir/python/
    rm -f $dir/python/get-pip.py
    mkdir -p $dir/python/Lib/site-packages
    for whl in ${pythonDepsWindows}/*.whl; do
      unzip -o -q "$whl" -d $dir/python/Lib/site-packages
    done

    cat > $dir/shell.bat << 'SHELL_EOF'
    @echo off
    set "TOOLCHAIN_DIR=%~dp0"
    set "PATH=%TOOLCHAIN_DIR%bin;%TOOLCHAIN_DIR%python;%PATH%"
    set "PYTHONUTF8=1"
    cmd /k echo papermario-dx development shell. Run 'python tools/build/configure.py' then 'ninja' to build.
    SHELL_EOF

    mkdir -p $out
    cd $dir/..
    zip -r $out/papermario-dx-windows.zip $dir
  '';

in
zip // {
  passthru = {
    inherit mips-toolchain python-windows ninja-windows ccache-windows n64crc-windows
            pigment64-windows crunch64-windows wineRom pythonDeps pythonDepsWindows;

    tests.wine = pkgs.runCommand "mips-toolchain-windows-test" {
      nativeBuildInputs = [ pkgs.wineWow64Packages.stable ];
      HOME = "/build/home";
      WINEPREFIX = "/build/wine";
      WINEDEBUG = "-all";
      TERM = "dumb";
    } ''
      mkdir -p $HOME $WINEPREFIX

      echo "=== gcc --version ==="
      wine ${mips-toolchain}/bin/mips-linux-gnu-gcc.exe --version

      echo "=== compile ==="
      echo 'int _start(void) { return 42; }' > test.c
      wine ${mips-toolchain}/bin/mips-linux-gnu-gcc.exe \
        -ffreestanding -c -march=vr4300 -mabi=32 -o test.o test.c
      file test.o | grep -q 'ELF 32-bit MSB relocatable, MIPS'

      echo "=== link ==="
      wine ${mips-toolchain}/bin/mips-linux-gnu-ld.exe \
        -e _start -o test.elf test.o
      file test.elf | grep -q 'ELF 32-bit MSB executable, MIPS'

      echo "=== pigment64 ==="
      wine ${pigment64-windows}/bin/pigment64.exe --version

      echo "=== crunch64 ==="
      wine ${crunch64-windows}/bin/crunch64.exe --version

      echo "=== ninja ==="
      wine ${ninja-windows}/bin/ninja.exe --version

      echo "=== n64crc ==="
      wine ${n64crc-windows}/bin/n64crc.exe || true

      echo "=== all tests passed ==="
      touch $out
    '';

    tests.build = pkgs.runCommand "windows-toolchain-build-test" {} ''
      test -f ${wineRom}/papermario.z64
      echo "=== ROM built successfully with Windows toolchain ==="
      touch $out
    '';
  };
}
