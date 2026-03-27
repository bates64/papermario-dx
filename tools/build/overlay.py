#!/usr/bin/env python3

import argparse
import os
import pickle
import struct
import subprocess
import sys
import zlib
from pathlib import Path

SCRIPT_DIR = Path(__file__).resolve().parent

OVL_MAGIC = b"MOD\x00"
CROSS = "mips-linux-gnu-"

R_MIPS_NONE = 0
R_MIPS_32 = 2
R_MIPS_26 = 4
R_MIPS_HI16 = 5
R_MIPS_LO16 = 6

SUPPORTED_RELOCS = {R_MIPS_32, R_MIPS_26, R_MIPS_HI16, R_MIPS_LO16}

SHT_NULL = 0
SHT_PROGBITS = 1
SHT_SYMTAB = 2
SHT_STRTAB = 3
SHT_RELA = 4
SHT_NOBITS = 8
SHT_REL = 9
SHT_INIT_ARRAY = 14
SHT_FINI_ARRAY = 15

SHF_COMPRESSED = 0x800

STB_LOCAL = 0
STB_GLOBAL = 1

SHN_UNDEF = 0
SHN_ABS = 0xFFF1
SHN_COMMON = 0xFFF2
IGNORED_SHNDX = {SHN_UNDEF, SHN_ABS, SHN_COMMON}


class ElfSection:
    def __init__(self, name, sh_type, sh_flags, sh_addr, sh_offset, sh_size, sh_link, sh_info, sh_addralign, sh_entsize, data):
        self.name = name
        self.type = sh_type
        self.flags = sh_flags
        self.addr = sh_addr
        self.offset = sh_offset
        self.size = sh_size
        self.link = sh_link
        self.info = sh_info
        self.addralign = sh_addralign
        self.entsize = sh_entsize
        self.content = data


STV_DEFAULT = 0
STV_HIDDEN = 2

class ElfSymbol:
    def __init__(self, name, st_value, st_size, st_info, st_other, st_shndx):
        self.name = name
        self.value = st_value
        self.size = st_size
        self.binding = st_info >> 4
        self.type = st_info & 0xF
        self.visibility = st_other & 0x3
        self.shndx = st_shndx


