#include "sbk_21.h"
#include "world/area/sbk/sbk_11.h"
#include "world/area/sbk/sbk_20.h"
#include "world/area/sbk/sbk_22.h"
#include "world/area/sbk/sbk_31.h"
#include "effects.h"

extern EvtScript EVS_Main;

EvtScript EVS_ExitWalk_sbk_20_1 = EVT_EXIT_WALK(60, $West, $sbk_20.East);
EvtScript EVS_ExitWalk_sbk_22_0 = EVT_EXIT_WALK(60, $East, $sbk_22.West);
EvtScript EVS_ExitWalk_sbk_11_3 = EVT_EXIT_WALK(60, $North, $sbk_11.South);
EvtScript EVS_ExitWalk_sbk_31_2 = EVT_EXIT_WALK(60, $South, $sbk_31.North);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_sbk_20_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_22_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_11_3, TRIGGER_FLOOR_ABOVE, COLLIDER_deilin, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_31_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deilis, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_DRY_DRY_DESERT)
    IfEq(GB_StoryProgress, STORY_CH2_GOT_PULSE_STONE)
        Call(DisablePulseStone, false)
    EndIf
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(SpawnSunEffect, FX_SUN_FROM_LEFT)
    Call(SetMusic, 0, SONG_DRY_DRY_DESERT, 0, VOL_LEVEL_FULL)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Return
    End
};
