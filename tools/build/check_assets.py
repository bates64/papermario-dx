#!/usr/bin/env python3
"""Checks that assets describe themselves as well as splat.yaml describes them.

Reads every image splat declares and compares it against what assets.py works
out from the file and its sidecars. Run this after touching png.py, assets.py
or a .meta file:

    python3 tools/build/check_assets.py
"""

import contextlib
import io
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))

from assets import Texture

ROOT = Path(__file__).parents[2]


def declared_images():
    """Every image splat.yaml declares, with the attributes it declares."""
    import splat
    import splat.scripts.split as split

    sys.argv = ["check_assets.py"]
    quiet = io.StringIO()
    with contextlib.redirect_stdout(quiet), contextlib.redirect_stderr(quiet):
        split.main([ROOT / "ver/us/splat.yaml"], ["ld"], verbose=False)

    images = {}

    def visit(segment):
        if isinstance(segment, splat.segtypes.n64.img.N64SegImg):
            image = segment.n64img
            images[Path(segment.out_path()).resolve()] = {
                "format": segment.type,
                "width": image.width,
                "height": image.height,
                "flip_x": bool(getattr(image, "flip_h", False)),
                "flip_y": bool(getattr(image, "flip_v", False)),
                "namespaced": "namespaced" in (getattr(segment, "args", []) or []),
            }
        for child in getattr(segment, "subsegments", []) or []:
            visit(child)

    visited = set()
    for entry in split.linker_writer.entries:
        parent = entry.segment.get_most_parent()
        if id(parent) not in visited:
            visited.add(id(parent))
            visit(parent)
    return images


def main() -> int:
    mismatches = []
    images = declared_images()
    for path, declared in sorted(images.items()):
        texture = Texture(path.relative_to(ROOT), ("mod", "dx", "us"))
        found = {
            "format": texture.format,
            "width": texture.width,
            "height": texture.height,
            "flip_x": texture.flip_x,
            "flip_y": texture.flip_y,
            "namespaced": texture.namespaced,
        }
        for key, want in declared.items():
            if found[key] != want:
                rel = path.relative_to(ROOT)
                mismatches.append(f"{rel}: {key} is {found[key]!r}, declared {want!r}")

    print(f"checked {len(images)} images")
    for line in mismatches:
        print(f"  {line}")
    if mismatches:
        print(f"{len(mismatches)} mismatches")
        return 1
    print("all images match their splat.yaml declaration")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
