#include "arn_13.h"

EvtScript EVS_ExitDoor_arn_12_1 = EVT_EXIT_SINGLE_DOOR(arn_13_ENTRY_0, "arn_12", arn_12_ENTRY_1,
    COLLIDER_ttw, MODEL_o44, DOOR_SWING_IN);

EvtScript EVS_ExitDoor_arn_11_0 = EVT_EXIT_SINGLE_DOOR(arn_13_ENTRY_1, "arn_11", arn_12_ENTRY_0,
    COLLIDER_tte, MODEL_o37, DOOR_SWING_OUT);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitDoor_arn_12_1), TRIGGER_WALL_PRESS_A, COLLIDER_ttw, 1, 0)
    BindTrigger(Ref(EVS_ExitDoor_arn_11_0), TRIGGER_WALL_PRESS_A, COLLIDER_tte, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(arn_13_ENTRY_0)
            Set(LVar2, MODEL_o44)
            Set(LVar3, DOOR_SWING_IN)
            ExecWait(EnterSingleDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq(arn_13_ENTRY_1)
            Set(LVar2, MODEL_o37)
            Set(LVar3, DOOR_SWING_OUT)
            ExecWait(EnterSingleDoor)
            Exec(EVS_BindExitTriggers)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_WINDY_MILL)
    Call(SetSpriteShading, SHADING_ARN_13)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, false, Ref(DefaultNPCs))
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMusic)
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
