#include "battle/battle.h"
#include "script_api/battle.h"
#include "dx/overlay.h"
#include "game_modes.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern StageListRow* gCurrentStagePtr;
extern u8* gBattleDmaDest;
extern s32 DebugBattlePreviewBattleCount;
extern s32 DebugBattlePreviewStageCount;
extern s32 DebugBattlePreviewLineCount;
extern char DebugBattlePreviewNames[6][24];
void dx_debug_load_battle_preview(s32 areaID, s32 formationID);
void dx_debug_force_end_battle(void);

GameStatus TestGameStatus;
GameStatus* gGameStatusPtr = &TestGameStatus;

struct Overlay {
    OverlayType type;
    char name[32];
    BattleArea area;
    Stage stage;
    Battle battles[2];
    StageListRow stages[3];
    FormationRow formation[7];
    ActorBlueprint actor;
    DmaTable dma[1];
    char actorNames[7][64];
};

static Overlay* Modules[4];
static s32 Loads;
static s32 Unloads;
static b32 MissingExport;
static b32 GraphicsFinished;
static b32 ScriptsKilled;
static s32 DeletedActors;
static s32 ModuleCleanups;
static s32 TransitionSteps;
static u8* DmaStart;
static u8* DmaEnd;
static void* DmaDest;
static u8 Animation[32];
static u8 AnimationDest[32];
static u8 AnimationOverride[32];

void is_debug_panic(const char* message) {
    fprintf(stderr, "Battle area panic: %s\n", message);
    exit(1);
}

Overlay* ovl_load(const char* name, OverlayType type) {
    s32 i;
    Overlay* overlay;
    Loads++;
    for (i = 0; i < ARRAY_COUNT(Modules); i++) {
        if (Modules[i] != nullptr && Modules[i]->type == type && strcmp(Modules[i]->name, name) == 0) {
            return Modules[i];
        }
    }
    for (i = 0; i < ARRAY_COUNT(Modules); i++) {
        if (Modules[i] == nullptr) {
            break;
        }
    }
    assert(i < ARRAY_COUNT(Modules));
    overlay = Modules[i] = calloc(1, sizeof(*overlay));
    assert(overlay != nullptr);
    overlay->type = type;
    strcpy(overlay->name, name);
    overlay->area = (BattleArea) {
        .battles = (BattleList*) &overlay->battles,
        .stages = (StageList*) &overlay->stages,
        .battleCount = 1,
        .stageCount = 2,
        .dmaTable = overlay->dma,
        .dmaCount = 1,
    };
    overlay->battles[0] = (Battle) {
        .name = "test battle",
        .formationSize = strcmp(name, "kmr_part_1") == 0 ? 2 : 7,
        .formation = (Formation*) &overlay->formation,
        .stage = "kmr_02",
    };
    overlay->stages[0] = (StageListRow) { "first", "kmr_02" };
    overlay->stages[1] = (StageListRow) { "alias", "nok_04" };
    overlay->dma[0] = (DmaTable) { Animation, Animation + sizeof(Animation), AnimationDest };
    for (i = 0; i < ARRAY_COUNT(overlay->formation); i++) {
        sprintf(overlay->actorNames[i], "actor_%d_with_a_very_long_name", (int)i);
        overlay->formation[i].overlay = overlay->actorNames[i];
    }
    overlay->formation[1].overlay = nullptr;
    overlay->formation[1].actor = &overlay->actor;
    return overlay;
}

void* ovl_import(const Overlay* overlay, const char* name) {
    if (overlay->type == OVL_BATTLE_AREA) {
        assert(strcmp(name, BATTLE_AREA_EXPORT_NAME) == 0);
        return MissingExport ? nullptr : (void*)&overlay->area;
    }
    assert(overlay->type == OVL_STAGE);
    assert(strcmp(name, BATTLE_STAGE_EXPORT_NAME) == 0);
    return (void*)&overlay->stage;
}

void ovl_unload(Overlay* overlay) {
    s32 i;
    if (overlay == nullptr) {
        return;
    }
    for (i = 0; i < ARRAY_COUNT(Modules); i++) {
        if (Modules[i] == overlay) {
            Modules[i] = nullptr;
            Unloads++;
            free(overlay);
            return;
        }
    }
    assert(!"Unloading an unowned module");
}

void btl_set_state(s32 state) {
    gBattleState = state;
}

s32 evt_get_variable(Evt* script, EvtVar value) {
    return value;
}

u32 dma_copy(Addr start, Addr end, void* dest) {
    DmaStart = start;
    DmaEnd = end;
    DmaDest = dest;
    return 0;
}

void nuGfxTaskAllEndWait(void) {
    GraphicsFinished = true;
}

void kill_all_scripts(void) {
    assert(GraphicsFinished && get_loaded_battle_area() != nullptr);
    ScriptsKilled = true;
}

void btl_delete_actor(Actor* actor) {
    s32 i;
    assert(ScriptsKilled && get_loaded_battle_area() != nullptr);
    if (actor == nullptr) {
        return;
    }
    DeletedActors++;
    for (i = 0; i < ARRAY_COUNT(gBattleStatus.enemyActors); i++) {
        if (gBattleStatus.enemyActors[i] == actor) {
            gBattleStatus.enemyActors[i] = nullptr;
        }
    }
    if (gBattleStatus.partnerActor == actor) {
        gBattleStatus.partnerActor = nullptr;
    }
}

void btl_delete_player_actor(Actor* actor) {
    assert(actor == gBattleStatus.playerActor);
    assert(ScriptsKilled && get_loaded_battle_area() != nullptr);
    DeletedActors++;
}

