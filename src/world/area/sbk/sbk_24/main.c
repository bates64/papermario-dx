#include "sbk_24.h"
#include "effects.h"
#include "entity.h"

extern EvtScript EVS_Main;
extern EvtScript EVS_SetupFoliage;
extern EvtScript EVS_MakeEntities;

EntryList Entrances = {
    [sbk_24_ENTRY_0]    { -475.0,    0.0,    0.0,   90.0 },
    [sbk_24_ENTRY_1]    {  475.0,    0.0,    0.0,  270.0 },
    [sbk_24_ENTRY_2]    {    0.0,    0.0, -475.0,  180.0 },
    [sbk_24_ENTRY_3]    {    0.0,    0.0,  475.0,    0.0 },
    [sbk_24_ENTRY_4]    {  157.0,  200.0, -338.0,   90.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "sbk_bg",
    .tattle = { MSG_MapTattle_sbk_24 },
};

EvtScript EVS_ExitWalk_sbk_23_1 = EVT_EXIT_WALK(60, sbk_24_ENTRY_0, "sbk_23", sbk_23_ENTRY_1);
EvtScript EVS_ExitWalk_sbk_25_0 = EVT_EXIT_WALK(60, sbk_24_ENTRY_1, "sbk_25", sbk_25_ENTRY_0);
EvtScript EVS_ExitWalk_sbk_14_3 = EVT_EXIT_WALK(60, sbk_24_ENTRY_2, "sbk_14", sbk_14_ENTRY_3);
EvtScript EVS_ExitWalk_sbk_34_2 = EVT_EXIT_WALK(60, sbk_24_ENTRY_3, "sbk_34", sbk_34_ENTRY_2);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitWalk_sbk_23_1), TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(Ref(EVS_ExitWalk_sbk_25_0), TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    BindTrigger(Ref(EVS_ExitWalk_sbk_14_3), TRIGGER_FLOOR_ABOVE, COLLIDER_deilin, 1, 0)
    BindTrigger(Ref(EVS_ExitWalk_sbk_34_2), TRIGGER_FLOOR_ABOVE, COLLIDER_deilis, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(sbk_24_ENTRY_4)
            Exec(EVS_BindExitTriggers)
        CaseDefault
            Set(LVar0, Ref(EVS_BindExitTriggers))
            Exec(EnterWalk)
    EndSwitch
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
    Exec(EVS_EnterMap)
    Wait(1)
    Exec(EVS_SetupFoliage)
    Return
    End
};
