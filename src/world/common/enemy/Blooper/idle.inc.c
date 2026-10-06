#pragma once
#include "idle.h"

NpcSettings NpcSettings_Blooper = {
    .height = 24,
    .radius = 24,
    .level = ACTOR_LEVEL_NONE,
};

static const char* BlooperBattles[] = {
    "tik2:blooper",
    "tik2:electro_blooper",
    "tik2:super_blooper",
};

API_CALLABLE(GetBlooperBattleID) {
    Bytecode* args = script->ptrReadPos;
    Enemy* enemy = script->owner1.enemy;
    s32 index = evt_get_variable(script, *args++);

    gCurrentEncounter.encounterList[enemy->encounterIndex]->battle = BlooperBattles[index];
    return ApiStatus_DONE2;
}
