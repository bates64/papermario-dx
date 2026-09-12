# Builds a downloadable, self-contained toolchain for the current system
# (one of x86_64-linux, aarch64-linux, aarch64-darwin - x86_64-darwin is
# unsupported since nixpkgs-unstable dropped it), analogous to tools/windows
# for Windows.
#
# Unlike the Windows toolchain (a Canadian cross that produces binaries with
# no /nix/store dependency by construction), these binaries are built
# natively and link against libraries in /nix/store, which won't exist on a
# plain (non-Nix) machine. To make them runnable there, this derivation:
#
#   1. Copies the full runtime closure of every tool into store/, preserving
#      each package's own internal layout (so e.g. GCC's relative lookup of
#      cc1/libexec keeps working unmodified).
#   2. Symlinks every shared library found anywhere in that closure into a
#      single flat lib/ directory.
#   3. Ships a generated activate.sh that, given the toolchain's own
#      (now-known) absolute install path, rewrites every binary's RPATH (and
#      on Linux, the ELF interpreter) to point at that lib/ directory -
#      patchelf on Linux (a static copy is bundled, since the target machine
#      won't have one), install_name_tool + ad-hoc codesign on macOS (via the
#      system copies from Xcode Command Line Tools).
{
  pkgs,
  nixpkgs-binutils-2_39,
  mipsCrossGcc,
}:

