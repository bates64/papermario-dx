#include "sbk_32.h"
#include "world/area/sbk/sbk_22.h"
#include "world/area/sbk/sbk_31.h"
#include "world/area/sbk/sbk_33.h"
#include "world/area/sbk/sbk_42.h"
#include "effects.h"

extern EvtScript EVS_Main;
extern NpcGroupList DefaultNPCs;

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .bgName = "sbk_bg",
    .tattle = { MSG_MapTattle_sbk_32 },
};

EvtScript EVS_ExitWalk_sbk_31_1 = EVT_EXIT_WALK(60, $West, $sbk_31.East);
EvtScript EVS_ExitWalk_sbk_33_0 = EVT_EXIT_WALK(60, $East, $sbk_33.West);
EvtScript EVS_ExitWalk_sbk_22_3 = EVT_EXIT_WALK(60, $North, $sbk_22.South);
EvtScript EVS_ExitWalk_sbk_42_2 = EVT_EXIT_WALK(60, $South, $sbk_42.North);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_sbk_31_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_33_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_22_3, TRIGGER_FLOOR_ABOVE, COLLIDER_deilin, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_42_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deilis, 1, 0)
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
    Call(MakeNpcs, false, DefaultNPCs)
    Call(SpawnSunEffect, FX_SUN_FROM_LEFT)
    Call(SetMusic, 0, SONG_DRY_DRY_DESERT, 0, VOL_LEVEL_FULL)
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
