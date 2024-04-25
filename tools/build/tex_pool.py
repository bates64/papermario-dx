#!/usr/bin/env python3

import os
import argparse
import json
from sys import path
from pathlib import Path, PosixPath
from typing import Dict, List, Tuple
from common import get_asset_path
from dataclasses import dataclass

path.append(str(Path(__file__).parent.parent / "splat"))
path.append(str(Path(__file__).parent.parent / "build"))

path.append(str(Path(__file__).parent.parent))
from splat_ext.tex_archives import (
    AUX_COMBINE_MODES_INV,
    TILES_BASIC,
    TILES_INDEPENDENT_AUX,
    TILES_MIPMAPS,
    TILES_SHARED_AUX,
    TexImage,
    get_format_code,
)

ASSETS_DIR = Path(__file__).parent.parent.parent / "assets"


# read texture properties from dictionary and load images
def img_from_json(json_data, asset_stack: Tuple[Path, ...]) -> TexImage:
    ret = TexImage()

    ret.img_name = json_data["name"]

    # read data for main tile
    main_data = json_data.get("main")
    if main_data == None:
        raise Exception(f"Texture {ret.img_name} has no definition for 'main'")

    (main_fmt_name, ret.main_hwrap, ret.main_vwrap) = ret.read_json_img(main_data, "main", ret.img_name)
    (ret.main_fmt, ret.main_depth) = get_format_code(main_fmt_name)

    # read main image
    img_path = get_asset_path(Path(f"tex_pool/{ret.img_name}.png"), asset_stack)
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
        img_path = get_asset_path(Path(f"tex_pool/{ret.img_name}_AUX.png"), asset_stack)
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
                    Path(f"tex_pool/{ret.img_name}_MM{mipmap_idx}.png"),
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


def collect_texture_files(asset_stack: Tuple[Path, ...]) -> Dict[str, PosixPath]:
    jsons: Dict[str, PosixPath] = {}

    for asset_dir in asset_stack:
        pool_dir = ASSETS_DIR / asset_dir / "tex_pool"
        if not pool_dir.exists():
            continue  # asset dir may be missing pool_dir

        for filename in os.listdir(pool_dir):
            if not filename.endswith(".json"):
                continue  # find only json files for textures

            # remove extension to get base texture name
            tex_name = filename[:-5]

            if tex_name in jsons:
                continue  # asset already exists

            # associate file path with base texture name
            jsons[tex_name] = asset_dir / "tex_pool" / filename

    return jsons


@dataclass
class TexPoolEntry:
    name: str
    start: int
    end: int


def build(out_path: Path, out_header: Path, asset_stack: Tuple[Path, ...]):
    out_bytes = bytearray()
    entries: List[TexPoolEntry] = []
    jsons = collect_texture_files(asset_stack)

    for tex_name, json_path in sorted(jsons.items()):
        start = len(out_bytes)

        with open(ASSETS_DIR / json_path) as json_file:
            json_str = json_file.read()
            json_data = json.loads(json_str)
            tex = img_from_json(json_data, asset_stack)
            tex.add_bytes(out_bytes)

        end = len(out_bytes)
        entries.append(TexPoolEntry(tex_name, start, end))

    with open(out_path, "wb") as out_bin:
        out_bin.write(out_bytes)

    with open(out_header, "w") as f:
        f.write('#include "dx/texture_pool.h"\n')
        f.write("\n")
        f.write("TexPoolEntry gTexturePoolEntries[] = {\n")
        for entry in entries:
            f.write(f'    {{ "{entry.name}", 0x{entry.start:X}, 0x{entry.end:X}, TXP_UNASSIGNED }},\n')
        f.write("    {} // blank final entry\n")
        f.write("};\n")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Icon archive")
    parser.add_argument("out_bin", type=Path, help="output binary file path")
    parser.add_argument("header_path", type=Path, help="output header file to generate")
    parser.add_argument("asset_stack", help="comma-separated asset stack")
    args = parser.parse_args()

    asset_stack = tuple(Path(d) for d in args.asset_stack.split(","))

    build(args.out_bin, args.header_path, asset_stack)