class Elf32:
    def __init__(self, data):
        self.data = data
        self.sections = []
        self.symbols = []
        self._parse()

    def _parse(self):
        if len(self.data) < 52:
            raise ValueError("File too small to be a valid ELF")
        if self.data[:4] != b"\x7fELF":
            raise ValueError("Not a valid ELF file")

        e_shoff = struct.unpack(">I", self.data[32:36])[0]
        e_shentsize = struct.unpack(">H", self.data[46:48])[0]
        e_shnum = struct.unpack(">H", self.data[48:50])[0]
        e_shstrndx = struct.unpack(">H", self.data[50:52])[0]

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

        if e_shstrndx < len(section_headers):
            shstrtab_offset = section_headers[e_shstrndx][4]
            shstrtab_size = section_headers[e_shstrndx][5]
            shstrtab = self.data[shstrtab_offset : shstrtab_offset + shstrtab_size]
        else:
            shstrtab = b""

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
            name_end = shstrtab.find(b"\x00", sh_name)
            if name_end == -1:
                name = ""
            else:
                name = shstrtab[sh_name:name_end].decode("ascii", errors="ignore")

            sec_data = (
                self.data[sh_offset : sh_offset + sh_size]
                if sh_type != SHT_NOBITS
                else b""
            )

            # Decompress SHF_COMPRESSED sections (gcc -gz)
            if (sh_flags & SHF_COMPRESSED) and len(sec_data) >= 12:
                ch_type, ch_size, ch_addralign = struct.unpack(">III", sec_data[:12])
                if ch_type == 1:  # ELFCOMPRESS_ZLIB
                    sec_data = zlib.decompress(sec_data[12:], bufsize=ch_size)
                    sh_size = len(sec_data)

            self.sections.append(
                ElfSection(name, sh_type, sh_flags, sh_addr, sh_offset, sh_size, sh_link, sh_info, sh_addralign, sh_entsize, sec_data)
            )

        symtab_sec = None
        strtab_sec = None
        for sec in self.sections:
            if sec.type == SHT_SYMTAB:
                symtab_sec = sec
                if sec.link < len(self.sections):
                    strtab_sec = self.sections[sec.link]
                break

        if symtab_sec and strtab_sec:
            for i in range(0, len(symtab_sec.content), 16):
                st_name, st_value, st_size, st_info, st_other, st_shndx = struct.unpack(
                    ">3I2BH", symtab_sec.content[i : i + 16]
                )

                name_end = strtab_sec.content.find(b"\x00", st_name)
                if name_end == -1:
                    name = ""
                else:
                    name = strtab_sec.content[st_name:name_end].decode(
                        "ascii", errors="ignore"
                    )

                self.symbols.append(
                    ElfSymbol(name, st_value, st_size, st_info, st_other, st_shndx)
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
        target_name = sec.name[4:]
        if target_name not in (".text", ".data"):
            continue

        data = sec.content
        for i in range(0, len(data), 8):
            r_offset, r_info = struct.unpack(">II", data[i : i + 8])
            r_type = r_info & 0xFF
            r_sym = r_info >> 8

            if r_type == R_MIPS_NONE:
                continue

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
    exports = []
    for sym in elf.symbols:
        if sym.binding != STB_GLOBAL:
            continue
        if sym.visibility != STV_DEFAULT:
            continue
        if sym.shndx == 0:
            continue
        if sym.shndx == 0xFFF1:
            continue
        if sym.name.startswith("__"):
            continue
        if not sym.name:
            continue

        exports.append((sym.value, sym.name))

    exports.sort(key=lambda e: e[0])
    return exports


def read_section_data(elf, names):
    for name in names:
        sec, data, size = get_section(elf, name)
        if sec is not None:
            return data, size
    return b"", 0


def _align(val, alignment):
    if alignment <= 1:
        return val
    return (val + alignment - 1) & ~(alignment - 1)


def link_overlay(obj_paths, syms, link_addr):
    """Pure-Python linker: link .o files into an overlay, returning ovl_bytes.

    Section layout:
      .text (.text, .text.*, .rodata, .rodata.*)
      .ctors (.ctors, .init_array)
      .dtors (.dtors, .fini_array)
      .data (.data, .data.*, .sdata, .sdata.*)
      .bss (.bss, .bss.*, .sbss, .sbss.*, COMMON) [NOLOAD]
    """
    # Parse all input ELFs
    elfs = []
    for path in obj_paths:
        with open(path, "rb") as f:
            elfs.append(Elf32(f.read()))

    # Section name groups
    # Each output section is a list of (pattern_group, ...) passes, mirroring
    # how GNU ld processes input-section wildcards: each *(...) line collects
    # matching sections from all inputs in input order before moving to the
    # next *(...) line.
    TEXT_GROUPS = [(".text",), (".rodata",)]
    CTORS_GROUPS = [(".ctors",), (".init_array",)]
    DTORS_GROUPS = [(".dtors",), (".fini_array",)]
    DATA_GROUPS = [(".data",), (".sdata",)]
    BSS_GROUPS = [(".bss",), (".sbss",)]

    def matches_pattern(sec_name, patterns):
        for pat in patterns:
            if sec_name == pat or sec_name.startswith(pat + "."):
                return True
        return False

    section_map = []  # [(elf_idx, sec_idx, output_vma, size)]
    cur_addr = link_addr

    def place_sections(groups, noload=False):
        nonlocal cur_addr
        start = cur_addr
        for patterns in groups:
            for elf_idx, elf in enumerate(elfs):
                for sec_idx, sec in enumerate(elf.sections):
                    if sec.type == SHT_NULL:
                        continue
                    if sec.size == 0:
                        continue
                    if not matches_pattern(sec.name, patterns):
                        continue
                    if noload:
                        if sec.type != SHT_NOBITS:
                            continue
                    else:
                        if sec.type not in (SHT_PROGBITS, SHT_INIT_ARRAY, SHT_FINI_ARRAY):
                            continue

                    align = max(sec.addralign, 1)
                    cur_addr = _align(cur_addr, align)
                    section_map.append((elf_idx, sec_idx, cur_addr, sec.size))
                    cur_addr += sec.size

        size = cur_addr - start
        return start, size

    text_start, text_total = place_sections(TEXT_GROUPS)
    ctors_start, ctors_total = place_sections(CTORS_GROUPS)
    dtors_start, dtors_total = place_sections(DTORS_GROUPS)
    data_start, data_total = place_sections(DATA_GROUPS)
    bss_start, bss_total = place_sections(BSS_GROUPS, noload=True)

    load_size = (data_start + data_total) - link_addr if data_total > 0 else (text_total + ctors_total + dtors_total)

    # Build load image
    load_data = bytearray(load_size)
    for elf_idx, sec_idx, vma, size in section_map:
        sec = elfs[elf_idx].sections[sec_idx]
        if sec.type == SHT_NOBITS or len(sec.content) == 0:
            continue
        off = vma - link_addr
        load_data[off:off + size] = sec.content[:size]

    # Build a lookup: (elf_idx, sec_idx) -> output VMA
    sec_vma_map = {}
    for elf_idx, sec_idx, vma, size in section_map:
        sec_vma_map[(elf_idx, sec_idx)] = vma

    # Build per-ELF symbol tables and a global export table
    # resolved_syms[(elf_idx, sym_idx)] = resolved_address
    resolved_syms = {}
    exports = []  # [(addr, name)]

    for elf_idx, elf in enumerate(elfs):
        for sym_idx, sym in enumerate(elf.symbols):
            if sym.shndx == SHN_UNDEF:
                # Undefined: look up in external syms dict
                if sym.name and sym.name in syms:
                    resolved_syms[(elf_idx, sym_idx)] = syms[sym.name]
                elif sym.name:
                    # Try other ELFs' globals
                    pass  # resolved in second pass
                continue
            if sym.shndx == SHN_ABS:
                resolved_syms[(elf_idx, sym_idx)] = sym.value
                continue
            if sym.shndx == SHN_COMMON:
                # COMMON symbols are allocated in .bss by the linker.
                # For .o files, they need to be placed. We handle them in
                # a separate pass below.
                continue

            key = (elf_idx, sym.shndx)
            if key in sec_vma_map:
                addr = sec_vma_map[key] + sym.value
                resolved_syms[(elf_idx, sym_idx)] = addr
                if sym.binding == STB_GLOBAL and sym.visibility == STV_DEFAULT:
                    if sym.name and not sym.name.startswith("__"):
                        exports.append((addr, sym.name))

    # Build global symbol table for cross-object resolution
    global_defined = {}  # name -> addr
    for (elf_idx, sym_idx), addr in resolved_syms.items():
        sym = elfs[elf_idx].symbols[sym_idx]
        if sym.binding == STB_GLOBAL and sym.name:
            global_defined[sym.name] = addr

    # Allocate COMMON symbols in bss
    common_addr = bss_start + bss_total
    for elf_idx, elf in enumerate(elfs):
        for sym_idx, sym in enumerate(elf.symbols):
            if sym.shndx != SHN_COMMON:
                continue
            align = max(sym.value, 1)  # for COMMON, st_value = alignment
            common_addr = _align(common_addr, align)
            resolved_syms[(elf_idx, sym_idx)] = common_addr
            if sym.binding == STB_GLOBAL and sym.name:
                global_defined[sym.name] = common_addr
            common_addr += sym.size
    bss_total = common_addr - bss_start

    # Second pass: resolve undefined symbols from other ELFs' globals
    for elf_idx, elf in enumerate(elfs):
        for sym_idx, sym in enumerate(elf.symbols):
            if (elf_idx, sym_idx) in resolved_syms:
                continue
            if sym.shndx == SHN_UNDEF and sym.name:
                if sym.name in global_defined:
                    resolved_syms[(elf_idx, sym_idx)] = global_defined[sym.name]
                elif sym.name in syms:
                    resolved_syms[(elf_idx, sym_idx)] = syms[sym.name]

    overlay_end = link_addr + load_size + bss_total

    # Apply relocations
    is_static = (link_addr != 0x80000000)
    reloc_entries = []  # (r_type, offset_in_load) for internal relocs

    for elf_idx, elf in enumerate(elfs):
        for sec in elf.sections:
            if sec.type != SHT_REL:
                continue
            target_sec_idx = sec.info
            target_key = (elf_idx, target_sec_idx)
            if target_key not in sec_vma_map:
                continue

            target_vma = sec_vma_map[target_key]
            data = sec.content
            pending_hi16 = []  # [(load_offset, sym_addr)]

            for i in range(0, len(data), 8):
                r_offset, r_info = struct.unpack(">II", data[i:i + 8])
                r_type = r_info & 0xFF
                r_sym = r_info >> 8

                if r_type == R_MIPS_NONE:
                    continue

                if r_type not in SUPPORTED_RELOCS:
                    print(f"warning: unsupported reloc type {r_type}", file=sys.stderr)
                    continue

                if (elf_idx, r_sym) not in resolved_syms:
                    sym = elf.symbols[r_sym] if r_sym < len(elf.symbols) else None
                    sym_name = sym.name if sym else f"sym#{r_sym}"
                    print(f"warning: unresolved symbol '{sym_name}'", file=sys.stderr)
                    continue

                sym_addr = resolved_syms[(elf_idx, r_sym)]
                load_offset = target_vma + r_offset - link_addr

                if load_offset < 0 or load_offset >= len(load_data):
                    continue

                is_internal = link_addr <= sym_addr < overlay_end

                if r_type == R_MIPS_32:
                    existing = struct.unpack_from(">I", load_data, load_offset)[0]
                    struct.pack_into(">I", load_data, load_offset, (sym_addr + existing) & 0xFFFFFFFF)
                    if is_internal and not is_static:
                        reloc_entries.append((R_MIPS_32, load_offset))

                elif r_type == R_MIPS_26:
                    insn = struct.unpack_from(">I", load_data, load_offset)[0]
                    target = ((insn & 0x3FFFFFF) << 2) + sym_addr
                    insn = (insn & 0xFC000000) | ((target >> 2) & 0x3FFFFFF)
                    struct.pack_into(">I", load_data, load_offset, insn)
                    if is_internal and not is_static:
                        reloc_entries.append((R_MIPS_26, load_offset))

                elif r_type == R_MIPS_HI16:
                    pending_hi16.append((load_offset, sym_addr))

                elif r_type == R_MIPS_LO16:
                    lo_insn = struct.unpack_from(">I", load_data, load_offset)[0]
                    lo_existing = lo_insn & 0xFFFF
                    if lo_existing >= 0x8000:
                        lo_existing -= 0x10000

                    for hi_load_offset, hi_sym_addr in pending_hi16:
                        hi_insn = struct.unpack_from(">I", load_data, hi_load_offset)[0]
                        hi_existing = hi_insn & 0xFFFF

                        full_addr = (hi_existing << 16) + lo_existing + hi_sym_addr
                        hi_val = ((full_addr >> 16) + (1 if full_addr & 0x8000 else 0)) & 0xFFFF
                        hi_insn = (hi_insn & 0xFFFF0000) | hi_val
                        struct.pack_into(">I", load_data, hi_load_offset, hi_insn)

                        if is_internal and not is_static:
                            reloc_entries.append((R_MIPS_HI16, hi_load_offset))

                    lo_val = (lo_existing + sym_addr) & 0xFFFF
                    lo_insn = (lo_insn & 0xFFFF0000) | lo_val
                    struct.pack_into(">I", load_data, load_offset, lo_insn)

                    if is_internal and not is_static:
                        reloc_entries.append((R_MIPS_LO16, load_offset))

                    pending_hi16 = []

    # For HI16/LO16 relocs in the .ovl, we need to pair them and store the
    # original address for HI16 entries (matching elf_to_overlay's format).
    r32_relocs = sorted([off for rt, off in reloc_entries if rt == R_MIPS_32])
    r26_relocs = sorted([off for rt, off in reloc_entries if rt == R_MIPS_26])

    # Rebuild HI16/LO16 pairing from reloc_entries order
    hi16_entries = []  # (offset, original_addr)
    lo16_offsets = []
    pending_hi = []
    for rt, off in reloc_entries:
        if rt == R_MIPS_HI16:
            pending_hi.append(off)
        elif rt == R_MIPS_LO16:
            if pending_hi:
                lo_insn = struct.unpack_from(">I", load_data, off)[0]
                lo_val = lo_insn & 0xFFFF
                if lo_val >= 0x8000:
                    lo_val -= 0x10000
                for hi_off in pending_hi:
                    hi_insn = struct.unpack_from(">I", load_data, hi_off)[0]
                    hi_val = hi_insn & 0xFFFF
                    hi16_entries.append((hi_off, (hi_val << 16) + lo_val))
                pending_hi = []
            lo16_offsets.append(off)

    # Get ctors/dtors data from the load image
    ctors_data = bytes(load_data[ctors_start - link_addr:ctors_start - link_addr + ctors_total]) if ctors_total > 0 else b""
    dtors_data = bytes(load_data[dtors_start - link_addr:dtors_start - link_addr + dtors_total]) if dtors_total > 0 else b""

    # The "text" size for the overlay header is text+rodata+ctors+dtors
    # (everything before .data)
    if data_total > 0:
        text_size = data_start - link_addr
    else:
        text_size = load_size

    # Build relocation blobs
    r32_blob = b"".join(struct.pack(">I", off) for off in r32_relocs)
    r26_blob = b"".join(struct.pack(">I", off) for off in r26_relocs)
    hi16_blob = b"".join(struct.pack(">II", off, addr) for off, addr in hi16_entries)
    lo16_blob = b"".join(struct.pack(">I", off) for off in lo16_offsets)

    # Build exports
    exports.sort(key=lambda e: e[0])
    export_entries = b""
    strtab = b""
    str_offsets = {}
    for offset, name in exports:
        if name not in str_offsets:
            str_offsets[name] = len(strtab)
            strtab += name.encode("ascii") + b"\x00"
        export_entries += struct.pack(">II", offset - link_addr, str_offsets[name])

    strtab_padded = strtab + b"\x00" * ((4 - len(strtab) % 4) % 4)

    # Meta section (persists in memory): exports + strtab (4-padded) + dtors
    meta_blob = export_entries + strtab_padded + dtors_data
    # Temporary section (DMA'd to stack): r32 + r26 + hi16 + lo16 + ctors
    temp_blob = r32_blob + r26_blob + hi16_blob + lo16_blob + ctors_data

    HEADER_SIZE = 48
    header = struct.pack(">4s", OVL_MAGIC)
    header += struct.pack(">I", len(load_data))
    header += struct.pack(">I", text_size)
    header += struct.pack(">I", bss_total)
    header += struct.pack(">I", len(exports))
    header += struct.pack(">I", len(strtab))  # unpadded
    header += struct.pack(">I", dtors_total // 4)
    header += struct.pack(">I", len(r32_relocs))
    header += struct.pack(">I", len(r26_relocs))
    header += struct.pack(">I", len(hi16_entries))
    header += struct.pack(">I", len(lo16_offsets))
    header += struct.pack(">I", ctors_total // 4)

    assert len(header) == HEADER_SIZE

    pad_to_16 = (16 - HEADER_SIZE % 16) % 16

    ovl = bytearray()
    ovl += header
    ovl += b"\x00" * pad_to_16
    ovl += load_data
    ovl += meta_blob
    ovl += temp_blob

    return bytes(ovl), exports, text_size, data_total, bss_total, load_data


def extract_debug_info_from_objects(obj_paths, section_map, sec_vma_map, elfs, link_addr):
    """Extract debug symbols from input .o files, adjusting to output layout.

    Returns a debug blob (SYMS format) with rom_base=0.
    """
    STT_FUNC = 2

    addr2name = {}
    all_line_entries = []

    for elf_idx, elf in enumerate(elfs):
        # Collect FUNC symbols
        for sym in elf.symbols:
            if sym.type != STT_FUNC or sym.value == 0:
                continue
            if sym.shndx in (SHN_UNDEF, SHN_ABS, SHN_COMMON):
                continue
            key = (elf_idx, sym.shndx)
            if key not in sec_vma_map:
                continue
            addr = sec_vma_map[key] + sym.value
            name = itanium_demangle(sym.name)
            if not name.startswith("dead_"):
                addr2name[addr] = name

        # Parse .debug_line (may fail for compressed/unusual debug sections)
        try:
            line_entries = parse_debug_line(elf)
        except (ValueError, IndexError, struct.error):
            line_entries = []
        # Remap addresses from input section to output layout
        for in_addr, file_basename, line_number in line_entries:
            # Find which section this address belongs to in the input ELF
            for sec_idx, sec in enumerate(elf.sections):
                if sec.type in (SHT_PROGBITS,) and sec.name.startswith(".text"):
                    if sec.addr <= in_addr < sec.addr + sec.size:
                        key = (elf_idx, sec_idx)
                        if key in sec_vma_map:
                            out_addr = sec_vma_map[key] + (in_addr - sec.addr)
                            all_line_entries.append((out_addr, file_basename, line_number))
                        break

    addr2line = {}
    for addr, file_basename, line_number in all_line_entries:
        addr2line[addr] = (file_basename, line_number)

    sorted_func_addrs = sorted(addr2name.keys())

    symbols = []
    for addr, (file_basename, line_number) in addr2line.items():
        if addr in addr2name:
            symbols.append((addr - link_addr, addr2name[addr], file_basename, line_number))
        else:
            closest_addr = None
            for a in sorted_func_addrs:
                if a < addr:
                    closest_addr = a
                else:
                    break
            if closest_addr is not None:
                symbols.append(
                    (addr - link_addr, addr2name[closest_addr], file_basename, line_number)
                )

    if len(symbols) == 0:
        for addr, name in addr2name.items():
            symbols.append((addr - link_addr, name, "", -1))

    symbols.sort(key=lambda x: x[0])
    return build_debug_symbol_table(symbols, 0)


def elf_to_overlay(input_path, output_path):
    """Convert a linked ELF (with --emit-relocs) into an overlay file."""
    with open(input_path, "rb") as f:
        elf_data = f.read()

    elf = Elf32(elf_data)

    text_sec, text_data, text_size = get_section(elf, ".text")
    LINK_ADDR = text_sec.addr if text_sec else 0x80000000

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

    exports = collect_exports(elf)

    # Static overlays don't need relocations (loaded at link address)
    if LINK_ADDR != 0x80000000:
        relocs = []
        r32_relocs = []
        r26_relocs = []
        lo16_relocs = []
    else:
        relocs = collect_relocs(elf)
        r32_relocs = sorted([r[1] for r in relocs if r[0] == R_MIPS_32])
        r26_relocs = sorted([r[1] for r in relocs if r[0] == R_MIPS_26])
        lo16_relocs = [r[1] for r in relocs if r[0] == R_MIPS_LO16]

    # Build load image preserving ELF memory layout (alignment gaps between
    # sections must be kept so that sym.value - LINK_ADDR indexes correctly).
    data_sec = elf.get_section(".data")
    if data_sec and data_size > 0:
        load_end = data_sec.addr + data_size
    else:
        load_end = LINK_ADDR + text_size
    load_data = bytearray(load_end - LINK_ADDR)
    load_data[0:text_size] = text_data
    if data_sec and data_size > 0:
        data_off = data_sec.addr - LINK_ADDR
        load_data[data_off:data_off + data_size] = data_data

    # Pair each HI16 with its next LO16 (MIPS ABI order) to recover the
    # original full address.  The pairing is only needed at build time;
    # at runtime HI16 and LO16 relocs are applied independently.
    hi16_entries = []  # (offset, original_addr)
    pending_hi16 = []
    for r_type, r_offset in relocs:
        if r_type == R_MIPS_HI16:
            pending_hi16.append(r_offset)
        elif r_type == R_MIPS_LO16 and pending_hi16:
            lo_insn = struct.unpack_from(">I", load_data, r_offset - LINK_ADDR)[0]
            lo_val = lo_insn & 0xFFFF
            if lo_val >= 0x8000:
                lo_val -= 0x10000
            for hi_off in pending_hi16:
                hi_insn = struct.unpack_from(">I", load_data, hi_off - LINK_ADDR)[0]
                hi_val = hi_insn & 0xFFFF
                hi16_entries.append((hi_off, (hi_val << 16) + lo_val))
            pending_hi16 = []
    if pending_hi16:
        print(
            f"warning: {len(pending_hi16)} orphan HI16 relocs",
            file=sys.stderr,
        )

    r32_blob = b"".join(struct.pack(">I", off - LINK_ADDR) for off in r32_relocs)
    r26_blob = b"".join(struct.pack(">I", off - LINK_ADDR) for off in r26_relocs)
    hi16_blob = b"".join(
        struct.pack(">II", off - LINK_ADDR, addr)
        for off, addr in hi16_entries
    )
    lo16_blob = b"".join(struct.pack(">I", off - LINK_ADDR) for off in lo16_relocs)

    export_entries = b""
    strtab = b""
    str_offsets = {}
    for offset, name in exports:
        if name not in str_offsets:
            str_offsets[name] = len(strtab)
            strtab += name.encode("ascii") + b"\x00"
        export_entries += struct.pack(">II", offset - LINK_ADDR, str_offsets[name])

    strtab_padded = strtab + b"\x00" * ((4 - len(strtab) % 4) % 4)

    # Meta section (persists in memory): exports + strtab (4-padded) + dtors
    meta_blob = export_entries + strtab_padded + dtors_data
    # Temporary section (DMA'd to stack): r32 + r26 + hi16 + lo16 + ctors
    temp_blob = r32_blob + r26_blob + hi16_blob + lo16_blob + ctors_data

    HEADER_SIZE = 48

    header = struct.pack(">4s", OVL_MAGIC)
    header += struct.pack(">I", len(load_data))
    header += struct.pack(">I", text_size)
    header += struct.pack(">I", bss_size)
    header += struct.pack(">I", len(exports))
    header += struct.pack(">I", len(strtab))  # unpadded
    header += struct.pack(">I", dtors_size // 4)
    header += struct.pack(">I", len(r32_relocs))
    header += struct.pack(">I", len(r26_relocs))
    header += struct.pack(">I", len(hi16_entries))
    header += struct.pack(">I", len(lo16_relocs))
    header += struct.pack(">I", ctors_size // 4)

    assert len(header) == HEADER_SIZE, (
        f"Header size mismatch: {len(header)} != {HEADER_SIZE}"
    )

    pad_to_16 = (16 - HEADER_SIZE % 16) % 16

    with open(output_path, "wb") as f:
        f.write(header)
        f.write(b"\x00" * pad_to_16)
        f.write(load_data)
        f.write(meta_blob)
        f.write(temp_blob)


# Overlay directory layout (must match overlay.c)
OVL_DIR_ENTRY_SIZE = 64 + 4 + 4 + 4 + 4  # name[64] + romStart + romEnd + debugRomStart + debugRomEnd
OVL_DIR_CAPACITY = 1024
OVL_DIR_HEADER_SIZE = 4 + 4  # magic(u32) + count(u32)


def parse_syms(syms_path):
    """Parse a syms.ld file into a dict of symbol name -> integer value."""
    syms = {}
    with open(syms_path) as f:
        for line in f:
            line = line.strip().rstrip(";").strip()
            if line.startswith("PROVIDE(") and line.endswith(")"):
                line = line[len("PROVIDE("):-1].strip()
            if "=" not in line:
                continue
            name, _, value = line.partition("=")
            name = name.strip()
            value = value.strip()
            try:
                syms[name] = int(value, 0)
            except ValueError:
                pass
    return syms


def load_syms(path):
    """Load a pickled syms dict from a .pkl file."""
    with open(path, "rb") as f:
        return pickle.load(f)


def gen_syms_from_elf(elf_path):
    """Read an ELF and return a dict of global defined symbol name -> value."""
    with open(elf_path, "rb") as f:
        elf = Elf32(f.read())

    STT_NOTYPE = 0
    STT_OBJECT = 1
    STT_FUNC = 2
    STT_SECTION = 3

    syms = {}
    for sym in elf.symbols:
        if not sym.name:
            continue
        if sym.binding == STB_LOCAL:
            continue
        if sym.shndx == SHN_UNDEF:
            continue
        # Match nm filter: T/t/D/d/B/b/A (global defined or absolute)
        syms[sym.name] = sym.value

    return syms


def cmd_gen_syms(args):
    """Subcommand: generate pickled syms from an ELF."""
    syms = gen_syms_from_elf(args.input)
    data = pickle.dumps(syms)

    # Restat: only update if contents changed
    tmp_path = args.output + ".tmp"
    with open(tmp_path, "wb") as f:
        f.write(data)

    try:
        with open(args.output, "rb") as f:
            old_data = f.read()
        if old_data == data:
            os.unlink(tmp_path)
            return
    except FileNotFoundError:
        pass

    os.replace(tmp_path, args.output)


def get_or_create_overlay_directory(syms, rom_data, type_index=0):
    """Get or create the overlay directory in the ROM, returning its ROM offset.

    rom_data is a bytearray that is modified in-place.

    ovlDirectoryRomAddr is an array of u32 pointers keyed by overlay type.
    type_index selects which element to use.

    On first invocation (the pointer is zero), creates the directory at the end
    of the ROM and patches the pointer. Subsequent invocations read the existing
    pointer.
    """
    for name in ("ovlDirectoryRomAddr", "main_VRAM", "main_ROM_START"):
        if name not in syms:
            print(f"error: '{name}' not found in syms file", file=sys.stderr)
            sys.exit(1)
    vma = syms["ovlDirectoryRomAddr"] + type_index * 4
    base = syms["main_VRAM"]
    rom_start = syms["main_ROM_START"]
    ptr_rom_offset = vma - base + rom_start

    dir_rom_addr = struct.unpack(">I", rom_data[ptr_rom_offset : ptr_rom_offset + 4])[0]

    if dir_rom_addr == 0:
        rom_end = len(rom_data)
        dir_rom_addr = (rom_end + 15) & ~15
        padding = dir_rom_addr - rom_end

        rom_data.extend(b"\x00" * padding)
        rom_data.extend(struct.pack(">II", 0x4D4F4444, 0))  # MODD magic, count=0
        rom_data.extend(b"\x00" * (OVL_DIR_ENTRY_SIZE * OVL_DIR_CAPACITY))

        struct.pack_into(">I", rom_data, ptr_rom_offset, dir_rom_addr)

    return dir_rom_addr


def apply_overlay(overlay_data, rom_data, name, dir_rom_offset, debug_blob=None):
    """Apply an overlay to rom_data (bytearray), modifying it in-place.

    debug_blob is a SYMS blob built with rom_base=0.  String offsets are
    fixed up to the actual placement address.
    """
    if len(name) >= 64:
        print(f"error: overlay name '{name}' exceeds 63 characters", file=sys.stderr)
        sys.exit(1)

    count = struct.unpack(">I", rom_data[dir_rom_offset + 4 : dir_rom_offset + 8])[0]
    entries_offset = dir_rom_offset + OVL_DIR_HEADER_SIZE

    existing_slot = None
    for i in range(count):
        entry_off = entries_offset + i * OVL_DIR_ENTRY_SIZE
        entry_name = rom_data[entry_off : entry_off + 64]
        entry_name = entry_name.split(b"\x00", 1)[0].decode("ascii")
        if entry_name == name:
            existing_slot = i
            break

    if existing_slot is not None:
        slot = existing_slot
    else:
        if count >= OVL_DIR_CAPACITY:
            print("error: max overlays of this type reached", file=sys.stderr)
            sys.exit(1)
        slot = count
        count += 1

    rom_end = len(rom_data)
    ovl_rom_start = (rom_end + 15) & ~15
    padding = ovl_rom_start - rom_end

    rom_data.extend(b"\x00" * padding)
    rom_data.extend(overlay_data)
    overlay_rom_end = ovl_rom_start + len(overlay_data)

    debug_rom_start = 0
    debug_rom_end = 0
    if debug_blob:
        debug_rom_start = (overlay_rom_end + 15) & ~15
        debug_padding = debug_rom_start - overlay_rom_end
        rom_data.extend(b"\x00" * debug_padding)
        # Fix up string offsets: each symbol entry is 12 bytes (addr, nameOff, fileOff)
        # starting after the 8-byte header.  Add rom_base to non-zero offsets.
        blob = bytearray(debug_blob)
        sym_count = struct.unpack_from(">I", blob, 4)[0]
        for i in range(sym_count):
            off = 8 + i * 12
            name_off = struct.unpack_from(">I", blob, off + 4)[0]
            file_off = struct.unpack_from(">I", blob, off + 8)[0]
            struct.pack_into(">I", blob, off + 4, name_off + debug_rom_start)
            if file_off != 0:
                struct.pack_into(">I", blob, off + 8, file_off + debug_rom_start)
        rom_data.extend(blob)
        debug_rom_end = debug_rom_start + len(blob)

    struct.pack_into(">I", rom_data, dir_rom_offset + 4, count)

    entry_off = entries_offset + slot * OVL_DIR_ENTRY_SIZE
    name_bytes = name.encode("ascii")
    rom_data[entry_off : entry_off + 64] = name_bytes + b"\x00" * (64 - len(name_bytes))
    struct.pack_into(">IIII", rom_data, entry_off + 64,
                     ovl_rom_start, overlay_rom_end,
                     debug_rom_start, debug_rom_end)


def parse_debug_line(elf):
    """Parse DWARF .debug_line to produce (address, file_basename, line) tuples."""
    sec = elf.get_section(".debug_line")
    if sec is None or sec.size == 0:
        return []

    data = sec.content
    results = []
    pos = 0

    while pos < len(data):
        unit_start = pos
        unit_length = struct.unpack(">I", data[pos:pos+4])[0]
        pos += 4
        unit_end = pos + unit_length

        version = struct.unpack(">H", data[pos:pos+2])[0]
        pos += 2
        header_length = struct.unpack(">I", data[pos:pos+4])[0]
        pos += 4
        header_end = pos + header_length

        minimum_instruction_length = data[pos]; pos += 1
        default_is_stmt = data[pos]; pos += 1
        line_base = data[pos]; pos += 1
        if line_base >= 128:
            line_base -= 256
        line_range = data[pos]; pos += 1
        opcode_base = data[pos]; pos += 1

        # Skip standard opcode lengths
        pos += opcode_base - 1

        # Include directories (null-terminated strings, ended by empty string)
        include_dirs = [""]  # index 0 = compilation directory
        while pos < header_end and data[pos] != 0:
            end = data.index(b"\x00"[0], pos)
            include_dirs.append(data[pos:end].decode("utf-8", errors="replace"))
            pos = end + 1
        pos += 1  # skip terminating zero

        # File name table
        file_names = [("", 0)]  # index 0 placeholder
        while pos < header_end and data[pos] != 0:
            end = data.index(b"\x00"[0], pos)
            fname = data[pos:end].decode("utf-8", errors="replace")
            pos = end + 1
            _dir_index = _read_uleb128(data, pos); pos = _dir_index[1]
            _mod_time = _read_uleb128(data, pos); pos = _mod_time[1]
            _file_length = _read_uleb128(data, pos); pos = _file_length[1]
            file_names.append((fname, _dir_index[0]))
        pos += 1  # skip terminating zero

        pos = header_end

        # Run the line number state machine
        address = 0
        line = 1
        file_idx = 1
        is_stmt = default_is_stmt
        end_sequence = False

        while pos < unit_end:
            opcode = data[pos]; pos += 1

            if opcode == 0:
                # Extended opcode
                ext_len, pos = _read_uleb128(data, pos)
                ext_end = pos + ext_len
                ext_op = data[pos]; pos += 1
                if ext_op == 1:  # DW_LNE_end_sequence
                    end_sequence = True
                    address = 0
                    line = 1
                    file_idx = 1
                elif ext_op == 2:  # DW_LNE_set_address
                    address = struct.unpack(">I", data[pos:pos+4])[0]
                    pos += 4
                else:
                    pos = ext_end
            elif opcode < opcode_base:
                # Standard opcodes
                if opcode == 1:  # DW_LNS_copy
                    if file_idx < len(file_names):
                        fname = file_names[file_idx][0]
                        if fname.endswith(".c") or fname.endswith(".cpp"):
                            basename = fname.rsplit("/", 1)[-1]
                            results.append((address, basename, line))
                elif opcode == 2:  # DW_LNS_advance_pc
                    adv, pos = _read_uleb128(data, pos)
                    address += adv * minimum_instruction_length
                elif opcode == 3:  # DW_LNS_advance_line
                    adv, pos = _read_sleb128(data, pos)
                    line += adv
                elif opcode == 4:  # DW_LNS_set_file
                    file_idx, pos = _read_uleb128(data, pos)
                elif opcode == 5:  # DW_LNS_set_column
                    _, pos = _read_uleb128(data, pos)
                elif opcode == 6:  # DW_LNS_negate_stmt
                    is_stmt = not is_stmt
                elif opcode == 7:  # DW_LNS_set_basic_block
                    pass
                elif opcode == 8:  # DW_LNS_const_add_pc
                    address += ((255 - opcode_base) // line_range) * minimum_instruction_length
                elif opcode == 9:  # DW_LNS_fixed_advance_pc
                    address += struct.unpack(">H", data[pos:pos+2])[0]
                    pos += 2
                else:
                    # Unknown standard opcode, skip operands
                    pass
            else:
                # Special opcode
                adjusted = opcode - opcode_base
                address += (adjusted // line_range) * minimum_instruction_length
                line += line_base + (adjusted % line_range)
                if file_idx < len(file_names):
                    fname = file_names[file_idx][0]
                    if fname.endswith(".c") or fname.endswith(".cpp"):
                        basename = fname.rsplit("/", 1)[-1]
                        results.append((address, basename, line))

        pos = unit_end

    return results


def _read_uleb128(data, pos):
    result = 0
    shift = 0
    while True:
        byte = data[pos]; pos += 1
        result |= (byte & 0x7F) << shift
        if (byte & 0x80) == 0:
            break
        shift += 7
    return result, pos


def _read_sleb128(data, pos):
    result = 0
    shift = 0
    while True:
        byte = data[pos]; pos += 1
        result |= (byte & 0x7F) << shift
        shift += 7
        if (byte & 0x80) == 0:
            if byte & 0x40:
                result |= -(1 << shift)
            break
    return result, pos


# Itanium ABI type codes used in mangled names
_BUILTIN_TYPES = {
    "v": "void", "w": "wchar_t", "b": "bool",
    "c": "char", "a": "signed char", "h": "unsigned char",
    "s": "short", "t": "unsigned short",
    "i": "int", "j": "unsigned int",
    "l": "long", "m": "unsigned long",
    "x": "long long", "y": "unsigned long long",
    "n": "__int128", "o": "unsigned __int128",
    "f": "float", "d": "double", "e": "long double",
    "z": "...",
}


def itanium_demangle(name):
    """Demangle an Itanium ABI mangled name. Falls back to the raw name."""
    if not name.startswith("_Z"):
        return name
    try:
        result, _ = _demangle_encoding(name, 2)
        return result
    except (IndexError, ValueError):
        return name


def _demangle_encoding(s, pos):
    if pos < len(s) and s[pos] == "N":
        return _demangle_nested_name(s, pos)
    name, pos = _demangle_unqualified_name(s, pos)
    if pos < len(s) and s[pos] not in ("E",):
        # Parse function parameter types for display
        params, pos = _demangle_type_list(s, pos)
        return f"{name}({', '.join(params)})", pos
    return name, pos


def _demangle_nested_name(s, pos):
    assert s[pos] == "N"
    pos += 1
    # Optional CV-qualifiers and ref-qualifier
    while pos < len(s) and s[pos] in ("r", "V", "K", "R", "O"):
        pos += 1
    parts = []
    while pos < len(s) and s[pos] != "E":
        if s[pos] == "I":
            # Template args
            args, pos = _demangle_template_args(s, pos)
            if parts:
                parts[-1] = parts[-1] + args
        elif s[pos] == "S":
            sub, pos = _demangle_substitution(s, pos)
            parts.append(sub)
        else:
            part, pos = _demangle_unqualified_name(s, pos)
            parts.append(part)
    if pos < len(s):
        pos += 1  # skip 'E'
    name = "::".join(parts)
    if pos < len(s) and s[pos] not in ("E",) and pos < len(s):
        params, pos = _demangle_type_list(s, pos)
        if params:
            return f"{name}({', '.join(params)})", pos
    return name, pos


def _demangle_unqualified_name(s, pos):
    if s[pos].isdigit():
        return _demangle_source_name(s, pos)
    if s[pos] == "C":
        pos += 2  # C1, C2, C3
        return "{ctor}", pos
    if s[pos] == "D":
        pos += 2  # D0, D1, D2
        return "{dtor}", pos
    return s[pos], pos + 1


def _demangle_source_name(s, pos):
    length = 0
    while pos < len(s) and s[pos].isdigit():
        length = length * 10 + int(s[pos])
        pos += 1
    name = s[pos : pos + length]
    return name, pos + length


def _demangle_type(s, pos):
    # Pointer
    if s[pos] == "P":
        inner, pos = _demangle_type(s, pos + 1)
        return f"{inner}*", pos
    # L-value reference
    if s[pos] == "R":
        inner, pos = _demangle_type(s, pos + 1)
        return f"{inner}&", pos
    # R-value reference
    if s[pos] == "O":
        inner, pos = _demangle_type(s, pos + 1)
        return f"{inner}&&", pos
    # Const
    if s[pos] == "K":
        inner, pos = _demangle_type(s, pos + 1)
        return f"{inner} const", pos
    # Volatile
    if s[pos] == "V":
        inner, pos = _demangle_type(s, pos + 1)
        return f"{inner} volatile", pos
    # Builtin
    if s[pos] in _BUILTIN_TYPES:
        return _BUILTIN_TYPES[s[pos]], pos + 1
    # Nested name
    if s[pos] == "N":
        name, pos = _demangle_nested_name(s, pos)
        return name, pos
    # Source name (unscoped)
    if s[pos].isdigit():
        name, pos = _demangle_source_name(s, pos)
        if pos < len(s) and s[pos] == "I":
            args, pos = _demangle_template_args(s, pos)
            name = name + args
        return name, pos
    # Substitution
    if s[pos] == "S":
        return _demangle_substitution(s, pos)
    # Function type F...E
    if s[pos] == "F":
        pos += 1
        ret, pos = _demangle_type(s, pos)
        params, pos = _demangle_type_list_until(s, pos, "E")
        pos += 1  # skip E
        return f"{ret}({', '.join(params)})", pos
    return s[pos], pos + 1


def _demangle_type_list(s, pos):
    types = []
    while pos < len(s) and s[pos] not in ("E",):
        try:
            t, new_pos = _demangle_type(s, pos)
            if new_pos == pos:
                break
            types.append(t)
            pos = new_pos
        except (IndexError, ValueError):
            break
    return types, pos


def _demangle_type_list_until(s, pos, end_char):
    types = []
    while pos < len(s) and s[pos] != end_char:
        t, pos = _demangle_type(s, pos)
        types.append(t)
    return types, pos


def _demangle_template_args(s, pos):
    assert s[pos] == "I"
    pos += 1
    args = []
    while pos < len(s) and s[pos] != "E":
        t, pos = _demangle_type(s, pos)
        args.append(t)
    if pos < len(s):
        pos += 1  # skip E
    return "<" + ", ".join(args) + ">", pos


def _demangle_substitution(s, pos):
    assert s[pos] == "S"
    pos += 1
    # Well-known substitutions
    if pos < len(s) and s[pos] == "t":
        return "std", pos + 1
    if pos < len(s) and s[pos] == "s":
        return "std::string", pos + 1
    if pos < len(s) and s[pos] == "a":
        return "std::allocator", pos + 1
    if pos < len(s) and s[pos] == "o":
        return "std::ostream", pos + 1
    if pos < len(s) and s[pos] == "i":
        return "std::istream", pos + 1
    # Numbered substitution S<seq-id>_ - just skip it
    while pos < len(s) and s[pos] != "_":
        pos += 1
    if pos < len(s):
        pos += 1  # skip _
    return "?", pos


def extract_debug_blob(elf_path):
    """Extract debug symbols from an overlay ELF and return a SYMS blob.

    The blob is built with rom_base=0; callers fix up string offsets by adding
    the actual ROM base.  Results are cached to <elf_path>.debug_syms.
    """
    cache_path = elf_path + ".debug_syms"
    try:
        if os.path.getmtime(cache_path) >= os.path.getmtime(elf_path):
            with open(cache_path, "rb") as f:
                return f.read()
    except OSError:
        pass

    with open(elf_path, "rb") as f:
        elf = Elf32(f.read())
    text_sec = elf.get_section(".text")
    LINK_ADDR = text_sec.addr if text_sec else 0x80000000

    STT_FUNC = 2
    addr2name = {}
    for sym in elf.symbols:
        if sym.type == STT_FUNC and sym.value != 0:
            name = itanium_demangle(sym.name)
            if not name.startswith("dead_"):
                addr2name[sym.value] = name

    line_entries = parse_debug_line(elf)
    addr2line = {}
    for addr, file_basename, line_number in line_entries:
        addr2line[addr] = (file_basename, line_number)

    sorted_func_addrs = sorted(addr2name.keys())

    symbols = []
    for addr, (file_basename, line_number) in addr2line.items():
        if addr in addr2name:
            symbols.append((addr - LINK_ADDR, addr2name[addr], file_basename, line_number))
        else:
            closest_addr = None
            for a in sorted_func_addrs:
                if a < addr:
                    closest_addr = a
                else:
                    break
            if closest_addr is not None:
                symbols.append(
                    (addr - LINK_ADDR, addr2name[closest_addr], file_basename, line_number)
                )

    if len(symbols) == 0:
        for addr, name in addr2name.items():
            symbols.append((addr - LINK_ADDR, name, "", -1))

    symbols.sort(key=lambda x: x[0])

    blob = build_debug_symbol_table(symbols, 0)

    with open(cache_path, "wb") as f:
        f.write(blob)

    return blob


def build_debug_symbol_table(symbols, rom_base):
    """Build a debug symbol table blob.

    rom_base is the ROM offset where this blob will be placed, used to compute
    absolute ROM offsets for strings.

    Returns the complete blob (header + symbols + strings).
    """
    sizeof_symbol = 4 + 4 + 4  # address, nameOffset, fileOffset
    header_size = 4 + 4  # magic + symbolCount
    strings_begin = rom_base + header_size + sizeof_symbol * len(symbols)

    strings = bytearray()
    string_map = {}

    def add_string(s):
        nonlocal strings
        if s not in string_map:
            string_map[s] = strings_begin + len(strings)
            strings += s.encode("utf-8")
            strings += b"\0"
        return string_map[s]

    blob = bytearray()
    blob += b"SYMS"
    blob += struct.pack(">I", len(symbols))

    for offset, name, file_basename, line_number in symbols:
        blob += struct.pack(">I", offset)
        blob += struct.pack(">I", add_string(name))
        if file_basename == "":
            blob += struct.pack(">I", 0)
        else:
            blob += struct.pack(">I", add_string(f"{file_basename}:{line_number}"))

    blob += strings

    # Pad to 16-byte alignment
    padding = (len(blob) + 15) & ~15
    blob += b"\x00" * (padding - len(blob))

    return bytes(blob)


def cmd_convert(args):
    """Subcommand: convert an ELF to overlay format."""
    elf_to_overlay(args.elf, args.output)


def cmd_link(args):
    """Subcommand: link .o files into an overlay directly."""
    syms = load_syms(args.syms_cache)
    link_addr = int(args.link_addr, 0)

    ovl_bytes, exports, text_size, data_size, bss_size, load_data = link_overlay(
        args.objects, syms, link_addr,
    )

    with open(args.output, "wb") as f:
        f.write(ovl_bytes)

    # Build debug symbols from the input .o files
    elfs = []
    for path in args.objects:
        with open(path, "rb") as f:
            elfs.append(Elf32(f.read()))

    # Rebuild section_map and sec_vma_map for debug extraction
    # (mirrors what link_overlay does)
    TEXT_GROUPS = [(".text",), (".rodata",)]
    CTORS_GROUPS = [(".ctors",), (".init_array",)]
    DTORS_GROUPS = [(".dtors",), (".fini_array",)]
    DATA_GROUPS = [(".data",), (".sdata",)]
    BSS_GROUPS = [(".bss",), (".sbss",)]

    def matches_pattern(sec_name, patterns):
        for pat in patterns:
            if sec_name == pat or sec_name.startswith(pat + "."):
                return True
        return False

    section_map = []
    sec_vma_map = {}
    cur_addr = link_addr

    def place_sections(groups, noload=False):
        nonlocal cur_addr
        for patterns in groups:
            for elf_idx, elf in enumerate(elfs):
                for sec_idx, sec in enumerate(elf.sections):
                    if sec.type == SHT_NULL:
                        continue
                    if sec.size == 0:
                        continue
                    if not matches_pattern(sec.name, patterns):
                        continue
                    if noload:
                        if sec.type != SHT_NOBITS:
                            continue
                    else:
                        if sec.type not in (SHT_PROGBITS, SHT_INIT_ARRAY, SHT_FINI_ARRAY):
                            continue
                    align = max(sec.addralign, 1)
                    cur_addr = _align(cur_addr, align)
                    section_map.append((elf_idx, sec_idx, cur_addr, sec.size))
                    sec_vma_map[(elf_idx, sec_idx)] = cur_addr
                    cur_addr += sec.size

    place_sections(TEXT_GROUPS)
    place_sections(CTORS_GROUPS)
    place_sections(DTORS_GROUPS)
    place_sections(DATA_GROUPS)
    place_sections(BSS_GROUPS, noload=True)

    debug_blob = extract_debug_info_from_objects(
        args.objects, section_map, sec_vma_map, elfs, link_addr,
    )

    debug_path = args.output + ".debug_syms"
    with open(debug_path, "wb") as f:
        f.write(debug_blob)


def cmd_apply(args):
    """Subcommand: apply an overlay to a ROM (non-mutating)."""

    syms = parse_syms(args.syms)

    with open(args.input_rom, "rb") as f:
        rom_data = bytearray(f.read())

    dir_offset = get_or_create_overlay_directory(syms, rom_data, args.type_index)

    with open(args.overlay_file, "rb") as f:
        overlay_data = f.read()

    debug_blob = None
    if args.elf:
        debug_blob = extract_debug_blob(args.elf)

    apply_overlay(overlay_data, rom_data, args.name, dir_offset, debug_blob)

    with open(args.output_rom, "wb") as f:
        f.write(rom_data)

    n64crc = SCRIPT_DIR / "rom" / "n64crc"
    subprocess.run([str(n64crc), args.output_rom], check=True)


def cmd_apply_all(args):
    """Subcommand: apply all overlays listed in a manifest to a ROM."""
    import json

    # Support both .pkl and .ld syms files
    if args.syms.endswith(".pkl"):
        syms = load_syms(args.syms)
    else:
        syms = parse_syms(args.syms)

    with open(args.manifest) as f:
        entries = json.load(f)

    with open(args.input_rom, "rb") as f:
        rom_data = bytearray(f.read())

    dir_offsets = {}

    for entry in entries:
        name = entry["name"]
        type_index = entry["type_index"]
        ovl_path = entry["ovl"]
        debug_syms_path = entry.get("debug_syms")
        elf_path = entry.get("elf")

        if type_index not in dir_offsets:
            dir_offsets[type_index] = get_or_create_overlay_directory(
                syms, rom_data, type_index
            )

        with open(ovl_path, "rb") as f:
            overlay_data = f.read()

        debug_blob = None
        if debug_syms_path:
            try:
                with open(debug_syms_path, "rb") as f:
                    debug_blob = f.read()
            except FileNotFoundError:
                pass
        elif elf_path:
            debug_blob = extract_debug_blob(elf_path)

        apply_overlay(
            overlay_data, rom_data,
            name, dir_offsets[type_index], debug_blob,
        )

    with open(args.output_rom, "wb") as f:
        f.write(rom_data)

    n64crc = SCRIPT_DIR / "rom" / "n64crc"
    subprocess.run([str(n64crc), args.output_rom], check=True)


def main():
    parser = argparse.ArgumentParser(description="Overlay builder")
    subparsers = parser.add_subparsers(dest="command", required=True)

    p_gen_syms = subparsers.add_parser("gen-syms", help="Generate pickled syms from ELF")
    p_gen_syms.add_argument("input", help="Input ELF file")
    p_gen_syms.add_argument("output", help="Output .pkl file")
    p_gen_syms.set_defaults(func=cmd_gen_syms)

    p_convert = subparsers.add_parser("convert", help="Convert ELF to overlay format")
    p_convert.add_argument("elf", help="Input ELF file")
    p_convert.add_argument("output", help="Output file")
    p_convert.set_defaults(func=cmd_convert)

    p_link = subparsers.add_parser("link", help="Link .o files into an overlay")
    p_link.add_argument("syms_cache", help="Pickled syms file (.pkl)")
    p_link.add_argument("output", help="Output .ovl file")
    p_link.add_argument("link_addr", help="Link address (e.g. 0x80240000)")
    p_link.add_argument("objects", nargs="+", help="Input .o files")
    p_link.set_defaults(func=cmd_link)

    p_apply = subparsers.add_parser("apply", help="Apply an overlay to a ROM")
    p_apply.add_argument("input_rom", help="Input ROM file (not modified)")
    p_apply.add_argument("output_rom", help="Output ROM file")
    p_apply.add_argument("syms", help="Symbol file (syms.ld)")
    p_apply.add_argument("name", help="Overlay name")
    p_apply.add_argument("overlay_file", help="Overlay file (.ovl)")
    p_apply.add_argument("--type-index", type=int, default=0, help="Overlay type index")
    p_apply.add_argument("--elf", help="ELF file for debug symbol extraction")
    p_apply.set_defaults(func=cmd_apply)

    p_apply_all = subparsers.add_parser("apply-all", help="Apply all overlays from a manifest")
    p_apply_all.add_argument("input_rom", help="Input ROM file (not modified)")
    p_apply_all.add_argument("output_rom", help="Output ROM file")
    p_apply_all.add_argument("syms", help="Symbol file (syms.ld)")
    p_apply_all.add_argument("manifest", help="JSON manifest listing overlays")
    p_apply_all.set_defaults(func=cmd_apply_all)

    args = parser.parse_args()
    args.func(args)


if __name__ == "__main__":
    main()
