#include "sbk_51.h"
#include "world/area/sbk/sbk_41.h"
#include "world/area/sbk/sbk_50.h"
#include "world/area/sbk/sbk_52.h"
#include "world/area/sbk/sbk_61.h"
#include "effects.h"

extern EvtScript EVS_Main;
extern NpcGroupList DefaultNPCs;

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .bgName = "sbk_bg",
    .tattle = { MSG_MapTattle_sbk_51 },
};

EvtScript EVS_ExitWalk_sbk_50_1 = EVT_EXIT_WALK(60, $West, $sbk_50.East);
EvtScript EVS_ExitWalk_sbk_52_0 = EVT_EXIT_WALK(60, $East, $sbk_52.West);
EvtScript EVS_ExitWalk_sbk_41_3 = EVT_EXIT_WALK(60, $North, $sbk_41.South);
EvtScript EVS_ExitWalk_sbk_61_2 = EVT_EXIT_WALK(60, $South, $sbk_61.North);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_sbk_50_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_52_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_41_3, TRIGGER_FLOOR_ABOVE, COLLIDER_deilin, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_61_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deilis, 1, 0)
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
