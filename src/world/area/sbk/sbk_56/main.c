
#include "sbk_56.h"
#include "world/area/sbk/sbk_46.h"
#include "world/area/sbk/sbk_55.h"
#include "world/area/sbk/sbk_66.h"
#include "effects.h"

extern EvtScript EVS_Main;
extern EvtScript EVS_MakeEntities;
extern EvtScript EVS_SetupFoliage;

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
    .bgName = "sbk_bg",
    .tattle = { MSG_MapTattle_sbk_56 },
};

API_CALLABLE(StartOasisTracks) {
    bgm_set_linked_mode(0, 1);
    return ApiStatus_DONE2;
}

API_CALLABLE(StopOasisTracks) {
    bgm_set_linked_mode(0, 0);
    return ApiStatus_DONE2;
}

EvtScript EVS_ExitWalk_sbk_55_1 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(UseExitHeading, 60, $West.index)
    Exec(ExitWalk)
    Call(StopOasisTracks)
    Call(GotoMap, $sbk_55.East)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitWalk_sbk_46_3 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(UseExitHeading, 60, $North.index)
    Exec(ExitWalk)
    Call(StopOasisTracks)
    Call(GotoMap, $sbk_46.South)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitWalk_sbk_66_2 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(UseExitHeading, 60, $South.index)
    Exec(ExitWalk)
    Call(StopOasisTracks)
    Call(GotoMap, $sbk_66.North)
    Wait(100)
    Return
    End
};

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_sbk_55_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_46_3, TRIGGER_FLOOR_ABOVE, COLLIDER_deilin, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_66_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deilis, 1, 0)
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
    Call(MakeTransformGroup, MODEL_sui)
    Call(SetMusic, 0, SONG_DRY_DRY_DESERT, 0, VOL_LEVEL_FULL)
    Call(StartOasisTracks)
    Call(PlaySound, SOUND_LOOP_SBK_OASIS_WATER)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Exec(EVS_SetupFoliage)
    Call(SetTexPanner, MODEL_o49, TEX_PANNER_1)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_1)
        TEX_PAN_PARAMS_STEP(   80,   80,  -80,  -80)
        TEX_PAN_PARAMS_FREQ(    1,    1,    1,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Return
    End
};
