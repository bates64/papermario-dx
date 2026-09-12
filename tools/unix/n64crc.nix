# Native build of n64crc.c, pre-built so the downloadable toolchain doesn't
# depend on the user already having a host C compiler.
{
  stdenv,
}:

stdenv.mkDerivation {
  pname = "n64crc";
  version = "0";
  dontUnpack = true;

  buildPhase = ''
    $CC -O2 -o n64crc ${../build/rom/n64crc.c}
  '';

  installPhase = ''
    mkdir -p $out/bin
    cp n64crc $out/bin/
  '';
}
