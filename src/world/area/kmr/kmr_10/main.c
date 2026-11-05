#include "kmr_10.h"
#include "world/area/kmr/kmr_11.h"
#include "world/area/mac/mac_00.h"

EvtScript EVS_ExitWalk_kmr_11_1 = EVT_EXIT_WALK(60, $GoombaKingsCastle, $kmr_11.ToadTownEntrance);
EvtScript EVS_ExitWalk_mac_00_0 = EVT_EXIT_WALK(60, $ToadTown, $mac_00.GoombaRoad);
EvtScript EVS_ExitWalk_mac_00_2 = EVT_EXIT_WALK(60, $Entry2, $mac_00.GoombaRoadUpper);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_kmr_11_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    BindTrigger(EVS_ExitWalk_mac_00_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deili2, 1, 0)
    BindTrigger(EVS_ExitWalk_mac_00_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deili3, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Return
    End
};

EvtScript EVS_Main = {
    Call(MakeNpcs, false, DefaultNPCs)
    Call(ClearDefeatedEnemies)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMusic)
    ExecWait(EVS_SetupFoliage)
    IfEq(GB_StoryProgress, STORY_CH0_KAMMY_RETURNED_TO_BOWSER)
        IfEq(AF_KMR10_LongEntryDelay, false)
            Wait(50)
            Set(AF_KMR10_LongEntryDelay, true)
        EndIf
    EndIf
    Exec(EVS_EnterMap)
    Wait(1)
    Set(GF_MAC01_RowfBadgesChosen, false)
    Return
    End
};
