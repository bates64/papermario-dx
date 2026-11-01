#include "kzn_03.h"
#include "entity.h"

API_CALLABLE(IsPlayerOnFirstCliff) {
    s32 result = -1;

    if (gPlayerStatus.lastGoodPos.y > 800.0) {
        result = 0;
    }
    if (gPlayerStatus.lastGoodPos.y < 680.0) {
        result = 1;
    }
    if (result >= 0) {
        evt_set_variable(script, MV_PlayerCliffState, result);
    }

    return ApiStatus_BLOCK;
}

EvtScript EVS_TetherCameraToPlayer = {
    Loop(0)
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
        Call(SetCamTarget, CAM_DEFAULT, LVar0, LVar1, LVar2)
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript EVS_UseSpringA = {
    Call(DisablePlayerInput, true)
    Call(DisablePlayerPhysics, true)
    Call(SetPlayerActionState, ACTION_STATE_IDLE)
    Wait(1)
    Call(SetPlayerActionState, ACTION_STATE_LAUNCH)
    Wait(1)
    Call(EnableCameraFollowPlayerY)
    ExecGetTID(EVS_TetherCameraToPlayer, LVarA)
    Call(SetPlayerJumpscale, 0.7)
    Call(PlayerJump, 335, 290, 360, 40)
    Call(SetPlayerFlagBits, PS_FLAG_FLYING, true)
    Call(SetPlayerActionState, ACTION_STATE_FALLING)
    Call(DisablePlayerPhysics, false)
    KillThread(LVarA)
    Call(DisableCameraFollowPlayerY)
    Return
    End
};

EvtScript EVS_UseSpringB = {
    Call(DisablePlayerPhysics, true)
    Call(SetPlayerActionState, ACTION_STATE_IDLE)
    Wait(1)
    Call(SetPlayerActionState, ACTION_STATE_JUMP)
    Wait(1)
    Call(EnableCameraFollowPlayerY)
    ExecGetTID(EVS_TetherCameraToPlayer, LVarA)
    Call(SetPlayerJumpscale, 0.7)
    Call(PlayerJump, 350, 470, 210, 40)
    Call(SetPlayerActionState, ACTION_STATE_LAND)
    Call(DisablePlayerPhysics, false)
    Call(DisablePlayerInput, false)
    KillThread(LVarA)
    Call(DisableCameraFollowPlayerY)
    Return
    End
};

EvtScript EVS_UseSpringC = {
    Call(DisablePlayerInput, true)
    Call(DisablePlayerPhysics, true)
    Call(SetPlayerActionState, ACTION_STATE_IDLE)
    Wait(1)
    Call(SetPlayerActionState, ACTION_STATE_JUMP)
    Wait(1)
    Call(EnableCameraFollowPlayerY)
    ExecGetTID(EVS_TetherCameraToPlayer, LVarA)
    IfEq(MV_PlayerCliffState, 0)
        Call(SetPlayerJumpscale, 1.4)
        Call(PlayerJump, -470, 670, 71, 18)
    Else
        Call(SetPlayerJumpscale, 0.7)
        Call(PlayerJump, -384, 870, -22, 40)
    EndIf
    Call(SetPlayerActionState, ACTION_STATE_LAND)
    Call(DisablePlayerPhysics, false)
    Call(DisablePlayerInput, false)
    KillThread(LVarA)
    Call(DisableCameraFollowPlayerY)
    Return
    End
};

EvtScript EVS_OnBreakBlock = {
    Set(GB_StoryProgress, STORY_CH5_SMASHED_ULTRA_BLOCK)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $SavePoint_1)
    Call(MakeMarkerEntity, $Item_FireShield_1)
    Call(MakeMarkerEntity, $BrickBlock_1)
    Call(MakeMarkerEntity, $BrickBlock_2)
    Call(MakeMarkerEntity, $Item_PowBlock_1)
    Call(MakeMarkerEntity, $YellowBlock_Coin_1)
    Call(MakeMarkerEntity, $YellowBlock_Coin_2)
    Call(MakeMarkerEntity, $YellowBlock_Coin_3)
    Call(MakeMarkerEntity, $YellowBlock_Coin_4)
    IfLt(GB_StoryProgress, STORY_CH5_SMASHED_ULTRA_BLOCK)
        Call(MakeMarkerEntity, $Hammer3Block_1)
        Thread
            Loop(0)
                IfGe(GB_StoryProgress, STORY_CH5_SMASHED_ULTRA_BLOCK)
                    BreakLoop
                EndIf
                Wait(1)
            EndLoop
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_on_off, COLLIDER_FLAGS_UPPER_MASK)
        EndThread
    Else
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_on_off, COLLIDER_FLAGS_UPPER_MASK)
    EndIf
    Call(MakeMarkerEntity, $ScriptSpring_1)
    Call(MakeMarkerEntity, $ScriptSpring_2)
    Thread
        Call(IsPlayerOnFirstCliff)
    EndThread
    Call(MakeMarkerEntity, $ScriptSpring_3)
    Return
    End
};
