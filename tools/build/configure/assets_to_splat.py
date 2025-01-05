from pathlib import Path
from typing import List

# This unused import makes the yaml library faster. don't remove
import pylibyaml  # pyright: ignore
import yaml

from .asset_stack import AssetPath, read_asset_dirs_from_yaml
from . import map_start_addresses

# 64mb isn't the real max size for the n64 (it's unlimited with bank switching), but if you go over you are doing something wrong
END_OF_ROM = 64 * 1024 * 1024

class SegmentConfig:
    def __init__(self):
        self.data = {}

    def add_simple_subsegment(self, type: str, name: str, *rest: str):
        self.data["subsegments"].append([
            "auto",
            type,
            name,
            *rest,
        ])

class Generator:
    def __init__(self):
        self.asset_dirs = read_asset_dirs_from_yaml(Path("assets/stack.yaml"))
        self.segments = []

    def add_code_segment(self, name: str, vram_class: str, dir: AssetPath) -> SegmentConfig:
        config = SegmentConfig()
        config.data["type"] = "code"
        config.data["name"] = name
        config.data["dir"] = str(Path(dir))
        config.data["vram_class"] = vram_class
        config.data["subsegments"] = []
        self.segments.append(config.data)
        return config

    def add_all_maps(self):
        for area in AssetPath(self.asset_dirs, "world", "area").iterdir():
            if not area.is_dir():
                continue
            for map in area.iterdir():
                if not map.is_dir():
                    continue

                # Is it a map? heuristic
                if not (map / (map.name + ".h")).exists():
                    continue

                segment = self.add_code_segment(map.name, "map", map)

                # If the map exists in vanilla, fetch its start address from there
                # This prevents "img with vram_start unset" errors by allowing splat to calculate an offset from the vram_class
                start = map_start_addresses.get(map.name)
                if start is not None:
                    segment.data["start"] = start

                # Look for optional map config
                map_yaml = map / "map.yaml"
                if map_yaml.exists():
                    with map_yaml.open() as file:
                        info = yaml.safe_load(file)

                        # If the map.yaml specifies segments, use that instead of auto-generating subsegments
                        if "segments" in info:
                            segment.data["subsegments"] = info["segments"]
                            continue # skip auto-generating segments
                        if "subsegments" in info:
                            print(f"error: {map_yaml.resolve()} should have 'segments' instead of 'subsegments'")
                            exit(1)

                # Auto-generate subsegments
                for source_file in map.iterdir(recursive=True):
                    if source_file.stem.endswith(".inc"):
                        pass
                    elif source_file.suffix in [".yaml", ".h", ".hpp", ".md", ".txt"]:
                        pass
                    elif source_file.suffix == ".c":
                        segment.add_simple_subsegment("c", source_file.relative_to(map).with_suffix("").as_posix())
                    elif source_file.suffix == ".cpp":
                        segment.add_simple_subsegment("cpp", source_file.relative_to(map).with_suffix("").as_posix())
                    elif source_file.is_dir():
                        pass
                    else:
                        # TODO: consider turning into a hard error that requires user to create a map.yaml with segments list
                        print(f"warning: cannot automatically generate segment for {source_file}")

    def dump(self, file):
        self.segments.sort(key=lambda segment: segment.get("start", END_OF_ROM))
        yaml.dump({
            "segments": self.segments + [[END_OF_ROM]],
        }, file)

def generate_splat_yaml_for_assets() -> str:
    """
    Generates a splat-assets.yaml config file from the assets directory.
    """

    generator = Generator()
    generator.add_all_maps()

    file_path = Path("ver/dx/build/splat-assets.yaml")
    file_path.parent.mkdir(parents=True, exist_ok=True)
    with open(file_path, "w") as file:
        generator.dump(file)
    return file_path

def find_splat_yamls_in_asset_dirs() -> List[str]:
    # Every asset stack can provide a splat.yaml for advanced configuration
    ret = []
    for dir in read_asset_dirs_from_yaml(Path("assets/stack.yaml")):
        path = dir / "splat.yaml"
        if path.exists():
            ret.append(path.as_posix())
    return ret
