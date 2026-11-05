#include "trd_03.h"
#include "world/area/trd/trd_02.h"
#include "world/area/trd/trd_04.h"
#include "effects.h"

extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_Scene_GreenKoopaBros;
extern EvtScript EVS_InitializePlatforms;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;

API_CALLABLE(GetHiddenDoorPushDirection) {
    Bytecode* args = script->ptrReadPos;
    s32 pushDir = 0;

    if ((gCollisionStatus.pushingAgainstWall == COLLIDER_o84) && (gGameStatusPtr->stickX[0] < 0)) {
        pushDir = 1;
    }
    if ((gCollisionStatus.pushingAgainstWall == COLLIDER_o85) && (gGameStatusPtr->stickX[0] > 0)) {
        pushDir = 2;
    }

    evt_set_variable(script, *args++, pushDir);
    return ApiStatus_DONE2;
}

API_CALLABLE(GetFrameCounter) {
    evt_set_variable(script, *script->ptrReadPos, gGameStatusPtr->frameCounter);
    return ApiStatus_DONE2;
}

EvtScript EVS_ExitDoors_trd_02_1 =
    EVT_EXIT_DOUBLE_DOOR($Trd04Lower, $trd_02.Trd03Lower, COLLIDER_ttw, MODEL_d1, MODEL_d2);
EvtScript EVS_ExitDoors_trd_04_0 =
    EVT_EXIT_DOUBLE_DOOR($Trd02Lower, $trd_04.Trd03Lower, COLLIDER_tte, MODEL_d3, MODEL_d4);
EvtScript EVS_ExitDoors_trd_02_3 =
    EVT_EXIT_DOUBLE_DOOR($Trd02Upper, $trd_02.Trd03Upper, COLLIDER_ttwo, MODEL_o33, MODEL_o34);
EvtScript EVS_ExitDoors_trd_04_2 =
    EVT_EXIT_DOUBLE_DOOR($Trd04Upper, $trd_04.Trd03Upper, COLLIDER_tteo, MODEL_o31, MODEL_o32);
EvtScript EVS_ExitDoors_trd_02_4 = EVT_EXIT_WALK(40, $Trd02Walk, $trd_02.Trd03Walk);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitDoors_trd_02_1, TRIGGER_WALL_PRESS_A, COLLIDER_ttw, 1, 0)
    BindTrigger(EVS_ExitDoors_trd_04_0, TRIGGER_WALL_PRESS_A, COLLIDER_tte, 1, 0)
    BindTrigger(EVS_ExitDoors_trd_02_3, TRIGGER_WALL_PRESS_A, COLLIDER_ttwo, 1, 0)
    BindTrigger(EVS_ExitDoors_trd_04_2, TRIGGER_WALL_PRESS_A, COLLIDER_tteo, 1, 0)
    BindTrigger(EVS_ExitDoors_trd_02_4, TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($Trd04Lower.index)
            Set(LVar2, MODEL_d1)
            Set(LVar3, MODEL_d2)
            ExecWait(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq($Trd02Lower.index)
            Set(LVar2, MODEL_d3)
            Set(LVar3, MODEL_d4)
            ExecWait(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq($Trd02Upper.index)
            Set(LVar2, MODEL_o33)
            Set(LVar3, MODEL_o34)
            ExecWait(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq($Trd04Upper.index)
            Set(LVar2, MODEL_o31)
            Set(LVar3, MODEL_o32)
            ExecWait(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq($Trd02Walk.index)
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
    EndSwitch
    Return
    End
};

BombTrigger BombPos_MiddleCell = {
    .pos = $BombPos_MiddleCell.pos,
    .diameter = 2.0f * $BombPos_MiddleCell.radius,
};

BombTrigger BombPos_RightCell = {
    .pos = $BombPos_RightCell.pos,
    .diameter = 2.0f * $BombPos_RightCell.radius,
};

EvtScript EVS_BombWall_MiddleCell = {
    PlayEffect(EFFECT_BOMBETTE_BREAKING, 0, $BombetteBreakingPos_1.pos.x, $BombetteBreakingPos_1.pos.y, $BombetteBreakingPos_1.pos.z, 10, 30)
    Call(EnableModel, MODEL_nk2, true)
    Loop(10)
        Call(SetGroupVisibility, MODEL_ana2, MODEL_GROUP_VISIBLE)
        Wait(1)
        Call(SetGroupVisibility, MODEL_ana2, MODEL_GROUP_HIDDEN)
        Wait(1)
    EndLoop
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilit2, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_tt2, COLLIDER_FLAGS_UPPER_MASK)
    Set(GF_TRD03_BombedCenterCell, true)
    Unbind
    Return
    End
};

EvtScript EVS_BombWall_RightCell = {
    PlayEffect(EFFECT_BOMBETTE_BREAKING, 0, $BombetteBreakingPos_2.pos.x, $BombetteBreakingPos_2.pos.y, $BombetteBreakingPos_2.pos.z, 10, 30)
    Call(EnableModel, MODEL_nk3, true)
    Loop(10)
        Call(SetGroupVisibility, MODEL_ana3, MODEL_GROUP_VISIBLE)
        Wait(1)
        Call(SetGroupVisibility, MODEL_ana3, MODEL_GROUP_HIDDEN)
        Wait(1)
    EndLoop
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilit3, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_tt3, COLLIDER_FLAGS_UPPER_MASK)
    Set(GF_TRD03_BombedRightCell, true)
    Unbind
    Return
    End
};

EvtScript EVS_HiddenDoor = {
    Set(LVarB, 0)
    SetF(LVarC, 0.0)
    Set(LVarD, 0)
    Set(LVarE, 0)
    Call(CloneModel, MODEL_rou2, CLONED_MODEL(0))
    Call(EnableModel, CLONED_MODEL(0), false)
    Call(ParentColliderToModel, COLLIDER_o84, CLONED_MODEL(0))
    Call(CloneModel, MODEL_rou2, CLONED_MODEL(1))
    Call(EnableModel, CLONED_MODEL(1), false)
    Call(ParentColliderToModel, COLLIDER_o85, CLONED_MODEL(1))
    Label(0)
        IfEq(LVarD, 0)
            Call(GetHiddenDoorPushDirection, LVar0)
            Switch(LVar0)
                // pushing left on COLLIDER_o84
                CaseEq(1)
                    Call(GetFrameCounter, LVar1)
                    Sub(LVar1, LVarA)
                    IfEq(LVar1, 1)
                        Add(LVarB, 1)
                        SubF(LVarC, 0.1)
                    Else
                        Set(LVarB, 0)
                    EndIf
                    IfGt(LVarB, 15)
                        Set(LVarB, 0)
                        Set(LVarD, 8)
                    EndIf
                    IfLt(LVarC, -3)
                        Set(LVarD, 8)
                    EndIf
                    // pushing right on COLLIDER_o85
                CaseEq(2)
                    Set(LVarD, -8)
                    // not pushing
                CaseDefault
                    Set(LVarB, 0)
                    IfLt(LVarC, 0)
                        AddF(LVarC, 0.2)
                        IfGt(LVarC, 0)
                            SetF(LVarC, 0.0)
                        EndIf
                    Else
                        SubF(LVarC, 0.2)
                        IfLt(LVarC, 0)
                            SetF(LVarC, 0.0)
                        EndIf
                    EndIf
            EndSwitch
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_CLEAR_BITS, COLLIDER_o84, 0x7FFFFFFF)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_CLEAR_BITS, COLLIDER_o85, 0x7FFFFFFF)
            Call(TranslateModel, CLONED_MODEL(0), LVarC, 0, 0)
            Call(TranslateModel, CLONED_MODEL(1), LVarC, 0, 0)
            Call(UpdateColliderTransform, COLLIDER_o84)
            Call(UpdateColliderTransform, COLLIDER_o85)
        Else
            SetF(LVarC, 0.0)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o84, 0x7FFFFFFF)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o85, 0x7FFFFFFF)
            IfGt(LVarD, 0)
                Sub(LVarD, 1)
                Call(GetPlayerPos, LVar0, LVar1, LVar2)
                SetF(LVar3, LVarD)
                MulF(LVar3, 1.8)
                SubF(LVar0, LVar3)
                Call(SetPlayerPos, LVar0, LVar1, LVar2)
            Else
                Add(LVarD, 1)
            EndIf
        EndIf
        Call(GetFrameCounter, LVarA)
        Wait(1)
        Goto(0)
    Return
    End
};

