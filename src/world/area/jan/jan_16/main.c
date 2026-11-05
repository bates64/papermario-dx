#include "jan_16.h"
#include "world/area/jan/jan_15.h"
#include "world/area/jan/jan_17.h"
#include "world/area/jan/jan_22.h"
#include "effects.h"

EvtScript EVS_ExitWalk_jan_15_1 = EVT_EXIT_WALK(60, $Jan15, $jan_15.Jan16);
EvtScript EVS_ExitWalk_jan_22_1 = EVT_EXIT_WALK(60, $Jan22, $jan_22.Jan16);
EvtScript EVS_ExitWalk_jan_17_0 = EVT_EXIT_WALK(60, $Jan17, $jan_17.Jan16);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_jan_15_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_jan_22_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    BindTrigger(EVS_ExitWalk_jan_17_0, TRIGGER_FLOOR_ABOVE, COLLIDER_o83, 1, 0)
    Return
    End
};

EvtScript EVS_SpawnButterflies = {
    IfNe(GB_StoryProgress, STORY_CH5_RAPHAEL_LEFT_NEST)
        PlayEffect(EFFECT_BUTTERFLIES, 5, $ButterfliesPos_1.pos.x, $ButterfliesPos_1.pos.y, $ButterfliesPos_1.pos.z)
        PlayEffect(EFFECT_BUTTERFLIES, 5, $ButterfliesPos_2.pos.x, $ButterfliesPos_2.pos.y, $ButterfliesPos_2.pos.z)
        PlayEffect(EFFECT_BUTTERFLIES, 5, $ButterfliesPos_3.pos.x, $ButterfliesPos_3.pos.y, $ButterfliesPos_3.pos.z)
    EndIf
    PlayEffect(EFFECT_BUTTERFLIES, 5, $ButterfliesPos_4.pos.x, $ButterfliesPos_4.pos.y, $ButterfliesPos_4.pos.z)
    PlayEffect(EFFECT_BUTTERFLIES, 5, $ButterfliesPos_5.pos.x, $ButterfliesPos_5.pos.y, $ButterfliesPos_5.pos.z)
    PlayEffect(EFFECT_BUTTERFLIES, 5, $ButterfliesPos_6.pos.x, $ButterfliesPos_6.pos.y, $ButterfliesPos_6.pos.z)
    Return
    End
};

