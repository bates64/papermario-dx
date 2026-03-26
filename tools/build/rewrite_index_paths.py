"""Rewrite file paths in a clangd RIFF index file.

The RIFF index stores all strings (including file URIs) in a zlib-compressed
string table. This script decompresses it, performs a find-and-replace on
the raw strings, then recompresses and patches the RIFF chunk in-place.
"""

import struct
import sys
import zlib


def rewrite_paths(data: bytes, old_prefix: bytes, new_prefix: bytes) -> bytes:
    """Rewrite paths in a clangd RIFF (.idx) index."""
    # RIFF header: "RIFF" <size:u32-le> <type:4bytes>
    assert data[:4] == b"RIFF", "not a RIFF file"
    riff_type = data[8:12]
    assert riff_type == b"CdIx", f"unexpected RIFF type: {riff_type}"

    pos = 12
    chunks = []

    while pos < len(data):
        chunk_id = data[pos : pos + 4]
        chunk_size = struct.unpack_from("<I", data, pos + 4)[0]
        chunk_data = data[pos + 8 : pos + 8 + chunk_size]
        chunks.append((chunk_id, chunk_data))
        # Chunks are 2-byte aligned
        pos += 8 + chunk_size
        if pos % 2 == 1:
            pos += 1

    # Rebuild, patching the "stri" (string table) chunk
    out_chunks = []
    for chunk_id, chunk_data in chunks:
        if chunk_id == b"stri":
            chunk_data = _rewrite_string_table(chunk_data, old_prefix, new_prefix)
        out_chunks.append((chunk_id, chunk_data))

    # Reassemble RIFF
    body = b""
    for chunk_id, chunk_data in out_chunks:
        body += chunk_id
        body += struct.pack("<I", len(chunk_data))
        body += chunk_data
        if len(chunk_data) % 2 == 1:
            body += b"\x00"  # padding

    return b"RIFF" + struct.pack("<I", 4 + len(body)) + riff_type + body


def _rewrite_string_table(
    chunk_data: bytes, old_prefix: bytes, new_prefix: bytes
) -> bytes:
    # First 4 bytes: uncompressed size (0 = no compression)
    uncompressed_size = struct.unpack_from("<I", chunk_data, 0)[0]

    if uncompressed_size == 0:
        # Not compressed — raw null-terminated strings after the size field
        raw = chunk_data[4:]
        raw = raw.replace(old_prefix, new_prefix)
        return struct.pack("<I", 0) + raw
    else:
        # zlib compressed
        compressed = chunk_data[4:]
        raw = zlib.decompress(compressed)
        assert len(raw) == uncompressed_size, (
            f"size mismatch: expected {uncompressed_size}, got {len(raw)}"
        )
        raw = raw.replace(old_prefix, new_prefix)
        recompressed = zlib.compress(raw)
        return struct.pack("<I", len(raw)) + recompressed


def main():
    if len(sys.argv) != 4:
        print(f"Usage: {sys.argv[0]} <index.idx> <old-prefix> <new-prefix>", file=sys.stderr)
        sys.exit(1)

    idx_path = sys.argv[1]
    old_prefix = sys.argv[2].encode()
    new_prefix = sys.argv[3].encode()

    with open(idx_path, "rb") as f:
        data = f.read()

    data = rewrite_paths(data, old_prefix, new_prefix)

    with open(idx_path, "wb") as f:
        f.write(data)


if __name__ == "__main__":
    main()
