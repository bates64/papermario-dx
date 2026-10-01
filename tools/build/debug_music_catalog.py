#!/usr/bin/env python3
"""Build the debug song browser from Star Rod's resolved song IDs."""

import argparse
import json
import re
from pathlib import Path


def catalog(header: str) -> str:
    enum = re.search(r"enum SongIDs\s*\{(.*?)\};", header, re.S)
    if enum is None:
        raise ValueError("generated audio header has no SongIDs enum")
    entries = re.findall(r"^\s*(SONG_[A-Z0-9_]+)\s*=\s*(0x[0-9A-Fa-f]+|[0-9]+)\s*,", enum[1], re.M)
    if not entries:
        raise ValueError("generated audio header has no songs")
    songs = sorted((int(value, 0), name) for name, value in entries)
    if len({song_id for song_id, _ in songs}) != len(songs) or len({name for _, name in songs}) != len(songs):
        raise ValueError("generated song IDs or names are not unique")
    lines = ["// Generated from audio/song_ids.h. Do not edit.\n"]
    for song_id, symbol in songs:
        if not 0 <= song_id <= 0xFF:
            raise ValueError(f"song ID outside native range: {symbol}")
        title = symbol.removeprefix("SONG_").replace("_", " ").title()
        if len(title) > 22:
            title = title[:19] + "..."
        lines.append(f"    {{ {symbol}, {json.dumps(title)} }},\n")
    return "".join(lines)


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("input", type=Path)
    parser.add_argument("output", type=Path)
    args = parser.parse_args()
    text = catalog(args.input.read_text())
    args.output.parent.mkdir(parents=True, exist_ok=True)
    if not args.output.exists() or args.output.read_text() != text:
        args.output.write_text(text)


if __name__ == "__main__":
    main()
