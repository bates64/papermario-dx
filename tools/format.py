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
      Lerp/EndLerp                indent body
      Thread/EndThread            indent body
      ChildThread/EndChildThread  indent body
      Finally/End                 indent cleanup tail
      Label                       indent body, if the source already does,
                                  until the source returns to Label's level
      Preprocessor directives     stay as written, continuation lines too
      Call arguments on           keep their position relative to the
        continuation lines          call's first line
      Everything else             indented at current level

  Initializer lists (arrays and struct literals) and enum bodies
    clang-format repacks array items to fill lines, destroying
    intentional grouping (e.g. natural pairs, one-per-line lists), and
    realigns enum values away from the columns they're written in.
    These are preserved as-written, with minimal cleanup:

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
    LERP = auto()
    THREAD = auto()
    CHILD_THREAD = auto()
    FINALLY = auto()
    LABEL = auto()


INDENT = "    "

# Paths left unformatted, relative to the repository root: generated map
# headers, vendored libultra and nusys, animation data (which clang-format can
# take gigabytes of memory to format), and a vendored host tool.
EXCLUDED_PATHS = (
    "include/mapfs/",
    "include/PR/",
    "include/nu/",
    "src/os/",
    "src/world/model_anim/",
    "src/battle/area/omo2/actor/animation.inc.c",
    "src/world/area/dgb/dgb_01/smash_bridges/anim.inc.c",
    "src/world/area/kmr/kmr_11/fortress_animation.c",
    "tools/build/rom/n64crc.c",
)

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

IF_MACROS = {
    "IfEq",
    "IfNe",
    "IfLt",
    "IfGt",
    "IfLe",
    "IfGe",
    "IfRange",
    "IfNotRange",
    "IfFlag",
    "IfNotFlag",
    "IfTrue",
    "IfFalse",
    "IfEval",
    "IfNotEval",
    "IfEvalF",
    "IfNotEvalF",
}

MACRO_RE = re.compile(r"^\s*(\w+)")

# EvtScript declaration that opens a block (multi-line body)
EVT_OPEN_RE = re.compile(r"^(\s*EvtScript\b.*)=\s*\{\s*$")

# Single-line EvtScript declaration (e.g. EvtScript N(x) = EVT_EXIT_WALK(...);)
EVT_SINGLE_LINE_RE = re.compile(r"^\s*EvtScript\b.*=\s*\S.*;\s*$")

# Any multi-line initializer (line ends with = {) or enum body
INIT_OPEN_RE = re.compile(r"^(.*=\s*|\s*(typedef\s+)?enum\b[^;=]*)\{\s*$")

# A struct or union body that opens on this line
STRUCT_OPEN_RE = re.compile(r"^\s*(typedef\s+)?(struct|union)\b[^;=(]*\{\s*$")

# An offset comment followed by more indentation, which shows nesting after
# the offset column: /* 0x10 */     struct {
NESTED_AFTER_OFFSET_RE = re.compile(r"^\s*/\*[^*]*\*/\s{2,}\S")

# String and character literals, which may hold parentheses
LITERAL_RE = re.compile(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'')


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
    """Insert // clang-format off/on around EvtScript blocks, initializer lists,
    and struct bodies that show nesting after their offset comments."""
    lines = source.split("\n")
    result = []
    i = 0
    while i < len(lines):
        line = lines[i]
        if EVT_SINGLE_LINE_RE.match(line):
            result.append(line)
            i += 1
            continue
        is_struct = STRUCT_OPEN_RE.match(line)
        if INIT_OPEN_RE.match(line) or is_struct:
            body, end = collect_block(lines, i + 1)
            if is_struct and not any(NESTED_AFTER_OFFSET_RE.match(l) for l in body):
                result.append(line)
                i += 1
                continue
            result.append("// clang-format off")
            result.append(line)
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


def paren_balance(line: str) -> int:
    """Count ( minus ) outside of string and character literals."""
    code = LITERAL_RE.sub("", line)
    return code.count("(") - code.count(")")


def indent_of(line: str) -> int:
    return len(line) - len(line.lstrip())


