#include "common.h"
#include "ld_addrs.h"
#include "battle/battle.h"
#include "hud_element.h"
#include "sprite.h"
#include "game_modes.h"
#include "battle/states/states.h"
#include "dx/overlay.h"

BSS s32 gBattleState;
BSS BattleStatus gBattleStatus;
BSS s32 gLastDrawBattleState;
BSS s32 gDefeatedBattleSubstate;
BSS s32 gBattleSubState;
BSS s32 gDefeatedBattleState;
// Own these strings across world teardown and temporary debug previews.
char gCurrentBattleName[BATTLE_REF_MAX];
char gCurrentStageName[BATTLE_KEY_MAX];
BSS Battle* gOverrideBattlePtr;
BSS Battle* gCurrentBattlePtr;

// Kept in resident code: the battle segment's BSS is not cleared on DMA load.
static Overlay* LoadedBattleStageOverlay;
static Overlay* LoadedBattleAreaOverlay;
static const BattleArea* LoadedBattleArea;

Stage* load_battle_stage(const char* overlayName) {
    Stage* stage;

    ASSERT_MSG(overlayName != nullptr, "Battle has no stage overlay");
    ASSERT_MSG(LoadedBattleStageOverlay == nullptr, "Previous battle stage was not unloaded");
    LoadedBattleStageOverlay = ovl_load(overlayName, OVL_STAGE);
    stage = ovl_import(LoadedBattleStageOverlay, BATTLE_STAGE_EXPORT_NAME);
    ASSERT_MSG(stage != nullptr, "Stage overlay '%s' has no %s export", overlayName, BATTLE_STAGE_EXPORT_NAME);
    gBattleStatus.curStage = stage;
    return stage;
}

void unload_battle_stage(void) {
    // Stages can also own model graphics callbacks, not just scripts and actors.
    // Callers wait until the renderer has switched away from battle models.
    gBattleStatus.curStage = nullptr;
    ovl_unload(LoadedBattleStageOverlay);
    LoadedBattleStageOverlay = nullptr;
}

void reset_battle_status(void) {
    gGameStatusPtr->demoBattleFlags = 0;
    gBattleState = BATTLE_STATE_NONE;
    gBattleSubState = BTL_SUBSTATE_INIT;
    gLastDrawBattleState = BATTLE_STATE_NONE;
    gCurrentBattlePtr = nullptr;
    gCurrentBattleName[0] = '\0';
    gCurrentStageName[0] = '\0';
    gOverrideBattlePtr = nullptr;
}

const char* split_battle_ref(const char* ref, char area[BATTLE_KEY_MAX]) {
    const char* separator;
    const char* p;
    s32 areaLength;

    if (ref == nullptr || (separator = strchr(ref, ':')) == nullptr) {
        return nullptr;
    }
    areaLength = separator - ref;
    if (areaLength == 0 || areaLength >= BATTLE_KEY_MAX
        || separator[1] == '\0' || strlen(separator + 1) >= BATTLE_KEY_MAX) {
        return nullptr;
    }
    for (p = ref; *p != '\0'; p++) {
        if (p != separator && !((*p >= 'a' && *p <= 'z')
            || (*p >= '0' && *p <= '9') || *p == '_')) {
            return nullptr;
        }
    }
    memcpy(area, ref, areaLength);
    area[areaLength] = '\0';
    return separator + 1;
}

void load_battle_section(void) {
    char areaName[BATTLE_KEY_MAX];
    const char* formation = split_battle_ref(gCurrentBattleName, areaName);
    const BattleArea* battleArea;
    s32 i;

    ASSERT_MSG(formation != nullptr, "Invalid battle reference '%s'", gCurrentBattleName);
    ASSERT_MSG(LoadedBattleAreaOverlay == nullptr, "Previous battle area was not unloaded");
    LoadedBattleAreaOverlay = ovl_load(areaName, OVL_BATTLE_AREA);
    battleArea = ovl_import(LoadedBattleAreaOverlay, BATTLE_AREA_EXPORT_NAME);
    ASSERT_MSG(battleArea != nullptr, "Area overlay '%s' has no %s export", areaName, BATTLE_AREA_EXPORT_NAME);
    LoadedBattleArea = battleArea;
    gCurrentBattlePtr = nullptr;
    for (i = 0; i < battleArea->battleCount; i++) {
        Battle* battle = &(*battleArea->battles)[i];
        if (strcmp(battle->name, formation) == 0) {
            ASSERT_MSG(gCurrentBattlePtr == nullptr, "Duplicate battle '%s'", gCurrentBattleName);
            gCurrentBattlePtr = battle;
        }
    }
    ASSERT_MSG(gCurrentBattlePtr != nullptr, "Unknown battle '%s'", gCurrentBattleName);

    btl_set_state(BATTLE_STATE_START);
    gLastDrawBattleState = BATTLE_STATE_NONE;
}

