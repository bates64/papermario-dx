#include "sbk_42.h"
#include "world/area/sbk/sbk_32.h"
#include "world/area/sbk/sbk_41.h"
#include "world/area/sbk/sbk_43.h"
#include "world/area/sbk/sbk_52.h"
#include "effects.h"

extern EvtScript EVS_Main;
extern NpcGroupList DefaultNPCs;

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .bgName = "sbk_bg",
    .tattle = { MSG_MapTattle_sbk_42 },
};

EvtScript EVS_ExitWalk_sbk_41_1 = EVT_EXIT_WALK(60, $West, $sbk_41.East);
EvtScript EVS_ExitWalk_sbk_43_0 = EVT_EXIT_WALK(60, $East, $sbk_43.West);
EvtScript EVS_ExitWalk_sbk_32_3 = EVT_EXIT_WALK(60, $North, $sbk_32.South);
EvtScript EVS_ExitWalk_sbk_52_2 = EVT_EXIT_WALK(60, $South, $sbk_52.North);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_sbk_41_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_43_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_32_3, TRIGGER_FLOOR_ABOVE, COLLIDER_deilin, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_52_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deilis, 1, 0)
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
    Call(SpawnSunEffect, FX_SUN_FROM_LEFT)
    Call(SetMusic, 0, SONG_DRY_DRY_DESERT, 0, VOL_LEVEL_FULL)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Return
    End
};
