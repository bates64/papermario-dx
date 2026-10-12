# Builds gdb for mips-linux-gnu to run on macOS, cross-compiled on Linux, with
# the libraries it needs built statically alongside it. It has no Python, so it
# can't run Python scripts.
{
  stdenvNoCC,
  buildCC,
  cross,
  hostTriple,
  gdbSrc,
  gdbVersion,
  m4,
  lib,
  arch,
  gmpSrc,
  mpfrSrc,
  texinfo,
  bison,
  flex,
}:

let
  # gmp and mpfr as static libraries, in a prefix gdb is told to look in.
  libraries = stdenvNoCC.mkDerivation {
    pname = "gdb-libraries-macos";
    version = "0";
    dontUnpack = true;
    dontFixup = true;
    nativeBuildInputs = [ cross buildCC m4 ];
    buildPhase = ''
      export CC_FOR_BUILD=${buildCC}/bin/cc
      mkdir gmp mpfr
      tar -xf ${gmpSrc} -C gmp --strip-components=1
      tar -xf ${mpfrSrc} -C mpfr --strip-components=1
      (cd gmp && ./configure --host=${hostTriple} --prefix=$out --disable-shared --enable-static ${lib.optionalString (arch == "x86_64") "--disable-assembly"} && make -j $NIX_BUILD_CORES && make install)
      (cd mpfr && ./configure --host=${hostTriple} --prefix=$out --with-gmp=$out --disable-shared --enable-static && make -j $NIX_BUILD_CORES && make install)
    '';
    installPhase = "true";
  };
in
stdenvNoCC.mkDerivation {
  pname = "mips-gdb-macos";
  version = gdbVersion;

  src = gdbSrc;

  nativeBuildInputs = [ cross buildCC texinfo bison flex ];

  # The compiler is a wrapper script that stdenv's fixup knows nothing about.
  dontFixup = true;

  preConfigure = ''
    export CC_FOR_BUILD=${buildCC}/bin/cc CXX_FOR_BUILD=${buildCC}/bin/c++
    export lt_cv_prog_gnu_ld=no
  '';

  configureFlags = [
    "--host=${hostTriple}"
    "--target=mips-linux-gnu"
    "--with-gmp=${libraries}"
    "--with-mpfr=${libraries}"
    "--with-libgmp-prefix=${libraries}"
    "--with-libmpfr-prefix=${libraries}"
    "--without-python"
    "--without-expat"
    "--without-guile"
    "--without-lzma"
    "--without-debuginfod"
    "--without-babeltrace"
    "--without-xxhash"
    "--with-system-zlib"
    "--disable-nls"
    "--disable-werror"
    "--disable-sim"
    "--disable-gdbserver"
    "--disable-tui"
    "--disable-source-highlight"
    "--disable-shared"
    "--enable-static"
  ];

  enableParallelBuilding = true;

  postInstall = ''
    rm -rf $out/share $out/include $out/lib
  '';
}
