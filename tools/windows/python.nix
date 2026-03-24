# Embeddable Python for Windows (fixed-output derivation).
# We fetch the official zip from python.org rather than cross-compiling CPython.
{
  fetchurl,
  unzip,
  stdenvNoCC,
}:

let
  version = "3.13.2";
  pythonZip = fetchurl {
    url = "https://www.python.org/ftp/python/${version}/python-${version}-embed-amd64.zip";
    sha256 = "14vvl9i0ihr7x24i4f4w4ddgggjijsrsxsiczafzdjs0n483d00y";
  };
  getPip = fetchurl {
    url = "https://bootstrap.pypa.io/get-pip.py";
    sha256 = "0g6azgrhc2w37cr06qwn3pg9vvn90b0r63dl76sy2nzlgmlirfpy";
  };
in
stdenvNoCC.mkDerivation {
  pname = "python-embed-windows";
  inherit version;
  dontUnpack = true;

  nativeBuildInputs = [ unzip ];

  installPhase = ''
    mkdir -p $out
    unzip ${pythonZip} -d $out

    # Remove the ._pth file so Python uses its normal sys.path initialization.
    # The ._pth file in the embeddable distribution restricts sys.path to only
    # the python dir and python313.zip, which prevents the script directory
    # (e.g. tools/build/) from being added to sys.path when running scripts.
    rm $out/python313._pth

    # Include get-pip.py for bootstrapping pip on first use.
    cp ${getPip} $out/get-pip.py
  '';
}
