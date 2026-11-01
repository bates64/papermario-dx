#include "nok_14.h"
#include "entity.h"

API_CALLABLE(CheckItemExists) {
    Bytecode* args = script->ptrReadPos;
    s32 itemIdx = evt_get_variable(script, *args++);
    s32 outVar = *args++;
    ItemEntity* itemEntity = get_item_entity(itemIdx);

    evt_set_variable(script, outVar, (s32) itemEntity);
    return ApiStatus_DONE2;
}

EvtScript EVS_ReadSign_NoEntry = {
    Call(IsStartingConversation, LVar0)
    IfEq(LVar0, true)
        Return
    EndIf
    SetGroup(EVT_GROUP_NEVER_PAUSE)
    Call(SetTimeFreezeMode, TIME_FREEZE_PARTIAL)
    Call(DisablePlayerInput, true)
    Call(ShowMessageAtScreenPos, MSG_Menus_0179, 160, 40)
    Call(DisablePlayerInput, false)
    Call(SetTimeFreezeMode, TIME_FREEZE_NONE)
    Return
    End
};

EvtScript EVS_BreakBlock_ThunderBolt = {
    IfEq(GF_NOK14_Item_ThunderBolt, true)
        Return
    EndIf
    Thread
        Call(DisablePlayerInput, true)
        Loop(25)
            Wait(1)
            Call(GetNpcPos, NPC_KoopaTroopa_02, LVar0, LVar1, LVar2)
            Call(CheckItemExists, MV_Item_ThunderBolt, LVarA)
            IfEq(LVarA, 0)
                // prevent crash from player picking up the item before the loop ends
                BreakLoop
            EndIf
            Call(SetItemPos, MV_Item_ThunderBolt, LVar0, LVar1, LVar2)
        EndLoop
        Call(SetNpcPos, NPC_KoopaTroopa_02, NPC_DISPOSE_LOCATION)
        Call(DisablePlayerInput, false)
    EndThread
    Call(SetNpcPos, NPC_KoopaTroopa_02, -345, 75, -117)
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Call(SetNpcJumpscale, NPC_KoopaTroopa_02, 1.5)
    IfLe(LVar0, -345)
        Call(NpcJump0, NPC_KoopaTroopa_02, -280, 0, -112, 20)
    Else
        Call(NpcJump0, NPC_KoopaTroopa_02, -410, 0, -112, 20)
    EndIf
    Return
    End
};

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $Signpost_1)
    Set(LVar0, 1)
    IfLt(GB_StoryProgress, STORY_CH1_MADE_SECOND_BRIDGE)
        Set(LVar0, 0)
    EndIf
    IfEq(LVar0, 0)
        Call(MakeMarkerEntity, $BlueSwitch_1)
    EndIf
    Call(MakeMarkerEntity, $Item_Coin_1)
    Call(MakeMarkerEntity, $Item_Coin_2)
    Call(MakeMarkerEntity, $Item_Coin_3)
    Call(MakeMarkerEntity, $Item_Coin_4)
    Call(MakeMarkerEntity, $Item_Coin_5)
    Call(MakeMarkerEntity, $BrickBlock_1)
    Call(MakeMarkerEntity, $Item_ThunderBolt_1)
    Set(MV_Item_ThunderBolt, LVar0)
    Call(MakeMarkerEntity, $BrickBlock_2)
    Call(MakeMarkerEntity, $HiddenYellowBlock_FireFlower_1)
    Call(MakeMarkerEntity, $BrickBlock_3)
    Call(MakeMarkerEntity, $HiddenPanel_1)
    Return
    End
};
