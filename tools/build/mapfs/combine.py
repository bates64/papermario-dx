#!/usr/bin/env python3

import json
import struct
from pathlib import Path
from sys import argv

HEADER_SIZE = 0x20
TOC_NAME_LEN = 64
TOC_ROW_SIZE = TOC_NAME_LEN + 4 * 3


def next_multiple(pos, multiple):
    return pos + pos % multiple


def get_version_date(version):
    return f"MAPFS {version}"


def build_mapfs(out_bin, assets, version):
    with open(out_bin, "wb") as f:
        f.write(get_version_date(version).encode("ascii"))

        next_data_pos = (len(assets) + 1) * TOC_ROW_SIZE

        asset_idx = 0
        for asset in assets:
            name = asset["name"] + "\0"
            if len(name) > TOC_NAME_LEN:
                print("error: filename too long:", name)
                exit(1)
            decompressed = Path(asset["decompressed"])
            compressed = Path(asset["compressed"] or asset["decompressed"])

            toc_entry_pos = HEADER_SIZE + asset_idx * TOC_ROW_SIZE

            # data for TOC entry
            offset = next_data_pos
            decompressed_size = decompressed.stat().st_size
            size = (
                next_multiple(compressed.stat().st_size, 2)
                if compressed.exists()
                else decompressed_size
            )

            # print(f"{name} {offset:08X} {size:08X} {decompressed_size:08X}")

            # write TOC entry.
            f.seek(toc_entry_pos)
            f.write(name.encode("ascii"))
            f.seek(toc_entry_pos + TOC_NAME_LEN)
            f.write(struct.pack(">III", offset, size, decompressed_size))

            # write data.
            f.seek(HEADER_SIZE + next_data_pos)
            f.write(
                compressed.read_bytes()
                if compressed.exists()
                else decompressed.read_bytes()
            )
            next_data_pos += size

            asset_idx += 1

        # sentinel
        toc_entry_pos = HEADER_SIZE + asset_idx * TOC_ROW_SIZE
        f.seek(toc_entry_pos)
        f.write("END DATA\0".encode("ascii"))
        f.write(struct.pack(">III", 0, 0, 0))


if __name__ == "__main__":
    argv.pop(0)  # python3
    project_name = argv.pop(0)
    out = argv.pop(0)
    input_json = argv.pop(0)

    with open(input_json, "r") as f:
        assets = json.load(f)

    build_mapfs(out, assets, project_name)
