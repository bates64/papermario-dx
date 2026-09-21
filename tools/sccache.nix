# Pre-built sccache for the current system (fixed-output derivation).
#
# Not taken from nixpkgs: nixpkgs-unstable currently ships 0.17.0, but
# SCCACHE_BASEDIRS (needed for cache hits across different absolute checkout
# paths - see tools/build/configure.py) only strips basedirs from compiler
# arguments, not just preprocessed source, since 0.18.0.
{
  pkgs,
  fetchurl,
  stdenvNoCC,
}:

let
  version = "0.18.0";

  platformTag = {
    "x86_64-linux" = "x86_64-unknown-linux-musl";
    "aarch64-linux" = "aarch64-unknown-linux-musl";
    "x86_64-darwin" = "x86_64-apple-darwin";
    "aarch64-darwin" = "aarch64-apple-darwin";
  }.${pkgs.stdenv.hostPlatform.system} or (throw "tools/sccache.nix: unsupported system ${pkgs.stdenv.hostPlatform.system}");

  sha256 = {
    "x86_64-unknown-linux-musl" = "12fcd96wrzh9liyawqlddhhi5lkxcxqfylg3plvk07i3przl9wa5";
    "aarch64-unknown-linux-musl" = "0jimlkjrfjgqsavlyxcdkjllmb48gfxpb7i2qiys8iivvbaq8cib";
    "aarch64-apple-darwin" = "13jfcx426w5ymsa3k4j1l09mm9kcdyrib1cy50jm2vv4kd8q909h";
  }.${platformTag} or (throw "tools/sccache.nix: no hash pinned for ${platformTag}");

  dirName = "sccache-v${version}-${platformTag}";
  sccacheTar = fetchurl {
    url = "https://github.com/mozilla/sccache/releases/download/v${version}/${dirName}.tar.gz";
    inherit sha256;
  };
in
stdenvNoCC.mkDerivation {
  pname = "sccache";
  inherit version;
  dontUnpack = true;

  installPhase = ''
    mkdir -p $out/bin
    tar xzf ${sccacheTar} ${dirName}/sccache
    cp ${dirName}/sccache $out/bin/
    chmod +x $out/bin/sccache
  '';
}
