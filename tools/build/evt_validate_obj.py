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
- mismatched, nested, or unclosed Lerp/EndLerp blocks;
- mismatched or unclosed Switch/EndSwitch blocks;
- Loop and Switch nesting deeper than the runtime supports;
- CaseOrEq/CaseAndEq groups missing an EndCaseGroup;
- CaseOrEq and CaseAndEq mixed within the same case group;
- EndCaseGroup without an active CaseOrEq/CaseAndEq group;
- mismatched or unclosed Thread/EndThread and ChildThread/EndChildThread blocks;
- BreakLoop outside a Loop or Lerp;
- ContinueLoop outside a Loop, or inside a Lerp;
- RetryLoop outside a Loop, or inside a Lerp;
- BreakSwitch or Case commands outside a Switch;
- duplicate Label values within the same thread scope;
- thread scopes with more Label commands than the runtime supports;
- Label/Goto operands that are not integer constants or relocation-backed string labels;
- Goto(label) commands with no matching Label(label) in the current thread scope;
- misplaced, duplicated, or blocking commands inside Finally cleanup tails;
- mixed integer/Float literal bounds in IfRange/IfNotRange;
- Float literals in integer-only math commands where a float variant exists;
- literal Clamp/ClampF bounds where min > max;
- literal Lerp durations less than zero;
- memory access types that are not supported literal EVT_MEM_* values;
- Eval/Invoke/IfEval function operands that are not relocation-backed function addresses;
- PlayEffect calls whose argument counts do not match effects.yaml.
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

from effect_data import Effect, effects_from_yaml


SHT_SYMTAB = 2
SHT_REL = 9
STT_NOTYPE = 0
STT_OBJECT = 1
STT_FUNC = 2
STT_SECTION = 3
STT_FILE = 4
SHN_UNDEF = 0
R_MIPS_32 = 2

BYTECODE_SIZE = 4
EVT_OP_INTERNAL_FETCH = 0x00

MAX_ARGC = 0xFF
MAX_EVAL_ARGS = 6
MAX_NUM_LABELS = 16
MAX_LABEL_NAME_LEN = 64
MAX_LOOP_DEPTH = 8
MAX_SWITCH_DEPTH = 8

EVT_LOCAL_VAR_CUTOFF = -20000000
EVT_FIXED_CUTOFF = -220000000
EVT_FIXED_OFFSET = 230000000
EVT_FIXED_END = -240000000
EVT_LIMIT = -270000000
EVT_ARG_INT_MARKER = EVT_LIMIT - 1
EVT_ARG_FLOAT_MARKER = EVT_LIMIT - 2

EVT_MEM_U8 = 0
EVT_MEM_F32 = 6


