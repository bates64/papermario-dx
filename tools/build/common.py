from functools import lru_cache
from itertools import zip_longest
import os
from pathlib import Path
from typing import Iterable, Optional, Tuple

ROOT = Path(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
ASSETS_DIR = ROOT / "assets"


def layer_relative(path: Path, asset_stack: Iterable) -> Optional[Path]:
    """Where a path sits within the asset layer holding it, or None if no layer does.

    Each layer is a directory relative to the root, such as `src` or `assets/us`,
    so `assets/us/sprite/npc` is `sprite/npc` within the `assets/us` layer.
    """
    path = Path(path)
    if path.is_absolute():
        path = path.relative_to(ROOT)
    for layer in asset_stack:
        try:
            return path.relative_to(layer)
        except ValueError:
            pass
    return None


@lru_cache(maxsize=None)
def get_asset_path(asset: Path, asset_stack: Tuple[Path, ...]) -> Path:
    """The file for an asset in the highest layer that has it."""
    for layer in asset_stack:
        potential_path = ROOT / layer / asset
        if potential_path.exists():
            return potential_path
    raise FileNotFoundError(f"Could not find asset {asset}")


def iter_in_groups(iterable, n, fillvalue=None):
    args = [iter(iterable)] * n
    return zip_longest(*args, fillvalue=fillvalue)
