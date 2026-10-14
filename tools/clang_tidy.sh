#!/usr/bin/env bash
# Runs clang-tidy on every file in compile_commands.json, failing on any
# warning. This includes the compiler warnings clangd shows.
#
# Given the files a change touched, it checks only those, if each is a compiled
# source file or can't reach the compiler, such as documentation. Any other
# file can affect sources it isn't part of, such as a header, a message or XML
# file that a header is generated from, or a clang-tidy setting, so a change
# touching one checks every file.
set -euo pipefail

cd "$(dirname "$0")/.."

python3 - "$@" <<'PY' | xargs -r -P "$(getconf _NPROCESSORS_ONLN)" -n 20 clang-tidy -p . --quiet --warnings-as-errors='*'
import json, os, sys

units = {
    os.path.relpath(os.path.join(entry["directory"], entry["file"]))
    for entry in json.load(open("compile_commands.json"))
}

changed = [os.path.normpath(path) for path in sys.argv[1:]]
if changed and all(path in units or path.endswith(".md") for path in changed):
    files = units.intersection(changed)
else:
    files = units
for file in sorted(files):
    print(file)
PY
