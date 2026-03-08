#!/usr/bin/env python3
"""
Generates gAreas[] from the map overlay directory structure.

Hardcodes vanilla area and map ordering for save compatibility.
New areas/maps added by mods are appended after vanilla entries.
"""

import argparse
from pathlib import Path
from typing import Dict, List

VANILLA_AREA_ORDER = [
    "kmr",
    "mac",
    "tik",
    "kgr",
    "kkj",
    "hos",
    "nok",
    "trd",
    "iwa",
    "dro",
    "sbk",
    "isk",
    "mim",
    "obk",
    "arn",
    "dgb",
    "omo",
    "jan",
    "kzn",
    "flo",
    "sam",
    "pra",
    "kpa",
    "osr",
    "end",
    "mgm",
    "gv",
    "tst",
]

VANILLA_MAP_ORDER: Dict[str, List[str]] = {
    "kmr": [
        "kmr_00",
        "kmr_02",
        "kmr_03",
        "kmr_04",
        "kmr_05",
        "kmr_06",
        "kmr_07",
        "kmr_09",
        "kmr_10",
        "kmr_11",
        "kmr_12",
        "kmr_20",
        "kmr_21",
        "kmr_22",
        "kmr_23",
        "kmr_24",
        "kmr_30",
    ],
    "mac": [
        "machi",
        "mac_00",
        "mac_01",
        "mac_02",
        "mac_03",
        "mac_04",
        "mac_05",
        "mac_06",
    ],
    "tik": [
        "tik_01",
        "tik_02",
        "tik_03",
        "tik_04",
        "tik_05",
        "tik_06",
        "tik_07",
        "tik_08",
        "tik_09",
        "tik_10",
        "tik_12",
        "tik_14",
        "tik_15",
        "tik_17",
        "tik_18",
        "tik_19",
        "tik_20",
        "tik_21",
        "tik_22",
        "tik_23",
        "tik_24",
        "tik_25",
    ],
    "kgr": ["kgr_01", "kgr_02"],
    "kkj": [
        "kkj_00",
        "kkj_01",
        "kkj_02",
        "kkj_03",
        "kkj_10",
        "kkj_11",
        "kkj_12",
        "kkj_13",
        "kkj_14",
        "kkj_15",
        "kkj_16",
        "kkj_17",
        "kkj_18",
        "kkj_19",
        "kkj_20",
        "kkj_21",
        "kkj_22",
        "kkj_23",
        "kkj_24",
        "kkj_25",
        "kkj_26",
        "kkj_26",
        "kkj_27",
        "kkj_28",
        "kkj_29",
    ],
    "hos": [
        "hos_00",
        "hos_01",
        "hos_02",
        "hos_03",
        "hos_04",
        "hos_05",
        "hos_06",
        "hos_10",
        "hos_20",
    ],
    "nok": [
        "nok_01",
        "nok_02",
        "nok_03",
        "nok_04",
        "nok_11",
        "nok_12",
        "nok_13",
        "nok_14",
        "nok_15",
    ],
    "trd": [
        "trd_00",
        "trd_01",
        "trd_02",
        "trd_03",
        "trd_04",
        "trd_05",
        "trd_06",
        "trd_07",
        "trd_08",
        "trd_09",
        "trd_10",
    ],
    "iwa": ["iwa_00", "iwa_01", "iwa_02", "iwa_03", "iwa_04", "iwa_10", "iwa_11"],
    "dro": ["dro_01", "dro_02"],
    "sbk": [
        "sbk_00",
        "sbk_01",
        "sbk_02",
        "sbk_03",
        "sbk_04",
        "sbk_05",
        "sbk_06",
        "sbk_10",
        "sbk_11",
        "sbk_12",
        "sbk_13",
        "sbk_14",
        "sbk_15",
        "sbk_16",
        "sbk_20",
        "sbk_21",
        "sbk_22",
        "sbk_23",
        "sbk_24",
        "sbk_25",
        "sbk_26",
        "sbk_30",
        "sbk_31",
        "sbk_32",
        "sbk_33",
        "sbk_34",
        "sbk_35",
        "sbk_36",
        "sbk_40",
        "sbk_41",
        "sbk_42",
        "sbk_43",
        "sbk_44",
        "sbk_45",
        "sbk_46",
        "sbk_50",
        "sbk_51",
        "sbk_52",
        "sbk_53",
        "sbk_54",
        "sbk_55",
        "sbk_56",
        "sbk_60",
        "sbk_61",
        "sbk_62",
        "sbk_63",
        "sbk_64",
        "sbk_65",
        "sbk_66",
        "sbk_99",
    ],
    "isk": [
        "isk_01",
        "isk_02",
        "isk_03",
        "isk_04",
        "isk_05",
        "isk_06",
        "isk_07",
        "isk_08",
        "isk_09",
        "isk_10",
        "isk_11",
        "isk_12",
        "isk_13",
        "isk_14",
        "isk_16",
        "isk_18",
        "isk_19",
    ],
    "mim": [
        "mim_01",
        "mim_02",
        "mim_03",
        "mim_04",
        "mim_05",
        "mim_06",
        "mim_07",
        "mim_08",
        "mim_09",
        "mim_10",
        "mim_11",
        "mim_12",
    ],
    "obk": [
        "obk_01",
        "obk_02",
        "obk_03",
        "obk_04",
        "obk_05",
        "obk_06",
        "obk_07",
        "obk_08",
        "obk_09",
    ],
    "arn": [
        "arn_02",
        "arn_03",
        "arn_04",
        "arn_05",
        "arn_07",
        "arn_08",
        "arn_09",
        "arn_10",
        "arn_11",
        "arn_12",
        "arn_13",
    ],
    "dgb": [
        "dgb_00",
        "dgb_01",
        "dgb_02",
        "dgb_03",
        "dgb_04",
        "dgb_05",
        "dgb_06",
        "dgb_07",
        "dgb_08",
        "dgb_09",
        "dgb_10",
        "dgb_11",
        "dgb_12",
        "dgb_13",
        "dgb_14",
        "dgb_15",
        "dgb_16",
        "dgb_17",
        "dgb_18",
    ],
    "omo": [
        "omo_01",
        "omo_02",
        "omo_03",
        "omo_04",
        "omo_05",
        "omo_06",
        "omo_07",
        "omo_08",
        "omo_09",
        "omo_10",
        "omo_11",
        "omo_12",
        "omo_13",
        "omo_14",
        "omo_15",
        "omo_16",
        "omo_17",
    ],
    "jan": [
        "jan_00",
        "jan_01",
        "jan_02",
        "jan_03",
        "jan_04",
        "jan_05",
        "jan_06",
        "jan_07",
        "jan_08",
        "jan_09",
        "jan_10",
        "jan_11",
        "jan_12",
        "jan_13",
        "jan_14",
        "jan_15",
        "jan_16",
        "jan_17",
        "jan_18",
        "jan_19",
        "jan_22",
        "jan_23",
    ],
    "kzn": [
        "kzn_01",
        "kzn_02",
        "kzn_03",
        "kzn_04",
        "kzn_05",
        "kzn_06",
        "kzn_07",
        "kzn_08",
        "kzn_09",
        "kzn_10",
        "kzn_11",
        "kzn_17",
        "kzn_18",
        "kzn_19",
        "kzn_20",
        "kzn_22",
        "kzn_23",
    ],
    "flo": [
        "flo_00",
        "flo_03",
        "flo_07",
        "flo_08",
        "flo_09",
        "flo_10",
        "flo_11",
        "flo_12",
        "flo_13",
        "flo_14",
        "flo_15",
        "flo_16",
        "flo_17",
        "flo_18",
        "flo_19",
        "flo_21",
        "flo_22",
        "flo_23",
        "flo_24",
        "flo_25",
    ],
    "sam": [
        "sam_01",
        "sam_02",
        "sam_03",
        "sam_04",
        "sam_05",
        "sam_06",
        "sam_07",
        "sam_08",
        "sam_09",
        "sam_10",
        "sam_11",
        "sam_12",
    ],
    "pra": [
        "pra_01",
        "pra_02",
        "pra_03",
        "pra_04",
        "pra_05",
        "pra_06",
        "pra_09",
        "pra_10",
        "pra_11",
        "pra_12",
        "pra_13",
        "pra_14",
        "pra_15",
        "pra_16",
        "pra_18",
        "pra_19",
        "pra_20",
        "pra_21",
        "pra_22",
        "pra_27",
        "pra_28",
        "pra_29",
        "pra_31",
        "pra_32",
        "pra_33",
        "pra_34",
        "pra_35",
        "pra_36",
        "pra_37",
        "pra_38",
        "pra_39",
        "pra_40",
    ],
    "kpa": [
        "kpa_01",
        "kpa_03",
        "kpa_04",
        "kpa_08",
        "kpa_09",
        "kpa_10",
        "kpa_11",
        "kpa_12",
        "kpa_13",
        "kpa_14",
        "kpa_15",
        "kpa_16",
        "kpa_17",
        "kpa_32",
        "kpa_33",
        "kpa_40",
        "kpa_41",
        "kpa_50",
        "kpa_51",
        "kpa_52",
        "kpa_53",
        "kpa_60",
        "kpa_61",
        "kpa_62",
        "kpa_63",
        "kpa_70",
        "kpa_81",
        "kpa_82",
        "kpa_83",
        "kpa_90",
        "kpa_91",
        "kpa_94",
        "kpa_95",
        "kpa_96",
        "kpa_100",
        "kpa_101",
        "kpa_102",
        "kpa_111",
        "kpa_112",
        "kpa_113",
        "kpa_114",
        "kpa_115",
        "kpa_116",
        "kpa_117",
        "kpa_118",
        "kpa_119",
        "kpa_121",
        "kpa_130",
        "kpa_133",
        "kpa_134",
    ],
    "osr": ["osr_00", "osr_01", "osr_02", "osr_03", "osr_04"],
    "end": ["end_00", "end_01"],
    "mgm": ["mgm_00", "mgm_01", "mgm_02", "mgm_03"],
    "gv": ["gv_01"],
    "tst": [
        "tst_01",
        "tst_02",
        "tst_03",
        "tst_04",
        "tst_10",
        "tst_11",
        "tst_12",
        "tst_13",
        "tst_20",
    ],
}


