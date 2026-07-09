#!/usr/bin/env python3
"""Validate EVT bytecode stored in MIPS ELF object files.

This is intentionally a structural validator. It trusts ELF symbol extents, not
EVT_OP_END, to bound a script. That lets it catch both missing End commands and
premature End commands with trailing unreachable bytecode/data.

Validation currently catches:
- missing End commands;
- early End commands followed by unreachable bytecode/data;
- unknown, truncated, or malformed commands;
- commands with the wrong number of arguments;
- mismatched or unclosed If/Else/EndIf blocks;
- mismatched or unclosed Loop/EndLoop blocks;
- mismatched or unclosed Switch/EndSwitch blocks;
- Loop and Switch nesting deeper than the runtime supports;
- CaseOrEq/CaseAndEq groups missing an EndCaseGroup;
- CaseOrEq and CaseAndEq mixed within the same case group;
- EndCaseGroup without an active CaseOrEq/CaseAndEq group;
- mismatched or unclosed Thread/EndThread and ChildThread/EndChildThread blocks;
- BreakLoop outside a Loop;
- BreakSwitch or Case commands outside a Switch;
- duplicate Label values within the same thread scope;
- thread scopes with more Label commands than the runtime supports;
- Label/Goto operands that are not integer constants or relocation-backed string labels;
- Goto(label) commands with no matching Label(label) in the current thread scope.
"""

from __future__ import annotations

import argparse
import re
import struct
import sys
from dataclasses import dataclass
from enum import IntEnum
from pathlib import Path
from typing import Iterable


SHT_SYMTAB = 2
SHT_REL = 9
STT_OBJECT = 1
STT_FILE = 4
SHN_UNDEF = 0
R_MIPS_32 = 2

BYTECODE_SIZE = 4
OPCODE_SHIFT = 24
ARGC_SHIFT = 16
ARGC_MASK = 0xFF
LINE_MASK = 0xFFFF
EVT_MAX_NUM_LABELS = 24
EVT_MAX_LABEL_NAME_LEN = 64
MAX_LOOP_DEPTH = 8
MAX_SWITCH_DEPTH = 8
EVT_LOCAL_VAR_CUTOFF = -20000000
EVT_LIMIT = -270000000
EVT_ARG_INT_MARKER = EVT_LIMIT - 1
EVT_ARG_FLOAT_MARKER = EVT_LIMIT - 2