const BattleArea* get_loaded_battle_area(void) {
    return LoadedBattleArea;
}

void unload_battle_area(void) {
    gCurrentBattlePtr = nullptr;
    gOverrideBattlePtr = nullptr;
    LoadedBattleArea = nullptr;
    ovl_unload(LoadedBattleAreaOverlay);
    LoadedBattleAreaOverlay = nullptr;
}

void load_battle(const char* battle, const char* stage) {
    char area[BATTLE_KEY_MAX];

    ASSERT_MSG(split_battle_ref(battle, area) != nullptr, "Invalid battle reference");
    ASSERT_MSG(stage == nullptr || (stage[0] != '\0' && strlen(stage) < BATTLE_KEY_MAX),
               "Invalid stage override");
    // memmove also permits restarting the current battle using these buffers.
    memmove(gCurrentBattleName, battle, strlen(battle) + 1);
    if (stage != nullptr) {
        memmove(gCurrentStageName, stage, strlen(stage) + 1);
    } else {
        gCurrentStageName[0] = '\0';
    }
    set_game_mode(GAME_MODE_BATTLE);
    gBattleState = BATTLE_STATE_NONE;
    gLastDrawBattleState = BATTLE_STATE_NONE;
    gBattleSubState = BTL_SUBSTATE_INIT;
}

void set_battle_formation(Battle* battle) {
    gOverrideBattlePtr = battle;
}

void setup_demo_player(void) {
    PlayerData* playerData = &gPlayerData;
    s32 i;

    playerData->curHP = 15;
    playerData->curMaxHP = 15;
    playerData->hardMaxHP = 15;
    playerData->curFP = 10;
    playerData->curMaxFP = 10;
    playerData->hardMaxFP = 10;
    playerData->level = 3;
    playerData->hasActionCommands = true;
    playerData->starPoints = 55;
    playerData->bootsLevel = GEAR_RANK_NORMAL;
    playerData->hammerLevel = GEAR_RANK_NORMAL;
    playerData->coins = 34;

    for (i = 1; i < ARRAY_COUNT(playerData->partners); i++) {
        playerData->partners[i].enabled = true;
        playerData->partners[i].level = 2;
    }

    playerData->curPartner = PARTNER_GOOMBARIO;

    for (i = 0; i < ARRAY_COUNT(playerData->badges); i++) {
        playerData->badges[i] = ITEM_NONE;
    }

    for (i = 0; i < ARRAY_COUNT(playerData->equippedBadges); i++) {
        playerData->equippedBadges[i] = ITEM_NONE;
    }

    for (i = 0; i < ARRAY_COUNT(playerData->invItems); i++) {
        playerData->invItems[i] = ITEM_NONE;
    }

    playerData->unused_288 = 0;
    playerData->merleeSpellType = MERLEE_SPELL_NONE;
    playerData->merleeCastsLeft = 0;
    playerData->merleeTurnCount = 0;
    playerData->maxStarPower = 0;
    playerData->starPower = 0;
    playerData->starBeamLevel = 0;
}

