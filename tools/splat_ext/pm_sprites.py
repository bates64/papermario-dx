#! /usr/bin/env python3
"""splat's sprite segment. The tables it reads live with the build tools."""

import sys
from pathlib import Path

from splat.segtypes.segment import Segment
from splat.util import options

sys.path.insert(0, str(Path(__file__).parent.parent / "build" / "sprite"))
from tables import *  # noqa: F401,F403
from tables import (  # noqa: F401
    NPC_SPRITE_MEDADATA_XML_FILENAME,
    PLAYER_SPRITE_MEDADATA_XML_FILENAME,
    NpcSprite,
    PlayerSprite,
)

class N64SegPm_sprites(Segment):
    DEFAULT_NPC_SPRITE_NAMES = [f"{i:02X}" for i in range(0xEA)]

    def __init__(self, rom_start, rom_end, type, name, vram_start, args, yaml) -> None:
        super().__init__(rom_start, rom_end, type, name, vram_start, args=args, yaml=yaml)

        path = Path(__file__).parent / f"npc_sprite_names.yaml"
        with path.open("r", encoding="utf-8") as f:
            self.npc_cfg = yaml_loader.load(f.read(), Loader=yaml_loader.SafeLoader)
        self.npc_cfg_modified_time = path.stat().st_mtime

        path = Path(__file__).parent / f"player_sprite_names.yaml"
        with path.open("r", encoding="utf-8") as f:
            self.player_cfg = yaml_loader.load(f.read(), Loader=yaml_loader.SafeLoader)
        self.player_cfg_modified_time = path.stat().st_mtime

    def out_path(self):
        return options.opts.asset_path / "sprite" / "sprites"

    def split_player(self, build_date: str, player_raster_data: bytes, player_yay0_data: bytes) -> None:
        player_sprite_cfg = self.player_cfg["player_sprites"]
        player_raster_names: List[str] = self.player_cfg["player_rasters"]

        player_sprite_names = []
        for sprite_name in player_sprite_cfg.keys():
            player_sprite_names.append(sprite_name)
            if player_sprite_cfg[sprite_name].get("has_back", False):
                player_sprite_names.append(sprite_name)

        # Header parsing
        index_ranges_offset = int.from_bytes(player_raster_data[0:0x4], "big")
        raster_info_offset = int.from_bytes(player_raster_data[0x4:0x8], "big")
        ci4_raster_data_offset = int.from_bytes(player_raster_data[0x8:0xC], "big")

        index_ranges = player_raster_data[index_ranges_offset:raster_info_offset]
        raster_info = player_raster_data[raster_info_offset:ci4_raster_data_offset]
        # ci4_raster_data = player_raster_data[ci4_raster_data_offset:]

        # Parse raster sets (readSpriteSections)
        raster_sets: List[PlayerSpriteRasterSet] = []
        for i in range(0, len(index_ranges) - 4, 4):
            start = int.from_bytes(index_ranges[i : i + 4], "big")
            end = int.from_bytes(index_ranges[i + 4 : i + 8], "big")
            raster_sets.append(PlayerSpriteRasterSet(start, end - start))

        raster_table_entry_dict = extract_raster_table_entries(raster_info, raster_sets)

        player_sprites = extract_sprites(player_yay0_data, raster_sets)

        #########
        # Writing
        #########

        player_out_path = self.out_path().parent / "player"

        player_out_path.mkdir(parents=True, exist_ok=True)
        write_player_metadata(
            self.out_path().parent,
            player_sprite_cfg,
            player_raster_names,
            build_date,
        )
        write_player_xmls(
            player_out_path,
            player_sprite_cfg,
            player_sprites,
            player_sprite_names,
            raster_sets,
            raster_table_entry_dict,
            player_raster_names,
        )
        write_player_rasters(
            player_out_path,
            raster_table_entry_dict,
            player_raster_data,
            player_raster_names,
        )
        write_player_palettes(
            player_out_path,
            player_sprite_cfg,
            player_sprites,
            player_sprite_names,
            raster_table_entry_dict,
            player_raster_data,
        )

    def split_npc(self, data: bytes) -> None:
        out_dir = self.out_path().parent / "npc"

        write_npc_metadata(
            self.out_path().parent,
            self.npc_cfg,
        )

        for i, sprite_name in enumerate(self.npc_cfg):
            sprite_dir = out_dir / sprite_name
            sprite_dir.mkdir(parents=True, exist_ok=True)

            start = int.from_bytes(data[i * 4 : (i + 1) * 4], byteorder="big")
            end = int.from_bytes(data[(i + 1) * 4 : (i + 2) * 4], byteorder="big")

            sprite_data = crunch64.yay0.decompress(data[start:end])
            sprite = NpcSprite.from_bytes(sprite_data)

            sprite.image_names = self.npc_cfg[sprite_name].get("frames", [])
            sprite.palette_names = self.npc_cfg[sprite_name].get("palettes", [])
            sprite.animation_names = self.npc_cfg[sprite_name].get("animations", [])
            sprite.variation_names = self.npc_cfg[sprite_name].get("variations", [])

            sprite.write_to_dir(sprite_dir)

    def split(self, rom_bytes) -> None:
        sprite_in_bytes = rom_bytes[self.rom_start : self.rom_end]
        build_date = sprite_in_bytes[0:0x10].decode("ascii").rstrip("\0")
        player_raster_offset = int.from_bytes(sprite_in_bytes[0x10:0x14], "big") + 0x10
        player_yay0_offset = int.from_bytes(sprite_in_bytes[0x14:0x18], "big") + 0x10
        npc_yay0_offset = int.from_bytes(sprite_in_bytes[0x18:0x1C], "big") + 0x10
        sprite_end_offset = int.from_bytes(sprite_in_bytes[0x1C:0x20], "big") + 0x10

        player_raster_data: bytes = sprite_in_bytes[player_raster_offset:player_yay0_offset]
        player_yay0_data: bytes = sprite_in_bytes[player_yay0_offset:npc_yay0_offset]
        npc_yay0_data: bytes = sprite_in_bytes[npc_yay0_offset:sprite_end_offset]

        self.split_player(build_date, player_raster_data, player_yay0_data)
        self.split_npc(npc_yay0_data)

    def get_linker_entries(self):
        from splat.segtypes.linker_entry import LinkerEntry
        import splat.scripts.split as split

        src_paths = [options.opts.asset_path / "sprite"]

        # read npc.xml - we can't use self.npc_cfg because nonvanilla asset packs can change it
        # for each sprite, add to src_paths
        asset_stack = tuple(Path(p) for p in split.config["asset_stack"])
        orderings_tree = ET.parse(get_asset_path(Path("sprite") / NPC_SPRITE_MEDADATA_XML_FILENAME, asset_stack))
        for sprite_tag in orderings_tree.getroot()[0]:
            name = sprite_tag.attrib["name"]
            src_paths.append(options.opts.asset_path / "sprite" / "npc" / name)

        return [LinkerEntry(self, src_paths, self.out_path(), self.get_linker_section(), self.get_linker_section())]

    def cache(self):
        return (self.yaml, self.rom_end, self.player_cfg_modified_time, self.npc_cfg_modified_time)
