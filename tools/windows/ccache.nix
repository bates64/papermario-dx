# Pre-built ccache for Windows (fixed-output derivation).
{
  fetchurl,
  unzip,
  stdenvNoCC,
}:

let
  version = "4.10.2";
  ccacheZip = fetchurl {
    url = "https://github.com/ccache/ccache/releases/download/v${version}/ccache-${version}-windows-x86_64.zip";
    sha256 = "1aadvzcpl7615bvz3mv1har8dm6hqnpaa4xf1xq9z6kahy0z0lk2";
  };
in
stdenvNoCC.mkDerivation {
  pname = "ccache-windows";
  inherit version;
  dontUnpack = true;

  nativeBuildInputs = [ unzip ];

  installPhase = ''
    mkdir -p $out/bin
    unzip ${ccacheZip}
    cp ccache-${version}-windows-x86_64/ccache.exe $out/bin/
  '';
}
