#include "sbk_25.h"
#include "world/area/sbk/sbk_15.h"
#include "world/area/sbk/sbk_24.h"
#include "world/area/sbk/sbk_26.h"
#include "world/area/sbk/sbk_35.h"
#include "effects.h"

extern EvtScript EVS_Main;
extern NpcGroupList DefaultNPCs;
extern EvtScript EVS_SetupFoliage;
extern EvtScript EVS_MakeEntities;

EvtScript EVS_ExitWalk_sbk_24_1 = EVT_EXIT_WALK(60, $West, $sbk_24.East);
EvtScript EVS_ExitWalk_sbk_26_0 = EVT_EXIT_WALK(60, $East, $sbk_26.West);
EvtScript EVS_ExitWalk_sbk_15_3 = EVT_EXIT_WALK(60, $North, $sbk_15.South);
EvtScript EVS_ExitWalk_sbk_35_2 = EVT_EXIT_WALK(60, $South, $sbk_35.North);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_sbk_24_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_26_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_15_3, TRIGGER_FLOOR_ABOVE, COLLIDER_deilin, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_35_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deilis, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    IfEq(GB_StoryProgress, STORY_CH2_GOT_PULSE_STONE)
        Call(DisablePulseStone, false)
    EndIf
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
