"""Reads the ROM layout: which segments exist, in what order, and where.

Segment membership of a source file comes from segments.py. This module
answers the other half: the segments themselves, the order they occupy the
ROM in, and the VRAM address each one loads at.
"""

from pathlib import Path
from typing import Dict, List, Optional

import yaml


class VramClass:
    def __init__(self, name: str, spec: dict):
        self.name = name
        self.vram: Optional[int] = spec.get("vram")
        self.vram_symbol: Optional[str] = spec.get("vram_symbol")
        self.follows: List[str] = spec.get("follows") or []

    @property
    def vram_symbol_expr(self) -> Optional[str]:
        if self.vram_symbol:
            return self.vram_symbol
        # A class that follows others starts above them, which only the linker
        # can work out, so defer to the symbol written for it.
        if self.follows:
            return f"{self.name}_CLASS_VRAM"
        return None


class SegmentSpec:
    def __init__(self, spec: dict, classes: Dict[str, VramClass], subalign: int):
        self.name: str = spec["name"]
        self.vram_class = classes.get(spec["class"]) if spec.get("class") else None
        self.subalign: int = spec.get("subalign", subalign)
        self.max_size: Optional[int] = spec.get("max_size")
        self.vram_start: Optional[int] = spec.get("vram")
        if self.vram_start is None and self.vram_class is not None:
            self.vram_start = self.vram_class.vram

    @property
    def vram_expr(self) -> Optional[str]:
        """Where the segment starts, as the linker script spells it."""
        if self.vram_class is not None:
            symbol = self.vram_class.vram_symbol_expr
            if symbol:
                return symbol
        if self.vram_start is not None:
            return f"0x{self.vram_start:X}"
        return None


class Layout:
    def __init__(self, path: Path):
        cfg = yaml.safe_load(path.read_text())
        subalign = (cfg.get("defaults") or {}).get("subalign", 8)
        self.classes = {
            name: VramClass(name, spec or {})
            for name, spec in (cfg.get("classes") or {}).items()
        }
        self.segments = [
            SegmentSpec(spec, self.classes, subalign) for spec in cfg["segments"]
        ]

        assets = cfg.get("assets") or {}
        self.asset_dirs: Dict[str, str] = assets.get("dirs") or {}
        self.asset_each: Dict[str, str] = assets.get("each") or {}
        self.asset_files: Dict[str, str] = assets.get("files") or {}
        self.packed = [Path(p) for p in cfg.get("packed") or []]
        self.imgfx: List[str] = cfg.get("imgfx") or []
        self.charsets: List[str] = cfg.get("charsets") or []
        self.asset_stack: List[str] = cfg.get("asset_stack") or []

    @property
    def follows(self) -> Dict[str, List[str]]:
        return {c.name: c.follows for c in self.classes.values() if c.follows}

    @property
    def packed_dirs(self) -> set:
        """Packed directories relative to an asset layer."""
        return {
            Path(*p.parts[2:]).as_posix() if p.parts[:1] == ("assets",) else p.as_posix()
            for p in self.packed
        }

    def is_packed(self, asset: Path) -> bool:
        """Whether an image is packed into a blob rather than a texture itself.

        Compared without the asset layer, so a texture overridden in another
        layer is classified the same as the one it replaces.
        """
        def strip(path: Path) -> Path:
            parts = path.parts
            return Path(*parts[2:]) if parts[:1] == ("assets",) else path

        target = strip(asset)
        for root in self.packed:
            stripped = strip(root)
            if target == stripped or stripped in target.parents:
                return True
        return False

    def segment_of_asset(self, object_path: Path) -> Optional[str]:
        """Which segment links an asset object, or None if nothing does."""
        asset = object_path.with_suffix("")  # drop .o
        if asset.as_posix() in self.asset_files:
            return self.asset_files[asset.as_posix()]
        for parent in asset.parents:
            key = parent.as_posix()
            if key in self.asset_each:
                # bg_1.png and bg_1.pal are both part of the bg_1 segment.
                stem = asset.name.split(".")[0]
                return self.asset_each[key] + stem
            if key in self.asset_dirs:
                return self.asset_dirs[key]
        return None
