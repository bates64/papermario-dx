#ifndef _COMMON_GIVE_REWARD_H_
#define _COMMON_GIVE_REWARD_H_

#include "common.h"

//static s32** N(varStash) = NULL;

// TODO extracted from world/common/todo/StashVars to reduce warnings (for now)
API_CALLABLE(N(StashVars)) {
    static s32** N(varStash) = NULL;
    s32 i;

    if (N(varStash) == NULL) {
        N(varStash) = heap_malloc(sizeof(script->varTable));

        for (i = 0; i < ARRAY_COUNT(script->varTable); i++) {
            N(varStash)[i] = (s32*) script->varTable[i];
        }
    } else {
        for (i = 0; i < ARRAY_COUNT(script->varTable); i++) {
            script->varTable[i] = (s32) N(varStash)[i];
        }

        heap_free(N(varStash));
        N(varStash) = NULL;
    }

    return ApiStatus_DONE2;
}

#include "world/common/todo/GetItemName.inc.c"

EvtScript N(GiveItemReward) = {
    Call(ShowGotItem, LVar0, TRUE, 0)
    Return
    End
};

EvtScript N(GiveCoinReward) = {
    Call(ShowGotItem, LVar0, TRUE, ITEM_PICKUP_FLAG_1_COIN)
    Return
    End
};

#define EVT_GIVE_KEY_REWARD(itemID) \
    Set(LVar0, itemID) \
    ExecWait(N(GiveItemReward)) \
    Call(AddItem, itemID, LVar1)

#define EVT_GIVE_BADGE_REWARD(itemID) \
    Set(LVar0, itemID) \
    ExecWait(N(GiveItemReward)) \
    Call(AddItem, itemID, LVar0)

#define EVT_GIVE_CONSUMABLE_REWARD(itemID) \
    Set(LVar0, itemID) \
    ExecWait(N(GiveItemReward)) \
    Call(AddItem, LVar0, LVar1)

#define EVT_GIVE_STAR_PIECE() \
    Set(LVar0, ITEM_STAR_PIECE) \
    ExecWait(N(GiveItemReward)) \
    Call(AddStarPieces, 1)

#endif
