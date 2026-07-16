from pathlib import Path
import sys

from splat.segtypes.segment import Segment
from splat.util import options

sys.path.append(str(Path(__file__).parent.parent / "build"))

from effect_data import effects_from_yaml


class N64SegPm_effect_loads(Segment):
    @staticmethod
    def get_dispatch_asm():
        return """.include "macro.inc"

.set noat
.set noreorder
.set gp=64

.section .text, "ax"

glabel fx_effect_dispatch
/* 00 27BDFFD0 */  addiu     $sp, $sp, -0x30
/* 04 AFA40010 */  sw        $a0, 0x10($sp)
/* 08 AFA50014 */  sw        $a1, 0x14($sp)
/* 0C AFA60018 */  sw        $a2, 0x18($sp)
/* 10 AFA7001C */  sw        $a3, 0x1C($sp)
/* 14 E7AC0020 */  swc1      $f12, 0x20($sp)
/* 18 E7AE0024 */  swc1      $f14, 0x24($sp)
/* 1C E7B00028 */  swc1      $f16, 0x28($sp)
/* 20 AFBF002C */  sw        $ra, 0x2C($sp)
/* 24 0C?????? */  jal       load_effect
/* 28 01002021 */   addu     $a0, $t0, $zero
/* 2C 8FA40010 */  lw        $a0, 0x10($sp)
/* 30 8FA50014 */  lw        $a1, 0x14($sp)
/* 34 8FA60018 */  lw        $a2, 0x18($sp)
/* 38 8FA7001C */  lw        $a3, 0x1C($sp)
/* 3C C7AC0020 */  lwc1      $f12, 0x20($sp)
/* 40 C7AE0024 */  lwc1      $f14, 0x24($sp)
/* 44 C7B00028 */  lwc1      $f16, 0x28($sp)
/* 48 8FBF002C */  lw        $ra, 0x2C($sp)
/* 4C 00400008 */  jr        $v0
/* 50 27BD0030 */   addiu    $sp, $sp, 0x30
"""

    @staticmethod
    def get_effect_asm(index, name):
        return f""".include "macro.inc"

.set noat
.set noreorder
.set gp=64

.section .text, "ax"

glabel fx_{name}
/* 00 08000000 */  j         fx_effect_dispatch
/* 04 24080000 */   addiu    $t0, $zero, 0x{index:X}
"""

    def __init__(
        self,
        rom_start,
        rom_end,
        type,
        name,
        vram_start,
        bss_size,
        args,
        yaml,
    ):
        super().__init__(
            rom_start,
            rom_end,
            type,
            name,
            vram_start,
            args=args,
            yaml=yaml,
            bss_size=bss_size,
        )

        self.effects = effects_from_yaml(options.opts.src_path / "effects.yaml")

    def effect_s_path(self, effect_name: str):
        return options.opts.build_path / "asm" / "effects" / f"{effect_name}.s"

    def write_asm(self):
        self.effect_s_path("").parent.mkdir(parents=True, exist_ok=True)

        with open(self.effect_s_path("dispatch"), "w") as f:
            f.write(self.get_dispatch_asm())

        for i, effect in enumerate(self.effects):
            if effect.empty:
                continue

            with open(self.effect_s_path(effect.name), "w") as f:
                f.write(self.get_effect_asm(i, effect.name))

    def split(self, rom_bytes):
        self.write_asm()

    def get_linker_entries(self):
        from splat.segtypes.linker_entry import LinkerEntry

        self.write_asm()

        dispatch_path = self.effect_s_path("dispatch")
        ret = [
            LinkerEntry(
                self,
                [dispatch_path],
                dispatch_path,
                ".text",
                ".text",
            )
        ]

        for effect in self.effects:
            if effect.empty:
                continue

            ret.append(
                LinkerEntry(
                    self,
                    [self.effect_s_path(effect.name)],
                    self.effect_s_path(effect.name),
                    ".text",
                    ".text",
                )
            )

        return ret

    def should_split(self) -> bool:
        return options.opts.is_mode_active(self.type)
