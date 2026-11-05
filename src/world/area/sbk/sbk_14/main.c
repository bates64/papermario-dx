#include "sbk_14.h"
#include "world/area/sbk/sbk_04.h"
#include "world/area/sbk/sbk_13.h"
#include "world/area/sbk/sbk_15.h"
#include "world/area/sbk/sbk_24.h"
#include "effects.h"
#include "entity.h"

extern EvtScript EVS_Main;
extern EvtScript EVS_MakeEntities;

EvtScript EVS_ExitWalk_sbk_13_1 = EVT_EXIT_WALK(60, $West, $sbk_13.East);
EvtScript EVS_ExitWalk_sbk_15_0 = EVT_EXIT_WALK(60, $East, $sbk_15.West);
EvtScript EVS_ExitWalk_sbk_04_3 = EVT_EXIT_WALK(60, $North, $sbk_04.South);
EvtScript EVS_ExitWalk_sbk_24_2 = EVT_EXIT_WALK(60, $South, $sbk_24.North);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_sbk_13_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_15_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_04_3, TRIGGER_FLOOR_ABOVE, COLLIDER_deilin, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_24_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deilis, 1, 0)
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
    Set(GB_WorldLocation, LOCATION_DRY_DRY_DESERT)
    IfEq(GB_StoryProgress, STORY_CH2_GOT_PULSE_STONE)
        Call(DisablePulseStone, false)
    EndIf
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    ExecWait(EVS_MakeEntities)
    Call(SpawnSunEffect, FX_SUN_FROM_LEFT)
    Call(SetMusic, 0, SONG_DRY_DRY_DESERT, 0, VOL_LEVEL_FULL)
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