void load_demo_battle(u32 index) {
    PlayerData* playerData = &gPlayerData;
    u32 mode;
    const char* battle;

    gGameStatusPtr->demoBattleFlags = 0;
    gGameStatusPtr->areaID = 0;
    gGameStatusPtr->mapID = 0;
    gGameStatusPtr->context = CONTEXT_WORLD;

    general_heap_create();
    clear_worker_list();
    clear_script_list();
    create_cameras();
    spr_init_sprites(PLAYER_SPRITES_MARIO_WORLD);
    clear_animator_list();
    clear_entity_models();
    clear_npcs();
    hud_element_clear_cache();
    clear_trigger_data();
    clear_model_data();
    clear_sprite_shading_data();
    reset_background_settings();
    reset_back_screen_overlay_progress();
    reset_battle_status();
    clear_encounter_status();
    clear_entity_data(true);
    clear_effect_data();
    clear_player_status();
    clear_printers();
    clear_item_entity_data();
    clear_player_data();
    initialize_status_bar();
    clear_item_entity_data();
    set_screen_overlay_params_front(OVERLAY_TYPE_9, 255.0f);

    switch (index) {
        case 0: // hammer first strike on Fuzzies
            setup_demo_player();
            mode = 0;
            playerData->hasActionCommands = false;
            battle = "dig:demo_01";
            break;
        case 1: // jump on Monty Mole
            setup_demo_player();
            mode = 0;
            playerData->curPartner = PARTNER_BOW;
            battle = "dig:demo_02";
            break;
        case 2: // Parakarry shell shot against Pokey
            setup_demo_player();
            mode = 0;
            playerData->curPartner = PARTNER_PARAKARRY;
            gGameStatusPtr->demoBattleFlags |= DEMO_BTL_FLAG_PARTNER_ACTING;
            battle = "dig:demo_03";
            break;
        case 3: // Thunder Rage on Shy Guys at the slot machine
            setup_demo_player();
            mode = 0;
            playerData->curPartner = PARTNER_WATT;
            battle = "dig:demo_04";
            break;
        case 4: // stomped by Tubba Blubba
            setup_demo_player();
            mode = 0;
            playerData->curPartner = PARTNER_KOOPER;
            gGameStatusPtr->demoBattleFlags |= DEMO_BTL_FLAG_ENEMY_ACTING;
            battle = "dig:demo_05";
            break;
        default:
            setup_demo_player();
            mode = 2;
            battle = "dig:demo_01";
    }

    gGameStatusPtr->debugEnemyContact = DEBUG_CONTACT_NONE;
    gGameStatusPtr->healthBarsEnabled = true;

    switch (mode) {
        case 0:
            gCurrentEncounter.firstStrikeType = FIRST_STRIKE_NONE;
            gCurrentEncounter.hitType = ENCOUNTER_TRIGGER_NONE;
            gCurrentEncounter.hitTier = 0;
            gGameStatusPtr->demoBattleFlags |= DEMO_BTL_FLAG_10;
            gGameStatusPtr->demoBattleFlags |= DEMO_BTL_FLAG_20;
            gGameStatusPtr->demoBattleFlags |= DEMO_BTL_FLAG_40;
            break;
        case 1:
            gCurrentEncounter.firstStrikeType = FIRST_STRIKE_PLAYER;
            gCurrentEncounter.hitType = ENCOUNTER_TRIGGER_HAMMER;
            gCurrentEncounter.hitTier = playerData->hammerLevel;
            gGameStatusPtr->demoBattleFlags |= DEMO_BTL_FLAG_10;
            break;
        case 2:
            gCurrentEncounter.firstStrikeType = FIRST_STRIKE_PLAYER;
            gCurrentEncounter.hitType = ENCOUNTER_TRIGGER_JUMP;
            gCurrentEncounter.hitTier = playerData->bootsLevel;
            gGameStatusPtr->demoBattleFlags |= DEMO_BTL_FLAG_10;
            break;
        case 3:
            gCurrentEncounter.firstStrikeType = FIRST_STRIKE_PLAYER;
            gCurrentEncounter.hitType = ENCOUNTER_TRIGGER_PARTNER;
            gGameStatusPtr->demoBattleFlags |= DEMO_BTL_FLAG_20;
            break;
        case 4:
            gCurrentEncounter.firstStrikeType = FIRST_STRIKE_ENEMY;
            gCurrentEncounter.hitType = ENCOUNTER_TRIGGER_NONE;
            gCurrentEncounter.hitTier = 0;
            gGameStatusPtr->demoBattleFlags |= DEMO_BTL_FLAG_40;
            break;
    }

    evt_set_variable(nullptr, GF_Tutorial_SwapTurnOrder, true);
    gCurrentEncounter.unk_07 = 0;
    gCurrentEncounter.instigatorValue = 0;
    gGameStatusPtr->demoBattleFlags |= DEMO_BTL_FLAG_ENABLED;
    gOverrideFlags &= ~GLOBAL_OVERRIDES_DISABLE_DRAW_FRAME;
    load_battle(battle, nullptr);
}
