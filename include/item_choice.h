#pragma once

#include "common.h"

extern EvtScript EVS_ChooseKeyItem;
extern EvtScript EVS_ChooseItem;

extern EvtScript EVS_GiveItemReward;
extern EvtScript EVS_GiveCoinReward;

extern API_CALLABLE(LetterDelivery_Init);
extern EvtScript EVS_DoLetterDelivery;

enum ItemChoiceResult {
    ITEM_CHOICE_NONE        = 0,  // player did not have any of the requested items
    ITEM_CHOICE_CANCELED    = -1, // player canceled the choice dialog
};

enum DeliveryResult {
    DELIVERY_NOT_POSSIBLE   = 0,
    DELIVERY_REJECTED       = 1,
    DELIVERY_ACCEPTED       = 2,
};

#define EVT_CHOOSE_ANY_CONSUMABLE(recipientNpc) \
    Set(LVar0, nullptr) \
    Set(LVar1, recipientNpc) \
    ExecWait(EVS_ChooseItem)

#define EVT_CHOOSE_CONSUMABLE_FROM(itemList, recipientNpc) \
    Set(LVar0, Ref(itemList)) \
    Set(LVar1, recipientNpc) \
    ExecWait(EVS_ChooseItem)

#define EVT_CHOOSE_ANY_KEY_ITEM(recipientNpc) \
    Set(LVar0, nullptr) \
    Set(LVar1, recipientNpc) \
    ExecWait(EVS_ChooseKeyItem)

#define EVT_CHOOSE_KEY_ITEM_FROM(itemList, recipientNpc) \
    Set(LVar0, Ref(itemList)) \
    Set(LVar1, recipientNpc) \
    ExecWait(EVS_ChooseKeyItem)

#define EVT_GIVE_REWARD(itemID) \
    Set(LVar0, itemID) \
    ExecWait(EVS_GiveItemReward) \
    Call(AddItem, itemID, LVar1)

#define EVT_GIVE_STAR_PIECE() \
    Set(LVar0, ITEM_STAR_PIECE) \
    ExecWait(EVS_GiveItemReward) \
    Call(AddStarPieces, 1)

#define EVT_LETTER_PROMPT(npcName, npcID, animTalk, animIdle, msg1, msg2, ms3, msg4, itemID, itemList) \
    EvtScript N(EVS_LetterPrompt_##npcName) = { \
        Call(LetterDelivery_Init, \
            npcID, animTalk, animIdle, \
            itemID, ITEM_NONE, \
            msg1, msg2, ms3, msg4, \
            Ref(itemList)) \
        ExecWait(EVS_DoLetterDelivery) \
        Return \
        End \
    }

#define EVT_LETTER_REWARD(npcName) \
    EvtScript N(EVS_LetterReward_##npcName) = { \
        IfEq(LVarC, DELIVERY_ACCEPTED) \
            EVT_GIVE_STAR_PIECE() \
        EndIf \
        Return \
        End \
    }

#define EVT_LETTER_CHECK(npcName) \
    ExecWait(N(EVS_LetterPrompt_##npcName)) \
    ExecWait(N(EVS_LetterReward_##npcName))

#define EVT_RETURN_IF_DELIVERED() \
    IfNe(LVarC, DELIVERY_NOT_POSSIBLE) \
        Return \
    EndIf
