#pragma once

#include "common.h"

extern EvtScript EVS_ChooseKeyItem;
extern EvtScript EVS_ChooseItem;

extern EvtScript EVS_GiveItemReward;
extern EvtScript EVS_GiveCoinReward;

extern EvtScript EVS_TryLetterDelivery;

#define ITEM_LIST(name, ...) \
    s32 name[] = { __VA_ARGS__, ITEM_NONE }

enum ItemChoiceResult {
    ITEM_CHOICE_NONE        = 0,  // player did not have any of the requested items
    ITEM_CHOICE_CANCELED    = -1, // player canceled the choice dialog
};

enum DeliveryResult {
    DELIVERY_NOT_POSSIBLE   = 0,
    DELIVERY_REJECTED       = 1,
    DELIVERY_ACCEPTED       = 2,
};

typedef struct LetterDelivery {
    /* 0x00 */ s32 recipientID;
    /* 0x04 */ AnimID recipientTalk;
    /* 0x08 */ AnimID recipientIdle;
    /* 0x0C */ MsgID msgGreeting;
    /* 0x10 */ MsgID msgCancelled;
    /* 0x14 */ MsgID msgDelivered;
    /* 0x18 */ MsgID msgRecieved;
    /* 0x1C */ union {
    /*      */   s32 letters[4];
    /*      */   s32* list;
    /* 0x2C */ };
    /* 0x2C */ s32 reward;
    /* 0x30 */ b32 deferReward; // caller will be responsible for giving reward
} LetterDelivery; // size = 0x34

#define EVT_CHOOSE_ANY_CONSUMABLE(recipientNpc) \
    Set(LVar0, nullptr) \
    Set(LVar1, recipientNpc) \
    ExecWait(EVS_ChooseItem)

#define EVT_CHOOSE_CONSUMABLE_FROM(itemList, recipientNpc) \
    Set(LVar0, Ref(itemList)) \
    Set(LVar1, recipientNpc) \
    ExecWait(EVS_ChooseItem)

#define EVT_CHOOSE_CONSUMABLE_ONLY(itemID, recipientNpc) \
    Set(LVar0, itemID) \
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

#define EVT_CHOOSE_KEY_ITEM_ONLY(itemID, recipientNpc) \
    Set(LVar0, itemID) \
    Set(LVar1, recipientNpc) \
    ExecWait(EVS_ChooseKeyItem)

#define EVT_GIVE_REWARD(itemID) \
    Set(LVar0, itemID) \
    ExecWait(EVS_GiveItemReward)

#define EVT_RETURN_IF_DELIVERED() \
    IfNe(LVar0, DELIVERY_NOT_POSSIBLE) \
        Return \
    EndIf
