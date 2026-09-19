"""Works out which segment each source file belongs to, and how to compile it.

A directory belongs to the segment its path names, so src/engine1 holds
engine1 and src/battle/area/arn holds battle/area/arn. A directory naming no
segment belongs to whichever its parent does, and src itself is main. Adding a
source file therefore needs no configuration; only the handful of directories
whose segment is not the one their path names are written down.
"""

from pathlib import Path
from typing import Dict, List, Optional

SOURCE_SUFFIXES = (".c", ".cpp", ".s")

# The console starts executing at the base of the main segment, so this file's
# code must be the first thing linked there whatever the sort order would be.
ENTRY_POINT = "src/boot/entry_point.s"


def _link_order(paths: List[Path]) -> List[Path]:
    ordered = sorted(paths, key=lambda p: p.as_posix())
    entry = next((p for p in ordered if p.as_posix() == ENTRY_POINT), None)
    if entry is not None:
        ordered.remove(entry)
        ordered.insert(0, entry)
    return ordered


def _is_source(path: Path) -> bool:
    return path.suffix in SOURCE_SUFFIXES and not path.name.endswith(
        (".inc.c", ".inc.cpp")
    )


class SegmentMap:
    def __init__(self, layout, src_root: Path):
        rules = layout.sources
        self.dirs: Dict[str, str] = rules.get("dirs") or {}
        self.each: Dict[str, str] = rules.get("each") or {}
        self.files: Dict[str, str] = rules.get("files") or {}
        self.cflag_dirs: Dict[str, str] = layout.cflags.get("dirs") or {}
        self.cflag_files: Dict[str, str] = layout.cflags.get("files") or {}
        self.src_root = src_root
        # Segment names are written as paths or with underscores depending on
        # the segment, so a directory may name one either way.
        self.segment_names = {seg.name for seg in layout.segments}
        # Overlays are linked separately, so their sources are not part of any
        # ROM segment even though they sit under a directory that declares one.
        self.excluded = {
            match
            for pattern in rules.get("exclude") or []
            for match in Path().glob(pattern)
        }

    def is_excluded(self, path: Path) -> bool:
        return any(p in self.excluded for p in (path, *path.parents))

    def segment_of(self, path: Path) -> Optional[str]:
        """Segment for one source file, or None if it belongs to no segment."""
        if self.is_excluded(path):
            return None
        if path.as_posix() in self.files:
            return self.files[path.as_posix()]
        for parent in path.parents:
            directory = parent.as_posix()
            if directory in self.dirs:
                return self.dirs[directory]
            if directory in self.each:
                return self.each[directory] + path.stem
            if directory == self.src_root.as_posix():
                return "main"
            relative = parent.relative_to(self.src_root).as_posix()
            for candidate in (relative, relative.replace("/", "_")):
                if candidate in self.segment_names:
                    return candidate
        return None

    def cflags(self, path: Path) -> Optional[str]:
        """The flags a source is compiled with, if not the default."""
        if path.as_posix() in self.cflag_files:
            return self.cflag_files[path.as_posix()]
        for parent in path.parents:
            if parent.as_posix() in self.cflag_dirs:
                return self.cflag_dirs[parent.as_posix()]
        return None

    def scan(self) -> Dict[str, List[Path]]:
        """Map every segment to its source files, in a stable link order.

        Sorting here rather than relying on linker wildcards keeps the link
        order identical across platforms.
        """
        found: Dict[str, List[Path]] = {}
        for path in self.src_root.rglob("*"):
            if not path.is_file() or not _is_source(path):
                continue
            segment = self.segment_of(path)
            if segment is None:
                continue
            found.setdefault(segment, []).append(path)
        return {
            segment: _link_order(paths) for segment, paths in sorted(found.items())
        }
