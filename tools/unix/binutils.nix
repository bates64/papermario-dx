# Build binutils for mips-linux-gnu, natively, from source. Building from
# source (rather than using nixpkgs' auto-wrapped pkgsCross binutils) avoids
# wrapper scripts that hardcode /nix/store paths, so the result can be
# relocated by tools/unix/default.nix's activate.sh.
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
  pname = "mips-binutils";
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
    # Binutils' own bundled zlib is old enough that it fails to parse
    # current libc headers on some platforms (e.g. the macOS SDK's stdio.h).
    "--with-system-zlib"
  ];

  enableParallelBuilding = true;

  postInstall = ''
    rm -rf $out/share $out/lib $out/include
  '';
}
