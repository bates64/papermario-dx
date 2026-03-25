{ lib, stdenv, fetchurl, autoPatchelfHook, libgcc, unzip }:

let
  version = "21.1.8";
  systems = {
    x86_64-linux = {
      url = "https://github.com/clangd/clangd/releases/download/${version}/clangd_indexing_tools-linux-${version}.zip";
      hash = "sha256-fFoSY1zp4/B5B4kxGgvNPTIFRRz6jJjIsj0FDIIBkyA=";
    };
  };
  platform = systems.${stdenv.hostPlatform.system}
    or (throw "clangd-indexing-tools: unsupported system ${stdenv.hostPlatform.system}");
in
stdenv.mkDerivation {
  pname = "clangd-indexing-tools";
  inherit version;

  src = fetchurl {
    inherit (platform) url hash;
  };

  sourceRoot = "clangd_${version}";

  nativeBuildInputs = [ autoPatchelfHook unzip ];
  buildInputs = [ stdenv.cc.cc.lib libgcc ];

  installPhase = ''
    mkdir -p $out/bin
    cp bin/* $out/bin/
  '';

  meta = {
    description = "clangd indexing tools (clangd-indexer, clangd-index-server)";
    homepage = "https://github.com/clangd/clangd";
    license = lib.licenses.asl20;
    platforms = builtins.attrNames systems;
  };
}
