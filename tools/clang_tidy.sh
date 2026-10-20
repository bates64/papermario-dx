#!/usr/bin/env bash
# Runs clang-tidy on every file in compile_commands.json, failing on any
# warning. This includes the compiler warnings clangd shows.
#
# Given the files a change touched, it checks the sources whose compile read
# any of them, directly or through a generated header, as the last build
# recorded. A change to clang-tidy's settings, to a file configure reads, to
# the tools, or to the toolchain checks every file, as does a change to anything
# but a source when there's no build to tell what reads it.
set -euo pipefail

cd "$(dirname "$0")/.."

python3 - "$@" <<'PY' | xargs -r -P "$(getconf _NPROCESSORS_ONLN)" -n 20 clang-tidy -p . --quiet --warnings-as-errors='*'
import json, os, subprocess, sys

SETTINGS = {".clang-tidy", ".clangd"}
EVERYTHING = {"flake.nix", "flake.lock"}

units = {
    os.path.relpath(os.path.join(entry["directory"], entry["file"]))
    for entry in json.load(open("compile_commands.json"))
}


def ninja_tool(*args):
    return subprocess.run(["ninja", "-t", *args], capture_output=True, text=True).stdout


def is_built(path):
    return path.startswith("ver/") and "/build/" in path


def readers():
    """Each file a unit's compile read, mapped to the units that read it, and
    each target in the deps log, such as a precompiled header, mapped to what it read."""
    read = {}
    recorded = {}
    deps = []
    target = None

    def finish():
        if target:
            recorded[target] = set(deps)
        unit = next((dep for dep in deps if dep in units), None)
        for dep in deps:
            if unit:
                read.setdefault(dep, set()).add(unit)

    for line in ninja_tool("deps").splitlines():
        if line.startswith(" "):
            deps.append(os.path.normpath(line.strip()))
        else:
            finish()
            deps = []
            target = os.path.normpath(line.split(":", 1)[0])
    finish()
    return read, recorded


def configure_inputs():
    """The files configure reads, which decide what is compiled and how."""
    return {path for path in generated_inputs({"build.ninja"})["build.ninja"] if os.path.isfile(path)}


def generated_inputs(targets):
    """Each built file among targets, and the built files they're made from, mapped to their inputs."""
    # A target with no build edge, such as a header configure writes, would
    # fail the whole query, and has no inputs to find.
    outputs = {os.path.normpath(line.rsplit(": ", 1)[0]) for line in ninja_tool("targets", "all").splitlines()}
    inputs = {}
    pending = sorted(targets)
    while pending:
        for target in pending:
            inputs.setdefault(target, set())
        queried = [target for target in pending if target in outputs]
        current = None
        in_inputs = False
        for line in ninja_tool("query", *queried).splitlines() if queried else []:
            if not line.startswith(" "):
                current = os.path.normpath(line.rstrip(":"))
                inputs[current] = set()
            elif line.startswith("  ") and not line.startswith("    "):
                in_inputs = line.strip().startswith("input:")
            elif in_inputs and not line.strip().startswith("||"):
                inputs[current].add(os.path.normpath(line.strip().removeprefix("| ")))
        for target in pending:
            inputs[target] |= recorded.get(target, set())
        pending = sorted({i for ins in inputs.values() for i in ins if is_built(i) and i not in inputs})
    return inputs


changed = {os.path.normpath(path) for path in sys.argv[1:]}
read, recorded = readers() if changed - units else ({}, {})
settings_changed = any(os.path.basename(path) in SETTINGS for path in changed)
tools_changed = any(path.startswith("tools/") for path in changed - units)
if not changed or settings_changed or tools_changed or changed & EVERYTHING or (changed - units and not read) or changed & configure_inputs():
    files = units
else:
    affected = set(changed)
    built = generated_inputs({path for path in read if is_built(path)})
    growing = True
    while growing:
        growing = False
        for output, inputs in built.items():
            if output not in affected and inputs & affected:
                affected.add(output)
                growing = True
    files = (changed & units).union(*(read.get(path, set()) for path in affected))
for file in sorted(files):
    print(file)
PY