class Opcode(IntEnum):
    def __new__(cls, opcode: int, argc: int | None):
        obj = int.__new__(cls, opcode)
        obj._value_ = opcode
        obj.argc = argc
        return obj

    EVT_OP_INTERNAL_FETCH = (0x00, None)
    EVT_OP_END = (0x01, 0)
    EVT_OP_RETURN = (0x02, 0)
    EVT_OP_LABEL = (0x03, 1)
    EVT_OP_GOTO = (0x04, 1)
    EVT_OP_LOOP = (0x05, 1)
    EVT_OP_END_LOOP = (0x06, 0)
    EVT_OP_BREAK_LOOP = (0x07, 0)
    EVT_OP_WAIT_FRAMES = (0x08, 1)
    EVT_OP_WAIT_SECS = (0x09, 1)
    EVT_OP_IF_EQ = (0x0A, 2)
    EVT_OP_IF_NE = (0x0B, 2)
    EVT_OP_IF_LT = (0x0C, 2)
    EVT_OP_IF_GT = (0x0D, 2)
    EVT_OP_IF_LE = (0x0E, 2)
    EVT_OP_IF_GE = (0x0F, 2)
    EVT_OP_IF_FLAG = (0x10, 2)
    EVT_OP_IF_NOT_FLAG = (0x11, 2)
    EVT_OP_ELSE = (0x12, 0)
    EVT_OP_END_IF = (0x13, 0)
    EVT_OP_SWITCH = (0x14, 1)
    EVT_OP_SWITCH_CONST = (0x15, 1)
    EVT_OP_CASE_EQ = (0x16, 1)
    EVT_OP_CASE_NE = (0x17, 1)
    EVT_OP_CASE_LT = (0x18, 1)
    EVT_OP_CASE_GT = (0x19, 1)
    EVT_OP_CASE_LE = (0x1A, 1)
    EVT_OP_CASE_GE = (0x1B, 1)
    EVT_OP_CASE_DEFAULT = (0x1C, 0)
    EVT_OP_CASE_OR_EQ = (0x1D, 1)
    EVT_OP_CASE_AND_EQ = (0x1E, 1)
    EVT_OP_CASE_FLAG = (0x1F, 1)
    EVT_OP_END_CASE_GROUP = (0x20, 0)
    EVT_OP_CASE_RANGE = (0x21, 2)
    EVT_OP_BREAK_SWITCH = (0x22, 0)
    EVT_OP_END_SWITCH = (0x23, 0)
    EVT_OP_SET = (0x24, 2)
    EVT_OP_SET_CONST = (0x25, 2)
    EVT_OP_SETF = (0x26, 2)
    EVT_OP_ADD = (0x27, None)
    EVT_OP_SUB = (0x28, None)
    EVT_OP_MUL = (0x29, None)
    EVT_OP_DIV = (0x2A, None)
    EVT_OP_MOD = (0x2B, None)
    EVT_OP_ADDF = (0x2C, None)
    EVT_OP_SUBF = (0x2D, None)
    EVT_OP_MULF = (0x2E, None)
    EVT_OP_DIVF = (0x2F, None)
    EVT_OP_USE_BUF = (0x30, 1)
    EVT_OP_BUF_READ1 = (0x31, 1)
    EVT_OP_BUF_READ2 = (0x32, 2)
    EVT_OP_BUF_READ3 = (0x33, 3)
    EVT_OP_BUF_READ4 = (0x34, 4)
    EVT_OP_BUF_PEEK = (0x35, 2)
    EVT_OP_USE_FBUF = (0x36, 1)
    EVT_OP_FBUF_READ1 = (0x37, 1)
    EVT_OP_FBUF_READ2 = (0x38, 2)
    EVT_OP_FBUF_READ3 = (0x39, 3)
    EVT_OP_FBUF_READ4 = (0x3A, 4)
    EVT_OP_FBUF_PEEK = (0x3B, 2)
    EVT_OP_USE_ARRAY = (0x3C, 1)
    EVT_OP_USE_FLAGS = (0x3D, 1)
    EVT_OP_MALLOC_ARRAY = (0x3E, 2)
    EVT_OP_BITWISE_AND = (0x3F, 2)
    EVT_OP_BITWISE_AND_CONST = (0x40, 2)
    EVT_OP_BITWISE_OR = (0x41, 2)
    EVT_OP_BITWISE_OR_CONST = (0x42, 2)
    EVT_OP_CALL = (0x43, None)
    EVT_OP_EXEC = (0x44, None)
    EVT_OP_EXEC_GET_TID = (0x45, None)
    EVT_OP_EXEC_WAIT = (0x46, None)
    EVT_OP_BIND_TRIGGER = (0x47, 5)
    EVT_OP_UNBIND = (0x48, 0)
    EVT_OP_KILL_THREAD = (0x49, 1)
    EVT_OP_JUMP = (0x4A, 1)
    EVT_OP_SET_PRIORITY = (0x4B, 1)
    EVT_OP_SET_TIMESCALE = (0x4C, 1)
    EVT_OP_SET_GROUP = (0x4D, 1)
    EVT_OP_BIND_PADLOCK = (0x4E, 6)
    EVT_OP_SUSPEND_GROUP = (0x4F, 1)
    EVT_OP_RESUME_GROUP = (0x50, 1)
    EVT_OP_SUSPEND_OTHERS = (0x51, 1)
    EVT_OP_RESUME_OTHERS = (0x52, 1)
    EVT_OP_SUSPEND_THREAD = (0x53, 1)
    EVT_OP_RESUME_THREAD = (0x54, 1)
    EVT_OP_IS_THREAD_RUNNING = (0x55, 2)
    EVT_OP_THREAD = (0x56, 0)
    EVT_OP_END_THREAD = (0x57, 0)
    EVT_OP_CHILD_THREAD = (0x58, 0)
    EVT_OP_END_CHILD_THREAD = (0x59, 0)
    EVT_OP_DEBUG_LOG = (0x5A, 1)
    EVT_OP_DEBUG_PRINT_VAR = (0x5B, 1)
    EVT_OP_EXPECT_ARGS = (0x5C, 1)
    EVT_OP_93 = (0x5D, 0)
    EVT_OP_94 = (0x5E, 0)
    EVT_OP_DEBUG_BREAKPOINT = (0x5F, 1)


IF_OPS = {
    Opcode.EVT_OP_IF_EQ,
    Opcode.EVT_OP_IF_NE,
    Opcode.EVT_OP_IF_LT,
    Opcode.EVT_OP_IF_GT,
    Opcode.EVT_OP_IF_LE,
    Opcode.EVT_OP_IF_GE,
    Opcode.EVT_OP_IF_FLAG,
    Opcode.EVT_OP_IF_NOT_FLAG,
}

CASE_OPS = {
    Opcode.EVT_OP_CASE_EQ,
    Opcode.EVT_OP_CASE_NE,
    Opcode.EVT_OP_CASE_LT,
    Opcode.EVT_OP_CASE_GT,
    Opcode.EVT_OP_CASE_LE,
    Opcode.EVT_OP_CASE_GE,
    Opcode.EVT_OP_CASE_DEFAULT,
    Opcode.EVT_OP_CASE_OR_EQ,
    Opcode.EVT_OP_CASE_AND_EQ,
    Opcode.EVT_OP_CASE_FLAG,
    Opcode.EVT_OP_CASE_RANGE,
}

