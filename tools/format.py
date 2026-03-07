#!/usr/bin/env python3

"""
C source formatter for the papermario-dx project.

Usage:
    tools/format.py [FILES...]          # format in-place
    tools/format.py --check [FILES...]  # exit 1 if changes needed
    cat file.c | tools/format.py        # stdin/stdout

Three kinds of code are formatted differently:

  Regular C code
    Formatted by clang-format (configured in .clang-format).

  EvtScript blocks
    clang-format destroys EvtScript because the macros expand to
    comma-separated array elements. EvtScript blocks are instead
    formatted with 4-space indentation based on control flow:

      Switch/SwitchConst          indent body, Case dedents to switch level
      If*/Else/EndIf              indent body
      Loop/EndLoop                indent body
      Thread/EndThread            indent body
      ChildThread/EndChildThread  indent body
      Preprocessor directives     stay at column 0
      Everything else             indented at current level

  Initializer lists (arrays and struct literals)
    clang-format repacks array items to fill lines, destroying
    intentional grouping (e.g. natural pairs, one-per-line lists).
    Initializer lists are preserved as-written, with minimal cleanup:

      - 4-space indentation normalised to brace nesting depth
      - Trailing whitespace stripped
      - Space ensured after commas
"""

import argparse
import os
import re
import subprocess
import sys
from enum import Enum, auto


class BlockKind(Enum):
    SWITCH = auto()
    CASE = auto()
    IF = auto()
    ELSE = auto()
    LOOP = auto()
    THREAD = auto()
    CHILD_THREAD = auto()


INDENT = "    "

SWITCH_MACROS = {"Switch", "SwitchConst"}

CASE_MACROS = {
    "CaseEq",
    "CaseNe",
    "CaseLt",
    "CaseGt",
    "CaseLe",
    "CaseGe",
    "CaseDefault",
    "CaseOrEq",
    "CaseAndEq",
    "CaseFlag",
    "CaseRange",
}

IF_MACROS = {"IfEq", "IfNe", "IfLt", "IfGt", "IfLe", "IfGe", "IfFlag", "IfNotFlag"}

MACRO_RE = re.compile(r"^\s*(\w+)")

# EvtScript declaration that opens a block (multi-line body)
EVT_OPEN_RE = re.compile(r"^(\s*EvtScript\b.*)=\s*\{\s*$")

# Single-line EvtScript declaration (e.g. EvtScript N(x) = EVT_EXIT_WALK(...);)
EVT_SINGLE_LINE_RE = re.compile(r"^\s*EvtScript\b.*=\s*\S.*;\s*$")

# Any multi-line initializer: line ends with = {
INIT_OPEN_RE = re.compile(r"^.*=\s*\{\s*$")


def count_braces(line: str) -> tuple[int, int]:
    """Count { and } outside of string literals and // comments."""
    in_string = False
    in_char = False
    escaped = False
    opens = 0
    closes = 0
    i = 0
    while i < len(line):
        c = line[i]
        if escaped:
            escaped = False
            i += 1
            continue
        if c == "\\":
            escaped = True
            i += 1
            continue
        if c == '"' and not in_char:
            in_string = not in_string
        elif c == "'" and not in_string:
            in_char = not in_char
        elif not in_string and not in_char:
            if c == "{":
                opens += 1
            elif c == "}":
                closes += 1
            elif c == "/" and i + 1 < len(line) and line[i + 1] == "/":
                break
        i += 1
    return opens, closes


def collect_block(lines: list[str], start: int) -> tuple[list[str], int]:
    """Collect lines from start until the matching closing brace.

    Returns (block_lines_excluding_close, index_of_closing_line).
    The opening line (with = {) should already be consumed; start points
    to the first line inside the block.
    """
    block_lines = []
    brace_depth = 1
    i = start
    while i < len(lines):
        line = lines[i]
        stripped = line.lstrip()
        if not stripped.startswith("//") and not stripped.startswith("#"):
            opens, closes = count_braces(line)
            brace_depth += opens - closes
        if brace_depth <= 0:
            break
        block_lines.append(line)
        i += 1
    return block_lines, i


# ---------------------------------------------------------------------------
# Protection: wrap blocks with // clang-format off/on
# ---------------------------------------------------------------------------

def protect_blocks(source: str) -> str:
    """Insert // clang-format off/on around EvtScript blocks and initializer lists."""
    lines = source.split("\n")
    result = []
    i = 0
    while i < len(lines):
        line = lines[i]
        if EVT_SINGLE_LINE_RE.match(line):
            result.append(line)
            i += 1
            continue
        if INIT_OPEN_RE.match(line):
            result.append("// clang-format off")
            result.append(line)
            _, end = collect_block(lines, i + 1)
            for j in range(i + 1, min(end + 1, len(lines))):
                result.append(lines[j])
            result.append("// clang-format on")
            i = end + 1
            continue
        result.append(line)
        i += 1
    return "\n".join(result)


