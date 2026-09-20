#!/usr/bin/env bash
set -e

ROOT="$(cd "$(dirname "$0")" && pwd)"
TOOLCHAIN_DIR="$ROOT/.dx/unix"

# If mips-linux-gnu-gcc isn't already on PATH (e.g. via `nix develop`),
# download the pre-built toolchain and use that instead.
if ! command -v mips-linux-gnu-gcc >/dev/null 2>&1; then
  "$ROOT/tools/unix/download_toolchain.sh"
  export PATH="$TOOLCHAIN_DIR/bin:$PATH"
  export PYTHONPATH="$TOOLCHAIN_DIR/python:$PYTHONPATH"
fi

if [ ! -f "$ROOT/build.ninja" ]; then
  echo "Running configure..."
  "$ROOT/configure"
fi

exec ninja "$@"