class Opcode(IntEnum):
    # keep these values and argument counts in sync with include/evt.h
    def __new__(cls, opcode: int, argc_min: int, argc_max: int | None = None):
        obj = int.__new__(cls, opcode)
        obj._value_ = opcode
        obj.argc_min = argc_min
        if argc_max is None:
            obj.argc_max = argc_min
        else:
            obj.argc_max = argc_max
        obj.is_variadic = obj.argc_min != obj.argc_max
        return obj

    EVT_OP_END = (0x01, 0)
    EVT_OP_RETURN = (0x02, 0)
    EVT_OP_LABEL = (0x03, 1)
    EVT_OP_GOTO = (0x04, 1)
    EVT_OP_LOOP = (0x05, 1)
    EVT_OP_END_LOOP = (0x06, 0)
    EVT_OP_BREAK_LOOP = (0x07, 0)
    EVT_OP_CONTINUE_LOOP = (0x08, 0)
    EVT_OP_RETRY_LOOP = (0x09, 0)
    EVT_OP_WAIT_FRAMES = (0x0A, 1)
    EVT_OP_WAIT_SECS = (0x0B, 1)
    EVT_OP_IF_EQ = (0x0C, 2)
    EVT_OP_IF_NE = (0x0D, 2)
    EVT_OP_IF_LT = (0x0E, 2)
    EVT_OP_IF_GT = (0x0F, 2)
    EVT_OP_IF_LE = (0x10, 2)
    EVT_OP_IF_GE = (0x11, 2)
    EVT_OP_IF_RANGE = (0x12, 3)
    EVT_OP_IF_NOT_RANGE = (0x13, 3)
    EVT_OP_IF_FLAG = (0x14, 2)
    EVT_OP_IF_NOT_FLAG = (0x15, 2)
    EVT_OP_ELSE = (0x16, 0)
    EVT_OP_END_IF = (0x17, 0)
    EVT_OP_SWITCH = (0x18, 1)
    EVT_OP_SWITCH_CONST = (0x19, 1)
    EVT_OP_CASE_EQ = (0x1A, 1)
    EVT_OP_CASE_NE = (0x1B, 1)
    EVT_OP_CASE_LT = (0x1C, 1)
    EVT_OP_CASE_GT = (0x1D, 1)
    EVT_OP_CASE_LE = (0x1E, 1)
    EVT_OP_CASE_GE = (0x1F, 1)
    EVT_OP_CASE_DEFAULT = (0x20, 0)
    EVT_OP_CASE_OR_EQ = (0x21, 1)
    EVT_OP_CASE_AND_EQ = (0x22, 1)
    EVT_OP_CASE_FLAG = (0x23, 1)
    EVT_OP_END_CASE_GROUP = (0x24, 0)
    EVT_OP_CASE_RANGE = (0x25, 2)
    EVT_OP_BREAK_SWITCH = (0x26, 0)
    EVT_OP_END_SWITCH = (0x27, 0)
    EVT_OP_SET = (0x28, 2)
    EVT_OP_SET_CONST = (0x29, 2)
    EVT_OP_SETF = (0x2A, 2)
    EVT_OP_ADD = (0x2B, 2, MAX_ARGC)
    EVT_OP_SUB = (0x2C, 2, 3)
    EVT_OP_MUL = (0x2D, 2, MAX_ARGC)
    EVT_OP_DIV = (0x2E, 2, 3)
    EVT_OP_MOD = (0x2F, 2, 3)
    EVT_OP_ADDF = (0x30, 2, MAX_ARGC)
    EVT_OP_SUBF = (0x31, 2, 3)
    EVT_OP_MULF = (0x32, 2, MAX_ARGC)
    EVT_OP_DIVF = (0x33, 2, 3)
    EVT_OP_NEG = (0x34, 1, 2)
    EVT_OP_NEGF = (0x35, 1, 2)
    EVT_OP_ABS = (0x36, 1, 2)
    EVT_OP_ABSF = (0x37, 1, 2)
    EVT_OP_SIGN = (0x38, 1, 2)
    EVT_OP_SIGNF = (0x39, 1, 2)
    EVT_OP_MIN = (0x3A, 2, MAX_ARGC)
    EVT_OP_MINF = (0x3B, 2, MAX_ARGC)
    EVT_OP_MAX = (0x3C, 2, MAX_ARGC)
    EVT_OP_MAXF = (0x3D, 2, MAX_ARGC)
    EVT_OP_CLAMP = (0x3E, 3, 4)
    EVT_OP_CLAMPF = (0x3F, 3, 4)
    EVT_OP_USE_BUF = (0x40, 1)
    EVT_OP_BUF_READ = (0x41, 1, MAX_ARGC)
    EVT_OP_BUF_PEEK = (0x42, 2)
    EVT_OP_USE_FBUF = (0x43, 1)
    EVT_OP_FBUF_READ = (0x44, 1, MAX_ARGC)
    EVT_OP_FBUF_PEEK = (0x45, 2)
    EVT_OP_MEM_GET = (0x46, 4)
    EVT_OP_MEM_SET = (0x47, 4)
    EVT_OP_USE_ARRAY = (0x48, 1)
    EVT_OP_USE_FLAGS = (0x49, 1)
    EVT_OP_MALLOC_ARRAY = (0x4A, 2)
    EVT_OP_BITWISE_AND = (0x4B, 2)
    EVT_OP_BITWISE_AND_CONST = (0x4C, 2)
    EVT_OP_BITWISE_OR = (0x4D, 2)
    EVT_OP_BITWISE_OR_CONST = (0x4E, 2)
    EVT_OP_CALL = (0x4F, 1, MAX_ARGC)
    EVT_OP_EXEC = (0x50, 1, MAX_ARGC)
    EVT_OP_EXEC_GET_ID = (0x51, 2, MAX_ARGC)
    EVT_OP_EXEC_WAIT = (0x52, 1, MAX_ARGC)
    EVT_OP_BIND_TRIGGER = (0x53, 5)
    EVT_OP_UNBIND = (0x54, 0)
    EVT_OP_KILL_SCRIPT = (0x55, 1)
    EVT_OP_JUMP = (0x56, 1)
    EVT_OP_SET_PRIORITY = (0x57, 1)
    EVT_OP_SET_TIMESCALE = (0x58, 1)
    EVT_OP_SET_GROUP = (0x59, 1)
    EVT_OP_BIND_ITEM_PROMPT = (0x5A, 6)
    EVT_OP_SUSPEND_GROUP = (0x5B, 1)
    EVT_OP_RESUME_GROUP = (0x5C, 1)
    EVT_OP_SUSPEND_OTHERS = (0x5D, 1)
    EVT_OP_RESUME_OTHERS = (0x5E, 1)
    EVT_OP_SUSPEND_SCRIPT = (0x5F, 1)
    EVT_OP_RESUME_SCRIPT = (0x60, 1)
    EVT_OP_IS_SCRIPT_RUNNING = (0x61, 2)
    EVT_OP_THREAD = (0x62, 0)
    EVT_OP_END_THREAD = (0x63, 0)
    EVT_OP_CHILD_THREAD = (0x64, 0)
    EVT_OP_END_CHILD_THREAD = (0x65, 0)
    EVT_OP_AWAIT_CHILDREN = (0x66, 0)
    EVT_OP_AWAIT_SCRIPT = (0x67, 1)
    EVT_OP_DEBUG_PRINT_VAR = (0x68, 1)
    EVT_OP_DEBUG_BREAKPOINT = (0x69, 1)
    EVT_OP_EXPECT_ARGS = (0x6A, 1)
    EVT_OP_FINALLY = (0x6B, 0)
    EVT_OP_EVAL = (0x6C, 2, 2 + MAX_EVAL_ARGS)
    EVT_OP_EVALF = (0x6D, 2, 2 + MAX_EVAL_ARGS)
    EVT_OP_INVOKE = (0x6E, 1, 1 + MAX_EVAL_ARGS)
    EVT_OP_INVOKEF = (0x6F, 1, 1 + MAX_EVAL_ARGS)
    EVT_OP_IF_EVAL = (0x70, 1, 1 + MAX_EVAL_ARGS)
    EVT_OP_IF_NOT_EVAL = (0x71, 1, 1 + MAX_EVAL_ARGS)
    EVT_OP_IF_EVALF = (0x72, 1, 1 + MAX_EVAL_ARGS)
    EVT_OP_IF_NOT_EVALF = (0x73, 1, 1 + MAX_EVAL_ARGS)
    EVT_OP_LERP = (0x74, 5)
    EVT_OP_END_LERP = (0x75, 0)


