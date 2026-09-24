# clangd, clang-tidy, and clang-format from an LLVM release, with clang's
# built-in headers.
{ lib, stdenv, fetchurl, autoPatchelfHook, unzip, zlib, version }:

let
  system = stdenv.hostPlatform.system;

  # Only the tools and headers are unpacked, so the release archive itself,
  # which is over a gigabyte, never reaches the store.
  release = platform: hash: fetchurl {
    url = "https://github.com/llvm/llvm-project/releases/download/llvmorg-${version}/LLVM-${version}-${platform}.tar.xz";
    inherit hash;
    downloadToTemp = true;
    recursiveHash = true;
    postFetch = ''
      mkdir $out
      tar -xJf $downloadedFile -C $out --strip-components=1 --wildcards \
        '*/bin/clangd' '*/bin/clang-tidy' '*/bin/clang-format' '*/lib/clang/*/include'
    '';
  };

  # LLVM has no x86_64 macOS release. clangd's own release has a universal
  # macOS build, and clang-tidy and clang-format come from their PyPI wheels.
  # The newest clang-tidy wheel is 21.1.6.
  isIntelMac = system == "x86_64-darwin";
  clangdMac = fetchurl {
    url = "https://github.com/clangd/clangd/releases/download/${version}/clangd-mac-${version}.zip";
    hash = "sha256-tDXo7/m7jbWdbw+HSzprHPqqlJgOCOOPD6AV3eGF020=";
  };
  intelMacWheels = [
    (fetchurl {
      url = "https://files.pythonhosted.org/packages/73/59/cef36a88d30ed6dfc7237b3a9fa7de062726b4f30aeacf3e0e0316eee41e/clang_tidy-21.1.6-py2.py3-none-macosx_10_9_x86_64.whl";
      hash = "sha256-Ny8gJn5n9Bt1iwwgCeRgfxtT++5ACS522jEhSR1DmYU=";
    })
    (fetchurl {
      url = "https://files.pythonhosted.org/packages/17/1d/4b1d85acb99a2ee3bad0b20cc3e82c58fbfb39bf4dd5856ac1f2c4f36e65/clang_format-21.1.8-py2.py3-none-macosx_10_9_x86_64.whl";
      hash = "sha256-9EcJHDRgJ6CXKKCpYSj+BYQZ/gbPIAzMPcmLzUOZ41E=";
    })
  ];

  sources = {
    x86_64-linux = release "Linux-X64" "sha256-S9VsguQgv6TTYMbTF0797M3qtlD+ncBL/kKEtjJdZO4=";
    aarch64-linux = release "Linux-ARM64" "sha256-rmxYynnR9nxmAEeJxEZOtAKbJXT0VzwjkIJABCB6QdA=";
    aarch64-darwin = release "macOS-ARM64" "sha256-+zi8lTOLkb0FDkD4Bcqm6B/cERAK92Y/5NKfWcmb5SQ=";
    x86_64-darwin = clangdMac;
  };
in
stdenv.mkDerivation {
  pname = "llvm-tools";
  inherit version;

  src = sources.${system} or (throw "llvm: unsupported system ${system}");

  nativeBuildInputs = lib.optionals isIntelMac [ unzip ]
    ++ lib.optionals stdenv.isLinux [ autoPatchelfHook ];
  buildInputs = lib.optionals stdenv.isLinux [ stdenv.cc.cc.lib zlib ];

  installPhase = ''
    mkdir -p $out
    cp -r bin lib $out/
  '' + lib.optionalString isIntelMac ''
    for wheel in ${lib.escapeShellArgs intelMacWheels}; do
      unzip -q "$wheel" '*/data/bin/*' -d wheels
    done
    cp wheels/*/data/bin/* $out/bin/
  '';

  meta = {
    homepage = "https://llvm.org";
    license = lib.licenses.asl20;
    platforms = builtins.attrNames sources;
  };
}