def remove_protection(source: str) -> str:
    """Remove the temporary // clang-format off/on comments we added."""
    lines = source.split("\n")
    result = []
    for line in lines:
        stripped = line.strip()
        if stripped == "// clang-format off" or stripped == "// clang-format on":
            continue
        result.append(line)
    return "\n".join(result)


# ---------------------------------------------------------------------------
# EvtScript reformatting
# ---------------------------------------------------------------------------

def pop_to_kind(stack: list, kind: BlockKind) -> int:
    """Pop stack entries until we find one of the given kind. Returns how many were popped."""
    count = 0
    while stack and stack[-1] != kind:
        stack.pop()
        count += 1
    return count


def reformat_evtscript_block(lines: list[str]) -> list[str]:
    """Reformat lines inside an EvtScript block with proper indentation."""
    stack: list[BlockKind] = []
    result = []

    for line in lines:
        stripped = line.strip()

        if not stripped:
            result.append("")
            continue

        if stripped.startswith("#"):
            result.append(stripped)
            continue

        if stripped.startswith("//") or stripped.startswith("/*"):
            result.append(INDENT + INDENT * len(stack) + stripped)
            continue

        m = MACRO_RE.match(stripped)
        macro = m.group(1) if m else ""

        if macro in SWITCH_MACROS:
            indent = INDENT * len(stack)
            result.append(INDENT + indent + stripped)
            stack.append(BlockKind.SWITCH)
        elif macro in CASE_MACROS:
            pop_to_kind(stack, BlockKind.SWITCH)
            indent = INDENT * len(stack)
            result.append(INDENT + indent + stripped)
            stack.append(BlockKind.CASE)
        elif macro == "EndCaseGroup":
            pop_to_kind(stack, BlockKind.SWITCH)
            indent = INDENT * len(stack)
            result.append(INDENT + indent + stripped)
        elif macro == "EndSwitch":
            pop_to_kind(stack, BlockKind.SWITCH)
            if stack and stack[-1] == BlockKind.SWITCH:
                stack.pop()
            indent = INDENT * len(stack)
            result.append(INDENT + indent + stripped)
        elif macro in IF_MACROS:
            indent = INDENT * len(stack)
            result.append(INDENT + indent + stripped)
            stack.append(BlockKind.IF)
        elif macro == "Else":
            if stack and stack[-1] == BlockKind.IF:
                stack.pop()
            indent = INDENT * len(stack)
            result.append(INDENT + indent + stripped)
            stack.append(BlockKind.ELSE)
        elif macro == "EndIf":
            if stack and stack[-1] in (BlockKind.IF, BlockKind.ELSE):
                stack.pop()
            indent = INDENT * len(stack)
            result.append(INDENT + indent + stripped)
        elif macro == "Loop":
            indent = INDENT * len(stack)
            result.append(INDENT + indent + stripped)
            stack.append(BlockKind.LOOP)
        elif macro == "EndLoop":
            if stack and stack[-1] == BlockKind.LOOP:
                stack.pop()
            indent = INDENT * len(stack)
            result.append(INDENT + indent + stripped)
        elif macro == "Thread":
            indent = INDENT * len(stack)
            result.append(INDENT + indent + stripped)
            stack.append(BlockKind.THREAD)
        elif macro == "EndThread":
            if stack and stack[-1] == BlockKind.THREAD:
                stack.pop()
            indent = INDENT * len(stack)
            result.append(INDENT + indent + stripped)
        elif macro == "ChildThread":
            indent = INDENT * len(stack)
            result.append(INDENT + indent + stripped)
            stack.append(BlockKind.CHILD_THREAD)
        elif macro == "EndChildThread":
            if stack and stack[-1] == BlockKind.CHILD_THREAD:
                stack.pop()
            indent = INDENT * len(stack)
            result.append(INDENT + indent + stripped)
        else:
            indent = INDENT * len(stack)
            result.append(INDENT + indent + stripped)

    return result


def reformat_evtscripts(source: str) -> str:
    """Find EvtScript blocks and reformat their contents."""
    lines = source.split("\n")
    result = []
    i = 0
    while i < len(lines):
        line = lines[i]
        if EVT_SINGLE_LINE_RE.match(line):
            result.append(line)
            i += 1
            continue
        if EVT_OPEN_RE.match(line):
            result.append(line)
            i += 1
            block_lines, end = collect_block(lines, i)
            reformatted = reformat_evtscript_block(block_lines)
            result.extend(reformatted)
            if end < len(lines):
                result.append(lines[end])
            i = end + 1
            continue
        result.append(line)
        i += 1
    return "\n".join(result)


# ---------------------------------------------------------------------------
# Initializer list cleanup
# ---------------------------------------------------------------------------

