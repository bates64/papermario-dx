#include "isk_10.h"
#include "world/area/isk/isk_08.h"
#include "world/area/isk/isk_14.h"
#include "world/area/isk/isk_18.h"

EvtScript EVS_ExitWalk_isk_08_1 = EVT_EXIT_WALK(40, $DescendingStairs2, $isk_08.VerticalShaft);
EvtScript EVS_ExitWalk_isk_14_0 = EVT_EXIT_WALK(40, $DiamondStoneRoom, $isk_14.VerticalShaft);
EvtScript EVS_ExitWalk_isk_18_0 = EVT_EXIT_WALK(40, $DeepTunnel, $isk_18.VerticalShaft);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_isk_08_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deilin, 1, 0)
    BindTrigger(EVS_ExitWalk_isk_14_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_isk_18_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_DRY_DRY_RUINS)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(SetCamSpeed, CAM_DEFAULT, 2.8)
    ExecWait(EVS_MakeEntities)
    ExecWait(EVS_SetupBombableWall)
#if VERSION_PAL
    Call(SetMusic, 0, SONG_DRY_DRY_RUINS, 0, VOL_LEVEL_FULL)
#else
    Switch(GB_StoryProgress)
        CaseLt(STORY_CH2_SOLVED_ARTIFACT_PUZZLE)
            Call(SetMusic, 0, SONG_DRY_DRY_RUINS, 0, VOL_LEVEL_FULL)
        CaseLt(STORY_CH2_DEFEATED_TUTANKOOPA)
            Call(SetMusic, 0, SONG_RUINS_BASEMENT, 0, VOL_LEVEL_FULL)
        CaseGe(STORY_CH2_DEFEATED_TUTANKOOPA)
            Call(SetMusic, 0, SONG_DRY_DRY_RUINS, 0, VOL_LEVEL_FULL)
    EndSwitch
#endif
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Return
    End
};
