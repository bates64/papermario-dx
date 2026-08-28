#pragma once

#include "common.h"

typedef enum BattleScriptKind {
    BATTLE_SCRIPT_KIND_MOVE,
    BATTLE_SCRIPT_KIND_ITEM,
    BATTLE_SCRIPT_KIND_STAR_POWER,
} BattleScriptKind;

typedef struct BattleScriptModule {
    /* 0x00 */ BattleScriptKind kind;
    /* 0x04 */ s32 entryCount;
    /* 0x08 */ EvtScript* const* entryScripts;
} BattleScriptModule; // size = 0x0C

typedef struct BattleScriptRef {
    /* 0x00 */ const char* overlayName;
    /* 0x04 */ BattleScriptKind kind;
    /* 0x08 */ s32 entryIndex;
} BattleScriptRef;

#define BATTLE_SCRIPT_EXPORT_NAME "gBattleScriptModule"

#define BATTLE_SCRIPT_MODULE(moduleKind, ...) \
    static EvtScript* const BattleScriptEntries[] = { __VA_ARGS__ }; \
    export const BattleScriptModule gBattleScriptModule = { \
        .kind = (moduleKind), \
        .entryCount = ARRAY_COUNT(BattleScriptEntries), \
        .entryScripts = BattleScriptEntries, \
    }

EvtScript* load_battle_script(const BattleScriptRef* ref);
void unload_battle_script(void);
