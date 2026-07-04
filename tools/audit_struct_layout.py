#!/usr/bin/env python3

import argparse
import os
import re
import struct
import subprocess
import sys
import tempfile
from dataclasses import dataclass
from pathlib import Path


script_dir = Path(os.path.dirname(os.path.realpath(__file__)))
root_dir = script_dir.parent


@dataclass
class Field:
    name: str | None
    line: int
    annotation: int | None
    text: str
    kind: str


@dataclass
class StructInfo:
    name: str
    c_name: str
    path: Path
    line: int
    close_line: int
    size_annotation: int | None
    fields: list[Field]


def strip_comments(line: str) -> str:
    line = re.sub(r"/\*.*?\*/", " ", line)
    line = re.sub(r"//.*", "", line)
    return line


def brace_delta(line: str) -> int:
    clean = strip_comments(line)
    return clean.count("{") - clean.count("}")


def parse_field_name(decl: str) -> str | None:
    clean = strip_comments(decl).strip()

    if not clean or clean.startswith("#") or clean.startswith("PAD("):
        return None
    if ":" in clean:
        return None

    # Function pointer: void (*name)(...)
    match = re.search(r"\(\s*\*\s*([A-Za-z_]\w*)\s*\)", clean)
    if match:
        return match.group(1)

    # Function-pointer typedef macro: VoidCallback(name);
    match = re.match(r"[A-Za-z_]\w*\s*\(\s*([A-Za-z_]\w*)\s*\)\s*;", clean)
    if match:
        return match.group(1)

    if ";" in clean:
        clean = clean[: clean.find(";")]

    clean = clean.split("=")[0].strip().split(",")[0].strip()

    # Arrays, including multi-dimensional arrays.
    while True:
        stripped = re.sub(r"\s*\[[^\]]*\]\s*$", "", clean).strip()
        if stripped == clean:
            break
        clean = stripped

    match = re.search(r"([A-Za-z_]\w*)\s*$", clean)
    if not match:
        return None

    name = match.group(1)
    if name in {"struct", "union", "enum"}:
        return None
    return name


def parse_structs(path: Path) -> list[StructInfo]:
    text = path.read_text(errors="ignore").splitlines()
    structs: list[StructInfo] = []
    start_re = re.compile(r"\b(?:typedef\s+)?struct\s*([A-Za-z_]\w*)?\s*\{")
    offset_re = re.compile(r"/\*\s*0x([0-9A-Fa-f]+)\s*\*/\s*(.*)")
    size_re = re.compile(r"}\s*([A-Za-z_]\w*)?\s*;\s*(?://|/\*)\s*(?:size|sizeof)\s*=\s*(?:0x)?([0-9A-Fa-f]+)", re.I)

    index = 0
    while index < len(text):
        match = start_re.search(text[index])
        if not match:
            index += 1
            continue

        tag_name = match.group(1)
        start_line = index + 1
        depth = brace_delta(text[index][text[index].find("{") :])
        body: list[tuple[int, str]] = []
        index += 1

        while index < len(text) and depth > 0:
            body.append((index + 1, text[index]))
            depth += brace_delta(text[index])
            index += 1

        if not body:
            continue

        close_line_num, close_line = body[-1]
        typedef_match = re.search(r"^\s*}\s*([A-Za-z_]\w*)?\s*;", close_line)
        typedef_name = typedef_match.group(1) if typedef_match else None
        name = typedef_name or tag_name
        if name is None:
            continue
        c_name = typedef_name or f"struct {tag_name}"

        size_match = size_re.search(close_line)
        size_annotation = int(size_match.group(2), 16) if size_match else None

        fields: list[Field] = []
        depth = 1
        item = 0
        while item < len(body):
            line_num, line = body[item]
            offset_match = offset_re.search(line)

            if depth == 1:
                annotation = int(offset_match.group(1), 16) if offset_match else None
                decl = offset_match.group(2).strip() if offset_match else line.strip()
                clean = strip_comments(decl).strip()

                if re.match(r"(union|struct)\s*\{", clean):
                    nested_depth = brace_delta(decl)
                    nested_index = item + 1
                    nested_close = ""
                    while nested_index < len(body) and nested_depth > 0:
                        nested_close = body[nested_index][1]
                        nested_depth += brace_delta(nested_close)
                        nested_index += 1
                    nested_match = re.search(r"}\s*([A-Za-z_]\w*)\s*;", strip_comments(nested_close))
                    nested_name = nested_match.group(1) if nested_match else None
                    kind = "field" if nested_name else "anonymous"
                    fields.append(Field(nested_name, line_num, annotation, line.strip(), kind))
                elif ";" in strip_comments(line) and not clean.startswith(("}", "#")):
                    field_name = parse_field_name(decl)
                    kind = "field" if field_name else "skip"
                    fields.append(Field(field_name, line_num, annotation, line.strip(), kind))

            depth += brace_delta(line)
            item += 1

        structs.append(StructInfo(name, c_name, path, start_line, close_line_num, size_annotation, fields))

    return structs


def find_structs(names: list[str], paths: list[Path]) -> dict[str, list[StructInfo]]:
    found = {name: [] for name in names}
    for path in paths:
        try:
            structs = parse_structs(path)
        except UnicodeDecodeError:
            continue
        for info in structs:
            if info.name in found:
                found[info.name].append(info)
    return found


