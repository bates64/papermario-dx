#!/usr/bin/env python3

from sys import argv, stderr
from os import path
from xml.dom.minidom import parse
from pathlib import Path


def eprint(*args, **kwargs):
    print(*args, file=stderr, **kwargs)


seen = set()
duplicate_warned = set()
def write_if_unique(f, name, value):
    """
    Write a define to the file if it is not already defined.
    Print a warning the first time a non-unique name is used (per name).
    """
    global seen, duplicate_warned
    if name in seen:
        if name not in duplicate_warned:
            print(f"warning: duplicate: {name}")
            duplicate_warned.add(name)
        return
    seen.add(name)
    f.write(f"#define {name} {value}\n")


if __name__ == "__main__":
    _, xml_path, out_path = argv

    xml = parse(xml_path)

    out_path = Path(out_path)
    f = out_path.open("w")

    is_shape = out_path.stem.endswith("_shape")
    is_hit = out_path.stem.endswith("_hit")
    is_combined = not is_shape and not is_hit

    map_name = path.basename(xml_path)[:-4]

    if is_shape or is_combined:
        for model in xml.getElementsByTagName("Model"):
            map_object = model.getElementsByTagName("MapObject")[0]
            name = map_object.getAttribute("name")
            if " " in name:
                continue
            idx = "0x" + map_object.getAttribute("id")
            write_if_unique(f, f"MODEL_{name}", idx)

    if is_hit or is_combined:
        if is_combined:
            f.write("\n")

        for collider in xml.getElementsByTagName("Collider"):
            map_object = collider.getElementsByTagName("MapObject")[0]
            name = map_object.getAttribute("name")
            if " " in name:
                continue
            idx = "0x" + map_object.getAttribute("id")
            write_if_unique(f, f"COLLIDER_{name}", idx)

        f.write("\n")

        for zone in xml.getElementsByTagName("Zone"):
            map_object = zone.getElementsByTagName("MapObject")[0]
            name = map_object.getAttribute("name")
            if " " in name:
                continue
            idx = "0x" + map_object.getAttribute("id")
            write_if_unique(f, f"ZONE_{name}", idx)

    f.close()
