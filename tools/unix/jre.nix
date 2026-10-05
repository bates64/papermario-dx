# Pre-built Eclipse Temurin JRE for the current platform, providing bin/java
# to run Star Rod's jar. Fetched directly rather than via nixpkgs'
# `temurin-jre-bin` (whose bin/java is a wrapper script embedding absolute
# /nix/store paths, which break once the toolchain is relocated outside Nix)
# — these are the same raw upstream archives, giving real ELF/Mach-O binaries
# compatible with default.nix's generic RPATH-relocation.
{ pkgs }:

let
  system = pkgs.stdenv.hostPlatform.system;
  releaseTag = "jdk-17.0.20.1%2B1";
  topDir = "jdk-17.0.20.1+1-jre";

  sources = {
    "x86_64-linux" = {
      asset = "OpenJDK17U-jre_x64_linux_hotspot_17.0.20.1_1.tar.gz";
      sha256 = "0b2b640e3046b64c8ec504de0ab9d91bb5610182bda21fad454681ce54d45a62";
      home = ".";
    };
    "aarch64-linux" = {
      asset = "OpenJDK17U-jre_aarch64_linux_hotspot_17.0.20.1_1.tar.gz";
      sha256 = "b8efcd5acc9109fe8d35bed132499643048a257b4f6042906ece37d03c839d77";
      home = ".";
    };
    "x86_64-darwin" = {
      asset = "OpenJDK17U-jre_x64_mac_hotspot_17.0.20.1_1.tar.gz";
      sha256 = "333cb81123c36568586646c73c8fa2326dab8badc43f5ea388a90fff59c9df27";
      home = "Contents/Home";
    };
    "aarch64-darwin" = {
      asset = "OpenJDK17U-jre_aarch64_mac_hotspot_17.0.20.1_1.tar.gz";
      sha256 = "190480874ccceb358cbc840393207f77ac3e63a4c5f8129d0e23e9518b96ad05";
      home = "Contents/Home";
    };
  }.${system} or (throw "tools/unix/jre.nix: unsupported system ${system}");

  jreTarball = pkgs.fetchurl {
    url = "https://github.com/adoptium/temurin17-binaries/releases/download/${releaseTag}/${sources.asset}";
    sha256 = sources.sha256;
  };
in
pkgs.stdenvNoCC.mkDerivation {
  pname = "jre-${system}";
  version = "17.0.20.1+1";
  dontUnpack = true;

  installPhase = ''
    mkdir -p $out
    tar -xzf ${jreTarball} -C $out
    cp -rL "$out/${topDir}/${sources.home}/." $out/
    rm -rf "$out/${topDir}"
  '';
}
