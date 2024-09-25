import subprocess
from typing import List, Tuple
import struct
import sys
import io


SYMBOL_TABLE_PTR_ROM_ADDR = 0x18


def readelf(elf: str) -> List[Tuple[int, str, str, int]]:
    addr2name = {}  # funcs
    addr2line = {}  # debug info

    process = subprocess.Popen(["mips-linux-gnu-readelf", "-s", elf, "--wide", "-wL"], stdout=subprocess.PIPE)
    for line in io.TextIOWrapper(process.stdout, encoding="utf-8"):
        parts = line.split()

        #  75082: 8048d5bc    44 FUNC    GLOBAL DEFAULT 1845 func_802BC0B8_E2E9E8
        if len(parts) == 8 and parts[3] == "FUNC":
            addr = int(parts[1], 16)
            name = parts[-1]
            if name.startswith("dead_"):
                continue
            addr2name[addr] = name

        # npc.c                                    120          0x8003910c               x
        elif len(parts) >= 4 and parts[2].startswith("0x"):
            file_basename = parts[0]
            if not file_basename.endswith(".c"):
                continue
            line_number = int(parts[1])
            addr = int(parts[2], 0)
            addr2line[addr] = (file_basename, line_number)

    sorted_addr2name_addrs = sorted(addr2name.keys())

    symbols = []
    for addr, (file_basename, line_number) in addr2line.items():
        if addr in addr2name:
            symbols.append((addr, addr2name[addr], file_basename, line_number))
        else:
            # find closest addr2name < addr
            closest_addr = None
            for a in sorted_addr2name_addrs:
                if a < addr:
                    closest_addr = a
                else:
                    break
            if closest_addr is not None:
                symbols.append((addr, addr2name[closest_addr], file_basename, line_number))

    # non-debug builds
    if len(symbols) == 0:
        print("no debug symbols found, using func names only")
        for addr, name in addr2name.items():
            symbols.append((addr, name, "", -1))

    # sort by address
    symbols.sort(key=lambda x: x[0])

    return symbols


if __name__ == "__main__":
    z64 = sys.argv[1]
    if not z64.endswith(".z64"):
        raise Exception("expected z64 as argument")
    elf = z64.replace(".z64", ".elf")

    symbols = readelf(elf)
    root_dir = subprocess.check_output(["git", "rev-parse", "--show-toplevel"]).decode("utf-8").strip()

    with open(z64, "r+b") as f:
        # seek to end
        f.seek(0, 2)
        symbol_table_addr = f.tell()
        print(f"ROM is 0x{symbol_table_addr:08X} bytes")

        # align
        if symbol_table_addr % 0x10 != 0:
            f.write(b"\x00" * (0x10 - (symbol_table_addr % 0x10)))
            symbol_table_addr = f.tell()

        print(f"placing symbol table at ROM 0x{symbol_table_addr:08X}")

        # write header (see backtrace.h)
        f.seek(symbol_table_addr)
        f.write(b"SYMS")
        f.write(struct.pack(">I", len(symbols)))

        sizeof_symbol = 4 + 4 + 4  # sizeof(Symbol)
        strings_begin = f.tell() + sizeof_symbol * len(symbols)
        strings = bytearray()
        string_map = {}

        # for deduplication
        def add_string(s: str):
            global strings
            if s not in string_map:
                string_map[s] = strings_begin + len(strings)
                strings += s.encode("utf-8")
                strings += b"\0"
            return string_map[s]

        for addr, name, file_basename, line_number in symbols:
            # file_line = file_line.replace(root_dir + "/", "")

            f.write(struct.pack(">I", addr))
            f.write(struct.pack(">I", add_string(name)))

            if file_basename == "":
                f.write(struct.pack(">I", 0))
            else:
                f.write(struct.pack(">I", add_string(f"{file_basename}:{line_number}")))  # can make more efficient

        f.write(strings)

        # Pad to the nearest 16-byte alignment
        padding_size = (f.tell() + 15) & ~15
        padding_bytes = b"\x00" * (padding_size - f.tell())
        f.write(padding_bytes)

        print("symbol table size: {} kib".format((f.tell() - symbol_table_addr) / 1024))

        print(f"updating SYMBOL_TABLE_PTR_ROM_ADDR")
        f.seek(SYMBOL_TABLE_PTR_ROM_ADDR)
        f.write(struct.pack(">I", symbol_table_addr))
