#include "common.h"
#include "sprite/player.h"
#include "inventory.h"
#include "item_choice.h"
#include "sprite/npc/WorldParakarry.h"

BSS s32 ChoiceList[NUM_ITEMS + 1];
BSS s32 SelectedItemID;
BSS b32 HasSelectedItem;
BSS s32 DeferredLetterReward;

static API_CALLABLE(ItemChoice_WaitForSelection) {
    Bytecode* args = script->ptrReadPos;

    if (isInitialCall) {
        HasSelectedItem = false;
    }

    if (HasSelectedItem) {
        HasSelectedItem = false;
        evt_set_variable(script, *args++, SelectedItemID);
        return ApiStatus_DONE2;
    }

    return ApiStatus_BLOCK;
}

static API_CALLABLE(ItemChoice_SaveSelected) {
    Bytecode* args = script->ptrReadPos;

    SelectedItemID = evt_get_variable(script, *args);
    HasSelectedItem = true;
    return ApiStatus_DONE2;
}

static API_CALLABLE(BuildKeyItemChoiceList) {
    Bytecode* args = script->ptrReadPos;
    s32 choiceArg = evt_get_variable(script, *args++);
    s32* allowedItemList = (s32*)choiceArg;
    s32 pos = 0;
    s32 i;

    if (choiceArg > ITEM_NONE && choiceArg < NUM_ITEMS) {
        // accept literal itemIDs as a trivial list
        ASSERT(item_is_key(choiceArg));
        ChoiceList[pos++] = choiceArg;
    } else if (allowedItemList == nullptr) {
        // null pointers are wildcard lists
        for (i = 0; i < NUM_ITEMS; i++) {
            if (item_is_key(i)) {
                ChoiceList[pos++] = i;
            }
        }
    } else {
        // normal key item list
        for (i = 0; allowedItemList[i] != ITEM_NONE; i++) {
            ASSERT(item_is_key(allowedItemList[i]));
            ChoiceList[pos++] = allowedItemList[i];
        }
    }
    // write list terminator
    ChoiceList[pos] = ITEM_NONE;

    return ApiStatus_DONE2;
}

static EvtScript EVS_KeyItemChoicePopup = {
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
    BindPadlock(Ref(EVS_KeyItemChoicePopup), TRIGGER_FORCE_ACTIVATE, 0, Ref(ChoiceList), 0, 1)
    Call(ItemChoice_WaitForSelection, LVar0)
    Return
    End
};

static API_CALLABLE(BuildItemChoiceList) {
    Bytecode* args = script->ptrReadPos;
    s32 choiceArg = evt_get_variable(script, *args++);
    s32* allowedItemList = (s32*)choiceArg;
    s32 pos = 0;
    s32 i;

    if (choiceArg > ITEM_NONE && choiceArg < NUM_ITEMS) {
        // accept literal itemIDs as a trivial list
        ASSERT(item_is_consumable(choiceArg));
        ChoiceList[pos++] = choiceArg;
    } else if (allowedItemList == nullptr) {
        // null pointers are wildcard lists
        for (i = 0; i < NUM_ITEMS; i++) {
            if (item_is_consumable(i)) {
                ChoiceList[pos++] = i;
            }
        }
    } else {
        // normal consumable list
        for (i = 0; allowedItemList[i] != ITEM_NONE; i++) {
            ASSERT(item_is_consumable(allowedItemList[i]));
            ChoiceList[pos++] = allowedItemList[i];
        }
    }
    // write list terminator
    ChoiceList[pos] = ITEM_NONE;

    return ApiStatus_DONE2;
}

