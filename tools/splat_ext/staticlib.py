from splat.segtypes.n64.segment import N64Segment
from splat.segtypes.linker_entry import LinkerEntry
from splat.util import options


class N64SegStaticlib(N64Segment):
    def should_scan(self):
        return False

    def should_split(self):
        return False

    def get_linker_entries(self):
        path = options.opts.asset_path / self.dir / (self.name + ".a")
        return [
            LinkerEntry(self, [path], path, ".", "."),
        ]