def discover_maps(src_dir: Path, asset_stack: List[str]) -> Dict[str, List[str]]:
    """Walk world/area/ in src/ and asset dirs to discover all maps."""
    areas: Dict[str, set] = {}

    roots = [src_dir / "area"]
    for asset_dir in asset_stack:
        roots.append(Path("assets") / asset_dir / "world" / "area")

    for area_root in roots:
        if not area_root.exists():
            continue
        for area_dir in sorted(area_root.iterdir()):
            if not area_dir.is_dir():
                continue
            area_id = area_dir.name
            if area_id not in areas:
                areas[area_id] = set()
            for map_dir in sorted(area_dir.iterdir()):
                if not map_dir.is_dir():
                    continue

                # Check it contains a TL
                # This avoids including 'common' dirs as maps
                for f in map_dir.iterdir():
                    is_c = f.suffix == ".c" or f.suffix == ".cpp"
                    is_inc = f.name.endswith(".inc.c") or f.name.endswith(".inc.cpp")
                    if is_c and not is_inc:
                        # Found a TL, add this map to the list
                        areas[area_id].add(map_dir.name)
                        break
            if len(areas[area_id]) == 0:
                del areas[area_id]

    return areas


def build_ordered_areas(discovered: Dict[str, set]) -> List[tuple]:
    """Build final ordered list of (area_id, [map_ids])."""
    result = []
    seen_areas = set()

    for area_id in VANILLA_AREA_ORDER:
        seen_areas.add(area_id)
        if area_id not in VANILLA_MAP_ORDER:
            continue
        if area_id not in discovered:
            continue

        discovered_set = discovered[area_id]
        vanilla_maps = VANILLA_MAP_ORDER[area_id]

        # Keep vanilla maps that exist on disk, in vanilla order
        ordered_maps = [m for m in vanilla_maps if m in discovered_set]

        # Append any new maps not in vanilla
        vanilla_set = set(vanilla_maps)
        new_maps = sorted(m for m in discovered_set if m not in vanilla_set)
        ordered_maps.extend(new_maps)

        if ordered_maps:
            result.append((area_id, ordered_maps))

    # Append new areas not in vanilla
    new_areas = sorted(a for a in discovered if a not in seen_areas)
    for area_id in new_areas:
        maps = sorted(discovered[area_id])
        result.append((area_id, maps))

    return result


