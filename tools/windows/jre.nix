# Pre-built Eclipse Temurin JRE for Windows (64-bit). Runs Star Rod's jar.
{
  fetchurl,
  unzip,
  stdenvNoCC,
}:

let
  version = "17.0.20.1+1";
  releaseTag = "jdk-17.0.20.1%2B1";
  jreZip = fetchurl {
    url = "https://github.com/adoptium/temurin17-binaries/releases/download/${releaseTag}/OpenJDK17U-jre_x64_windows_hotspot_17.0.20.1_1.zip";
    sha256 = "bc21a93923103cdaac93ee337b0ae4365e739fde36df823dd456bc67c8a9d352";
  };
in
stdenvNoCC.mkDerivation {
  pname = "jre-windows";
  inherit version;
  dontUnpack = true;

  nativeBuildInputs = [ unzip ];

  installPhase = ''
    mkdir -p $out
    unzip -q ${jreZip} -d $out
    mv $out/jdk-17.0.20.1+1-jre/* $out/
    rmdir $out/jdk-17.0.20.1+1-jre
  '';
}
