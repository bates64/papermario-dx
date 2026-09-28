# Every file that any toolchain installs from requirements.txt, for every
# platform, as a directory for `pip install --no-index --find-links`.
#
# pip evaluates markers on the build machine, so they're dropped to download
# the same files everywhere. That lets one hash, computed on any machine, cover
# every platform.
{
  lib,
  runCommand,
  stdenvNoCC,
  python3,
  cacert,
  callPackage,
}:

let
  requirements = runCommand "requirements-without-markers.txt" {} ''
    sed -E 's/^([^ #]+==[^ ]+) ;.*/\1/' ${./requirements.txt} > $out
  '';

  # pip only accepts wheels tagged with a listed platform, so list every glibc
  # version a Linux wheel might target.
  manylinux = arch:
    map (minor: "manylinux_2_${toString minor}_${arch}") (lib.range 17 28)
    ++ [ "manylinux2014_${arch}" "manylinux2010_${arch}" "manylinux1_${arch}" ];

  unixPython = python3.pythonVersion;
  windowsPython = lib.versions.majorMinor (callPackage ./windows/python.nix {}).version;

  download = python: tags: ''
    pip download --quiet --no-deps -r ${requirements} -d $out \
      --python-version ${python} --implementation cp ${lib.concatMapStringsSep " " (tag: "--platform ${tag}") tags}
  '';
in
stdenvNoCC.mkDerivation {
  # Changing requirements.txt changes the name, so a stale hash fails instead
  # of reusing the previous download.
  name = "papermario-python-packages-${builtins.substring 0 8 (builtins.hashFile "sha256" ./requirements.txt)}";
  outputHashMode = "recursive";
  outputHash = "sha256-SxObaxvQOQTzEraxKQZAY08qx21DGjqDzhrdhoTEht0=";
  nativeBuildInputs = [ python3 python3.pkgs.pip cacert ];
  buildCommand = ''
    export SSL_CERT_FILE=${cacert}/etc/ssl/certs/ca-bundle.crt
    export HOME=$(mktemp -d)
    ${download unixPython (manylinux "x86_64")}
    ${download unixPython (manylinux "aarch64")}
    ${download unixPython [ "macosx_11_0_x86_64" ]}
    ${download unixPython [ "macosx_11_0_arm64" ]}
    ${download windowsPython [ "win_amd64" ]}
  '';

  passthru = { inherit requirements; };
}
