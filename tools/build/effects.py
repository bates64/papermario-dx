import argparse
from pathlib import Path

from effect_data import effects_from_yaml


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Builds effect table, function declarations, and enum")
    parser.add_argument("in_yaml")
    parser.add_argument("out_dir", type=Path)
    args = parser.parse_args()

    effect_enum_text = "enum EffectID {\n"
    effect_table_text = "EffectTableEntry gEffectTable[] = {\n"
    effect_arg_counts_text = "const u8 gEffectArgCounts[] = {\n"
    fx_decls_text = ""

    effects = effects_from_yaml(args.in_yaml)

    for i, effect in enumerate(effects):
        effect_enum_text += f"    {effect.enum_name} = 0x{i:02X},\n"
        effect_arg_counts_text += f"    {effect.arg_count},\n"
        if not effect.empty:
            effect_table_text += f"    FX_ENTRY({effect.name}, effect_gfx_{effect.gfx}),\n"
            fx_decls_text += effect.get_decl("fx_" + effect.name) + ";\n"
        else:
            effect_table_text += "    {},\n"

    effect_enum_text += f"    EFFECT_COUNT = 0x{len(effects):02X},\n"
    effect_enum_text += "};\n\n"
    effect_enum_text += f"#define EFFECT_MAX_ARGS {max(effect.arg_count for effect in effects)}\n"

    args.out_dir.mkdir(parents=True, exist_ok=True)

    with open(args.out_dir / "effect_table.c", "w") as f:
        f.write(effect_table_text + "};\n\n" + effect_arg_counts_text + "};\n")

    with open(args.out_dir / "effect_defs.h", "w") as f:
        f.write(effect_enum_text + "\n\n" + fx_decls_text)
