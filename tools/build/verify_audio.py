#!/usr/bin/env python3
"""Checks that a built audio.sbn matches the baserom's, using Star Rod.

Usage: verify_audio.py <star-rod command> <splat.yaml> <baserom> <audio.sbn> <stamp>
"""

import struct
import subprocess
import sys
import tempfile
from pathlib import Path

import yaml


def main() -> int:
    star_rod, splat_yaml, baserom, built, stamp = sys.argv[1:]

    segments = yaml.safe_load(Path(splat_yaml).read_text())["segments"]
    start = next(
        s[0] if isinstance(s, list) else s["start"]
        for s in segments
        if (s[1] if isinstance(s, list) else s.get("type")) == "pm_sbn"
    )
    rom = Path(baserom).read_bytes()
    (size,) = struct.unpack_from(">i", rom, start + 4)

    with tempfile.TemporaryDirectory() as tmp:
        vanilla = Path(tmp) / "vanilla.sbn"
        vanilla.write_bytes(rom[start : start + size])
        result = subprocess.run([star_rod, "-VerifyAudio", built, str(vanilla)])
    if result.returncode == 0:
        Path(stamp).write_text("")
    return result.returncode


if __name__ == "__main__":
    sys.exit(main())
