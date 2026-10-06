from splat.segtypes.n64.vtx import N64SegVtx


class N64SegVtx_common(N64SegVtx):
    def cache(self):
        return (*super().cache(), "plain-symbols")

    def format_sym_name(self, sym):
        return sym.name[7:]
