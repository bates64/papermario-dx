# A relocatable CPython for macOS, from python-build-standalone, with
# requirements.txt installed for it. It is the same minor version as the
# Python the Linux toolchains ship, so one set of downloaded wheels serves all.
{
  lib,
  fetchurl,
  stdenvNoCC,
  python3,
  unzip,
  pythonDeps,
  arch,
}:

let
  release = "20261009";
  version = "3.12.15";
  runtime = fetchurl {
    url = "https://github.com/astral-sh/python-build-standalone/releases/download/${release}/cpython-${version}%2B${release}-${arch}-apple-darwin-install_only.tar.gz";
    hash = {
      aarch64 = "sha256-g9ywR3fHmL2V82h6z5roSwmGAnLua9+wW+i8+UR/dbg=";
      x86_64 = "sha256-TITvWr5LwUVkYXX86biBk21gEmuaP5okxjCOLQNcpcY=";
    }.${arch};
  };
  platform = if arch == "aarch64" then "macosx_11_0_arm64" else "macosx_11_0_x86_64";
in
{
  inherit runtime;

  # Wheels to unpack into site-packages. Packages published only as source
  # are pure Python, so they're built into py3-none-any wheels here.
  packages = stdenvNoCC.mkDerivation {
    pname = "python-packages-macos-${arch}";
    version = "0";
    dontUnpack = true;
    nativeBuildInputs = [
      python3
      python3.pkgs.pip
      python3.pkgs.setuptools
      python3.pkgs.wheel
      unzip
    ];
    installPhase = ''
      export HOME=$(mktemp -d)
      mkdir -p $out files wheels
      pip download --quiet --no-deps --no-index --find-links=${pythonDeps} \
        --platform ${platform} --python-version ${lib.versions.majorMinor version} --implementation cp \
        -r ${pythonDeps.requirements} -d files
      for file in files/*; do
        case "$file" in
          *.whl) cp "$file" wheels/ ;;
          *) pip wheel --no-deps --no-build-isolation --no-index "$file" -w wheels --quiet ;;
        esac
      done
      for whl in wheels/*.whl; do
        unzip -o -q "$whl" -d $out
      done
    '';
  };
}
