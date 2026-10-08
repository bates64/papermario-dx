# Registries

The YAML files in this directory are ordered lists that the build turns into enums and data tables. Each entry's position is its ID.

| Registry | Generates |
| --- | --- |
| [`actions.yaml`](actions.yaml) | [`action_state_enum.h`](../../ver/us/build/include/action_state_enum.h): The `ActionStates` enum.<br>[`action_data.inc.c`](../../ver/us/build/include/action_data.inc.c): Table mapping each action state to an overlay and entrypoint. |
| [`effects.yaml`](effects.yaml) | [`effect_defs.h`](../../ver/us/build/include/effects/effect_defs.h): Effect IDs and effect-spawning C signatures.<br>[`effect_table.c`](../../ver/us/build/include/effects/effect_table.c): Table mapping effect IDs to overlays, and the runtime argument count table. |
| [`actors.yaml`](actors.yaml) | [`battle/actor_types.h`](../../ver/us/build/include/battle/actor_types.h): The `ActorTypes` enum and actor levels.<br>[`battle/actor_types.inc.c`](../../ver/us/build/include/battle/actor_types.inc.c): Actor name, tattle, sound, and offset tables. |
| [`items.yaml`](items.yaml) | [`item_enum.h`](../../ver/us/build/include/item_enum.h): The `ItemIDs` enum.<br>[`item_data.inc.c`](../../ver/us/build/include/item_data.inc.c): The item table, along with HudScripts, ItemScripts, and icon data for each item. |
| [`moves.yaml`](moves.yaml) | [`move_enum.h`](../../ver/us/build/include/move_enum.h): The `MoveIDs` enum.<br>[`move_data.inc.c`](../../ver/us/build/include/move_data.inc.c): The move data table. |
| [`recipes.yaml`](recipes.yaml) | [`recipes.inc.c`](../../ver/us/build/include/recipes.inc.c): Cooking ingredient and result tables. |
