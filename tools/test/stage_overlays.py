#!/usr/bin/env python3
"""Validate built stage modules, relocations, and every battle-area stage reference.

Run after building the ROM: python3 tools/test/stage_overlays.py [--version us]
This checks compiled data, not in-game rendering or script execution.
"""

import argparse
import json
from pathlib import Path
import struct
import sys

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools/build"))
from overlay_impl import Elf32, OVL_MAGIC, get_loaded_footprint

LINK_BASE = 0x80000000
TEST_BASE = 0x80500000
STAGE_TYPE = 10


def check_stage(path):
    blob = path.read_bytes()
    header = struct.unpack_from(">4s11I", blob)
    magic, load_size, _, bss_size, exports, strings_size, dtors, r32_count, *_ = header
    assert magic == OVL_MAGIC, path
    meta = 48 + load_size
    strings = meta + exports * 8
    export_offsets = {}
    for i in range(exports):
        offset, name_offset = struct.unpack_from(">II", blob, meta + i * 8)
        start = strings + name_offset
        name = blob[start:blob.index(b"\0", start)].decode("ascii")
        export_offsets[name] = offset
    assert set(export_offsets) == {"gBattleStage"}, (path, export_offsets)
    stage = export_offsets["gBattleStage"]
    assert stage + 0x28 <= load_size, path

    relocs = strings + ((strings_size + 3) & ~3) + dtors * 4
    r32 = set(struct.unpack_from(f">{r32_count}I", blob, relocs))
    image = bytearray(blob[48:48 + load_size]) + bytearray(bss_size)
    for offset in r32:
        value = struct.unpack_from(">I", image, offset)[0]
        assert LINK_BASE <= value <= LINK_BASE + len(image), (path, offset, value)
        struct.pack_into(">I", image, offset, value + TEST_BASE - LINK_BASE)

    def internal_pointer(offset, required=False):
        value = struct.unpack_from(">I", image, offset)[0]
        if not required and value == 0:
            return None
        assert offset in r32, (path, "unrelocated stage pointer", offset)
        assert TEST_BASE <= value < TEST_BASE + len(image), (path, offset, value)
        return value - TEST_BASE

    # Asset names, entry scripts, background, foreground list, and stage formation.
    for offset in (0, 4, 8, 12, 16, 20, 24, 32):
        internal_pointer(stage + offset, required=offset in (0, 4))
    for offset in (0, 4, 8, 20):
        value = internal_pointer(stage + offset)
        if value is not None:
            assert image.index(0, value) > value, (path, "empty asset name")

    actor_count = struct.unpack_from(">I", image, stage + 28)[0]
    if actor_count:
        formation = internal_pointer(stage + 32, required=True)
        for i in range(actor_count):
            row = formation + i * 0x20
            # Stage-owned actors stay in the stage module; they are not engine imports.
            internal_pointer(row, required=True)
            internal_pointer(row + 8, required=True)
    return get_loaded_footprint(blob)


def check_area_references(elf, stages):
    references = 0
    areas = set()
    for symbol in elf.symbols:
        if not symbol.name.startswith("b_area_"):
            continue
        if symbol.name.endswith("_Formations"):
            stride, field = 0x14, 0x0C
        elif symbol.name.endswith("_Stages"):
            stride, field = 8, 4
            areas.add(symbol.name)
        else:
            continue
        section = elf.sections[symbol.shndx]
        start = symbol.value - section.addr
        assert symbol.size % stride == 0 and symbol.size >= stride, symbol.name
        assert not any(section.content[start + symbol.size - stride:start + symbol.size]), symbol.name
        for pos in range(start, start + symbol.size - stride, stride):
            address = struct.unpack_from(">I", section.content, pos + field)[0]
            offset = address - section.addr
            assert 0 <= offset < section.size, (symbol.name, address)
            name = section.content[offset:section.content.index(b"\0", offset)].decode("ascii")
            assert name in stages, (symbol.name, "missing stage overlay", name)
            references += 1
    assert areas and references
    return len(areas), references


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--version", default="us")
    args = parser.parse_args()
    build = ROOT / "ver" / args.version / "build"
    manifest = json.loads((build / "ovl/manifest.json").read_text())
    stages = {entry["name"]: entry for entry in manifest if entry["type_index"] == STAGE_TYPE}
    assert stages, "No stage overlays in the build manifest"
    sizes = [check_stage(ROOT / entry["ovl"]) for entry in stages.values()]
    elf = Elf32((build / "papermario.elf").read_bytes())
    areas, references = check_area_references(elf, stages)
    print(f"Validated {len(stages)} stage overlays and {references} references across {areas} areas.")
    print(f"Largest stage footprint: {max(sizes)} bytes, including persistent metadata.")


if __name__ == "__main__":
    main()
