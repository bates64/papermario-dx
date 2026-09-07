"""Resolves which ROM segment each source file links into.

Segment membership comes from the filesystem: a source file belongs to the
segment declared by its nearest ancestor directory in ver/<version>/segments.yaml.
Adding a source file to a directory that already has a rule needs no config
change; only creating a new segment does.
"""

from pathlib import Path
from typing import Dict, List

import yaml

SOURCE_SUFFIXES = (".c", ".cpp", ".s")


def _is_source(path: Path) -> bool:
    return path.suffix in SOURCE_SUFFIXES and not path.name.endswith(
        (".inc.c", ".inc.cpp")
    )


class SegmentMap:
    def __init__(self, config_path: Path, src_root: Path):
        cfg = yaml.safe_load(config_path.read_text())
        self.dirs: Dict[str, str] = cfg.get("dirs") or {}
        self.each: Dict[str, str] = cfg.get("each") or {}
        self.files: Dict[str, str] = cfg.get("files") or {}
        self.cflags: Dict[str, str] = cfg.get("cflags") or {}
        self.src_root = src_root
        # Overlays are linked separately, so their sources are not part of any
        # ROM segment even though they sit under a directory that declares one.
        self.excluded = {
            match
            for pattern in cfg.get("exclude") or []
            for match in Path().glob(pattern)
        }

    def is_excluded(self, path: Path) -> bool:
        return any(p in self.excluded for p in (path, *path.parents))

    def segment_of(self, path: Path) -> str:
        """Segment for one source file, or None if no rule covers it."""
        if self.is_excluded(path):
            return None
        key = path.as_posix()
        if key in self.files:
            return self.files[key]
        for parent in path.parents:
            d = parent.as_posix()
            if d in self.each:
                return self.each[d] + path.stem
            if d in self.dirs:
                return self.dirs[d]
        return None

    def scan(self) -> Dict[str, List[Path]]:
        """Map every segment to its source files, sorted for a stable link order.

        Sorting here rather than relying on linker wildcards keeps the link
        order identical across platforms.
        """
        found: Dict[str, List[Path]] = {}
        for path in self.src_root.rglob("*"):
            if not path.is_file() or not _is_source(path):
                continue
            seg = self.segment_of(path)
            if seg is None:
                continue
            found.setdefault(seg, []).append(path)
        return {
            seg: sorted(paths, key=lambda p: p.as_posix())
            for seg, paths in sorted(found.items())
        }
