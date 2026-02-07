#!/usr/bin/env python3
"""Convert a MIPS ELF .so into a .module file."""

import struct
import sys
from pathlib import Path

MOD_MAGIC = b"MOD\x00"
MOD_VERSION = 1

R_MIPS_NONE = 0
R_MIPS_32 = 2
R_MIPS_26 = 4
R_MIPS_HI16 = 5
R_MIPS_LO16 = 6

SUPPORTED_RELOCS = {R_MIPS_32, R_MIPS_26, R_MIPS_HI16, R_MIPS_LO16}

# ELF constants
SHT_NULL = 0
SHT_PROGBITS = 1
SHT_SYMTAB = 2
SHT_STRTAB = 3
SHT_RELA = 4
SHT_NOBITS = 8
SHT_REL = 9

STB_LOCAL = 0
STB_GLOBAL = 1

SHN_UNDEF = 0
SHN_ABS = 0xFFF1
SHN_COMMON = 0xFFF2
IGNORED_SHNDX = {SHN_UNDEF, SHN_ABS, SHN_COMMON}


class ElfSection:
    def __init__(self, name, sh_type, sh_offset, sh_size, sh_link, data):
        self.name = name
        self.type = sh_type
        self.offset = sh_offset
        self.size = sh_size
        self.link = sh_link
        self.content = data


class ElfSymbol:
    def __init__(self, name, st_value, st_size, st_info, st_shndx):
        self.name = name
        self.value = st_value
        self.size = st_size
        self.binding = st_info >> 4
        self.type = st_info & 0xF
        self.shndx = st_shndx


class Elf32:
    def __init__(self, data):
        self.data = data
        self.sections = []
        self.symbols = []
        self._parse()

    def _parse(self):
        # Parse ELF header (52 bytes for ELF32)
        if len(self.data) < 52:
            raise ValueError("File too small to be a valid ELF")

        # Check magic
        if self.data[:4] != b"\x7fELF":
            raise ValueError("Not a valid ELF file")

        # Get section header info from ELF header
        # Offsets 32, 46, 48, 50 for e_shoff, e_shentsize, e_shnum, e_shstrndx
        e_shoff = struct.unpack(">I", self.data[32:36])[0]
        e_shentsize = struct.unpack(">H", self.data[46:48])[0]
        e_shnum = struct.unpack(">H", self.data[48:50])[0]
        e_shstrndx = struct.unpack(">H", self.data[50:52])[0]

        # Parse section headers (40 bytes each for ELF32)
        section_headers = []
        for i in range(e_shnum):
            off = e_shoff + i * e_shentsize
            sh_data = self.data[off : off + 40]
            (
                sh_name,
                sh_type,
                sh_flags,
                sh_addr,
                sh_offset,
                sh_size,
                sh_link,
                sh_info,
                sh_addralign,
                sh_entsize,
            ) = struct.unpack(">10I", sh_data)
            section_headers.append(
                (
                    sh_name,
                    sh_type,
                    sh_flags,
                    sh_addr,
                    sh_offset,
                    sh_size,
                    sh_link,
                    sh_info,
                    sh_addralign,
                    sh_entsize,
                )
            )

        # Read section string table
        if e_shstrndx < len(section_headers):
            shstrtab_offset = section_headers[e_shstrndx][4]
            shstrtab_size = section_headers[e_shstrndx][5]
            shstrtab = self.data[shstrtab_offset : shstrtab_offset + shstrtab_size]
        else:
            shstrtab = b""

        # Build sections
        for (
            sh_name,
            sh_type,
            sh_flags,
            sh_addr,
            sh_offset,
            sh_size,
            sh_link,
            sh_info,
            sh_addralign,
            sh_entsize,
        ) in section_headers:
            # Read section name from string table
            name_end = shstrtab.find(b"\x00", sh_name)
            if name_end == -1:
                name = ""
            else:
                name = shstrtab[sh_name:name_end].decode("ascii", errors="ignore")

            # Read section data
            sec_data = (
                self.data[sh_offset : sh_offset + sh_size]
                if sh_type != SHT_NOBITS
                else b""
            )

            self.sections.append(
                ElfSection(name, sh_type, sh_offset, sh_size, sh_link, sec_data)
            )

        # Parse symbol table
        symtab_sec = None
        strtab_sec = None
        for sec in self.sections:
            if sec.type == SHT_SYMTAB:
                symtab_sec = sec
                # The sh_link field points to the string table
                if sec.link < len(self.sections):
                    strtab_sec = self.sections[sec.link]
                break

        if symtab_sec and strtab_sec:
            # Parse symbols (16 bytes each for ELF32)
            for i in range(0, len(symtab_sec.content), 16):
                st_name, st_value, st_size, st_info, st_other, st_shndx = struct.unpack(
                    ">3I2BH", symtab_sec.content[i : i + 16]
                )

                # Read symbol name from string table
                name_end = strtab_sec.content.find(b"\x00", st_name)
                if name_end == -1:
                    name = ""
                else:
                    name = strtab_sec.content[st_name:name_end].decode(
                        "ascii", errors="ignore"
                    )

                self.symbols.append(
                    ElfSymbol(name, st_value, st_size, st_info, st_shndx)
                )

    def get_section(self, name):
        for sec in self.sections:
            if sec.name == name:
                return sec
        return None


def get_section(elf, name):
    sec = elf.get_section(name)
    if sec is None or sec.size == 0:
        return None, b"", 0
    return sec, sec.content, sec.size