def reformat_evtscript_block(lines: list[str]) -> list[str]:
    """Reformat lines inside an EvtScript block with proper indentation."""
    stack: list[BlockKind] = []
    result = []
    # Label bodies the source indents, as (source indent of the Label line,
    # position of its entry in stack).
    labels: list[tuple[int, int]] = []
    in_directive = False
    # Unclosed parentheses of a call split over several lines, and how far
    # its first line moved, which its other lines move by too.
    open_parens = 0
    call_shift = 0

    for i, line in enumerate(lines):
        stripped = line.strip()
        source_indent = indent_of(line)

        if in_directive or stripped.startswith("#"):
            result.append(line.rstrip())
            in_directive = stripped.endswith("\\")
            continue

        if not stripped:
            result.append("")
            continue

        if open_parens > 0:
            result.append(" " * max(0, source_indent + call_shift) + stripped)
            open_parens = max(0, open_parens + paren_balance(stripped))
            continue

        while labels and source_indent <= labels[-1][0]:
            _, position = labels.pop()
            if position < len(stack):
                del stack[position]

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
        elif macro == "Lerp":
            indent = INDENT * len(stack)
            result.append(INDENT + indent + stripped)
            stack.append(BlockKind.LERP)
        elif macro == "EndLerp":
            if stack and stack[-1] == BlockKind.LERP:
                stack.pop()
            indent = INDENT * len(stack)
            result.append(INDENT + indent + stripped)
        elif macro == "Thread":
            indent = INDENT * len(stack)
            result.append(INDENT + indent + stripped)
            stack.append(BlockKind.THREAD)
        elif macro == "EndThread":
            if stack and stack[-1] == BlockKind.FINALLY:
                stack.pop()
            if stack and stack[-1] == BlockKind.THREAD:
                stack.pop()
            indent = INDENT * len(stack)
            result.append(INDENT + indent + stripped)
        elif macro == "ChildThread":
            indent = INDENT * len(stack)
            result.append(INDENT + indent + stripped)
            stack.append(BlockKind.CHILD_THREAD)
        elif macro == "EndChildThread":
            if stack and stack[-1] == BlockKind.FINALLY:
                stack.pop()
            if stack and stack[-1] == BlockKind.CHILD_THREAD:
                stack.pop()
            indent = INDENT * len(stack)
            result.append(INDENT + indent + stripped)
        elif macro == "Finally":
            indent = INDENT * len(stack)
            result.append(INDENT + indent + stripped)
            stack.append(BlockKind.FINALLY)
        elif macro == "End":
            if stack and stack[-1] == BlockKind.FINALLY:
                stack.pop()
            indent = INDENT * len(stack)
            result.append(INDENT + indent + stripped)
        elif macro == "Label" and i + 1 < len(lines) and lines[i + 1].strip() and indent_of(lines[i + 1]) > source_indent:
            indent = INDENT * len(stack)
            result.append(INDENT + indent + stripped)
            labels.append((source_indent, len(stack)))
            stack.append(BlockKind.LABEL)
        else:
            indent = INDENT * len(stack)
            result.append(INDENT + indent + stripped)

        open_parens = max(0, paren_balance(stripped))
        call_shift = indent_of(result[-1]) - source_indent

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


def cleanup_initializer_block(block_lines: list[str]) -> list[str]:
    """Apply minimal formatting to an initializer list or enum body.

    Preserves the author's line breaks and indentation.
    Fixes: trailing whitespace, space after comma.
    """
    result = []
    for line in block_lines:
        stripped = line.strip()
        if not stripped:
            result.append("")
        elif stripped.startswith("#"):
            # Preprocessor directives stay at column 0
            result.append(stripped)
        else:
            result.append(fix_comma_spacing(line.rstrip()))
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
            cleaned = cleanup_initializer_block(block_lines)
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

    repo_root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    any_changed = False
    for path in args.files:
        if os.path.relpath(os.path.abspath(path), repo_root).replace(os.sep, "/").startswith(EXCLUDED_PATHS):
            continue
        with open(path, "r", encoding="utf-8") as f:
            source = f.read()
        result = format_source(source, path)
        if result != source:
            any_changed = True
            if args.check:
                print(f"::warning file={path},title=File not formatted::This file was changed, but it isn't formatted correctly. Run treefmt to format this file.")
            else:
                with open(path, "w", encoding="utf-8") as f:
                    f.write(result)
                print(f"reformatted {path}", file=sys.stderr)

    if args.check and any_changed:
        sys.exit(1)


if __name__ == "__main__":
    main()
