"""Describes how to build an asset, mostly by looking at the asset itself.

A texture's format and size come from the PNG (see raster.py), so most assets
need no declaration at all. The handful whose intent the file cannot express
carry a sidecar: `<name>.png.meta` for one asset, or `.meta` in a directory
for every asset in it.
"""

import re
from functools import lru_cache
from pathlib import Path
from typing import Dict, List, Optional

import yaml

from raster import Png

DIRECTORY_SIDECAR = ".meta"
SIDECAR_SUFFIX = ".meta"


@lru_cache(maxsize=None)
def _sidecar(path: Path) -> Dict:
    if not path.is_file():
        return {}
    return yaml.safe_load(path.read_text()) or {}


def _layers(png_path: Path, asset_stack) -> List[Path]:
    """The asset's path in each layer of the stack, lowest priority first.

    Assets split from the ROM are not version controlled, so their sidecars
    live in a layer that is, and have to be found from there.
    """
    parts = list(png_path.parts)
    if len(parts) < 2 or parts[0] != "assets":
        return [png_path]
    paths = []
    for layer in reversed(list(asset_stack)):
        parts[1] = layer
        paths.append(Path(*parts))
    return paths


def metadata(png_path: Path, asset_stack=("us",)) -> Dict:
    """Sidecar values for an asset, the nearest declaration winning."""
    values: Dict = {}
    for path in _layers(png_path, asset_stack):
        for directory in reversed(path.parent.parents):
            values.update(_sidecar(directory / DIRECTORY_SIDECAR))
        values.update(_sidecar(path.parent / DIRECTORY_SIDECAR))
        values.update(_sidecar(path.with_suffix(path.suffix + SIDECAR_SUFFIX)))
    return values


class Texture:
    def __init__(self, path: Path, asset_stack=("us",)):
        self.path = path
        self.png = Png(path)
        meta = metadata(path, asset_stack)
        # Two N64 formats can encode identical pixels, so an asset that wants
        # the wider one has to say so.
        self.format: str = meta.get("format") or self.png.format()
        self.flip_x: bool = bool(meta.get("flip_x", False))
        self.flip_y: bool = bool(meta.get("flip_y", False))
        self.namespaced: bool = bool(meta.get("namespaced", False))

    @property
    def width(self) -> int:
        return self.png.width

    @property
    def height(self) -> int:
        return self.png.height

    def flags(self) -> str:
        return ("--flip-x " if self.flip_x else "") + (
            "--flip-y " if self.flip_y else ""
        )


INCLUDE_MACRO = re.compile(
    r'INCLUDE_(?:IMG|PAL)\(\s*"([^"]+)"\s*,\s*([A-Za-z_][A-Za-z0-9_]*)'
)


def include_symbols(src_root: Path) -> Dict[str, str]:
    """Asset path to the C symbol its generated header should define.

    A texture's dimensions are referred to by the name the source includes it
    under, so the generated header has to agree. An asset included twice under
    different names has no single answer and falls back to the file's name.
    """
    symbols: Dict[str, str] = {}
    seen = set()
    for source in sorted(src_root.rglob("*.c")):
        for asset, symbol in INCLUDE_MACRO.findall(source.read_text()):
            # An _OFFSET symbol addresses the asset's place in ROM rather
            # than naming the image.
            if symbol.endswith("_OFFSET"):
                continue
            if asset in symbols and symbols[asset] != symbol:
                seen.add(asset)
            symbols.setdefault(asset, symbol)
    for asset in seen:
        del symbols[asset]
    return symbols


def included_palettes(src_root: Path) -> set:
    """Assets whose palette the source includes, named by their image path.

    An indexed PNG only needs its palette split out if something asks for it.
    """
    palettes = set()
    for source in sorted(src_root.rglob("*.c")):
        for match in re.finditer(r'INCLUDE_PAL\(\s*"([^"]+)"', source.read_text()):
            palettes.add(str(Path(match.group(1)).with_suffix(".png")))
    return palettes