CASE_GROUP_OPS = {
    Opcode.EVT_OP_CASE_OR_EQ,
    Opcode.EVT_OP_CASE_AND_EQ,
}

EXEC_MIN_ARGC = {
    Opcode.EVT_OP_EXEC: 1,
    Opcode.EVT_OP_EXEC_GET_TID: 2,
    Opcode.EVT_OP_EXEC_WAIT: 1,
}

EXEC_ARG_MARKERS = {
    EVT_ARG_INT_MARKER: "ARG_INT",
    EVT_ARG_FLOAT_MARKER: "ARG_FLOAT",
}

VARIADIC_MIN_ARGC = {
    Opcode.EVT_OP_ADD: 2,
    Opcode.EVT_OP_SUB: 2,
    Opcode.EVT_OP_MUL: 2,
    Opcode.EVT_OP_DIV: 2,
    Opcode.EVT_OP_MOD: 2,
    Opcode.EVT_OP_ADDF: 2,
    Opcode.EVT_OP_SUBF: 2,
    Opcode.EVT_OP_MULF: 2,
    Opcode.EVT_OP_DIVF: 2,
    **EXEC_MIN_ARGC,
}

VARIADIC_MAX_ARGC = {
    Opcode.EVT_OP_SUB: 3,
    Opcode.EVT_OP_DIV: 3,
    Opcode.EVT_OP_MOD: 3,
    Opcode.EVT_OP_SUBF: 3,
    Opcode.EVT_OP_DIVF: 3,
}


@dataclass(frozen=True)
class Section:
    index: int
    name: str
    type: int
    offset: int
    size: int
    entsize: int
    link: int
    info: int


@dataclass(frozen=True)
class Symbol:
    name: str
    value: int
    size: int
    info: int
    shndx: int

    @property
    def type(self) -> int:
        return self.info & 0xF


@dataclass(frozen=True)
class ScriptSymbol:
    symbol: Symbol
    section: Section
    source_path: str | None


@dataclass(frozen=True)
class Block:
    kind: str
    start_pos: int


@dataclass(frozen=True)
class CaseGroup:
    opcode: Opcode
    start_pos: int


@dataclass(frozen=True)
class LabelValue:
    kind: str
    value: int | str


@dataclass
class LabelScope:
    kind: str
    start_pos: int
    labels: dict[LabelValue, int]


@dataclass(frozen=True)
class GotoRef:
    op_pos: int
    label: LabelValue
    scope: LabelScope


@dataclass(frozen=True)
class Relocation:
    offset: int
    sym_index: int
    type: int
    symtab_index: int


class ElfError(Exception):
    pass


class ValidationError(Exception):
    pass


def stderr_supports_color() -> bool:
    return True


def error_prefix() -> str:
    if stderr_supports_color():
        return "\033[1;31merror:\033[0m"
    return "error:"


def highlight_error_message(message: str) -> str:
    if not stderr_supports_color():
        return message

    head, sep, tail = message.rpartition(": ")
    if not sep:
        return f"\033[1;31m{message}\033[0m"
    return f"{head}{sep}\033[1;31m{tail}\033[0m"


def format_cli_error(
    error: Exception, current_object: Path | None, objects: list[Path]
) -> str:
    if isinstance(error, ValidationError):
        return highlight_error_message(str(error))
    if current_object is not None:
        return highlight_error_message(f"{current_object}: {error}")
    if objects:
        return highlight_error_message(f"{', '.join(str(path) for path in objects)}: {error}")
    return highlight_error_message(str(error))


def c_string(data: bytes, offset: int) -> str:
    end = data.find(b"\0", offset)
    if end < 0:
        end = len(data)
    return data[offset:end].decode("utf-8", errors="replace")


