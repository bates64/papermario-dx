#include "kpa_82.h"
#include "world/area/kpa/kpa_113.h"
#include "world/area/kpa/kpa_61.h"

export s32 map_init(void) {
    use_map_geometry("kpa_80");
    return false;
}

s32 RightDoorModels[] = {
    MODEL_o140,
    MODEL_o142,
    MODEL_o121,
    MODEL_g35,
    MODEL_o116,
    MODEL_o170,
    -1
};

s32 LeftDoorModels[] = {
    MODEL_o161,
    MODEL_o162,
    MODEL_o119,
    MODEL_g33,
    MODEL_o126,
    MODEL_o171,
    -1
};

EvtScript EVS_ExitDoors_kpa_113_1 =
    EVT_EXIT_DOUBLE_DOOR($HiddenDoorRoom2, $kpa_113.GuardDoor2, COLLIDER_deilittw, MODEL_o174, MODEL_o173);

EvtScript EVS_ExitDoors_kpa_61_0 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Set(LVar0, $Battlement.index)
    Set(LVar1, COLLIDER_o166)
    Set(LVar2, RightDoorModels)
    Set(LVar3, LeftDoorModels)
    Exec(BaseExitDoor)
    Wait(17)
    Call(GotoMap, $kpa_61.GuardDoor2)
    Wait(100)
    Return
    End
};

EvtScript EVS_Inspect_FaceDoor = {
    IfEq(GF_KPA82_PassedThroughDoor, true)
        Return
    EndIf
    Set(GF_KPA82_PassedThroughDoor, true)
    Return
    End
};

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitDoors_kpa_113_1, TRIGGER_WALL_PRESS_A, COLLIDER_deilittw, 1, 0)
    IfEq(GB_KPA82_BowserDoorState, 0)
        BindTrigger(EVS_Inspect_FaceDoor, TRIGGER_WALL_PRESS_A, COLLIDER_o166, 1, 0)
    Else
        BindTrigger(EVS_ExitDoors_kpa_61_0, TRIGGER_WALL_PRESS_A, COLLIDER_o166, 1, 0)
    EndIf
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($HiddenDoorRoom2.index)
            Set(LVar0, $HiddenDoorRoom2.index)
            Set(LVar2, MODEL_o174)
            Set(LVar3, MODEL_o173)
            Exec(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq($Battlement.index)
            Set(LVar0, $Battlement.index)
            Set(LVar2, LeftDoorModels)
            Set(LVar3, RightDoorModels)
            ExecWait(BaseEnterDoor)
            Exec(EVS_BindExitTriggers)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_BOWSERS_CASTLE)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, true, DefaultNPCs)
    Call(EnableModel, MODEL_o166, false)
    Call(EnableModel, MODEL_m_, false)
    Call(EnableModel, MODEL_m_kai, false)
    Call(EnableModel, MODEL_m1, false)
    Call(EnableModel, MODEL_m2, false)
    Call(EnableModel, MODEL_m3, false)
    Call(EnableModel, MODEL_m4, false)
    Call(EnableModel, MODEL_m5, false)
    Call(EnableModel, MODEL_m6, false)
    Call(EnableModel, MODEL_m7, false)
    Call(EnableModel, MODEL_b_, false)
    Call(EnableModel, MODEL_b_kai, false)
    Call(EnableModel, MODEL_b1, false)
    Call(EnableModel, MODEL_b2, false)
    Call(EnableModel, MODEL_b3, false)
    Call(EnableModel, MODEL_b4, false)
    Call(EnableModel, MODEL_b5, false)
    Call(EnableModel, MODEL_b6, false)
    Call(EnableModel, MODEL_b7, false)
    Exec(EVS_EnterMap)
    Wait(1)
    Exec(EVS_SetupMusic)
    Return
    End
};
