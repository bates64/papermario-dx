{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

    # This commit uses binutils 2.39. We don't want binutils 2.40+ because of a performance regression in ld.
    nixpkgs-binutils-2_39.url = "github:NixOS/nixpkgs/55070e598e0e03d1d116c49b9eff322ef07c6ac6";

    flake-utils.url = "github:numtide/flake-utils";

    star-rod.url = "github:z64a/star-rod/9339cb4e867514267ff8ab404b00b53e5a5e67dd";
    star-rod.inputs.nixpkgs.follows = "nixpkgs";

    dream2nix.url = "github:nix-community/dream2nix";
    dream2nix.inputs.nixpkgs.follows = "nixpkgs";

    pre-commit-hooks.url = "github:cachix/git-hooks.nix";
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
  outputs =
    {
      self,
      nixpkgs,
      flake-utils,
      nixpkgs-binutils-2_39,
      star-rod,
      dream2nix,
      pre-commit-hooks,
    }:
    flake-utils.lib.eachDefaultSystem (
      system:
      let
        name = "papermario-dx";
        crossSystem = {
          config = "mips-linux-gnu"; # prefix expected by scripts in tools/
          system = "mips64-elf";
          gcc = {
            arch = "vr4300";
            tune = "vr4300";
            abi = "32";
          };
        };
        pkgs = import nixpkgs { inherit system; };
        pkgsCross = import nixpkgs { inherit system crossSystem; };
        binutils2_39 =
          (import nixpkgs-binutils-2_39 { inherit system crossSystem; }).buildPackages.binutilsNoLibc;
        baseRom = pkgs.requireFile {
          name = "papermario.us.z64";
          message = ''
            ==== MISSING BASE ROM =======================================================

            Paper Mario DX only supports the US version of Paper Mario. You need to
            provide a copy of the ROM in z64 format to build the project.

            Please rename your ROM to papermario.us.z64 and add it to the Nix store using
                nix-store --add-fixed sha256 papermario.us.z64
            then retry.

            If you don't have a ROM, dump it from your own cartridge.

            If you have a ROM but it is in n64 or v64 format, convert it to z64 first:
                https://hack64.net/tools/swapper.php

            If you added your ROM to the Nix store already, but it's still not working,
            your ROM must be incorrect. Make sure the version is US, the format is z64,
            and that it has not been modified.
          '';
          sha256 = "9ec6d2a5c2fca81ab86312328779fd042b5f3b920bf65df9f6b87b376883cb5b";
        };
        configure = dream2nix.lib.evalModules {
          packageSets.nixpkgs = pkgs;
          modules = [
            ./tools/configure/default.nix
            {
              paths = {
                projectRoot = ./.;
                projectRootFile = "flake.nix";
                package = ./tools/configure;
              };
            }
          ];
        };
        assets =
          pkgsCross.runCommand "papermario-assets"
            {
              nativeBuildInputs = [ configure ];
              srcs = [
                ./ver/us
                ./tools
                ./src/effects.yaml
                ./src/effect_shims.yaml
              ];
            }
            ''
              mkdir -p assets/us ver/us src
              cp ${baseRom} ver/us/baserom.z64
              cp -r ${./ver/us}/* ver/us
              ln -s ${./tools} tools
              ln -s ${./src/effects.yaml} src/effects.yaml
              ln -s ${./src/effect_shims.yaml} src/effect_shims.yaml

              configure --assets

              mkdir -p $out
              cp -r assets $out
              cp -r ver/us/build $out     # pm_effect_shims.py asm
            '';
        configured =
          pkgsCross.runCommand "${name}-configured"
            {
              nativeBuildInputs = [
                configure
                pkgs.ninja
                pkgs.ccache
              ];
              srcs = [
                assets
                ./assets
                ./ver/us
                ./tools
                ./src/effects.yaml
                ./src/effect_shims.yaml
              ];
            }
            ''
              mkdir -p assets ver/us src
              cp ${baseRom} ver/us/baserom.z64
              cp -r ${./ver/us}/* ver/us
              ln -s ${./tools} tools
              ln -s ${./src/effects.yaml} src/effects.yaml
              ln -s ${./src/effect_shims.yaml} src/effect_shims.yaml
              ln -s ${./assets}/* assets/
              rm -rf assets/us && ln -s ${assets}/assets/us assets/us

              mkdir -p $out

              PAPERMARIO_LD="${binutils2_39}/bin/mips-linux-gnu-ld" configure
              cp ver/us/papermario.ld $out
              cp build.ninja $out
              cp ver/us/build/include/ld_addrs.h $out
            '';
        commonDeps = with pkgs; [
          ninja
          zlib
          libyaml
          python3
          ccache
          git
          iconv
          gcc # for n64crc
          (callPackage ./tools/pigment64.nix { })
          (callPackage ./tools/crunch64.nix { })
        ];
        z64 = pkgsCross.stdenv.mkDerivation {
          inherit name;
          src = pkgs.symlinkJoin {
            name = "configured-src";
            paths = [
              assets
              configured
              ./.
            ];
          };
          nativeBuildInputs = commonDeps ++ [ configure.pyEnv ];
          configurePhase = ''
            ln -s $src/assets assets
            ln -s $src/src src
            ln -s $src/include include
            ln -s $src/tools tools

            mv build ver/us
            mv papermario.ld ver/us

            mkdir -p ver/us/build/include
            mv ld_addrs.h ver/us/build/include
          '';
          buildPhase = ''
            ninja
          '';
          installPhase = ''
            mkdir -p $out
            cp ver/us/build/papermario.z64 $out/${name}.z64
          '';
          enableParallelBuilding = true;
        };
      in
      {
        packages = {
          default = z64;
          bps = pkgs.stdenv.mkDerivation {
            name = "${name}-bps";
            src = z64;
            nativeBuildInputs = [ pkgs.flips ];
            buildPhase = ''
              mkdir -p $
              flips ${baseRom} $src/${name}.z64 $out/${name}.bps || true
            '';
          };
          inherit configure; # for `nix run ".#configure.lock"` to update lockfile
        };

        apps.default = {
          type = "app";
          program = "${
            pkgs.writeShellApplication {
              inherit name;
              runtimeInputs = [ pkgs.ares ];
              text = ''
                ares ${z64}/${name}.z64
              '';
            }
          }/bin/${name}";
        };

        devShells.default = pkgsCross.mkShell {
          name = "${name}-dev";
          inputsFrom = [ configure.devShell ];
          packages =
            with pkgs;
            [
              n2
              star-rod.packages.${system}.default
              clang-tools
              include-what-you-use
              assets
              configured
            ]
            ++ commonDeps
            ++ (if pkgs.stdenv.isLinux then [ pkgs.ares ] else [ ]); # https://github.com/NixOS/nixpkgs/issues/373508
          shellHook = ''
            # Old versions of this devshell created this dir, delete it
            rm -rf venv

            rm -rf assets/us && ln -sf ${assets}/assets/us assets/us

            mkdir -p ver/us/build/asm/effect_shims/ && cp -rf ${assets}/build/asm/effect_shims/* ver/us/build/asm/effect_shims/
            mkdir -p ver/us/build/asm/effects/ && cp -rf ${assets}/build/asm/effects/* ver/us/build/asm/effects/
            mkdir -p ver/us/build/include && ln -sf ${configured}/ld_addrs.h ver/us/build/include/ld_addrs.h
            chmod -R +w ver/us/build

            ln -sf ${configured}/papermario.ld ver/us/papermario.ld
            ln -sf ${configured}/build.ninja build.ninja

            rm -f compile_commands.json
            ninja -t compdb > compile_commands.json
            python3 ./tools/clean_up_compdb.py compile_commands.json

            # TODO: fix Star Rod being unable to follow WSL symlinks
            rm -f ./ver/us/baserom.z64 && cp ${baseRom} ./ver/us/baserom.z64

            ${self.checks.${system}.pre-commit-check.shellHook}
          '';
        };

        checks = {
          pre-commit-check = pre-commit-hooks.lib.${system}.run {
            src = pkgs.symlinkJoin {
              name = "pre-commit-check-src";
              paths = [
                configured
                ./.
              ];
            };
            hooks = {
              nixfmt-rfc-style.enable = true;
              statix.enable = true;
              deadnix.enable = true;
              clang-format = {
                enable = false; # TODO
                types_or = pkgs.lib.mkForce [
                  "c"
                  "c++"
                ];
              };
              clang-tidy.enable = true;
              include-what-you-use = {
                enable = true;
                name = "include-what-you-use";
                entry = "./tools/include-what-you-use";
                types = [ "c" "c++" ];
              };
              ruff-format.enable = true;
              check-xml.enable = true;
              check-yaml.enable = true;
              check-symlinks.enable = true;
              check-toml.enable = true;
              check-case-conflicts.enable = true;
              check-merge-conflicts.enable = true;
              actionlint.enable = true;
              end-of-file-fixer.enable = true;
              trim-trailing-whitespace.enable = true;
              editorconfig-checker.enable = false; # TODO(clang-format)
              check-shebang-scripts-are-executable.enable = true;
              check-executables-have-shebangs.enable = true;
              fix-byte-order-marker.enable = true;
              mixed-line-endings.enable = true;
            };
          };
        };
      }
    );
}