def fix_comma_spacing(line: str) -> str:
    """Ensure space after commas outside of string literals and comments."""
    result = []
    in_string = False
    in_char = False
    escaped = False
    i = 0
    while i < len(line):
        c = line[i]
        if escaped:
            escaped = False
            result.append(c)
            i += 1
            continue
        if c == "\\":
            escaped = True
            result.append(c)
            i += 1
            continue
        if c == '"' and not in_char:
            in_string = not in_string
            result.append(c)
            i += 1
            continue
        if c == "'" and not in_string:
            in_char = not in_char
            result.append(c)
            i += 1
            continue
        if not in_string and not in_char:
            if c == "/" and i + 1 < len(line) and line[i + 1] == "/":
                result.append(line[i:])
                break
        if c == "," and not in_string and not in_char:
            result.append(",")
            if i + 1 < len(line) and line[i + 1] not in (" ", "\t"):
                result.append(" ")
            i += 1
            continue
        result.append(c)
        i += 1
    return "".join(result)


def cleanup_initializer_block(block_lines: list[str], base_indent: int) -> list[str]:
    """Apply minimal formatting to an initializer list block.

    Preserves the author's line breaks (no packing/unpacking).
    Fixes: indentation, trailing whitespace, space after comma.
    """
    result = []
    depth = 1

    for line in block_lines:
        stripped = line.strip()

        if not stripped:
            result.append("")
            continue

        # Preprocessor directives stay at column 0
        if stripped.startswith("#"):
            result.append(stripped)
            continue

        opens, closes = count_braces(stripped)
        net = opens - closes

        if net < 0:
            depth += net
            depth = max(depth, 0)

        indent = base_indent + 4 * depth
        fixed = fix_comma_spacing(stripped)
        result.append(" " * indent + fixed)

        if net > 0:
            depth += net

    return result


def cleanup_initializer_lists(source: str) -> str:
    """Find non-EvtScript initializer lists and apply minimal cleanup."""
    lines = source.split("\n")
    result = []
    i = 0
    while i < len(lines):
        line = lines[i]
        if EVT_OPEN_RE.match(line) or EVT_SINGLE_LINE_RE.match(line):
            # EvtScript blocks are handled separately; pass through
            if EVT_OPEN_RE.match(line):
                result.append(line)
                i += 1
                block_lines, end = collect_block(lines, i)
                result.extend(block_lines)
                if end < len(lines):
                    result.append(lines[end])
                i = end + 1
            else:
                result.append(line)
                i += 1
            continue
        if INIT_OPEN_RE.match(line):
            # Determine base indentation from the declaration line
            base_indent = len(line) - len(line.lstrip())
            result.append(line.rstrip())
            i += 1
            block_lines, end = collect_block(lines, i)
            cleaned = cleanup_initializer_block(block_lines, base_indent)
            result.extend(cleaned)
            if end < len(lines):
                # Closing line (e.g. "};") gets base indent
                closing = lines[end].strip()
                result.append(" " * base_indent + closing)
            i = end + 1
            continue
        result.append(line)
        i += 1
    return "\n".join(result)


# ---------------------------------------------------------------------------
# Global cleanup
# ---------------------------------------------------------------------------

def strip_trailing_whitespace(source: str) -> str:
    lines = source.split("\n")
    return "\n".join(line.rstrip() for line in lines)


# ---------------------------------------------------------------------------
# Pipeline
# ---------------------------------------------------------------------------

def run_clang_format(source: str, filename: str = "input.c") -> str:
    """Run clang-format on source code."""
    script_dir = os.path.dirname(os.path.abspath(__file__))
    repo_root = os.path.dirname(script_dir)
    assumed = os.path.join(repo_root, os.path.basename(filename))
    proc = subprocess.run(
        ["clang-format", "--style=file", f"--assume-filename={assumed}"],
        input=source,
        capture_output=True,
        text=True,
    )
    if proc.returncode != 0:
        print(f"clang-format error: {proc.stderr}", file=sys.stderr)
        sys.exit(1)
    return proc.stdout


def format_source(source: str, filename: str = "input.c") -> str:
    """Full formatting pipeline."""
    protected = protect_blocks(source)
    formatted = run_clang_format(protected, filename)
    unprotected = remove_protection(formatted)
    result = reformat_evtscripts(unprotected)
    result = cleanup_initializer_lists(result)
    result = strip_trailing_whitespace(result)
    return result


def main():
    parser = argparse.ArgumentParser(description="Format C source files with EvtScript support")
    parser.add_argument("files", nargs="*", help="Files to format (omit for stdin/stdout)")
    parser.add_argument("--check", action="store_true", help="Check formatting without modifying files")
    args = parser.parse_args()

    if not args.files:
        source = sys.stdin.read()
        result = format_source(source)
        if args.check:
            if result != source:
                sys.exit(1)
        else:
            sys.stdout.write(result)
        return

    any_changed = False
    for path in args.files:
        with open(path, "r") as f:
            source = f.read()
        result = format_source(source, path)
        if result != source:
            any_changed = True
            if args.check:
                print(f"::warning file={path},title=File not formatted::This file was changed, but it isn't formatted correctly. Run treefmt to format this file.")
            else:
                with open(path, "w") as f:
                    f.write(result)
                print(f"reformatted {path}", file=sys.stderr)

    if args.check and any_changed:
        sys.exit(1)


if __name__ == "__main__":
    main()
