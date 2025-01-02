{ pkgsNative ? import <nixpkgs> {}
, pkgsCross ? import <nixpkgs> { crossSystem = { config = "mips-linux-gnu"; }; }
, pkgsCrossOld ? import (builtins.fetchTarball {
    # This commit uses binutils 2.39. We don't want binutils 2.40+ because of a performance regression in ld.
    url = "https://github.com/NixOS/nixpkgs/archive/55070e598e0e03d1d116c49b9eff322ef07c6ac6.tar.gz";
  }) { crossSystem = { config = "mips-linux-gnu"; }; }
}:

pkgsCross.mkShell {
  nativeBuildInputs = (with pkgsNative; [
    ninja
    zlib
    libyaml
    python3
    python3Packages.virtualenv
    cargo
    rustc
    ccache
    gdb
  ]);
  buildInputs = (with pkgsCross; [
    gcc
    pkgsCrossOld.binutils
  ]);
  shellHook = ''
    # Install Rust deps
    export PATH=$HOME/.cargo/bin:$PATH
    cargo install pigment64 crunch64-cli

    # Install python packages
    virtualenv venv
    source venv/bin/activate
    pip install -r ${./requirements.txt}
    pip install -r ${./requirements_extra.txt}

    # Use old ld (but not the rest of binutils)
    BINUTILS=$(find /nix/store -maxdepth 1 -name '*-mips-linux-gnu-binutils-2.39' | head -n 1)
    export PAPERMARIO_LD="$BINUTILS/bin/mips-linux-gnu-ld"

    # Confirm that ld is 2.39
    LD_VERSION=$($PAPERMARIO_LD --version | head -n 1)
    if [[ $LD_VERSION != *2.39* ]]; then
      echo "Expected $PAPERMARIO_LD to be 2.39, got $LD_VERSION"
    fi
  '';
}
