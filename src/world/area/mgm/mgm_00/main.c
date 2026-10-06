#include "mgm_00.h"

EvtScript EVS_SetupMusic = {
    Return
    End
};

#include "world/common/entity/Pipe.inc.c"

EvtScript EVS_GotoMap_ToadTown = {
    Call(GotoMap, Ref("mac_03"), mac_03_ENTRY_2)
    Wait(100)
    Return
    End
};

EvtScript EVS_OnEnterPipe_ToadTown = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Set(LVarA, mgm_00_ENTRY_0)
    Set(LVarB, COLLIDER_deili1)
    Set(LVarC, Ref(EVS_GotoMap_ToadTown))
    ExecWait(EVS_Pipe_ExitHorizontal)
    Return
    End
};

EvtScript EVS_GotoMap_JumpAttack = {
    Call(GotoMap, Ref("mgm_01"), mgm_01_ENTRY_0)
    Wait(100)
    Return
    End
};

EvtScript EVS_OnEnterPipe_JumpAttack = EVT_EXIT_PIPE_VERTICAL(
    mgm_00_ENTRY_1, COLLIDER_deili2, EVS_GotoMap_JumpAttack);

EvtScript EVS_GotoMap_SmashAttack = {
    Call(GotoMap, Ref("mgm_02"), mgm_02_ENTRY_0)
    Wait(100)
    Return
    End
};

EvtScript EVS_OnEnterPipe_SmashAttack = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Set(LVarA, mgm_00_ENTRY_2)
    Set(LVarB, COLLIDER_deili3)
    Set(LVarC, Ref(EVS_GotoMap_SmashAttack))
    ExecWait(EVS_Pipe_ExitVertical)
    Return
    End
};

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_OnEnterPipe_ToadTown), TRIGGER_WALL_PUSH, COLLIDER_deili1, 1, 0)
    IfEq(GF_MGM_Unlocked_JumpAttack, true)
        BindTrigger(Ref(EVS_OnEnterPipe_JumpAttack), TRIGGER_FLOOR_TOUCH, COLLIDER_deili2, 1, 0)
    EndIf
    IfEq(GF_MGM_Unlocked_SmashAttack, true)
        BindTrigger(Ref(EVS_OnEnterPipe_SmashAttack), TRIGGER_FLOOR_TOUCH, COLLIDER_deili3, 1, 0)
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
        CaseEq(mgm_00_ENTRY_0)
            Set(LVarA, Ref(EVS_BindExitTriggers))
            Set(LVarB, 1)
            Exec(EVS_Pipe_EnterHorizontal)
        CaseEq(mgm_00_ENTRY_1)
            Set(LVarA, Ref(EVS_BindExitTriggers))
            Exec(EVS_Pipe_EnterVertical)
        CaseEq(mgm_00_ENTRY_2)
            Set(LVarA, Ref(EVS_BindExitTriggers))
            Exec(EVS_Pipe_EnterVertical)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    ExecWait(EVS_SetupScoreboard)
    Call(MakeNpcs, false, Ref(DefaultNPCs))
    ExecWait(EVS_SetupMusic)
    Exec(EVS_BindInteractTriggers)
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
