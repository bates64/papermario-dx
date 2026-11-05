#include "sbk_24.h"
#include "world/area/sbk/sbk_14.h"
#include "world/area/sbk/sbk_23.h"
#include "world/area/sbk/sbk_25.h"
#include "world/area/sbk/sbk_34.h"
#include "effects.h"
#include "entity.h"

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupFoliage;
extern EvtScript EVS_MakeEntities;

EvtScript EVS_ExitWalk_sbk_23_1 = EVT_EXIT_WALK(60, $West, $sbk_23.East);
EvtScript EVS_ExitWalk_sbk_25_0 = EVT_EXIT_WALK(60, $East, $sbk_25.West);
EvtScript EVS_ExitWalk_sbk_14_3 = EVT_EXIT_WALK(60, $North, $sbk_14.South);
EvtScript EVS_ExitWalk_sbk_34_2 = EVT_EXIT_WALK(60, $South, $sbk_34.North);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_sbk_23_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_25_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_14_3, TRIGGER_FLOOR_ABOVE, COLLIDER_deilin, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_34_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deilis, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($Pipe.index)
            Exec(EVS_BindExitTriggers)
        CaseDefault
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
    EndSwitch
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
    Exec(EVS_EnterMap)
    Wait(1)
    Exec(EVS_SetupFoliage)
    Return
    End
};
