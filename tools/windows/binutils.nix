{
  stdenv,
  buildCC,
  binutilsSrc,
  binutilsPatches,
  binutilsVersion,
  texinfo,
  bison,
  flex,
  zlib,
}:

stdenv.mkDerivation {
  pname = "mips-binutils-windows";
  version = binutilsVersion;

  src = binutilsSrc;
  patches = binutilsPatches;

  # buildCC provides the native compiler for build-time tools (e.g. bfd/doc/chew).
  depsBuildBuild = [ buildCC ];
  nativeBuildInputs = [ texinfo bison flex ];
  buildInputs = [ zlib ];

  configureFlags = [
    "--target=mips-linux-gnu"
    "--disable-nls"
    "--disable-werror"
    "--disable-gdb"
    "--disable-sim"
    "--disable-readline"
    "--with-sysroot=/dev/null"
  ];

  enableParallelBuilding = true;

  postInstall = ''
    rm -rf $out/share $out/lib $out/include
    find $out/bin -name '*.exe' -exec x86_64-w64-mingw32-strip {} +
  '';
}
