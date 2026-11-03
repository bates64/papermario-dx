#include "kpa_01.h"
#include "world/area/kpa/kpa_03.h"
#include "world/area/kpa/kpa_14.h"

#include "world/common/util/CreateDarkness.inc.c"

EvtScript EVS_ExitDoor_kpa_14_1 =
    EVT_EXIT_SINGLE_DOOR($LavaChannel3, $kpa_14.DarkCave1, COLLIDER_tte, MODEL_o205, DOOR_SWING_IN);

EvtScript EVS_ExitWalk_kpa_03_0 = EVT_EXIT_WALK(60, $DarkCave2, $kpa_03.DarkCave1);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitDoor_kpa_14_1, TRIGGER_WALL_PRESS_A, COLLIDER_tte, 1, 0)
    BindTrigger(EVS_ExitWalk_kpa_03_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($LavaChannel3.index)
            Set(LVar0, $LavaChannel3.index)
            Set(LVar1, MODEL_exit2)
            Set(LVar2, MODEL_o205)
            Set(LVar3, DOOR_SWING_IN)
            Exec(EnterSingleDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq($DarkCave2.index)
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_BOWSERS_CASTLE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Call(MakeNpcs, true, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_CreateDarkness)
    Exec(EVS_EnterMap)
    Wait(1)
    Exec(EVS_SetupMusic)
    Return
    End
};
