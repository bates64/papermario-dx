#include "sbk_12.h"
#include "world/area/sbk/sbk_02.h"
#include "world/area/sbk/sbk_11.h"
#include "world/area/sbk/sbk_13.h"
#include "world/area/sbk/sbk_22.h"
#include "effects.h"

extern EvtScript EVS_Main;
extern NpcGroupList DefaultNPCs;

EvtScript EVS_ExitWalk_sbk_11_1 = EVT_EXIT_WALK(60, $West, $sbk_11.East);
EvtScript EVS_ExitWalk_sbk_13_0 = EVT_EXIT_WALK(60, $East, $sbk_13.West);
EvtScript EVS_ExitWalk_sbk_02_3 = EVT_EXIT_WALK(60, $North, $sbk_02.South);
EvtScript EVS_ExitWalk_sbk_22_2 = EVT_EXIT_WALK(60, $South, $sbk_22.North);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_sbk_11_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_13_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_02_3, TRIGGER_FLOOR_ABOVE, COLLIDER_deilin, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_22_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deilis, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    IfEq(GB_StoryProgress, STORY_CH2_GOT_PULSE_STONE)
        Call(DisablePulseStone, false)
    EndIf
    Call(MakeNpcs, false, DefaultNPCs)
    Call(SpawnSunEffect, FX_SUN_FROM_LEFT)
    Call(SetMusic, 0, SONG_DRY_DRY_DESERT, 0, VOL_LEVEL_FULL)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Return
    End
};
