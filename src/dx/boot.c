#include "dx/boot.h"
#include "dx/config.h"
#include "fio.h"
#include "game_modes.h"
#include <string.h>

/// Whether the game booted into gSaveBootRecord.
b32 BootRecordActive;
/// Whether the boot record's entrance has been used.
b32 BootEntranceUsed;
/// Whether the boot record's battle has started.
b32 BootBattleStarted;
/// Whether the battle loading is the boot record's.
b32 BootBattleLoading;

/// The boot record's battle and stage, as dx_begin_battle takes them.
char BootBattleRef[BATTLE_REF_MAX];
char BootStageName[sizeof(gSaveBootRecord.stage) + 1];
char BootActorName[sizeof(gSaveBootRecord.actor) + 1];

FormationRow BootActorFormation[1];
Battle BootActorBattle = {
    .formationSize = ARRAY_COUNT(BootActorFormation),
    .formation = (Formation*) BootActorFormation,
};

EnemyDrops DebugDummyDrops = NO_DROPS;

Enemy DebugDummyEnemy = {
    .npcID = DX_DEBUG_DUMMY_ID,
    .drops = &DebugDummyDrops,
};

Encounter DebugDummyEncounter = {
    .encounterID = DX_DEBUG_DUMMY_ID,
    .enemy = { &DebugDummyEnemy },
    .count = 0,
    .battle = nullptr,
    .stage = nullptr,
};

// skips fading out the world before a battle
static void begin_battle_from_black(void) {
    gEncounterSubState = ENCOUNTER_SUBSTATE_PRE_BATTLE_RESTART;
    gCurrentEncounter.fadeOutAmount = 255;
    set_screen_overlay_color(SCREEN_LAYER_FRONT, 0, 0, 0);
    set_screen_overlay_params_front(OVERLAY_SCREEN_COLOR, 255.0f);
}

void dx_begin_battle(const char* battle, const char* stage, b32 restarting) {
    EncounterStatus* es = &gCurrentEncounter;

    DebugDummyEncounter.battle = battle;
    DebugDummyEncounter.stage = stage;

    es->curEncounter = &DebugDummyEncounter;
    es->curEnemy = &DebugDummyEnemy;
    es->hitType = ENCOUNTER_TRIGGER_NONE;
    es->firstStrikeType = FIRST_STRIKE_NONE;
    es->forbidFleeing = false;
    es->scriptedBattle = true;
    es->songID = -1;
    es->unk_18 = -1;
    es->fadeOutAmount = 0;
    es->substateDelay = 0;

    // A replacement battle inherits the encounter's existing input locks.
    // The final post-battle cleanup releases them once for the whole chain.
    if (!restarting) {
        disable_player_input();
        partner_disable_input();
    }

    gEncounterState = ENCOUNTER_STATE_PRE_BATTLE;
    gEncounterSubState = ENCOUNTER_SUBSTATE_PRE_BATTLE_INIT;
    if (restarting) {
        // Restoring world resources is necessary for teardown, but there is no
        // need to show the world or push its music again between battles.
        begin_battle_from_black();
    }
    EncounterStateChanged = true;
}

// copies a boot record name, which has no terminator when it fills its field
static void copy_record_name(char* dest, const char* name, s32 size) {
    s32 i;

    for (i = 0; i < size && name[i] != '\0'; i++) {
        dest[i] = name[i];
    }
    dest[i] = '\0';
}

// starts a new game, saved to the first empty file, or the first file if none is
void boot_new_game(void) {
    s32 slot = fio_find_empty_slot();
    s32 i;

    if (slot < 0) {
        slot = 0;
    }

    clear_player_data();
    clear_saved_variables();
    get_map_IDs_by_name_checked(NEW_GAME_MAP_ID, &gGameStatus.areaID, &gGameStatus.mapID);
    gGameStatus.entryID = NEW_GAME_ENTRY_ID;
    evt_set_variable(nullptr, GB_StoryProgress, NEW_GAME_STORY_PROGRESS);

    for (i = 0; i < ARRAY_COUNT(gSaveSlotSummary[slot].filename); i++) {
        gSaveSlotSummary[slot].filename[i] = MSG_CHAR_READ_SPACE;
    }
    fio_save_game(slot);

    // fio_save_game resets bootTo
    gSaveBootRecord.baseSlot = slot;
    gSaveGlobals.bootTo = BOOT_TO_RECORD;
    fio_save_globals();
}

