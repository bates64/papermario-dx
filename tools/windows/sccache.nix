# Pre-built sccache for Windows (fixed-output derivation).
{
  fetchurl,
  unzip,
  stdenvNoCC,
}:

let
  version = "0.18.0";
  sccacheZip = fetchurl {
    url = "https://github.com/mozilla/sccache/releases/download/v${version}/sccache-v${version}-x86_64-pc-windows-msvc.zip";
    sha256 = "0g9n92in29y2iyaaq6yw521g817myg98mqa1yx2548labr6wfrc9";
  };
in
stdenvNoCC.mkDerivation {
  pname = "sccache-windows";
  inherit version;
  dontUnpack = true;

  nativeBuildInputs = [ unzip ];

  installPhase = ''
    mkdir -p $out/bin
    unzip ${sccacheZip}
    cp sccache-v${version}-x86_64-pc-windows-msvc/sccache.exe $out/bin/
  '';
}
