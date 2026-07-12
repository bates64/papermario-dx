#!/usr/bin/env python3

from __future__ import annotations

import os
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
TEST_DIR = Path(__file__).resolve().with_suffix("")


def run(
    command: list[str],
    *,
    env: dict[str, str] | None = None,
    show_output: bool = True,
) -> None:
    result = subprocess.run(command, cwd=ROOT, env=env, text=True, capture_output=True)
    if result.returncode != 0:
        if result.stdout:
            print(result.stdout, end="", file=sys.stderr)
        if result.stderr:
            print(result.stderr, end="", file=sys.stderr)
        raise subprocess.CalledProcessError(result.returncode, command)
    if show_output and result.stdout:
        print(result.stdout, end="")


def run_expect_failure(command: list[str], expected: str, *, env: dict[str, str]) -> None:
    result = subprocess.run(command, cwd=ROOT, env=env, text=True, capture_output=True)
    if result.returncode == 0 or expected not in result.stderr or "stack-overflow" in result.stderr:
        if result.stdout:
            print(result.stdout, end="", file=sys.stderr)
        if result.stderr:
            print(result.stderr, end="", file=sys.stderr)
        raise subprocess.CalledProcessError(result.returncode, command)


def main() -> int:
    cc = shutil.which("gcc")
    if cc is None:
        print("gcc was not found on PATH", file=sys.stderr)
        return 1
    ninja = shutil.which("ninja")
    if ninja is None:
        print("ninja was not found on PATH", file=sys.stderr)
        return 1

    common_flags = [
        "-std=gnu11",
        "-D_MIPS_SZLONG=64",
        "-D_LANGUAGE_C",
        "-DMODERN_COMPILER",
        "-DNON_MATCHING",
        "-DDEBUG",
        "-Iver/us/include",
        "-Iver/us/build/include",
        "-Iinclude",
        "-Isrc",
        "-Iassets/us",
        "-include",
        "common.h",
        "-ffunction-sections",
        "-fdata-sections",
        "-falign-functions=16",
        "-fno-pie",
        "-fsanitize=address,undefined",
        "-Wno-attributes",
        "-Wno-builtin-declaration-mismatch",
        "-Wno-incompatible-pointer-types",
    ]
    sources = [
        ROOT / "src/evt/evt.c",
        ROOT / "src/evt/script_list.c",
        TEST_DIR / "runtime_test.c",
    ]

    try:
        validation_env = os.environ.copy()
        validation_env["CCACHE_DISABLE"] = "1"
        run([ninja, "validate_evt_us"], env=validation_env, show_output=False)
        print("Whole-project EVT validation passed.")
        with tempfile.TemporaryDirectory(prefix="evt_runtime_test_", dir="/tmp") as temp_dir:
            temp = Path(temp_dir)
            objects = []
            for source in sources:
                obj = temp / f"{source.stem}_{len(objects)}.o"
                run([cc, "-c", *common_flags, str(source), "-o", str(obj)])
                objects.append(obj)

            executable = temp / "runtime_test"
            run(
                [
                    cc,
                    "-no-pie",
                    "-Wl,--gc-sections",
                    "-fsanitize=address,undefined",
                    *(str(obj) for obj in objects),
                    "-o",
                    str(executable),
                ]
            )

            env = os.environ.copy()
            env["ASAN_OPTIONS"] = "detect_leaks=0"
            env["UBSAN_OPTIONS"] = "halt_on_error=1:print_stacktrace=1"
            run([str(executable)], env=env)
            run_expect_failure(
                [str(executable), "--error-finalizer"],
                "Command in Finally returned an error",
                env=env,
            )
            run_expect_failure(
                [str(executable), "--exec-wait-finalizer"],
                "Command is not allowed inside Finally",
                env=env,
            )
            run_expect_failure(
                [str(executable), "--call-start-owned-finalizer"],
                "owned child script",
                env=env,
            )
    except subprocess.CalledProcessError:
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
