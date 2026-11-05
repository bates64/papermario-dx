
#include "kpa_51.h"
#include "world/area/kpa/kpa_133.h"
#include "world/area/kpa/kpa_32.h"

export s32 map_init(void) {
    use_map_geometry("kpa_50");
    return false;
}

EvtScript EVS_ExitDoors_kpa_32_2 =
    EVT_EXIT_DOUBLE_DOOR($LowerGrandHall, $kpa_32.WaterPuzzleHall, COLLIDER_ttw, MODEL_o321, MODEL_o323);
EvtScript EVS_ExitDoors_kpa_133_0 =
    EVT_EXIT_DOUBLE_DOOR($LeftWaterPuzzle, $kpa_133.WaterPuzzleHall, COLLIDER_tte, MODEL_o324, MODEL_o322);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitDoors_kpa_32_2, TRIGGER_WALL_PRESS_A, COLLIDER_ttw, 1, 0)
    BindTrigger(EVS_ExitDoors_kpa_133_0, TRIGGER_WALL_PRESS_A, COLLIDER_tte, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($LowerGrandHall.index)
            Set(LVar0, $LowerGrandHall.index)
            Set(LVar2, MODEL_o321)
            Set(LVar3, MODEL_o323)
            Exec(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq($LeftWaterPuzzle.index)
            Set(LVar0, $LeftWaterPuzzle.index)
            Set(LVar2, MODEL_o324)
            Set(LVar3, MODEL_o322)
            Exec(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Call(MakeNpcs, true, DefaultNPCs)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_CLEAR_BITS, COLLIDER_ttw, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_CLEAR_BITS, COLLIDER_tte, COLLIDER_FLAGS_UPPER_MASK)
    Exec(EVS_EnterMap)
    Wait(1)
    Exec(EVS_SetupMusic)
    Return
    End
};
