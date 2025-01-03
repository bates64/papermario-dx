{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

    # This commit uses binutils 2.39. We don't want binutils 2.40+ because of a performance regression in ld.
    nixpkgs-binutils-2_39.url = "github:NixOS/nixpkgs/55070e598e0e03d1d116c49b9eff322ef07c6ac6";

    flake-utils.url = "github:numtide/flake-utils";
  };
  outputs = { self, nixpkgs, flake-utils, nixpkgs-binutils-2_39 }:
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
      in {
        # TODO: migrate devShell from shell.nix. requires python dependencies to be derivations, as flakes are pure
      }
    );
}
