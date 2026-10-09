{
  stdenv,
  buildCC,
  gdbSrc,
  gdbVersion,
  python-windows,
  fetchurl,
  unzip,
  writeShellScript,
  texinfo,
  bison,
  flex,
  gmp,
  mpfr,
  expat,
  zlib,
}:

let
  # Python's headers, from python.org's NuGet package of the same CPython the
  # toolchain's embeddable Python is. The embeddable one has none.
  pythonDev = fetchurl {
    url = "https://api.nuget.org/v3-flatcontainer/python/${python-windows.version}/python.${python-windows.version}.nupkg";
    hash = "sha256-qPj2fTbAmHh+hFB5xT8Odg0oQRhtGj+HwuxkaFJ8EBc=";
  };

  # Stands in for python-config, which gdb's configure runs through the Python
  # it's given, as "<python> python-config.py --includes" and so on. No
  # --exec-prefix, so gdb leaves Python to find its home from its DLL.
  pythonConfig = writeShellScript "python-config" ''
    case "$2" in
      --includes) echo "-I$NIX_BUILD_TOP/python-dev/tools/include" ;;
      --ldflags) echo "-L${python-windows} -lpython313" ;;
    esac
  '';
in
stdenv.mkDerivation {
  pname = "mips-gdb-windows";
  version = gdbVersion;

  src = gdbSrc;

  hardeningDisable = [ "format" ];

  # buildCC provides the native compiler for build-time tools.
  depsBuildBuild = [ buildCC ];
  nativeBuildInputs = [ texinfo bison flex unzip ];
  buildInputs = [ gmp mpfr expat zlib ];

  postUnpack = ''
    unzip -q ${pythonDev} 'tools/include/*' -d python-dev
  '';

  configureFlags = [
    "--target=mips-linux-gnu"
    "--with-python=${pythonConfig}"
    "--with-expat"
    "--with-libgmp-prefix=${gmp.dev}"
    "--with-libmpfr-prefix=${mpfr.dev}"
    "--disable-nls"
    "--disable-werror"
    "--disable-sim"
    "--disable-gdbserver"
    "--disable-tui"
    "--without-debuginfod"
    "--without-babeltrace"
    "--without-xxhash"
    "--disable-source-highlight"
  ];

  enableParallelBuilding = true;

  # Python finds its standard library next to the DLL it loads from, so gdb
  # gets its own copy of both, and of the C runtime the DLL needs.
  postInstall = ''
    rm -rf $out/share/info $out/share/man $out/include $out/lib
    cp ${python-windows}/python313.dll ${python-windows}/python313.zip ${python-windows}/vcruntime140*.dll $out/bin/
    find $out/bin -name 'mips-linux-gnu-*.exe' -exec x86_64-w64-mingw32-strip {} +
  '';
}
