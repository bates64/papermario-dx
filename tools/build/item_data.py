#!/usr/bin/env python3

import re
import sys
import yaml
import argparse
from pathlib import Path
from typing import Dict, List, Tuple
from common import get_asset_path
import xml.etree.ElementTree as ET
from io import TextIOWrapper


class ItemEntry:
    hudElemID: int  # assigned later
    itemEntID: int  # assigned later

    def __init__(self, entry):
        self.name = list(entry.keys())[0]
        data = entry[self.name]

        self.nameMsg = data.get("nameMsg", "MSG_NONE")
        self.fullDescMsg = data.get("fullDescMsg", "MSG_NONE")
        self.shortDescMsg = data.get("shortDescMsg", "MSG_NONE")
        self.hudElementTemplate = data.get("hudElementTemplate", "MISSING_TEMPLATE")
        self.itemEntityTemplate = data.get("itemEntityTemplate", "MISSING_TEMPLATE")
        self.skipScriptArg = data.get("noArgScripts", False)
        self.icon = data.get("icon", "key/Gift")
        self.sellValue = data.get("sellValue", -1)
        self.sortValue = data.get("sortValue", 0)
        self.targetFlags = data.get("targetFlags", [])
        self.typeFlags = data.get("typeFlags", [])
        self.moveID = data.get("moveID", "MOVE_NONE")
        self.potencyA = data.get("potencyA", 0)
        self.potencyB = data.get("potencyB", 0)

        self.icon = re.sub("\\W", "_", self.icon)


def read_items_yaml(in_yaml: Path) -> List[ItemEntry]:
    items: List[ItemEntry] = []

    with open(in_yaml) as f:
        entry_list = yaml.load(f.read(), Loader=yaml.SafeLoader)

        for entry in entry_list:
            items.append(ItemEntry(entry))

    return items


def read_icons_xml(asset_stack: Tuple[Path, ...]) -> Dict[str, bool]:
    pair_map: Dict[str, bool] = {}

    xml = ET.parse(get_asset_path(Path("icon/Icons.xml"), asset_stack))
    IconList = xml.getroot()

    for Icon in IconList.findall("Icon"):
        type = Icon.attrib["type"]
        name = Icon.attrib["name"]

        if name is None:
            raise Exception("Icon is missing attribute: 'name'")

        if type is None:
            raise Exception("Icon is missing attribute: 'type'")

        name = re.sub("\\W", "_", name)
        pair_map[name] = type == "pair"

    return pair_map


def generate_item_table(fout: TextIOWrapper, items: List[ItemEntry]):
    fout.write("ItemData gItemTable[] = {\n")

    def join_flags(flags: List[str]) -> str:
        if len(flags) > 0:
            joined = " | ".join(flags)
        else:
            joined = "0"
        return joined

    for idx, item in enumerate(items):
        fout.write(f"    {{   // 0x{idx:03X}: {item.name}\n")
        fout.write(f"        .nameMsg = {item.nameMsg},\n")
        fout.write(f"        .fullDescMsg = {item.fullDescMsg},\n")
        fout.write(f"        .shortDescMsg = {item.shortDescMsg},\n")
        fout.write(f"        .hudElemID = {item.hudElemID},\n")
        fout.write(f"        .sellValue = {item.sellValue},\n")
        fout.write(f"        .sortValue = {item.sortValue},\n")
        fout.write(f"        .targetFlags = {join_flags(item.targetFlags)},\n")
        fout.write(f"        .typeFlags = {join_flags(item.typeFlags)},\n")
        fout.write(f"        .moveID = {item.moveID},\n")
        fout.write(f"        .potencyA = {item.potencyA},\n")
        fout.write(f"        .potencyB = {item.potencyB},\n")
        fout.write(f"    }},\n")

    fout.write("};\n")
    fout.write("\n")


