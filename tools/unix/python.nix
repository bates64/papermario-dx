# Python packages (requirements.txt + requirements_extra.txt) for bundling
# into the downloadable toolchain. Downloaded natively for the current
# platform, so pip resolves the correct wheels without cross-platform flags
# (contrast tools/windows/default.nix's pythonDepsWindows, which has to fetch
# win_amd64 wheels from a Linux build machine).
{ pkgs }:

let
  requirements = ../../requirements.txt;
  requirementsExtra = ../../requirements_extra.txt;
  requirementsDigest = builtins.substring 0 8 (builtins.hashFile "sha256" requirements);

  # Each platform resolves a different set of wheels, so each needs its own
  # hash. Fixed-output derivation, so it's allowed network access in the Nix
  # sandbox. Update an entry by running the build once: it fails on hash
  # mismatch and reports the correct value to paste in.
  wheelHashes = {
    "x86_64-linux" = "sha256-fE/68DoCfnoaIN8nVjnfe8+XKbsfBsSXBPlPEgVc8WQ=";
    "aarch64-linux" = "sha256-aOgCFi6gQhCTAC1MzoX5TcBunoDFUsizvRZYzkgq+4g=";
    "aarch64-darwin" = "sha256-UE+EqFe+LEM9OFF76GdUcW/HXe9bpPzDsD1dY3L/R6M=";
  };

  wheels = pkgs.stdenvNoCC.mkDerivation {
    name = "papermario-python-wheels-${pkgs.stdenv.hostPlatform.system}-${requirementsDigest}";
    outputHashMode = "recursive";
    outputHashAlgo = "sha256";
    outputHash = wheelHashes.${pkgs.stdenv.hostPlatform.system};
    nativeBuildInputs = [ pkgs.python3 pkgs.python3Packages.pip pkgs.cacert pkgs.gcc ];
    buildCommand = ''
      export SSL_CERT_FILE=${pkgs.cacert}/etc/ssl/certs/ca-bundle.crt
      pip download -r ${requirements} -r ${requirementsExtra} setuptools wheel -d $out
    '';
  };
in
pkgs.stdenvNoCC.mkDerivation {
  pname = "papermario-python-packages";
  version = "0";
  dontUnpack = true;

  nativeBuildInputs = [ pkgs.python3 pkgs.python3Packages.pip pkgs.gcc ];

  installPhase = ''
    mkdir -p $out
    pip install --no-index --find-links=${wheels} --target $out \
      -r ${requirements} -r ${requirementsExtra} --quiet
  '';
}
