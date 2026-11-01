#include "jan_03.h"
#include "world/area/tik/tik_08.h"
#include "entity.h"
#include "sprite/player.h"

EvtScript EVS_GotoMap_tik_08_4 = {
    Call(GotoMap, $tik_08.JadeJungle)
    Wait(100)
    Return
    End
};

API_CALLABLE(GiveInitialSpringBoost) {
    f32 x = gPlayerStatus.curSpeed * 5.0f * sin_deg(gPlayerStatus.targetYaw);
    f32 z = gPlayerStatus.curSpeed * 5.0f * -cos_deg(gPlayerStatus.targetYaw);

    script->varTable[0] = gPlayerStatus.pos.x + x;
    script->varTable[1] = gPlayerStatus.pos.z + z;
    return ApiStatus_DONE2;
}

EvtScript EVS_TetherCamToPlayer = {
    Label(0)
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
        Call(SetCamTarget, CAM_DEFAULT, LVar0, LVar1, LVar2)
        Wait(1)
        Goto(0)
    Return
    End
};

EvtScript EVS_UseSpring = {
    Call(GiveInitialSpringBoost)
    Call(DisablePlayerInput, true)
    Call(DisablePlayerPhysics, true)
    Call(SetPlayerActionState, ACTION_STATE_IDLE)
    Wait(1)
    Call(SetPlayerActionState, ACTION_STATE_LAUNCH)
    Wait(1)
    ExecGetTID(EVS_TetherCamToPlayer, LVarA)
    Call(SetPlayerJumpscale, 0.1)
    Call(PlayerJump, -556, 300, -195, 15)
    Call(DisablePlayerPhysics, false)
    Call(FacePlayerTowardPoint, -630, -50, 0)
    Call(SetPlayerAnimation, ANIM_Mario1_Fall)
    Call(SetPlayerJumpscale, 1.0)
    Call(PlayerJump2, -601, 376, -105, 30)
    Call(SetPlayerAnimation, ANIM_Mario1_Idle)
    KillThread(LVarA)
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    IfEq(GF_JAN03_WarpPipe, false)
        IfEq(GF_TIK08_WarpPipe, true)
            Call(GetEntryID, LVar0)
            IfNe(LVar0, $Pipe.index)
                Set(GF_JAN03_WarpPipe, true)
            EndIf
        EndIf
    EndIf
    Call(MakeMarkerEntity, $BlueWarpPipe_1)
    Call(MakeMarkerEntity, $SavePoint_1)
    Call(MakeMarkerEntity, $ScriptSpring_1)
    Return
    End
};
