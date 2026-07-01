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
- mismatched or unclosed Thread/EndThread and ChildThread/EndChildThread blocks;
- BreakLoop outside a Loop;
- BreakSwitch or Case commands outside a Switch;
- constant Goto(label) commands with no matching Label(label).

TODO:
- opcode and argument counts
- matching If/Switch/Loop structures
- valid labels
- nesting limits
- writable destination operands
- obvious zero-divides
- nonblocking infinite loops
- malformed script termination
"""

from __future__ import annotations

import argparse
import re
import struct
import sys
from dataclasses import dataclass
from pathlib import Path
from typing import Iterable


SHT_SYMTAB = 2
STT_OBJECT = 1
SHN_UNDEF = 0

BYTECODE_SIZE = 4
ARGC_MASK = 0xFFFF


OPCODES = {
    0: "EVT_OP_INTERNAL_FETCH",
    1: "EVT_OP_END",
    2: "EVT_OP_RETURN",
    3: "EVT_OP_LABEL",
    4: "EVT_OP_GOTO",
    5: "EVT_OP_LOOP",
    6: "EVT_OP_END_LOOP",
    7: "EVT_OP_BREAK_LOOP",
    8: "EVT_OP_WAIT_FRAMES",
    9: "EVT_OP_WAIT_SECS",
    10: "EVT_OP_IF_EQ",
    11: "EVT_OP_IF_NE",
    12: "EVT_OP_IF_LT",
    13: "EVT_OP_IF_GT",
    14: "EVT_OP_IF_LE",
    15: "EVT_OP_IF_GE",
    16: "EVT_OP_IF_FLAG",
    17: "EVT_OP_IF_NOT_FLAG",
    18: "EVT_OP_ELSE",
    19: "EVT_OP_END_IF",
    20: "EVT_OP_SWITCH",
    21: "EVT_OP_SWITCH_CONST",
    22: "EVT_OP_CASE_EQ",
    23: "EVT_OP_CASE_NE",
    24: "EVT_OP_CASE_LT",
    25: "EVT_OP_CASE_GT",
    26: "EVT_OP_CASE_LE",
    27: "EVT_OP_CASE_GE",
    28: "EVT_OP_CASE_DEFAULT",
    29: "EVT_OP_CASE_OR_EQ",
    30: "EVT_OP_CASE_AND_EQ",
    31: "EVT_OP_CASE_FLAG",
    32: "EVT_OP_END_CASE_GROUP",
    33: "EVT_OP_CASE_RANGE",
    34: "EVT_OP_BREAK_SWITCH",
    35: "EVT_OP_END_SWITCH",
    36: "EVT_OP_SET",
    37: "EVT_OP_SET_CONST",
    38: "EVT_OP_SETF",
    39: "EVT_OP_ADD",
    40: "EVT_OP_SUB",
    41: "EVT_OP_MUL",
    42: "EVT_OP_DIV",
    43: "EVT_OP_MOD",
    44: "EVT_OP_ADDF",
    45: "EVT_OP_SUBF",
    46: "EVT_OP_MULF",
    47: "EVT_OP_DIVF",
    48: "EVT_OP_USE_BUF",
    49: "EVT_OP_BUF_READ1",
    50: "EVT_OP_BUF_READ2",
    51: "EVT_OP_BUF_READ3",
    52: "EVT_OP_BUF_READ4",
    53: "EVT_OP_BUF_PEEK",
    54: "EVT_OP_USE_FBUF",
    55: "EVT_OP_FBUF_READ1",
    56: "EVT_OP_FBUF_READ2",
    57: "EVT_OP_FBUF_READ3",
    58: "EVT_OP_FBUF_READ4",
    59: "EVT_OP_FBUF_PEEK",
    60: "EVT_OP_USE_ARRAY",
    61: "EVT_OP_USE_FLAGS",
    62: "EVT_OP_MALLOC_ARRAY",
    63: "EVT_OP_BITWISE_AND",
    64: "EVT_OP_BITWISE_AND_CONST",
    65: "EVT_OP_BITWISE_OR",
    66: "EVT_OP_BITWISE_OR_CONST",
    67: "EVT_OP_CALL",
    68: "EVT_OP_EXEC",
    69: "EVT_OP_EXEC_GET_TID",
    70: "EVT_OP_EXEC_WAIT",
    71: "EVT_OP_BIND_TRIGGER",
    72: "EVT_OP_UNBIND",
    73: "EVT_OP_KILL_THREAD",
    74: "EVT_OP_JUMP",
    75: "EVT_OP_SET_PRIORITY",
    76: "EVT_OP_SET_TIMESCALE",
    77: "EVT_OP_SET_GROUP",
    78: "EVT_OP_BIND_PADLOCK",
    79: "EVT_OP_SUSPEND_GROUP",
    80: "EVT_OP_RESUME_GROUP",
    81: "EVT_OP_SUSPEND_OTHERS",
    82: "EVT_OP_RESUME_OTHERS",
    83: "EVT_OP_SUSPEND_THREAD",
    84: "EVT_OP_RESUME_THREAD",
    85: "EVT_OP_IS_THREAD_RUNNING",
    86: "EVT_OP_THREAD",
    87: "EVT_OP_END_THREAD",
    88: "EVT_OP_CHILD_THREAD",
    89: "EVT_OP_END_CHILD_THREAD",
    90: "EVT_OP_DEBUG_LOG",
    91: "EVT_OP_DEBUG_PRINT_VAR",
    92: "EVT_OP_92",
    93: "EVT_OP_93",
    94: "EVT_OP_94",
    95: "EVT_OP_DEBUG_BREAKPOINT",
}


FIXED_ARGC = {
    1: 0,
    2: 0,
    3: 1,
    4: 1,
    5: 1,
    6: 0,
    7: 0,
    8: 1,
    9: 1,
    10: 2,
    11: 2,
    12: 2,
    13: 2,
    14: 2,
    15: 2,
    16: 2,
    17: 2,
    18: 0,
    19: 0,
    20: 1,
    21: 1,
    22: 1,
    23: 1,
    24: 1,
    25: 1,
    26: 1,
    27: 1,
    28: 0,
    29: 1,
    30: 1,
    31: 1,
    32: 0,
    33: 2,
    34: 0,
    35: 0,
    36: 2,
    37: 2,
    38: 2,
    39: 2,
    40: 2,
    41: 2,
    42: 2,
    43: 2,
    44: 2,
    45: 2,
    46: 2,
    47: 2,
    48: 1,
    49: 1,
    50: 2,
    51: 3,
    52: 4,
    53: 2,
    54: 1,
    55: 1,
    56: 2,
    57: 3,
    58: 4,
    59: 2,
    60: 1,
    61: 1,
    62: 2,
    63: 2,
    64: 2,
    65: 2,
    66: 2,
    # 67 EVT_OP_CALL is variadic.
    68: 1,
    69: 2,
    70: 1,
    71: 5,
    72: 0,
    73: 1,
    74: 1,
    75: 1,
    76: 1,
    77: 1,
    78: 6,
    79: 1,
    80: 1,
    81: 1,
    82: 1,
    83: 1,
    84: 1,
    85: 2,
    86: 0,
    87: 0,
    88: 0,
    89: 0,
    90: 1,
    91: 1,
    92: 1,
    93: 0,
    94: 0,
    95: 1,
}


IF_OPS = set(range(10, 18))
CASE_OPS = {22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 33}


@dataclass(frozen=True)
class Section:
    name: str
    type: int
    offset: int
    size: int
    entsize: int
    link: int


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


class ElfError(Exception):
    pass


class ValidationError(Exception):
    pass


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
        self.symbols = self._read_symbols()

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
        for fields in raw_sections:
            name_off, sh_type, _flags, _addr, sh_offset, sh_size, sh_link, _info, _align, sh_entsize = fields
            sections.append(
                Section(
                    name=c_string(shstr_data, name_off),
                    type=sh_type,
                    offset=sh_offset,
                    size=sh_size,
                    entsize=sh_entsize,
                    link=sh_link,
                )
            )
        return sections

    def _read_symbols(self) -> list[Symbol]:
        symbols = []
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
            for i in range(count):
                off = section.offset + i * section.entsize
                st_name, st_value, st_size, st_info, _st_other, st_shndx = struct.unpack(
                    self.endian + "IIIBBH",
                    self.data[off : off + 16],
                )
                symbols.append(
                    Symbol(
                        name=c_string(strtab_data, st_name),
                        value=st_value,
                        size=st_size,
                        info=st_info,
                        shndx=st_shndx,
                    )
                )
        return symbols

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


def is_candidate_symbol(symbol: Symbol, regex: re.Pattern[str]) -> bool:
    if symbol.shndx == SHN_UNDEF:
        return False
    if symbol.type != STT_OBJECT:
        return False
    if symbol.size < 3 * BYTECODE_SIZE or symbol.size % BYTECODE_SIZE != 0:
        return False
    return bool(regex.search(symbol.name))


def signed_word(data: bytes, offset: int) -> int:
    return struct.unpack_from(">i", data, offset)[0]


def unsigned_word(data: bytes, offset: int) -> int:
    return struct.unpack_from(">I", data, offset)[0]


def word_at(data: bytes, word_index: int) -> int:
    return signed_word(data, word_index * BYTECODE_SIZE)


def line_from_raw_argc(raw_argc: int) -> int:
    return (raw_argc >> 16) & 0xFFFF


def validate_argc(symbol: Symbol, word_pc: int, opcode: int, argc: int) -> None:
    if opcode == 67:
        if argc < 1:
            raise ValidationError(f"{symbol.name}+0x{word_pc * 4:X}: EVT_OP_CALL has no function argument")
        return
    expected = FIXED_ARGC.get(opcode)
    if expected is None:
        raise ValidationError(
            f"{symbol.name}+0x{word_pc * 4:X}: {OPCODES.get(opcode, opcode)} is not valid in script bytecode"
        )
    if argc != expected:
        raise ValidationError(
            f"{symbol.name}+0x{word_pc * 4:X}: {OPCODES[opcode]} has argc {argc}, expected {expected}"
        )


def validate_script(script: ScriptSymbol, data: bytes) -> None:
    symbol = script.symbol
    if len(data) % BYTECODE_SIZE != 0:
        raise ValidationError(f"{symbol.name}: size 0x{len(data):X} is not word-aligned")

    words = len(data) // BYTECODE_SIZE
    pc = 0
    end_pc = None
    stack: list[tuple[str, int]] = []
    labels: dict[int, int] = {}
    gotos: list[tuple[int, int]] = []

    while pc < words:
        inst_pc = pc
        if pc + 2 > words:
            raise ValidationError(f"{symbol.name}+0x{inst_pc * 4:X}: truncated command header")

        opcode = word_at(data, pc)
        raw_argc = unsigned_word(data, (pc + 1) * BYTECODE_SIZE)
        argc = raw_argc & ARGC_MASK
        line = line_from_raw_argc(raw_argc)
        pc += 2

        if opcode not in OPCODES:
            raise ValidationError(
                f"{symbol.name}+0x{inst_pc * 4:X}: unknown opcode {opcode}"
                + (f" (source line {line})" if line else "")
            )
        if opcode == 0:
            raise ValidationError(f"{symbol.name}+0x{inst_pc * 4:X}: EVT_OP_INTERNAL_FETCH appears in script data")
        if pc + argc > words:
            raise ValidationError(
                f"{symbol.name}+0x{inst_pc * 4:X}: {OPCODES[opcode]} argc {argc} runs past symbol boundary"
            )

        args = [word_at(data, pc + i) for i in range(argc)]
        validate_argc(symbol, inst_pc, opcode, argc)
        pc += argc

        if opcode == 1:
            end_pc = pc
            break

        if opcode == 3:
            label = args[0]
            labels.setdefault(label, inst_pc)
        elif opcode == 4:
            gotos.append((inst_pc, args[0]))
        elif opcode in IF_OPS:
            stack.append(("if", inst_pc))
        elif opcode == 18:
            if not stack or stack[-1][0] != "if":
                raise ValidationError(f"{symbol.name}+0x{inst_pc * 4:X}: Else without matching If")
            stack[-1] = ("else", stack[-1][1])
        elif opcode == 19:
            if not stack or stack[-1][0] not in {"if", "else"}:
                raise ValidationError(f"{symbol.name}+0x{inst_pc * 4:X}: EndIf without matching If")
            stack.pop()
        elif opcode == 5:
            stack.append(("loop", inst_pc))
        elif opcode == 6:
            if not stack or stack[-1][0] != "loop":
                raise ValidationError(f"{symbol.name}+0x{inst_pc * 4:X}: EndLoop without matching Loop")
            stack.pop()
        elif opcode == 7:
            if not any(kind == "loop" for kind, _ in stack):
                raise ValidationError(f"{symbol.name}+0x{inst_pc * 4:X}: BreakLoop outside Loop")
        elif opcode in {20, 21}:
            stack.append(("switch", inst_pc))
        elif opcode in CASE_OPS or opcode == 32:
            if not any(kind == "switch" for kind, _ in stack):
                raise ValidationError(f"{symbol.name}+0x{inst_pc * 4:X}: {OPCODES[opcode]} outside Switch")
        elif opcode == 34:
            if not any(kind == "switch" for kind, _ in stack):
                raise ValidationError(f"{symbol.name}+0x{inst_pc * 4:X}: BreakSwitch outside Switch")
        elif opcode == 35:
            if not stack or stack[-1][0] != "switch":
                raise ValidationError(f"{symbol.name}+0x{inst_pc * 4:X}: EndSwitch without matching Switch")
            stack.pop()
        elif opcode == 86:
            stack.append(("thread", inst_pc))
        elif opcode == 87:
            if not stack or stack[-1][0] != "thread":
                raise ValidationError(f"{symbol.name}+0x{inst_pc * 4:X}: EndThread without matching Thread")
            stack.pop()
        elif opcode == 88:
            stack.append(("child_thread", inst_pc))
        elif opcode == 89:
            if not stack or stack[-1][0] != "child_thread":
                raise ValidationError(
                    f"{symbol.name}+0x{inst_pc * 4:X}: EndChildThread without matching ChildThread"
                )
            stack.pop()

    if end_pc is None:
        raise ValidationError(f"{symbol.name}: missing End before symbol boundary 0x{len(data):X}")

    if stack:
        kind, start_pc = stack[-1]
        raise ValidationError(
            f"{symbol.name}: unclosed {kind} block opened at +0x{start_pc * 4:X} before End at +0x{(end_pc - 3) * 4:X}"
        )

    trailing_words = words - end_pc
    if trailing_words:
        raise ValidationError(
            f"{symbol.name}: {trailing_words * BYTECODE_SIZE} unreachable byte(s) after End at +0x{(end_pc - 3) * 4:X}"
        )

    for goto_pc, label in gotos:
        # Runtime accepts expressions here, but constant labels are nonnegative.
        if label >= 0 and label not in labels:
            raise ValidationError(f"{symbol.name}+0x{goto_pc * 4:X}: Goto({label}) has no matching Label")


def find_scripts(elf: Elf32, regex: re.Pattern[str]) -> Iterable[ScriptSymbol]:
    for symbol in elf.symbols:
        if not is_candidate_symbol(symbol, regex):
            continue
        section, _data = elf.section_data_for_symbol(symbol)
        yield ScriptSymbol(symbol=symbol, section=section)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("object", type=Path, help="ELF object file to validate")
    parser.add_argument("--out", type=Path, help="stamp file to write on success")
    parser.add_argument(
        "--symbol-regex",
        default=r"(^|_)EVS_",
        help="regex selecting object symbols to treat as EvtScript bytecode",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    try:
        regex = re.compile(args.symbol_regex)
        elf = Elf32(args.object)
        checked = 0
        for script in find_scripts(elf, regex):
            _section, data = elf.section_data_for_symbol(script.symbol)
            validate_script(script, data)
            checked += 1
        if args.out:
            args.out.parent.mkdir(parents=True, exist_ok=True)
            args.out.write_text(f"{checked}\n")
    except (ElfError, OSError, ValidationError, re.error) as e:
        print(f"evt_validate_obj: {args.object}: {e}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
