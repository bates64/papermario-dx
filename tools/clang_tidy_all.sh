#!/usr/bin/env bash
# Runs clang-tidy on every file in compile_commands.json, failing on any
# warning. This includes the compiler warnings clangd shows.
set -euo pipefail

cd "$(dirname "$0")/.."

python3 -c '
import json
for file in sorted({entry["file"] for entry in json.load(open("compile_commands.json"))}):
    print(file)
' | xargs -P "$(getconf _NPROCESSORS_ONLN)" -n 20 clang-tidy -p . --quiet --warnings-as-errors='*'
