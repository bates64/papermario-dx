from splat.segtypes.n64.segment import N64Segment
from splat.util import options


class N64SegPm_tex_pool(N64Segment):
    def split(self, rom_bytes):
        pass  # textures dumped from pm_map_data

    def get_linker_entries(self):
        from splat.segtypes.linker_entry import LinkerEntry

        return [
            LinkerEntry(
                self,
                [],
                options.opts.asset_path / "tex_pool.bin",
                self.get_linker_section(),
                self.get_linker_section(),
            )
        ]
