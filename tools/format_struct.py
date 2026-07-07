#!/usr/bin/env python3

import argparse
import difflib
import re
import struct
import subprocess
import sys
import tempfile
from dataclasses import dataclass
from pathlib import Path

from audit_struct_layout import (
    Field,
    StructInfo,
    brace_delta,
    find_structs,
    parse_pad_size,
    root_dir,
    source_paths,
    strip_comments,
)


@dataclass
class FormatResult:
    lines: list[str]
    warnings: list[str]


def offset_width(size: int) -> int:
    return max(2, len(f"{max(0, size - 1):X}"))


def size_width(size: int) -> int:
    return max(2, len(f"{size:X}"))


def offset_comment(offset: int, width: int) -> str:
    return f"/* 0x{offset:0{width}X} */"


def blank_comment(width: int) -> str:
    return "/*" + (" " * (width + 4)) + "*/"


def remove_leading_annotation(line: str) -> str:
    stripped = line.lstrip()
    return re.sub(r"^/\*\s*(?:0x[0-9A-Fa-f]+|\s*)\s*\*/\s*", "", stripped).rstrip()


def declaration_text(line: str) -> str:
    return remove_leading_annotation(line).strip()


def has_top_level_comma(decl: str) -> bool:
    clean = strip_comments(decl)
    if ";" in clean:
        clean = clean[: clean.find(";")]

    paren_depth = 0
    bracket_depth = 0
    brace_depth = 0

    for char in clean:
        if char == "(":
            paren_depth += 1
        elif char == ")":
            paren_depth = max(0, paren_depth - 1)
        elif char == "[":
            bracket_depth += 1
        elif char == "]":
            bracket_depth = max(0, bracket_depth - 1)
        elif char == "{":
            brace_depth += 1
        elif char == "}":
            brace_depth = max(0, brace_depth - 1)
        elif char == "," and paren_depth == 0 and bracket_depth == 0 and brace_depth == 0:
            return True

    return False


def format_size_line(line: str, size: int) -> str:
    match = re.search(r"(?:size|sizeof)\s*=\s*0x([0-9A-Fa-f]+)", line, re.I)
    width = len(match.group(1)) if match else size_width(size)
    text = re.sub(r"\s*(?://|/\*)\s*(?:size|sizeof)\s*=.*$", "", line).rstrip()
    return f"{text} // size = 0x{size:0{width}X}"


