#!/usr/bin/env python3

"""
Sets what Paper Mario DX boots into when it powers on, by editing its FlashRAM
save, ares's by default. This never changes the game's save files.

Examples:

    # power on into the file you quick saved last, where you saved it
    tools/save_file.py continue

    # power on into the first file, at the first entrance of kmr_09
    tools/save_file.py map kmr_09 --file 1

    # power on into kmr_part_1's battle with two Goombas
    tools/save_file.py battle kmr_part_1:goomba_2

    # power on into a battle with a Paragoomba alone, starting over each time it ends
    tools/save_file.py actor paragoomba --repeat

    # power on as dx/config.h says again
    tools/save_file.py normal

Without --file or --new-game, the game loads the file it loaded last, or
starts a new game if there's none.
"""

import argparse
import re
import struct
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
# where ares keeps the save of the ROM this repository builds
DEFAULT_SAVE = REPO / "ver" / "current" / "build" / "papermario.flash"
BATTLE_AREAS = REPO / "src" / "battle" / "area"

FLASH_SIZE = 0x20000
SECTOR_SIZE = 0x4000
PHYSICAL_SAVE_COUNT = 6
GLOBALS_SECTORS = (6, 7)
SLOT_COUNT = 4

MAGIC = b"Mario Story 006"

GLOBALS_SIZE = 0x80
GLOBALS_BOOT_TO = 0x40
GLOBALS_BOOT_SCENE = 0x41

# SaveBootRecord, on the flash page after the globals
RECORD_OFFSET = 0x80
RECORD_SIZE = 0x100
RECORD_BASE_SLOT = 0x08
RECORD_START = 0x09
RECORD_ON_BATTLE_END = 0x0A
RECORD_ENTRY_ID = 0x0C
RECORD_NAMES = {
    "map": (0x10, 16),
    "battle_area": (0x20, 32),
    "battle": (0x40, 64),
    "stage": (0x80, 32),
    "actor": (0xA0, 32),
}

SAVE_SIZE = 0x1380
SAVE_MOD_NAME = 0x10
SAVE_VERSION = 0x2C
SAVE_SLOT = 0x38
SAVE_PLAYER_LEVEL = 0x40 + 0x09
SAVE_MAP_HASH = 0x468
SAVE_ENTRY_ID = 0x46C

BOOT_TO = ["normal", "logos", "intro", "demo", "title", "file-select", "record"]
BOOT_START = ["saved", "entrance", "battle"]
BATTLE_END = ["return", "restart"]


def hash_string(name: str) -> int:
    """A map's hash, as hash_string in src/math_util.c computes it and saves store it."""
    value = 0x811C9DC5
    for byte in name.encode():
        value = ((value ^ byte) * 0x01000193) & 0xFFFFFFFF
    return value


def checksum(data: bytes) -> int:
    """The sum of a block's big-endian words, as fio_calc_file_checksum computes it."""
    return sum(struct.unpack(f">{len(data) // 4}I", data)) & 0xFFFFFFFF


def has_valid_checksums(block: bytes, offset: int) -> bool:
    """Whether a block's checksums, at offset in it, match its contents."""
    crc1, crc2 = struct.unpack_from(">II", block, offset)
    if crc1 != crc2 ^ 0xFFFFFFFF:
        return False
    unsigned = bytearray(block)
    struct.pack_into(">II", unsigned, offset, 0, 0xFFFFFFFF)
    return checksum(unsigned) == crc1


def sign(block: bytearray, offset: int) -> None:
    """Sets a block's checksums, at offset in it, as the game does before writing it."""
    struct.pack_into(">II", block, offset, 0, 0xFFFFFFFF)
    crc = checksum(block)
    struct.pack_into(">II", block, offset, crc, crc ^ 0xFFFFFFFF)


def c_string(data: bytes) -> str:
    return bytes(data).split(b"\0", 1)[0].decode(errors="replace")