static EvtScript EVS_ItemChoicePopup = {
    Set(LVar9, LVar1)
    Call(ShowConsumableChoicePopup)
    Set(LVarA, LVar0)
    Switch(LVar0)
        CaseEq(ITEM_CHOICE_NONE)
        CaseEq(ITEM_CHOICE_CANCELED)
        CaseDefault
            Call(RemoveItemAt, LVar1)
            Call(GetPlayerPos, LVar3, LVar4, LVar5)
            Call(AddPlayerHandsOffset, LVar3, LVar4, LVar5)
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

EvtScript EVS_ChooseItem = {
    Call(BuildItemChoiceList, LVar0)
    BindPadlock(Ref(EVS_ItemChoicePopup), TRIGGER_FORCE_ACTIVATE, 0, Ref(ChoiceList), 0, 1)
    Call(ItemChoice_WaitForSelection, LVar0)
    Return
    End
};

EvtScript EVS_GiveItemReward = {
    IfEq(LVar0, ITEM_STAR_PIECE)
        Call(ShowGotItem, ITEM_STAR_PIECE, true, 0)
        Call(AddStarPieces, 1)
    Else
        Call(ShowGotItem, LVar0, true, 0)
        Call(AddItem, LVar0, LVar1)
    EndIf
    Return
    End
};

EvtScript EVS_GiveCoinReward = {
    Call(ShowGotItem, LVar0, true, ITEM_PICKUP_FLAG_1_COIN)
    Return
    End
};

BSS s32 UnpackedLetterList[5]; // needs one more than LetterDelivery::letters for end-of-list sentinel
BSS s32 DeliverySavedAnim;

static API_CALLABLE(UnpackLetterDelivery) {
    Bytecode* args = script->ptrReadPos;
    LetterDelivery* delivery = (LetterDelivery*) evt_get_variable(script, *args++);
    s32* letterList;
    s32 i;
    s32 count = 0;

    // interpret union as an item list if the first element is a valid itemID
    if (delivery->letters[0] >= 0 && delivery->letters[0] < NUM_ITEMS) {
        for (i = 0; i < ARRAY_COUNT(delivery->letters); i++) {
            s32 itemID = delivery->letters[i];
            UnpackedLetterList[count++] = delivery->letters[i];

            if (itemID == ITEM_NONE || count > ARRAY_COUNT(UnpackedLetterList)) {
                break;
            }
        }
        UnpackedLetterList[count] = ITEM_NONE;
        letterList = UnpackedLetterList;
    } else {
        letterList = delivery->list;
    }

    script->varTable[2] = delivery->recipientID;
    script->varTable[3] = delivery->recipientTalk;
    script->varTable[4] = delivery->recipientIdle;

    script->varTable[5] = letterList[0]; // visual item to hand over

    if (delivery->deferReward) {
        script->varTable[6] = ITEM_NONE;
        DeferredLetterReward = delivery->reward;
    } else {
        script->varTable[6] = delivery->reward;
        DeferredLetterReward = ITEM_NONE;
    }

    script->varTable[7] = delivery->msgGreeting;
    script->varTable[8] = delivery->msgCancelled;
    script->varTable[9] = delivery->msgDelivered;
    script->varTable[10] = delivery->msgRecieved;

    script->varTablePtr[11] = letterList;

    return ApiStatus_DONE2;
}

static API_CALLABLE(LetterDelivery_GetDeferredReward) {
    Bytecode* args = script->ptrReadPos;

    evt_set_variable(script, *args++, DeferredLetterReward);
    return ApiStatus_DONE2;
}

static API_CALLABLE(LetterDelivery_CalcLetterPos) {
    Bytecode* args = script->ptrReadPos;
    s32 xVar = *args++;
    s32 yVar = *args++;
    s32 zVar = *args++;

    f32 x = evt_get_variable(script, xVar);
    f32 y = evt_get_variable(script, yVar);
    f32 z = evt_get_variable(script, zVar);
    f32 cameraYaw = clamp_angle(gCameras[gCurrentCameraID].curYaw + 180.0f);

    Npc* partner = get_npc_unsafe(NPC_PARTNER);

    add_vec2D_polar(&x, &z, 15.0f, partner->yaw);
    add_vec2D_polar(&x, &z, 10.0f, cameraYaw);

    evt_set_variable(script, xVar, x);
    evt_set_variable(script, yVar, y);
    evt_set_variable(script, zVar, z);

    return ApiStatus_DONE2;
}

static API_CALLABLE(LetterDelivery_SaveNpcAnim) {
    Npc* npc = get_npc_unsafe(script->varTable[2]);

    DeliverySavedAnim = npc->curAnim;
    npc->curAnim = script->varTable[4];
    return ApiStatus_DONE2;
}

static API_CALLABLE(LetterDelivery_RestoreNpcAnim) {
    Npc* npc = get_npc_unsafe(script->varTable[2]);

    npc->curAnim = DeliverySavedAnim;
    return ApiStatus_DONE2;
}

static EvtScript EVS_LetterDelivery_CarryLetter = {
    Loop(0)
        Call(GetNpcPos, NPC_PARTNER, LVar3, LVar4, LVar5)
        Call(LetterDelivery_CalcLetterPos, LVar3, LVar4, LVar5)
        Call(SetItemPos, LVar0, LVar3, LVar4, LVar5)
        Wait(1)
    EndLoop
    Return
    End
};

static EvtScript EVS_LetterDelivery_ItemPrompt = {
    Set(LVar9, LVar1)
    Call(ShowKeyChoicePopup)
    Set(LVarA, LVar0)
    Switch(LVar0)
        CaseEq(ITEM_CHOICE_NONE)
        CaseEq(ITEM_CHOICE_CANCELED)
        CaseDefault
            Call(RemoveKeyItemAt, LVar1)
            Call(DisablePartnerAI, false)
            Call(GetNpcPos, NPC_PARTNER, LVar3, LVar4, LVar5)
            Call(LetterDelivery_CalcLetterPos, LVar3, LVar4, LVar5)
            BitwiseOrConst(LVar0, VIS_GROUP_5 << 16)
            Call(MakeItemEntity, LVar0, LVar3, LVar4, LVar5, ITEM_SPAWN_MODE_DECORATION, 0)
            ExecGetTID(EVS_LetterDelivery_CarryLetter, LVarA)
            Call(SetNpcAnimation, NPC_PARTNER, ANIM_WorldParakarry_Walk)
            Call(GetAngleBetweenNPCs, LVar9, NPC_PARTNER, LVarB)
            Call(GetNpcPos, NPC_PARTNER, LVar3, LVar4, LVar5)
            Call(GetNpcPos, LVar9, LVar6, LVar7, LVar8)
            Call(SetNpcFlagBits, NPC_PARTNER, NPC_FLAG_IGNORE_CHAR_COLLISION, true)
            IfLe(LVarB, 180)
                Add(LVar6, 20)
            Else
                Add(LVar6, -20)
            EndIf
            Add(LVar7, 10)
            Call(SetNpcJumpscale, NPC_PARTNER, Float(0.0))
            Call(NpcJump1, NPC_PARTNER, LVar6, LVar7, LVar8, 20)
            KillThread(LVarA)
            Call(RemoveItemEntity, LVar0)
            Wait(20)
            Call(GetNpcYaw, NPC_PARTNER, LVarA)
            Add(LVarA, 180)
            Call(InterpNpcYaw, NPC_PARTNER, LVarA, 0)
            Wait(5)
            Call(NpcJump1, NPC_PARTNER, LVar3, LVar4, LVar5, 20)
            Call(SetNpcAnimation, NPC_PARTNER, ANIM_WorldParakarry_Idle)
            Call(NpcFaceNpc, NPC_PARTNER, LVar9, 0)
            Wait(5)
            Call(SetNpcFlagBits, NPC_PARTNER, NPC_FLAG_IGNORE_CHAR_COLLISION, false)
            Call(EnablePartnerAI)
            Wait(5)
    EndSwitch
    Call(ItemChoice_SaveSelected, LVarA)
    Call(CloseChoicePopup)
    Unbind
    Return
    End
};

static EvtScript N(EVS_ShowLetterChoice) = {
    Set(LVar0, LVarB)
    Set(LVar1, LVar2)
    Call(BuildKeyItemChoiceList, LVar0)
    BindPadlock(EVS_LetterDelivery_ItemPrompt, TRIGGER_FORCE_ACTIVATE, 0, Ref(ChoiceList), 0, 1)
    Call(ItemChoice_WaitForSelection, LVar0)
    Return
    End
};

// returns DeliveryResult on LVarC
static EvtScript EVS_DoLetterDelivery = {
    Set(LVarC, DELIVERY_NOT_POSSIBLE)
    IfLt(GB_StoryProgress, STORY_CH2_PARAKARRY_JOINED_PARTY)
        Return
    EndIf
    Call(LetterDelivery_SaveNpcAnim)
    Call(GetCurrentPartnerID, LVar0)
    Call(FindItem, LVar5, LVar1)
    IfEq(LVar0, PARTNER_PARAKARRY)
        IfNe(LVar1, -1)
            Call(DisablePartnerAI, false)
            Call(PlayerFaceNpc, LVar2, false)
            Wait(1)
            Call(GetNpcPos, LVar2, LVarD, LVar0, LVarE)
            Call(GetNpcPos, NPC_PARTNER, LVarD, LVarE, LVarF)
            Call(SetNpcJumpscale, NPC_PARTNER, Float(0.0))
            Add(LVar0, 10)
            Call(NpcJump1, NPC_PARTNER, LVarD, LVar0, LVarF, 10)
            Call(SpeakToNpc, NPC_PARTNER, ANIM_WorldParakarry_Talk, ANIM_WorldParakarry_Idle, 0, LVar2, LVar7)
            Call(EnablePartnerAI)
            ExecWait(N(EVS_ShowLetterChoice))
            Switch(LVar0)
                CaseEq(ITEM_CHOICE_CANCELED)
                    Call(DisablePartnerAI, false)
                    Wait(1)
                    Call(SpeakToPlayer, NPC_PARTNER, ANIM_WorldParakarry_Talk, ANIM_WorldParakarry_Idle, 5, LVar8)
                    Call(EnablePartnerAI)
                    Set(LVarC, DELIVERY_REJECTED)
                CaseDefault
                    Call(DisablePartnerAI, false)
                    Wait(1)
                    Call(SpeakToPlayer, NPC_PARTNER, ANIM_WorldParakarry_Talk, ANIM_WorldParakarry_Idle, 5, LVar9)
                    IfNe(LVarA, 0)
                        Call(SpeakToPlayer, LVar2, LVar3, LVar4, 0, LVarA)
                    EndIf
                    Call(EnablePartnerAI)
                    Set(LVarC, DELIVERY_ACCEPTED)
            EndSwitch
        EndIf
    EndIf
    Call(LetterDelivery_RestoreNpcAnim)
    Return
    End
};

// expects LetterDelivery* on LVar0
// returns DeliveryResult on LVar0 and deferred reward item on LVar1, or ITEM_NONE if not deferred
EvtScript EVS_TryLetterDelivery = {
    Call(UnpackLetterDelivery, LVar0)
    ExecWait(EVS_DoLetterDelivery)
    IfEq(LVarC, DELIVERY_ACCEPTED)
        IfNe(LVar6, ITEM_NONE)
            EVT_GIVE_REWARD(LVar6)
        EndIf
        Call(LetterDelivery_GetDeferredReward, LVar1)
    Else
        Set(LVar1, ITEM_NONE)
    EndIf
    Set(LVar0, LVarC)
    Return
    End
};
