#include "dgb_11.h"
#include "world/area/dgb/dgb_10.h"
#include "entity.h"
#include "animation_script.h"
#include "sprite/player.h"

extern AnimScript Entity_ScriptSpring_AnimLaunch;

API_CALLABLE(PlaySpringAnimation) {
    Entity* entity = get_entity_by_index(evt_get_variable(nullptr, MV_SpringEntityID));

    if (entity == nullptr) {
        return ApiStatus_BLOCK;
    }

    play_model_animation(entity->virtualModelIndex, Entity_ScriptSpring_AnimLaunch);

    return ApiStatus_DONE2;
}

EvtScript EVS_TetherCamToPlayer = {
    Label(0)
        Call(GetPlayerPos, LVar0, LVar1, LVar2)
        IfGe(LVar1, LVar3)
            Set(LVar1, LVar3)
        EndIf
        Call(SetCamTarget, CAM_DEFAULT, LVar0, LVar1, LVar2)
        Wait(1)
        Goto(0)
    Return
    End
};

EvtScript EVS_LaunchToCeiling = {
    Call(PlayerJump, 375, 270, -250, 20)
    Return
    End
};

EvtScript EVS_UseSpring = {
    IfEq(AF_DGB11_SpringInUse, true)
        Return
    EndIf
    Set(AF_DGB11_SpringInUse, true)
    Call(DisablePlayerInput, true)
    Call(SetZoneEnabled, ZONE_o203, false)
    IfEq(AF_DGB11_FallingFromHole, false)
        IfEq(GF_DGB10_BoardedFloor3, false)
            Call(DisablePlayerPhysics, true)
            Call(SetPlayerActionState, ACTION_STATE_JUMP)
            Wait(1)
            Set(LVar3, 500)
            ExecGetTID(EVS_TetherCamToPlayer, LVarA)
            Call(SetPlayerJumpscale, 0.7)
            ExecGetTID(EVS_LaunchToCeiling, LVarB)
            Loop(0)
                Wait(1)
                Call(GetPlayerPos, LVar0, LVar1, LVar2)
                IfGe(LVar1, 165)
                    BreakLoop
                EndIf
            EndLoop
            Call(GetPlayerPos, LVar0, LVar1, LVar2)
            Call(SetPlayerPos, LVar0, 165, LVar2)
            KillThread(LVarB)
            Call(SetPlayerAnimation, ANIM_MarioW2_JumpHitHead)
            Call(ShakeCam, CAM_DEFAULT, 0, 20, 1.0)
            Wait(10)
            Call(SetPlayerAnimation, ANIM_Mario1_Idle)
            Call(SetPlayerJumpscale, 0.0)
            Call(PlayerJump1, 375, 25, -250, 10)
            Call(PlaySpringAnimation)
            Call(PlaySoundAtPlayer, SOUND_SPRING, SOUND_SPACE_DEFAULT)
            Call(SetPlayerJumpscale, 0.7)
            Call(PlayerJump, 375, 0, -175, 15)
            KillThread(LVarA)
            Call(SetPlayerActionState, ACTION_STATE_IDLE)
            Wait(2)
            Call(SetZoneEnabled, ZONE_o203, true)
            Call(DisablePlayerPhysics, false)
            Call(DisablePlayerInput, false)
            Set(AF_DGB11_SpringInUse, false)
        Else
            Call(DisablePlayerPhysics, true)
            Call(SetPlayerActionState, ACTION_STATE_JUMP)
            Wait(1)
            Thread
                Wait(8)
                Call(GotoMap, $dgb_10.Dgb11)
                Wait(100)
            EndThread
            Set(LVar3, 500)
            ExecGetTID(EVS_TetherCamToPlayer, LVarA)
            Call(SetPlayerJumpscale, 0.7)
            Call(PlayerJump, 375, 270, -250, 20)
            Set(AF_DGB11_SpringInUse, false)
        EndIf
    Else
        Call(SetPlayerActionState, ACTION_STATE_JUMP)
        Wait(1)
        Set(LVar3, 25)
        Call(SetPlayerJumpscale, 0.7)
        Call(PlayerJump, 375, 0, -175, 15)
        Set(AF_DGB11_FallingFromHole, false)
        KillThread(LVarA)
        Call(SetPlayerActionState, ACTION_STATE_IDLE)
        Wait(2)
        Call(SetZoneEnabled, ZONE_o203, true)
        Call(DisablePlayerInput, false)
        Set(AF_DGB11_SpringInUse, false)
    EndIf
    Return
    End
};

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $Item_DDownJump_1)
    Call(MakeMarkerEntity, $ScriptSpring_1)
    Set(MV_SpringEntityID, LVar0)
    Return
    End
};
