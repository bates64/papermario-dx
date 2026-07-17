# Registries

The YAML files in this directory are used to automatically generate tables and enums related to various game systems:

| Registry | Generates |
| --- | --- |
| `actions.yaml` | [`action_state_enum.h`](../../ver/us/build/include/action_state_enum.h) : The `ActionStates` enum.<br>[`action_data.inc.c`](../../ver/us/build/include/action_data.inc.c) : Table mapping each ActionState to an overlay + entrypoint |
| `actors.yaml` | [`battle/actor_types.h`](../../ver/us/build/include/battle/actor_types.h) : The `ActorTypes` enum and actor levels.<br>[`battle/actor_types.inc.c`](../../ver/us/build/include/battle/actor_types.inc.c) : Actor name, tattle, sound, and offset tables. |
| `effects.yaml` | [`effect_defs.h`](../../assets/us/effects/effect_defs.h) : Effect IDs and effect-spawning c signatures.<br>[`effect_table.c`](../../assets/us/effects/effect_table.c) : Table mapping effect IDs to overlays and runtime argcount table. |
| `items.yaml` | [`item_enum.h`](../../ver/us/build/include/item_enum.h) : The `ItemIDs` enum.<br>[`item_data.inc.c`](../../ver/us/build/include/item_data.inc.c) : The item table, along with HudScripts, ItemScripts, and icon data for each item. |
| `moves.yaml` | [`move_enum.h`](../../ver/us/build/include/move_enum.h) : The `MoveIDs` enum.<br>[`move_data.inc.c`](../../ver/us/build/include/move_data.inc.c) : The move data table. |
| `recipes.yaml` | [`recipes.inc.c`](../../ver/us/build/include/recipes.inc.c) : Cooking ingredient and result tables. |

## Note About Overlays

Not every overlay type is registered here. The build intentionally derives overlay boundaries in three different ways, according to what defines the module:

- Maps and battle actors use their source directory as the boundary.
- Actions and effects use registries because their logical IDs bind directly to overlay implementations.
- World partners use their splat vram class. Partner IDs describe a broader game concept than merely a world implementation, so we let splat define the members of the class and map them manually with a table.
