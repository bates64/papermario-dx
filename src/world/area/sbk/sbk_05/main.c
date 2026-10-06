#include "sbk_05.h"
#include "effects.h"

extern EvtScript EVS_Main;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DefaultNPCs;

EntryList Entrances = {
    [sbk_05_ENTRY_0]    { -475.0,    0.0,    0.0,   90.0 },
    [sbk_05_ENTRY_1]    {  475.0,    0.0,    0.0,  270.0 },
    [sbk_05_ENTRY_2]    {    0.0,    0.0, -475.0,  180.0 },
    [sbk_05_ENTRY_3]    {    0.0,    0.0,  475.0,    0.0 },
    [sbk_05_ENTRY_4]    {  157.0,  200.0, -338.0,   90.0 },
};

export MapSettings settings = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "sbk_bg",
    .tattle = { MSG_MapTattle_sbk_05 },
};

EvtScript EVS_ExitWalk_sbk_04_1 = EVT_EXIT_WALK(60, sbk_05_ENTRY_0, "sbk_04", sbk_04_ENTRY_1);
EvtScript EVS_ExitWalk_sbk_06_0 = EVT_EXIT_WALK(60, sbk_05_ENTRY_1, "sbk_06", sbk_06_ENTRY_0);
EvtScript EVS_ExitWalk_sbk_15_2 = EVT_EXIT_WALK(60, sbk_05_ENTRY_3, "sbk_15", sbk_15_ENTRY_2);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitWalk_sbk_04_1), TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(Ref(EVS_ExitWalk_sbk_06_0), TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    BindTrigger(Ref(EVS_ExitWalk_sbk_15_2), TRIGGER_FLOOR_ABOVE, COLLIDER_deilis, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(sbk_05_ENTRY_4)
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
    Call(MakeNpcs, false, Ref(DefaultNPCs))
    ExecWait(EVS_MakeEntities)
    Call(SpawnSunEffect, FX_SUN_FROM_LEFT)
    Call(SetMusic, 0, SONG_DRY_DRY_DESERT, 0, VOL_LEVEL_FULL)
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
