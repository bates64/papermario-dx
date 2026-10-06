#include "kmr_10.h"

EvtScript EVS_ExitWalk_kmr_11_1 = EVT_EXIT_WALK(60, kmr_10_ENTRY_0, "kmr_11", kmr_11_ENTRY_1);
EvtScript EVS_ExitWalk_mac_00_0 = EVT_EXIT_WALK(60, kmr_10_ENTRY_1, "mac_00", mac_00_ENTRY_0);
EvtScript EVS_ExitWalk_mac_00_2 = EVT_EXIT_WALK(60, kmr_10_ENTRY_2, "mac_00", mac_00_ENTRY_2);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitWalk_kmr_11_1), TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    BindTrigger(Ref(EVS_ExitWalk_mac_00_0), TRIGGER_FLOOR_ABOVE, COLLIDER_deili2, 1, 0)
    BindTrigger(Ref(EVS_ExitWalk_mac_00_2), TRIGGER_FLOOR_ABOVE, COLLIDER_deili3, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Set(LVar0, Ref(EVS_BindExitTriggers))
    Exec(EnterWalk)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_GOOMBA_ROAD)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Call(MakeNpcs, false, Ref(DefaultNPCs))
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