IF_OPS = {
    Opcode.EVT_OP_IF_EQ,
    Opcode.EVT_OP_IF_NE,
    Opcode.EVT_OP_IF_LT,
    Opcode.EVT_OP_IF_GT,
    Opcode.EVT_OP_IF_LE,
    Opcode.EVT_OP_IF_GE,
    Opcode.EVT_OP_IF_RANGE,
    Opcode.EVT_OP_IF_NOT_RANGE,
    Opcode.EVT_OP_IF_FLAG,
    Opcode.EVT_OP_IF_NOT_FLAG,
    Opcode.EVT_OP_IF_EVAL,
    Opcode.EVT_OP_IF_NOT_EVAL,
    Opcode.EVT_OP_IF_EVALF,
    Opcode.EVT_OP_IF_NOT_EVALF,
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

FINALLY_FORBIDDEN_OPS = {
    Opcode.EVT_OP_RETURN,
    Opcode.EVT_OP_LABEL,
    Opcode.EVT_OP_GOTO,
    Opcode.EVT_OP_LOOP,
    Opcode.EVT_OP_END_LOOP,
    Opcode.EVT_OP_BREAK_LOOP,
    Opcode.EVT_OP_CONTINUE_LOOP,
    Opcode.EVT_OP_RETRY_LOOP,
    Opcode.EVT_OP_LERP,
    Opcode.EVT_OP_END_LERP,
    Opcode.EVT_OP_WAIT_FRAMES,
    Opcode.EVT_OP_WAIT_SECS,
    Opcode.EVT_OP_EXEC_WAIT,
    Opcode.EVT_OP_AWAIT_CHILDREN,
    Opcode.EVT_OP_AWAIT_SCRIPT,
    Opcode.EVT_OP_DEBUG_BREAKPOINT,
    Opcode.EVT_OP_JUMP,
    Opcode.EVT_OP_THREAD,
    Opcode.EVT_OP_CHILD_THREAD,
}

FINALLY_COMMAND_NAME_OVERRIDES = {
    Opcode.EVT_OP_WAIT_FRAMES: "Wait",
    Opcode.EVT_OP_WAIT_SECS: "WaitSecs",
    Opcode.EVT_OP_DEBUG_BREAKPOINT: "BreakPoint",
}

EXEC_OPS = {
    Opcode.EVT_OP_EXEC,
    Opcode.EVT_OP_EXEC_GET_ID,
    Opcode.EVT_OP_EXEC_WAIT,
}

EXEC_ARG_MARKERS = {
    EVT_ARG_INT_MARKER: "ARG_INT",
    EVT_ARG_FLOAT_MARKER: "ARG_FLOAT",
}

RANGE_IF_OPS = {
    Opcode.EVT_OP_IF_RANGE,
    Opcode.EVT_OP_IF_NOT_RANGE,
}

INTEGER_MATH_FLOAT_VARIANT = {
    Opcode.EVT_OP_NEG: "NegF",
    Opcode.EVT_OP_ABS: "AbsF",
    Opcode.EVT_OP_SIGN: "SignF",
    Opcode.EVT_OP_MIN: "MinF",
    Opcode.EVT_OP_MAX: "MaxF",
    Opcode.EVT_OP_CLAMP: "ClampF",
}

CLAMP_OPS = {
    Opcode.EVT_OP_CLAMP,
    Opcode.EVT_OP_CLAMPF,
}

FUNCTION_ARG_INDEX_BY_OP = {
    Opcode.EVT_OP_EVAL: 1,
    Opcode.EVT_OP_EVALF: 1,
    Opcode.EVT_OP_INVOKE: 0,
    Opcode.EVT_OP_INVOKEF: 0,
    Opcode.EVT_OP_IF_EVAL: 0,
    Opcode.EVT_OP_IF_NOT_EVAL: 0,
    Opcode.EVT_OP_IF_EVALF: 0,
    Opcode.EVT_OP_IF_NOT_EVALF: 0,
}


def command_display_name(opcode: Opcode) -> str:
    override = FINALLY_COMMAND_NAME_OVERRIDES.get(opcode)
    if override is not None:
        return override
    return "".join(part.capitalize() for part in opcode.name.removeprefix("EVT_OP_").split("_"))


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
    stack_base: int
    labels: dict[LabelValue, int]
    case_group_stack: list[CaseGroup | None]
    finally_pos: int | None = None


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
    return sys.stderr.isatty()


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
    return (raw_cmd >> 24) & 0xFF


def argc_from_raw_cmd(raw_cmd: int) -> int:
    return (raw_cmd >> 16) & 0xFF


def line_from_raw_cmd(raw_cmd: int) -> int:
    return raw_cmd & 0xFFFF


def is_label_initial_byte(ch: int) -> bool:
    return ch == ord("_") or ord("A") <= ch <= ord("Z") or ord("a") <= ch <= ord("z")


def is_label_byte(ch: int) -> bool:
    return is_label_initial_byte(ch) or ord("0") <= ch <= ord("9")


def read_label_name(data: bytes, offset: int) -> str | None:
    if not (0 <= offset < len(data)):
        return None
    if not is_label_initial_byte(data[offset]):
        return None

    end = min(len(data), offset + MAX_LABEL_NAME_LEN)
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

    if not opcode.is_variadic:
        if argc != opcode.argc_min:
            raise ValidationError(
                f"{format_script_site(script, op_pos, line)}: {opcode.name} has argc {argc}, expected {opcode.argc_min}"
            )
        return

    if argc < opcode.argc_min:
        raise ValidationError(
            f"{format_script_site(script, op_pos, line)}: {opcode.name} has argc {argc}, expected at least {opcode.argc_min}"
        )

    if argc > opcode.argc_max:
        raise ValidationError(
            f"{format_script_site(script, op_pos, line)}: {opcode.name} has argc {argc}, expected at most {opcode.argc_max}"
        )


def validate_exec_arg_stream(
    script: ScriptSymbol,
    op_pos: int,
    opcode: Opcode,
    args: list[int],
    line: int | None,
) -> None:
    if opcode not in EXEC_OPS:
        return

    i = opcode.argc_min
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


def is_fixed_literal(value: int) -> bool:
    return EVT_FIXED_END <= value <= EVT_FIXED_CUTOFF


def is_plain_int_literal(value: int) -> bool:
    return value > EVT_LOCAL_VAR_CUTOFF


def is_encoded_evt_expression(value: int) -> bool:
    return EVT_LIMIT < value <= EVT_LOCAL_VAR_CUTOFF


def literal_as_float(value: int) -> float | None:
    if is_fixed_literal(value):
        return (value + EVT_FIXED_OFFSET) / 1024.0
    if is_plain_int_literal(value):
        return float(value)
    return None


def validate_range_bound_types(
    script: ScriptSymbol,
    op_pos: int,
    opcode: Opcode,
    args: list[int],
    line: int | None,
) -> None:
    if opcode not in RANGE_IF_OPS:
        return

    min_value = args[1]
    max_value = args[2]
    min_is_float = is_fixed_literal(min_value)
    max_is_float = is_fixed_literal(max_value)
    if min_is_float == max_is_float:
        return

    # Variable-backed bounds may hold either int-shaped or fixed-point values at runtime.
    min_is_dynamic = is_encoded_evt_expression(min_value) and not min_is_float
    max_is_dynamic = is_encoded_evt_expression(max_value) and not max_is_float
    if min_is_dynamic or max_is_dynamic:
        return

    raise ValidationError(
        f"{format_script_site(script, op_pos, line)}: {opcode.name} min/max bounds mix "
        "Float and integer literals"
    )


def validate_integer_math_arg_types(
    script: ScriptSymbol,
    op_pos: int,
    opcode: Opcode,
    args: list[int],
    line: int | None,
) -> None:
    float_variant = INTEGER_MATH_FLOAT_VARIANT.get(opcode)
    if float_variant is None:
        return

    for i, value in enumerate(args[1:], start=1):
        if is_fixed_literal(value):
            raise ValidationError(
                f"{format_script_site(script, op_pos, line)}: {opcode.name} arg {i} uses "
                f"Float literal; use {float_variant}"
            )


def validate_clamp_literal_bounds(
    script: ScriptSymbol,
    op_pos: int,
    opcode: Opcode,
    args: list[int],
    line: int | None,
) -> None:
    if opcode not in CLAMP_OPS:
        return

    if len(args) == 3:
        min_index = 1
        max_index = 2
    else:
        min_index = 2
        max_index = 3

    min_value = literal_as_float(args[min_index])
    max_value = literal_as_float(args[max_index])
    if min_value is None or max_value is None:
        return

    if min_value > max_value:
        raise ValidationError(
            f"{format_script_site(script, op_pos, line)}: {opcode.name} min bound is greater than max bound"
        )


def validate_lerp_duration(
    script: ScriptSymbol,
    op_pos: int,
    opcode: Opcode,
    args: list[int],
    line: int | None,
) -> None:
    if opcode != Opcode.EVT_OP_LERP:
        return

    duration = literal_as_float(args[3])
    if duration is None:
        return

    if duration < 0:
        raise ValidationError(
            f"{format_script_site(script, op_pos, line)}: Lerp duration must be >= 0"
        )


def validate_mem_type(
    elf: Elf32,
    script: ScriptSymbol,
    op_pos: int,
    arg_pos: int,
    args: list[int],
    opcode: Opcode,
    line: int | None,
) -> None:
    if opcode not in {Opcode.EVT_OP_MEM_GET, Opcode.EVT_OP_MEM_SET}:
        return

    type_arg_index = 0
    relocation = elf.relocation_at(
        script.section.index,
        script.symbol.value + (arg_pos + type_arg_index) * BYTECODE_SIZE,
    )
    if relocation is not None:
        raise ValidationError(
            f"{format_script_site(script, op_pos, line)}: {opcode.name} memory type must be "
            "a literal EVT_MEM_* value"
        )

    mem_type = args[type_arg_index]
    if EVT_MEM_U8 <= mem_type <= EVT_MEM_F32:
        return
    if is_encoded_evt_expression(mem_type):
        raise ValidationError(
            f"{format_script_site(script, op_pos, line)}: {opcode.name} memory type is an EVT expression; "
            "expected a literal EVT_MEM_* value"
        )
    raise ValidationError(
        f"{format_script_site(script, op_pos, line)}: {opcode.name} has unknown memory type {mem_type}; "
        "expected EVT_MEM_U8 through EVT_MEM_F32"
    )


def validate_function_arg(
    elf: Elf32,
    script: ScriptSymbol,
    op_pos: int,
    arg_pos: int,
    raw_args: list[int],
    opcode: Opcode,
    line: int | None,
) -> None:
    func_arg_index = FUNCTION_ARG_INDEX_BY_OP.get(opcode)
    if func_arg_index is None:
        return

    relocation = elf.relocation_at(
        script.section.index,
        script.symbol.value + (arg_pos + func_arg_index) * BYTECODE_SIZE,
    )
    if relocation is None:
        raise ValidationError(
            f"{format_script_site(script, op_pos, line)}: {opcode.name} function argument at arg "
            f"{func_arg_index} is not relocation-backed"
        )
    if relocation.type != R_MIPS_32:
        raise ValidationError(
            f"{format_script_site(script, op_pos, line)}: {opcode.name} function argument uses unsupported "
            f"relocation type {relocation.type}"
        )

    reloc_symbol = elf.symbol_for_relocation(relocation)
    if reloc_symbol.type == STT_SECTION:
        target_value = reloc_symbol.value + raw_args[func_arg_index]
        for symbol in elf.symbols:
            if symbol.type != STT_FUNC or symbol.shndx != reloc_symbol.shndx:
                continue
            if symbol.value <= target_value < symbol.value + symbol.size:
                return
        raise ValidationError(
            f"{format_script_site(script, op_pos, line)}: {opcode.name} function argument points to "
            f"non-function location in {reloc_symbol.name}"
        )

    if reloc_symbol.type not in {STT_NOTYPE, STT_FUNC}:
        raise ValidationError(
            f"{format_script_site(script, op_pos, line)}: {opcode.name} function argument points to "
            f"non-function symbol {reloc_symbol.name}"
        )


def validate_play_effect(
    elf: Elf32,
    effects: list[Effect] | None,
    script: ScriptSymbol,
    op_pos: int,
    arg_pos: int,
    args: list[int],
    opcode: Opcode,
    line: int | None,
) -> None:
    if effects is None or opcode != Opcode.EVT_OP_CALL or not args:
        return

    function_relocation = elf.relocation_at(
        script.section.index,
        script.symbol.value + arg_pos * BYTECODE_SIZE,
    )
    if function_relocation is None or function_relocation.type != R_MIPS_32:
        return
    function_symbol = elf.symbol_for_relocation(function_relocation)
    if function_symbol.name != "PlayEffect_impl":
        return

    if len(args) < 2:
        raise ValidationError(
            f"{format_script_site(script, op_pos, line)}: PlayEffect has no effect ID"
        )

    effect_arg_pos = arg_pos + 1
    effect_relocation = elf.relocation_at(
        script.section.index,
        script.symbol.value + effect_arg_pos * BYTECODE_SIZE,
    )
    effect_index = args[1]
    if effect_relocation is not None or not is_plain_int_literal(effect_index):
        raise ValidationError(
            f"{format_script_site(script, op_pos, line)}: PlayEffect effect ID must be a literal EFFECT_* value"
        )
    if not 0 <= effect_index < len(effects):
        raise ValidationError(
            f"{format_script_site(script, op_pos, line)}: PlayEffect has invalid effect ID 0x{effect_index:X}"
        )

    effect = effects[effect_index]
    if effect.empty:
        raise ValidationError(
            f"{format_script_site(script, op_pos, line)}: PlayEffect cannot use empty effect ID 0x{effect_index:X}"
        )

    actual_arg_count = len(args) - 2
    if actual_arg_count != effect.arg_count:
        raise ValidationError(
            f"{format_script_site(script, op_pos, line)}: PlayEffect({effect.enum_name}) has "
            f"argc {actual_arg_count}, expected {effect.arg_count}"
        )


class ScriptWalkContext:
    def __init__(self, script: ScriptSymbol):
        self.script = script
        self.stack: list[Block] = []
        self.gotos: list[GotoRef] = []
        self.label_scopes: list[LabelScope] = [LabelScope("root", 0, 0, {}, [])]
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

    def current_label_scope(self) -> LabelScope:
        return self.label_scopes[-1]

    def current_scope_blocks(self) -> list[Block]:
        return self.stack[self.current_label_scope().stack_base:]

    def contains(self, kind: str) -> bool:
        return any(block.kind == kind for block in self.current_scope_blocks())

    def scope_is_at_top_level(self, scope: LabelScope) -> bool:
        return len(self.stack) == scope.stack_base

    def enter_finally(self, op_pos: int) -> None:
        scope = self.current_label_scope()
        if scope.finally_pos is not None:
            raise self.error_at(
                op_pos,
                f"duplicate Finally in {scope.kind} scope; previous Finally at +0x{scope.finally_pos * 4:X}",
            )
        if not self.scope_is_at_top_level(scope):
            raise self.error_at(op_pos, "Finally must be top-level in its script or thread scope")
        scope.finally_pos = op_pos

    def check_finally_command_allowed(self, op_pos: int, opcode: Opcode) -> None:
        scope = self.current_label_scope()
        if scope.finally_pos is None or opcode == Opcode.EVT_OP_FINALLY:
            return
        if opcode == Opcode.EVT_OP_RETURN:
            raise self.error_at(op_pos, "Return is not allowed inside Finally; use the terminator command")
        if opcode in FINALLY_FORBIDDEN_OPS:
            raise self.error_at(op_pos, f"{command_display_name(opcode)} is not allowed inside Finally")

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

    def enter_loop_like(self, op_pos: int, kind: str, command: str) -> None:
        loop_depth = sum(block.kind in {"loop", "lerp"} for block in self.current_scope_blocks()) + 1
        if loop_depth > MAX_LOOP_DEPTH:
            raise self.error_at(
                op_pos,
                f"{command} nesting depth {loop_depth} exceeds runtime limit of {MAX_LOOP_DEPTH}",
            )
        self.push(kind, op_pos)

    def enter_loop(self, op_pos: int) -> None:
        self.enter_loop_like(op_pos, "loop", "Loop")

    def exit_loop(self, op_pos: int) -> None:
        if not self.top_is("loop"):
            raise self.error_at(op_pos, "EndLoop without matching Loop")
        self.pop()

    def enter_lerp(self, op_pos: int) -> None:
        if self.contains("lerp"):
            raise self.error_at(op_pos, "nested Lerp is not allowed")
        self.enter_loop_like(op_pos, "lerp", "Lerp")

    def exit_lerp(self, op_pos: int) -> None:
        if not self.top_is("lerp"):
            raise self.error_at(op_pos, "EndLerp without matching Lerp")
        self.pop()

    def nearest_loop_kind(self) -> str | None:
        for block in reversed(self.current_scope_blocks()):
            if block.kind in {"loop", "lerp"}:
                return block.kind
        return None

    def check_break_loop(self, op_pos: int) -> None:
        if self.nearest_loop_kind() is None:
            raise self.error_at(op_pos, "BreakLoop outside Loop or Lerp")

    def check_continue_loop(self, op_pos: int) -> None:
        nearest_loop = self.nearest_loop_kind()
        if nearest_loop is None:
            raise self.error_at(op_pos, "ContinueLoop outside Loop")
        if nearest_loop == "lerp":
            raise self.error_at(op_pos, "ContinueLoop is not allowed inside Lerp")

    def check_retry_loop(self, op_pos: int) -> None:
        nearest_loop = self.nearest_loop_kind()
        if nearest_loop is None:
            raise self.error_at(op_pos, "RetryLoop outside Loop")
        if nearest_loop == "lerp":
            raise self.error_at(op_pos, "RetryLoop is not allowed inside Lerp")

    def enter_switch(self, op_pos: int) -> None:
        switch_depth = sum(block.kind == "switch" for block in self.current_scope_blocks()) + 1
        if switch_depth > MAX_SWITCH_DEPTH:
            raise self.error_at(
                op_pos,
                f"Switch nesting depth {switch_depth} exceeds runtime limit of {MAX_SWITCH_DEPTH}",
            )
        self.push("switch", op_pos)
        self.current_label_scope().case_group_stack.append(None)

    def exit_switch(self, op_pos: int) -> None:
        if not self.top_is("switch"):
            raise self.error_at(op_pos, "EndSwitch without matching Switch")
        self.check_no_open_case_group(op_pos, "EndSwitch")
        self.pop()
        self.current_label_scope().case_group_stack.pop()

    def check_inside_switch(self, op_pos: int, name: str) -> None:
        if not self.contains("switch"):
            raise self.error_at(op_pos, f"{name} outside Switch")

    def active_case_group(self) -> CaseGroup | None:
        case_group_stack = self.current_label_scope().case_group_stack
        if not case_group_stack:
            return None
        return case_group_stack[-1]

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
                self.current_label_scope().case_group_stack[-1] = CaseGroup(opcode, op_pos)
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
        self.current_label_scope().case_group_stack[-1] = None

    def enter_thread(self, op_pos: int) -> None:
        self.push("thread", op_pos)
        self.label_scopes.append(LabelScope("thread", op_pos, len(self.stack), {}, []))

    def exit_thread(self, op_pos: int) -> None:
        if not self.top_is("thread"):
            raise self.error_at(op_pos, "EndThread without matching Thread")
        self.pop()
        self.label_scopes.pop()

    def enter_child_thread(self, op_pos: int) -> None:
        self.push("child_thread", op_pos)
        self.label_scopes.append(LabelScope("child_thread", op_pos, len(self.stack), {}, []))

    def exit_child_thread(self, op_pos: int) -> None:
        if not self.top_is("child_thread"):
            raise self.error_at(op_pos, "EndChildThread without matching ChildThread")
        self.pop()
        self.label_scopes.pop()

    def define_label(self, op_pos: int, label: LabelValue) -> None:
        scope = self.current_label_scope()
        prev = scope.labels.get(label)
        if prev is not None:
            raise self.error_at(
                op_pos,
                f"duplicate Label({format_label(label)}) previously defined at +0x{prev * 4:X}",
            )

        scope.labels[label] = op_pos
        if len(scope.labels) > MAX_NUM_LABELS:
            raise self.error_at(
                op_pos,
                f"Label count {len(scope.labels)} exceeds runtime limit of {MAX_NUM_LABELS} in this thread scope",
            )

    def define_goto(self, op_pos: int, label: LabelValue) -> None:
        self.gotos.append(GotoRef(op_pos, label, self.current_label_scope()))


def validate_script(
    elf: Elf32,
    effects: list[Effect] | None,
    script: ScriptSymbol,
    data: bytes,
) -> None:
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

        if opcode_value == EVT_OP_INTERNAL_FETCH:
            raise ValidationError(f"{format_script_site(script, op_pos, ctx.current_line)}: EVT_OP_INTERNAL_FETCH appears in script data")
        try:
            opcode = Opcode(opcode_value)
        except ValueError:
            raise ValidationError(
                f"{format_script_site(script, op_pos, ctx.current_line)}: unknown opcode 0x{opcode_value:X}"
            )
        if read_pos + argc > words:
            raise ValidationError(
                f"{format_script_site(script, op_pos, ctx.current_line)}: {opcode.name} argc {argc} runs past symbol boundary"
            )

        arg_pos = read_pos
        args = [word_at(data, arg_pos + i) for i in range(argc)]
        raw_args = [unsigned_word(data, (arg_pos + i) * BYTECODE_SIZE) for i in range(argc)]
        validate_argc(script, op_pos, opcode, argc, ctx.current_line)
        validate_exec_arg_stream(script, op_pos, opcode, args, ctx.current_line)
        validate_range_bound_types(script, op_pos, opcode, args, ctx.current_line)
        validate_integer_math_arg_types(script, op_pos, opcode, args, ctx.current_line)
        validate_clamp_literal_bounds(script, op_pos, opcode, args, ctx.current_line)
        validate_lerp_duration(script, op_pos, opcode, args, ctx.current_line)
        validate_mem_type(elf, script, op_pos, arg_pos, args, opcode, ctx.current_line)
        validate_function_arg(elf, script, op_pos, arg_pos, raw_args, opcode, ctx.current_line)
        validate_play_effect(elf, effects, script, op_pos, arg_pos, args, opcode, ctx.current_line)
        read_pos += argc

        ctx.check_finally_command_allowed(op_pos, opcode)

        if opcode == Opcode.EVT_OP_END:
            end_pos = read_pos
            end_op_pos = op_pos
            end_line = ctx.current_line
            break

        if opcode == Opcode.EVT_OP_FINALLY:
            ctx.enter_finally(op_pos)
        elif opcode == Opcode.EVT_OP_LABEL:
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
        elif opcode == Opcode.EVT_OP_LERP:
            ctx.enter_lerp(op_pos)
        elif opcode == Opcode.EVT_OP_END_LERP:
            ctx.exit_lerp(op_pos)
        elif opcode == Opcode.EVT_OP_BREAK_LOOP:
            ctx.check_break_loop(op_pos)
        elif opcode == Opcode.EVT_OP_CONTINUE_LOOP:
            ctx.check_continue_loop(op_pos)
        elif opcode == Opcode.EVT_OP_RETRY_LOOP:
            ctx.check_retry_loop(op_pos)
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


def validate_object(path: Path, regex: re.Pattern[str], effects: list[Effect] | None) -> int:
    elf = Elf32(path)
    checked = 0

    for script in find_scripts(elf, regex):
        _section, data = elf.section_data_for_symbol(script.symbol)
        validate_script(elf, effects, script, data)
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
        "--effects-yaml",
        type=Path,
        help="effects.yaml used to validate PlayEffect argument counts",
    )
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
        effects = effects_from_yaml(args.effects_yaml) if args.effects_yaml else None
        checked = 0
        objects = list(args.objects)

        for object_list_path in args.object_lists:
            for path in object_list_path.read_text().splitlines():
                if path:
                    objects.append(Path(path))

        if not objects:
            raise ValidationError("no object files provided")

        for current_object in objects:
            checked += validate_object(current_object, regex, effects)

        if args.out:
            args.out.parent.mkdir(parents=True, exist_ok=True)
            args.out.write_text(f"{checked}\n")
    except (ElfError, OSError, ValidationError, re.error) as e:
        print(f"{error_prefix()} {format_cli_error(e, current_object, objects)}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