class SaveFile:
    def __init__(self, data: bytes):
        if len(data) != FLASH_SIZE:
            raise ValueError(f"expected a {FLASH_SIZE // 1024} KiB FlashRAM image, but it's {len(data)} bytes")
        self.data = bytearray(data)

    @classmethod
    def blank(cls) -> "SaveFile":
        """Erased flash, as a cartridge holds before the game first saves."""
        return cls(b"\xff" * FLASH_SIZE)

    def block(self, sector: int, offset: int, size: int) -> bytes:
        start = sector * SECTOR_SIZE + offset
        return bytes(self.data[start : start + size])

    def latest_saves(self) -> dict[int, int]:
        """The physical save holding each file's most recent save, as fio_fetch_saved_file_info picks them."""
        latest: dict[int, tuple[int, int]] = {}
        for physical in range(PHYSICAL_SAVE_COUNT):
            block = self.block(physical, 0, SAVE_SIZE)
            if not block.startswith(MAGIC + b"\0") or not has_valid_checksums(block, 0x30):
                continue
            slot, count = struct.unpack_from(">ii", block, SAVE_SLOT)
            if slot not in latest or latest[slot][1] < count:
                latest[slot] = (physical, count)
        return {slot: physical for slot, (physical, _) in latest.items()}

    def globals_block(self) -> bytearray:
        """The game's globals, or fresh ones if neither copy is valid, as fio_load_globals falls back."""
        for sector in GLOBALS_SECTORS:
            block = self.block(sector, 0, GLOBALS_SIZE)
            if block.startswith(MAGIC + b"\0") and has_valid_checksums(block, 0x30):
                return bytearray(block)
        return bytearray(GLOBALS_SIZE)

    def record_block(self) -> bytearray | None:
        """The boot record, or None if neither copy is valid."""
        for sector in GLOBALS_SECTORS:
            block = self.block(sector, RECORD_OFFSET, RECORD_SIZE)
            if has_valid_checksums(block, 0):
                return bytearray(block)
        return None

    def write_globals(self, globals_block: bytearray, record: bytearray) -> None:
        """Writes the globals and the boot record into both of their sectors, as fio_save_globals does."""
        globals_block[0:16] = MAGIC.ljust(16, b"\0")
        sign(globals_block, 0x30)
        sign(record, 0)
        for sector in GLOBALS_SECTORS:
            start = sector * SECTOR_SIZE
            self.data[start : start + GLOBALS_SIZE] = globals_block
            self.data[start + RECORD_OFFSET : start + RECORD_OFFSET + RECORD_SIZE] = record


def area_source(area: str) -> str | None:
    """A battle area's source, which lists its battles, or None if there's no such area."""
    for extension in (".c", ".cpp"):
        path = BATTLE_AREAS / (area + extension)
        if path.exists():
            return path.read_text()
    return None


def first_battle(area: str) -> str:
    """The formation of an area's first battle, such as goomba_1."""
    source = area_source(area)
    if source is None:
        sys.exit(f"There's no battle area {area} in {BATTLE_AREAS}.")
    # BATTLE(goomba_1, "kmr_04") or BATTLE_WITH_SCRIPT(demo_01, "nok_04", EVS_Demo01)
    match = re.search(r"\bBATTLE(?:_WITH_SCRIPT)?\(\s*(\w+)\s*,", source)
    if match is None:
        sys.exit(f"Battle area {area} has no battles.")
    return match[1]


def battle_on_stage(stage: str) -> tuple[str, str]:
    """The first battle fought on the stage, as its area and formation, or else the first area's first battle."""
    areas = sorted(path.stem for path in BATTLE_AREAS.glob("*.c*"))
    if not areas:
        sys.exit(f"There are no battle areas in {BATTLE_AREAS}.")
    for area in areas:
        # BATTLE(goomba_1, "kmr_04") or BATTLE_WITH_SCRIPT(demo_01, "nok_04", EVS_Demo01)
        match = re.search(rf'\bBATTLE(?:_WITH_SCRIPT)?\(\s*(\w+)\s*,\s*"{re.escape(stage)}"', area_source(area) or "")
        if match is not None:
            return area, match[1]
    return areas[0], first_battle(areas[0])


def area_using_actor(actor: str) -> str:
    """The first battle area whose battles use the actor, or else the first area."""
    areas = sorted(path.stem for path in BATTLE_AREAS.glob("*.c*"))
    if not areas:
        sys.exit(f"There are no battle areas in {BATTLE_AREAS}.")
    for area in areas:
        if f'"{actor}"' in (area_source(area) or ""):
            return area
    return areas[0]


