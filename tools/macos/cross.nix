# A C and C++ compiler and the usual binary tools, set up to build for macOS
# from Linux. They are LLVM's, pointed at the macOS SDK. Binaries made with
# them link only against the system libraries macOS ships, so they run
# wherever they're unpacked. LLVM's linker signs arm64 binaries ad hoc, which
# is all they need to run.
{
  lib,
  runCommand,
  llvmPackages_19,
  sdk,
  arch,
}:

let
  llvm = llvmPackages_19;
  clangArch = if arch == "aarch64" then "arm64" else "x86_64";
  flags = "-Qunused-arguments --target=${clangArch}-apple-macos11 -isysroot ${sdk} -fuse-ld=lld -B${llvm.lld}/bin -B$out/bin -resource-dir ${llvm.clang-unwrapped.lib}/lib/clang/${lib.versions.major llvm.clang-unwrapped.version}";
in
runCommand "macos-${arch}-cross-tools" { } ''
  mkdir -p $out/bin
  wrap() {
    printf '#!/bin/sh\nexec %s %s "$@"\n' "$2" "$3" > $out/bin/$1
    chmod +x $out/bin/$1
  }
  for name in cc gcc clang; do wrap $name ${llvm.clang-unwrapped}/bin/clang "${flags}"; done
  for name in c++ g++ clang++; do wrap $name ${llvm.clang-unwrapped}/bin/clang++ "${flags} -stdlib=libc++"; done
  wrap cpp ${llvm.clang-unwrapped}/bin/clang "${flags} -E"
  for tool in ar ranlib nm strip objdump otool lipo install_name_tool; do
    case $tool in
      otool) src=llvm-otool ;;
      install_name_tool) src=llvm-install-name-tool ;;
      *) src=llvm-$tool ;;
    esac
    ln -s ${llvm.llvm}/bin/$src $out/bin/$tool
  done
  # The linker driver runs it on binaries built with -g; the debug info is of no use here.
  printf '#!/bin/sh\n' > $out/bin/dsymutil
  chmod +x $out/bin/dsymutil
  ln -s ${llvm.lld}/bin/ld64.lld $out/bin/ld
''
