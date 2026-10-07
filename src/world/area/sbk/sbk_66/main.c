#include "sbk_66.h"
#include "effects.h"

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupFoliage;
extern NpcGroupList DefaultNPCs;
extern EvtScript EVS_MakeEntities;

EntryList Entrances = {
    [sbk_66_ENTRY_0]    { -475.0,    0.0,    0.0,   90.0 },
    [sbk_66_ENTRY_1]    {  475.0,    0.0,    0.0,  270.0 },
    [sbk_66_ENTRY_2]    {    0.0,    0.0, -475.0,  180.0 },
    [sbk_66_ENTRY_3]    {    0.0,    0.0,  475.0,    0.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "sbk_bg",
    .tattle = { MSG_MapTattle_sbk_66 },
};

EvtScript EVS_ExitWalk_sbk_65_1 = EVT_EXIT_WALK(60, sbk_66_ENTRY_0, "sbk_65", sbk_65_ENTRY_1);
EvtScript EVS_ExitWalk_sbk_56_3 = EVT_EXIT_WALK(60, sbk_66_ENTRY_2, "sbk_56", sbk_56_ENTRY_3);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitWalk_sbk_65_1), TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(Ref(EVS_ExitWalk_sbk_56_3), TRIGGER_FLOOR_ABOVE, COLLIDER_deilin, 1, 0)
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
    ExecWait(EVS_MakeEntities)
    Call(SpawnSunEffect, FX_SUN_FROM_LEFT)
    Call(SetMusic, 0, SONG_DRY_DRY_DESERT, 0, VOL_LEVEL_FULL)
    Set(LVar0, Ref(EVS_BindExitTriggers))
    Exec(EnterWalk)
    Exec(EVS_SetupFoliage)
    Return
    End
};
