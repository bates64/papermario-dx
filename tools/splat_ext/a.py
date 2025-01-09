from pathlib import Path
from splat.segtypes.segment import Segment
from splat.segtypes.linker_entry import LinkerEntry
from splat.util import options
from os import getenv

class N64SegA(Segment):
    def get_linker_entries(self):
        if self.name.startswith("$"):
            name = self.name[1:]
            # env var set in flake.nix
            src_path = Path(getenv(name))
            # must copy elsewhere because /nix is read-only
            obj_path = Path(name + ".a")
        else:
            src_path = options.opts.asset_path / self.dir / (self.name + ".a")
            obj_path = src_path

        return [
            LinkerEntry(self, [src_path], obj_path, ".text", ".text"),
            LinkerEntry(self, [src_path], obj_path, ".data", ".data"),
            LinkerEntry(self, [src_path], obj_path, ".rodata", ".rodata"),
            LinkerEntry(self, [src_path], obj_path, ".bss", ".bss"),
        ]
