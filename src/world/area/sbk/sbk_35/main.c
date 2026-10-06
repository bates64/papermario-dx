#include "sbk_35.h"
#include "effects.h"

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupFoliage;
extern NpcGroupList DefaultNPCs;

EntryList Entrances = {
    [sbk_35_ENTRY_0]    { -475.0,    0.0,    0.0,   90.0 },
    [sbk_35_ENTRY_1]    {  475.0,    0.0,    0.0,  270.0 },
    [sbk_35_ENTRY_2]    {    0.0,    0.0, -475.0,  180.0 },
    [sbk_35_ENTRY_3]    {    0.0,    0.0,  475.0,    0.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "sbk_bg",
    .tattle = { MSG_MapTattle_sbk_35 },
};

EvtScript EVS_ExitWalk_sbk_34_1 = EVT_EXIT_WALK(60, sbk_35_ENTRY_0, "sbk_34", sbk_34_ENTRY_1);
EvtScript EVS_ExitWalk_sbk_36_0 = EVT_EXIT_WALK(60, sbk_35_ENTRY_1, "sbk_36", sbk_36_ENTRY_0);
EvtScript EVS_ExitWalk_sbk_25_3 = EVT_EXIT_WALK(60, sbk_35_ENTRY_2, "sbk_25", sbk_25_ENTRY_3);
EvtScript EVS_ExitWalk_sbk_45_2 = EVT_EXIT_WALK(60, sbk_35_ENTRY_3, "sbk_45", sbk_45_ENTRY_2);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitWalk_sbk_34_1), TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(Ref(EVS_ExitWalk_sbk_36_0), TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    BindTrigger(Ref(EVS_ExitWalk_sbk_25_3), TRIGGER_FLOOR_ABOVE, COLLIDER_deilin, 1, 0)
    BindTrigger(Ref(EVS_ExitWalk_sbk_45_2), TRIGGER_FLOOR_ABOVE, COLLIDER_deilis, 1, 0)
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
    Call(MakeNpcs, false, Ref(DefaultNPCs))
    Call(SpawnSunEffect, FX_SUN_FROM_LEFT)
    Call(SetMusic, 0, SONG_DRY_DRY_DESERT, 0, VOL_LEVEL_FULL)
    Set(LVar0, Ref(EVS_BindExitTriggers))
    Exec(EnterWalk)
    Exec(EVS_SetupFoliage)
    Return
    End
};
