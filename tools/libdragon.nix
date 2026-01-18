{
  stdenv,
  inputs,
}:
let
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

  makeTool = name: stdenv.mkDerivation {
    pname = name;
    version = inputs.libdragon.shortRev;
    src = inputs.libdragon;
    sourceRoot = "source/tools";
    enableParallelBuilding = true;
    passthru.toolName = name;
    buildFlags = name;
    installTargets = "N64_INST=$(out) ${name}-install";
    NIX_CFLAGS_COMPILE = "-Wno-error";
  };
in {
  tools = (map makeTool basicToolNames);
  includePath = "${inputs.libdragon}/include";
}