// represent branch wobble with a damped spring system
// provide impulses with MV_BranchWobbleVel and the scale of MODEL_g47 with be
// modulated by the displacement of the 'spring'
EvtScript EVS_UpdateBranchWobble = {
    SetF(LVarA, 0.0) // system "displacement"
    Loop(0)
        // scaleX = 1.0 - 0.02 * vel
        // scaleY = 1.0 + 0.04 * vel
        SetF(LVar0, MV_BranchWobbleVel)
        SetF(LVar1, MV_BranchWobbleVel)
        MulF(LVar0, -0.02)
        MulF(LVar1, 0.04)
        AddF(LVar0, 1)
        AddF(LVar1, 1)
        Call(ScaleGroup, MODEL_g47, LVar0, LVar1, 1)
        // Damped spring update, with units of dt = 1 and mass = 1:
        // accel = -(54/64) * (3/64) * X_n
        // V_n+1 = (54/64) * V_n - (81/2048) * X_n
        // X_n+1 = X_n + V_n+1
        SetF(LVar0, LVarA)
        MulF(LVar0, -0.046875) // accel = (-3/64) * displacement, multiplied by (54/64) shortly
        AddF(MV_BranchWobbleVel, LVar0)
        MulF(MV_BranchWobbleVel, 0.84375) // damping = (54/64)
        AddF(LVarA, MV_BranchWobbleVel)
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript EVS_EnterFalling = {
    Exec(EVS_UpdateBranchWobble)
    Call(DisablePlayerInput, true)
    Call(DisablePlayerPhysics, true)
    Call(SetPlayerActionState, ACTION_STATE_LAND)
    Call(DisablePartnerAI, false)
    Call(SetNpcFlagBits, NPC_PARTNER, NPC_FLAG_GRAVITY, false)
    Call(UseSettingsFrom, CAM_DEFAULT, 35, 100, 330)
    Call(SetPanTarget, CAM_DEFAULT, 35, 100, 330)
    Call(SetCamSpeed, CAM_DEFAULT, 90.0)
    Call(PanToTarget, CAM_DEFAULT, 0, true)
    Call(WaitForCam, CAM_DEFAULT, 1.0)
    Call(GetPartnerInUse, LVar0)
    IfNe(LVar0, PARTNER_NONE)
        Call(InterruptUsePartner)
    EndIf
    Wait(15)
    Thread
        Wait(30)
        Call(SetPanTarget, CAM_DEFAULT, 35, 0, 330)
        Call(SetCamSpeed, CAM_DEFAULT, 0.8)
        Call(PanToTarget, CAM_DEFAULT, 0, true)
    EndThread
    Call(DisablePlayerPhysics, false)
    Call(SetNpcFlagBits, NPC_PARTNER, NPC_FLAG_GRAVITY, true)
    Call(SetPlayerPos, 35, 600, 340)
    Call(MakeLerp, 600, 130, 15, EASING_LINEAR)
    Loop(0)
        Call(UpdateLerp)
        Call(SetPlayerPos, 35, LVar0, 340)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    PlayEffect(EFFECT_DROP_LEAVES, 0, $DropLeavesPos_1.pos.x, $DropLeavesPos_1.pos.y, $DropLeavesPos_1.pos.z, 100)
    PlayEffect(EFFECT_DROP_LEAVES, 0, $DropLeavesPos_2.pos.x, $DropLeavesPos_2.pos.y, $DropLeavesPos_2.pos.z, 100)
    AddF(MV_BranchWobbleVel, -7.5)
    Call(SetPanTarget, CAM_DEFAULT, 0, 190, 350)
    Call(SetCamSpeed, CAM_DEFAULT, 1.2)
    Call(PanToTarget, CAM_DEFAULT, 0, true)
    Thread
        Call(SetPlayerJumpscale, 2.0)
        Call(PlaySoundAtPlayer, SOUND_SHAKE_TREE_LEAVES, SOUND_SPACE_DEFAULT)
        Call(PlayerJump, -35, 0, 385, 30)
        Call(SetPlayerActionState, ACTION_STATE_LAND)
    EndThread
    Call(SetNpcJumpscale, NPC_PARTNER, 0)
    Call(NpcJump0, NPC_PARTNER, 35, 130, 330, 15)
    Thread
        Loop(3)
            PlayEffect(EFFECT_DROP_LEAVES, 0, $DropLeavesPos_1.pos.x, $DropLeavesPos_1.pos.y, $DropLeavesPos_1.pos.z, 100)
            PlayEffect(EFFECT_DROP_LEAVES, 0, $DropLeavesPos_3.pos.x, $DropLeavesPos_3.pos.y, $DropLeavesPos_3.pos.z, 100)
            Wait(5)
        EndLoop
    EndThread
    AddF(MV_BranchWobbleVel, -7.5)
    Call(SetPanTarget, CAM_DEFAULT, -35, 0, 385)
    Call(SetCamSpeed, CAM_DEFAULT, 1.8)
    Call(PanToTarget, CAM_DEFAULT, 0, true)
    Call(SetNpcJumpscale, NPC_PARTNER, 2.0)
    Call(NpcJump0, NPC_PARTNER, -10, 0, 395, 20)
    Call(EnablePartnerAI)
    Call(ResetCam, CAM_DEFAULT, 4.0)
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript EVS_Main = {
    Call(MakeNpcs, false, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_Scene_ReachedRaphaelsTree)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitw, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilite, COLLIDER_FLAGS_UPPER_MASK)
    Call(GetEntryID, LVar0)
    IfEq(LVar0, $Jan23.index)
        Exec(EVS_EnterFalling)
        Exec(EVS_BindExitTriggers)
    Else
        Set(LVar0, EVS_BindExitTriggers)
        Exec(EnterWalk)
    EndIf
    ExecWait(EVS_SetupMusic)
    Exec(EVS_SetupBushes)
    Exec(EVS_SpawnButterflies)
    Call(SetModelTintMode, APPLY_TINT_MODELS, -1, ENV_TINT_REMAP)
    Call(SetModelTintMode, APPLY_TINT_BG, nullptr, ENV_TINT_REMAP)
    Call(SetModelTintParams, ENV_TINT_REMAP, 255, 255, 255, 0, 0, 25, 0, 0, 0)
    Return
    End
};
