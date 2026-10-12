# Builds binutils for mips-linux-gnu to run on macOS, cross-compiled on Linux.
{
  stdenvNoCC,
  buildCC,
  cross,
  hostTriple,
  binutilsSrc,
  binutilsPatches,
  binutilsVersion,
  texinfo,
  bison,
  flex,
}:

stdenvNoCC.mkDerivation {
  pname = "mips-binutils-macos";
  version = binutilsVersion;

  src = binutilsSrc;
  patches = binutilsPatches;

  nativeBuildInputs = [ cross buildCC texinfo bison flex ];

  # The compiler is a wrapper script that stdenv's fixup knows nothing about.
  dontFixup = true;

  preConfigure = ''
    export CC_FOR_BUILD=${buildCC}/bin/cc CXX_FOR_BUILD=${buildCC}/bin/c++
    # The linker is not GNU ld, whatever libtool concludes from its name.
    export lt_cv_prog_gnu_ld=no
  '';

  configureFlags = [
    "--host=${hostTriple}"
    "--target=mips-linux-gnu"
    "--disable-nls"
    "--disable-werror"
    "--disable-gdb"
    "--disable-sim"
    "--disable-readline"
    "--disable-shared"
    "--enable-static"
    "--with-sysroot=/dev/null"
    # The bundled zlib does not compile against the macOS SDK; macOS ships its own.
    "--with-system-zlib"
  ];

  enableParallelBuilding = true;

  postInstall = ''
    rm -rf $out/share $out/lib $out/include
  '';
}
