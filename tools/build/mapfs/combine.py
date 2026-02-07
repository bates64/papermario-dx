#!/usr/bin/env python3

import struct
import subprocess
from pathlib import Path
from sys import argv

HEADER_SIZE = 0x20
TOC_ROW_SIZE = 0x1C
TOC_NAME_LEN = 16


def next_multiple(pos, multiple):
    return pos + pos % multiple


def get_version_date(version):
    return f"MAPFS {version}"


def build_mapfs(out_bin, assets, version, pre_write_assets):
    with open(out_bin, "wb") as f:
        f.write(get_version_date(version).encode("ascii"))

        next_data_pos = (len(assets) + 1) * TOC_ROW_SIZE

        asset_idx = 0
        for decompressed, compressed in assets:
            toc_entry_pos = HEADER_SIZE + asset_idx * TOC_ROW_SIZE

            # data for TOC entry
            name = decompressed.stem + "\0"
            offset = next_data_pos
            decompressed_size = decompressed.stat().st_size
            size = (
                next_multiple(compressed.stat().st_size, 2)
                if compressed.exists()
                else decompressed_size
            )

            if version == "ique" and decompressed.stem == "title_data":
                size = compressed.stat().st_size

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
    version = argv.pop(0)
    out = argv.pop(0)

    assets = []
    pre_write_assets = {}

    for path in argv:
        path = Path(path)
        if path.suffixes[-2:] == [".raw", ".dat"]:
            pre_write_assets[path.with_suffix("").stem] = path
        else:
            assets.append(path)

    # turn them into pairs
    assets = list(zip(assets[::2], assets[1::2]))

    build_mapfs(out, assets, version, pre_write_assets)
