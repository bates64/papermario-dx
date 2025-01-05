from pathlib import Path, PurePath
from os import PathLike
from typing import Generator, List

# This unused import makes the yaml library faster. don't remove
import pylibyaml  # pyright: ignore
import yaml

def read_asset_dirs_from_yaml(yaml_path: Path) -> List[Path]:
    with open(yaml_path, "r") as file:
        asset_stack = yaml.safe_load(file)["asset_stack"]
    dirs = [Path("assets") / asset_dir for asset_dir in asset_stack]
    for d in dirs:
        if not d.exists():
            raise FileNotFoundError(d)
        if not d.is_dir():
            raise NotADirectoryError(d)
    return dirs

class AssetPath(PurePath):
    def __init__(self, asset_dirs: List[Path], *pathsegments):
        self.asset_dirs = asset_dirs
        super().__init__(*pathsegments)

    def with_segments(self, *pathsegments):
        """Construct a new path object from any number of path-like objects.
        Subclasses may override this method to customize how new path objects
        are created from methods like `iterdir()`.
        """
        return type(self)(self.asset_dirs, *pathsegments)

    def _make_child_relpath(self, name):
        path_str = str(self)
        tail = self._tail
        if tail:
            path_str = f'{path_str}{self._flavour.sep}{name}'
        elif path_str != '.':
            path_str = f'{path_str}{name}'
        else:
            path_str = name
        path = self.with_segments(path_str)
        path._str = path_str
        path._drv = self.drive
        path._root = self.root
        path._tail_cached = tail + [name]
        return path

    def iterdir(self, recursive=False) -> Generator["AssetPath", None, None]:
        seen = set()
        for asset_dir in self.asset_dirs:
            try:
                resolved_parent = self.resolve_for_asset_dir(asset_dir)
            except FileNotFoundError:
                continue

            for resolved_child in resolved_parent.iterdir():
                if resolved_child.name in seen:
                    continue
                seen.add(resolved_child.name)

                child = self._make_child_relpath(resolved_child.name)
                if recursive and child.is_dir():
                    yield from child.iterdir(recursive=True)
                yield child

    def resolve(self) -> Path:
        for asset_dir in self.asset_dirs:
            full_path = asset_dir / self
            if full_path.exists():
                return full_path
        raise FileNotFoundError(self)

    def resolve_for_asset_dir(self, asset_dir: Path) -> Path:
        full_path = asset_dir / self
        if full_path.exists():
            return full_path
        raise FileNotFoundError(full_path)

    def exists(self) -> bool:
        try:
            self.resolve()
            return True
        except FileNotFoundError:
            return False

    def is_file(self) -> bool:
        try:
            return self.resolve().is_file()
        except FileNotFoundError:
            return False

    def is_dir(self) -> bool:
        try:
            return self.resolve().is_dir()
        except FileNotFoundError:
            return False

    def open(self, *args, **kwargs):
        return self.resolve().open(*args, **kwargs)

PathLike.register(AssetPath)
