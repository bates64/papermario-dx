#include "pra_04.h"

EvtScript N(EVS_ExitDoor_pra_02_4) = EVT_EXIT_SINGLE_DOOR(pra_04_ENTRY_0, "pra_02", pra_02_ENTRY_4,
    COLLIDER_deilittssw, MODEL_o847, DOOR_SWING_OUT);

EvtScript N(EVS_ExitDoors_pra_39_0) = EVT_EXIT_DOUBLE_DOOR(pra_04_ENTRY_1, "pra_39", pra_39_ENTRY_0, COLLIDER_deilittse, MODEL_o874, MODEL_o876);
EvtScript N(EVS_ExitDoors_pra_10_0) = EVT_EXIT_DOUBLE_DOOR(pra_04_ENTRY_2, "pra_10", pra_10_ENTRY_0, COLLIDER_deilittsse, MODEL_o986, MODEL_o987);

EvtScript N(EVS_BindExitTriggers) = {
    BindTrigger(Ref(N(EVS_ExitDoor_pra_02_4)), TRIGGER_WALL_PRESS_A, COLLIDER_deilittssw, 1, 0)
    BindTrigger(Ref(N(EVS_ExitDoors_pra_39_0)), TRIGGER_WALL_PRESS_A, COLLIDER_deilittse, 1, 0)
    BindTrigger(Ref(N(EVS_ExitDoors_pra_10_0)), TRIGGER_WALL_PRESS_A, COLLIDER_deilittsse, 1, 0)
    Return
    End
};

EvtScript N(EVS_EnterMap) = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(pra_04_ENTRY_0)
            Set(LVar2, MODEL_o847)
            Set(LVar3, DOOR_SWING_OUT)
            ExecWait(EnterSingleDoor)
        CaseEq(pra_04_ENTRY_1)
            Set(LVar2, MODEL_o874)
            Set(LVar3, MODEL_o876)
            ExecWait(EnterDoubleDoor)
        CaseEq(pra_04_ENTRY_2)
            Set(LVar2, MODEL_o986)
            Set(LVar3, MODEL_o987)
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
    Call(MakeNpcs, TRUE, Ref(N(DefaultNPCs)))
    ExecWait(N(EVS_MakeEntities))
    Exec(N(EVS_SetupMusic))
    IfEq(GF_PRA04_BoardedFloor, TRUE)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitts, COLLIDER_FLAGS_UPPER_MASK)
        Call(EnableModel, MODEL_o994, FALSE)
    EndIf
    Exec(N(EVS_EnterMap))
    Wait(1)
    Return
    End
};
