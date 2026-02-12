#!/usr/bin/env python3
"""
Reorganize mapfs directory structure from flat to area-based hierarchy.

This script reorganizes map assets from:
  assets/us/mapfs/geom/<map>.xml
  assets/us/mapfs/tex/<area>_tex/
  assets/us/mapfs/bg/<name>_bg.png

To:
  assets/us/mapfs/areas/<area>/<map>.map/map.xml
  assets/us/mapfs/areas/<area>/<area>.tex/
  assets/us/mapfs/backgrounds/<name>.bg.png
"""

import sys
from pathlib import Path
import shutil
from typing import Dict, List, Tuple

# Japanese to English party member name mapping
PARTY_NAME_MAP = {
    "party_kurio": "goombario",
    "party_kameki": "kooper",
    "party_pinki": "bombette",
    "party_pareta": "parakarry",
    "party_resa": "bow",
    "party_akari": "watt",
    "party_opuku": "sushie",
    "party_pokopi": "lakilester",
}


def parse_area_from_map_name(map_name: str) -> str:
    """
    Extract area code from map name.

    Args:
        map_name: Map name like "kmr_20", "arn_bt01", or "machi"

    Returns:
        Area code (e.g., "kmr", "arn", "mac")
    """
    # Special case: "machi" belongs to "mac" area
    if map_name == "machi":
        return "mac"

    # For names with underscore, take prefix
    if "_" in map_name:
        return map_name.split("_")[0]

    # Single-part names: take first 3 characters
    # (This shouldn't happen for maps but handles edge cases)
    return map_name[:3]


def is_battle_stage(map_name: str) -> bool:
    """
    Check if map name represents a battle stage.

    Args:
        map_name: Map name like "kmr_20" or "arn_bt01"

    Returns:
        True for battle stages, False for regular maps
    """
    return "_bt" in map_name


def transform_background_name(filename: str) -> str:
    """
    Transform background filename from old to new format.

    Examples:
        kmr_bg.png -> kmr.bg.png
        sbk_bg.1.png -> sbk.1.bg.png
        sbk3_bg.png -> sbk3.bg.png

    Args:
        filename: Original background filename

    Returns:
        Transformed filename
    """
    # Remove .png extension
    name = filename[:-4] if filename.endswith(".png") else filename

    # Handle variants with dots (e.g., sbk_bg.1)
    if "_bg." in name:
        # sbk_bg.1 -> sbk.1.bg
        parts = name.split("_bg.")
        return f"{parts[0]}.{parts[1]}.bg.png"

    # Handle standard _bg suffix
    if name.endswith("_bg"):
        # kmr_bg -> kmr.bg
        return name[:-3] + ".bg.png"

    # Handle numbered variants without dot (e.g., sbk3_bg)
    # This is just sbk3_bg -> sbk3.bg
    if "_bg" in name:
        return name.replace("_bg", ".bg") + ".png"

    # Fallback: add .bg.png
    return name + ".bg.png"


def transform_texture_dir_name(dirname: str) -> str:
    """
    Transform texture directory name from old to new format.

    Examples:
        kmr_tex -> kmr.tex
        gv__tex -> gv_.tex

    Args:
        dirname: Original texture directory name

    Returns:
        Transformed directory name
    """
    if dirname.endswith("_tex"):
        # Strip _tex suffix and add .tex extension
        return dirname[:-4] + ".tex"

    # Fallback
    return dirname + ".tex"


def reorganize_maps(mapfs_dir: Path) -> Dict[str, any]:
    """
    Reorganize map files into area-based directories.

    Args:
        mapfs_dir: Path to mapfs directory (e.g., assets/us/mapfs/)

    Returns:
        Statistics dict with counts and errors
    """
    stats = {
        "maps_moved": 0,
        "stages_moved": 0,
        "files_moved": 0,
        "errors": [],
        "areas": set(),
    }

    geom_dir = mapfs_dir / "geom"
    if not geom_dir.exists():
        stats["errors"].append(f"Geometry directory not found: {geom_dir}")
        return stats

    areas_dir = mapfs_dir / "areas"
    areas_dir.mkdir(parents=True, exist_ok=True)

    # Find all map files (XML, shape, hit)
    xml_files = list(geom_dir.glob("*.xml"))
    shape_files = list(geom_dir.glob("*_shape.bin"))
    hit_files = list(geom_dir.glob("*_hit.bin"))

    # Group by map name (xml, shape.bin, hit.bin)
    maps: Dict[str, List[Path]] = {}

    # Process XML files and their associated files
    for xml_file in xml_files:
        map_name = xml_file.stem
        if map_name not in maps:
            maps[map_name] = []
        maps[map_name].append(xml_file)

    # Process shape files (may exist without XML)
    for shape_file in shape_files:
        map_name = shape_file.stem[:-6]  # Strip _shape
        if map_name not in maps:
            maps[map_name] = []
        maps[map_name].append(shape_file)

    # Process hit files (may exist without XML)
    for hit_file in hit_files:
        map_name = hit_file.stem[:-4]  # Strip _hit
        if map_name not in maps:
            maps[map_name] = []
        maps[map_name].append(hit_file)

    # Move each map
    for map_name, files in maps.items():
        area = parse_area_from_map_name(map_name)
        stats["areas"].add(area)

        # Determine directory extension
        if is_battle_stage(map_name):
            ext = ".stage"
            stats["stages_moved"] += 1
        else:
            ext = ".map"
            stats["maps_moved"] += 1

        # Create area and map directories
        area_dir = areas_dir / area
        area_dir.mkdir(exist_ok=True)

        map_dir = area_dir / (map_name + ext)
        map_dir.mkdir(exist_ok=True)

        # Move files
        for src_file in files:
            if src_file.suffix == ".xml":
                dst_file = map_dir / "map.xml"
            elif src_file.name.endswith("_shape.bin"):
                dst_file = map_dir / "shape.bin"
            elif src_file.name.endswith("_hit.bin"):
                dst_file = map_dir / "hit.bin"
            else:
                stats["errors"].append(f"Unexpected file: {src_file}")
                continue

            try:
                shutil.move(str(src_file), str(dst_file))
                stats["files_moved"] += 1
            except Exception as e:
                stats["errors"].append(f"Failed to move {src_file} to {dst_file}: {e}")

    return stats


