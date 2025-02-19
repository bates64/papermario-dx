#!/usr/bin/env python3

"""
clang tools don't like certain flags that we pass to gcc, so this script strips them.
"""

import os
import json
from sys import argv

fname = argv[1]

with open(fname, "r") as f:
    compdb = json.load(f)

for entry in compdb:
    entry["directory"] = os.path.abspath(".")
    entry["command"] = (
        entry["command"]
        .replace("-gas-loc-support", "")
        .replace("-mgp32", "")
        .replace("-fno-toplevel-reorder", "")
        .replace("-march=vr4300", "-mcpu=mips3")
    )

with open(fname, "w") as f:
    json.dump(compdb, f, indent=2)
