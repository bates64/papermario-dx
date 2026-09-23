# Builds a downloadable, self-contained toolchain for the current system
# (one of x86_64-linux, aarch64-linux, x86_64-darwin, aarch64-darwin),
# analogous to tools/windows for Windows.
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
  mipsGdb,
  starRodJar,
}:

let
  isDarwin = pkgs.stdenv.isDarwin;
  system = pkgs.stdenv.hostPlatform.system;

  platformTag = {
    "x86_64-linux" = "linux-x86_64";
    "aarch64-linux" = "linux-aarch64";
    "x86_64-darwin" = "macos-x86_64";
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
  sccache-native = pkgs.callPackage ../sccache.nix { };
  evt-validate-native = pkgs.callPackage ../evt_validate.nix { };
  python-packages = import ./python.nix { inherit pkgs; };
  jre = import ./jre.nix { inherit pkgs; };

  # MIPS glibc headers, borrowed from the reference native cross-compiler for
  # the same target (this build only compiles `all-gcc`, not target libs).
  mipsGlibcDev = mipsCrossGcc.libc.dev;

  closureRoots = [
    mips-binutils
    mips-gcc
    mipsGdb
    n64crc
    pigment64-native
    crunch64-native
    pkgs.ninja
    sccache-native
    evt-validate-native
    pkgs.python3
    jre
    starRodJar
    pkgs.llvmPackages.clang-unwrapped
  ];
  closure = pkgs.closureInfo { rootPaths = closureRoots; };

  archive = pkgs.runCommand "papermario-dx-${platformTag}-toolchain"
    {
      nativeBuildInputs = [ pkgs.gnutar pkgs.xz pkgs.coreutils ]
        ++ pkgs.lib.optional (!isDarwin) pkgs.pkgsStatic.patchelf;
    }
    ''
      dir=papermario-dx-${platformTag}
      mkdir -p $dir/store $dir/bin $dir/lib

      # Copy the whole runtime closure, preserving each package's own layout.
      # Symlinks are kept, so a library isn't stored once per name it goes by
      # (libLLVM alone has three), and any that point into another store path
      # are redirected to its copy here.
      while read -r p; do
        cp -r --no-preserve=ownership "$p" "$dir/store/$(basename "$p")"
      done < ${closure}/store-paths
      # The copies are as read-only as the originals; the steps below edit them.
      chmod -R u+w "$dir/store"
      find "$dir/store" -type l | while read -r l; do
        target=$(readlink "$l")
        case "$target" in
          /nix/store/*)
            ln -sfn "$(realpath -s --relative-to="$(dirname "$l")" "$dir/store/''${target#/nix/store/}")" "$l"
            ;;
        esac
      done

      # Static libraries are only used for linking, and the only thing this
      # toolchain links is MIPS code, so drop the host ones (about 1 GB, most
      # of it LLVM's).
      find "$dir/store" -name '*.a' -not -path "$dir/store/*mips*" -delete

      # Flatten every shared library into lib/ as relative symlinks, so every
      # binary can share a single RPATH pointing at lib/. The closure also
      # holds libraries built for the MIPS target, some with the same name as
      # a host library (such as libc.so.6 and libstdc++.so.6); skip them. They
      # are big-endian ELF (EI_DATA = 2), and every supported host is
      # little-endian. Sorted, so which copy a name ends up pointing at
      # doesn't depend on the order the filesystem lists them in.
      find "$dir/store" \( -type f -o -type l \) \( -name '*.so' -o -name '*.so.*' -o -name '*.dylib' \) | sort | while read -r f; do
        [ "$(od -An -tx1 -j5 -N1 "$f" | tr -d ' ')" = "02" ] && continue
        ln -sf "$(realpath --relative-to="$dir/lib" "$f")" "$dir/lib/$(basename "$f")"
      done

      # bin/ symlinks for the tools users and ninja invoke directly.
      link_bin() {
        f=$(find "$dir/store" -mindepth 3 -maxdepth 3 -path '*/bin/'"$1" | head -n1)
        [ -n "$f" ] && ln -sf "$(realpath --relative-to="$dir/bin" "$f")" "$dir/bin/$1"
      }
      for tool in mips-linux-gnu-gcc mips-linux-gnu-g++ mips-linux-gnu-cpp mips-linux-gnu-ld mips-linux-gnu-as \
                  mips-linux-gnu-ar mips-linux-gnu-nm mips-linux-gnu-objcopy mips-linux-gnu-objdump \
                  mips-linux-gnu-ranlib mips-linux-gnu-readelf mips-linux-gnu-strip \
                  ninja sccache evt_validate pigment64 crunch64 n64crc python3 java clang-format clang-tidy clangd; do
        link_bin "$tool"
      done

      # The debugger an editor attaches to ares' GDB stub with. Its package is
      # named for the bare-metal triple rather than the compiler's, so link it
      # under a stable name instead of deriving one.
      gdb=$(find "$dir/store/$(basename ${mipsGdb})/bin" -name '*gdb' | head -n1)
      if [ -z "$gdb" ]; then
        echo "tools/unix: no gdb binary in ${mipsGdb}" >&2
        exit 1
      fi
      ln -sf "$(realpath --relative-to="$dir/bin" "$gdb")" "$dir/bin/gdb"

      # Star Rod: bundled jar + a wrapper script, launched via bin/java.
      mkdir -p $dir/share/java
      cp -L "$(find "$dir/store" -path '*/share/java/StarRod.jar' | head -n1)" $dir/share/java/StarRod.jar
      cat > $dir/bin/star-rod << 'STARROD_EOF'
      #!/bin/sh
      DIR="$(cd "$(dirname "$0")/.." && pwd)"
      exec "$DIR/bin/java" -jar "$DIR/share/java/StarRod.jar" "$@"
      STARROD_EOF
      chmod +x $dir/bin/star-rod

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

      # Everything copied above came from read-only /nix/store paths. Make the
      # whole tree writable, without disturbing the executable bits that
      # --no-preserve=mode would otherwise reset: activation rewrites the
      # binaries in place, and a read-only directory anywhere in here would
      # also stop download_toolchain.sh removing the toolchain to update it.
      chmod -R u+w "$dir"

      # sccache identifies the compiler and the assembler it runs by their
      # file contents, but activate.sh writes the install path into every
      # binary, so no two installs would share a cache entry. Put a wrapper
      # script in front of each instead: it's byte-identical wherever the
      # toolchain is installed, and names its target's store path, so it
      # still changes whenever the target does.
      wrap() {
        target=$(realpath -s --relative-to="$(dirname "$dir/$1")" "$dir/$2")
        rm -f "$dir/$1"
        printf '#!/bin/sh\nexec "$(dirname "$0")/%s" "$@"\n' "$target" > "$dir/$1"
        chmod +x "$dir/$1"
      }
      gccStore=store/$(basename ${mips-gcc})
      binutilsStore=store/$(basename ${mips-binutils})
      wrap bin/mips-linux-gnu-gcc $gccStore/bin/mips-linux-gnu-gcc
      wrap bin/mips-linux-gnu-g++ $gccStore/bin/mips-linux-gnu-g++
      wrap $gccStore/mips-linux-gnu/bin/as $binutilsStore/bin/mips-linux-gnu-as

      ${pkgs.lib.optionalString (!isDarwin) ''
        cp ${pkgs.pkgsStatic.patchelf}/bin/patchelf $dir/bin/.patchelf

        # Find the files activate.sh has to patch now, rather than having it
        # probe each of the toolchain's thousands of files one at a time.
        # Only host binaries need patching, and every supported host is
        # little-endian (EI_DATA = 1), unlike the MIPS target's libraries.
        # Static-PIE binaries (like sccache) have a dynamic section but no
        # interpreter or DT_NEEDED, and setting an RPATH on them corrupts them.
        (
          cd $dir
          touch .activate-interp .activate-rpath
          find store python -type f | sort | while read -r f; do
            case "$(od -An -tx1 -N6 "$f" | tr -d ' \n')" in
              7f454c46??01) ;;
              *) continue ;;
            esac
            if patchelf --print-interpreter "$f" >/dev/null 2>&1; then
              echo "$f" >> .activate-interp
            elif [ -n "$(patchelf --print-needed "$f" 2>/dev/null)" ]; then
              echo "$f" >> .activate-rpath
            fi
          done
        )
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
        cd "$DIR"
        tr '\n' '\0' < .activate-interp | xargs -0 "$PATCHELF" --set-rpath "$DIR/lib" --set-interpreter "$DIR/lib/${interpName}"
        tr '\n' '\0' < .activate-rpath | xargs -0 "$PATCHELF" --set-rpath "$DIR/lib"
      ''}
      ACTIVATE_EOF2
      chmod +x $dir/activate.sh

      mkdir -p $out
      # xz rather than zip: it's about half the size, and any tar on macOS or
      # Linux can extract it. Fixed file order, times, and owners keep the
      # archive the same when its contents are, so the publish step stores
      # an unchanged toolchain only once.
      tar --sort=name --mtime=@0 --owner=0 --group=0 --numeric-owner -c $dir \
        | xz -9 -T0 > $out/papermario-dx-${platformTag}.tar.xz
    '';
in
archive
