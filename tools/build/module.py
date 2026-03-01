#!/usr/bin/env python3
"""Build and attach a module to a Paper Mario ROM.

Usage: module.py [--version VERSION] <rom> <syms> <name> <sources...>

Compiles the source files, links them into a relocatable module,
and attaches to the ROM.
"""

import argparse
import json
import struct
import subprocess
import sys
import tempfile
from pathlib import Path

SCRIPT_DIR = Path(__file__).resolve().parent
ROOT = SCRIPT_DIR.parent.parent

MOD_MAGIC = b"MOD\x00"
MOD_VERSION = 2
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

            self.sections.append(
                ElfSection(name, sh_type, sh_offset, sh_size, sh_link, sec_data)
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
        target_name = sec.name[4:]
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


def elf_to_module(input_path, output_path):
    """Convert a linked ELF (with --emit-relocs) into a .module file."""
    with open(input_path, "rb") as f:
        elf_data = f.read()

    elf = Elf32(elf_data)
    LINK_ADDR = 0x80000000

    _, text_data, text_size = get_section(elf, ".text")

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

    r32_relocs = sorted([r[1] for r in relocs if r[0] == R_MIPS_32])
    r26_relocs = sorted([r[1] for r in relocs if r[0] == R_MIPS_26])
    hi16_relocs = [r[1] for r in relocs if r[0] == R_MIPS_HI16]
    lo16_relocs = [r[1] for r in relocs if r[0] == R_MIPS_LO16]

    if len(hi16_relocs) != len(lo16_relocs):
        print(
            f"error: HI16/LO16 count mismatch ({len(hi16_relocs)} vs {len(lo16_relocs)})",
            file=sys.stderr,
        )
        sys.exit(1)

    r32_blob = b"".join(struct.pack(">I", off - LINK_ADDR) for off in r32_relocs)
    r26_blob = b"".join(struct.pack(">I", off - LINK_ADDR) for off in r26_relocs)
    hi16_blob = b"".join(struct.pack(">I", off - LINK_ADDR) for off in hi16_relocs)
    lo16_blob = b"".join(struct.pack(">I", off - LINK_ADDR) for off in lo16_relocs)

    export_entries = b""
    strtab = b""
    str_offsets = {}
    for offset, name in exports:
        if name not in str_offsets:
            str_offsets[name] = len(strtab)
            strtab += name.encode("ascii") + b"\x00"
        export_entries += struct.pack(">II", offset - LINK_ADDR, str_offsets[name])

    HEADER_SIZE = 92

    off = (HEADER_SIZE + 15) & ~15
    text_off = off
    off += len(text_data)
    data_off = off
    off += len(data_data)
    r32_off = off
    off += len(r32_blob)
    r26_off = off
    off += len(r26_blob)
    hi16_off = off
    off += len(hi16_blob)
    lo16_off = off
    off += len(lo16_blob)
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
    header += struct.pack(">II", r32_off, len(r32_relocs))
    header += struct.pack(">II", r26_off, len(r26_relocs))
    header += struct.pack(">II", hi16_off, len(hi16_relocs))
    header += struct.pack(">II", lo16_off, len(lo16_relocs))
    header += struct.pack(">II", ctor_off, ctors_size // 4)
    header += struct.pack(">II", dtor_off, dtors_size // 4)
    header += struct.pack(">II", export_off, len(exports))
    header += struct.pack(">II", strtab_off, len(strtab))

    assert len(header) == HEADER_SIZE, (
        f"Header size mismatch: {len(header)} != {HEADER_SIZE}"
    )

    with open(output_path, "wb") as f:
        f.write(header)
        f.write(b"\x00" * (text_off - HEADER_SIZE))
        f.write(text_data)
        f.write(data_data)
        f.write(r32_blob)
        f.write(r26_blob)
        f.write(hi16_blob)
        f.write(lo16_blob)
        f.write(ctors_data)
        f.write(dtors_data)
        f.write(export_entries)
        f.write(strtab)

    total_size = off
    total_relocs = len(r32_relocs) + len(r26_relocs) + len(hi16_relocs) + len(lo16_relocs)
    print(
        f"  {Path(output_path).name}: {total_size} bytes "
        f"(text={text_size} data={data_size} bss={bss_size} "
        f"relocs={total_relocs} exports={len(exports)})"
    )


# Module directory layout (must match module.cpp)
MODULE_DIR_ENTRY_SIZE = 64 + 4 + 4 + 4 + 4 + 4  # name[64] + romStart + romEnd + flags + debugRomStart + debugRomEnd
MODULE_DIR_CAPACITY = 1024
MODULE_DIR_HEADER_SIZE = 4 + 4  # magic(u32) + count(u32)

MODULE_FLAG_AUTOLOAD = 1 << 0


def parse_syms(syms_path):
    """Parse a syms.ld file into a dict of symbol name -> integer value."""
    syms = {}
    with open(syms_path) as f:
        for line in f:
            line = line.strip().rstrip(";").strip()
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


def module_directory_rom_offset(syms):
    """Compute the ROM file offset of moduleDirectory from linker symbols."""
    for name in ("moduleDirectory", "main_VRAM", "main_ROM_START"):
        if name not in syms:
            print(f"error: '{name}' not found in syms file", file=sys.stderr)
            sys.exit(1)
    vma = syms["moduleDirectory"]
    base = syms["main_VRAM"]
    rom_start = syms["main_ROM_START"]
    offset = vma - base + rom_start
    print(f"  moduleDirectory: VMA=0x{vma:08X} main_VRAM=0x{base:08X} main_ROM_START=0x{rom_start:08X} -> ROM offset 0x{offset:08X}")
    return offset


def compile_sources(sources, version, build_dir):
    """Compile source files and return a list of object file paths."""
    build_dir.mkdir(parents=True, exist_ok=True)

    cppflags = [
        f"-I{ROOT}/include",
        f"-I{ROOT}/src",
        f"-I{ROOT}/ver/{version}/include",
        f"-I{ROOT}/ver/{version}/build/include",
        f"-I{ROOT}/assets/{version}",
        "-D_FINALROM",
        f"-DVERSION={version}",
        "-DF3DEX_GBI_2",
        "-D_MIPS_SZLONG=32",
    ]

    cflags = [
        "-c", "-G0", "-O2", "-g1",
        "-funsigned-char", "-mgp32", "-mfp32", "-mabi=32",
        "-mfix4300", "-march=vr4300", "-mno-gpopt",
        "-mno-abicalls", "-fno-pic", "-fno-exceptions",
        "-fno-stack-protector", "-fno-zero-initialized-in-bss",
    ]

    objects = []
    for src in sources:
        src = Path(src)
        obj = build_dir / (src.stem + ".o")

        if src.suffix in (".cpp", ".cxx", ".cc"):
            compiler = f"{CROSS}g++"
            lang_flags = ["-std=c++20", "-D_LANGUAGE_C_PLUS_PLUS"]
        elif src.suffix == ".c":
            compiler = f"{CROSS}gcc"
            lang_flags = ["-D_LANGUAGE_C"]
        else:
            print(f"error: unsupported source type: {src}", file=sys.stderr)
            sys.exit(1)

        cmd = [compiler] + cflags + cppflags + lang_flags + [str(src), "-o", str(obj)]
        print(f"  CC {src}")
        result = subprocess.run(cmd)
        if result.returncode != 0:
            sys.exit(result.returncode)

        objects.append(obj)

    return objects


def link_module(objects, syms_path, output_path):
    """Link object files into a module ELF with preserved relocations."""
    module_ld = SCRIPT_DIR / "module.ld"
    cmd = [
        f"{CROSS}ld",
        "--emit-relocs", "-nostdlib",
        "-T", str(module_ld),
        "-T", str(syms_path),
    ] + [str(o) for o in objects] + ["-o", str(output_path)]
    print(f"  LD {output_path.name}")
    result = subprocess.run(cmd)
    if result.returncode != 0:
        sys.exit(result.returncode)


def attach_to_rom(module_data, rom_path, name, dir_rom_offset, flags, debug_symbols=None):
    """Attach module data to a ROM by updating the module directory.

    If debug_symbols is provided (list from module_readelf), a debug symbol table
    is also appended after the module data.
    """
    if len(name) >= 64:
        print(f"error: module name '{name}' exceeds 63 characters", file=sys.stderr)
        sys.exit(1)

    with open(rom_path, "r+b") as f:
        rom_data = f.read()

    count = struct.unpack(">I", rom_data[dir_rom_offset + 4 : dir_rom_offset + 8])[0]
    entries_offset = dir_rom_offset + MODULE_DIR_HEADER_SIZE

    existing_slot = None
    for i in range(count):
        entry_off = entries_offset + i * MODULE_DIR_ENTRY_SIZE
        entry_name = rom_data[entry_off : entry_off + 64]
        entry_name = entry_name.split(b"\x00", 1)[0].decode("ascii")
        if entry_name == name:
            existing_slot = i
            break

    if existing_slot is not None:
        slot = existing_slot
    else:
        if count >= MODULE_DIR_CAPACITY:
            print("error: module directory is full", file=sys.stderr)
            sys.exit(1)
        slot = count
        count += 1

    rom_end = len(rom_data)
    rom_start = (rom_end + 15) & ~15
    padding = rom_start - rom_end

    with open(rom_path, "r+b") as f:
        f.seek(rom_end)
        if padding > 0:
            f.write(b"\x00" * padding)
        f.write(module_data)
        module_rom_end = rom_start + len(module_data)

        debug_rom_start = 0
        debug_rom_end = 0
        if debug_symbols:
            debug_rom_start = (module_rom_end + 15) & ~15
            debug_padding = debug_rom_start - module_rom_end
            debug_blob = build_debug_symbol_table(debug_symbols, debug_rom_start)
            f.seek(module_rom_end)
            if debug_padding > 0:
                f.write(b"\x00" * debug_padding)
            f.write(debug_blob)
            debug_rom_end = debug_rom_start + len(debug_blob)
            print(
                f"  debug symbols: ROM 0x{debug_rom_start:08X}-0x{debug_rom_end:08X} "
                f"({len(debug_blob)} bytes, {len(debug_symbols)} symbols)"
            )

        f.seek(dir_rom_offset + 4)
        f.write(struct.pack(">I", count))

        entry_off = entries_offset + slot * MODULE_DIR_ENTRY_SIZE
        f.seek(entry_off)
        name_bytes = name.encode("ascii")
        f.write(name_bytes + b"\x00" * (64 - len(name_bytes)))
        f.write(struct.pack(">IIIII", rom_start, module_rom_end, flags,
                            debug_rom_start, debug_rom_end))

    print(
        f"  attached '{name}' "
        f"(ROM 0x{rom_start:08X}-0x{module_rom_end:08X}, {len(module_data)} bytes, "
        f"slot {slot}, flags=0x{flags:X})"
    )


def module_readelf(elf_path):
    """Extract demangled function names + file:line from a module ELF.

    Returns a list of (offset, name, file_basename, line_number) sorted by offset.
    Addresses are stored as offsets from LINK_ADDR (0x80000000).
    """
    import io

    LINK_ADDR = 0x80000000
    addr2name = {}
    addr2line = {}

    process = subprocess.Popen(
        ["mips-linux-gnu-readelf", "-s", str(elf_path), "--wide", "-wL", "--demangle"],
        stdout=subprocess.PIPE,
    )
    for line in io.TextIOWrapper(process.stdout, encoding="utf-8"):
        parts = line.split()

        if len(parts) == 8 and parts[3] == "FUNC":
            addr = int(parts[1], 16)
            name = parts[-1]
            if name.startswith("dead_"):
                continue
            addr2name[addr] = name

        elif len(parts) >= 4 and parts[2].startswith("0x"):
            file_basename = parts[0]
            if not file_basename.endswith(".c") and not file_basename.endswith(".cpp"):
                continue
            line_number = int(parts[1])
            addr = int(parts[2], 0)
            addr2line[addr] = (file_basename, line_number)

    sorted_addr2name_addrs = sorted(addr2name.keys())

    symbols = []
    for addr, (file_basename, line_number) in addr2line.items():
        if addr in addr2name:
            symbols.append((addr - LINK_ADDR, addr2name[addr], file_basename, line_number))
        else:
            closest_addr = None
            for a in sorted_addr2name_addrs:
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
    return symbols


def build_debug_symbol_table(symbols, rom_base):
    """Build a debug symbol table blob in the same format as the main symbol table.

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


def load_module_json(module_dir):
    """Load module.json from a module directory, returning the parsed config."""
    json_path = Path(module_dir) / "module.json"
    if not json_path.exists():
        return {}
    with open(json_path) as f:
        return json.load(f)


def main():
    parser = argparse.ArgumentParser(description="Build and attach a Paper Mario module")
    parser.add_argument("rom", help="ROM file (.z64) to mutate")
    parser.add_argument("syms", help="Symbol file (syms.ld)")
    parser.add_argument("name", help="Module name")
    parser.add_argument("sources", nargs="+", help="Source files to compile")
    parser.add_argument("--version", default="us", help="Game version (default: us)")

    args = parser.parse_args()

    # Source files share a common parent directory (the module directory)
    module_dir = Path(args.sources[0]).parent
    config = load_module_json(module_dir)

    name = config.get("name", args.name)

    flags = 0
    if config.get("autoload", False):
        flags |= MODULE_FLAG_AUTOLOAD

    print(f"module {name}")

    syms = parse_syms(args.syms)
    dir_offset = module_directory_rom_offset(syms)

    with tempfile.TemporaryDirectory() as tmpdir:
        tmpdir = Path(tmpdir)

        objects = compile_sources(args.sources, args.version, tmpdir)

        elf_path = tmpdir / f"{name}.elf"
        link_module(objects, Path(args.syms).resolve(), elf_path)

        mod_path = tmpdir / f"{name}.module"
        elf_to_module(str(elf_path), str(mod_path))

        debug_symbols = module_readelf(elf_path)
        print(f"  {len(debug_symbols)} debug symbols extracted")

        with open(mod_path, "rb") as f:
            module_data = f.read()
        attach_to_rom(module_data, args.rom, name, dir_offset, flags, debug_symbols)

    n64crc = SCRIPT_DIR / "rom" / "n64crc"
    subprocess.run([str(n64crc), args.rom], check=True)


if __name__ == "__main__":
    main()
