#include "common.h"
#include "battle/battle.h"
#include "battle/script_module.h"
#include "dx/overlay.h"

#define MOVE_SCRIPT(name, entry) \
    { "battle_move_" name, BATTLE_SCRIPT_KIND_MOVE, entry }

static const BattleScriptRef gMoveScriptTable[] = {
    [MOVE_NONE]                 {},
    [MOVE_UNUSED_01]            {},
    [MOVE_UNUSED_02]            {},
    [MOVE_HAMMER1]              MOVE_SCRIPT("hammer_attack", 0),
    [MOVE_HAMMER2]              MOVE_SCRIPT("hammer_attack", 0),
    [MOVE_HAMMER3]              MOVE_SCRIPT("hammer_attack", 0),
    [MOVE_FIRST_STRIKE_HAMMER]  MOVE_SCRIPT("hammer_attack", 1),
    [MOVE_BERSERKER_HAMMER]     MOVE_SCRIPT("hammer_attack", 2),
    [MOVE_SPIN_SMASH]           MOVE_SCRIPT("spin_smash", 0),
    [MOVE_QUAKE_HAMMER]         MOVE_SCRIPT("quake_hammer", 0),
    [MOVE_D_DOWN_POUND]         MOVE_SCRIPT("d_down_pound", 0),
    [MOVE_SMASH_CHARGE0]        MOVE_SCRIPT("hammer_charge_0", 0),
    [MOVE_UNUSED_HAMMER_0C]     MOVE_SCRIPT("hammer_charge_0", 1),
    [MOVE_HAMMER_THROW]         MOVE_SCRIPT("hammer_throw", 0),
    [MOVE_MEGA_QUAKE]           MOVE_SCRIPT("mega_quake", 0),
    [MOVE_SMASH_CHARGE]         MOVE_SCRIPT("hammer_charge_1", 0),
    [MOVE_UNUSED_HAMMER_10]     MOVE_SCRIPT("hammer_charge_1", 1),
    [MOVE_SUPER_SMASH_CHARGE]   MOVE_SCRIPT("hammer_charge_2", 0),
    [MOVE_UNUSED_HAMMER_12]     MOVE_SCRIPT("hammer_charge_2", 1),
    [MOVE_AUTO_SMASH]           MOVE_SCRIPT("auto_smash", 0),
    [MOVE_POWER_QUAKE]          MOVE_SCRIPT("power_quake", 0),
    [MOVE_POWER_SMASH]          MOVE_SCRIPT("power_smash", 0),
    [MOVE_SUPER_SMASH]          MOVE_SCRIPT("super_smash", 0),
    [MOVE_MEGA_SMASH]           MOVE_SCRIPT("mega_smash", 0),
    [MOVE_SHRINK_SMASH]         MOVE_SCRIPT("shrink_smash", 0),
    [MOVE_SHELL_CRACK]          MOVE_SCRIPT("shell_crack", 0),
    [MOVE_JUMP1]                MOVE_SCRIPT("jump_attack", 0),
    [MOVE_JUMP2]                MOVE_SCRIPT("jump_attack", 0),
    [MOVE_JUMP3]                MOVE_SCRIPT("jump_attack", 0),
    [MOVE_FIRST_STRIKE_JUMP]    MOVE_SCRIPT("jump_attack", 1),
    [MOVE_BERSERKER_JUMP]       MOVE_SCRIPT("jump_attack", 2),
    [MOVE_MULTIBOUNCE]          MOVE_SCRIPT("multibounce", 0),
    [MOVE_POWER_BOUNCE]         MOVE_SCRIPT("power_bounce", 0),
    [MOVE_SLEEP_STOMP]          MOVE_SCRIPT("sleep_stomp", 0),
    [MOVE_DIZZY_STOMP]          MOVE_SCRIPT("dizzy_stomp", 0),
    [MOVE_JUMP_CHARGE0]         MOVE_SCRIPT("jump_charge_0", 0),
    [MOVE_UNUSED_24]            MOVE_SCRIPT("jump_charge_0", 1),
    [MOVE_JUMP_CHARGE]          MOVE_SCRIPT("jump_charge_1", 0),
    [MOVE_UNUSED_26]            MOVE_SCRIPT("jump_charge_1", 1),
    [MOVE_SUPER_JUMP_CHARGE]    MOVE_SCRIPT("jump_charge_2", 0),
    [MOVE_UNUSED_28]            MOVE_SCRIPT("jump_charge_2", 1),
    [MOVE_AUTO_JUMP]            MOVE_SCRIPT("auto_jump", 0),
    [MOVE_AUTO_MULTIBOUNCE]     MOVE_SCRIPT("auto_multibounce", 0),
    [MOVE_POWER_JUMP]           MOVE_SCRIPT("power_jump", 0),
    [MOVE_SUPER_JUMP]           MOVE_SCRIPT("super_jump", 0),
    [MOVE_MEGA_JUMP]            MOVE_SCRIPT("mega_jump", 0),
    [MOVE_D_DOWN_JUMP]          MOVE_SCRIPT("d_down_jump", 0),
    [MOVE_SHRINK_STOMP]         MOVE_SCRIPT("shrink_stomp", 0),
    [MOVE_EARTHQUAKE_JUMP]      MOVE_SCRIPT("earthquake_jump", 0),
};