void remove_all_effects(void) {
    assert(ScriptsKilled && get_loaded_battle_area() != nullptr);
}

void set_windows_visible(s32 group) {
}

static void cleanup_module(void) {
    assert(ScriptsKilled && get_loaded_battle_area() != nullptr);
    ModuleCleanups++;
}

void unload_action_command(void) { cleanup_module(); }
void unload_battle_script(void) { cleanup_module(); }
void unload_battle_partner(void) { cleanup_module(); }
void unload_battle_menu(void) { cleanup_module(); }

void state_init_end_battle(void) {
    assert(DeletedActors == 3 && ModuleCleanups == 4);
}

void state_step_end_battle(void) {
    if (++TransitionSteps == 5) {
        gGameStatusPtr->context = CONTEXT_WORLD;
        unload_battle_stage();
        unload_battle_area();
    }
}

int main(int argc, char** argv) {
    const BattleArea* area;
    Stage* stage;
    s32 savedLoads;
    s32 savedUnloads;
    s32 i;
    Bytecode dmaArgs[] = { 0 };
    Evt script = { .ptrReadPos = dmaArgs };
    Actor enemy = {0}, partner = {0}, player = {0};
    const char* mode = argc > 1 ? argv[1] : "";

    gCurrentBattleID = 0;
    gCurrentStageID = -1;
    if (strcmp(mode, "--invalid-area") == 0) gCurrentBattleID = 0x4000;
    if (strcmp(mode, "--invalid-battle") == 0) gCurrentBattleID = 1;
    if (strcmp(mode, "--invalid-stage") == 0) gCurrentStageID = 7;
    if (strcmp(mode, "--missing-export") == 0) MissingExport = true;
    load_battle_section();
    if (strcmp(mode, "--double-load") == 0) load_battle_section();
    if (strcmp(mode, "--invalid-animation") == 0) dmaArgs[0] = 1;
    LoadBattleDmaData(&script, true);
    assert(argc == 1); // every failure mode must panic before this point

    area = get_loaded_battle_area();
    assert(area != nullptr && gCurrentBattlePtr == &(*area->battles)[0]);
    assert(gCurrentStagePtr == nullptr);
    assert(DmaStart == Animation && DmaEnd == Animation + sizeof(Animation) && DmaDest == AnimationDest);
    gBattleDmaDest = AnimationOverride;
    LoadBattleDmaData(&script, true);
    assert(DmaDest == AnimationOverride);
    stage = load_battle_stage(gCurrentBattlePtr->stage);
    assert(gBattleStatus.curStage == stage);

    savedUnloads = Unloads;
    dx_debug_load_battle_preview(0, 0); // borrow the live area
    assert(get_loaded_battle_area() == area && Unloads == savedUnloads);
    assert(DebugBattlePreviewBattleCount == 1 && DebugBattlePreviewStageCount == 2);
    assert(DebugBattlePreviewLineCount == 2);
    assert(strlen(DebugBattlePreviewNames[0]) == 23);
    assert(strcmp(DebugBattlePreviewNames[1], "(anonymous)") == 0);
    savedLoads = Loads;
    dx_debug_load_battle_preview(0, 0);
    assert(Loads == savedLoads); // unchanged preview does not reload anything
    dx_debug_load_battle_preview(1, 0); // temporary different area
    assert(Unloads == savedUnloads + 1 && get_loaded_battle_area() == area);
    assert(DebugBattlePreviewLineCount == 6);
    assert(strcmp(DebugBattlePreviewNames[5], "... and 2 more") == 0);
    assert(strncmp(DebugBattlePreviewNames[0], "actor_0", 7) == 0); // copied before free
    dx_debug_load_battle_preview(1, 9);
    assert(Unloads == savedUnloads + 2);
    assert(strcmp(DebugBattlePreviewNames[0], "(invalid battle)") == 0);
    dx_debug_load_battle_preview(-1, 0);
    assert(Unloads == savedUnloads + 2);

    unload_battle_stage();
    unload_battle_area();
    assert(get_loaded_battle_area() == nullptr && gBattleStatus.curStage == nullptr);
    assert(gCurrentBattlePtr == nullptr && gCurrentStagePtr == nullptr && gOverrideBattlePtr == nullptr);
    savedUnloads = Unloads;
    unload_battle_stage();
    unload_battle_area();
    assert(Unloads == savedUnloads);

    gCurrentBattleID = 0x100;
    gCurrentStageID = 1;
    load_battle_section(); // another battle, selecting an aliased stage
    area = get_loaded_battle_area();
    assert(gCurrentStagePtr == &(*area->stages)[1]);
    assert(strcmp(gCurrentStagePtr->stage, "nok_04") == 0);
    load_battle_stage(gCurrentStagePtr->stage);
    gBattleStatus.enemyActors[0] = &enemy;
    gBattleStatus.partnerActor = &partner;
    gBattleStatus.playerActor = &player;
    gGameStatusPtr->context = CONTEXT_BATTLE;
    dx_debug_force_end_battle();
    assert(gGameStatusPtr->context == CONTEXT_WORLD);
    assert(get_loaded_battle_area() == nullptr && gBattleStatus.curStage == nullptr);
    assert(dx_debug_consume_discard_frame());
    assert(!dx_debug_consume_discard_frame());
    for (i = 0; i < ARRAY_COUNT(Modules); i++) assert(Modules[i] == nullptr);
    puts("All battle-area loader, preview, animation, and forced-teardown tests passed.");
    return 0;
}
