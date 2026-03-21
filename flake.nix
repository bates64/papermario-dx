{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

    # This commit uses binutils 2.39. We don't want binutils 2.40+ because of a performance regression in ld.
    nixpkgs-binutils-2_39.url = "github:NixOS/nixpkgs/55070e598e0e03d1d116c49b9eff322ef07c6ac6";

    flake-utils.url = "github:numtide/flake-utils";

    star-rod.url = "github:z64a/star-rod/9339cb4e867514267ff8ab404b00b53e5a5e67dd";
    star-rod.inputs.nixpkgs.follows = "nixpkgs";
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
        binutils2_39 = (import nixpkgs-binutils-2_39 { inherit system crossSystem; }).buildPackages.binutilsNoLibc;
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
        windowsToolchain = import ./tools/windows {
          inherit pkgs nixpkgs-binutils-2_39 baseRom;
          mipsCrossGcc = pkgsCross.stdenv.cc;
          src = self;
        };
        pythonDeps = windowsToolchain.passthru.pythonDeps;
        requirementsExtra = ./requirements_extra.txt;
        pythonDepsExtra = pkgs.stdenvNoCC.mkDerivation {
          name = "papermario-python-deps-extra";
          outputHashMode = "recursive";
          outputHashAlgo = "sha256";
          outputHash = "sha256-UpAKsz4JCCWJHl6hTpIi/dzLISDF7RcGuY/hFjAMex8=";
          nativeBuildInputs = [ pkgs.python3 pkgs.python3Packages.pip pkgs.cacert ];
          buildCommand = ''
            export SSL_CERT_FILE=${pkgs.cacert}/etc/ssl/certs/ca-bundle.crt
            pip download -r ${./requirements.txt} -r ${requirementsExtra} setuptools wheel -d $out
          '';
        };
        linuxRom = pkgs.runCommand "papermario-linux-rom" {
          nativeBuildInputs = [
            pkgsCross.stdenv.cc
            binutils2_39
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
          ] ++ pkgs.lib.optional pkgs.stdenv.isLinux pkgs.flips;
          # Disable nixpkgs hardening flags (zerocallusedregs, fortify, etc.)
          # that the cross-compiler wrapper injects. The build system manages
          # its own flags and we want output identical to the Windows toolchain.
          NIX_HARDENING_ENABLE = "";
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
          pip install --no-index --find-links=${pythonDeps} -r requirements.txt --quiet

          export PAPERMARIO_LD="${binutils2_39}/bin/mips-linux-gnu-ld"
          python3 tools/build/configure.py --no-ccache
          ninja

          mkdir -p $out
          cp ver/us/build/papermario.z64 $out/
          ${pkgs.lib.optionalString pkgs.stdenv.isLinux
            "flips --create --bps ${baseRom} ver/us/build/papermario.z64 $out/papermario.bps"}
        '';
      in {
        packages = {
          default = linuxRom;
        } // pkgs.lib.optionalAttrs (system == "x86_64-linux") {
          windows-toolchain = windowsToolchain;
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

        devShells.default = pkgsCross.mkShell {
          name = "papermario-dx";
          venvDir = "./venv";
          # Disable nixpkgs hardening flags (stackprotector, fortify, pic, etc.)
          # that the cross-compiler wrapper injects. These change MIPS code
          # generation and would cause Linux builds to differ from Windows.
          NIX_HARDENING_ENABLE = "";
          packages = with pkgs; [
            ninja # needed for ninja -t compdb in configure, as n2 doesn't support it
            n2 # same as ninja, but with prettier output
            zlib
            libyaml
            python3
            python3Packages.virtualenv
            ccache
            git
            iconv
            gcc # for n64crc
            (callPackage ./tools/pigment64.nix {})
            (callPackage ./tools/crunch64.nix {})
            star-rod.packages.${system}.default
            clang-tools
            treefmt
          ] ++ (if pkgs.stdenv.isLinux then [ pkgs.flips ] else []); # https://github.com/NixOS/nixpkgs/issues/373508
          shellHook = ''
            rm -f ./ver/us/baserom.z64 && cp ${baseRom} ./ver/us/baserom.z64
            export PAPERMARIO_LD="${binutils2_39}/bin/mips-linux-gnu-ld"

            # Install python packages from cached wheels (offline)
            virtualenv venv --quiet
            source venv/bin/activate
            pip install --no-index --find-links=${pythonDepsExtra} -r ${./requirements.txt} -r ${./requirements_extra.txt} --quiet
          '';
        };
      }
    );
}