class Elf32:
    def __init__(self, path: Path):
        self.path = path
        self.data = path.read_bytes()
        if self.data[:4] != b"\x7fELF":
            raise ElfError("not an ELF file")
        if self.data[4] != 1:
            raise ElfError("not an ELF32 file")
        if self.data[5] == 1:
            self.endian = "<"
        elif self.data[5] == 2:
            self.endian = ">"
        else:
            raise ElfError("unknown ELF endianness")

        header = struct.unpack(self.endian + "16sHHIIIIIHHHHHH", self.data[:52])
        (
            _ident,
            _type,
            _machine,
            _version,
            _entry,
            _phoff,
            self.shoff,
            _flags,
            _ehsize,
            _phentsize,
            _phnum,
            self.shentsize,
            self.shnum,
            self.shstrndx,
        ) = header

        self.sections = self._read_sections()
        self.symbols, self.symtabs = self._read_symbols()
        self.source_path = self._read_source_path()
        self.relocations = self._read_relocations()

    def _read_sections(self) -> list[Section]:
        raw_sections = []
        for i in range(self.shnum):
            off = self.shoff + i * self.shentsize
            fields = struct.unpack(self.endian + "IIIIIIIIII", self.data[off : off + 40])
            raw_sections.append(fields)

        if not (0 <= self.shstrndx < len(raw_sections)):
            raise ElfError("invalid section string table index")

        shstr = raw_sections[self.shstrndx]
        shstr_data = self.data[shstr[4] : shstr[4] + shstr[5]]
        sections = []
        for i, fields in enumerate(raw_sections):
            name_off, sh_type, _flags, _addr, sh_offset, sh_size, sh_link, sh_info, _align, sh_entsize = fields
            sections.append(
                Section(
                    index=i,
                    name=c_string(shstr_data, name_off),
                    type=sh_type,
                    offset=sh_offset,
                    size=sh_size,
                    entsize=sh_entsize,
                    link=sh_link,
                    info=sh_info,
                )
            )
        return sections

    def _read_symbols(self) -> tuple[list[Symbol], dict[int, list[Symbol]]]:
        symbols = []
        symtabs = {}
        for section in self.sections:
            if section.type != SHT_SYMTAB:
                continue
            if section.entsize == 0:
                continue
            if not (0 <= section.link < len(self.sections)):
                raise ElfError(f"invalid symbol string table for {section.name}")

            strtab = self.sections[section.link]
            strtab_data = self.data[strtab.offset : strtab.offset + strtab.size]
            count = section.size // section.entsize
            cur_symbols = []
            for i in range(count):
                off = section.offset + i * section.entsize
                st_name, st_value, st_size, st_info, _st_other, st_shndx = struct.unpack(
                    self.endian + "IIIBBH",
                    self.data[off : off + 16],
                )
                cur_symbols.append(
                    Symbol(
                        name=c_string(strtab_data, st_name),
                        value=st_value,
                        size=st_size,
                        info=st_info,
                        shndx=st_shndx,
                    )
                )
            symtabs[section.index] = cur_symbols
            symbols.extend(cur_symbols)
        return symbols, symtabs

    def _read_source_path(self) -> str | None:
        for symbol in self.symbols:
            if symbol.type == STT_FILE and symbol.name:
                return symbol.name
        return None

    def _read_relocations(self) -> dict[int, dict[int, Relocation]]:
        relocations: dict[int, dict[int, Relocation]] = {}

        for section in self.sections:
            if section.type != SHT_REL:
                continue
            if section.entsize == 0:
                continue
            if not (0 <= section.info < len(self.sections)):
                raise ElfError(f"invalid relocation target section for {section.name}")
            if section.link not in self.symtabs:
                raise ElfError(f"invalid relocation symbol table for {section.name}")

            target_relocations = relocations.setdefault(section.info, {})
            count = section.size // section.entsize
            for i in range(count):
                off = section.offset + i * section.entsize
                r_offset, r_info = struct.unpack(self.endian + "II", self.data[off : off + 8])
                relocation = Relocation(
                    offset=r_offset,
                    sym_index=r_info >> 8,
                    type=r_info & 0xFF,
                    symtab_index=section.link,
                )
                if r_offset in target_relocations:
                    raise ElfError(f"duplicate relocation at {section.name}+0x{r_offset:X}")
                target_relocations[r_offset] = relocation

        return relocations

    def section_data_for_symbol(self, symbol: Symbol) -> tuple[Section, bytes]:
        if not (0 <= symbol.shndx < len(self.sections)):
            raise ElfError(f"{symbol.name}: invalid section index {symbol.shndx}")
        section = self.sections[symbol.shndx]
        if symbol.value + symbol.size > section.size:
            raise ElfError(
                f"{symbol.name}: symbol extent 0x{symbol.value:X}+0x{symbol.size:X} "
                f"exceeds section {section.name} size 0x{section.size:X}"
            )
        start = section.offset + symbol.value
        return section, self.data[start : start + symbol.size]

    def relocation_at(self, section_index: int, offset: int) -> Relocation | None:
        return self.relocations.get(section_index, {}).get(offset)

    def symbol_for_relocation(self, relocation: Relocation) -> Symbol:
        symtab = self.symtabs.get(relocation.symtab_index)
        if symtab is None:
            raise ElfError(f"invalid symbol table index {relocation.symtab_index} for relocation")
        if not (0 <= relocation.sym_index < len(symtab)):
            raise ElfError(f"invalid relocation symbol index {relocation.sym_index}")
        return symtab[relocation.sym_index]

    def section_data(self, section_index: int) -> bytes:
        section = self.sections[section_index]
        return self.data[section.offset : section.offset + section.size]


def is_candidate_symbol(symbol: Symbol, regex: re.Pattern[str]) -> bool:
    if symbol.shndx == SHN_UNDEF:
        return False
    if symbol.type != STT_OBJECT:
        return False
    if symbol.size < BYTECODE_SIZE or symbol.size % BYTECODE_SIZE != 0:
        return False
    return bool(regex.search(symbol.name))


def signed_word(data: bytes, offset: int) -> int:
    return struct.unpack_from(">i", data, offset)[0]


