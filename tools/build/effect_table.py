"""The effect list, read from the yaml the game is built from.

Kept out of the splat extension so the build can read it without splat.
"""

from dataclasses import dataclass
from pathlib import Path
from typing import List

import yaml as yaml_loader


@dataclass
class Effect:
    name: str
    args: str
    gfx: str
    empty: bool
    returns_void: bool

    def get_macro_def(self) -> str:
        ret_type = "void" if self.returns_void else "EffectInstance*"

        return f"#define EFFECT_DEF_{self.name.upper()}(func_name) {ret_type} func_name({self.args})"

    def get_macro_call(self, func_name: str) -> str:
        return f"EFFECT_DEF_{self.name.upper()}({func_name})"


def effects_from_yaml(yaml_path: Path) -> List[Effect]:
    with open(yaml_path, "r", encoding="utf-8") as f:
        effects_yaml = yaml_loader.load(f.read(), Loader=yaml_loader.SafeLoader)

    effects: List[Effect] = []
    for effect_yaml in effects_yaml:
        name = str(effect_yaml.get("name", f"{len(effects):02X}"))
        effects.append(
            Effect(
                name=name,
                args=effect_yaml.get("args", ""),
                gfx=effect_yaml.get("gfx", name),
                empty="name" not in effect_yaml,
                returns_void=effect_yaml.get("void", False),
            )
        )

    return effects
