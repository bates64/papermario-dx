#include "kpa_09.h"
#include "world/area/kpa/kpa_101.h"
#include "world/area/kpa/kpa_33.h"

EvtScript EVS_ExitWalk_kpa_101_0 = EVT_EXIT_WALK(60, $ShroomRoom, $kpa_101.ShroomTimingPuzzle);
EvtScript EVS_ExitDoors_kpa_33_3 =
    EVT_EXIT_DOUBLE_DOOR($UpperGrandHall, $kpa_33.ShroomTimingPuzzle, COLLIDER_tte, MODEL_o159, MODEL_o160);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_kpa_101_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    BindTrigger(EVS_ExitDoors_kpa_33_3, TRIGGER_WALL_PRESS_A, COLLIDER_ttw, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($ShroomRoom.index)
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
            Wait(1)
        CaseEq($UpperGrandHall.index)
            Set(LVar0, 1)
            Set(LVar2, MODEL_o159)
            Set(LVar3, MODEL_o160)
            Exec(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Call(MakeNpcs, true, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_tte, COLLIDER_FLAGS_UPPER_MASK)
    Call(EnableModel, MODEL_o180, false)
    Call(EnableModel, MODEL_o181, false)
    Exec(EVS_EnterMap)
    Wait(1)
    Exec(EVS_SetupMusic)
    Return
    End
};