b32 dx_boot_from_record(void) {
    if (gSaveBootRecord.baseSlot < 0) {
        boot_new_game();
    } else if (!fio_load_game(gSaveBootRecord.baseSlot)) {
        return false;
    }

    BootRecordActive = true;
    BootEntranceUsed = false;
    BootBattleStarted = false;
    return true;
}

b32 dx_boot_use_entrance(void) {
    if (!BootRecordActive || BootEntranceUsed || gSaveBootRecord.start != BOOT_START_ENTRANCE) {
        return false;
    }
    // later map loads, such as after a game over, start where the game was saved
    BootEntranceUsed = true;
    get_map_IDs_by_name_checked(gSaveBootRecord.map, &gGameStatus.areaID, &gGameStatus.mapID);
    gGameStatus.entryID = gSaveBootRecord.entryID;
    return true;
}

void boot_begin_battle(void) {
    SaveBootRecord* record = &gSaveBootRecord;
    char* variant;
    s32 length;

    copy_record_name(BootBattleRef, record->battleArea, sizeof(record->battleArea));
    length = strlen(BootBattleRef);
    BootBattleRef[length++] = ':';
    if (record->battle[0] != '\0') {
        copy_record_name(&BootBattleRef[length], record->battle, sizeof(record->battle));
    } else {
        // dx_boot_resolve_battle stands in a battle for a lone actor, named for its overlay without the variant
        copy_record_name(&BootBattleRef[length], record->actor, sizeof(record->actor));
        variant = strchr(&BootBattleRef[length], ':');
        if (variant != nullptr) {
            *variant = '\0';
        }
    }
    copy_record_name(BootStageName, record->stage, sizeof(record->stage));

    BootBattleLoading = true;
    dx_begin_battle(BootBattleRef, BootStageName[0] != '\0' ? BootStageName : nullptr, false);
    // the world is only there for the battle to return to
    begin_battle_from_black();
}

b32 dx_boot_enters_battle(void) {
    return BootRecordActive && gSaveBootRecord.start == BOOT_START_BATTLE && !BootBattleStarted;
}

void dx_boot_start_battle(void) {
    if (BootRecordActive && gSaveBootRecord.start == BOOT_START_BATTLE && !BootBattleStarted) {
        BootBattleStarted = true;
        boot_begin_battle();
    }
}

void dx_boot_on_battle_end(void) {
    if (BootBattleStarted && gSaveBootRecord.onBattleEnd == BOOT_BATTLE_END_RESTART) {
        boot_begin_battle();
    }
}

const char* dx_boot_resolve_battle(const BattleArea* area, const char* formation) {
    Battle* standIn;

    if (!BootBattleLoading) {
        return formation;
    }
    BootBattleLoading = false;
    if (gSaveBootRecord.battle[0] != '\0') {
        return formation;
    }

    ASSERT_MSG(area->battleCount > 0, "No battle to fight %s in", gCurrentBattleName);
    standIn = &(*area->battles)[0];
    copy_record_name(BootActorName, gSaveBootRecord.actor, sizeof(gSaveBootRecord.actor));
    BootActorFormation[0] = (FormationRow) {
        .overlay = BootActorName,
        .home = { .index = BTL_POS_GROUND_B },
        .priority = 10,
    };
    BootActorBattle.name = standIn->name;
    BootActorBattle.stage = standIn->stage;
    gOverrideBattlePtr = &BootActorBattle;
    return standIn->name;
}

#if DX_DEBUG_MENU

