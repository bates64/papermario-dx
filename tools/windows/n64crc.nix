# Cross-compile n64crc.c for Windows.
# This is normally built by the ninja build itself, but on Windows there's no
# host C compiler, so we ship it pre-built.
{
  stdenv,
}:

stdenv.mkDerivation {
  pname = "n64crc-windows";
  version = "0";
  dontUnpack = true;

  buildPhase = ''
    $CC -O2 -o n64crc.exe ${../build/rom/n64crc.c}
  '';

  installPhase = ''
    mkdir -p $out/bin
    cp n64crc.exe $out/bin/
  '';
}
