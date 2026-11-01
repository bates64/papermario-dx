#include "kpa_50.h"
#include "world/area/kpa/kpa_70.h"
#include "world/area/kpa/kpa_81.h"

EvtScript EVS_ExitWalk_kpa_70_1 = EVT_EXIT_WALK(60, $EntryLavaHall, $kpa_70.GuardDoor1Hall);
EvtScript EVS_ExitDoors_kpa_81_0 =
    EVT_EXIT_DOUBLE_DOOR($GuardDoor1, $kpa_81.GuardDoor1Hall, COLLIDER_tte, MODEL_o324, MODEL_o322);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_kpa_70_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitDoors_kpa_81_0, TRIGGER_WALL_PRESS_A, COLLIDER_tte, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($EntryLavaHall.index)
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
        CaseEq($GuardDoor1.index)
            Set(LVar0, $GuardDoor1.index)
            Set(LVar2, MODEL_o324)
            Set(LVar3, MODEL_o322)
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
    Call(SetGroupVisibility, MODEL_dw1, MODEL_GROUP_HIDDEN)
    Call(SetGroupVisibility, MODEL_dw2, MODEL_GROUP_HIDDEN)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_CLEAR_BITS, COLLIDER_tte, COLLIDER_FLAGS_UPPER_MASK)
    Exec(EVS_EnterMap)
    Wait(1)
    Exec(EVS_SetupMusic)
    Return
    End
};
