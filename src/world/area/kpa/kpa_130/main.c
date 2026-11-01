#include "kpa_130.h"
#include "world/area/kpa/kpa_111.h"
#include "world/area/kpa/kpa_134.h"

EvtScript EVS_ExitDoors_kpa_134_1 =
    EVT_EXIT_DOUBLE_DOOR($RightWaterPuzzle, $kpa_134.BillBlasterHall, COLLIDER_ttw, MODEL_o11, MODEL_o9);
EvtScript EVS_ExitDoors_kpa_111_0 =
    EVT_EXIT_DOUBLE_DOOR($HiddenDoorRoom1, $kpa_111.BillBlasterHall, COLLIDER_tte, MODEL_o455, MODEL_o454);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitDoors_kpa_134_1, TRIGGER_WALL_PRESS_A, COLLIDER_ttw, 1, 0)
    BindTrigger(EVS_ExitDoors_kpa_111_0, TRIGGER_WALL_PRESS_A, COLLIDER_tte, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($RightWaterPuzzle.index)
            Set(LVar0, $RightWaterPuzzle.index)
            Set(LVar2, MODEL_o11)
            Set(LVar3, MODEL_o9)
            Exec(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq($HiddenDoorRoom1.index)
            Set(LVar0, 1)
            Set(LVar2, MODEL_o455)
            Set(LVar3, MODEL_o454)
            Exec(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_BOWSERS_CASTLE)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Call(MakeNpcs, true, DefaultNPCs)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_CLEAR_BITS, COLLIDER_ttw, COLLIDER_FLAGS_UPPER_MASK)
    Exec(EVS_EnterMap)
    Wait(1)
    Exec(EVS_SetupMusic)
    Return
    End
};
