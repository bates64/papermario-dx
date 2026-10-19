import os
import shutil
from pathlib import Path
from splat.segtypes.segment import Segment
import n64img.image
from splat.util.color import unpack_color
from common import iter_in_groups
from splat.util import options
import yaml as yaml_loader

script_dir = Path(os.path.dirname(os.path.realpath(__file__)))


def parse_palette(data):
    palette = []

    for a, b in iter_in_groups(data, 2):
        palette.append(unpack_color([a, b]))

    return palette


class N64SegPm_icons(Segment):
    def split(self, rom_bytes):
        self.out_dir = options.opts.asset_path / "icon"

        with open(script_dir / "icon.yaml", "r", encoding="utf-8") as f:
            self.icons = yaml_loader.load(f.read(), Loader=yaml_loader.SafeLoader)

        # The build packs every PNG here, so files from an earlier dump must not linger.
        shutil.rmtree(self.out_dir, ignore_errors=True)

        data = rom_bytes[self.rom_start : self.rom_end]
        pos = 0
        self.files = []

        def write_img(name, img):
            out_file = self.out_dir / (name + ".png")
            os.makedirs(os.path.dirname(out_file), exist_ok=True)
            img.write(out_file)
            self.files.append(out_file)

        for _, icon in enumerate(self.icons):
            # read yaml entry
            fmt = icon[0]
            name = icon[1]
            w = int(icon[2])
            h = int(icon[3])

            if fmt == "solo" or fmt == "pair":
                img_size = w * h // 2
                img_bytes = data[pos : pos + img_size]
                pos += img_size

                pal_bytes = data[pos : pos + 32]
                pos += 32

                img = n64img.image.CI4(data=img_bytes, width=w, height=h)
                img.palette = parse_palette(pal_bytes)
                write_img(name, img)

                if fmt == "pair":
                    pal_bytes = data[pos : pos + 32]
                    pos += 32

                    img.palette = parse_palette(pal_bytes)
                    write_img(name + ".disabled", img)

            elif fmt == "rgba16":
                img_size = w * h * 2
                img_bytes = data[pos : pos + img_size]
                pos += img_size
                img = n64img.image.RGBA16(data=img_bytes, width=w, height=h)
                write_img(name, img)

    def get_linker_entries(self):
        from splat.segtypes.linker_entry import LinkerEntry

        return [
            LinkerEntry(
                self,
                [options.opts.asset_path / "icon"],
                options.opts.asset_path / "icons.bin",
                self.get_linker_section(),
                self.get_linker_section(),
            )
        ]
