import subprocess
import tqdm
from typing import List
import struct
import sys


SYMBOL_TABLE_PTR_ROM_ADDR = 0x18


def get_func_ram_addresses(elf: str) -> List[int]:
    p = subprocess.run(["mips-linux-gnu-readelf", "-s", elf], capture_output=True)
    lines = p.stdout.decode("utf-8").split("\n")
    addrs = set()
    for line in lines:
        if " FUNC " in line:
            parts = line.split()
            addr = int(parts[1], 16)
            addrs.add(addr)
    sorted = list(addrs)
    sorted.sort()
    return sorted


def addr2line(elf: str, addrs: List[int]):
    with subprocess.Popen(["mips-linux-gnu-addr2line", "-e", elf, "-fC"], stdin=subprocess.PIPE, stdout=subprocess.PIPE) as process:
        for addr in addrs:
            process.stdin.write(f"0x{addr:08X}\n".encode())
        process.stdin.flush()

        for addr in tqdm.tqdm(addrs):
            symbol_name = process.stdout.readline().decode("utf-8").strip()
            file_line = process.stdout.readline().decode("utf-8").strip()
            yield addr, symbol_name, file_line


if __name__ == '__main__':
    z64 = sys.argv[1]
    if not z64.endswith(".z64"):
        raise Exception("expected z64 as argument")
    elf = z64.replace(".z64", ".elf")

    addrs = get_func_ram_addresses(elf)
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
        f.write(struct.pack(">I", len(addrs)))

        sizeof_symbol = 4 + 4 + 4 # sizeof(Symbol)
        strings_begin = f.tell() + sizeof_symbol * len(addrs)
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

        for addr, symbol_name, file_line in addr2line(elf, addrs):
            file_line = file_line.replace(root_dir + "/", "")

            f.write(struct.pack(">I", addr))
            f.write(struct.pack(">I", add_string(symbol_name)))
            f.write(struct.pack(">I", add_string(file_line)))

        f.write(strings)

        print("symbol table size: {} kib".format((f.tell() - symbol_table_addr) / 1024))

        print(f"updating SYMBOL_TABLE_PTR_ROM_ADDR")
        f.seek(SYMBOL_TABLE_PTR_ROM_ADDR)
        f.write(struct.pack(">I", symbol_table_addr))
