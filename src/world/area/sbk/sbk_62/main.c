#include "sbk_62.h"
#include "world/area/sbk/sbk_52.h"
#include "world/area/sbk/sbk_61.h"
#include "world/area/sbk/sbk_63.h"
#include "effects.h"

extern EvtScript EVS_Main;
extern NpcGroupList DefaultNPCs;

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .bgName = "sbk_bg",
    .tattle = { MSG_MapTattle_sbk_62 },
};

EvtScript EVS_ExitWalk_sbk_61_1 = EVT_EXIT_WALK(60, $West, $sbk_61.East);
EvtScript EVS_ExitWalk_sbk_63_0 = EVT_EXIT_WALK(60, $East, $sbk_63.West);
EvtScript EVS_ExitWalk_sbk_52_3 = EVT_EXIT_WALK(60, $North, $sbk_52.South);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_sbk_61_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_63_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_52_3, TRIGGER_FLOOR_ABOVE, COLLIDER_deilin, 1, 0)
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
