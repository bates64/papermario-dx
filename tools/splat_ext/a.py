from splat.segtypes.segment import Segment
from splat.segtypes.linker_entry import LinkerEntry
from splat.util import options


class N64SegA(Segment):
    def get_linker_entries(self):
        path = options.opts.asset_path / self.dir / (self.name + ".a")

        return [
            LinkerEntry(
                self,
                [path],
                path,
                ".",
                ".",
            ),
        ]
