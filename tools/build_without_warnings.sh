#!/usr/bin/env bash
# Builds the game, failing if anything in the build prints a warning.
# Up-to-date targets don't rerun, so only this build's commands are checked.
set -euo pipefail

cd "$(dirname "$0")/.."

log=$(mktemp)
trap 'rm -f "$log"' EXIT
ninja 2>&1 | tee "$log"

# Strip GCC's color codes, which sit between the location and "warning:".
if sed 's/\x1b\[[0-9;]*[mK]//g' "$log" | grep -i 'warning:' >/dev/null; then
    echo "error: the build printed warnings" >&2
    exit 1
fi
