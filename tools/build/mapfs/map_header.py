#!/usr/bin/env python3

from sys import argv, stderr
from os import path
from xml.dom.minidom import parse
from pathlib import Path

def eprint(*args, **kwargs):
    print(*args, file=stderr, **kwargs)


if __name__ == "__main__":
    _, xml_path, out_path = argv

    xml = parse(xml_path)

    out_path = Path(out_path)
    f = out_path.open("w")

    is_shape = out_path.stem.endswith("_shape")
    is_hit = out_path.stem.endswith("_hit")

    map_name = path.basename(xml_path)[:-4]

    if is_shape:
        for model in xml.getElementsByTagName("Model"):
            map_object = model.getElementsByTagName("MapObject")[0]
            name = map_object.getAttribute("name")
            idx = "0x" + map_object.getAttribute("id")
            f.write(f"#define MODEL_{name} {idx}\n")
    elif is_hit:
        for collider in xml.getElementsByTagName("Collider"):
            map_object = collider.getElementsByTagName("MapObject")[0]
            name = map_object.getAttribute("name")
            idx = "0x" + map_object.getAttribute("id")
            f.write(f"#define COLLIDER_{name} {idx}\n")

        f.write("\n")

        for zone in xml.getElementsByTagName("Zone"):
            map_object = zone.getElementsByTagName("MapObject")[0]
            name = map_object.getAttribute("name")
            idx = "0x" + map_object.getAttribute("id")
            f.write(f"#define ZONE_{name} {idx}\n")
    else:
        raise ValueError("Invalid output file name")

    f.close()