def collect_relocs(elf):
    relocs = []
    syms = elf.symbols

    for sec in elf.sections:
        if not sec.name.startswith(".rel."):
            continue
        target_name = sec.name[4:]  # ".rel.text" -> ".text"
        if target_name not in (
            ".text",
            ".data",
            ".ctors",
            ".dtors",
            ".init_array",
            ".fini_array",
        ):
            continue

        data = sec.content
        # MIPS32 REL entries: 8 bytes each (u32 offset, u32 info)
        for i in range(0, len(data), 8):
            r_offset, r_info = struct.unpack(">II", data[i : i + 8])
            r_type = r_info & 0xFF
            r_sym = r_info >> 8

            if r_type == R_MIPS_NONE:
                continue

            # Skip linked symbols
            sym = syms[r_sym] if r_sym < len(syms) else None
            if sym and sym.shndx in IGNORED_SHNDX:
                continue

            if r_type in SUPPORTED_RELOCS:
                relocs.append((r_type, r_offset))
            else:
                print(
                    f"warning: unsupported reloc type {r_type} at {r_offset:#x}",
                    file=sys.stderr,
                )

    return relocs


def collect_exports(elf):
    """Collect all global symbols as (offset, name) sorted by offset."""
    exports = []
    for sym in elf.symbols:
        # Skip local, undefined, and section symbols
        if sym.binding != STB_GLOBAL:
            continue
        if sym.shndx == 0:  # SHN_UNDEF
            continue
        if sym.shndx == 0xFFF1:  # SHN_ABS
            continue
        # Skip linker-generated symbols
        if sym.name.startswith("__"):
            continue
        if not sym.name:
            continue

        exports.append((sym.value, sym.name))

    exports.sort(key=lambda e: e[0])
    return exports


def read_section_data(elf, names):
    """Read concatenated data from a list of section names."""
    for name in names:
        sec, data, size = get_section(elf, name)
        if sec is not None:
            return data, size
    return b"", 0


def build_module(input_path, output_path):
    with open(input_path, "rb") as f:
        elf_data = f.read()

    elf = Elf32(elf_data)
    LINK_ADDR = 0x80000000

    # Collect section data
    _, text_data, text_size = get_section(elf, ".text")

    # .rodata is part of .text in our linker script, but check anyway
    rodata_sec = elf.get_section(".rodata")
    if rodata_sec and rodata_sec.size > 0:
        print(
            "warning: .rodata not merged into .text, check linker script",
            file=sys.stderr,
        )

    _, data_data, data_size = get_section(elf, ".data")
    bss_sec = elf.get_section(".bss")
    bss_size = bss_sec.size if bss_sec else 0

    ctors_data, ctors_size = read_section_data(elf, [".ctors", ".init_array"])
    dtors_data, dtors_size = read_section_data(elf, [".dtors", ".fini_array"])

    relocs = collect_relocs(elf)
    exports = collect_exports(elf)

    # Build reloc table: packed (u8 type, u8 pad, u16 pad, u32 offset)
    reloc_blob = b""
    for r_type, r_offset in relocs:
        reloc_blob += struct.pack(">BxxxI", r_type, r_offset - LINK_ADDR)

    # Build export table and string table
    export_entries = b""
    strtab = b""
    str_offsets = {}
    for offset, name in exports:
        # Deduplicate strings
        if name not in str_offsets:
            str_offsets[name] = len(strtab)
            strtab += name.encode("ascii") + b"\x00"
        export_entries += struct.pack(">II", offset - LINK_ADDR, str_offsets[name])

    # Build header
    HEADER_SIZE = 68

    off = HEADER_SIZE
    text_off = off
    off += len(text_data)
    data_off = off
    off += len(data_data)
    reloc_off = off
    off += len(reloc_blob)
    ctor_off = off
    off += len(ctors_data)
    dtor_off = off
    off += len(dtors_data)
    export_off = off
    off += len(export_entries)
    strtab_off = off
    off += len(strtab)

    header = struct.pack(">4sI", MOD_MAGIC, MOD_VERSION)
    header += struct.pack(">II", text_off, text_size)
    header += struct.pack(">II", data_off, data_size)
    header += struct.pack(">I", bss_size)
    header += struct.pack(">II", reloc_off, len(relocs))
    header += struct.pack(">II", ctor_off, ctors_size // 4)
    header += struct.pack(">II", dtor_off, dtors_size // 4)
    header += struct.pack(">II", export_off, len(exports))
    header += struct.pack(">II", strtab_off, len(strtab))

    assert len(header) == HEADER_SIZE, (
        f"Header size mismatch: {len(header)} != {HEADER_SIZE}"
    )

    with open(output_path, "wb") as f:
        f.write(header)
        f.write(text_data)
        f.write(data_data)
        f.write(reloc_blob)
        f.write(ctors_data)
        f.write(dtors_data)
        f.write(export_entries)
        f.write(strtab)

    total_size = off
    print(
        f"{Path(output_path).name}: {total_size} bytes "
        f"(text={text_size} data={data_size} bss={bss_size} "
        f"relocs={len(relocs)} exports={len(exports)})"
    )


def main():
    if len(sys.argv) != 3:
        print(f"usage: {sys.argv[0]} <input.so> <output.module>", file=sys.stderr)
        sys.exit(1)
    build_module(sys.argv[1], sys.argv[2])


if __name__ == "__main__":
    main()
