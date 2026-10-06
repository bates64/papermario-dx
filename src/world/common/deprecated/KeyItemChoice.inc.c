#ifndef _COMMON_KEY_CHOICE_
#define _COMMON_KEY_CHOICE_

#include "common.h"
#include "sprite/player.h"
#include "inventory.h"

static s32 KeyItemChoiceList[ITEM_NUM_KEYS + 1];

#ifndef _CHOICE_SUPPORT_
#define _CHOICE_SUPPORT_

s32 ItemChoice_HasSelectedItem = 0;
s32 ItemChoice_SelectedItemID = 0;

#include "world/common/deprecated/GetNpcCollisionHeight.inc.c"
#include "world/common/deprecated/AddPlayerHandsOffset.inc.c"

API_CALLABLE(ItemChoice_WaitForSelection) {
    Bytecode* args = script->ptrReadPos;

    if (isInitialCall) {
        ItemChoice_HasSelectedItem = false;
    }

    if (ItemChoice_HasSelectedItem) {
        ItemChoice_HasSelectedItem = false;
        evt_set_variable(script, *args++, ItemChoice_SelectedItemID);
        return ApiStatus_DONE2;
    }

    return ApiStatus_BLOCK;
}

API_CALLABLE(ItemChoice_SaveSelected) {
    Bytecode* args = script->ptrReadPos;

    ItemChoice_SelectedItemID = evt_get_variable(script, *args);
    ItemChoice_HasSelectedItem = true;
    return ApiStatus_DONE2;
}

#endif

API_CALLABLE(BuildKeyItemChoiceList) {
    Bytecode* args = script->ptrReadPos;
    s32* allowedItemList = (s32*)evt_get_variable(script, *args++);
    s32 i;

    if (allowedItemList != nullptr) {
        for (i = 0; allowedItemList[i] != ITEM_NONE; i++) {
            KeyItemChoiceList[i] = allowedItemList[i];
        }
        KeyItemChoiceList[i] = ITEM_NONE;
    } else {
        s32 pos = 0;
        for (i = 0; i < NUM_ITEMS; i++) {
            if (item_is_key(i)) {
                KeyItemChoiceList[pos++] = i;
            }
        }
        KeyItemChoiceList[pos] = ITEM_NONE;
    }
    return ApiStatus_DONE2;
}

EvtScript EVS_KeyItemChoicePopup = {
    Set(LVar9, LVar1)
    Call(ShowKeyChoicePopup)
    Set(LVarA, LVar0)
    Switch(LVar0)
        CaseEq(ITEM_CHOICE_NONE)
        CaseEq(ITEM_CHOICE_CANCELED)
        CaseDefault
            Call(RemoveKeyItemAt, LVar1)
            Call(GetPlayerPos, LVar3, LVar4, LVar5)
            Call(AddPlayerHandsOffset, LVar3, LVar4, LVar5)
            BitwiseOrConst(LVar0, ITEM_VIS_GROUP(ITEM_NONE, 5))
            Call(MakeItemEntity, LVar0, LVar3, LVar4, LVar5, ITEM_SPAWN_MODE_DECORATION, 0)
            Call(SetPlayerAnimation, ANIM_MarioW1_TakeItem)
            Wait(30)
            Call(SetPlayerAnimation, ANIM_Mario1_Idle)
            Call(RemoveItemEntity, LVar0)
    EndSwitch
    Call(ItemChoice_SaveSelected, LVarA)
    Call(CloseChoicePopup)
    Unbind
    Return
    End
};

EvtScript EVS_ChooseKeyItem = {
    Call(BuildKeyItemChoiceList, LVar0)
    BindPadlock(Ref(EVS_KeyItemChoicePopup), TRIGGER_FORCE_ACTIVATE, 0, Ref(KeyItemChoiceList), 0, 1)
    Call(ItemChoice_WaitForSelection, LVar0)
    Return
    End
};

#define EVT_CHOOSE_ANY_KEY_ITEM(recipientNpc) \
    Set(LVar0, nullptr) \
    Set(LVar1, recipientNpc) \
    ExecWait(EVS_ChooseKeyItem)

#define EVT_CHOOSE_KEY_ITEM_FROM(itemList, recipientNpc) \
    Set(LVar0, Ref(itemList)) \
    Set(LVar1, recipientNpc) \
    ExecWait(EVS_ChooseKeyItem)

#endif
