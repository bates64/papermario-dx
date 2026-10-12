# The macOS SDK, as nixpkgs fetches it from Apple for its own Darwin builds,
# for cross-compiling the macOS toolchain on Linux.
{ lib, path, callPackage }:

let
  dir = "${path}/pkgs/by-name/ap/apple-sdk";
  versions = lib.importJSON "${dir}/metadata/versions.json";
in
callPackage "${dir}/common/fetch-sdk.nix" { } versions."15"
