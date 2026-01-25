#ifndef _COMMON_GIVE_REWARD_H_
#define _COMMON_GIVE_REWARD_H_

#include "common.h"

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

#define EVT_GIVE_REWARD(itemID) \
    Set(LVar0, itemID) \
    ExecWait(N(GiveItemReward)) \
    Call(AddItem, itemID, LVar1)

#define EVT_GIVE_STAR_PIECE() \
    Set(LVar0, ITEM_STAR_PIECE) \
    ExecWait(N(GiveItemReward)) \
    Call(AddStarPieces, 1)

#endif
