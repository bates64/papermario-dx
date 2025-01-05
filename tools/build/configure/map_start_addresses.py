import yaml
from typing import Optional

kv = {}
with open("ver/us/splat.yaml") as file:
    config = yaml.safe_load(file)
    for segment in config["segments"]:
        if isinstance(segment, dict):
            if segment.get("vram_class") == "map":
                kv[segment["name"]] = segment["start"]

def get(map_name: str) -> Optional[int]:
    return kv.get(map_name)