def unsigned_word(data: bytes, offset: int) -> int:
    return struct.unpack_from(">I", data, offset)[0]


def word_at(data: bytes, word_index: int) -> int:
    return signed_word(data, word_index * BYTECODE_SIZE)


def opcode_from_raw_cmd(raw_cmd: int) -> int:
    return (raw_cmd >> OPCODE_SHIFT) & 0xFF


def argc_from_raw_cmd(raw_cmd: int) -> int:
    return (raw_cmd >> ARGC_SHIFT) & ARGC_MASK


def line_from_raw_cmd(raw_cmd: int) -> int:
    return raw_cmd & LINE_MASK


def is_label_initial_byte(ch: int) -> bool:
    return ch == ord("_") or ord("A") <= ch <= ord("Z") or ord("a") <= ch <= ord("z")


def is_label_byte(ch: int) -> bool:
    return is_label_initial_byte(ch) or ord("0") <= ch <= ord("9")


def read_label_name(data: bytes, offset: int) -> str | None:
    if not (0 <= offset < len(data)):
        return None
    if not is_label_initial_byte(data[offset]):
        return None

    end = min(len(data), offset + EVT_MAX_LABEL_NAME_LEN)
    chars = bytearray([data[offset]])
    for i in range(offset + 1, end):
        ch = data[i]
        if ch == 0:
            return chars.decode("ascii")
        if not is_label_byte(ch):
            return None
        chars.append(ch)
    return None


def format_label(label: LabelValue) -> str:
    if label.kind == "number":
        return str(label.value)
    return f'"{label.value}"'


def format_script_symbol(script: ScriptSymbol) -> str:
    if script.source_path:
        return f"{script.source_path}: {script.symbol.name}"
    return script.symbol.name


def format_script_site(script: ScriptSymbol, op_pos: int, line: int | None = None) -> str:
    script_pos = f"{script.symbol.name}+0x{op_pos * 4:X}"
    if script.source_path and line:
        return f"{script.source_path}:{line}: {script_pos}"
    if script.source_path:
        return f"{script.source_path}: {script_pos}"
    if line:
        return f"{script_pos} (source line {line})"
    return script_pos


def decode_label_value(
    elf: Elf32,
    script: ScriptSymbol,
    value_word_index: int,
    raw_value: int,
    raw_bits: int,
    op_pos: int,
    line: int | None,
    opname: str,
) -> LabelValue:
    relocation = elf.relocation_at(script.section.index, script.symbol.value + value_word_index * BYTECODE_SIZE)

    if relocation is not None:
        reloc_symbol = elf.symbol_for_relocation(relocation)
        if relocation.type != R_MIPS_32:
            raise ValidationError(
                f"{format_script_site(script, op_pos, line)}: {opname} uses unsupported relocation type {relocation.type}"
            )
        if reloc_symbol.shndx == SHN_UNDEF:
            raise ValidationError(
                f"{format_script_site(script, op_pos, line)}: {opname} uses unresolved string label relocation"
            )
        if not (0 <= reloc_symbol.shndx < len(elf.sections)):
            raise ElfError(f"{reloc_symbol.name}: invalid section index {reloc_symbol.shndx}")

        target_data = elf.section_data(reloc_symbol.shndx)
        label_name = read_label_name(target_data, reloc_symbol.value + raw_bits)
        if label_name is None:
            raise ValidationError(
                f"{format_script_site(script, op_pos, line)}: {opname} does not point to a valid label string"
            )
        return LabelValue("string", label_name)

    if raw_value > EVT_LOCAL_VAR_CUTOFF:
        return LabelValue("number", raw_value)

    if raw_value <= EVT_LIMIT:
        raise ValidationError(
            f"{format_script_site(script, op_pos, line)}: {opname} uses raw pointer-like value 0x{raw_bits:08X}"
        )

    raise ValidationError(
        f"{format_script_site(script, op_pos, line)}: {opname} value {raw_value} is not a constant label"
    )


def validate_argc(script: ScriptSymbol, op_pos: int, opcode: Opcode, argc: int, line: int | None) -> None:
    if opcode == Opcode.EVT_OP_CALL:
        if argc < 1:
            raise ValidationError(f"{format_script_site(script, op_pos, line)}: EVT_OP_CALL has no function argument")
        return
    if opcode in VARIADIC_MIN_ARGC:
        expected_min = VARIADIC_MIN_ARGC[opcode]
        if argc < expected_min:
            raise ValidationError(
                f"{format_script_site(script, op_pos, line)}: {opcode.name} has argc {argc}, expected at least {expected_min}"
            )
        expected_max = VARIADIC_MAX_ARGC.get(opcode)
        if expected_max is not None and argc > expected_max:
            raise ValidationError(
                f"{format_script_site(script, op_pos, line)}: {opcode.name} has argc {argc}, expected at most {expected_max}"
            )
        return
    expected = opcode.argc
    if expected is None:
        raise ValidationError(
            f"{format_script_site(script, op_pos, line)}: {opcode.name} is not valid in script bytecode"
        )
    if argc != expected:
        raise ValidationError(
            f"{format_script_site(script, op_pos, line)}: {opcode.name} has argc {argc}, expected {expected}"
        )