let
  isDarwin = pkgs.stdenv.isDarwin;
  system = pkgs.stdenv.hostPlatform.system;

  platformTag = {
    "x86_64-linux" = "linux-x86_64";
    "aarch64-linux" = "linux-aarch64";
    "aarch64-darwin" = "macos-aarch64";
  }.${system} or (throw "tools/unix: unsupported system ${system}");

  # ELF interpreter names, needed to fix up PT_INTERP after relocation
  # (only meaningful on Linux; unused on Darwin).
  interpName = {
    "x86_64-linux" = "ld-linux-x86-64.so.2";
    "aarch64-linux" = "ld-linux-aarch64.so.1";
  }.${system} or null;

  # Extract source, patches, and version from the pinned binutils 2.39 nixpkgs commit.
  binutilsPkg = (import nixpkgs-binutils-2_39 { system = "x86_64-linux"; }).binutils-unwrapped;
  # Extract source, patches, and version from the nixpkgs GCC derivation.
  gccPkg = pkgs.gcc.cc;

  mips-binutils = import ./binutils.nix {
    stdenv = pkgs.stdenv;
    buildCC = pkgs.stdenv.cc;
    binutilsSrc = binutilsPkg.src;
    binutilsPatches = binutilsPkg.patches;
    binutilsVersion = binutilsPkg.version;
    inherit (pkgs) texinfo bison flex zlib;
  };

  mips-gcc = import ./gcc.nix {
    stdenv = pkgs.stdenv;
    buildCC = pkgs.stdenv.cc;
    gccSrc = gccPkg.src;
    gccPatches = gccPkg.patches;
    gccVersion = gccPkg.version;
    inherit mips-binutils mipsCrossGcc;
    gmpSrc = pkgs.gmp.src;
    mpfrSrc = pkgs.mpfr.src;
    mpcSrc = pkgs.libmpc.src;
    islSrc = pkgs.isl.src;
    inherit (pkgs) texinfo bison flex zlib;
  };

  n64crc = import ./n64crc.nix { stdenv = pkgs.stdenv; };
  pigment64-native = pkgs.callPackage ../pigment64.nix { };
  crunch64-native = pkgs.callPackage ../crunch64.nix { };
  python-packages = import ./python.nix { inherit pkgs; };

  # MIPS glibc headers, borrowed from the reference native cross-compiler for
  # the same target (this build only compiles `all-gcc`, not target libs).
  mipsGlibcDev = mipsCrossGcc.libc.dev;

  closureRoots = [
    mips-binutils
    mips-gcc
    n64crc
    pigment64-native
    crunch64-native
    pkgs.ninja
    pkgs.ccache
    pkgs.python3
  ];
  closure = pkgs.closureInfo { rootPaths = closureRoots; };

  zip = pkgs.runCommand "papermario-dx-${platformTag}-toolchain"
    {
      nativeBuildInputs = [ pkgs.zip pkgs.unzip pkgs.coreutils ]
        ++ pkgs.lib.optional (!isDarwin) pkgs.pkgsStatic.patchelf;
    }
    ''
      dir=papermario-dx-${platformTag}
      mkdir -p $dir/store $dir/bin $dir/lib

      # Copy the whole runtime closure, preserving each package's own layout.
      while read -r p; do
        cp -rL --no-preserve=ownership "$p" "$dir/store/$(basename "$p")"
      done < ${closure}/store-paths
      # /nix/store paths are read-only; make our copies writable for
      # patchelf/install_name_tool later, without disturbing the executable
      # bits that --no-preserve=mode would otherwise reset.
      chmod -R u+w "$dir/store"

      # Flatten every shared library into lib/ as relative symlinks, so every
      # binary can share a single RPATH pointing at lib/.
      find "$dir/store" -type f \( -name '*.so' -o -name '*.so.*' -o -name '*.dylib' \) | while read -r f; do
        ln -sf "$(realpath --relative-to="$dir/lib" "$f")" "$dir/lib/$(basename "$f")"
      done

      # bin/ symlinks for the tools users and ninja invoke directly.
      link_bin() {
        f=$(find "$dir/store" -mindepth 3 -maxdepth 3 -path '*/bin/'"$1" | head -n1)
        [ -n "$f" ] && ln -sf "$(realpath --relative-to="$dir/bin" "$f")" "$dir/bin/$1"
      }
      for tool in mips-linux-gnu-gcc mips-linux-gnu-g++ mips-linux-gnu-ld mips-linux-gnu-as \
                  mips-linux-gnu-ar mips-linux-gnu-nm mips-linux-gnu-objcopy mips-linux-gnu-objdump \
                  mips-linux-gnu-ranlib mips-linux-gnu-strip \
                  ninja ccache pigment64 crunch64 n64crc python3; do
        link_bin "$tool"
      done

      # MIPS glibc headers (string.h, stdio.h, etc.) in the sysroot.
      mkdir -p $dir/mips-linux-gnu/sys-include
      cp -rL ${mipsGlibcDev}/include/* $dir/mips-linux-gnu/sys-include/

      # libstdc++ headers, borrowed from the reference cross-compiler for the
      # same target. GCC derives its C++ search path from the prefix it is run
      # from, which is its own copy under store/, so they belong in there
      # rather than alongside it.
      gccPrefix=$dir/store/$(basename ${mips-gcc})
      gccVersion=$(ls ${mips-gcc}/lib/gcc/mips-linux-gnu)
      mkdir -p $gccPrefix/mips-linux-gnu/include/c++/$gccVersion
      cp -rL ${mipsCrossGcc.cc}/include/c++/*/* $gccPrefix/mips-linux-gnu/include/c++/$gccVersion/

      # Python packages (requirements.txt + requirements_extra.txt), found via
      # PYTHONPATH rather than baked into the interpreter's own store copy.
      mkdir -p $dir/python
      cp -rL --no-preserve=ownership ${python-packages}/* $dir/python/
      chmod -R u+w $dir/python

      ${pkgs.lib.optionalString (!isDarwin) ''
        cp ${pkgs.pkgsStatic.patchelf}/bin/patchelf $dir/bin/.patchelf
      ''}

      cat > $dir/activate.sh << 'ACTIVATE_EOF'
      #!/bin/sh
      # Relocates the toolchain to run from its current install path. Must be
      # run once after extracting, with this directory's own absolute path as
      # $1 (download_toolchain.sh does this automatically).
      set -e
      DIR="$1"
      ACTIVATE_EOF
      cat >> $dir/activate.sh << 'ACTIVATE_EOF2'
      ${if isDarwin then ''
        find "$DIR/store" -type f | while read -r f; do
          if file "$f" 2>/dev/null | grep -q 'Mach-O'; then
            # Mach-O load commands embed the full dependency path (unlike
            # ELF's bare DT_NEEDED names), so an rpath alone doesn't help -
            # each /nix/store reference has to be rewritten explicitly.
            otool -L "$f" 2>/dev/null | tail -n +2 | awk '{print $1}' | while read -r dep; do
              case "$dep" in
                /nix/store/*)
                  install_name_tool -change "$dep" "$DIR/lib/$(basename "$dep")" "$f" >/dev/null 2>&1 || true
                  ;;
              esac
            done
            id=$(otool -D "$f" 2>/dev/null | tail -n +2)
            case "$id" in
              /nix/store/*)
                install_name_tool -id "$DIR/lib/$(basename "$id")" "$f" >/dev/null 2>&1 || true
                ;;
            esac
            codesign --force --sign - "$f" >/dev/null 2>&1 || true
          fi
        done
      '' else ''
        PATCHELF="$DIR/bin/.patchelf"
        find "$DIR/store" -type f | while read -r f; do
          if "$PATCHELF" --print-rpath "$f" >/dev/null 2>&1; then
            "$PATCHELF" --set-rpath "$DIR/lib" "$f" || true
            if "$PATCHELF" --print-interpreter "$f" >/dev/null 2>&1; then
              "$PATCHELF" --set-interpreter "$DIR/lib/${interpName}" "$f" || true
            fi
          fi
        done
      ''}
      ACTIVATE_EOF2
      chmod +x $dir/activate.sh

      mkdir -p $out
      cd $dir/..
      zip -yr $out/papermario-dx-${platformTag}.zip $dir
    '';
in
zip
