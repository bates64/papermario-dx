#include "sbk_36.h"
#include "world/area/dro/dro_01.h"
#include "world/area/sbk/sbk_26.h"
#include "world/area/sbk/sbk_35.h"
#include "world/area/sbk/sbk_46.h"
#include "effects.h"

extern EvtScript EVS_Main;
extern EvtScript EVS_MakeEntities;
extern EvtScript EVS_SetupFoliage;

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .bgName = "sbk_bg",
    .tattle = { MSG_MapTattle_sbk_36 },
};

EvtScript EVS_ExitWalk_sbk_35_1 = EVT_EXIT_WALK(60, $West, $sbk_35.East);
EvtScript EVS_ExitWalk_dro_01_0 = EVT_EXIT_WALK(60, $DryDryOutpost, $dro_01.DryDryDesert);
EvtScript EVS_ExitWalk_sbk_26_3 = EVT_EXIT_WALK(60, $North, $sbk_26.South);
EvtScript EVS_ExitWalk_sbk_46_2 = EVT_EXIT_WALK(60, $South, $sbk_46.North);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_sbk_35_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_dro_01_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_26_3, TRIGGER_FLOOR_ABOVE, COLLIDER_deilin, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_46_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deilis, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_DRY_DRY_DESERT)
    Call(SetSpriteShading, SHADING_NONE)
    IfEq(GB_StoryProgress, STORY_CH2_GOT_PULSE_STONE)
        Call(DisablePulseStone, false)
    EndIf
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    ExecWait(EVS_MakeEntities)
    Call(SpawnSunEffect, FX_SUN_FROM_LEFT)
    Call(SetMusic, 0, SONG_DRY_DRY_DESERT, 0, VOL_LEVEL_FULL)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Exec(EVS_SetupFoliage)
    Return
    End
};
