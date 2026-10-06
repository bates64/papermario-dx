#!/usr/bin/env python3
"""Exercise the actual area/stage loaders and debug previews with a mock overlay store."""

import os
from pathlib import Path
import shutil
import subprocess
import tempfile

from evt_runtime import ROOT, run, run_expect_failure


def main():
    cc = shutil.which("gcc")
    if cc is None:
        raise SystemExit("gcc was not found on PATH")
    flags = [
        "-std=gnu11", "-D_MIPS_SZLONG=64", "-D_LANGUAGE_C", "-DMODERN_COMPILER",
        "-DNON_MATCHING", "-DDEBUG", "-Iver/us/include", "-Iver/us/build/include",
        "-Iinclude", "-Isrc", "-Iassets/us", "-include", "common.h",
        "-ffunction-sections", "-fdata-sections", "-fno-pie",
        "-fsanitize=address,undefined", "--param=asan-globals=0",
        "-Wno-attributes", "-Wno-builtin-declaration-mismatch",
        "-Wno-incompatible-pointer-types",
    ]
    sources = [
        ROOT / "src/battle.c",
        ROOT / "src/battle/181810.c",
        ROOT / "src/dx/debug_menu.c",
        Path(__file__).with_suffix("") / "runtime_test.c",
    ]
    with tempfile.TemporaryDirectory(prefix="battle_area_runtime_", dir="/tmp") as directory:
        temp = Path(directory)
        objects = []
        for i, source in enumerate(sources):
            obj = temp / f"source_{i}.o"
            run([cc, *flags, "-c", str(source), "-o", str(obj)])
            objects.append(str(obj))
        executable = temp / "runtime_test"
        run([cc, "-no-pie", "-Wl,--gc-sections", "-fsanitize=address,undefined",
             *objects, "-lm", "-o", str(executable)])
        env = os.environ.copy()
        # LeakSanitizer cannot run under the sandbox's ptrace-based runner.
        # The fixture explicitly checks that every mock module was released.
        env["ASAN_OPTIONS"] = "detect_leaks=0"
        env["UBSAN_OPTIONS"] = "halt_on_error=1:print_stacktrace=1"
        run([str(executable)], env=env)
        for mode, message in [
            ("--invalid-area", "Invalid battle area"),
            ("--invalid-battle", "Invalid battle"),
            ("--invalid-stage", "Invalid stage"),
            ("--double-load", "Previous battle area was not unloaded"),
            ("--missing-export", "has no gBattleArea export"),
            ("--invalid-animation", "Invalid battle animation"),
        ]:
            run_expect_failure([str(executable), mode], message, env=env)


if __name__ == "__main__":
    try:
        main()
    except subprocess.CalledProcessError:
        raise SystemExit(1)
