#!/usr/bin/env python3
"""Packs every map texture into one pool, which models find their textures in by name.

The textures come from each texture archive in mapfs/tex, across the asset stack.
Within the pool, each archive's textures stay together and in their archive's
order, so a model's texture variants still follow its texture.
"""

import argparse
import json
import os
from pathlib import Path
from sys import path
from typing import Dict, List, Tuple

path.append(str(Path(__file__).parent))
path.append(str(Path(__file__).parent.parent))
path.append(str(Path(__file__).parent.parent / "splat"))

from assets import is_deleted
from common import ROOT, get_asset_path
from splat_ext.tex_archives import (
    AUX_COMBINE_MODES_INV,
    TILES_BASIC,
    TILES_INDEPENDENT_AUX,
    TILES_MIPMAPS,
    TILES_SHARED_AUX,
    TexImage,
    get_format_code,
)
# read texture properties from dictionary and load images
def img_from_json(json_data, tex_name: str, asset_stack: Tuple[Path, ...]) -> TexImage:
    ret = TexImage()

    ret.img_name = json_data["name"]

    # read data for main tile
    main_data = json_data.get("main")
    if main_data == None:
        raise Exception(f"Texture {ret.img_name} has no definition for 'main'")

    (main_fmt_name, ret.main_hwrap, ret.main_vwrap) = ret.read_json_img(main_data, "main", ret.img_name)
    (ret.main_fmt, ret.main_depth) = get_format_code(main_fmt_name)

    # read main image
    img_path = get_asset_path(Path(f"mapfs/tex/{tex_name}/{ret.img_name}.png"), asset_stack)
    if not os.path.isfile(img_path):
        raise Exception(f"Could not find main image for texture: {ret.img_name}")
    (
        ret.main_img,
        ret.main_pal,
        ret.main_width,
        ret.main_height,
    ) = ret.get_img_file(main_fmt_name, str(img_path))

    # read data for aux tile
    ret.has_aux = "aux" in json_data
    if ret.has_aux:
        aux_data = json_data.get("aux")
        (aux_fmt_name, ret.aux_hwrap, ret.aux_vwrap) = ret.read_json_img(aux_data, "aux", ret.img_name)

        if aux_fmt_name == "Shared":
            # aux tiles have blank attributes in SHARED mode
            aux_fmt_name = main_fmt_name
            ret.aux_fmt = 0
            ret.aux_depth = 0
            ret.aux_hwrap = 0
            ret.aux_vwrap = 0
            ret.extra_tiles = TILES_SHARED_AUX
        else:
            (ret.aux_fmt, ret.aux_depth) = get_format_code(aux_fmt_name)
            ret.extra_tiles = TILES_INDEPENDENT_AUX

        # read aux image
        img_path = get_asset_path(Path(f"mapfs/tex/{tex_name}/{ret.img_name}_AUX.png"), asset_stack)
        if not os.path.isfile(img_path):
            raise Exception(f"Could not find AUX image for texture: {ret.img_name}")
        (
            ret.aux_img,
            ret.aux_pal,
            ret.aux_width,
            ret.aux_height,
        ) = ret.get_img_file(aux_fmt_name, str(img_path))
        if ret.extra_tiles == TILES_SHARED_AUX:
            # aux tiles have blank sizes in SHARED mode
            ret.main_height *= 2
            ret.aux_width = 0
            ret.aux_height = 0

    else:
        ret.aux_fmt = 0
        ret.aux_depth = 0
        ret.aux_hwrap = 0
        ret.aux_vwrap = 0
        ret.aux_width = 0
        ret.aux_height = 0
        ret.extra_tiles = TILES_BASIC

    # read mipmaps
    ret.has_mipmaps = json_data.get("hasMipmaps", False)
    if ret.has_mipmaps:
        ret.mipmaps = []
        mipmap_idx = 1
        divisor = 2
        if ret.main_width >= (32 >> ret.main_depth):
            while True:
                if (ret.main_width // divisor) <= 0:
                    break
                mmw = ret.main_width // divisor
                mmh = ret.main_height // divisor

                img_path = get_asset_path(
                    Path(f"mapfs/tex/{tex_name}/{ret.img_name}_MM{mipmap_idx}.png"),
                    asset_stack,
                )
                if not os.path.isfile(img_path):
                    raise Exception(
                        f"Texture {ret.img_name} is missing mipmap level {mipmap_idx} (size = {mmw} x {mmh})"
                    )

                (raster, pal, width, height) = ret.get_img_file(main_fmt_name, str(img_path))
                ret.mipmaps.append(raster)
                if width != mmw or height != mmh:
                    raise Exception(
                        f"Texture {ret.img_name} has wrong size for mipmap level {mipmap_idx} \n"
                        + f"MM{mipmap_idx} size = {width} x {height}, but should be = {mmw} x {mmh}"
                    )

                divisor = divisor * 2
                mipmap_idx += 1
                if (ret.main_width // divisor) < (16 >> ret.main_depth):
                    break
        ret.extra_tiles = TILES_MIPMAPS

    # read filter mode
    if json_data.get("filter", False):
        ret.filter_mode = 2
    else:
        ret.filter_mode = 0

    # read tile combine mode
    combine_str = json_data.get("combine", "Missing")
    ret.combine = AUX_COMBINE_MODES_INV.get(combine_str)
    if ret.combine == None:
        raise Exception(f"Texture {ret.img_name} has invalid 'combine'")

    ret.is_variant = json_data.get("variant", False)

    return ret


def archive_names(asset_stack: Tuple[Path, ...]) -> List[str]:
    """Every texture archive in any layer that no .meta deletes, such as kmr_tex."""
    names = set()
    for layer in asset_stack:
        tex_dir = ROOT / layer / "mapfs" / "tex"
        if tex_dir.is_dir():
            names.update(p.stem for p in tex_dir.glob("*_tex.json") if not is_deleted(p, asset_stack))
    return sorted(names)


def hash_texture_name(name: str) -> int:
    """FNV-1a, as hash_texture_name in src/dx/texture_pool.c."""
    h = 0x811C9DC5
    for byte in name.encode("ascii"):
        h ^= byte
        h = (h * 0x01000193) & 0xFFFFFFFF
    return h


def build(out_path: Path, header_path: Path, asset_stack: Tuple[Path, ...]):
    out_bytes = bytearray()
    # each texture's name, start, size, and how many variants follow it
    entries: List[Tuple[str, int, int, int]] = []
    archive_of: Dict[str, str] = {}

    for archive in archive_names(asset_stack):
        with open(get_asset_path(Path(f"mapfs/tex/{archive}.json"), asset_stack)) as f:
            textures = json.load(f)

        for index, texture in enumerate(textures):
            name = texture["name"]
            if name in archive_of:
                raise Exception(f"Texture {name} is in both {archive_of[name]} and {archive}")
            archive_of[name] = archive

            variants = 0
            while index + 1 + variants < len(textures) and textures[index + 1 + variants].get("variant", False):
                variants += 1

            start = len(out_bytes)
            img_from_json(texture, archive, asset_stack).add_bytes(archive, out_bytes)
            entries.append((name, start, len(out_bytes) - start, variants))

    hashes: Dict[int, str] = {}
    for name, *_ in entries:
        h = hash_texture_name(name)
        if h in hashes:
            raise Exception(f"Textures {hashes[h]} and {name} have the same hash; rename one of them")
        hashes[h] = name
    by_hash = sorted((hash_texture_name(name), index) for index, (name, *_) in enumerate(entries))

    with open(out_path, "wb") as f:
        f.write(out_bytes)

    with open(header_path, "w") as f:
        f.write('#include "dx/texture_pool.h"\n\n')
        f.write(f"const s32 gTexturePoolCount = {len(entries)};\n\n")
        f.write("const TexPoolEntry gTexturePoolEntries[] = {\n")
        for name, start, size, _ in entries:
            f.write(f"    {{ 0x{start:X}, 0x{size:X} }}, // {name}\n")
        f.write("};\n\n")
        f.write("const u8 gTexturePoolVariantCounts[] = {\n")
        for name, _, _, variants in entries:
            f.write(f"    {variants}, // {name}\n")
        f.write("};\n\n")
        f.write("// Every texture's name hash, sorted, and the index in gTexturePoolEntries of the texture with each.\n")
        f.write("static const u32 gTexturePoolHashes[] = {\n")
        for h, _ in by_hash:
            f.write(f"    0x{h:08X},\n")
        f.write("};\n\n")
        f.write("static const u16 gTexturePoolHashIndices[] = {\n")
        for _, index in by_hash:
            f.write(f"    {index},\n")
        f.write("};\n\n")
        f.write(f"u8 gTexturePoolHandles[{len(entries)}];\n")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("out_bin", type=Path, help="the pool to write")
    parser.add_argument("header_path", type=Path, help="the table of the pool's textures to write")
    parser.add_argument("asset_stack", help="comma-separated asset stack, highest layer first")
    args = parser.parse_args()

    build(args.out_bin, args.header_path, tuple(Path(d) for d in args.asset_stack.split(",")))
