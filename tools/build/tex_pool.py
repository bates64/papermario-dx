#!/usr/bin/env python3
"""Packs every map texture into one pool, which models find their textures in by name.

The textures come from each texture archive in mapfs/tex, across the asset stack.
Within the pool, each archive's textures stay together and in their archive's
order, so a model's texture variants still follow its texture.
"""

import argparse
import json
from pathlib import Path
from sys import path
from typing import Dict, List, Tuple

path.append(str(Path(__file__).parent))
path.append(str(Path(__file__).parent / "mapfs"))

from assets import is_deleted
from common import ROOT, get_asset_path
from tex import img_from_json


def archive_names(asset_stack: Tuple[Path, ...]) -> List[str]:
    """Every texture archive in any layer that no .meta deletes, such as kmr_tex."""
    names = set()
    for layer in asset_stack:
        tex_dir = ROOT / layer / "mapfs" / "tex"
        if tex_dir.is_dir():
            names.update(p.stem for p in tex_dir.glob("*_tex.json") if not is_deleted(p, asset_stack))
    return sorted(names)


def build(out_path: Path, header_path: Path, asset_stack: Tuple[Path, ...]):
    out_bytes = bytearray()
    entries: List[Tuple[str, int, int]] = []
    archive_of: Dict[str, str] = {}

    for archive in archive_names(asset_stack):
        with open(get_asset_path(Path(f"mapfs/tex/{archive}.json"), asset_stack)) as f:
            textures = json.load(f)

        for texture in textures:
            name = texture["name"]
            if name in archive_of:
                raise Exception(f"Texture {name} is in both {archive_of[name]} and {archive}")
            archive_of[name] = archive

            start = len(out_bytes)
            img_from_json(texture, archive, asset_stack).add_bytes(archive, out_bytes)
            entries.append((name, start, len(out_bytes)))

    with open(out_path, "wb") as f:
        f.write(out_bytes)

    with open(header_path, "w") as f:
        f.write('#include "dx/texture_pool.h"\n\n')
        f.write("TexPoolEntry gTexturePoolEntries[] = {\n")
        for name, start, end in entries:
            f.write(f'    {{ "{name}", 0x{start:X}, 0x{end:X}, TXP_UNASSIGNED }},\n')
        f.write("    {},\n")
        f.write("};\n")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("out_bin", type=Path, help="the pool to write")
    parser.add_argument("header_path", type=Path, help="the table of the pool's textures to write")
    parser.add_argument("asset_stack", help="comma-separated asset stack, highest layer first")
    args = parser.parse_args()

    build(args.out_bin, args.header_path, tuple(Path(d) for d in args.asset_stack.split(",")))
