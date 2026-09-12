# Build GCC for mips-linux-gnu, natively, from source (only the driver and
# frontends, i.e. `make all-gcc` - not target libgcc/libstdc++). See
# tools/unix/binutils.nix for why this is built from source rather than via
# nixpkgs' pkgsCross wrapper.
{
  stdenv,
  buildCC,
  gccSrc,
  gccPatches,
  gccVersion,
  mips-binutils,
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
  pname = "mips-gcc";
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

  # Place binutils at the standard GCC search path (<prefix>/mips-linux-gnu/bin/)
  # so GCC finds them via relative lookup instead of hardcoded nix store paths.
  preConfigure = ''
    export gcc_cv_as_compress_debug=1
    export gcc_cv_ld_compress_debug=1
    mkdir -p $out/mips-linux-gnu/bin
    for tool in ${mips-binutils}/bin/mips-linux-gnu-*; do
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
}
