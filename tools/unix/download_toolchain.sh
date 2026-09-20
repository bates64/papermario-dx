#!/bin/sh
# Downloads and activates the pre-built macOS/Linux toolchain for the
# current platform, if it isn't already present and up to date. Mirrors
# tools/windows/download_toolchain.bat.
set -e

REPO="bates64/papermario-dx"
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
DX_DIR="$ROOT/.dx"
TOOLCHAIN_DIR="$DX_DIR/unix"
TOOLCHAIN_ZIP="$DX_DIR/papermario-dx-unix.zip"
TAG_FILE="$DX_DIR/unix-tag"

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
ASSET="papermario-dx-$PLATFORM.zip"

mkdir -p "$DX_DIR"

# Get the nearest dx-* tag (current commit or ancestor): prefer jj if this is
# a jj repo, otherwise fall back to git.
if [ -d "$ROOT/.jj" ] && command -v jj >/dev/null 2>&1; then
  TAG=$(jj -R "$ROOT" log -r 'latest(tags(glob:"dx-*") & ::@)' --no-graph -T 'self.tags().join("\n")' 2>/dev/null | head -n1)
  TAG_HASH=$(jj -R "$ROOT" log -r 'latest(tags(glob:"dx-*") & ::@)' --no-graph -T 'commit_id' 2>/dev/null)
elif command -v git >/dev/null 2>&1; then
  TAG=$(git -C "$ROOT" describe --tags --abbrev=0 --match 'dx-*' 2>/dev/null || true)
  # Resolve to the commit hash the tag points to, so a force-moved tag (e.g. a
  # rolling dx-nightly) is detected as an update rather than reused from cache.
  TAG_HASH=$(git -C "$ROOT" rev-parse "$TAG^{}" 2>/dev/null || true)
else
  echo "Error: this needs jj or git to find the toolchain version to download." >&2
  echo "Install jj (https://jj-vcs.github.io/jj/latest/install-and-setup/) or git (https://git-scm.com/)." >&2
  exit 1
fi

if [ -z "$TAG" ]; then
  echo "Error: no dx-* tag found in the commit history." >&2
  echo "The downloadable toolchain requires a tagged release with a pre-built toolchain." >&2
  exit 1
fi

NEED_DOWNLOAD=0
if [ ! -x "$TOOLCHAIN_DIR/bin/mips-linux-gnu-gcc" ]; then
  NEED_DOWNLOAD=1
fi
if [ -f "$TAG_FILE" ]; then
  CURRENT_TAG=$(cat "$TAG_FILE")
  if [ "$CURRENT_TAG" != "$TAG_HASH" ]; then
    NEED_DOWNLOAD=1
  fi
elif [ -d "$TOOLCHAIN_DIR" ]; then
  NEED_DOWNLOAD=1
fi

if [ "$NEED_DOWNLOAD" = "1" ]; then
  echo "Downloading toolchain for $TAG ($PLATFORM)..." >&2

  rm -rf "$TOOLCHAIN_DIR" "$TOOLCHAIN_ZIP"

  URL="https://github.com/$REPO/releases/download/$TAG/$ASSET"
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

  echo "$TAG_HASH" > "$TAG_FILE"
fi