def describe(globals_block: bytes, record: bytes) -> str:
    """What the game powers on into, as a sentence."""
    boot_to = BOOT_TO[globals_block[GLOBALS_BOOT_TO]]
    if boot_to == "normal":
        return "The game powers on as dx/config.h says."
    if boot_to != "record":
        screen = {"logos": "logos", "intro": "story book", "demo": "demo", "title": "title screen",
                  "file-select": "file select"}[boot_to]
        scene = globals_block[GLOBALS_BOOT_SCENE]
        start = {"intro": f", from part {scene}", "demo": f", from scene {scene}"}.get(boot_to, "")
        return f"The game powers on to the {screen}{start}."

    base_slot = struct.unpack_from(">b", record, RECORD_BASE_SLOT)[0]
    base = "a new game" if base_slot < 0 else f"file {base_slot + 1}"
    names = {field: c_string(record[offset : offset + size]) for field, (offset, size) in RECORD_NAMES.items()}
    start = BOOT_START[record[RECORD_START]]
    if start == "saved":
        if base_slot < 0:
            return "The game powers on into a new game."
        return f"The game powers on into {base}, where it was saved."
    if start == "entrance":
        entry = struct.unpack_from(">h", record, RECORD_ENTRY_ID)[0]
        return f"The game powers on into {base}, at entrance {entry} of {names['map']}."
    fight = f"battle {names['battle_area']}:{names['battle']}" if names["battle"] else (
        f"a battle with {names['actor']} alone, in {names['battle_area']}"
    )
    stage = f" on stage {names['stage']}" if names["stage"] else ""
    repeat = ", starting it over each time it ends" if BATTLE_END[record[RECORD_ON_BATTLE_END]] == "restart" else ""
    return f"The game powers on into {base}, in {fight}{stage}{repeat}."


def boot_to(save_file: SaveFile, args: argparse.Namespace) -> None:
    """Powers on to a screen, without loading a file."""
    globals_block = save_file.globals_block()
    globals_block[GLOBALS_BOOT_TO] = BOOT_TO.index(args.command)
    globals_block[GLOBALS_BOOT_SCENE] = getattr(args, "scene", 0)
    save_file.write_globals(globals_block, save_file.record_block() or new_record())


def new_record() -> bytearray:
    record = bytearray(RECORD_SIZE)
    struct.pack_into(">b", record, RECORD_BASE_SLOT, -1)
    return record


