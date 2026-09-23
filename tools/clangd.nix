{ lib, stdenv, fetchurl, autoPatchelfHook, libgcc, unzip, version }:

let
  systems = {
    x86_64-linux = {
      url = "https://github.com/clangd/clangd/releases/download/${version}/clangd-linux-${version}.zip";
      hash = "sha256-4LIUpZkG387vM0Boc8Q3n7jnaPtDRdivp/MHvS7Imd4=";
    };
    aarch64-darwin = {
      url = "https://github.com/clangd/clangd/releases/download/${version}/clangd-mac-${version}.zip";
      hash = "sha256-tDXo7/m7jbWdbw+HSzprHPqqlJgOCOOPD6AV3eGF020=";
    };
    x86_64-darwin = systems.aarch64-darwin;
  };
  platform = systems.${stdenv.hostPlatform.system}
    or (throw "clangd: unsupported system ${stdenv.hostPlatform.system}");
in
stdenv.mkDerivation {
  pname = "clangd";
  inherit version;

  src = fetchurl {
    inherit (platform) url hash;
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
    description = "clangd";
    homepage = "https://github.com/clangd/clangd";
    license = lib.licenses.asl20;
    platforms = builtins.attrNames systems;
  };
}
