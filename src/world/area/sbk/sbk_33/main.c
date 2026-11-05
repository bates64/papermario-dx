#include "sbk_33.h"
#include "world/area/sbk/sbk_23.h"
#include "world/area/sbk/sbk_32.h"
#include "world/area/sbk/sbk_34.h"
#include "world/area/sbk/sbk_43.h"
#include "effects.h"

extern EvtScript EVS_MakeEntities;

EvtScript EVS_ExitWalk_sbk_32_1 = EVT_EXIT_WALK(60, $West, $sbk_32.East);
EvtScript EVS_ExitWalk_sbk_34_0 = EVT_EXIT_WALK(60, $East, $sbk_34.West);
EvtScript EVS_ExitWalk_sbk_23_3 = EVT_EXIT_WALK(60, $North, $sbk_23.South);
EvtScript EVS_ExitWalk_sbk_43_2 = EVT_EXIT_WALK(60, $South, $sbk_43.North);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_sbk_32_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_34_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_23_3, TRIGGER_FLOOR_ABOVE, COLLIDER_deilin, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_43_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deilis, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    IfEq(GB_StoryProgress, STORY_CH2_GOT_PULSE_STONE)
        Call(DisablePulseStone, false)
    EndIf
    ExecWait(EVS_MakeEntities)
    Call(SpawnSunEffect, FX_SUN_FROM_LEFT)
    Call(SetMusic, 0, SONG_DRY_DRY_DESERT, 0, VOL_LEVEL_FULL)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Return
    End
};
