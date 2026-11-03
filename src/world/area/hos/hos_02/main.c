#include "hos_02.h"
#include "world/area/hos/hos_01.h"
#include "world/area/hos/hos_03.h"
#include "world/surfaces.h"

EvtScript EVS_ExitStarWarp = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Call(GetPartnerInUse, LVar0)
    IfNe(LVar0, PARTNER_NONE)
        Call(InterruptUsePartner)
        Wait(20)
        Loop(0)
            Wait(1)
            Call(IsPlayerOnValidFloor, LVar0)
            IfEq(LVar0, true)
                BreakLoop
            EndIf
        EndLoop
    EndIf
    Call(DisablePlayerPhysics, true)
    Call(DisablePartnerAI, false)
    ExecWait(EVS_DescendStarWarp)
    Call(GotoMap, $hos_01.StarWay)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitWalk_hos_03_0 = EVT_EXIT_WALK(60, $StarHaven, $hos_03.StarWay);

EvtScript EVS_BindExitTriggers = {
    Call(GetEntryID, LVar0)
    IfNe(LVar0, $ShootingStarSummit.index)
        BindTrigger(EVS_ExitStarWarp, TRIGGER_FLOOR_TOUCH, COLLIDER_deiliw, 1, 0)
    EndIf
    BindTrigger(EVS_ExitWalk_hos_03_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript EVS_EnterStarWarp = {
    Call(DisablePlayerInput, true)
    Call(DisablePlayerPhysics, true)
    Call(DisablePartnerAI, false)
    Call(SetNpcFlagBits, NPC_PARTNER, NPC_FLAG_GRAVITY, false)
    Call(UseSettingsFrom, CAM_DEFAULT, -1105, -171, 225)
    Call(SetPanTarget, CAM_DEFAULT, -1105, -171, 225)
    Call(SetCamDistance, CAM_DEFAULT, 300.0)
    Call(SetCamSpeed, CAM_DEFAULT, 90.0)
    Call(PanToTarget, CAM_DEFAULT, 0, true)
    Call(WaitForCam, CAM_DEFAULT, 1.0)
    Set(LVar2, 360)
    Call(MakeLerp, -400, -171, 60, EASING_QUADRATIC_OUT)
    Loop(0)
        Call(UpdateLerp)
        Call(SetPlayerPos, -1105, LVar0, 225)
        Call(SetNpcPos, NPC_PARTNER, -1105, LVar0, 215)
        Add(LVar2, 40)
        Call(InterpPlayerYaw, LVar2, 0)
        Call(SetNpcRotation, NPC_PARTNER, 0, LVar2, 0)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Set(LVar0, LVar2)
    Sub(LVar0, 360)
    Sub(LVar2, LVar0)
    Set(LVar0, 40)
    Label(10)
        IfLt(LVar2, 450)
            Call(InterpPlayerYaw, LVar2, 0)
            Call(SetNpcRotation, NPC_PARTNER, 0, LVar2, 0)
            Add(LVar2, LVar0)
            Wait(1)
            Goto(10)
        EndIf
        Set(LVar2, 90)
        Sub(LVar0, 5)
        IfGt(LVar0, 20)
            Goto(10)
        EndIf
    Call(SetNpcRotation, NPC_PARTNER, 0, 0, 0)
    Call(SetStarWarpIdleParams, MV_StarWarpEffect)
    Call(SetNpcFlagBits, NPC_PARTNER, NPC_FLAG_GRAVITY, true)
    Call(EnablePartnerAI)
    Call(DisablePlayerPhysics, false)
    Call(PanToTarget, CAM_DEFAULT, 0, false)
    Call(SetMusic, 0, SONG_STAR_WAY_OPENS, BGM_VARIATION_3, VOL_LEVEL_FULL)
    Call(DisablePlayerInput, false)
    Call(AwaitPlayerLeave, -1105, 225, 40)
    BindTrigger(EVS_ExitStarWarp, TRIGGER_FLOOR_TOUCH, COLLIDER_deiliw, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_STAR_WAY)
    Call(SetSurfaceWalkEffect, SURFACE_WALK_FX_SPARKLE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Set(GF_MAP_StarWay, true)
    Call(MakeNpcs, false, DefaultNPCs)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($ShootingStarSummit.index)
            Thread
                ExecWait(EVS_EnterStarWarp)
                Exec(EVS_BindExitTriggers)
            EndThread
        CaseEq($StarHaven.index)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilite, COLLIDER_FLAGS_UPPER_MASK)
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
    EndSwitch
    Exec(EVS_SetupModelFX)
    Exec(EVS_SetupUnused)
    Exec(EVS_SetupMusic)
    Return
    End
};
