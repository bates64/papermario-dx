#pragma once

#include "common.h"
#include "battle/battle.h"
#include "dx/versioning.h"
#include "dx/config.h"

#ifdef _LANGUAGE_C_PLUS_PLUS
extern "C" {
#endif

/// Starts a battle, such as "kmr_part_1:goomba_2", against a stand-in enemy
/// with NPC ID DX_DEBUG_DUMMY_ID. A null stage uses the battle's own. Both
/// strings must outlive the battle's loading. Set `restarting` to replace a
/// battle that has just ended.
void dx_begin_battle(const char* battle, const char* stage, b32 restarting);

/// Loads gSaveBootRecord's file, or starts a new game. Returns false if the
/// file can't be loaded.
b32 dx_boot_from_record(void);

/// Whether the first map load starts at the boot record's entrance. If so,
/// sets gGameStatus's map and entrance to it.
b32 dx_boot_use_entrance(void);

/// Whether the world is loading only for the boot record's battle to return to.
b32 dx_boot_enters_battle(void);

/// Starts the boot record's battle, once, as the world starts.
void dx_boot_start_battle(void);

/// Restarts the boot record's battle when it ends, if the record asks to.
void dx_boot_on_battle_end(void);

/// The formation to load from `area`. For the boot record's lone actor, the
/// area's first battle stands in.
const char* dx_boot_resolve_battle(const BattleArea* area, const char* formation);

#if DX_DEBUG_MENU
/// Saves the current file and makes the game boot back into it. In a battle,
/// it saves the player's data from the battle's start, and boots into the
/// battle.
void dx_quick_save(void);

/// Records the player's data as a battle begins, for a quick save during it.
void dx_boot_on_battle_start(void);
#endif

#ifdef _LANGUAGE_C_PLUS_PLUS
}
#endif
