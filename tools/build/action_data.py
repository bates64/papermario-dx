#!/usr/bin/env python3

import argparse
import re
from dataclasses import dataclass
from pathlib import Path
from typing import List, Optional

import yaml


C_IDENTIFIER = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")
OVERLAY_NAME = re.compile(r"^[a-z0-9_]+$")


@dataclass(frozen=True)
class ActionDefinition:
    state: str
    desc: Optional[str]
    overlay: str
    entry: Optional[str]
    enabled_for_peach: bool


def actions_from_yaml(path: Path) -> List[ActionDefinition]:
    with path.open() as stream:
        data = yaml.load(stream, Loader=yaml.SafeLoader)

    if not isinstance(data, list):
        raise ValueError("action data must be a YAML list")

    actions = []
    states = set()
    for index, value in enumerate(data):
        if not isinstance(value, dict):
            raise ValueError(f"action {index} must be a mapping")

        missing = {"state", "overlay", "entry", "enabledForPeach"} - value.keys()
        extra = value.keys() - {"state", "desc", "overlay", "entry", "enabledForPeach"}
        if missing:
            raise ValueError(f"action {index} is missing: {', '.join(sorted(missing))}")
        if extra:
            raise ValueError(f"action {index} has unknown fields: {', '.join(sorted(extra))}")

        state = value["state"]
        desc = value.get("desc")
        overlay = value["overlay"]
        entry = value["entry"]
        enabled_for_peach = value["enabledForPeach"]

        if (
            not isinstance(state, str)
            or not state.startswith("ACTION_STATE_")
            or not C_IDENTIFIER.fullmatch(state)
        ):
            raise ValueError(f"action {index} has invalid state {state!r}")
        if state in states:
            raise ValueError(f"duplicate action state {state}")
        states.add(state)

        if desc is not None and (not isinstance(desc, str) or "\n" in desc):
            raise ValueError(f"action {state} has invalid description {desc!r}")
        if not isinstance(overlay, str) or not OVERLAY_NAME.fullmatch(overlay):
            raise ValueError(f"action {state} has invalid overlay {overlay!r}")
        if entry is not None and (
            not isinstance(entry, str) or not C_IDENTIFIER.fullmatch(entry)
        ):
            raise ValueError(f"action {state} has invalid entry {entry!r}")
        if not isinstance(enabled_for_peach, bool):
            raise ValueError(f"action {state} enabledForPeach must be a boolean")

        actions.append(ActionDefinition(state, desc, overlay, entry, enabled_for_peach))

    return actions


def generate_action_state_enum(path: Path, actions: List[ActionDefinition]):
    lines = [
        "/* This file is auto-generated. Do not edit. */\n",
        "\n",
        "#pragma once\n",
        "\n",
        "enum ActionStates {\n",
    ]
    for index, action in enumerate(actions):
        line = f"    {action.state:43} = 0x{index:08X},"
        if action.desc is not None:
            line += f"  ///< {action.desc}"
        lines.append(line + "\n")
    lines.extend([
        "};\n",
        "\n",
        f"#define ACTION_COUNT {len(actions)}\n",
    ])
    path.write_text("".join(lines))


def generate_table(path: Path, actions: List[ActionDefinition]):
    lines = [
        "/* This file is auto-generated. Do not edit. */\n",
        "Action PlayerActionsTable[ACTION_COUNT] = {\n",
    ]
    for action in actions:
        entry = "nullptr" if action.entry is None else f'"{action.entry}"'
        lines.extend([
            f"    [{action.state}] = {{\n",
            f'        .family = "{action.overlay}",\n',
            f"        .entry = {entry},\n",
            f"        .enabledForPeach = {'true' if action.enabled_for_peach else 'false'},\n",
            "    },\n",
        ])
    lines.extend([
        "};\n",
    ])
    path.write_text("".join(lines))


def main():
    parser = argparse.ArgumentParser(description="Generates player action data")
    parser.add_argument("out_data", type=Path)
    parser.add_argument("out_enum", type=Path)
    parser.add_argument("actions_yaml", type=Path)
    args = parser.parse_args()

    actions = actions_from_yaml(args.actions_yaml)
    for path in (args.out_data, args.out_enum):
        path.parent.mkdir(parents=True, exist_ok=True)

    generate_table(args.out_data, actions)
    generate_action_state_enum(args.out_enum, actions)


if __name__ == "__main__":
    main()
