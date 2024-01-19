#!/usr/bin/env python3
"""Convert hit.bin to C code with pointer-based structs."""

import argparse
import struct
from pathlib import Path
from typing import List, Optional, TextIO


def read_section(data: bytes, offset: int, prefix: str):
    """Parse a HitFileHeader and all its sub-data from the blob."""
    if offset == 0:
        return None

    # HitFileHeader: s16 numColliders, s16 pad, s32 collidersOffset,
    #                s16 numVertices, s16 pad, s32 verticesOffset,
    #                s16 boundingBoxesDataSize, s16 pad, s32 boundingBoxesOffset
    (
        num_colliders, _, colliders_offset,
        num_vertices, _, vertices_offset,
        bbox_data_size, _, bbox_offset,
    ) = struct.unpack_from(">hhi hhi hhi", data, offset)

    # Parse vertices (Vec3s: 3 * s16 = 6 bytes each)
    vertices = []
    for i in range(num_vertices):
        x, y, z = struct.unpack_from(">hhh", data, vertices_offset + i * 6)
        vertices.append((x, y, z))

    # Parse bounding boxes (raw u32 array)
    bboxes = []
    for i in range(bbox_data_size):
        (val,) = struct.unpack_from(">I", data, bbox_offset + i * 4)
        bboxes.append(val)

    # Parse colliders (HitAssetCollider: s16 boundingBoxOffset, s16 nextSibling,
    #                   s16 firstChild, s16 numTriangles, s32 trianglesOffset)
    colliders = []
    for i in range(num_colliders):
        co = colliders_offset + i * 0x0C
        bbox_off, next_sib, first_child, num_tris, tris_offset = struct.unpack_from(
            ">hhhhi", data, co
        )

        # Parse packed triangles for this collider
        triangles = []
        for j in range(num_tris):
            (packed,) = struct.unpack_from(">i", data, tris_offset + j * 4)
            triangles.append(packed)

        colliders.append({
            "bbox_offset": bbox_off,
            "next_sibling": next_sib,
            "first_child": first_child,
            "num_triangles": num_tris,
            "triangles": triangles,
        })

    return {
        "prefix": prefix,
        "num_colliders": num_colliders,
        "num_vertices": num_vertices,
        "bbox_data_size": bbox_data_size,
        "vertices": vertices,
        "bboxes": bboxes,
        "colliders": colliders,
    }


def write_section(f: TextIO, section: dict):
    """Write C code for one section (collision or zone)."""
    prefix = section["prefix"]

    # Vertices
    f.write(f"static Vec3s {prefix}_vertices[] = {{\n")
    for x, y, z in section["vertices"]:
        f.write(f"    {{ {x}, {y}, {z} }},\n")
    f.write("};\n\n")

    # Bounding boxes (raw u32 array)
    if section["bboxes"]:
        f.write(f"static u32 {prefix}_bboxes[] = {{\n")
        for val in section["bboxes"]:
            f.write(f"    0x{val:08X},\n")
        f.write("};\n\n")

    # Triangles per collider
    for i, col in enumerate(section["colliders"]):
        if col["triangles"]:
            f.write(f"static s32 {prefix}_triangles_{i}[] = {{\n")
            for packed in col["triangles"]:
                f.write(f"    0x{packed & 0xFFFFFFFF:08X},\n")
            f.write("};\n\n")

    # Collider structs
    f.write(f"static HitAssetCollider {prefix}_colliders[] = {{\n")
    for i, col in enumerate(section["colliders"]):
        bbox_off = col["bbox_offset"]
        if col["triangles"]:
            tris_ptr = f"{prefix}_triangles_{i}"
        else:
            tris_ptr = "NULL"
        f.write(
            f"    {{ .boundingBoxOffset = {bbox_off}, "
            f".nextSibling = {col['next_sibling']}, "
            f".firstChild = {col['first_child']}, "
            f".numTriangles = {col['num_triangles']}, "
            f".triangles = {tris_ptr} }},\n"
        )
    f.write("};\n\n")

    # Header struct
    bbox_ptr = f"{prefix}_bboxes" if section["bboxes"] else "NULL"
    f.write(f"static HitFileHeader {prefix}_header = {{\n")
    f.write(f"    .numColliders = {section['num_colliders']},\n")
    f.write(f"    .colliders = {prefix}_colliders,\n")
    f.write(f"    .numVertices = {section['num_vertices']},\n")
    f.write(f"    .vertices = {prefix}_vertices,\n")
    f.write(f"    .boundingBoxesDataSize = {section['bbox_data_size']},\n")
    f.write(f"    .boundingBoxes = {bbox_ptr},\n")
    f.write("};\n\n")


def convert(in_bin: Path, out_c: Path):
    data = in_bin.read_bytes()
    convert_bytes(data, out_c)

def convert_bytes(data: bytes, out_c: Path):

    # HitFile: u32 collisionOffset, u32 zoneOffset
    collision_offset, zone_offset = struct.unpack_from(">II", data, 0)

    collision = read_section(data, collision_offset, "collision")
    zone = read_section(data, zone_offset, "zone")

    with open(out_c, "w") as f:
        f.write('#include "common.h"\n')
        f.write('#include "hit_asset.h"\n\n')

        if collision:
            write_section(f, collision)
        if zone:
            write_section(f, zone)

        # Exported symbol
        collision_ptr = "&collision_header" if collision else "NULL"
        zone_ptr = "&zone_header" if zone else "NULL"
        f.write(f"HitFile hit = {{\n")
        f.write(f"    .collision = {collision_ptr},\n")
        f.write(f"    .zone = {zone_ptr},\n")
        f.write("};\n")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("in_bin", type=Path, help="input hit binary file")
    parser.add_argument("out_c", type=Path, help="output C file")
    args = parser.parse_args()

    convert(args.in_bin, args.out_c)