def validate_exec_arg_stream(
    script: ScriptSymbol,
    op_pos: int,
    opcode: Opcode,
    args: list[int],
    line: int | None,
) -> None:
    base_argc = EXEC_MIN_ARGC.get(opcode)
    if base_argc is None:
        return

    i = base_argc
    while i < len(args):
        marker_name = EXEC_ARG_MARKERS.get(args[i])
        if marker_name is None:
            i += 1
            continue

        if i + 1 >= len(args):
            raise ValidationError(
                f"{format_script_site(script, op_pos, line)}: {opcode.name} {marker_name} marker at arg {i} has no value"
            )
        i += 2


class ScriptWalkContext:
    def __init__(self, script: ScriptSymbol):
        self.script = script
        self.stack: list[Block] = []
        self.gotos: list[GotoRef] = []
        self.label_scopes: list[LabelScope] = [LabelScope("root", 0, {})]
        self.cur_loop_depth = 0
        self.cur_switch_depth = 0
        self.case_group_stack: list[CaseGroup | None] = []
        self.current_line: int | None = None

    def error_at(self, op_pos: int, message: str) -> ValidationError:
        return ValidationError(f"{format_script_site(self.script, op_pos, self.current_line)}: {message}")

    def push(self, kind: str, op_pos: int) -> None:
        self.stack.append(Block(kind, op_pos))

    def pop(self) -> Block:
        return self.stack.pop()

    def top_is(self, kind: str) -> bool:
        return bool(self.stack and self.stack[-1].kind == kind)

    def top_is_any(self, kinds: set[str]) -> bool:
        return bool(self.stack and self.stack[-1].kind in kinds)

    def contains(self, kind: str) -> bool:
        return any(block.kind == kind for block in self.stack)

    def current_label_scope(self) -> LabelScope:
        return self.label_scopes[-1]

    def enter_if(self, op_pos: int) -> None:
        self.push("if", op_pos)

    def enter_else(self, op_pos: int) -> None:
        if not self.top_is("if"):
            raise self.error_at(op_pos, "Else without matching If")
        self.stack[-1] = Block("else", self.stack[-1].start_pos)

    def exit_if(self, op_pos: int) -> None:
        if not self.top_is_any({"if", "else"}):
            raise self.error_at(op_pos, "EndIf without matching If")
        self.pop()

    def enter_loop(self, op_pos: int) -> None:
        self.cur_loop_depth += 1
        if self.cur_loop_depth > MAX_LOOP_DEPTH:
            raise self.error_at(
                op_pos,
                f"Loop nesting depth {self.cur_loop_depth} exceeds runtime limit of {MAX_LOOP_DEPTH}",
            )
        self.push("loop", op_pos)

    def exit_loop(self, op_pos: int) -> None:
        if not self.top_is("loop"):
            raise self.error_at(op_pos, "EndLoop without matching Loop")
        self.pop()
        self.cur_loop_depth -= 1

    def check_inside_loop(self, op_pos: int) -> None:
        if not self.contains("loop"):
            raise self.error_at(op_pos, "BreakLoop outside Loop")

    def enter_switch(self, op_pos: int) -> None:
        self.cur_switch_depth += 1
        if self.cur_switch_depth > MAX_SWITCH_DEPTH:
            raise self.error_at(
                op_pos,
                f"Switch nesting depth {self.cur_switch_depth} exceeds runtime limit of {MAX_SWITCH_DEPTH}",
            )
        self.push("switch", op_pos)
        self.case_group_stack.append(None)

    def exit_switch(self, op_pos: int) -> None:
        if not self.top_is("switch"):
            raise self.error_at(op_pos, "EndSwitch without matching Switch")
        self.check_no_open_case_group(op_pos, "EndSwitch")
        self.pop()
        self.case_group_stack.pop()
        self.cur_switch_depth -= 1

    def check_inside_switch(self, op_pos: int, name: str) -> None:
        if not self.contains("switch"):
            raise self.error_at(op_pos, f"{name} outside Switch")

    def active_case_group(self) -> CaseGroup | None:
        if not self.case_group_stack:
            return None
        return self.case_group_stack[-1]

    def check_no_open_case_group(self, op_pos: int, name: str) -> None:
        group = self.active_case_group()
        if group is not None:
            raise self.error_at(
                op_pos,
                f"{name} reached before EndCaseGroup for {group.opcode.name} group opened at +0x{group.start_pos * 4:X}",
            )

    def enter_case(self, op_pos: int, opcode: Opcode) -> None:
        self.check_inside_switch(op_pos, opcode.name)
        if opcode in CASE_GROUP_OPS:
            group = self.active_case_group()
            if group is None:
                self.case_group_stack[-1] = CaseGroup(opcode, op_pos)
            elif group.opcode != opcode:
                raise self.error_at(
                    op_pos,
                    f"{opcode.name} cannot continue {group.opcode.name} group opened at +0x{group.start_pos * 4:X}",
                )
        else:
            self.check_no_open_case_group(op_pos, opcode.name)

    def end_case_group(self, op_pos: int) -> None:
        self.check_inside_switch(op_pos, Opcode.EVT_OP_END_CASE_GROUP.name)
        if self.active_case_group() is None:
            raise self.error_at(op_pos, "EndCaseGroup without active CaseOrEq/CaseAndEq group")
        self.case_group_stack[-1] = None

    def enter_thread(self, op_pos: int) -> None:
        self.push("thread", op_pos)
        self.label_scopes.append(LabelScope("thread", op_pos, {}))

    def exit_thread(self, op_pos: int) -> None:
        if not self.top_is("thread"):
            raise self.error_at(op_pos, "EndThread without matching Thread")
        self.pop()
        self.label_scopes.pop()

    def enter_child_thread(self, op_pos: int) -> None:
        self.push("child_thread", op_pos)
        self.label_scopes.append(LabelScope("child_thread", op_pos, {}))

    def exit_child_thread(self, op_pos: int) -> None:
        if not self.top_is("child_thread"):
            raise self.error_at(op_pos, "EndChildThread without matching ChildThread")
        self.pop()
        self.label_scopes.pop()

    def define_label(self, op_pos: int, label: LabelValue) -> None:
        scope = self.current_label_scope()
        prev_pos = scope.labels.get(label)
        if prev_pos is not None:
            raise self.error_at(
                op_pos,
                f"duplicate Label({format_label(label)}) previously defined at +0x{prev_pos * 4:X}",
            )

        scope.labels[label] = op_pos
        if len(scope.labels) > EVT_MAX_NUM_LABELS:
            raise self.error_at(
                op_pos,
                f"Label count {len(scope.labels)} exceeds runtime limit of {EVT_MAX_NUM_LABELS} in this thread scope",
            )

    def define_goto(self, op_pos: int, label: LabelValue) -> None:
        self.gotos.append(GotoRef(op_pos, label, self.current_label_scope()))


