#!/bin/sh
# Downloads and activates the pre-built macOS/Linux toolchain for the
# current platform, if it isn't already present and up to date. Mirrors
# tools/windows/download_toolchain.bat.
set -e

CANONICAL_URL="https://github.com/bates64/papermario-dx.git"
S3_BASE="https://fsn1.your-objectstorage.com/starhaven/papermario-dx"
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
DX_DIR="$ROOT/.dx"
TOOLCHAIN_DIR="$DX_DIR/unix"
TOOLCHAIN_ZIP="$DX_DIR/papermario-dx-unix.zip"
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

if ! command -v git >/dev/null 2>&1; then
  echo "Error: this needs git to find the toolchain version to download (even in a jj repo)." >&2
  echo "Install git: https://git-scm.com/" >&2
  exit 1
fi

# Find the current commit: prefer jj if this is a jj repo, otherwise git.
if [ -d "$ROOT/.jj" ] && command -v jj >/dev/null 2>&1; then
  CURRENT=$(jj -R "$ROOT" log -r @ --no-graph -T 'commit_id' 2>/dev/null)
else
  CURRENT=$(git -C "$ROOT" rev-parse HEAD 2>/dev/null || true)
fi

if [ -z "$CURRENT" ]; then
  echo "Error: could not determine the current commit." >&2
  exit 1
fi

# Toolchains are only published for commits on dx's main branch. Since users
# branch away from main, walking back from the current commit alone would
# just walk through their own commits, none of which are published. Fetching
# main and taking the merge-base finds the point where their history
# actually meets dx's, wherever they've branched from.
BASE="$CURRENT"
if [ -d "$ROOT/.git" ]; then
  git -C "$ROOT" fetch --quiet "$CANONICAL_URL" main 2>/dev/null || true
  MAIN_HASH=$(git -C "$ROOT" rev-parse FETCH_HEAD 2>/dev/null || true)
  if [ -n "$MAIN_HASH" ]; then
    MERGE_BASE=$(git -C "$ROOT" merge-base "$CURRENT" "$MAIN_HASH" 2>/dev/null || true)
    [ -n "$MERGE_BASE" ] && BASE="$MERGE_BASE"
  fi
fi

# Walk back from there until a published toolchain is found - a commit's
# build can be missing if CI failed for it.
HASH=""
COMMIT=""
if [ -d "$ROOT/.git" ]; then
  CANDIDATES=$(git -C "$ROOT" log --format=%H -n 20 "$BASE" 2>/dev/null || echo "$BASE")
else
  CANDIDATES="$BASE"
fi
for commit in $CANDIDATES; do
  candidate=$(curl -fsL "$S3_BASE/commits/$commit/$PLATFORM" 2>/dev/null || true)
  if [ -n "$candidate" ]; then
    HASH="$candidate"
    COMMIT="$commit"
    break
  fi
done

if [ -z "$HASH" ]; then
  echo "Error: no published $PLATFORM toolchain found near commit $BASE." >&2
  echo "The downloadable toolchain requires a build published from dx's main branch." >&2
  exit 1
fi

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

  rm -rf "$TOOLCHAIN_DIR" "$TOOLCHAIN_ZIP"

  URL="$S3_BASE/toolchains/$HASH.zip"
  if ! curl -fL -o "$TOOLCHAIN_ZIP" "$URL"; then
    echo "Error: failed to download toolchain from $URL" >&2
    exit 1
  fi

  echo "Extracting toolchain..." >&2
  if command -v unzip >/dev/null 2>&1; then
    unzip -q "$TOOLCHAIN_ZIP" -d "$DX_DIR"
  else
    tar -xf "$TOOLCHAIN_ZIP" -C "$DX_DIR"
  fi
  mv "$DX_DIR/papermario-dx-$PLATFORM" "$TOOLCHAIN_DIR"
  rm -f "$TOOLCHAIN_ZIP"

  echo "Activating toolchain..." >&2
  if [ "$OS" = "macos" ] && ! command -v install_name_tool >/dev/null 2>&1; then
    echo "Error: install_name_tool is not installed. Install the Xcode Command Line Tools with: xcode-select --install" >&2
    exit 1
  fi
  "$TOOLCHAIN_DIR/activate.sh" "$TOOLCHAIN_DIR"

  echo "$HASH" > "$HASH_FILE"
fi
