"""Writes the linker script and its symbol header.

Which objects a segment contains comes from the filesystem (see segments.py).
Where a segment lives comes from splat's segment metadata: either an explicit
VRAM address or, for a chained vram_class, the symbol the previous segment
ends at.

Segments are laid out uniformly. Object order within a segment is the sorted
order segments.py produces, so the script is identical on every platform.
"""

import re
from pathlib import Path
from typing import Dict, List, Optional

BUILD_SECTIONS = ("TEXT", "DATA", "RODATA")
SYMBOL_SUFFIXES = (
    "ROM_START", "ROM_END", "VRAM", "VRAM_END",
    *(f"{s}_{k}" for s in (*BUILD_SECTIONS, "BSS") for k in ("START", "END", "SIZE")),
)


def data_label(object_path: str, build_prefix: str, roots) -> str:
    """The symbol naming the start of an object's data."""
    rest = object_path[len(build_prefix):].removesuffix(".o")
    for root in roots:
        if rest.startswith(root):
            rest = rest[len(root):]
            break
    return re.sub(r"\W", "_", rest)


def symbol_name(segment_name: str) -> str:
    """Segment names reach the linker as symbols, so make them identifiers."""
    return re.sub(r"\W", "_", segment_name)


class Segment:
    def __init__(self, name: str, vram: Optional[str], subalign: Optional[int],
                 objects: List[str], vram_class: Optional[str] = None):
        self.name = symbol_name(name)
        self.vram = vram
        self.subalign = subalign
        self.objects = objects
        self.vram_class = vram_class



def _section(out: List[str], name: str, kind: str, objects) -> None:
    out.append(f"        {name}_{kind}_START = .;")
    for obj, label in objects:
        # Data symbols are addressed by name from C, so label each contribution.
        if kind == "DATA":
            out.append(f"        {label} = .;")
        out.append(f"        {obj}(.{kind.lower()}*);")
    out.append("        . = ALIGN(., 16);")
    out.append(f"        {name}_{kind}_END = .;")
    out.append(
        f"        {name}_{kind}_SIZE = ABSOLUTE({name}_{kind}_END - {name}_{kind}_START);"
    )


def _class_vram(segments: List[Segment], follows: Dict[str, List[str]]):
    """Where to define each vram class's CLASS_VRAM symbol.

    A class that follows others starts above all of their segments, which the
    linker can only evaluate once those segments have been laid out.
    """
    members: Dict[str, List[str]] = {}
    for seg in segments:
        members.setdefault(seg.vram_class, []).append(seg.name)
    position = {seg.name: i for i, seg in enumerate(segments)}

    emit: Dict[str, List[str]] = {}
    for name, followed in follows.items():
        inputs = [s for cls in followed for s in members.get(cls, [])]
        if not inputs:
            continue
        lines = [f"    {name}_CLASS_VRAM = {inputs[0]}_VRAM_END;"]
        lines += [
            f"    {name}_CLASS_VRAM = MAX({name}_CLASS_VRAM, {s}_VRAM_END);"
            for s in inputs[1:]
        ]
        emit.setdefault(max(inputs, key=position.get), []).extend(lines + [""])
    return emit


def write_script(path: Path, segments: List[Segment],
                 follows: Dict[str, List[str]] = {}) -> None:
    class_vram = _class_vram(segments, follows)
    out = ["SECTIONS", "{", "    __romPos = 0;", ""]
    for seg in segments:
        name = seg.name
        addr = f"{seg.vram} " if seg.vram else ""
        subalign = f" SUBALIGN({seg.subalign})" if seg.subalign else ""

        out.append(f"    {name}_ROM_START = __romPos;")
        out.append(f"    {name}_VRAM = ADDR(.{name});")
        out.append(f"    .{name} {addr}: AT({name}_ROM_START){subalign}")
        out.append("    {")
        out.append("        FILL(0x00000000);")
        for kind in BUILD_SECTIONS:
            _section(out, name, kind, seg.objects)
        out.append("    }")

        out.append(f"    {name}_bss_VRAM = ADDR(.{name}_bss);")
        out.append(f"    .{name}_bss (NOLOAD) :")
        out.append("    {")
        out.append("        FILL(0x00000000);")
        _section(out, name, "BSS", seg.objects)
        out.append("    }")

        out.append(f"    __romPos += SIZEOF(.{name});")
        out.append("    __romPos = ALIGN(__romPos, 16);")
        out.append("    . = ALIGN(., 16);")
        out.append(f"    {name}_ROM_END = __romPos;")
        out.append(f"    {name}_VRAM_END = .;")
        out.append("")
        out += class_vram.get(name, [])

    out += ["    /DISCARD/ :", "    {", "        *(*);", "    }", "}", ""]
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text("\n".join(out))


def write_symbol_header(path: Path, segments: List[Segment]) -> None:
    out = ["#ifndef _HEADER_SYMBOLS_H_", "#define _HEADER_SYMBOLS_H_", "",
           '#include "common.h"', ""]
    seen = set()
    for seg in segments:
        out += [f"extern Addr {seg.name}_{suffix};" for suffix in SYMBOL_SUFFIXES]
        for _, label in seg.objects:
            if label not in seen:
                seen.add(label)
                out.append(f"extern Addr {label};")
    out += ["", "#endif", ""]
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text("\n".join(out))