def reorganize_textures(mapfs_dir: Path) -> Dict[str, any]:
    """
    Reorganize texture directories into area directories.

    Args:
        mapfs_dir: Path to mapfs directory

    Returns:
        Statistics dict with counts and errors
    """
    stats = {
        "tex_dirs_moved": 0,
        "tex_files_moved": 0,
        "errors": [],
    }

    tex_dir = mapfs_dir / "tex"
    if not tex_dir.exists():
        stats["errors"].append(f"Texture directory not found: {tex_dir}")
        return stats

    areas_dir = mapfs_dir / "areas"

    # Process each texture directory
    for src_tex_dir in tex_dir.iterdir():
        if not src_tex_dir.is_dir():
            continue

        area_name = src_tex_dir.name
        if not area_name.endswith("_tex"):
            stats["errors"].append(f"Unexpected texture directory name: {area_name}")
            continue

        # Determine area code (strip _tex suffix)
        area = area_name[:-4]

        # Handle special cases like gv__tex -> gv_
        # (The extra underscore is intentional in the codebase)

        area_dir = areas_dir / area
        area_dir.mkdir(parents=True, exist_ok=True)

        # Transform directory name
        new_tex_name = transform_texture_dir_name(area_name)
        dst_tex_dir = area_dir / new_tex_name

        try:
            shutil.move(str(src_tex_dir), str(dst_tex_dir))
            stats["tex_dirs_moved"] += 1

            # Count files moved
            stats["tex_files_moved"] += sum(1 for _ in dst_tex_dir.rglob("*") if _.is_file())

            # Move JSON metadata file if it exists
            json_file = tex_dir / (area_name + ".json")
            if json_file.exists():
                dst_json = dst_tex_dir / "textures.json"
                shutil.move(str(json_file), str(dst_json))
                stats["tex_files_moved"] += 1
        except Exception as e:
            stats["errors"].append(f"Failed to move texture directory {src_tex_dir}: {e}")

    return stats


def reorganize_backgrounds(mapfs_dir: Path) -> Dict[str, any]:
    """
    Reorganize background images into shared backgrounds directory.

    Args:
        mapfs_dir: Path to mapfs directory

    Returns:
        Statistics dict with counts and errors
    """
    stats = {
        "bg_files_moved": 0,
        "errors": [],
    }

    bg_dir = mapfs_dir / "bg"
    if not bg_dir.exists():
        stats["errors"].append(f"Background directory not found: {bg_dir}")
        return stats

    backgrounds_dir = mapfs_dir / "backgrounds"
    backgrounds_dir.mkdir(exist_ok=True)

    # Move all background files
    for src_bg_file in bg_dir.iterdir():
        if not src_bg_file.is_file():
            continue

        # Transform filename
        new_name = transform_background_name(src_bg_file.name)
        dst_bg_file = backgrounds_dir / new_name

        try:
            shutil.move(str(src_bg_file), str(dst_bg_file))
            stats["bg_files_moved"] += 1
        except Exception as e:
            stats["errors"].append(f"Failed to move background {src_bg_file}: {e}")

    return stats


def reorganize_party_icons(mapfs_dir: Path) -> Dict[str, any]:
    """
    Reorganize party icon images into partner directories.

    Args:
        mapfs_dir: Path to mapfs directory

    Returns:
        Statistics dict with counts and errors
    """
    stats = {
        "party_icons_moved": 0,
        "errors": [],
    }

    party_dir = mapfs_dir / "party"
    if not party_dir.exists():
        stats["errors"].append(f"Party directory not found: {party_dir}")
        return stats

    # Move all party icon files into .partner directories
    for src_party_file in party_dir.iterdir():
        if not src_party_file.is_file():
            continue

        # Get the Japanese name (e.g., "party_kurio")
        japanese_name = src_party_file.stem

        # Look up English name, or use Japanese name if not found (for user mods)
        if japanese_name in PARTY_NAME_MAP:
            english_name = PARTY_NAME_MAP[japanese_name]
        else:
            # Strip "party_" prefix if present
            english_name = japanese_name[6:] if japanese_name.startswith("party_") else japanese_name

        # Create partner directory (e.g., "goombario.partner")
        partner_dir = party_dir / f"{english_name}.partner"
        partner_dir.mkdir(exist_ok=True)

        # Move file as art.png
        dst_file = partner_dir / "art.png"

        try:
            shutil.move(str(src_party_file), str(dst_file))
            stats["party_icons_moved"] += 1
        except Exception as e:
            stats["errors"].append(f"Failed to move party icon {src_party_file}: {e}")

    return stats


