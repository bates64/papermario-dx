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
- mismatched or unclosed Thread/EndThread and ChildThread/EndChildThread blocks;
- BreakLoop outside a Loop;
- BreakSwitch or Case commands outside a Switch;
- constant Goto(label) commands with no matching Label(label).

TODO:
- writable destination operands
- obvious zero-divides
- nonblocking infinite loops
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
STT_OBJECT = 1
SHN_UNDEF = 0

BYTECODE_SIZE = 4
ARGC_MASK = 0xFFFF
MAX_LOOP_DEPTH = 8
MAX_SWITCH_DEPTH = 8


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
    EVT_OP_ADD = (0x27, 2)
    EVT_OP_SUB = (0x28, 2)
    EVT_OP_MUL = (0x29, 2)
    EVT_OP_DIV = (0x2A, 2)
    EVT_OP_MOD = (0x2B, 2)
    EVT_OP_ADDF = (0x2C, 2)
    EVT_OP_SUBF = (0x2D, 2)
    EVT_OP_MULF = (0x2E, 2)
    EVT_OP_DIVF = (0x2F, 2)
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
    EVT_OP_EXEC = (0x44, 1)
    EVT_OP_EXEC_GET_TID = (0x45, 2)
    EVT_OP_EXEC_WAIT = (0x46, 1)
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
    EVT_OP_92 = (0x5C, 1)
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


@dataclass(frozen=True)
class Block:
    kind: str
    start_pos: int


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


def validate_argc(symbol: Symbol, op_pos: int, opcode: Opcode, argc: int) -> None:
    if opcode == Opcode.EVT_OP_CALL:
        if argc < 1:
            raise ValidationError(f"{symbol.name}+0x{op_pos * 4:X}: EVT_OP_CALL has no function argument")
        return
    expected = opcode.argc
    if expected is None:
        raise ValidationError(
            f"{symbol.name}+0x{op_pos * 4:X}: {opcode.name} is not valid in script bytecode"
        )
    if argc != expected:
        raise ValidationError(
            f"{symbol.name}+0x{op_pos * 4:X}: {opcode.name} has argc {argc}, expected {expected}"
        )


class ScriptWalkContext:
    def __init__(self, symbol: Symbol):
        self.symbol = symbol
        self.stack: list[Block] = []
        self.labels: dict[int, int] = {}
        self.gotos: list[tuple[int, int]] = []
        self.cur_loop_depth = 0
        self.cur_switch_depth = 0

    def error_at(self, op_pos: int, message: str) -> ValidationError:
        return ValidationError(f"{self.symbol.name}+0x{op_pos * 4:X}: {message}")

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

    def exit_switch(self, op_pos: int) -> None:
        if not self.top_is("switch"):
            raise self.error_at(op_pos, "EndSwitch without matching Switch")
        self.pop()
        self.cur_switch_depth -= 1

    def check_inside_switch(self, op_pos: int, name: str) -> None:
        if not self.contains("switch"):
            raise self.error_at(op_pos, f"{name} outside Switch")

    def enter_thread(self, op_pos: int) -> None:
        self.push("thread", op_pos)

    def exit_thread(self, op_pos: int) -> None:
        if not self.top_is("thread"):
            raise self.error_at(op_pos, "EndThread without matching Thread")
        self.pop()

    def enter_child_thread(self, op_pos: int) -> None:
        self.push("child_thread", op_pos)

    def exit_child_thread(self, op_pos: int) -> None:
        if not self.top_is("child_thread"):
            raise self.error_at(op_pos, "EndChildThread without matching ChildThread")
        self.pop()


def validate_script(script: ScriptSymbol, data: bytes) -> None:
    symbol = script.symbol
    if len(data) % BYTECODE_SIZE != 0:
        raise ValidationError(f"{symbol.name}: size 0x{len(data):X} is not word-aligned")

    words = len(data) // BYTECODE_SIZE
    read_pos = 0
    end_pos = None
    ctx = ScriptWalkContext(symbol)

    while read_pos < words:
        op_pos = read_pos
        if read_pos + 2 > words:
            raise ValidationError(f"{symbol.name}+0x{op_pos * 4:X}: truncated command header")

        opcode_value = word_at(data, read_pos)
        raw_argc = unsigned_word(data, (read_pos + 1) * BYTECODE_SIZE)
        argc = raw_argc & ARGC_MASK
        line = line_from_raw_argc(raw_argc)
        read_pos += 2

        try:
            opcode = Opcode(opcode_value)
        except ValueError:
            raise ValidationError(
                f"{symbol.name}+0x{op_pos * 4:X}: unknown opcode 0x{opcode_value:X}"
                + (f" (source line {line})" if line else "")
            )
        if opcode == Opcode.EVT_OP_INTERNAL_FETCH:
            raise ValidationError(f"{symbol.name}+0x{op_pos * 4:X}: EVT_OP_INTERNAL_FETCH appears in script data")
        if read_pos + argc > words:
            raise ValidationError(
                f"{symbol.name}+0x{op_pos * 4:X}: {opcode.name} argc {argc} runs past symbol boundary"
            )

        args = [word_at(data, read_pos + i) for i in range(argc)]
        validate_argc(symbol, op_pos, opcode, argc)
        read_pos += argc

        if opcode == Opcode.EVT_OP_END:
            end_pos = read_pos
            break

        if opcode == Opcode.EVT_OP_LABEL:
            label = args[0]
            ctx.labels.setdefault(label, op_pos)
        elif opcode == Opcode.EVT_OP_GOTO:
            ctx.gotos.append((op_pos, args[0]))
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
        elif opcode in CASE_OPS or opcode == Opcode.EVT_OP_END_CASE_GROUP:
            ctx.check_inside_switch(op_pos, opcode.name)
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
        raise ValidationError(f"{symbol.name}: missing End before symbol boundary 0x{len(data):X}")

    if ctx.stack:
        block = ctx.stack[-1]
        raise ValidationError(
            f"{symbol.name}: unclosed {block.kind} block opened at +0x{block.start_pos * 4:X} "
            f"before End at +0x{(end_pos - 3) * 4:X}"
        )

    trailing_words = words - end_pos
    if trailing_words:
        raise ValidationError(
            f"{symbol.name}: {trailing_words * BYTECODE_SIZE} unreachable byte(s) after End at +0x{(end_pos - 3) * 4:X}"
        )

    for goto_pos, label in ctx.gotos:
        # Runtime accepts expressions here, but constant labels are nonnegative.
        if label >= 0 and label not in ctx.labels:
            raise ValidationError(f"{symbol.name}+0x{goto_pos * 4:X}: Goto({label}) has no matching Label")


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
