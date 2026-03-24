# Pre-built ninja for Windows (fixed-output derivation).
{
  fetchurl,
  unzip,
  stdenvNoCC,
}:

let
  ninjaZip = fetchurl {
    url = "https://github.com/ninja-build/ninja/releases/download/v1.12.1/ninja-win.zip";
    sha256 = "0yj6128i5fyw793blsldcy8pd8vp4963fg6vy9cgzmmn0p3zwl7m";
  };
in
stdenvNoCC.mkDerivation {
  pname = "ninja-windows";
  version = "1.12.1";
  dontUnpack = true;

  nativeBuildInputs = [ unzip ];

  installPhase = ''
    mkdir -p $out/bin
    unzip ${ninjaZip} -d $out/bin
  '';
}
