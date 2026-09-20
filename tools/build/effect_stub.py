#!/usr/bin/env python3
"""Write resident dispatcher and entry trampolines for effect overlays.

    effect_stub.py dispatch dispatch 0 <out>
    effect_stub.py load <name> <index> <out>
"""

import sys

PROLOGUE = """.include "macro.inc"

.set noat
.set noreorder
.set gp=64

.section .text, "ax"

glabel {label}
"""

DISPATCH_BODY = """  addiu     $sp, $sp, -0x30
  sw        $a0, 0x10($sp)
  sw        $a1, 0x14($sp)
  sw        $a2, 0x18($sp)
  sw        $a3, 0x1c($sp)
  swc1      $f12, 0x20($sp)
  swc1      $f14, 0x24($sp)
  swc1      $f16, 0x28($sp)
  sw        $ra, 0x2c($sp)
  jal       load_effect
   addu     $a0, $t0, $zero
  lw        $a0, 0x10($sp)
  lw        $a1, 0x14($sp)
  lw        $a2, 0x18($sp)
  lw        $a3, 0x1c($sp)
  lwc1      $f12, 0x20($sp)
  lwc1      $f14, 0x24($sp)
  lwc1      $f16, 0x28($sp)
  lw        $ra, 0x2c($sp)
  jr        $v0
   addiu    $sp, $sp, 0x30
"""

LOAD_BODY = """  j         fx_effect_dispatch
   addiu    $t0, $zero, 0x{index:X}
"""


def main() -> None:
    kind, name, index, out = sys.argv[1:5]
    if kind == "dispatch":
        text = PROLOGUE.format(label="fx_effect_dispatch") + DISPATCH_BODY
    elif kind == "load":
        text = PROLOGUE.format(label=f"fx_{name}") + LOAD_BODY.format(
            index=int(index)
        )
    else:
        raise ValueError(f"unknown effect-stub kind: {kind}")
    with open(out, "w", encoding="utf-8") as f:
        f.write(text)


if __name__ == "__main__":
    main()
