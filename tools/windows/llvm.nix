# clangd, clang-tidy, and clang-format from the LLVM release installer, with
# clang's built-in headers. Only those are unpacked, so the installer itself
# never reaches the store.
{ lib, fetchurl, p7zip, version }:

fetchurl {
  name = "llvm-tools-windows-${version}";
  url = "https://github.com/llvm/llvm-project/releases/download/llvmorg-${version}/LLVM-${version}-win64.exe";
  hash = "sha256-Qz1ehvmKpKpPgCF6T1MOQF3aplMZv6TmzXGV4MHRQIw=";
  downloadToTemp = true;
  recursiveHash = true;
  nativeBuildInputs = [ p7zip ];
  postFetch = ''
    7z x $downloadedFile -o$out bin/clangd.exe bin/clang-tidy.exe bin/clang-format.exe \
      lib/clang/${lib.versions.major version}/include
  '';
}
