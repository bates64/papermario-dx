{
  stdenv,
  buildCC,
  gccSrc,
  gccPatches,
  gccVersion,
  mips-binutils-windows,
  mipsCrossGcc,
  gmpSrc,
  mpfrSrc,
  mpcSrc,
  islSrc,
  texinfo,
  bison,
  flex,
  zlib,
}:

stdenv.mkDerivation {
  pname = "mips-gcc-windows";
  version = gccVersion;

  src = gccSrc;
  patches = gccPatches;

  hardeningDisable = [ "format" ];

  depsBuildBuild = [ buildCC ];
  nativeBuildInputs = [ texinfo bison flex ];
  buildInputs = [ zlib ];

  # Place prerequisite sources inside the GCC tree for in-tree build.
  # GCC's configure detects these directories and builds them automatically.
  postUnpack = ''
    pushd $sourceRoot
    tar xf ${gmpSrc} && mv gmp-* gmp
    tar xf ${mpfrSrc} && mv mpfr-* mpfr
    tar xf ${mpcSrc} && mv mpc-* mpc
    tar xf ${islSrc} && mv isl-* isl
    popd
  '';

  configureFlags = [
    "--target=mips-linux-gnu"
    "--with-headers=${mipsCrossGcc.libc.dev}/include"
    "--enable-languages=c,c++"
    "--with-arch=vr4300"
    "--with-tune=vr4300"
    "--with-abi=32"
    "--disable-shared"
    "--disable-threads"
    "--disable-tls"
    "--disable-multilib"
    "--disable-libssp"
    "--disable-libgomp"
    "--disable-libquadmath"
    "--disable-libatomic"
    "--disable-libsanitizer"
    "--disable-libvtv"
    "--disable-bootstrap"
    "--disable-nls"
    "--with-system-zlib"
  ];

  # GCC's configure can't run the Windows cross-assembler to test features.
  # Override cache variables so configure doesn't error.
  # Place binutils at the standard GCC search path (<prefix>/mips-linux-gnu/bin/)
  # so GCC finds them via relative lookup instead of hardcoded nix store paths.
  preConfigure = ''
    export gcc_cv_as_compress_debug=1
    export gcc_cv_ld_compress_debug=1
    mkdir -p $out/mips-linux-gnu/bin
    for tool in ${mips-binutils-windows}/bin/mips-linux-gnu-*.exe; do
      name=$(basename "$tool" | sed 's/^mips-linux-gnu-//')
      ln -s "$tool" $out/mips-linux-gnu/bin/$name
    done
    # Place glibc headers in the sysroot so GCC finds them during build
    mkdir -p $out/mips-linux-gnu/sys-include
    cp -rL ${mipsCrossGcc.libc.dev}/include/* $out/mips-linux-gnu/sys-include/
  '';

  enableParallelBuilding = true;

  buildPhase = ''
    runHook preBuild
    # The specs target runs mips-linux-gnu-gcc -dumpspecs, but in a Canadian
    # cross build the just-built compiler is a Windows .exe that can't run on
    # Linux. Provide the native MIPS cross-compiler so make can find it.
    export PATH="${mipsCrossGcc}/bin:$PATH"
    make all-gcc
    runHook postBuild
  '';

  installPhase = ''
    runHook preInstall
    make install-gcc DESTDIR=
    rm -rf $out/share $out/include
    # Keep lib/gcc/.../include (GCC built-in headers like stddef.h)
    # but remove libraries we don't need.
    find $out/lib -name '*.a' -delete 2>/dev/null || true
    find $out/lib -name '*.la' -delete 2>/dev/null || true
    runHook postInstall
  '';

  # Copy runtime DLLs alongside libexec executables (cc1.exe, cc1plus.exe, etc.)
  # so they can find them without requiring bin/ on PATH. This must run after
  # fixupPhase, which is when the mingw stdenv copies DLLs into bin/.
  postFixup = ''
    for dll in $out/bin/*.dll; do
      [ -f "$dll" ] && cp "$dll" $out/libexec/gcc/mips-linux-gnu/*/
    done
  '';
}
