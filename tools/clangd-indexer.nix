# clangd-indexer, built from LLVM's source. clangd's releases only have it for
# x86_64, so this is how other machines get it. Its index is only loaded by a
# clangd of the same version, so the version here is the one tools/llvm.nix
# gives users. It builds nothing else of LLVM, but that is still most of Clang,
# so the result is worth caching.
{
  lib,
  stdenv,
  fetchurl,
  cmake,
  ninja,
  python3,
  zlib,
  version,
  hash ? "sha256-RjOiNhf6MaPqUSQlhup/sdpxQOQmvWL8FkJh/gNqoUI=",
}:

stdenv.mkDerivation {
  pname = "clangd-indexer";
  inherit version;

  src = fetchurl {
    url = "https://github.com/llvm/llvm-project/releases/download/llvmorg-${version}/llvm-project-${version}.src.tar.xz";
    inherit hash;
  };
  sourceRoot = "llvm-project-${version}.src/llvm";

  nativeBuildInputs = [ cmake ninja python3 ];
  buildInputs = [ zlib ];

  cmakeFlags = [
    "-DCMAKE_BUILD_TYPE=Release"
    "-DLLVM_ENABLE_PROJECTS=clang;clang-tools-extra"
    # Indexing only parses code, so no code generator is needed.
    "-DLLVM_TARGETS_TO_BUILD=Native"
    "-DLLVM_ENABLE_ASSERTIONS=OFF"
    "-DLLVM_ENABLE_ZLIB=ON"
    "-DLLVM_ENABLE_ZSTD=OFF"
    "-DLLVM_ENABLE_LIBXML2=OFF"
    "-DLLVM_INCLUDE_TESTS=OFF"
    "-DLLVM_INCLUDE_BENCHMARKS=OFF"
    "-DLLVM_INCLUDE_EXAMPLES=OFF"
    "-DLLVM_INCLUDE_DOCS=OFF"
    "-DCLANG_INCLUDE_TESTS=OFF"
    "-DCLANG_INCLUDE_DOCS=OFF"
    # clangd links these in for features the indexer doesn't use, and they are
    # about half of what would otherwise be built.
    "-DCLANGD_TIDY_CHECKS=OFF"
    "-DCLANG_ENABLE_STATIC_ANALYZER=OFF"
    "-DCLANG_ENABLE_ARCMT=OFF"
    # Linking Clang's libraries takes several gigabytes each.
    "-DLLVM_PARALLEL_LINK_JOBS=1"
    # The spindle gives a build 6 GB, and compiling Clang's Sema takes
    # more than one gigabyte per job.
    "-DLLVM_PARALLEL_COMPILE_JOBS=3"
  ];

  # Without the target, Nix would build all of LLVM and Clang.
  ninjaFlags = [ "clangd-indexer" "clang-resource-headers" ];
  dontUseCmakeInstall = true;

  # clangd-indexer finds Clang's built-in headers in ../lib/clang/ relative to
  # itself.
  installPhase = ''
    runHook preInstall
    mkdir -p $out/bin $out/lib/clang
    cp bin/clangd-indexer $out/bin/
    cp -r lib/clang/* $out/lib/clang/
    runHook postInstall
  '';

  meta = {
    homepage = "https://clangd.llvm.org";
    license = lib.licenses.asl20;
  };
}
