# Prebuilt binaries from a clangd/clangd release.
{ lib, stdenv, fetchurl, autoPatchelfHook, libgcc, unzip, version, archive }:

let
  hashes = {
    clangd_indexing_tools = {
      x86_64-linux = "sha256-fFoSY1zp4/B5B4kxGgvNPTIFRRz6jJjIsj0FDIIBkyA=";
    };
  };
  system = stdenv.hostPlatform.system;
  os = if stdenv.isDarwin then "mac" else "linux";
in
stdenv.mkDerivation {
  pname = lib.replaceStrings [ "_" ] [ "-" ] archive;
  inherit version;

  src = fetchurl {
    url = "https://github.com/clangd/clangd/releases/download/${version}/${archive}-${os}-${version}.zip";
    hash = hashes.${archive}.${system} or (throw "${archive}: unsupported system ${system}");
  };

  sourceRoot = "clangd_${version}";

  nativeBuildInputs = [ unzip ]
    ++ lib.optionals stdenv.isLinux [ autoPatchelfHook ];
  buildInputs = lib.optionals stdenv.isLinux [ stdenv.cc.cc.lib libgcc ];

  installPhase = ''
    mkdir -p $out
    cp -r bin lib $out/
  '';

  meta = {
    homepage = "https://github.com/clangd/clangd";
    license = lib.licenses.asl20;
    platforms = builtins.attrNames hashes.${archive};
  };
}
