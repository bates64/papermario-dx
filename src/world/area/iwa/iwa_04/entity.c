#include "iwa_04.h"
#include "entity.h"

API_CALLABLE(MonitorPlayerAltitude) {
    s32 status = -1;

    if (gPlayerStatus.lastGoodPos.y > -100.0) {
        status = 0;
    }
    if (gPlayerStatus.lastGoodPos.y < -240.0) {
        status = 1;
    }
    if (status >= 0) {
        evt_set_variable(script, MV_PlayerCliffLevel, status);
    }

    return ApiStatus_BLOCK;
}

EvtScript TetherCameraToPlayer = {
    Loop(0)
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
        Call(SetCamTarget, CAM_DEFAULT, LVar0, LVar1, LVar2)
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript EVS_UseSpring = {
    Call(DisablePlayerInput, true)
    Call(DisablePlayerPhysics, true)
    Call(SetPlayerActionState, ACTION_STATE_LAUNCH)
    Wait(1)
    ExecGetTID(TetherCameraToPlayer, LVarA)
    IfEq(MV_PlayerCliffLevel, 0)
        Call(SetPlayerJumpscale, 1.4)
        Call(PlayerJump, -560, -250, 190, 15)
    Else
        Call(SetPlayerJumpscale, 0.7)
        Call(PlayerJump, -560, 0, 90, 40)
    EndIf
    KillThread(LVarA)
    Call(SetPlayerActionState, ACTION_STATE_IDLE)
    Call(DisablePlayerPhysics, false)
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    Thread
        Call(MonitorPlayerAltitude)
    EndThread
    Call(MakeMarkerEntity, $ScriptSpring_1)
    Call(MakeMarkerEntity, $ArrowSign_1)
    Call(MakeMarkerEntity, $ArrowSign_2)
    Call(MakeMarkerEntity, $ArrowSign_3)
    Call(MakeMarkerEntity, $ArrowSign_4)
    Call(MakeMarkerEntity, $Item_LetterChainGoompapa1_1)
    Return
    End
};
