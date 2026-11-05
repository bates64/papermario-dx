#include "sbk_53.h"
#include "world/area/sbk/sbk_43.h"
#include "world/area/sbk/sbk_52.h"
#include "world/area/sbk/sbk_54.h"
#include "world/area/sbk/sbk_63.h"
#include "effects.h"

extern EvtScript EVS_Main;
extern NpcGroupList DefaultNPCs;

EvtScript EVS_ExitWalk_sbk_52_1 = EVT_EXIT_WALK(60, $West, $sbk_52.East);
EvtScript EVS_ExitWalk_sbk_54_0 = EVT_EXIT_WALK(60, $East, $sbk_54.West);
EvtScript EVS_ExitWalk_sbk_43_3 = EVT_EXIT_WALK(60, $North, $sbk_43.South);
EvtScript EVS_ExitWalk_sbk_63_2 = EVT_EXIT_WALK(60, $South, $sbk_63.North);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_sbk_52_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_54_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_43_3, TRIGGER_FLOOR_ABOVE, COLLIDER_deilin, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_63_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deilis, 1, 0)
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
