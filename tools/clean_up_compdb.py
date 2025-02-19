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
        .replace("-mfp32", "")
        .replace("-mabi=32", "")
        .replace("-fno-toplevel-reorder", "")
        .replace("-fcall-used-gp", "")
        .replace("-freg-struct-return", "")
        .replace("-march=vr4300", "-D__mips__")
        .replace("-Wno-builtin-declaration-mismatch", "")
        .replace("-Wmissing-parameter-type", "")
        .replace("-Werror=old-style-declaration", "")
        .replace("-Werror=missing-parameter-type", "")
    )

with open(fname, "w") as f:
    json.dump(compdb, f, indent=2)
