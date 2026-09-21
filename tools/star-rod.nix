# Builds StarRod.jar from the pinned upstream flake, reusing its own
# offline Gradle setup for reproducibility. Unlike upstream's own package,
# this doesn't wrap the jar with a JRE: each toolchain (tools/windows,
# tools/unix) bundles its own relocatable JRE and jar path instead, since
# the jar itself is plain platform-independent bytecode.
{
  starRod,
  system,
}:

let
  pkgs = import starRod.inputs.nixpkgs { inherit system; };
  gradleInit = (import starRod.inputs.gradle-dot-nix {
    inherit pkgs;
    gradle-verification-metadata-file = starRod + "/gradle/verification-metadata.xml";
  }).gradle-init;
  jdk = pkgs.jdk17;
  gradle = pkgs.gradle.override { java = jdk; };
in
pkgs.stdenv.mkDerivation {
  pname = "star-rod-jar";
  version = builtins.elemAt
    (builtins.match "^.*version=([[:digit:].]+).*$" (builtins.readFile (starRod + "/app.properties")))
    0;
  src = starRod;

  nativeBuildInputs = [ pkgs.unzip gradle jdk ];

  # The nix build sandbox has no locale set, so javac's default charset
  # resolves to US-ASCII and chokes on the UTF-8 source files. C.UTF-8 needs
  # no locale-gen/glibcLocales; javac only inspects the LANG string itself.
  LANG = "C.UTF-8";

  buildPhase = ''
    export GRADLE_USER_HOME="$TMPDIR/gradle-home"
    gradle createReleaseZip -I ${gradleInit} --offline --full-stacktrace
  '';

  installPhase = ''
    mkdir -p $out/share/java
    unzip -p build/release/StarRod-*.zip StarRod.jar > $out/share/java/StarRod.jar
  '';
}
