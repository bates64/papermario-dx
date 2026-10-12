import shutil
import struct
import subprocess

# splat imports; will fail if script run directly
try:
    from splat.segtypes.segment import Segment
    from splat.segtypes.linker_entry import LinkerEntry
    from splat.util import options

    from common import ROOT, star_rod

    splat_loaded = True
except ImportError:
    splat_loaded = False


if splat_loaded:

    class N64SegPm_sbn(Segment):
        def split(self, rom_bytes):
            assert self.rom_start is not None
            (size,) = struct.unpack_from(">i", rom_bytes, self.rom_start + 4)
            if self.rom_end:
                assert size == self.rom_end - self.rom_start
            else:
                self.rom_end = self.rom_start + size

            # Star Rod reads the SBN from a file and writes <asset_path>/audio.
            shutil.rmtree(options.opts.asset_path / self.dir / self.name, ignore_errors=True)
            sbn = (options.opts.build_path / "audio_dump.sbn").resolve()
            sbn.parent.mkdir(parents=True, exist_ok=True)
            sbn.write_bytes(rom_bytes[self.rom_start : self.rom_end])
            subprocess.run(
                [star_rod(), "-DumpAudio", str(sbn), str(options.opts.asset_path.resolve())],
                cwd=ROOT,
                check=True,
            )

        def get_linker_entries(self):
            dir = options.opts.asset_path / self.dir / self.name
            out = options.opts.asset_path / self.dir / (self.name + ".sbn")

            return [
                LinkerEntry(
                    self,
                    [dir],
                    out,
                    ".data",
                    ".data",
                ),
            ]