def run_probe(
    code: list[str],
    labels: list[str],
    cc: str,
    objcopy: str,
) -> tuple[dict[str, int] | None, str]:
    with tempfile.TemporaryDirectory(prefix="format-struct-") as tmp:
        tmp_path = Path(tmp)
        source = tmp_path / "probe.c"
        obj = tmp_path / "probe.o"
        binary = tmp_path / "layout.bin"
        source.write_text("\n".join(code))

        cc_cmd = [
            cc,
            "-c",
            "-std=gnu99",
            "-w",
            "-g0",
            "-I.",
            "-Iver/us/include",
            "-Iver/us/build/include",
            "-Iinclude",
            "-Isrc",
            "-Iassets/us",
            "-D_FINALROM",
            "-DVERSION=us",
            "-DVERSION_US",
            "-DF3DEX_GBI_2",
            "-D_MIPS_SZLONG=32",
            "-DNON_MATCHING",
            "-DDEBUG",
            "-DSHIFT",
            "-D_LANGUAGE_C",
            "-include",
            "common.h",
            str(source),
            "-o",
            str(obj),
        ]
        result = subprocess.run(cc_cmd, cwd=root_dir, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        if result.returncode != 0:
            return None, result.stderr

        objcopy_cmd = [objcopy, "-O", "binary", "-j", ".layout", str(obj), str(binary)]
        result = subprocess.run(objcopy_cmd, cwd=root_dir, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        if result.returncode != 0:
            return None, result.stderr

        data = binary.read_bytes()

    values = [struct.unpack(">I", data[index : index + 4])[0] for index in range(0, len(data), 4)]
    if len(values) != len(labels):
        return None, f"probe returned {len(values)} values for {len(labels)} labels"

    return dict(zip(labels, values)), ""


def probe_values(
    info: StructInfo,
    extra_includes: list[str],
    cc: str,
    objcopy: str,
) -> dict[str, int]:
    labels: list[str] = []

    def emit_values() -> list[str]:
        code = ['const unsigned int __attribute__((used,section(".layout"))) layout_values[] = {']
        labels.append(f"{info.name}.__sizeof")
        code.append(f"    (unsigned)sizeof({info.c_name}),")

        for field in info.fields:
            if field.name is None:
                continue
            labels.append(f"{info.name}.{field.name}")
            code.append(f"    (unsigned)offsetof({info.c_name}, {field.name}),")
            labels.append(f"{info.name}.{field.name}.__sizeof")
            code.append(f"    (unsigned)sizeof(((const {info.c_name}*)0)->{field.name}),")
            labels.append(f"{info.name}.{field.name}.__alignof")
            code.append(f"    (unsigned)__alignof__(((const {info.c_name}*)0)->{field.name}),")

        code.append("};")
        return code

    include_code = [
        "#include <stddef.h>",
        '#include "common.h"',
    ]
    for include in extra_includes:
        include_code.append(f'#include "{include}"')
    include_code.append(f'#include "{info.path.relative_to(root_dir).as_posix()}"')

    labels.clear()
    values, error = run_probe(include_code + emit_values(), labels, cc, objcopy)
    if values is not None:
        return values

    source_lines = info.path.read_text(errors="ignore").splitlines()
    struct_lines = source_lines[info.line - 1 : info.close_line]
    extract_code = [
        "#include <stddef.h>",
        '#include "common.h"',
    ]
    for include in extra_includes:
        extract_code.append(f'#include "{include}"')
    extract_code.extend(struct_lines)

    labels.clear()
    values, extract_error = run_probe(extract_code + emit_values(), labels, cc, objcopy)
    if values is not None:
        return values

    print(error, file=sys.stderr)
    print(extract_error, file=sys.stderr)
    raise SystemExit(1)


def field_for_line(info: StructInfo) -> dict[int, Field]:
    return {field.line: field for field in info.fields}


def format_pad_size(size: int) -> str:
    if size >= 0x10:
        return f"0x{size:X}"
    return str(size)


def format_pad(size: int, offset: int, width: int) -> str:
    return f"    {offset_comment(offset, width)} PAD({format_pad_size(size)});"


def parse_formatted_pad(line: str) -> tuple[int, int] | None:
    match = re.match(r"\s*/\*\s*0x([0-9A-Fa-f]+)\s*\*/\s*PAD\(\s*(0x[0-9A-Fa-f]+|\d+)\s*\);$", line)
    if not match:
        return None
    return int(match.group(1), 16), int(match.group(2), 0)


def append_pad(lines: list[str], size: int, offset: int, width: int):
    if size <= 0:
        return

    if lines:
        previous = parse_formatted_pad(lines[-1])
        if previous is not None:
            previous_offset, previous_size = previous
            if previous_offset + previous_size == offset:
                lines[-1] = format_pad(previous_size + size, previous_offset, width)
                return

    lines.append(format_pad(size, offset, width))


def format_decl(decl: str, offset: int, width: int) -> str:
    return f"    {offset_comment(offset, width)} {decl}"


def format_nested_block(block: list[str], offset: int, width: int) -> list[str]:
    lines: list[str] = []
    start_decl = declaration_text(block[0])
    lines.append(format_decl(start_decl, offset, width))

    depth = brace_delta(start_decl)
    blank = blank_comment(width)

    for line in block[1:-1]:
        decl = declaration_text(line)
        if not decl:
            lines.append("")
            continue

        line_depth = depth - 1 if decl.startswith("}") else depth
        indent = "    " * max(1, line_depth)
        lines.append(f"    {blank} {indent}{decl}")
        depth += brace_delta(decl)

    close_decl = declaration_text(block[-1])
    lines.append(format_decl(close_decl, offset, width))
    return lines


def collect_nested_block(lines: list[str], start: int) -> tuple[list[str], int]:
    block = [lines[start]]
    depth = brace_delta(lines[start])
    index = start + 1

    while index < len(lines) and depth > 0:
        block.append(lines[index])
        depth += brace_delta(lines[index])
        index += 1

    return block, index


def is_nested_start(line: str) -> bool:
    return re.match(r"(union|struct)\s*\{", declaration_text(line)) is not None


def format_struct(
    info: StructInfo,
    values: dict[str, int],
    insert_padding: bool,
) -> FormatResult:
    source_lines = info.path.read_text(errors="ignore").splitlines()
    original = source_lines[info.line - 1 : info.close_line]
    body = original[1:-1]
    fields_by_line = field_for_line(info)
    size = values[f"{info.name}.__sizeof"]
    width = offset_width(size)
    warnings: list[str] = []
    result = [original[0].rstrip()]
    prev_end: int | None = None
    index = 0

    while index < len(body):
        abs_line = info.line + 1 + index
        line = body[index]
        field = fields_by_line.get(abs_line)
        decl = declaration_text(line)

        if is_nested_start(line):
            block, next_index = collect_nested_block(body, index)
            offset = field.annotation if field and field.annotation is not None else prev_end
            if field and field.name is not None:
                actual = values.get(f"{info.name}.{field.name}")
                size_value = values.get(f"{info.name}.{field.name}.__sizeof")
                if actual is not None:
                    offset = actual
                if insert_padding and prev_end is not None and actual is not None and actual > prev_end:
                    append_pad(result, actual - prev_end, prev_end, width)
                if actual is not None and size_value is not None:
                    prev_end = actual + size_value
                else:
                    prev_end = None
            else:
                prev_end = None

            if offset is None:
                result.extend(line.rstrip() for line in block)
                warnings.append(f"{info.path}:{abs_line}: could not infer offset for nested block")
            else:
                result.extend(format_nested_block(block, offset, width))

            index = next_index
            continue

        if field is None:
            result.append(line.rstrip())
            prev_end = None if decl and not decl.startswith(("//", "/*")) else prev_end
            index += 1
            continue

        if field.kind == "pad":
            pad_size = field.pad_size
            if pad_size is None:
                pad_size = parse_pad_size(decl)
            offset = prev_end if prev_end is not None else field.annotation
            if offset is None or pad_size is None:
                result.append(line.rstrip())
                warnings.append(f"{info.path}:{abs_line}: could not infer offset for PAD")
            else:
                append_pad(result, pad_size, offset, width)
                prev_end = offset + pad_size
            index += 1
            continue

        if field.name is None:
            result.append(line.rstrip())
            prev_end = None
            index += 1
            continue

        actual = values.get(f"{info.name}.{field.name}")
        size_value = values.get(f"{info.name}.{field.name}.__sizeof")
        if actual is None or size_value is None:
            result.append(line.rstrip())
            prev_end = None
            index += 1
            continue

        if insert_padding and prev_end is not None and actual > prev_end:
            append_pad(result, actual - prev_end, prev_end, width)

        result.append(format_decl(decl, actual, width))
        if has_top_level_comma(decl):
            prev_end = None
            warnings.append(f"{info.path}:{abs_line}: comma declaration formatted as one field")
        else:
            prev_end = actual + size_value

        index += 1

    if insert_padding and prev_end is not None and size > prev_end:
        append_pad(result, size - prev_end, prev_end, width)

    result.append(format_size_line(original[-1].rstrip(), size))
    return FormatResult(result, warnings)


def find_one_struct(name: str, files: list[str]) -> StructInfo:
    paths = [root_dir / path for path in files] if files else source_paths()
    found = find_structs([name], paths)[name]

    if not found:
        print(f"{name}: no struct definition found", file=sys.stderr)
        raise SystemExit(1)
    if len(found) > 1:
        print(f"{name}: found multiple definitions; use --file to choose one:", file=sys.stderr)
        for match in found:
            rel = match.path.relative_to(root_dir)
            print(f"  {rel}:{match.line}", file=sys.stderr)
        raise SystemExit(1)

    return found[0]


def unified_diff(path: Path, old_lines: list[str], new_lines: list[str]) -> str:
    rel = path.relative_to(root_dir).as_posix()
    return "".join(
        difflib.unified_diff(
            [line + "\n" for line in old_lines],
            [line + "\n" for line in new_lines],
            fromfile=f"a/{rel}",
            tofile=f"b/{rel}",
        )
    )


def main() -> int:
    parser = argparse.ArgumentParser(description="Format one struct definition using compiler-verified layout values.")
    parser.add_argument("struct", help="struct typedef/tag name to format, e.g. Camera")
    parser.add_argument("--file", action="append", default=[], help="source/header file to search instead of all include/src files")
    parser.add_argument("--include", action="append", default=[], help='emit extra #include "..." lines before probing layout')
    parser.add_argument("--skip-padding", action="store_true", help="leave implicit padding gaps alone")
    parser.add_argument("--print", action="store_true", dest="print_struct", help="print the formatted struct instead of modifying the source file")
    parser.add_argument("--check", action="store_true", help="print a diff and return nonzero if formatting would change")
    parser.add_argument("--cc", default="mips-linux-gnu-gcc", help="compiler to use")
    parser.add_argument("--objcopy", default="mips-linux-gnu-objcopy", help="objcopy to use")
    args = parser.parse_args()

    info = find_one_struct(args.struct, args.file)
    values = probe_values(info, args.include, args.cc, args.objcopy)
    formatted = format_struct(info, values, not args.skip_padding)

    source_lines = info.path.read_text(errors="ignore").splitlines()
    old_block = source_lines[info.line - 1 : info.close_line]
    changed = old_block != formatted.lines

    for warning in formatted.warnings:
        print(f"warning: {warning}", file=sys.stderr)

    if args.check:
        if changed:
            print(unified_diff(info.path, old_block, formatted.lines), end="")
            return 1
        return 0

    if args.print_struct:
        print("\n".join(formatted.lines))
        return 0

    if changed:
        new_source = source_lines[: info.line - 1] + formatted.lines + source_lines[info.close_line :]
        info.path.write_text("\n".join(new_source) + "\n")
        print(f"formatted {info.path.relative_to(root_dir)}:{info.line}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
