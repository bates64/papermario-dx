#!/usr/bin/env python3

from __future__ import annotations

import argparse
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
SUITE_ROOT = Path(__file__).resolve().with_suffix("")
PASS_DIR = SUITE_ROOT / "pass"
FAIL_DIR = SUITE_ROOT / "fail"
VALIDATOR = ROOT / "tools/build/evt_validate_obj.py"
EFFECTS_YAML = ROOT / "src/registry/effects.yaml"


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Run fixture tests for evt_validate_obj.py")
    parser.add_argument("--filter", help="only run cases whose relative path contains this substring")
    parser.add_argument("--keep-temp", action="store_true", help="keep compiled test objects")
    parser.add_argument("--stamp", type=Path, help="write a stamp file on success")
    parser.add_argument("--version", default="us", help="asset/include version to compile against (default: us)")
    return parser.parse_args()


def required_substrings(path: Path) -> list[str]:
    substrings = []
    for line in path.read_text().splitlines():
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        substrings.append(line)
    return substrings


def compiler_for_tests() -> str:
    compiler = shutil.which("mips-linux-gnu-gcc")
    if compiler is None:
        raise RuntimeError("mips-linux-gnu-gcc was not found on PATH")
    return compiler


def compile_command(compiler: str, version: str, source_rel: Path, object_path: Path) -> list[str]:
    version_upper = version.upper()
    return [
        compiler,
        "-c",
        "-EB",
        "-G0",
        "-g1",
        "-gdwarf",
        "-funsigned-char",
        "-mgp32",
        "-mfp32",
        "-mabi=32",
        "-mfix4300",
        "-march=vr4300",
        "-mno-gpopt",
        "-mno-abicalls",
        "-fno-pic",
        "-fno-exceptions",
        "-fno-stack-protector",
        "-fno-toplevel-reorder",
        "-fno-zero-initialized-in-bss",
        "-Wno-builtin-declaration-mismatch",
        f"-Iver/{version}/include",
        f"-Iver/{version}/build/include",
        "-Iinclude",
        "-Isrc",
        f"-Iassets/{version}",
        "-D_FINALROM",
        f"-DVERSION={version}",
        "-DF3DEX_GBI_2",
        "-D_MIPS_SZLONG=32",
        "-DNON_MATCHING",
        "-DDEBUG",
        "-DSHIFT",
        f"-DVERSION_{version_upper}",
        "-DMODERN_COMPILER",
        "-include",
        "common.h",
        "-D_LANGUAGE_C",
        str(source_rel),
        "-o",
        str(object_path),
    ]


def run_command(command: list[str]) -> subprocess.CompletedProcess[str]:
    return subprocess.run(
        command,
        cwd=ROOT,
        capture_output=True,
        text=True,
    )


def fixture_sources(root: Path, filter_text: str | None) -> list[Path]:
    sources = sorted(root.glob("*.c"))
    if filter_text is None:
        return sources
    return [path for path in sources if filter_text in str(path.relative_to(ROOT))]


def format_failure(case: str, message: str, stdout: str, stderr: str) -> str:
    parts = [f"{case}: {message}"]
    if stdout.strip():
        parts.append("stdout:")
        parts.append(stdout.rstrip())
    if stderr.strip():
        parts.append("stderr:")
        parts.append(stderr.rstrip())
    return "\n".join(parts)


def run_case(
    compiler: str,
    version: str,
    source: Path,
    should_pass: bool,
    temp_root: Path,
) -> str | None:
    source_rel = source.relative_to(ROOT)
    object_path = temp_root / source_rel.with_suffix(".o")
    object_path.parent.mkdir(parents=True, exist_ok=True)

    compile_result = run_command(compile_command(compiler, version, source_rel, object_path))
    if compile_result.returncode != 0:
        return format_failure(
            str(source_rel),
            "failed to compile fixture",
            compile_result.stdout,
            compile_result.stderr,
        )

    validate_result = run_command(
        [
            sys.executable,
            str(VALIDATOR),
            "--effects-yaml",
            str(EFFECTS_YAML),
            str(object_path),
        ]
    )
    if should_pass:
        if validate_result.returncode != 0:
            return format_failure(
                str(source_rel),
                "validator rejected passing fixture",
                validate_result.stdout,
                validate_result.stderr,
            )
        return None

    expected_path = source.with_suffix(".stderr")
    if not expected_path.exists():
        return f"{source_rel}: missing expected stderr file {expected_path.relative_to(ROOT)}"
    if validate_result.returncode == 0:
        return format_failure(
            str(source_rel),
            "validator unexpectedly accepted failing fixture",
            validate_result.stdout,
            validate_result.stderr,
        )

    stderr = validate_result.stderr
    missing = [text for text in required_substrings(expected_path) if text not in stderr]
    if missing:
        missing_lines = "\n".join(f"missing substring: {text}" for text in missing)
        return format_failure(
            str(source_rel),
            missing_lines,
            validate_result.stdout,
            validate_result.stderr,
        )
    return None


def main() -> int:
    args = parse_args()
    compiler = compiler_for_tests()
    temp_root = Path(tempfile.mkdtemp(prefix="evt_validate_obj_tests_", dir="/tmp"))
    failures: list[str] = []
    cases_run = 0

    try:
        for root, should_pass in ((PASS_DIR, True), (FAIL_DIR, False)):
            for source in fixture_sources(root, args.filter):
                cases_run += 1
                rel = source.relative_to(ROOT)
                print(f"[{cases_run:02d}] {rel}")
                failure = run_case(compiler, args.version, source, should_pass, temp_root)
                if failure is not None:
                    failures.append(failure)

        if cases_run == 0:
            print("No EVT validator test cases matched.", file=sys.stderr)
            return 1

        if failures:
            print(f"\n{len(failures)} EVT validator test(s) failed.\n", file=sys.stderr)
            for failure in failures:
                print(failure, file=sys.stderr)
                print("", file=sys.stderr)
            print(f"Kept temporary files in {temp_root}", file=sys.stderr)
            return 1

        if args.stamp:
            args.stamp.parent.mkdir(parents=True, exist_ok=True)
            args.stamp.write_text(f"{cases_run}\n")
        print(f"All {cases_run} EVT validator tests passed.")
        if args.keep_temp:
            print(f"Kept temporary files in {temp_root}")
        else:
            shutil.rmtree(temp_root)
        return 0
    except Exception:
        print(f"Kept temporary files in {temp_root}", file=sys.stderr)
        raise


if __name__ == "__main__":
    raise SystemExit(main())