def generate_item_enum(fout: TextIOWrapper, items: List[ItemEntry]):
    fout.write("#ifndef ITEM_ENUM_H\n")
    fout.write("#define ITEM_ENUM_H\n")
    fout.write("\n")

    fout.write("enum ItemIDs {\n")

    item_enum: List[str] = []

    for idx, item in enumerate(items):
        # FireFlower     -> FIRE_FLOWER
        # POWBlock       -> POW_BLOCK
        # MagicalSeed1   -> MAGICAL_SEED1
        # UnusedLetter_4 -> UNUSED_LETTER_4
        # etc
        name = "ITEM_" + re.sub("((?<=[a-z0-9])[A-Z]|(?!^)(?<!_)[A-Z](?=[a-z]))", r"_\1", item.name).upper()
        item_enum.append(name)
        fout.write(f"    {name:39} = 0x{idx:03X},\n")

    fout.write("};\n")
    fout.write("\n")

    nconsumables = 0
    nbadges = 0
    nkeys = 0

    first_consumable = -1

    for idx, item in enumerate(items):
        if ("ITEM_TYPE_FLAG_CONSUMABLE") in item.typeFlags:
            nconsumables += 1
            if first_consumable == -1:
                first_consumable = idx
        if ("ITEM_TYPE_FLAG_BADGE") in item.typeFlags:
            nbadges += 1
        if ("ITEM_TYPE_FLAG_KEY") in item.typeFlags:
            nkeys += 1

    fout.write(f"#define NUM_ITEMS {len(items)}\n")
    fout.write(f"#define ITEM_NUM_CONSUMABLES {nconsumables}\n")
    fout.write(f"#define ITEM_NUM_BADGES {nbadges}\n")
    fout.write(f"#define ITEM_NUM_KEYS {nkeys}\n")
    fout.write(f"#define ITEM_FIRST_CONSUMABLE {first_consumable}\n")
    fout.write("\n")

    fout.write("#endif // ITEM_ENUM_H\n")


class HudScriptEntry:
    def __init__(self, full_name: str, template: str, icon: str, pair: bool, index: int, skipArg: bool):
        self.full_name = full_name
        self.template = template
        self.icon = icon
        self.pair = pair
        self.index = index
        self.skipArg = skipArg


def snake_to_pascal(s: str) -> str:
    return s.replace("_", " ").title().replace(" ", "")


def generate_hud_element_scripts(fout: TextIOWrapper, items: List[ItemEntry], pair_map: Dict[str, bool]):
    hud_scripts: List[HudScriptEntry] = []
    hud_script_map: Dict[str, HudScriptEntry] = {}

    # determine a set of hud scripts to generate consisting of each unique pair of template + icon
    # and then assign the index of the generated scripts to each of the items using that pair
    for item in items:
        if item.skipScriptArg:
            template_name = snake_to_pascal(item.hudElementTemplate.lower())
            script_name = f"HES_{template_name}"
        else:
            icon_name = snake_to_pascal(item.icon)
            template_name = snake_to_pascal(item.hudElementTemplate.lower())
            script_name = f"HES_{template_name}_{icon_name}"

        if not script_name in hud_script_map:
            if not item.icon in pair_map:
                raise Exception(f"Item {item.name} requires undefined icon: {item.icon}")

            cur_script = HudScriptEntry(
                script_name,
                item.hudElementTemplate,
                item.icon,
                pair_map[item.icon],
                1 + len(hud_scripts),
                item.skipScriptArg,
            )
            hud_scripts.append(cur_script)
            hud_script_map[script_name] = cur_script
            item.hudElemID = cur_script.index
        else:
            cur_script = hud_script_map[script_name]
            item.hudElemID = cur_script.index

    # write the hud script bodies
    for script in hud_scripts:
        script_arg = "" if script.skipArg else script.icon
        fout.write(f"HudScript {script.full_name} = HES_TEMPLATE_{script.template}({script_arg});\n")

        if script.pair:
            script_arg = "" if script.skipArg else script.icon + "_disabled"
            fout.write(f"HudScript {script.full_name}_disabled = HES_TEMPLATE_{script.template}({script_arg});\n")

    fout.write("\n")

    # write the hud script table
    fout.write("IconHudScriptPair gItemHudScripts[] = {\n")
    fout.write("    { .enabled = NULL, .disabled = NULL },\n")  # array index 0 is always NULL

    for script in hud_scripts:
        if script.pair:
            fout.write(f"    {{ .enabled = &{script.full_name}, .disabled = &{script.full_name}_disabled }},\n")
        else:
            fout.write(f"    {{ .enabled = &{script.full_name}, .disabled = &{script.full_name} }},\n")

    fout.write("};\n")
    fout.write("\n")


