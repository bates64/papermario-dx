#!/usr/bin/env python3

import re
import argparse
from pathlib import Path
from typing import Dict, Optional, Tuple
from assets import is_deleted
from common import ROOT, get_asset_path
from raster import Png
from img.build import Converter
import png


def get_img_file(fmt_str, img_file: str):
    def pack_color(r, g, b, a):
        r = r >> 3
        g = g >> 3
        b = b >> 3
        a = a >> 7

        return (r << 11) | (g << 6) | (b << 1) | a

    (out_img, out_w, out_h) = Converter(mode=fmt_str.lower(), infile=img_file).convert()

    out_pal = bytearray()
    if fmt_str == "CI4" or fmt_str == "CI8":
        img = png.Reader(img_file)
        img.preamble(True)
        palette = img.palette(alpha="force")
        for rgba in palette:
            if rgba[3] not in (0, 0xFF):
                print("alpha mask mode but translucent pixels used")

            color = pack_color(*rgba)
            out_pal += color.to_bytes(2, byteorder="big")

    return (out_img, out_pal, out_w, out_h)


def find_icons(asset_stack: Tuple[Path, ...]) -> Dict[str, Optional[Path]]:
    """Every icon's PNG, keyed by its name, such as key/Gift.

    An icon is a pair, with a palette for when it is disabled, if it has a
    <name>.disabled.png; that file is the value, or None for other icons.
    """
    found: Dict[str, Path] = {}
    for layer in reversed(asset_stack):
        root = ROOT / layer / "icon"
        if layer != asset_stack[-1] and (root / "Icons.xml").exists():
            raise Exception(
                f"{layer}/icon/Icons.xml isn't used anymore, so delete it. The build finds icons from their PNG files."
            )
        for path in root.glob("**/*.png"):
            found[path.relative_to(root).with_suffix("").as_posix()] = path

    def kept(name: str) -> bool:
        return name in found and not is_deleted(found[name], asset_stack)

    return {
        name: found[name + ".disabled"] if kept(name + ".disabled") else None
        for name in sorted(found)
        if not name.endswith(".disabled") and kept(name)
    }


def build(out_bin: Path, out_header: Path, asset_stack: Tuple[Path, ...]):
    out_bytes = bytearray()
    offsets: Dict[str, int] = {}

    for file, disabled in find_icons(asset_stack).items():
        img_path = get_asset_path(Path(f"icon/{file}.png"), asset_stack)
        fmt = Png(img_path).format()
        name = re.sub("\\W", "_", file)

        if disabled is not None and fmt != "ci4":
            raise Exception(
                f"{img_path.relative_to(ROOT)} is {fmt.upper()}, so it can't use the disabled palette from {disabled.relative_to(ROOT)}. "
                "Save it as CI4, or delete the disabled icon with a .meta file containing 'delete: true'."
            )

        if fmt == "ci4":
            (out_img, out_pal, out_w, out_h) = get_img_file("CI4", str(img_path))

            offsets[name + "_raster"] = len(out_bytes)
            out_bytes += out_img

            offsets[name + "_palette"] = len(out_bytes)
            out_bytes += out_pal

            if disabled is not None:
                (out_img, out_pal, out_w, out_h) = get_img_file("CI4", str(disabled))

                offsets[name + "_disabled_raster"] = offsets[name + "_raster"]
                offsets[name + "_disabled_palette"] = len(out_bytes)
                out_bytes += out_pal

        elif fmt == "rgba16":
            (out_img, out_pal, out_w, out_h) = get_img_file("RGBA16", str(img_path))

            offsets[name + "_raster"] = len(out_bytes)
            out_bytes += out_img

        else:
            raise Exception(f"{img_path}: icons must be CI4 or RGBA16, but this image is {fmt.upper()}")

    with open(out_bin, "wb") as f:
        f.write(out_bytes)

    with open(out_header, "w", encoding="utf-8") as f:
        f.write("#ifndef ICON_OFFSETS_H\n")
        f.write("#define ICON_OFFSETS_H\n")
        f.write(f"/* This file is auto-generated. Do not edit. */\n\n")

        for name, offset in offsets.items():
            f.write(f"#define ICON_{name} 0x{offset:X}\n")

        f.write("\n#endif // ICON_OFFSETS_H\n")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Icon archive")
    parser.add_argument("out_bin", type=Path, help="output binary file path")
    parser.add_argument("header_path", type=Path, help="output header file to generate")
    parser.add_argument("asset_stack", help="comma-separated asset stack")
    args = parser.parse_args()

    asset_stack = tuple(Path(d) for d in args.asset_stack.split(","))

    build(args.out_bin, args.header_path, asset_stack)
