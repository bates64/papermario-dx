#!/usr/bin/env python3
"""Converts a PNG to N64 texture data in the format its pixels need.

Inferring the format as the texture builds, rather than when configure runs,
keeps the data in step with the image as it's edited.

Usage: pigment.py <in.png> <out.bin> [pigment64 flags...]
"""

import subprocess
from pathlib import Path
from sys import argv, path

path.append(str(Path(__file__).parent.parent))

from raster import Png

if __name__ == "__main__":
    infile, outfile, *flags = argv[1:]
    fmt = Png(Path(infile)).format()
    subprocess.run(["pigment64", "to-bin", *flags, "-f", fmt, "-o", outfile, infile], check=True)