def generate(out_path: Path, areas: List[tuple]):
    with open(out_path, "w") as f:
        f.write("/* Auto-generated by gen_areas.py. Do not edit. */\n\n")

        for area_id, maps in areas:
            var_name = f"{area_id}_maps"
            f.write(f"static MapConfig {var_name}[] = {{\n")
            for map_id in maps:
                f.write(f'    {{ "{map_id}" }},\n')
            f.write("};\n\n")

        f.write("AreaConfig gAreas[] = {\n")
        for area_id, maps in areas:
            var_name = f"{area_id}_maps"
            f.write(f'    {{ ARRAY_COUNT({var_name}), {var_name}, "{area_id}" }},\n')
        f.write("    {},\n")
        f.write("};\n")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Generate gAreas from directory structure"
    )
    parser.add_argument("out", type=Path, help="Output .inc.c file")
    parser.add_argument("src_dir", type=Path, help="src/world directory")
    parser.add_argument(
        "--asset-stack", default="us", help="Comma-separated asset stack dirs"
    )
    args = parser.parse_args()

    asset_stack = [s.strip() for s in args.asset_stack.split(",") if s.strip()]
    discovered = discover_maps(args.src_dir, asset_stack)
    areas = build_ordered_areas(discovered)
    args.out.parent.mkdir(parents=True, exist_ok=True)
    generate(args.out, areas)
