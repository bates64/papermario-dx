#include "pra_03.h"

EvtScript N(EVS_ExitDoors_pra_02_1) = EVT_EXIT_SINGLE_DOOR(pra_03_ENTRY_0, "pra_02", pra_02_ENTRY_1,
    COLLIDER_deilittnnw, MODEL_o774, DOOR_SWING_IN);

EvtScript N(EVS_ExitDoors_pra_38_0) = EVT_EXIT_DOUBLE_DOOR(pra_03_ENTRY_1, "pra_38", pra_38_ENTRY_0, COLLIDER_deilittne, MODEL_o880, MODEL_o878);
EvtScript N(EVS_ExitDoors_pra_09_0) = EVT_EXIT_DOUBLE_DOOR(pra_03_ENTRY_2, "pra_09", pra_09_ENTRY_0, COLLIDER_deilittnne, MODEL_o989, MODEL_o988);

EvtScript N(EVS_BindExitTriggers) = {
    BindTrigger(Ref(N(EVS_ExitDoors_pra_02_1)), TRIGGER_WALL_PRESS_A, COLLIDER_deilittnnw, 1, 0)
    BindTrigger(Ref(N(EVS_ExitDoors_pra_38_0)), TRIGGER_WALL_PRESS_A, COLLIDER_deilittne, 1, 0)
    BindTrigger(Ref(N(EVS_ExitDoors_pra_09_0)), TRIGGER_WALL_PRESS_A, COLLIDER_deilittnne, 1, 0)
    Return
    End
};

EvtScript N(EVS_EnterMap) = {
    Call(GetLoadType, LVar1)
    IfEq(LVar1, LOAD_FROM_FILE_SELECT)
        Exec(EnterSavePoint)
        Exec(N(EVS_BindExitTriggers))
        Return
    EndIf
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(pra_03_ENTRY_0)
            Set(LVar2, MODEL_o774)
            Set(LVar3, DOOR_SWING_IN)
            ExecWait(EnterSingleDoor)
        CaseEq(pra_03_ENTRY_1)
            Set(LVar2, MODEL_o880)
            Set(LVar3, MODEL_o878)
            ExecWait(EnterDoubleDoor)
        CaseEq(pra_03_ENTRY_2)
            Set(LVar2, MODEL_o989)
            Set(LVar3, MODEL_o988)
            ExecWait(EnterDoubleDoor)
    EndSwitch
    Exec(N(EVS_BindExitTriggers))
    Return
    End
};

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_CRYSTAL_PALACE)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(24, 24, 40)
    ExecWait(N(EVS_MakeEntities))
    Exec(N(EVS_SetupMusic))
    IfEq(GF_PRA04_BoardedFloor, true)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilittn, COLLIDER_FLAGS_UPPER_MASK)
        Call(EnableModel, MODEL_g286, false)
    Else
        Call(EnableModel, MODEL_o998, false)
    EndIf
    Exec(N(EVS_EnterMap))
    Wait(1)
    Return
    End
};
