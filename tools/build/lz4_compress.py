#!/usr/bin/env python3
"""Compress a file with LZ4 raw block format for N64 decompressor."""

import sys
from pathlib import Path
import lz4.block

def main():
    if len(sys.argv) != 3:
        print(f"usage: {sys.argv[0]} <input> <output>", file=sys.stderr)
        sys.exit(1)

    input_path = Path(sys.argv[1])
    output_path = Path(sys.argv[2])

    data = input_path.read_bytes()

    # Compress with LZ4 block format (no framing, raw blocks)
    # store_size=False means no size prefix - decompressor gets size from asset table
    compressed = lz4.block.compress(data, mode="high_compression", store_size=False)

    output_path.write_bytes(compressed)

    ratio = len(compressed) / len(data) * 100 if data else 0
    print(f"{output_path.name}: {len(data)} -> {len(compressed)} bytes ({ratio:.1f}%)")


if __name__ == "__main__":
    main()
