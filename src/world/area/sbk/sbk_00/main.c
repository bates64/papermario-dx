#include "sbk_00.h"
#include "world/area/sbk/sbk_01.h"
#include "world/area/sbk/sbk_10.h"
#include "effects.h"

EvtScript EVS_ExitWalk_sbk_01_0 = EVT_EXIT_WALK(60, $East, $sbk_01.West);
EvtScript EVS_ExitWalk_sbk_10_2 = EVT_EXIT_WALK(60, $South, $sbk_10.North);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_sbk_01_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_10_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deilis, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_DRY_DRY_DESERT)
    IfEq(GB_StoryProgress, STORY_CH2_GOT_PULSE_STONE)
        Call(DisablePulseStone, false)
    EndIf
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, false, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    Call(SpawnSunEffect, FX_SUN_FROM_LEFT)
    Call(SetMusic, 0, SONG_DRY_DRY_DESERT, 0, VOL_LEVEL_FULL)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Return
    End
};
