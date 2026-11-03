#include "sbk_43.h"
#include "world/area/sbk/sbk_33.h"
#include "world/area/sbk/sbk_42.h"
#include "world/area/sbk/sbk_44.h"
#include "world/area/sbk/sbk_53.h"
#include "effects.h"
#include "entity.h"

extern EvtScript EVS_Main;
extern EvtScript EVS_MakeEntities;

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .bgName = "sbk_bg",
    .tattle = { MSG_MapTattle_sbk_43 },
};

EvtScript EVS_ExitWalk_sbk_42_1 = EVT_EXIT_WALK(60, $West, $sbk_42.East);
EvtScript EVS_ExitWalk_sbk_44_0 = EVT_EXIT_WALK(60, $East, $sbk_44.West);
EvtScript EVS_ExitWalk_sbk_33_3 = EVT_EXIT_WALK(60, $North, $sbk_33.South);
EvtScript EVS_ExitWalk_sbk_53_2 = EVT_EXIT_WALK(60, $South, $sbk_53.North);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_sbk_42_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_44_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_33_3, TRIGGER_FLOOR_ABOVE, COLLIDER_deilin, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_53_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deilis, 1, 0)
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
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Return
    End
};