def source_paths() -> list[Path]:
    paths: list[Path] = []
    for dirname in ["include", "src"]:
        paths.extend((root_dir / dirname).rglob("*.h"))
        paths.extend((root_dir / dirname).rglob("*.c"))
    return sorted(set(paths))


def compile_probe(
    infos: list[StructInfo],
    extra_includes: list[str],
    cc: str,
    objcopy: str,
) -> dict[str, int]:
    labels: list[str] = []
    code: list[str] = [
        "#include <stddef.h>",
        '#include "common.h"',
    ]

    include_paths: list[str] = []
    for info in infos:
        rel = info.path.relative_to(root_dir).as_posix()
        if rel not in include_paths:
            include_paths.append(rel)
    for include in extra_includes:
        if include not in include_paths:
            include_paths.append(include)

    for include in include_paths:
        code.append(f'#include "{include}"')

    code.append('const unsigned int __attribute__((used,section(".layout"))) layout_values[] = {')

    for info in infos:
        labels.append(f"{info.name}.__sizeof")
        code.append(f"    (unsigned)sizeof({info.c_name}),")

        for field in info.fields:
            if field.name is None:
                continue
            labels.append(f"{info.name}.{field.name}")
            code.append(f"    (unsigned)offsetof({info.c_name}, {field.name}),")

    code.append("};")

    with tempfile.TemporaryDirectory(prefix="struct-layout-") as tmp:
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
            print(result.stderr, file=sys.stderr)
            raise SystemExit(result.returncode)

        objcopy_cmd = [objcopy, "-O", "binary", "-j", ".layout", str(obj), str(binary)]
        result = subprocess.run(objcopy_cmd, cwd=root_dir, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        if result.returncode != 0:
            print(result.stderr, file=sys.stderr)
            raise SystemExit(result.returncode)

        data = binary.read_bytes()

    values = [struct.unpack(">I", data[index : index + 4])[0] for index in range(0, len(data), 4)]
    if len(values) != len(labels):
        raise SystemExit(f"probe returned {len(values)} values for {len(labels)} labels")

    return dict(zip(labels, values))


def fmt(value: int | None, width: int = 4) -> str:
    if value is None:
        return "-"
    return f"0x{value:0{width}X}"


def print_struct(info: StructInfo, values: dict[str, int], compare: bool) -> int:
    size_actual = values[f"{info.name}.__sizeof"]
    size_bad = info.size_annotation is not None and info.size_annotation != size_actual
    bad_count = 1 if size_bad else 0

    rel = info.path.relative_to(root_dir)
    print(f"{info.name} ({rel}:{info.line})")
    print("  field                         actual   annotated  line  bad")
    print("  ----------------------------  -------  ---------  ----  ---")

    for field in info.fields:
        actual = values.get(f"{info.name}.{field.name}") if field.name is not None else None
        bad = compare and field.annotation is not None and actual is not None and field.annotation != actual
        bad_count += 1 if bad else 0
        marker = "x" if bad else ""
        name = field.name or f"<{field.kind}>"
        print(f"  {name:<28}  {fmt(actual):>7}  {fmt(field.annotation):>9}  {field.line:>4}  {marker}")

    print()
    if compare:
        marker = "x" if size_bad else ""
        print(f"  {'sizeof:':<28}  {fmt(size_actual):>7}  {fmt(info.size_annotation):>9}  {'':>4}  {marker}")
    else:
        print(f"  {'sizeof:':<28}  {fmt(size_actual):>7}")

    print()
    return bad_count


def main() -> int:
    parser = argparse.ArgumentParser(description="Audit struct sizeof and offsetof values with the MIPS compiler.")
    parser.add_argument("struct", nargs="+", help="struct typedef/tag name to audit, e.g. Camera")
    parser.add_argument("--include", action="append", default=[], help="extra file to include in the probe")
    parser.add_argument("--file", action="append", default=[], help="source/header file to search instead of all include/src files")
    parser.add_argument("--no-compare", action="store_true", help="only print compiler layout values")
    parser.add_argument("--cc", default="mips-linux-gnu-gcc", help="compiler to use")
    parser.add_argument("--objcopy", default="mips-linux-gnu-objcopy", help="objcopy to use")
    args = parser.parse_args()

    paths = [root_dir / path for path in args.file] if args.file else source_paths()
    found = find_structs(args.struct, paths)

    selected: list[StructInfo] = []
    for name in args.struct:
        matches = found[name]
        if not matches:
            print(f"{name}: no struct definition found", file=sys.stderr)
            return 1
        if len(matches) > 1:
            print(f"{name}: found multiple definitions; use --file to choose one:", file=sys.stderr)
            for match in matches:
                rel = match.path.relative_to(root_dir)
                print(f"  {rel}:{match.line}", file=sys.stderr)
            return 1
        selected.append(matches[0])

    values = compile_probe(selected, args.include, args.cc, args.objcopy)

    bad_count = 0
    for info in selected:
        bad_count += print_struct(info, values, not args.no_compare)

    if not args.no_compare:
        if bad_count:
            print(f"{bad_count} bad annotation(s) detected.")
        else:
            print("No problems detected.")

    return 2 if bad_count and not args.no_compare else 0


if __name__ == "__main__":
    raise SystemExit(main())
