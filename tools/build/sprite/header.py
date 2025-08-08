#!/usr/bin/env python3

from sys import argv, path
from pathlib import Path

path.append(str(Path(__file__).parent.parent))

from sprite.npc_sprite import from_dir as npc_from_dir

seen = set()
duplicate_warned = set()
def write_if_unique(f, name, value):
    """
    Write a define to the file if it is not already defined.
    Print a warning the first time a non-unique name is used (per name).
    """
    global seen, duplicate_warned
    if name in seen:
        if name not in duplicate_warned:
            print(f"warning: duplicate: {name}")
            duplicate_warned.add(name)
        return
    seen.add(name)
    f.write(f"#define {name} {value}\n")

if __name__ == "__main__":
    if len(argv) < 4:
        print("usage: header.py [OUT] [NAME] [ID]")
        exit(1)

    _, outfile, sprite_name, s_in, asset_stack_raw = argv

    asset_stack = tuple(Path(d) for d in asset_stack_raw.split(","))

    with open(outfile, "w") as f:
        # get sprite index
        s = int(s_in)
        assert s >= 1

        sprite = npc_from_dir(sprite_name, asset_stack, load_images=False)

        f.write(f"#pragma once\n")
        f.write("\n")
        f.write('#include "types.h"\n')
        f.write("\n")

        # sprite definition
        write_if_unique(f, f"SPR_{sprite_name}", f"0x{s:02X}")
        f.write("\n")

        # definitions for images
        for i, image_name in enumerate(sprite.image_names):
            image_name = image_name.replace(" ", "_")
            write_if_unique(f, f"SPR_IMG_{sprite_name}_{image_name}", f"0x{i:X}")
        f.write("\n")

        # definitions for palettes
        for p, palette_name in enumerate(sprite.palette_names):
            palette_name = palette_name.replace(" ", "_")
            if palette_name == "Default":
                write_if_unique(f, f"SPR_PAL_{sprite_name}", f"0x{p:X}")
            else:
                write_if_unique(f, f"SPR_PAL_{sprite_name}_{palette_name}", f"0x{p:X}")
        f.write("\n")

        # definitions for animations
        for p, palette_name in enumerate(sprite.palette_names):
            palette_name = palette_name.replace(" ", "_")
            for a, name in enumerate(sprite.animation_names):
                name = name.replace(" ", "_")
                if palette_name == "Default":
                    write_if_unique(f, f"ANIM_{sprite_name}_{name}", f"0x{s:02X}{p:02X}{a:02X}")
                else:
                    write_if_unique(f, f"ANIM_{sprite_name}_{palette_name}_{name}", f"0x{s:02X}{p:02X}{a:02X}")
            f.write("\n")
