# A stand-in for rustPlatform that builds Rust programs for macOS on Linux, so
# the existing Rust package files work unchanged. It uses Rust's own release of
# the compiler: the macOS standard library only loads in a compiler from the
# same release build, which nixpkgs' rustc is not. Programs are linked with the
# cross compiler.
{
  lib,
  stdenv,
  fetchurl,
  autoPatchelfHook,
  zlib,
  rustPlatform,
  cross,
  arch,
}:

let
  version = "1.83.0";
  target = "${arch}-apple-darwin";
  targetEnv = builtins.replaceStrings [ "-" ] [ "_" ] target;
  host = stdenv.buildPlatform.rust.rustcTarget;

  dist = component: triple: hash: fetchurl {
    url = "https://static.rust-lang.org/dist/${component}-${version}-${triple}.tar.xz";
    inherit hash;
  };

  hostHashes = {
    x86_64-unknown-linux-gnu = {
      rustc = "sha256-bsQOBAXIy+07eGqX03TBRLAS/IMbfCK1NfjstST0la0=";
      cargo = "sha256-3oNKQGLZzSAPjgzcqJTAuYr+JvE5bYB2XfgoiAo5uYw=";
      rust-std = "sha256-yI/myyL50nIfJkMLa90pHlYtp1noYp4rTH6yx8rXBfI=";
    };
    aarch64-unknown-linux-gnu = {
      rustc = "sha256-ql0HX5kDaC5RcfNZlIcX0ykRvtjDngOVBC5iVlIGLqk=";
      cargo = "sha256-W5arpIeQrPrOpgpmQ6TzDX7cE+kYmtNrQbus2tE9SeE=";
      rust-std = "sha256-iAT2c4CcXD2xG6NUtc+XJK7WiIR3H6Mq9LNHISenYCg=";
    };
  }.${host} or (throw "tools/macos/rust.nix: no Rust release pinned for ${host}");

  targetHash = {
    aarch64 = "sha256-Y1IwoUIQ6HuCxvfwWXNJxcueXuOiYMmwSbSweK9y6uE=";
    x86_64 = "sha256-lWLJjFnGNE9TpPTDMeNMyIl1FTuMJd2LehHOAAd+48s=";
  }.${arch};

  toolchain = stdenv.mkDerivation {
    pname = "rust-for-${target}";
    inherit version;
    srcs = [
      (dist "rustc" host hostHashes.rustc)
      (dist "cargo" host hostHashes.cargo)
      (dist "rust-std" host hostHashes.rust-std)
      (dist "rust-std" target targetHash)
    ];
    sourceRoot = ".";
    nativeBuildInputs = [ autoPatchelfHook ];
    buildInputs = [ stdenv.cc.cc.lib zlib ];
    appendRunpaths = [ "${placeholder "out"}/lib" ];
    dontConfigure = true;
    dontBuild = true;
    # Stripping breaks the compiler.
    dontStrip = true;
    installPhase = ''
      for dir in rustc-* cargo-* rust-std-*; do
        (cd $dir && bash ./install.sh --prefix=$out --disable-ldconfig >/dev/null)
      done
    '';
  };

  buildRustPackage =
    {
      pname,
      version,
      src,
      cargoHash ? null,
      cargoLock ? null,
      buildAndTestSubdir ? null,
      ...
    }:
    stdenv.mkDerivation {
      inherit pname version src;

      cargoDeps =
        if cargoLock != null then
          rustPlatform.importCargoLock cargoLock
        else
          rustPlatform.fetchCargoTarball {
            inherit src;
            name = "${pname}-${version}";
            hash = cargoHash;
          };

      nativeBuildInputs = [ rustPlatform.cargoSetupHook toolchain ];

      dontFixup = true;

      # The host strip does not understand Mach-O.
      CARGO_PROFILE_RELEASE_STRIP = "none";

      "CARGO_TARGET_${lib.toUpper targetEnv}_LINKER" = "${cross}/bin/cc";
      "CC_${targetEnv}" = "${cross}/bin/cc";
      "AR_${targetEnv}" = "${cross}/bin/ar";

      buildPhase = ''
        runHook preBuild
        ${lib.optionalString (buildAndTestSubdir != null) "cd ${buildAndTestSubdir}"}
        cargo build --release --frozen --target ${target} -j $NIX_BUILD_CORES
        runHook postBuild
      '';

      installPhase = ''
        runHook preInstall
        mkdir -p $out/bin
        cd "$NIX_BUILD_TOP/$sourceRoot"
        find target/${target}/release -maxdepth 1 -type f -perm -u+x ! -name '*.*' -exec cp {} $out/bin/ \;
        runHook postInstall
      '';
    };
in
{
  inherit buildRustPackage;
}
