#!/usr/bin/env python3
"""Writes the header a map's code includes as map.xml.h, or a stage's as stage.xml.h.

It gives the IDs of the geometry's models, colliders, and zones, from the
headers Star Rod writes beside the compiled geometry.

Usage: source_header.py <out> <geometry name, such as w_kmr_02>
"""

from sys import argv

out, name = argv[1:]
with open(out, "w") as f:
    f.write(f'#pragma once\n#include "mapfs/{name}_shape.h"\n#include "mapfs/{name}_hit.h"\n')
