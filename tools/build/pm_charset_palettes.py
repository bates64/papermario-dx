#!/usr/bin/env python3

from sys import argv
from pathlib import Path

if __name__ == "__main__":
    argv.pop(0)  # python3
    out = argv.pop(0)

    paths = []
    for arg in argv:
        if arg.endswith(".rsp"):
            paths.extend(Path(arg).read_text().split())
        else:
            paths.append(arg)

    with open(out, "wb") as f:
        for path in paths:
            with open(path, "rb") as j:
                f.write(j.read())