def validate_script(elf: Elf32, script: ScriptSymbol, data: bytes) -> None:
    symbol = script.symbol
    if len(data) % BYTECODE_SIZE != 0:
        raise ValidationError(f"{format_script_symbol(script)}: size 0x{len(data):X} is not word-aligned")

    words = len(data) // BYTECODE_SIZE
    read_pos = 0
    end_pos = None
    end_op_pos = None
    ctx = ScriptWalkContext(script)
    op_lines: dict[int, int] = {}
    end_line = None

    while read_pos < words:
        op_pos = read_pos
        if read_pos + 1 > words:
            raise ValidationError(f"{format_script_site(script, op_pos)}: truncated command header")

        raw_cmd = unsigned_word(data, read_pos * BYTECODE_SIZE)
        opcode_value = opcode_from_raw_cmd(raw_cmd)
        argc = argc_from_raw_cmd(raw_cmd)
        line = line_from_raw_cmd(raw_cmd)
        ctx.current_line = line if line else None
        if line:
            op_lines[op_pos] = line
        read_pos += 1

        try:
            opcode = Opcode(opcode_value)
        except ValueError:
            raise ValidationError(
                f"{format_script_site(script, op_pos, ctx.current_line)}: unknown opcode 0x{opcode_value:X}"
            )
        if opcode == Opcode.EVT_OP_INTERNAL_FETCH:
            raise ValidationError(f"{format_script_site(script, op_pos, ctx.current_line)}: EVT_OP_INTERNAL_FETCH appears in script data")
        if read_pos + argc > words:
            raise ValidationError(
                f"{format_script_site(script, op_pos, ctx.current_line)}: {opcode.name} argc {argc} runs past symbol boundary"
            )

        arg_pos = read_pos
        args = [word_at(data, arg_pos + i) for i in range(argc)]
        raw_args = [unsigned_word(data, (arg_pos + i) * BYTECODE_SIZE) for i in range(argc)]
        validate_argc(script, op_pos, opcode, argc, ctx.current_line)
        validate_exec_arg_stream(script, op_pos, opcode, args, ctx.current_line)
        read_pos += argc

        if opcode == Opcode.EVT_OP_END:
            end_pos = read_pos
            end_op_pos = op_pos
            end_line = ctx.current_line
            break

        if opcode == Opcode.EVT_OP_LABEL:
            ctx.define_label(
                op_pos,
                decode_label_value(elf, script, arg_pos, args[0], raw_args[0], op_pos, ctx.current_line, "Label"),
            )
        elif opcode == Opcode.EVT_OP_GOTO:
            ctx.define_goto(
                op_pos,
                decode_label_value(elf, script, arg_pos, args[0], raw_args[0], op_pos, ctx.current_line, "Goto"),
            )
        elif opcode in IF_OPS:
            ctx.enter_if(op_pos)
        elif opcode == Opcode.EVT_OP_ELSE:
            ctx.enter_else(op_pos)
        elif opcode == Opcode.EVT_OP_END_IF:
            ctx.exit_if(op_pos)
        elif opcode == Opcode.EVT_OP_LOOP:
            ctx.enter_loop(op_pos)
        elif opcode == Opcode.EVT_OP_END_LOOP:
            ctx.exit_loop(op_pos)
        elif opcode == Opcode.EVT_OP_BREAK_LOOP:
            ctx.check_inside_loop(op_pos)
        elif opcode in {Opcode.EVT_OP_SWITCH, Opcode.EVT_OP_SWITCH_CONST}:
            ctx.enter_switch(op_pos)
        elif opcode in CASE_OPS:
            ctx.enter_case(op_pos, opcode)
        elif opcode == Opcode.EVT_OP_END_CASE_GROUP:
            ctx.end_case_group(op_pos)
        elif opcode == Opcode.EVT_OP_BREAK_SWITCH:
            ctx.check_inside_switch(op_pos, "BreakSwitch")
        elif opcode == Opcode.EVT_OP_END_SWITCH:
            ctx.exit_switch(op_pos)
        elif opcode == Opcode.EVT_OP_THREAD:
            ctx.enter_thread(op_pos)
        elif opcode == Opcode.EVT_OP_END_THREAD:
            ctx.exit_thread(op_pos)
        elif opcode == Opcode.EVT_OP_CHILD_THREAD:
            ctx.enter_child_thread(op_pos)
        elif opcode == Opcode.EVT_OP_END_CHILD_THREAD:
            ctx.exit_child_thread(op_pos)

    if end_pos is None:
        raise ValidationError(f"{format_script_symbol(script)}: missing End before symbol boundary 0x{len(data):X}")

    if ctx.stack:
        block = ctx.stack[-1]
        block_line = op_lines.get(block.start_pos)
        raise ValidationError(
            f"{format_script_symbol(script)}: unclosed {block.kind} block opened at +0x{block.start_pos * 4:X}"
            + (f" (source line {block_line})" if block_line else "")
            + " "
            f"before End at +0x{end_op_pos * 4:X}"
            + (f" (source line {end_line})" if end_line else "")
        )

    trailing_words = words - end_pos
    if trailing_words:
        raise ValidationError(
            f"{format_script_symbol(script)}: {trailing_words * BYTECODE_SIZE} unreachable byte(s) after End at +0x{end_op_pos * 4:X}"
            + (f" (source line {end_line})" if end_line else "")
        )

    for goto in ctx.gotos:
        if goto.label not in goto.scope.labels:
            raise ValidationError(
                f"{format_script_site(script, goto.op_pos, op_lines.get(goto.op_pos))}: "
                f"Goto({format_label(goto.label)}) has no matching Label in this thread scope"
            )


