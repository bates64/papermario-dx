# Python packages (requirements.txt) for bundling into the downloadable
# toolchain.
{ pkgs }:

pkgs.stdenvNoCC.mkDerivation {
  pname = "papermario-python-packages";
  version = "0";
  dontUnpack = true;

  nativeBuildInputs = [ pkgs.python3 pkgs.python3Packages.pip pkgs.gcc ];

  installPhase = ''
    mkdir -p $out
    pip install --no-index --find-links=${pkgs.callPackage ../python-packages.nix {}} --target $out \
      -r ${../requirements.txt} --quiet
  '';
}