static Overlay* LoadedBattleScriptOverlay;
static const BattleScriptModule* LoadedBattleScriptModule;
static const char* LoadedBattleScriptName;

void unload_battle_script(void) {
    ovl_unload(LoadedBattleScriptOverlay);
    LoadedBattleScriptOverlay = nullptr;
    LoadedBattleScriptModule = nullptr;
    LoadedBattleScriptName = nullptr;
}

EvtScript* load_battle_script(const BattleScriptRef* ref) {
    ASSERT_MSG(ref != nullptr && ref->overlayName != nullptr, "Invalid battle script reference");

    if (LoadedBattleScriptModule == nullptr || strcmp(LoadedBattleScriptName, ref->overlayName) != 0) {
        unload_battle_script();
        LoadedBattleScriptOverlay = ovl_load(ref->overlayName, OVL_BATTLE_SCRIPT);
        LoadedBattleScriptName = ref->overlayName;
        LoadedBattleScriptModule = ovl_import(LoadedBattleScriptOverlay, BATTLE_SCRIPT_EXPORT_NAME);
        ASSERT_MSG(LoadedBattleScriptModule != nullptr,
                   "Battle script overlay '%s' has no %s export",
                   ref->overlayName, BATTLE_SCRIPT_EXPORT_NAME);
        ASSERT_MSG(LoadedBattleScriptModule->entryCount > 0 &&
                   LoadedBattleScriptModule->entryScripts != nullptr,
                   "Battle script overlay '%s' has no entries", ref->overlayName);
    }

    ASSERT_MSG(LoadedBattleScriptModule->kind == ref->kind,
               "Battle script overlay '%s' has kind %d, expected %d",
               ref->overlayName, (int)LoadedBattleScriptModule->kind, (int)ref->kind);
    ASSERT_MSG((u32)ref->entryIndex < (u32)LoadedBattleScriptModule->entryCount,
               "Battle script overlay '%s' has no entry %d",
               ref->overlayName, (int)ref->entryIndex);
    ASSERT_MSG(LoadedBattleScriptModule->entryScripts[ref->entryIndex] != nullptr,
               "Battle script overlay '%s' entry %d is null",
               ref->overlayName, (int)ref->entryIndex);
    return LoadedBattleScriptModule->entryScripts[ref->entryIndex];
}

API_CALLABLE(LoadMoveScript) {
    BattleStatus* battleStatus = &gBattleStatus;
    const BattleScriptRef* moveScript;

    ASSERT_MSG((u32)battleStatus->selectedMoveID < ARRAY_COUNT(gMoveScriptTable),
               "Invalid move ID %d", (int)battleStatus->selectedMoveID);
    moveScript = &gMoveScriptTable[battleStatus->selectedMoveID];
    ASSERT_MSG(moveScript->overlayName != nullptr,
               "Move ID %d has no battle script", (int)battleStatus->selectedMoveID);
    script->varTablePtr[0] = load_battle_script(moveScript);

    deduct_current_move_fp();

    if (gBattleStatus.flags2 & BS_FLAGS2_HAS_RUSH) {
        enable_player_blur();
    }

    return ApiStatus_DONE2;
}
