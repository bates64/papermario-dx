#!/usr/bin/env python3

import json
import struct
from pathlib import Path
from sys import argv

HEADER_SIZE = 0x20
TOC_NAME_LEN = 64
TOC_ROW_SIZE = TOC_NAME_LEN + 4 * 4  # name + offset + compressed_size + decompressed_size + hash


def next_multiple(pos, multiple):
    return pos + pos % multiple


def build_mapfs(out_bin, assets, version):
    with open(out_bin, "wb") as f:
        # Write AssetTableHeader
        magic = f"MAPFS {version}"[:8].ljust(8, '\0')
        entry_count = len(assets)
        next_table = 0  # No linked tables for now

        # Calculate hash of entry names for quick change detection
        import hashlib
        entries_hash_str = "".join(sorted(asset["name"] for asset in assets))
        entries_hash = int.from_bytes(hashlib.sha256(entries_hash_str.encode()).digest()[:4], 'big')

        generation = 0  # Base table always starts at generation 0

        f.write(magic.encode("ascii"))
        f.write(struct.pack(">III", entry_count, next_table, entries_hash))
        f.write(struct.pack("B", generation))
        f.write(b'\x00' * 11)  # reserved[11]

        # Calculate where data starts (after header + all entries)
        next_data_pos = HEADER_SIZE + len(assets) * TOC_ROW_SIZE

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

            # Hash is always 0 for vanilla assets
            data_hash = 0

            # write TOC entry.
            f.seek(toc_entry_pos)
            f.write(name.encode("ascii"))
            f.seek(toc_entry_pos + TOC_NAME_LEN)
            f.write(struct.pack(">IIII", offset, size, decompressed_size, data_hash))

            # write data.
            f.seek(next_data_pos)
            f.write(
                compressed.read_bytes()
                if compressed.exists()
                else decompressed.read_bytes()
            )
            next_data_pos += size

            asset_idx += 1


if __name__ == "__main__":
    argv.pop(0)  # python3
    project_name = argv.pop(0)
    out = argv.pop(0)
    input_json = argv.pop(0)

    with open(input_json, "r") as f:
        assets = json.load(f)

    build_mapfs(out, assets, project_name)
