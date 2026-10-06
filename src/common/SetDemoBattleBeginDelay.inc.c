#include "common.h"
#include "npc.h"

extern s16 DemoBattleBeginDelay;

static API_CALLABLE(SetDemoBattleBeginDelay) {
    DemoBattleBeginDelay = script->varTable[0];
    return ApiStatus_DONE2;
}
