# The standalone clangd editor binary, fetched from the same clangd/clangd
# release as clangd-indexing-tools.nix's clangd-indexer. Both must come from
# the same version: clangd's on-disk index format isn't stable across
# releases, and clangd refuses to load an index built by a mismatched
# version. Used in the devShell in place of nixpkgs' own clangd (whose
# version tracks nixpkgs, not this project's downloadable index).
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
    description = "clangd (matches the version that builds this project's downloadable index)";
    homepage = "https://github.com/clangd/clangd";
    license = lib.licenses.asl20;
    platforms = builtins.attrNames systems;
  };
}
