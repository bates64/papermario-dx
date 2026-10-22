# Builds a downloadable, self-contained toolchain for macOS, cross-compiled on
# Linux, so the one Linux machine that publishes dx's toolchains can build every
# platform's. The binaries link only against the system libraries macOS ships,
# so nothing in the archive needs relocating. The layout is the same as the
# Linux toolchains'.
{
  pkgs,
  arch, # "aarch64" or "x86_64"
  nixpkgs-binutils-2_39,
  mipsCrossGcc,
  starRodJar,
  llvmVersion,
  pythonDeps,
}:

let
  platformTag = "macos-${arch}";
  hostTriple = "${arch}-apple-darwin";
  system = "${arch}-darwin";

  sdk = pkgs.callPackage ./sdk.nix { };
  cross = pkgs.callPackage ./cross.nix { inherit sdk arch; };

  # Extract source, patches, and version from the pinned binutils 2.39 nixpkgs commit.
  binutilsPkg = (import nixpkgs-binutils-2_39 { system = "x86_64-linux"; }).binutils-unwrapped;
  # Extract source, patches, and version from the nixpkgs GCC derivation.
  gccPkg = pkgs.gcc.cc;

  mips-binutils = pkgs.callPackage ./binutils.nix {
    inherit cross hostTriple;
    buildCC = pkgs.stdenv.cc;
    binutilsSrc = binutilsPkg.src;
    binutilsPatches = binutilsPkg.patches;
    binutilsVersion = binutilsPkg.version;
  };

  mips-gcc = pkgs.callPackage ./gcc.nix {
    inherit cross hostTriple mips-binutils mipsCrossGcc;
    buildCC = pkgs.stdenv.cc;
    gccSrc = gccPkg.src;
    gccPatches = gccPkg.patches;
    gccVersion = gccPkg.version;
    gmpSrc = pkgs.gmp.src;
    mpfrSrc = pkgs.mpfr.src;
    mpcSrc = pkgs.libmpc.src;
    islSrc = pkgs.isl.src;
  };

  crossRust = pkgs.callPackage ./rust.nix { inherit cross arch; };
  rustPackages = { rustPlatform = crossRust; };
  pigment64 = pkgs.callPackage ../pigment64.nix rustPackages;
  crunch64 = pkgs.callPackage ../crunch64.nix rustPackages;
  evt-validate = pkgs.callPackage ../evt_validate.nix rustPackages;

  mips-gdb = pkgs.callPackage ./gdb.nix {
    inherit cross hostTriple arch;
    buildCC = pkgs.stdenv.cc;
    gdbSrc = pkgs.gdb.src;
    gdbVersion = pkgs.gdb.version;
    gmpSrc = pkgs.gmp.src;
    mpfrSrc = pkgs.mpfr.src;
  };

  n64crc = pkgs.stdenvNoCC.mkDerivation {
    pname = "n64crc-macos";
    version = "0";
    dontUnpack = true;
    dontFixup = true;
    buildPhase = ''
      ${cross}/bin/cc -O2 -o n64crc ${../build/rom/n64crc.c}
    '';
    installPhase = ''
      mkdir -p $out/bin
      cp n64crc $out/bin/
    '';
  };

  ninja = pkgs.stdenvNoCC.mkDerivation {
    pname = "ninja-macos";
    version = "1.12.1";
    src = pkgs.fetchurl {
      url = "https://github.com/ninja-build/ninja/releases/download/v1.12.1/ninja-mac.zip";
      hash = "sha256-iaKHREtbPpj4ipRa+lDOk3uP/R3MWcVVrZsbr4VSmMk=";
    };
    sourceRoot = ".";
    nativeBuildInputs = [ pkgs.unzip ];
    dontFixup = true;
    installPhase = ''
      mkdir -p $out/bin
      cp ninja $out/bin/
    '';
  };

  sccache = pkgs.callPackage ../sccache.nix { inherit system; };
  llvm = pkgs.callPackage ../llvm.nix { version = llvmVersion; inherit system; };
  jre = import ../unix/jre.nix { inherit pkgs system; };
  python = pkgs.callPackage ./python.nix { inherit pythonDeps arch; };

  # MIPS glibc headers from the native cross-compiler, needed for string.h etc.
  mipsGlibcDev = mipsCrossGcc.libc.dev;

  archive = pkgs.runCommand "papermario-dx-${platformTag}-toolchain"
    {
      nativeBuildInputs = [ pkgs.gnutar pkgs.xz pkgs.coreutils cross ];
    }
    ''
      dir=papermario-dx-${platformTag}
      mkdir -p $dir/bin $dir/share/java

      # MIPS cross-compiler: the drivers in bin/, the compiler proper in
      # libexec/, and its built-in headers (stddef.h, stdarg.h, etc.) in lib/.
      cp -rL ${mips-binutils}/bin/* ${mips-gcc}/bin/* $dir/bin/
      cp -rL ${mips-gcc}/libexec $dir/
      cp -rL ${mips-gcc}/lib $dir/
      chmod -R u+w $dir
      # Binutils in GCC's standard search path (<prefix>/mips-linux-gnu/bin/)
      mkdir -p $dir/mips-linux-gnu/bin
      for tool in ${mips-binutils}/bin/mips-linux-gnu-*; do
        name=$(basename "$tool" | sed 's/^mips-linux-gnu-//')
        cp -L "$tool" $dir/mips-linux-gnu/bin/$name
      done
      # MIPS glibc headers (string.h, stdio.h, etc.) in the sysroot
      mkdir -p $dir/mips-linux-gnu/sys-include
      cp -rL ${mipsGlibcDev}/include/* $dir/mips-linux-gnu/sys-include/
      # libstdc++ headers, which this GCC can't build, from the native
      # cross-compiler for the same target. They go in GCC's C++ search path,
      # <prefix>/mips-linux-gnu/include/c++/<version>/, where the version is
      # GCC's own rather than the nixpkgs package version.
      gccVersion=$(ls ${mips-gcc}/lib/gcc/mips-linux-gnu)
      mkdir -p $dir/mips-linux-gnu/include/c++/$gccVersion
      cp -rL ${mipsCrossGcc.cc}/include/c++/*/* $dir/mips-linux-gnu/include/c++/$gccVersion/
      chmod -R u+w $dir

      # gdb
      cp -L ${mips-gdb}/bin/mips-linux-gnu-gdb $dir/bin/gdb

      # Tools the build runs
      cp ${pigment64}/bin/pigment64 ${crunch64}/bin/crunch64 ${evt-validate}/bin/evt_validate \
        ${n64crc}/bin/n64crc ${ninja}/bin/ninja ${sccache}/bin/sccache $dir/bin/

      # clangd, clang-tidy, and clang-format, which find clang's built-in
      # headers in ../lib/clang/ relative to themselves
      cp ${llvm}/bin/* $dir/bin/
      cp -r ${llvm}/lib/clang $dir/lib/

      # Python, and its packages where the build puts them on PYTHONPATH
      mkdir -p $dir/python-runtime
      tar -xzf ${python.runtime} -C $dir/python-runtime --strip-components=1
      ln -s ../python-runtime/bin/python3 $dir/bin/python3
      cp -r ${python.packages} $dir/python
      chmod -R u+w $dir

      # Star Rod: bundled JRE and jar, launched via a wrapper script. The
      # jar's entry point only checks for Java 17 and then starts Star Rod in
      # a second JVM, so the wrapper starts Star Rod directly.
      mkdir -p $dir/jre
      cp -rL ${jre}/* $dir/jre/
      chmod -R u+w $dir
      ln -s ../jre/bin/java $dir/bin/java
      cp -L ${starRodJar}/share/java/StarRod.jar $dir/share/java/StarRod.jar
      cat > $dir/bin/star-rod << 'STARROD_EOF'
      #!/bin/sh
      DIR="$(cd "$(dirname "$0")/.." && pwd)"
      exec "$DIR/bin/java" -cp "$DIR/share/java/StarRod.jar" app.StarRodMain "$@"
      STARROD_EOF
      chmod +x $dir/bin/star-rod

      # Nothing here needs relocating, but the download script runs this.
      printf '#!/bin/sh\n' > $dir/activate.sh
      chmod +x $dir/activate.sh

      # Every binary must be for this architecture and load nothing from
      # outside macOS, since there is no /nix/store on the machine that runs it.
      find $dir -type f | sort | while read -r f; do
        [ "$(head -c 4 "$f" | od -An -tx1 | tr -d ' ')" = "cffaedfe" ] || continue
        if ! otool -hv "$f" | grep -q ${if arch == "aarch64" then "ARM64" else "X86_64"}; then
          echo "$f is not built for ${arch}" >&2; exit 1
        fi
        if otool -L "$f" | tail -n +2 | grep -q /nix/store; then
          echo "$f loads a library from /nix/store:" >&2; otool -L "$f" >&2; exit 1
        fi
      done

      mkdir -p $out
      # Fixed file order, times, and owners keep the archive the same when its
      # contents are, so the publish step stores an unchanged toolchain once.
      # Each -9 thread takes about 674 MiB, so two threads keep it inside a CI
      # container's memory. The archive is the same however many threads
      # compress it.
      tar --sort=name --mtime=@0 --owner=0 --group=0 --numeric-owner -c $dir \
        | xz -9 -T2 > $out/papermario-dx-${platformTag}.tar.xz
    '';
in
archive
// {
  passthru = {
    inherit mips-binutils mips-gcc mips-gdb cross sdk pigment64 crunch64 evt-validate n64crc ninja sccache llvm jre python;
  };
}
