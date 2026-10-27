{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

    # This commit uses binutils 2.39. We don't want binutils 2.40+ because of a performance regression in ld.
    nixpkgs-binutils-2_39.url = "github:NixOS/nixpkgs/55070e598e0e03d1d116c49b9eff322ef07c6ac6";

    flake-utils.url = "github:numtide/flake-utils";

    # Not `follows`-ed to our nixpkgs: star-rod builds its jar with its own
    # pinned nixpkgs/Gradle, since its offline dependency resolution
    # (gradle/verification-metadata.xml) is pinned to that exact Gradle version.
    star-rod.url = "git+https://tangled.org/starhaven.dev/star-rod?rev=488166b546f6731443505c057c5645b78b0396df";
  };
  nixConfig = {
    extra-substituters = [
      "https://papermario-dx.cachix.org"
      "https://papermario-dx-aarch64-darwin.cachix.org"
    ];
    extra-trusted-public-keys = [
      "papermario-dx.cachix.org-1:VTXILrqiajck9s5U2O3nDJH0pAI64GAJK41b2pt1JIk="
      "papermario-dx-aarch64-darwin.cachix.org-1:Tr3Kx63xvrTDCOELacSPjMC3Re0Nwg2WBRSprH3eMU0="
    ];
  };
  outputs = { self, nixpkgs, flake-utils, nixpkgs-binutils-2_39, star-rod }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        crossSystem = {
          config = "mips-linux-gnu"; # prefix expected by scripts in tools/
          system = "mips64-elf";
          gcc.arch = "vr4300";
          gcc.tune = "vr4300";
          gcc.abi = "32";
        };
        pkgs = import nixpkgs { inherit system; };
        pkgsCross = import nixpkgs { inherit system crossSystem; };
        baseRom = pkgs.requireFile {
          name = "papermario.us.z64";
          message = ''
            ==== MISSING BASE ROM =======================================================

            Paper Mario DX only supports the US version of Paper Mario. You need to
            provide a copy of the ROM in z64 format to build the project.

            Please rename your ROM to papermario.us.z64 and add it to the Nix store using
                nix-store --add-fixed sha256 papermario.us.z64
            then rerun nix-shell.

            If you don't have a ROM, dump it from your own cartridge.

            If you have a ROM but it is in n64 or v64 format, convert it to z64 first:
                https://hack64.net/tools/swapper.php

            If you added your ROM to the Nix store already, but it's still not working,
            your ROM must be incorrect. Make sure the version is US, the format is z64,
            and that it has not been modified.
          '';
          sha256 = "9ec6d2a5c2fca81ab86312328779fd042b5f3b920bf65df9f6b87b376883cb5b";
        };
        # Built for this system, so building any of the toolchains here never
        # needs another system's build or a cache that has it.
        starRodJar = star-rod.packages.${system}.jar;

        windowsToolchain = import ./tools/windows {
          inherit pkgs nixpkgs-binutils-2_39 baseRom llvmVersion starRodJar;
          mipsCrossGcc = pkgsCross.stdenv.cc;
          src = self;
        };
        pythonDeps = windowsToolchain.passthru.pythonDeps;

        macosToolchain = arch: import ./tools/macos {
          inherit pkgs arch nixpkgs-binutils-2_39 starRodJar llvmVersion pythonDeps;
          mipsCrossGcc = pkgsCross.stdenv.cc;
        };

        # Runs on this machine and debugs MIPS, so it comes from the cross
        # package set's build packages rather than pkgs.
        mipsGdb = pkgsCross.buildPackages.gdb;

        sccachePkg = pkgs.callPackage ./tools/sccache.nix { };
        evtValidatePkg = pkgs.callPackage ./tools/evt_validate.nix { };
        # The jar's entry point only checks for Java 17 and then starts
        # Star Rod in a second JVM, so this starts Star Rod directly.
        starRodPkg = pkgs.writeShellScriptBin "star-rod" ''
          exec ${pkgs.jdk17}/bin/java -cp ${starRodJar}/share/java/StarRod.jar app.StarRodMain "$@"
        '';

        unixToolchainWith = starRodJar: import ./tools/unix {
          inherit pkgs nixpkgs-binutils-2_39 mipsGdb starRodJar llvmTools;
          mipsCrossGcc = pkgsCross.stdenv.cc;
        };
        unixToolchain = unixToolchainWith starRodJar;
        # The toolchain's own compiler and binutils, so every build of the game uses the same ones.
        mipsTools = [ unixToolchain.passthru.mips-gcc unixToolchain.passthru.mips-binutils ];
        linuxRom = pkgs.runCommand "papermario-linux-rom" {
          nativeBuildInputs = mipsTools ++ [
            pkgs.python3
            pkgs.python3Packages.pip
            pkgs.python3Packages.virtualenv
            pkgs.ninja
            pkgs.gcc
            pkgs.git
            pkgs.libyaml
            pkgs.iconv
            (pkgs.callPackage ./tools/pigment64.nix {})
            (pkgs.callPackage ./tools/crunch64.nix {})
            evtValidatePkg
            starRodPkg
          ] ++ pkgs.lib.optional pkgs.stdenv.isLinux pkgs.flips;
        } ''
          cp -r --no-preserve=mode ${self} build
          chmod -R u+w build
          find build -name '*.py' -exec chmod +x {} +
          cd build
          git init --quiet
          cp ${baseRom} ver/us/baserom.z64
          patchShebangs --build tools/

          virtualenv venv --quiet
          source venv/bin/activate
          pip install --no-index --find-links=${pythonDeps} -r tools/requirements.txt --quiet

          python3 tools/build/configure.py --no-sccache
          ninja

          mkdir -p $out
          cp ver/us/build/papermario.z64 $out/
          ${pkgs.lib.optionalString pkgs.stdenv.isLinux
            "flips --create --bps ${baseRom} ver/us/build/papermario.z64 $out/papermario.bps"}
        '';

        # clangd only loads indexes built by the same version of clangd-indexer.
        llvmVersion = "21.1.8";
        llvmTools = pkgs.callPackage ./tools/llvm.nix { version = llvmVersion; };
        # clangd's release has these for x86_64 only; elsewhere they are built.
        clangdIndexer = pkgs.callPackage ./tools/clangd-indexer.nix { version = llvmVersion; };
        clangdIndexingTools =
          if system == "x86_64-linux"
          then pkgs.callPackage ./tools/clangd.nix { version = llvmVersion; archive = "clangd_indexing_tools"; }
          else clangdIndexer;
        clangdIndex = pkgs.runCommand "papermario-dx-clangd-index" {
          nativeBuildInputs = mipsTools ++ [
            pkgs.python3
            pkgs.python3Packages.pip
            pkgs.python3Packages.virtualenv
            pkgs.ninja
            pkgs.gcc
            pkgs.git
            pkgs.libyaml
            pkgs.iconv
            (pkgs.callPackage ./tools/pigment64.nix {})
            (pkgs.callPackage ./tools/crunch64.nix {})
            evtValidatePkg
            starRodPkg
            clangdIndexingTools
          ];
        } ''
          cp -r --no-preserve=mode ${self} build
          chmod -R u+w build
          find build -name '*.py' -exec chmod +x {} +
          cd build
          git init --quiet
          cp ${baseRom} ver/us/baserom.z64
          patchShebangs --build tools/

          virtualenv venv --quiet
          source venv/bin/activate
          pip install --no-index --find-links=${pythonDeps} -r tools/requirements.txt --quiet

          python3 tools/build/configure.py --no-sccache
          ninja

          # Build binary RIFF index with a known path prefix.
          # configure.py uses rewrite_index_paths.py to replace it with
          # the local project root at download time.
          clangd-indexer --executor=all-TUs compile_commands.json > papermario-dx.idx

          # Rewrite paths in the RIFF string table
          python3 tools/build/rewrite_index_paths.py papermario-dx.idx \
            "$(pwd)/" '$$ROOT$$/'

          mkdir -p $out
          mv papermario-dx.idx $out/papermario-dx.idx
        '';

      in {
        packages = {
          default = linuxRom;
          unix-toolchain = unixToolchain;
        } // pkgs.lib.optionalAttrs pkgs.stdenv.isLinux {
          # Cross-compiled, so the one Linux machine that publishes toolchains
          # builds every platform's.
          windows-toolchain = windowsToolchain;
          clangd-index = clangdIndex;
          clangd-indexer = clangdIndexer;
          macos-aarch64-toolchain = macosToolchain "aarch64";
          macos-x86_64-toolchain = macosToolchain "x86_64";
          macos-aarch64-gcc = (macosToolchain "aarch64").passthru.mips-gcc;
        } // pkgs.lib.optionalAttrs (system == "x86_64-linux") {
          # The x86_64 toolchain that's published, which CI builds on an
          # aarch64-linux host. The jar is the same bytecode on every system,
          # so the aarch64 one spares compiling it under emulation.
          unix-toolchain-with-aarch64-jar = unixToolchainWith star-rod.packages.aarch64-linux.jar;
          windows-rom = windowsToolchain.passthru.wineRom;
        };

        checks = pkgs.lib.optionalAttrs (system == "x86_64-linux") {
          windows-toolchain = windowsToolchain.passthru.tests.wine;
          windows-toolchain-build = windowsToolchain.passthru.tests.build;
          windows-linux-match = pkgs.runCommand "windows-linux-rom-match" {} ''
            if cmp -s ${linuxRom}/papermario.z64 ${windowsToolchain.passthru.wineRom}/papermario.z64; then
              echo "=== Linux and Windows ROMs match ==="
              touch $out
            else
              echo "=== ERROR: Linux and Windows ROMs differ ==="
              exit 1
            fi
          '';
        };

        devShells.default = pkgs.mkShell {
          name = "papermario-dx";
          venvDir = "./venv";
          packages = mipsTools ++ (with pkgs; [
            ninja
            zlib
            libyaml
            python3
            python3Packages.virtualenv
            sccachePkg
            git
            iconv
            gcc # for n64crc
            (callPackage ./tools/pigment64.nix {})
            (callPackage ./tools/crunch64.nix {})
            evtValidatePkg
            starRodPkg
            llvmTools
            treefmt
          ]) ++ [ mipsGdb ] ++ (if pkgs.stdenv.isLinux then [ pkgs.flips ] else []); # https://github.com/NixOS/nixpkgs/issues/373508
          shellHook = ''
            rm -f ./ver/us/baserom.z64 && cp ${baseRom} ./ver/us/baserom.z64
            export SCCACHE_CONF="$PWD/.dx/sccache-config.toml"
            export AWS_SHARED_CREDENTIALS_FILE="$PWD/.dx/sccache-credentials"
            export SCCACHE_BASEDIRS="$PWD"
            export SCCACHE_SKIP_CACHE_CHECK=1

            virtualenv venv --quiet
            source venv/bin/activate
            # pygfxd has no manylinux aarch64 wheel on PyPI (only
            # x86_64), so on that platform pip would otherwise silently
            # install the incompatible x86_64 build; force a source build
            # there. Elsewhere the prebuilt wheel is already correct and
            # faster to install.
            pip install ${
              pkgs.lib.optionalString (pkgs.stdenv.hostPlatform.isLinux && pkgs.stdenv.hostPlatform.isAarch64)
                "--no-binary pygfxd"
            } -r ${./tools/requirements.txt} --quiet
          '';
        };
      }
    );
}
