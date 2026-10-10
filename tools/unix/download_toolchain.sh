#!/bin/sh
# Downloads and activates the pre-built macOS/Linux toolchain for the
# current platform, if it isn't already present and up to date. Mirrors
# tools/windows/download_toolchain.bat.
set -e

S3_BASE="https://fsn1.your-objectstorage.com/starhaven/papermario-dx"
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
DX_DIR="$ROOT/.dx"
TOOLCHAIN_DIR="$DX_DIR/unix"
TOOLCHAIN_ARCHIVE="$DX_DIR/papermario-dx-unix.tar.xz"
HASH_FILE="$DX_DIR/unix-hash"

case "$(uname -s)" in
  Linux) OS=linux ;;
  Darwin) OS=macos ;;
  *)
    echo "Error: unsupported OS $(uname -s). The downloadable toolchain only supports Linux and macOS." >&2
    exit 1
    ;;
esac

case "$(uname -m)" in
  x86_64 | amd64) ARCH=x86_64 ;;
  arm64 | aarch64) ARCH=aarch64 ;;
  *)
    echo "Error: unsupported architecture $(uname -m)." >&2
    exit 1
    ;;
esac

PLATFORM="$OS-$ARCH"

mkdir -p "$DX_DIR"

# The index lists every commit with published toolchains, with each one's
# hash, so finding the toolchain needs no fetch and works in shallow clones.
# The last copy downloaded is kept for building offline.
INDEX="$DX_DIR/index.txt"
if curl -fsL -o "$INDEX.new" "$S3_BASE/index.txt" 2>/dev/null; then
  mv "$INDEX.new" "$INDEX"
else
  rm -f "$INDEX.new"
fi
if [ ! -f "$INDEX" ]; then
  echo "Error: couldn't download the list of published toolchains from $S3_BASE/index.txt." >&2
  exit 1
fi
PUBLISHED="$DX_DIR/published.txt"
awk -v key="$PLATFORM.tar.xz" '$1 == "commit" && $3 == key { print $2 }' "$INDEX" > "$PUBLISHED"

# The newest published commit in the current history is where it meets dx's,
# wherever it's branched from. A commit CI failed for isn't in the index, so
# this finds the one before it.
if [ -d "$ROOT/.jj" ] && command -v jj >/dev/null 2>&1; then
  COMMIT=$(jj -R "$ROOT" log --no-graph -r "::@" -T 'commit_id ++ "\n"' 2>/dev/null | grep -Fx -m 1 -f "$PUBLISHED" || true)
elif command -v git >/dev/null 2>&1; then
  COMMIT=$(git -C "$ROOT" rev-list --topo-order HEAD 2>/dev/null | grep -Fx -m 1 -f "$PUBLISHED" || true)
else
  echo "Error: this needs jj or git to find the toolchain version to download." >&2
  echo "Install jj (https://jj-vcs.github.io/jj/latest/install-and-setup/) or git (https://git-scm.com/)." >&2
  exit 1
fi

if [ -z "$COMMIT" ]; then
  echo "Error: no commit in this history has a published $PLATFORM toolchain." >&2
  echo "Toolchains are kept for every dx release and dx's newest commits on main. Merge a dx release, then build again." >&2
  exit 1
fi
HASH=$(awk -v commit="$COMMIT" -v key="$PLATFORM.tar.xz" '$1 == "commit" && $2 == commit && $3 == key { print $4; exit }' "$INDEX")

NEED_DOWNLOAD=0
if [ ! -x "$TOOLCHAIN_DIR/bin/mips-linux-gnu-gcc" ]; then
  NEED_DOWNLOAD=1
fi
if [ -f "$HASH_FILE" ]; then
  [ "$(cat "$HASH_FILE")" != "$HASH" ] && NEED_DOWNLOAD=1
elif [ -d "$TOOLCHAIN_DIR" ]; then
  NEED_DOWNLOAD=1
fi

if [ "$NEED_DOWNLOAD" = "1" ]; then
  echo "Downloading toolchain for commit $COMMIT ($PLATFORM)..." >&2

  rm -rf "$TOOLCHAIN_DIR" "$TOOLCHAIN_ARCHIVE"

  URL="$S3_BASE/toolchains/$HASH.tar.xz"
  if ! curl -fL -o "$TOOLCHAIN_ARCHIVE" "$URL"; then
    echo "Error: failed to download toolchain from $URL" >&2
    exit 1
  fi

  echo "Extracting toolchain..." >&2
  tar -xJf "$TOOLCHAIN_ARCHIVE" -C "$DX_DIR"
  mv "$DX_DIR/papermario-dx-$PLATFORM" "$TOOLCHAIN_DIR"
  rm -f "$TOOLCHAIN_ARCHIVE"

  echo "Activating toolchain..." >&2
  if [ "$OS" = "macos" ] && ! command -v install_name_tool >/dev/null 2>&1; then
    echo "Error: install_name_tool is not installed. Install the Xcode Command Line Tools with: xcode-select --install" >&2
    exit 1
  fi
  "$TOOLCHAIN_DIR/activate.sh" "$TOOLCHAIN_DIR"

  echo "$HASH" > "$HASH_FILE"
fi
