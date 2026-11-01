#include "kmr_03.h"
#include "entity.h"

EvtScript EVS_OnSmashBlock1 = {
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_tt1, COLLIDER_FLAGS_UPPER_MASK)
    Set(GB_StoryProgress, STORY_CH0_LEFT_THE_PLAYGROUND)
    Return
    End
};

EvtScript EVS_OnSmashBlock2 = {
    Set(GF_KMR03_Hammer1Block, true)
    Return
    End
};

API_CALLABLE(GetPlayerForwardPosition) {
    f32 dx = gPlayerStatus.curSpeed * 5.0f * sin_deg(gPlayerStatus.targetYaw);
    f32 dy = gPlayerStatus.curSpeed * 5.0f * -cos_deg(gPlayerStatus.targetYaw);

    script->varTable[0] = gPlayerStatus.pos.x + dx;
    script->varTable[1] = gPlayerStatus.pos.z + dy;

    return ApiStatus_DONE2;
}

EvtScript EVS_TetherCameraToPlayer = {
    Label(0)
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
        Call(SetCamTarget, CAM_DEFAULT, LVar0, LVar1, LVar2)
        Wait(1)
        Goto(0)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    IfLt(GB_StoryProgress, STORY_CH0_LEFT_THE_PLAYGROUND)
        Call(MakeMarkerEntity, $Hammer1Block_1)
    Else
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_tt1, COLLIDER_FLAGS_UPPER_MASK)
    EndIf
    IfEq(GF_KMR03_Hammer1Block, false)
        Call(MakeMarkerEntity, $Hammer2Block_1)
    EndIf
    Call(MakeMarkerEntity, $HiddenYellowBlock_RepelGel_1)
    Call(MakeMarkerEntity, $BrickBlock_1)
    Call(MakeMarkerEntity, $BrickBlock_2)
    Call(MakeMarkerEntity, $YellowBlock_Coin_1)
    Call(MakeMarkerEntity, $SimpleSpring_1)
    Call(MakeMarkerEntity, $Item_Coin_1)
    Call(MakeMarkerEntity, $Item_Coin_2)
    Call(MakeMarkerEntity, $Item_Coin_3)
    Call(MakeMarkerEntity, $Item_Coin_4)
    Call(MakeMarkerEntity, $Item_FireFlower_1)
    Call(MakeMarkerEntity, $HiddenPanel_1)
    Call(MakeMarkerEntity, $HeartBlock_1)
    Return
    End
};
