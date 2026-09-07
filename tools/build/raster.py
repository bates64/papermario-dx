"""Reads PNG files and infers the N64 texture format each one encodes.

Assets describe themselves: dimensions, colour mode and palette all come from
the file, so adding a texture needs no declaration anywhere. Where a PNG could
encode more than one N64 format the pixels decide, since the narrower format is
only usable when the data actually fits it.
"""

import struct
import zlib
from pathlib import Path
from typing import List, Optional, Tuple

SIGNATURE = b"\x89PNG\r\n\x1a\n"

GRAY, RGB, INDEXED, GRAY_ALPHA, RGBA = 0, 2, 3, 4, 6
CHANNELS = {GRAY: 1, RGB: 3, INDEXED: 1, GRAY_ALPHA: 2, RGBA: 4}

def _widened(bits: int) -> frozenset:
    """The 8-bit values an N-bit channel can produce.

    Narrow channels are widened by repeating their bit pattern, so a value
    outside this set proves the image needs more than N bits.
    """
    values = set()
    for v in range(1 << bits):
        acc, filled = 0, 0
        while filled < 8:
            acc = (acc << bits) | v
            filled += bits
        values.add((acc >> (filled - 8)) & 0xFF)
    return frozenset(values)


FITS_5_BIT = _widened(5)
FITS_4_BIT = _widened(4)
FITS_3_BIT = _widened(3)
FITS_1_BIT = _widened(1)


class Png:
    def __init__(self, path: Path):
        data = path.read_bytes()
        if data[:8] != SIGNATURE:
            raise ValueError(f"{path} is not a PNG")
        self.path = path
        self.width, self.height, self.depth, self.color_type = struct.unpack(
            ">IIBB", data[16:26]
        )
        self.palette_size: Optional[int] = None
        idat = []
        offset = 8
        while offset < len(data):
            length, kind = struct.unpack(">I4s", data[offset : offset + 8])
            body = data[offset + 8 : offset + 8 + length]
            if kind == b"PLTE":
                self.palette_size = length // 3
            elif kind == b"IDAT":
                idat.append(body)
            elif kind == b"IEND":
                break
            offset += 12 + length
        self._idat = b"".join(idat)
        self._pixels: Optional[bytes] = None

    @property
    def pixels(self) -> bytes:
        """Unfiltered image bytes, channels interleaved."""
        if self._pixels is None:
            self._pixels = self._unfilter(zlib.decompress(self._idat))
        return self._pixels

    def _unfilter(self, raw: bytes) -> bytes:
        step = CHANNELS[self.color_type] * (self.depth // 8)
        stride = self.width * step
        previous = bytearray(stride)
        rows: List[bytes] = []
        offset = 0
        for _ in range(self.height):
            kind = raw[offset]
            offset += 1
            row = bytearray(raw[offset : offset + stride])
            offset += stride
            for i in range(stride):
                left = row[i - step] if i >= step else 0
                up = previous[i]
                up_left = previous[i - step] if i >= step else 0
                if kind == 1:
                    row[i] = (row[i] + left) & 0xFF
                elif kind == 2:
                    row[i] = (row[i] + up) & 0xFF
                elif kind == 3:
                    row[i] = (row[i] + ((left + up) >> 1)) & 0xFF
                elif kind == 4:
                    row[i] = (row[i] + _paeth(left, up, up_left)) & 0xFF
            rows.append(bytes(row))
            previous = row
        return b"".join(rows)

    def channel(self, index: int, of: int) -> set:
        return set(self.pixels[index::of])

    def format(self) -> str:
        """The narrowest N64 format that encodes this image without loss."""
        if self.color_type == INDEXED:
            # Index width, not palette length: a 4-bit image may carry a
            # palette padded out to 256 entries.
            return "ci4" if max(self.pixels) < 16 else "ci8"
        if self.color_type == GRAY:
            # i1 exists but is indistinguishable from a two-tone i4, so it is
            # only ever reached by an explicit override.
            return "i4" if set(self.pixels) <= FITS_4_BIT else "i8"
        if self.color_type == GRAY_ALPHA:
            intensity = self.channel(0, 2)
            alpha = self.channel(1, 2)
            if intensity <= FITS_3_BIT and alpha <= FITS_1_BIT:
                return "ia4"
            if intensity <= FITS_4_BIT and alpha <= FITS_4_BIT:
                return "ia8"
            return "ia16"
        if self.color_type == RGBA:
            colour = set(self.pixels[0::4]) | set(self.pixels[1::4]) | set(
                self.pixels[2::4]
            )
            if colour <= FITS_5_BIT and self.channel(3, 4) <= FITS_1_BIT:
                return "rgba16"
            return "rgba32"
        raise ValueError(f"{self.path}: unsupported colour type {self.color_type}")


def _paeth(a: int, b: int, c: int) -> int:
    p = a + b - c
    pa, pb, pc = abs(p - a), abs(p - b), abs(p - c)
    if pa <= pb and pa <= pc:
        return a
    return b if pb <= pc else c
