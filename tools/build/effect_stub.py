#!/usr/bin/env python3
"""Writes the trampoline that reaches an effect or one of its shims.

Effects live in TLB mapped memory, so calling one goes through a stub that
loads it first, and an effect calling back into the engine goes through a shim
that jumps via a function table. Both are fixed code apart from the index, so
they are generated rather than kept as source.

    effect_stub.py load <name> <index> <out>
    effect_stub.py shim <name> <index> <out>
"""

import sys

PROLOGUE = """.include "macro.inc"

# assembler directives
.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches
.set gp=64     # allow use of 64-bit general purpose registers

.section .text, "ax"

glabel {label}
"""

# Effect entries are 0x18 bytes, shim entries one pointer.
EFFECT_TABLE_STRIDE = 0x18
SHIM_TABLE_STRIDE = 4

LOAD_BODY = """  addiu     $sp, $sp, -0x30
  sw        $a0, 0x10($sp)
  sw        $a1, 0x14($sp)
  sw        $a2, 0x18($sp)
  sw        $a3, 0x1c($sp)
  swc1      $f12, 0x20($sp)
  swc1      $f14, 0x24($sp)
  swc1      $f16, 0x28($sp)
  sw        $ra, 0x2c($sp)
  jal       load_effect
   addiu    $a0, $zero, 0x{index:X}
  lw        $a0, 0x10($sp)
  lw        $a1, 0x14($sp)
  lw        $a2, 0x18($sp)
  lw        $a3, 0x1c($sp)
  lwc1      $f12, 0x20($sp)
  lwc1      $f14, 0x24($sp)
  lwc1      $f16, 0x28($sp)
  lw        $ra, 0x2c($sp)
  addiu     $sp, $sp, 0x30
  lui       $at, %hi(gEffectTable + 0x{offset:X})
  lw        $at, %lo(gEffectTable + 0x{offset:X})($at)
  jr        $at
   nop
"""

SHIM_BODY = """  lui       $at, %hi(effectFuncs + 0x{offset:X})
  lw        $at, %lo(effectFuncs + 0x{offset:X})($at)
  jr        $at
   nop
"""


def main() -> None:
    kind, name, index, out = sys.argv[1:5]
    index = int(index)
    if kind == "load":
        text = PROLOGUE.format(label=f"fx_{name}") + LOAD_BODY.format(
            index=index, offset=index * EFFECT_TABLE_STRIDE
        )
    else:
        text = PROLOGUE.format(label=name) + SHIM_BODY.format(
            offset=index * SHIM_TABLE_STRIDE
        )
    with open(out, "w") as f:
        f.write(text)


if __name__ == "__main__":
    main()