def find_scripts(elf: Elf32, regex: re.Pattern[str]) -> Iterable[ScriptSymbol]:
    for symbol in elf.symbols:
        if not is_candidate_symbol(symbol, regex):
            continue
        section, _data = elf.section_data_for_symbol(symbol)
        yield ScriptSymbol(symbol=symbol, section=section, source_path=elf.source_path)


def validate_object(path: Path, regex: re.Pattern[str]) -> int:
    elf = Elf32(path)
    checked = 0

    for script in find_scripts(elf, regex):
        _section, data = elf.section_data_for_symbol(script.symbol)
        validate_script(elf, script, data)
        checked += 1

    return checked


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("objects", nargs="*", type=Path, help="ELF object file(s) to validate")
    parser.add_argument(
        "--object-list",
        action="append",
        dest="object_lists",
        type=Path,
        default=[],
        help="text file containing one ELF object path per line",
    )
    parser.add_argument("--out", type=Path, help="stamp file to write on success")
    parser.add_argument(
        "--symbol-regex",
        default=r"(^|_)EVS_",
        help="regex selecting object symbols to treat as EvtScript bytecode",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    current_object = None
    objects = []

    try:
        regex = re.compile(args.symbol_regex)
        checked = 0
        objects = list(args.objects)

        for object_list_path in args.object_lists:
            for path in object_list_path.read_text().splitlines():
                if path:
                    objects.append(Path(path))

        if not objects:
            raise ValidationError("no object files provided")

        for current_object in objects:
            checked += validate_object(current_object, regex)

        if args.out:
            args.out.parent.mkdir(parents=True, exist_ok=True)
            args.out.write_text(f"{checked}\n")
    except (ElfError, OSError, ValidationError, re.error) as e:
        print(f"{error_prefix()} {format_cli_error(e, current_object, objects)}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
