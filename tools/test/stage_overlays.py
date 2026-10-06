#!/usr/bin/env python3
"""Validate built battle-area/stage modules, relocations, and catalog references.

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
AREA_TYPE = 4
STAGE_TYPE = 5
ACTOR_TYPE = 6


def load_image(path, export_name):
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
    assert set(export_offsets) == {export_name}, (path, export_offsets)
    entry = export_offsets[export_name]
    assert entry < load_size, path

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
        assert offset in r32, (path, "unrelocated internal pointer", offset)
        assert TEST_BASE <= value < TEST_BASE + len(image), (path, offset, value)
        return value - TEST_BASE

    return blob, entry, image, internal_pointer, r32


def check_stage(path):
    blob, stage, image, internal_pointer, _ = load_image(path, "gBattleStage")
    assert stage + 0x28 <= len(image), path
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
            home = struct.unpack_from(">i", image, row + 8)[0]
            if home >= -270000000:  # EVT_LIMIT: standard home-position index
                assert 0 <= home <= 16, (path, row, home)
            else:
                internal_pointer(row + 8, required=True)
    return get_loaded_footprint(blob)


def check_area(path, stages, actors, vine_base):
    blob, area, image, pointer, r32 = load_image(path, "gBattleArea")
    battle_count, stage_count = struct.unpack_from(">II", image, area + 8)
    references = 0

    def string(offset):
        start = pointer(offset, required=True)
        return image[start:image.index(0, start)].decode("ascii")

    for offset, count, stride, field in ((0, battle_count, 0x14, 12), (4, stage_count, 8, 4)):
        start = pointer(area + offset, required=True)
        end = start + count * stride
        assert end + stride <= len(image), path
        assert not any(image[end:end + stride]), (path, "missing table terminator")
        for row in range(start, end, stride):
            # Battle debug names are SJIS, so validate termination without decoding.
            image.index(0, pointer(row, required=True))
            assert string(row + field) in stages, (path, row)
            references += 1
            if offset != 0:
                continue
            pointer(row + 16)  # optional onBattleStart script
            formation = pointer(row + 8, required=True)
            actor_count = struct.unpack_from(">I", image, row + 4)[0]
            assert formation + actor_count * 0x20 <= len(image), path
            for actor in range(formation, formation + actor_count * 0x20, 0x20):
                blueprint = pointer(actor)
                overlay = pointer(actor + 4)
                assert (blueprint is None) != (overlay is None), (path, actor)
                if overlay is not None:
                    assert string(actor + 4) in actors, (path, actor)
                home = struct.unpack_from(">i", image, actor + 8)[0]
                if home >= -270000000:
                    assert 0 <= home <= 16, (path, actor, home)
                else:
                    pointer(actor + 8, required=True)

    dma_count = struct.unpack_from(">I", image, area + 20)[0]
    dma = pointer(area + 16, required=dma_count != 0)
    assert (dma is None) == (dma_count == 0), path
    if dma_count:
        for row in range(dma, dma + dma_count * 12, 12):
            start, end, dest = struct.unpack_from(">III", image, row)
            assert not r32.intersection((row, row + 4, row + 8)), path
            assert 0 < end - start <= 0x4000, (path, row)
            assert dest == vine_base, (path, row, dest, vine_base)
    return get_loaded_footprint(blob), references


def check_catalog(elf, areas):
    symbols = {symbol.name: symbol for symbol in elf.symbols}
    assert not any(name.startswith("b_area_") for name in symbols), "Area symbols remain resident"
    symbol = symbols["gBattleAreas"]
    section = elf.sections[symbol.shndx]
    start = symbol.value - section.addr
    assert symbol.size % 8 == 0
    catalog = []
    for row in range(start, start + symbol.size, 8):
        for field in (0, 4):
            address = struct.unpack_from(">I", section.content, row + field)[0]
            offset = address - section.addr
            assert 0 <= offset < section.size, address
            name = section.content[offset:section.content.index(b"\0", offset)].decode("ascii")
            assert name
            if field == 4:
                catalog.append(name)
    assert len(catalog) == len(set(catalog)), "Duplicate catalog entry"
    assert set(catalog) == set(areas), (set(catalog) - set(areas), set(areas) - set(catalog))

    # The animation scratch buffers must not move with the KZN2 module.
    for i, size in enumerate((0x4000, 0x3000, 0x3000, 0x2000)):
        symbol = symbols[f"Vine{i}Base"]
        assert elf.sections[symbol.shndx].name == ".heaps_legacy_bss", symbol.name
        assert symbol.size == size, symbol.name
    return symbols["Vine0Base"].value


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--version", default="us")
    args = parser.parse_args()
    build = ROOT / "ver" / args.version / "build"
    manifest = json.loads((build / "ovl/manifest.json").read_text())
    stages = {entry["name"]: entry for entry in manifest if entry["type_index"] == STAGE_TYPE}
    areas = {entry["name"]: entry for entry in manifest if entry["type_index"] == AREA_TYPE}
    actors = {entry["name"] for entry in manifest if entry["type_index"] == ACTOR_TYPE}
    assert stages and areas, "No battle overlays in the build manifest"
    sizes = [check_stage(ROOT / entry["ovl"]) for entry in stages.values()]
    elf = Elf32((build / "papermario.elf").read_bytes())
    vine_base = check_catalog(elf, areas)
    area_results = [check_area(ROOT / entry["ovl"], stages, actors, vine_base) for entry in areas.values()]
    references = sum(refs for _, refs in area_results)
    print(f"Validated {len(stages)} stage overlays and {references} references across {len(areas)} area overlays.")
    print(f"Largest loaded stage: {max(sizes)} bytes; largest area: {max(size for size, _ in area_results)} bytes.")


if __name__ == "__main__":
    main()
