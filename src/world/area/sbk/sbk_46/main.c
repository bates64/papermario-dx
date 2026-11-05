#include "sbk_46.h"
#include "world/area/sbk/sbk_36.h"
#include "world/area/sbk/sbk_45.h"
#include "world/area/sbk/sbk_56.h"
#include "effects.h"

extern EvtScript EVS_Main;
extern NpcGroupList DefaultNPCs;
extern EvtScript EVS_SetupFoliage;
extern EvtScript EVS_MakeEntities;

EvtScript EVS_ExitWalk_sbk_45_1 = EVT_EXIT_WALK(60, $West, $sbk_45.East);
EvtScript EVS_ExitWalk_sbk_36_3 = EVT_EXIT_WALK(60, $North, $sbk_36.South);
EvtScript EVS_ExitWalk_sbk_56_2 = EVT_EXIT_WALK(60, $South, $sbk_56.North);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_sbk_45_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_36_3, TRIGGER_FLOOR_ABOVE, COLLIDER_deilin, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_56_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deilis, 1, 0)
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
    Exec(EVS_SetupFoliage)
    Return
    End
};
