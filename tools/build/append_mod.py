#!/usr/bin/env python3

import struct
import sys
import argparse

# "Unknown 2" in header.s
FIRST_MOD_PTR_ROM_ADDR = 0x1C


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("z64", help="Path to the target z64", type=str)
    parser.add_argument("name", help="Mod short name (lowercase, kebab-case)", type=str)
    parser.add_argument("uuid", help="Mod UUID", type=int)
    parser.add_argument("dfs", help="Path to mod's filesystem image made with mkdfs", type=str)
    args = parser.parse_args()

    name_ascii = args.name.encode("ascii")
    if len(name_ascii) > 31:
        print("Error: name too long (max 31 characters)")
        sys.exit(1)

    with open(args.z64, "r+b") as f:
        # read current mod stack
        mods = []
        f.seek(FIRST_MOD_PTR_ROM_ADDR)
        next_addr, = struct.unpack(">I", f.read(4))
        while next_addr != 0:
            mods.append(next_addr)
            f.seek(next_addr)
            f.read(32)  # name
            f.read(4)   # prev
            next_addr, = struct.unpack(">I", f.read(4))

        prev_addr = mods[-1] if mods else 0

        # seek to end of file and write our mod there
        f.seek(0, 2)
        mod_addr = f.tell()
        if mod_addr % 0x10 != 0:
            f.write(b"\x00" * (0x10 - (mod_addr % 0x10)))
            mod_addr = f.tell()

        print(f"Writing mod '{args.name}' to 0x{mod_addr:08X}")

        # write header (see LoadableMod in mod_loader.hpp)
        f.seek(mod_addr)
        f.write(b"DXv1")
        f.write(struct.pack(">I", args.uuid))
        f.write(name_ascii.ljust(32, b"\0"))
        f.write(struct.pack(">I", prev_addr))
        f.write(struct.pack(">I", 0)) # next
        dfs_addr_addr = f.tell()
        f.write(struct.pack(">I", 0)) # dfsAddress

        # align to 0x10
        dfs_addr = f.tell()
        if dfs_addr % 0x10 != 0:
            f.write(b"\x00" * (0x10 - (dfs_addr % 0x10)))
            dfs_addr = f.tell()

        # write dfs
        with open(args.dfs, "rb") as dfs_file:
            dfs_data = dfs_file.read()
            f.write(dfs_data)

        end_addr = f.tell()
        size_kib = (end_addr - mod_addr) // 1024
        print(f"Size: {size_kib:.1f} KiB")

        # go back and write dfs address
        f.seek(dfs_addr_addr)
        f.write(struct.pack(">I", dfs_addr))

        # go to prev mod and update its "next" pointer
        if prev_addr == 0:
            # this is the first mod
            f.seek(FIRST_MOD_PTR_ROM_ADDR)
        else:
            f.seek(prev_addr + 32 + 4)  # name + prev
        f.write(struct.pack(">I", mod_addr))
