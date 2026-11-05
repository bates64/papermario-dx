#include "sbk_41.h"
#include "world/area/sbk/sbk_31.h"
#include "world/area/sbk/sbk_40.h"
#include "world/area/sbk/sbk_42.h"
#include "world/area/sbk/sbk_51.h"
#include "effects.h"

extern EvtScript EVS_Main;
extern EvtScript EVS_MakeEntities;

EvtScript EVS_ExitWalk_sbk_40_1 = EVT_EXIT_WALK(60, $West, $sbk_40.East);
EvtScript EVS_ExitWalk_sbk_42_0 = EVT_EXIT_WALK(60, $East, $sbk_42.West);
EvtScript EVS_ExitWalk_sbk_31_3 = EVT_EXIT_WALK(60, $North, $sbk_31.South);
EvtScript EVS_ExitWalk_sbk_51_2 = EVT_EXIT_WALK(60, $South, $sbk_51.North);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_sbk_40_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_42_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_31_3, TRIGGER_FLOOR_ABOVE, COLLIDER_deilin, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_51_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deilis, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_DRY_DRY_DESERT)
    IfEq(GB_StoryProgress, STORY_CH2_GOT_PULSE_STONE)
        Call(DisablePulseStone, false)
    EndIf
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    ExecWait(EVS_MakeEntities)
    Call(SpawnSunEffect, FX_SUN_FROM_LEFT)
    Call(SetMusic, 0, SONG_DRY_DRY_DESERT, 0, VOL_LEVEL_FULL)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Return
    End
};