class ItemScriptEntry:
    def __init__(self, full_name: str, template: str, icon: str, index: int, skipArg: bool):
        self.full_name = full_name
        self.template = template
        self.icon = icon
        self.index = index
        self.skipArg = skipArg


def generate_item_entity_scripts(fout: TextIOWrapper, items: List[ItemEntry]):
    item_scripts: List[ItemScriptEntry] = []
    item_script_map: Dict[str, ItemScriptEntry] = {}

    # determine a set of items scripts to generate consisting of each unique pair of template + icon
    # and then assign the index of the generated scripts to each of the items using that pair
    for item in items:
        if item.skipScriptArg:
            template_name = snake_to_pascal(item.itemEntityTemplate.lower())
            script_name = f"IES_{template_name}"
        else:
            icon_name = snake_to_pascal(item.icon)
            template_name = snake_to_pascal(item.itemEntityTemplate.lower())
            script_name = f"IES_{template_name}_{icon_name}"

        if not script_name in item_script_map:
            cur_script = ItemScriptEntry(
                script_name, item.itemEntityTemplate, item.icon, len(item_scripts), item.skipScriptArg
            )
            item_scripts.append(cur_script)
            item_script_map[script_name] = cur_script
            item.itemEntID = cur_script.index
        else:
            cur_script = item_script_map[script_name]
            item.itemEntID = cur_script.index

    # write the item entity script bodies
    for script in item_scripts:
        script_arg = "" if script.skipArg else script.icon
        fout.write(f"ItemScript {script.full_name} = IES_TEMPLATE_{script.template}({script_arg});\n")

    fout.write("\n")

    # write the item script table
    fout.write("// indexed by itemID\n")
    fout.write("s32* gItemEntityScripts[] = {\n")
    for item in items:
        script = item_scripts[item.itemEntID]
        fout.write(f"    {script.full_name},\n")
    fout.write("};\n")
    fout.write("\n")


def generate_item_icon_tables(fout: TextIOWrapper, items: List[ItemEntry]):
    fout.write("// indexed by itemID\n")
    fout.write("s32 gItemIconRasterOffsets[] = {\n")
    for item in items:
        fout.write(f"    ICON_{item.icon}_raster,\n")
    fout.write("};\n")
    fout.write("\n")

    fout.write("// indexed by itemID\n")
    fout.write("s32 gItemIconPaletteOffsets[] = {\n")
    for item in items:
        fout.write(f"    ICON_{item.icon}_palette,\n")
    fout.write("};\n")
    fout.write("\n")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generates item table")
    parser.add_argument("out_data", help="output header file to generate containing the data")
    parser.add_argument("out_enum", help="output header file to generate containing the enum")
    parser.add_argument("items_yaml", type=Path, help="input yaml file path")
    parser.add_argument("asset_stack", help="comma-separated asset stack")
    args = parser.parse_args()

    asset_stack = tuple(Path(d) for d in args.asset_stack.split(","))

    items = read_items_yaml(args.items_yaml)
    icons = read_icons_xml(asset_stack)

    with open(args.out_data, "w") as fout:
        fout.write("/* This file is auto-generated. Do not edit. */\n")
        fout.write('#include "common.h"\n')
        fout.write('#include "message_ids.h"\n')
        fout.write('#include "hud_element.h"\n')
        fout.write('#include "item_entity.h"\n')
        fout.write('#include "icon_offsets.h"\n')
        fout.write("\n")

        generate_hud_element_scripts(fout, items, icons)
        generate_item_entity_scripts(fout, items)

        generate_item_table(fout, items)
        generate_item_icon_tables(fout, items)

    with open(args.out_enum, "w") as fout:
        fout.write("/* This file is auto-generated. Do not edit. */\n")
        fout.write("\n")

        generate_item_enum(fout, items)
