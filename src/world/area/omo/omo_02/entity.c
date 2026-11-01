#include "omo_02.h"
#include "entity.h"

EvtScript EVS_TetherCamToPlayer = {
    Label(0)
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
        Call(SetCamTarget, CAM_DEFAULT, LVar0, LVar1, LVar2)
        Wait(1)
        Goto(0)
    Return
    End
};

EvtScript EVS_StarBoxLaunch_Impl = {
    Call(DisablePlayerInput, true)
    Call(DisablePlayerPhysics, true)
    Call(SetPlayerActionState, ACTION_STATE_JUMP)
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    Loop(4)
        Add(LVar1, 10)
        Call(SetPlayerPos, LVar0, LVar1, LVar2)
        Wait(1)
    EndLoop
    Call(EnableCameraFollowPlayerY)
    ExecGetTID(EVS_TetherCamToPlayer, LVarA)
    Call(SetPlayerJumpscale, 0.7)
    Call(PlayerJump, -290, 85, -78, 40)
    KillThread(LVarA)
    Call(DisableCameraFollowPlayerY)
    Wait(3)
    Call(SetPlayerActionState, ACTION_STATE_IDLE)
    Call(DisableCameraFollowPlayerY)
    Call(DisablePlayerPhysics, false)
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $YellowBlock_SleepySheep_1)
    Call(MakeMarkerEntity, $HiddenYellowBlock_Coin_1)
    Call(MakeMarkerEntity, $BrickBlock_1)
    Call(MakeMarkerEntity, $Item_ShootingStar_1)
    Call(MakeMarkerEntity, $StarBoxLauncher_1)
    Return
    End
};
