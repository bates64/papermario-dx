#include "kkj_25.h"
#include "world/area/kkj/kkj_24.h"

EvtScript EVS_ExitDoors_kkj_24_1 =
    EVT_EXIT_DOUBLE_DOOR($TowerStaircase, $kkj_24.BossArena, COLLIDER_ttw, MODEL_o84, MODEL_o85);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitDoors_kkj_24_1, TRIGGER_WALL_PRESS_A, COLLIDER_ttw, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($TowerStaircase.index)
            IfEq(GF_KKJ25_Visited, false)
                Call(DisablePlayerInput, true)
                Call(SetPlayerPos, -645, 0, 0)
                Call(GetPartnerInUse, LVar0)
                IfEq(LVar0, 0)
                    Call(DisablePartnerAI, false)
                    Call(SetNpcPos, NPC_PARTNER, -660, 0, 0)
                    Wait(1)
                    Call(EnablePartnerAI)
                EndIf
                Wait(150)
                Call(PlaySoundAtCollider, COLLIDER_ttw, SOUND_LARGE_DOOR_OPEN, 0)
                Call(MakeLerp, 0, 80, 10, EASING_LINEAR)
                Loop(0)
                    Call(UpdateLerp)
                    Call(RotateModel, MODEL_o84, LVar0, 0, -1, 0)
                    Call(RotateModel, MODEL_o85, LVar0, 0, 1, 0)
                    Wait(1)
                    IfEq(LVar1, 0)
                        BreakLoop
                    EndIf
                EndLoop
                Call(SetPlayerPos, -605, 0, 0)
                Call(DisablePlayerInput, false)
                Call(SetZoneEnabled, ZONE_o15, false)
                Call(ResetCam, CAM_DEFAULT, 90.0)
                Set(GF_KKJ25_Visited, true)
            Else
                Call(SetZoneEnabled, ZONE_o15, false)
                Call(ResetCam, CAM_DEFAULT, 90.0)
            EndIf
            Set(LVar0, 0)
            Set(LVar2, MODEL_o84)
            Set(LVar3, MODEL_o85)
            ExecWait(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
            Exec(EVS_Scene_BowserTrapsMario)
        CaseEq(1)
            Exec(EVS_Scene_KammyDefeated)
        CaseEq(2)
            Exec(EVS_Scene_BowserDefeated)
    EndSwitch
    Return
    End
};

EvtScript EVS_Rotate_Propellers = {
    Thread
        Set(LVar2, 0)
        Loop(0)
            Add(LVar2, 10)
            Call(RotateGroup, MODEL_g3, LVar2, 0, 1, 0)
            Call(RotateGroup, MODEL_g12, LVar2, 0, 1, 0)
            Call(RotateGroup, MODEL_g14, LVar2, 0, 1, 0)
            Call(RotateGroup, MODEL_g16, LVar2, 0, 1, 0)
            Call(RotateGroup, MODEL_g18, LVar2, 0, 1, 0)
            Wait(1)
        EndLoop
    EndThread
    Set(LVar2, 90)
    Loop(0)
        Add(LVar2, 10)
        Call(RotateGroup, MODEL_g11, LVar2, 0, 1, 0)
        Call(RotateGroup, MODEL_g13, LVar2, 0, 1, 0)
        Call(RotateGroup, MODEL_g15, LVar2, 0, 1, 0)
        Call(RotateGroup, MODEL_g17, LVar2, 0, 1, 0)
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript EVS_Main = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(1)
            Set(GF_KKJ25_Defeated_Kammy, true)
        CaseEq(2)
            Set(GF_KKJ25_Defeated_Kammy, true)
            Set(GF_KKJ25_Defeated_Bowser, true)
    EndSwitch
    Call(SetCamSpeed, CAM_DEFAULT, 0.75)
    IfEq(GF_KKJ25_Defeated_Bowser, false)
        IfEq(GF_KKJ25_Defeated_Kammy, false)
            Call(MakeNpcs, false, InitialNpcs)
        Else
            Call(MakeNpcs, false, MidpointNpcs)
            Call(EnableGroup, MODEL_g30, false)
        EndIf
    Else
        Call(MakeNpcs, false, FinaleNpcs)
        Call(EnableGroup, MODEL_g30, false)
    EndIf
    ExecWait(EVS_MakeEntities)
    Call(UseDoorSounds, DOOR_SOUNDS_LARGE)
    Exec(EVS_EnterMap)
    Call(ParentColliderToModel, COLLIDER_o128, MODEL_o1)
    Exec(EVS_Rotate_Propellers)
    Call(GetEntryID, LVar0)
    Thread
        Set(MV_ArenaState, ARENA_STATE_IDLE)
        IfEq(LVar0, $TowerStaircase.index)
            Call(EnableModel, MODEL_o122, false)
            Loop(0)
                Wait(1)
                IfEq(MV_ArenaState, ARENA_STATE_ACTIVATING)
                    BreakLoop
                EndIf
            EndLoop
        Else
            Call(ScaleModel, MODEL_o122, 250, 1, 250)
        EndIf
        Exec(EVS_ManageArenaEffects)
    EndThread
    Return
    End
};
