#!/usr/bin/env python3
"""
Writes the JSON Mamar's website reads to play songs in this build, patched onto
a vanilla ROM with papermario.bps: the addresses of the Mamar globals (see
src/dx/mamar.h), and the patch's SHA-256, so the website can tell whether the
patch it downloaded matches.

Usage: mamar_symbols.py <papermario.elf> <papermario.bps> <symbols.json>
"""

import hashlib
import json
import subprocess
import sys


def main():
    elf, bps, out = sys.argv[1:4]

    nm = subprocess.run(["mips-linux-gnu-nm", elf], capture_output=True, text=True, check=True)
    symbols = {}
    for line in nm.stdout.splitlines():
        parts = line.split()
        if len(parts) == 3 and parts[2].startswith("Mamar"):
            # nm sign-extends the 32-bit addresses to 64 bits.
            symbols[parts[2]] = int(parts[0], 16) & 0xFFFFFFFF

    with open(bps, "rb") as f:
        patch_sha256 = hashlib.sha256(f.read()).hexdigest()

    with open(out, "w") as f:
        json.dump({"patchSha256": patch_sha256, "symbols": symbols}, f, indent=2, sort_keys=True)
        f.write("\n")


if __name__ == "__main__":
    main()
