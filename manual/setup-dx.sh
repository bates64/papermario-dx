#!/usr/bin/env bash

set -e
trap cleanup EXIT

cleanup() {
    if [ $COMPLETE -eq 0 ]; then
        if [ -d $DX_DIR ]; then
            rm -rf $DX_DIR
        fi
    fi
}

PURPLE="\033[1;35m"
YELLOW='\033[1;33m'
RED="\033[1;31m"
GREEN='\033[1;32m'
RESET='\033[0m'

GIT_REPO="${GIT_REPO:-https://github.com/bates64/papermario-dx.git}"

DX_DIR="${DX_DIR:-$HOME/papermario-dx}"
DX_DIR="$(printf '%s\n' "$DX_DIR")" # Expand ~ in path

COMPLETE=0

echo -e "${PURPLE}This script will install Paper Mario DX in $DX_DIR.${RESET}"

# Check for $DX_DIR; if it exists, exit
if [ -d "$DX_DIR" ]; then
    COMPLETE=1
    echo -e "${RED}$DX_DIR already exists!${RESET}"
    echo -e "${RED}If you would like to reinstall, run the following command, then try again:${RESET}"
    echo -e "${YELLOW}    rm -rf $DX_DIR${RESET}"
    exit 1
fi

# Ensure Nix is installed
if ! command -v nix > /dev/null; then
    echo -e "${PURPLE}Installing Nix...${RESET}"
    sh <(curl -L https://nixos.org/nix/install) --no-daemon
fi

# Prompt for baserom
echo -e "${PURPLE}Drag and drop a Paper Mario (US) ROM file below, then press Enter.${RESET}"
read -r -p "> " baserom
# Some terminals wrap the path in quotes, so remove them
baserom="${baserom%\"}"
baserom="${baserom#\"}"
baserom="${baserom%\'}"
baserom="${baserom#\'}"
# Convert Windows path to Linux path
if command -v wslpath > /dev/null; then
    baserom=$(wslpath -u "$baserom")
fi
if [ ! -f "$baserom" ]; then
    echo -e "${RED}File not found: $baserom${RESET}"
    exit 1
fi
sha1=$(sha1sum "$baserom" | cut -d ' ' -f 1)
if [ "$sha1" != "3837f44cda784b466c9a2d99df70d77c322b97a0" ]; then
    echo -e "${RED}Bad ROM!${RESET}"
    echo -e "${RED}Make sure this is an unmodified Paper Mario (US) ROM.${RESET}"
    exit 1
fi

# Add baserom to Nix store
cd /tmp
cp "$baserom" papermario.us.z64
nix-store --add-fixed sha256 papermario.us.z64

# Clone the repository
git clone "$GIT_REPO" "$DX_DIR" --depth 1
cd "$DX_DIR"

# Prepare devshell
echo -e "${PURPLE}Downloading dependencies and splitting assets from ROM...${RESET}"
nix --extra-experimental-features "flakes nix-command" develop --profile .nix-profile --accept-flake-config --command ./configure

echo -e "${GREEN}Paper Mario DX has been installed in $DX_DIR!${RESET}"
COMPLETE=1

# Open in VS Code if available
code . || true
