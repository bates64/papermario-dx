from dataclasses import dataclass
from pathlib import Path
from typing import List, Optional

import yaml as yaml_loader


@dataclass
class Effect:
    name: str
    args: str
    gfx: Optional[str]
    empty: bool
    returns_void: bool

    @property
    def arg_count(self) -> int:
        return len([arg for arg in self.args.split(",") if arg.strip()])

    @property
    def enum_name(self) -> str:
        name = self.name.upper()
        if not name.startswith("EFFECT_"):
            name = "EFFECT_" + name
        return name

    def get_decl(self, func_name: str) -> str:
        ret_type = "void" if self.returns_void else "EffectInstance*"

        return f"{ret_type} {func_name}({self.args})"


def effects_from_yaml(yaml_path: Path) -> List[Effect]:
    with open(yaml_path) as f:
        effects_yaml = yaml_loader.load(f.read(), Loader=yaml_loader.SafeLoader)

    effects: List[Effect] = []
    for effect_yaml in effects_yaml:
        name = str(effect_yaml.get("name", f"{len(effects):02X}"))
        gfx = effect_yaml.get("gfx", name)
        if gfx == "None":
            gfx = None
        elif gfx is not None and not isinstance(gfx, str):
            raise ValueError(f"effect {name} has invalid gfx {gfx!r}")

        effects.append(
            Effect(
                name=name,
                args=effect_yaml.get("args", ""),
                gfx=gfx,
                empty="name" not in effect_yaml,
                returns_void=effect_yaml.get("void", False),
            )
        )

    return effects
