from functools import lru_cache
from itertools import zip_longest
import os
from pathlib import Path
from typing import Tuple

ASSETS_DIR = Path(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))) / "assets"


@lru_cache(maxsize=None)
def get_asset_path(asset: Path, asset_stack: Tuple[Path, ...]) -> Path:
    from assets import is_deleted

    for sdir in asset_stack:
        potential_path = ASSETS_DIR / sdir / asset
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
