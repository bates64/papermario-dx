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
    ITEM_CHOICE_NONE        = 0,  /// player did not have any of the requested items
    ITEM_CHOICE_CANCELED    = -1, /// player canceled the choice dialog
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
    /* 0x30 */ b32 deferReward; /// caller will be responsible for giving reward
} LetterDelivery; // size = 0x34

/// Opens a consumable item choice popup which accepts any consumable item.
/// Returns the selected item ID in `LVar0`, `ITEM_CHOICE_NONE` if no matching item exists,
/// or `ITEM_CHOICE_CANCELED` if the player closes the popup without choosing an item.
#define EVT_CHOOSE_ANY_CONSUMABLE(recipientNpc) \
    Set(LVar0, nullptr) \
    Set(LVar1, recipientNpc) \
    ExecWait(EVS_ChooseItem)

/// Opens a consumable item choice popup which accepts only items from `itemList` (terminated with ITEM_NONE).
/// Returns the selected item ID in `LVar0`, `ITEM_CHOICE_NONE` if no matching item exists,
/// or `ITEM_CHOICE_CANCELED` if the player closes the popup without choosing an item.
#define EVT_CHOOSE_CONSUMABLE_FROM(itemList, recipientNpc) \
    Set(LVar0, Ref(itemList)) \
    Set(LVar1, recipientNpc) \
    ExecWait(EVS_ChooseItem)

/// Opens a consumable item choice popup which accepts only a single consumable item.
/// Returns the selected item ID in `LVar0`, `ITEM_CHOICE_NONE` if the player does not have that item,
/// or `ITEM_CHOICE_CANCELED` if the player closes the popup without choosing it.
#define EVT_CHOOSE_CONSUMABLE_ONLY(itemID, recipientNpc) \
    Set(LVar0, itemID) \
    Set(LVar1, recipientNpc) \
    ExecWait(EVS_ChooseItem)

/// Opens a key item choice popup which accepts any key item.
/// Returns the selected item ID in `LVar0`, `ITEM_CHOICE_NONE` if no matching item exists,
/// or `ITEM_CHOICE_CANCELED` if the player closes the popup without choosing an item.
#define EVT_CHOOSE_ANY_KEY_ITEM(recipientNpc) \
    Set(LVar0, nullptr) \
    Set(LVar1, recipientNpc) \
    ExecWait(EVS_ChooseKeyItem)

/// Opens a key item choice popup which accepts only items from `itemList` (terminated with ITEM_NONE).
/// Returns the selected item ID in `LVar0`, `ITEM_CHOICE_NONE` if no matching item exists,
/// or `ITEM_CHOICE_CANCELED` if the player closes the popup without choosing an item.
#define EVT_CHOOSE_KEY_ITEM_FROM(itemList, recipientNpc) \
    Set(LVar0, Ref(itemList)) \
    Set(LVar1, recipientNpc) \
    ExecWait(EVS_ChooseKeyItem)

/// Opens a key-item choice popup which accepts only a single key item.
/// Returns the selected item ID in `LVar0`, `ITEM_CHOICE_NONE` if the player does not have that item,
/// or `ITEM_CHOICE_CANCELED` if the player closes the popup without choosing it.
#define EVT_CHOOSE_KEY_ITEM_ONLY(itemID, recipientNpc) \
    Set(LVar0, itemID) \
    Set(LVar1, recipientNpc) \
    ExecWait(EVS_ChooseKeyItem)

/// Shows the standard Got Item! reward popup for `itemID`, then adds the item to player inventory
/// or increments the star piece counter for `ITEM_STAR_PIECE`.
#define EVT_GIVE_REWARD(itemID) \
    Set(LVar0, itemID) \
    ExecWait(EVS_GiveItemReward)

/// Returns early if a preceding letter-delivery attempt produced any delivery result.
/// This is typically used after `EVS_TryLetterDelivery`; it returns when `LVar0` is
/// not `DELIVERY_NOT_POSSIBLE`.
#define EVT_RETURN_IF_DELIVERED() \
    IfNe(LVar0, DELIVERY_NOT_POSSIBLE) \
        Return \
    EndIf