EvtScript EVS_Main = {
    Call(MakeNpcs, true, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    IfLt(GB_StoryProgress, STORY_CH1_KOOPA_BROS_HID_KEY)
        Exec(EVS_Scene_GreenKoopaBros)
    Else
        Exec(EVS_EnterMap)
    EndIf
    IfEq(GF_TRD02_BombedWall, false)
        Call(EnableModel, MODEL_nk1, false)
    Else
        Call(SetGroupVisibility, MODEL_ana1, MODEL_GROUP_HIDDEN)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilit1, COLLIDER_FLAGS_UPPER_MASK)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_tt1, COLLIDER_FLAGS_UPPER_MASK)
    EndIf
    IfEq(GF_TRD03_BombedCenterCell, false)
        Call(EnableModel, MODEL_nk2, false)
        BindTrigger(EVS_BombWall_MiddleCell, TRIGGER_POINT_BOMB, BombPos_MiddleCell, 1, 0)
    Else
        Call(SetGroupVisibility, MODEL_ana2, MODEL_GROUP_HIDDEN)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilit2, COLLIDER_FLAGS_UPPER_MASK)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_tt2, COLLIDER_FLAGS_UPPER_MASK)
    EndIf
    IfEq(GF_TRD03_BombedRightCell, false)
        Call(EnableModel, MODEL_nk3, false)
        BindTrigger(EVS_BombWall_RightCell, TRIGGER_POINT_BOMB, BombPos_RightCell, 1, 0)
    Else
        Call(SetGroupVisibility, MODEL_ana3, MODEL_GROUP_HIDDEN)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilit3, COLLIDER_FLAGS_UPPER_MASK)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_tt3, COLLIDER_FLAGS_UPPER_MASK)
    EndIf
    Exec(EVS_SetupMusic)
    IfLt(GB_StoryProgress, STORY_CH1_KOOPA_BROS_HID_KEY)
        Call(TranslateModel, MODEL_0ri, 0, 100, -1)
    EndIf
    ExecWait(EVS_InitializePlatforms)
    Exec(EVS_HiddenDoor)
    Return
    End
};
