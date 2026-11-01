#include "mgm_00.h"
#include "world/area/mac/mac_03.h"
#include "world/area/mgm/mgm_01.h"
#include "world/area/mgm/mgm_02.h"

EvtScript EVS_SetupMusic = {
    Return
    End
};

#include "world/common/entity/Pipe.inc.c"

EvtScript EVS_GotoMap_ToadTown = {
    Call(GotoMap, $mac_03.PlayroomPipe)
    Wait(100)
    Return
    End
};

EvtScript EVS_OnEnterPipe_ToadTown = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Set(LVarA, $StationDistrict.index)
    Set(LVarB, COLLIDER_deili1)
    Set(LVarC, EVS_GotoMap_ToadTown)
    ExecWait(EVS_Pipe_ExitHorizontal)
    Return
    End
};

EvtScript EVS_GotoMap_JumpAttack = {
    Call(GotoMap, $mgm_01.Lobby)
    Wait(100)
    Return
    End
};

EvtScript EVS_OnEnterPipe_JumpAttack = EVT_EXIT_PIPE_VERTICAL($JumpAttack, COLLIDER_deili2, EVS_GotoMap_JumpAttack);

EvtScript EVS_GotoMap_SmashAttack = {
    Call(GotoMap, $mgm_02.Lobby)
    Wait(100)
    Return
    End
};

EvtScript EVS_OnEnterPipe_SmashAttack = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Set(LVarA, $SmashAttack.index)
    Set(LVarB, COLLIDER_deili3)
    Set(LVarC, EVS_GotoMap_SmashAttack)
    ExecWait(EVS_Pipe_ExitVertical)
    Return
    End
};

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_OnEnterPipe_ToadTown, TRIGGER_WALL_PUSH, COLLIDER_deili1, 1, 0)
    IfEq(GF_MGM_Unlocked_JumpAttack, true)
        BindTrigger(EVS_OnEnterPipe_JumpAttack, TRIGGER_FLOOR_TOUCH, COLLIDER_deili2, 1, 0)
    EndIf
    IfEq(GF_MGM_Unlocked_SmashAttack, true)
        BindTrigger(EVS_OnEnterPipe_SmashAttack, TRIGGER_FLOOR_TOUCH, COLLIDER_deili3, 1, 0)
    EndIf
    Return
    End
};

EvtScript EVS_EnterMap = {
    IfEq(GF_MGM_Unlocked_JumpAttack, false)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o5, COLLIDER_FLAGS_UPPER_MASK)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deili2, COLLIDER_FLAGS_UPPER_MASK)
        Call(EnableModel, MODEL_o5, false)
    EndIf
    IfEq(GF_MGM_Unlocked_SmashAttack, false)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o9, COLLIDER_FLAGS_UPPER_MASK)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deili3, COLLIDER_FLAGS_UPPER_MASK)
        Call(EnableModel, MODEL_o9, false)
    EndIf
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($StationDistrict.index)
            Set(LVarA, EVS_BindExitTriggers)
            Set(LVarB, 1)
            Exec(EVS_Pipe_EnterHorizontal)
        CaseEq($JumpAttack.index)
            Set(LVarA, EVS_BindExitTriggers)
            Exec(EVS_Pipe_EnterVertical)
        CaseEq($SmashAttack.index)
            Set(LVarA, EVS_BindExitTriggers)
            Exec(EVS_Pipe_EnterVertical)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    ExecWait(EVS_SetupScoreboard)
    Call(MakeNpcs, false, DefaultNPCs)
    ExecWait(EVS_SetupMusic)
    Exec(EVS_BindInteractTriggers)
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