def boot_into_game(save_file: SaveFile, args: argparse.Namespace) -> None:
    """Powers on into a file or a new game, starting where the command says."""
    globals_block = save_file.globals_block()
    globals_block[GLOBALS_BOOT_TO] = BOOT_TO.index("record")

    # keeps only which file to load from the last record, if it's valid
    last = save_file.record_block()
    record = new_record()
    if last is not None:
        record[RECORD_BASE_SLOT] = last[RECORD_BASE_SLOT]
    if getattr(args, "new_game", False):
        struct.pack_into(">b", record, RECORD_BASE_SLOT, -1)
    elif getattr(args, "file", None) is not None:
        struct.pack_into(">b", record, RECORD_BASE_SLOT, args.file - 1)

    names: dict[str, str] = {}
    if args.command == "continue":
        record[RECORD_START] = BOOT_START.index("saved")
    elif args.command == "map":
        base_slot = struct.unpack_from(">b", record, RECORD_BASE_SLOT)[0]
        latest = save_file.latest_saves()
        saved_in_map = base_slot in latest and struct.unpack_from(
            ">I", save_file.block(latest[base_slot], 0, SAVE_SIZE), SAVE_MAP_HASH
        )[0] == hash_string(args.map)
        if args.resume and saved_in_map:
            record[RECORD_START] = BOOT_START.index("saved")
        else:
            record[RECORD_START] = BOOT_START.index("entrance")
            struct.pack_into(">h", record, RECORD_ENTRY_ID, args.entry)
            names["map"] = args.map
    else:
        record[RECORD_START] = BOOT_START.index("battle")
        record[RECORD_ON_BATTLE_END] = BATTLE_END.index("restart" if args.repeat else "return")
        if args.command == "battle":
            area, _, formation = args.battle.partition(":")
            names["battle_area"] = area
            names["battle"] = formation or first_battle(area)
        elif args.command == "stage":
            names["battle_area"], names["battle"] = battle_on_stage(args.stage)
        else:
            names["battle_area"] = args.area or area_using_actor(args.actor)
            names["actor"] = args.actor
        if args.stage is not None:
            names["stage"] = args.stage

    for field, value in names.items():
        offset, size = RECORD_NAMES[field]
        encoded = value.encode()
        # the game reads each name up to its first null, so one must fit
        if len(encoded) >= size:
            sys.exit(f"{value!r} is {len(encoded)} bytes, but the save only has room for {size - 1}.")
        record[offset : offset + size] = encoded.ljust(size, b"\0")

    save_file.write_globals(globals_block, record)


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    commands = parser.add_subparsers(dest="command", required=True, metavar="COMMAND")

    save = argparse.ArgumentParser(add_help=False)
    save.add_argument("--save", type=Path, default=DEFAULT_SAVE, help="the save to edit, instead of ares's")

    file = argparse.ArgumentParser(add_help=False)
    which_file = file.add_mutually_exclusive_group()
    which_file.add_argument("--file", type=int, choices=range(1, SLOT_COUNT + 1), help="the file to load")
    which_file.add_argument("--new-game", action="store_true", help="start a new game instead of loading a file")

    battle = argparse.ArgumentParser(add_help=False)
    battle.add_argument("--stage", help="the stage to fight on, such as kmr_04, instead of the battle's own")
    battle.add_argument("--repeat", action="store_true", help="start the battle over each time it ends")

    commands.add_parser("normal", parents=[save], help="power on as dx/config.h says, such as to the logos")
    commands.add_parser("logos", parents=[save], help="power on to the logos")
    intro = commands.add_parser("intro", parents=[save], help="power on to the story book")
    intro.add_argument("scene", metavar="part", type=int, nargs="?", default=0, help="the part to start from, 0 by default")
    demo = commands.add_parser("demo", parents=[save], help="power on to the demo that plays at the title screen")
    demo.add_argument("scene", type=int, nargs="?", default=0, help="the scene to start from, 0 by default")
    commands.add_parser("title", parents=[save], help="power on to the title screen")
    commands.add_parser("file-select", parents=[save], help="power on to the file select")

    continue_parser = commands.add_parser("continue", parents=[save], help="power on into a file, where it was saved")
    continue_parser.add_argument("--file", type=int, choices=range(1, SLOT_COUNT + 1), help="the file to load")
    map_parser = commands.add_parser("map", parents=[save, file], help="power on into a map, at an entrance")
    map_parser.add_argument("map", help="the map, such as kmr_20")
    where = map_parser.add_mutually_exclusive_group()
    where.add_argument("--entry", type=int, default=0, help="the entrance to start at, 0 by default")
    where.add_argument("--resume", action="store_true",
                       help="start where the file was saved instead, if that's in the map")
    battle_parser = commands.add_parser("battle", parents=[save, file, battle], help="power on into a battle")
    battle_parser.add_argument("battle", help="the battle area and its battle's formation, such as kmr_part_1:goomba_2, "
                               "or just the area for its first battle")
    stage_parser = commands.add_parser("stage", parents=[save, file], help="power on into a battle on a stage")
    stage_parser.add_argument("stage", help="the stage, such as kmr_04, which the first battle fought on it uses")
    stage_parser.add_argument("--repeat", action="store_true", help="start the battle over each time it ends")
    actor_parser = commands.add_parser("actor", parents=[save, file, battle], help="power on into a battle with one actor")
    actor_parser.add_argument("actor", help="the actor, such as paragoomba, or one of its variants, such as koopa_bros:red")
    actor_parser.add_argument("--area", help="the battle area to fight in, instead of the first whose battles use the actor")

    args = parser.parse_args()
    save_file = SaveFile(args.save.read_bytes()) if args.save.exists() else SaveFile.blank()
    if args.command in ("continue", "map", "battle", "stage", "actor"):
        boot_into_game(save_file, args)
    else:
        boot_to(save_file, args)
    args.save.write_bytes(save_file.data)
    print(describe(save_file.globals_block(), save_file.record_block()))


if __name__ == "__main__":
    main()
