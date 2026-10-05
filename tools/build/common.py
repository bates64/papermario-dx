from functools import lru_cache
from itertools import zip_longest
import os
import shutil
import sys
from pathlib import Path
from typing import Iterable, Optional, Tuple

ROOT = Path(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
ASSETS_DIR = ROOT / "assets"


def star_rod() -> str:
    """The path of the program that runs Star Rod: the one on PATH, else the repo's wrapper.

    It is a full path because Windows only finds star-rod.bat by name through
    a shell. The wrapper fetches the toolchain when it is missing. Run it from
    the root.
    """
    found = shutil.which("star-rod")
    if found:
        return found
    return "tools\\star-rod.bat" if sys.platform == "win32" else "tools/star-rod.sh"


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
    from assets import is_deleted

    for layer in asset_stack:
        potential_path = ROOT / layer / asset
        if potential_path.exists():
            if is_deleted(potential_path, [str(s) for s in asset_stack]):
                raise FileNotFoundError(
                    f"Asset {asset} is used, but its .meta sets delete: true"
                )
            return potential_path
    raise FileNotFoundError(f"Could not find asset {asset}")


def iter_in_groups(iterable, n, fillvalue=None):
    args = [iter(iterable)] * n
    return zip_longest(*args, fillvalue=fillvalue)
