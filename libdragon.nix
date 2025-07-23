{
  runCommand,
  stdenv,

  n64Pkgs,
  libdragon,
}:

let
  buildEnv = runCommand "libdragon-build-env" { } ''
    mkdir -p $out/bin
    ln -s ${n64Pkgs.buildPackages.binutils}/bin/mips64-elf-* $out/bin/
    ln -s ${n64Pkgs.buildPackages.gcc}/bin/mips64-elf-{gcc,g++} $out/bin/
  '';

  # Anything that doesn't need a MIPS toolchain to build
  basicToolNames = [
    "n64tool"
    "n64sym"
    "ed64romconfig"
    "mkdfs"
    "dumpdfs"
    "mkasset"
    "n64dso"
    "n64dso-msym"
    "n64dso-extern"
  ];

  # Tools that need a MIPS toolchain to build
  mipsToolNames = [
    "n64elfcompress"
  ];

  makeTool = withBuildEnv: name: stdenv.mkDerivation {
    pname = name;
    version = libdragon.shortRev;
    src = libdragon;
    sourceRoot = "source/tools";
    enableParallelBuilding = true;
    passthru.toolName = name;
    preBuild = if withBuildEnv then "export N64_INST=${buildEnv}" else "";
    buildFlags = name;
    installTargets = "N64_INST=$(out) ${name}-install";
    NIX_CFLAGS_COMPILE = "-Wno-error";
  };

  makeBasicTool = makeTool false;
  makeMipsTool = makeTool true;

  tools =
    (map makeBasicTool basicToolNames) ++
    (map makeMipsTool mipsToolNames);

  lib = stdenv.mkDerivation {
    pname = "libdragon-lib";
    version = libdragon.shortRev;

    src = libdragon;
    enableParallelBuilding = true;
    buildFlags = "N64_INST=${buildEnv}";
    installFlags = "N64_INST=${builtins.placeholder "out"}";
  };
in {
  inherit lib tools buildEnv;
}