def cleanup_old_directories(mapfs_dir: Path) -> None:
    """
    Remove old empty directories after reorganization.

    Args:
        mapfs_dir: Path to mapfs directory
    """
    dirs_to_remove = ["geom", "tex", "bg"]

    for dir_name in dirs_to_remove:
        dir_path = mapfs_dir / dir_name
        if dir_path.exists():
            try:
                # Only remove if empty
                if not any(dir_path.iterdir()):
                    dir_path.rmdir()
                    print(f"Removed empty directory: {dir_path}")
                else:
                    print(f"Warning: Directory not empty, not removing: {dir_path}")
            except Exception as e:
                print(f"Warning: Failed to remove directory {dir_path}: {e}")


def reorganize_mapfs(version: str = "us") -> None:
    """
    Main entry point for mapfs reorganization.

    Args:
        version: Game version (us, jp, ique)
    """
    assets_dir = Path(__file__).parent.parent.parent / "assets"
    mapfs_dir = assets_dir / version / "mapfs"

    if not mapfs_dir.exists():
        print(f"Error: mapfs directory not found: {mapfs_dir}")
        return

    # Check if already reorganized
    areas_dir = mapfs_dir / "areas"
    if areas_dir.exists() and any(areas_dir.iterdir()):
        print(f"Mapfs already reorganized (areas/ exists), skipping")
        return

    print(f"Reorganizing mapfs for {version}...")
    print(f"Source: {mapfs_dir}")
    print()

    # Reorganize maps
    print("Reorganizing maps...")
    map_stats = reorganize_maps(mapfs_dir)
    print(f"  Regular maps moved: {map_stats['maps_moved']}")
    print(f"  Battle stages moved: {map_stats['stages_moved']}")
    print(f"  Total files moved: {map_stats['files_moved']}")
    print(f"  Areas processed: {len(map_stats['areas'])}")
    if map_stats['errors']:
        print(f"  Errors: {len(map_stats['errors'])}")
        for error in map_stats['errors'][:5]:  # Show first 5 errors
            print(f"    - {error}")
    print()

    # Reorganize textures
    print("Reorganizing textures...")
    tex_stats = reorganize_textures(mapfs_dir)
    print(f"  Texture directories moved: {tex_stats['tex_dirs_moved']}")
    print(f"  Total texture files moved: {tex_stats['tex_files_moved']}")
    if tex_stats['errors']:
        print(f"  Errors: {len(tex_stats['errors'])}")
        for error in tex_stats['errors'][:5]:
            print(f"    - {error}")
    print()

    # Reorganize backgrounds
    print("Reorganizing backgrounds...")
    bg_stats = reorganize_backgrounds(mapfs_dir)
    print(f"  Background files moved: {bg_stats['bg_files_moved']}")
    if bg_stats['errors']:
        print(f"  Errors: {len(bg_stats['errors'])}")
        for error in bg_stats['errors'][:5]:
            print(f"    - {error}")
    print()

    # Reorganize party icons
    print("Reorganizing party icons...")
    party_stats = reorganize_party_icons(mapfs_dir)
    print(f"  Party icons moved: {party_stats['party_icons_moved']}")
    if party_stats['errors']:
        print(f"  Errors: {len(party_stats['errors'])}")
        for error in party_stats['errors'][:5]:
            print(f"    - {error}")
    print()

    # Cleanup
    print("Cleaning up old directories...")
    cleanup_old_directories(mapfs_dir)
    print()

    # Summary
    print("=" * 60)
    print("Reorganization complete!")
    print(f"  Total maps: {map_stats['maps_moved'] + map_stats['stages_moved']}")
    print(f"  Total files moved: {map_stats['files_moved'] + tex_stats['tex_files_moved'] + bg_stats['bg_files_moved'] + party_stats['party_icons_moved']}")
    print(f"  Areas: {', '.join(sorted(map_stats['areas']))}")

    total_errors = len(map_stats['errors']) + len(tex_stats['errors']) + len(bg_stats['errors']) + len(party_stats['errors'])
    if total_errors > 0:
        print(f"  Total errors: {total_errors}")
        print()
        print("Please review errors above and fix manually if needed.")
    else:
        print("  No errors!")
    print("=" * 60)


if __name__ == "__main__":
    version = sys.argv[1] if len(sys.argv) > 1 else "us"
    reorganize_mapfs(version)
