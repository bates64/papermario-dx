#!/usr/bin/env bash
set -e

ROOT="$(cd "$(dirname "$0")" && pwd)"
TOOLCHAIN_DIR="$ROOT/.dx/unix"

# If star-rod isn't already on PATH (e.g. via `nix develop`), download the
# pre-built toolchain and use that instead.
if command -v star-rod >/dev/null 2>&1; then
  exec star-rod "$@"
fi

"$ROOT/tools/unix/download_toolchain.sh"
exec "$TOOLCHAIN_DIR/bin/star-rod" "$@"
