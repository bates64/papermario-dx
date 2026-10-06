from splat.segtypes.n64.gfx import N64SegGfx


class N64SegGfx_common(N64SegGfx):
    def cache(self):
        return (*super().cache(), "plain-symbols")

    def format_sym_name(self, sym):
        return sym.name[7:]