/// Set to ask for a quick save once dx_can_quick_save allows. Cleared once
/// it's made.
u8 gQuickSaveRequested;

/// The player's data at the battle's start, which a quick save in a battle saves.
PlayerData BattleStartPlayerData;
PlayerData BattleCurrentPlayerData;

void dx_boot_on_battle_start(void) {
    BattleStartPlayerData = gPlayerData;
}

// stores a name in a boot record field, which holds it without a terminator when it fills the field; false if it's too long
static b32 store_record_name(char* field, s32 size, const char* name) {
    s32 length = strlen(name);

    if (length > size) {
        return false;
    }
    memcpy(field, name, length);
    bzero(field + length, size - length);
    return true;
}

// makes the boot record start the current battle, unless a name in it is too long for the record
void boot_record_current_battle(void) {
    SaveBootRecord battle = gSaveBootRecord;
    char area[BATTLE_KEY_MAX];
    const char* formation = split_battle_ref(gCurrentBattleName, area);
    b32 stored;

    if (gOverrideBattlePtr == &BootActorBattle) {
        stored = store_record_name(battle.actor, sizeof(battle.actor), BootActorName);
    } else {
        stored = store_record_name(battle.battle, sizeof(battle.battle), formation);
    }
    if (stored
        && store_record_name(battle.battleArea, sizeof(battle.battleArea), area)
        && store_record_name(battle.stage, sizeof(battle.stage), gCurrentStageName)) {
        battle.start = BOOT_START_BATTLE;
        gSaveBootRecord = battle;
    }
}

void dx_quick_save(void) {
    b32 inBattle = gGameStatusPtr->context == CONTEXT_BATTLE;

    gGameStatusPtr->savedPos.x = gPlayerStatusPtr->pos.x;
    gGameStatusPtr->savedPos.y = gPlayerStatusPtr->pos.y;
    gGameStatusPtr->savedPos.z = gPlayerStatusPtr->pos.z;
    if (inBattle) {
        BattleCurrentPlayerData = gPlayerData;
        gPlayerData = BattleStartPlayerData;
    }
    fio_save_game(gGameStatusPtr->saveSlot);
    if (inBattle) {
        gPlayerData = BattleCurrentPlayerData;
    }

    bzero(&gSaveBootRecord, sizeof(gSaveBootRecord));
    gSaveBootRecord.baseSlot = gGameStatusPtr->saveSlot;
    if (inBattle) {
        boot_record_current_battle();
    }
    // fio_save_game has just set the game to boot normally
    gSaveGlobals.bootTo = BOOT_TO_RECORD;
    fio_save_globals();
}

b32 dx_can_quick_save(void) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    s32 actionState = playerStatus->actionState;

    if (gGameStatusPtr->context == CONTEXT_BATTLE) {
        // the battle restarts from its beginning, so only its start and end are unsafe
        return get_game_mode() == GAME_MODE_BATTLE
            && gBattleState >= BATTLE_STATE_FIRST_STRIKE
            && gBattleState <= BATTLE_STATE_DEFEND;
    }

    // as for opening the pause menu, which only a player in control can do
    return get_game_mode() == GAME_MODE_WORLD
        && playerStatus->inputDisabledCount == 0
        && !(playerStatus->animFlags & PA_FLAG_CHANGING_MAP)
        && !(playerStatus->flags & (PS_FLAG_PAUSE_DISABLED | PS_FLAG_NO_STATIC_COLLISION))
        && !(gOverrideFlags & GLOBAL_OVERRIDES_DISABLE_MENUS)
        && !is_picking_up_item()
        && gPartnerStatus.partnerActionState == PARTNER_ACTION_NONE
        && (actionState == ACTION_STATE_IDLE || actionState == ACTION_STATE_WALK || actionState == ACTION_STATE_RUN);
}

void dx_boot_update(void) {
    if (gQuickSaveRequested && dx_can_quick_save()) {
        dx_quick_save();
        gQuickSaveRequested = false;
    }
}

#endif
