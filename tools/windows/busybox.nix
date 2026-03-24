# Pre-built busybox for Windows (64-bit).
# Provides Unix utilities (cp, mkdir, rm, etc.) needed by the build system.
{
  fetchurl,
  runCommand,
}:

let
  exe = fetchurl {
    url = "https://frippery.org/files/busybox/busybox-w64-FRP-5857-g3681e397f.exe";
    sha256 = "00dr5rj30qhfi5xaibw658rxnx7gkmwnkagrkyb7ksmdk2nbzqhf";
  };
in
runCommand "busybox-windows" {} ''
  mkdir -p $out/bin
  cp ${exe} $out/bin/busybox.exe
''
