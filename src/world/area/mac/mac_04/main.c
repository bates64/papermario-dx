#include "mac_04.h"
#include "model.h"

API_CALLABLE(SetNightFogParams) {
    Bytecode* args = script->ptrReadPos;
    s32 primR = evt_get_variable(script, *args++);
    s32 primG = evt_get_variable(script, *args++);
    s32 primB = evt_get_variable(script, *args++);
    s32 primA = evt_get_variable(script, *args++);
    s32 fogR = evt_get_variable(script, *args++);
    s32 fogG = evt_get_variable(script, *args++);
    s32 fogB = evt_get_variable(script, *args++);
    s32 fogStart = evt_get_variable(script, *args++);
    s32 fogEnd = evt_get_variable(script, *args++);

    mdl_set_depth_tint_params(primR, primG, primB, primA, fogR, fogG, fogB, fogStart, fogEnd);
    return ApiStatus_DONE2;
}

API_CALLABLE(SetNightTintMode) {
    mdl_set_all_tint_type(ENV_TINT_REMAP);
    return ApiStatus_DONE2;
}

EvtScript EVS_ExitWalk_mac_05_0 = EVT_EXIT_WALK(60, mac_04_ENTRY_1, "mac_05", mac_05_ENTRY_0);
EvtScript EVS_ExitWalk_mac_02_0 = EVT_EXIT_WALK(60, mac_04_ENTRY_0, "mac_02", mac_02_ENTRY_0);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitWalk_mac_05_0), TRIGGER_FLOOR_ABOVE, COLLIDER_deilisw, 1, 0)
    BindTrigger(Ref(EVS_ExitWalk_mac_02_0), TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(mac_04_ENTRY_2)
            Exec(EVS_BindExitTriggers)
            Exec(EVS_ExitToybox)
            Thread
                Wait(20)
                Set(MF_MusicMixTrigger, true)
            EndThread
        CaseEq(mac_04_ENTRY_3)
            Exec(EVS_BindExitTriggers)
            Call(SetPlayerPos, -420, 20, -95)
            Call(SetNpcPos, NPC_PARTNER, -420, 20, -65)
            Thread
                Wait(20)
                Set(MF_MusicMixTrigger, true)
            EndThread
        CaseEq(mac_04_ENTRY_4)
            Call(SetNightTintMode)
            Call(SetNightFogParams, 0, 0, 0, 0, 0, 0, 0, 950, 1000)
            Exec(EVS_Scene_WishingToadKid)
        CaseEq(mac_04_ENTRY_5)
            Exec(EVS_BindExitTriggers)
        CaseDefault
            Set(LVar0, Ref(EVS_BindExitTriggers))
            Exec(EnterWalk)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_TOAD_TOWN)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(GetEntryID, LVar0)
    IfEq(LVar0, mac_04_ENTRY_4)
        Call(MakeNpcs, false, Ref(WishSceneNPCs))
    Else
        Switch(GB_StoryProgress)
            CaseLt(STORY_CH3_STAR_SPRIT_DEPARTED)
                Call(MakeNpcs, false, Ref(DefaultNPCs))
            CaseLt(STORY_CH4_BEGAN_PEACH_MISSION)
                Call(MakeNpcs, false, Ref(Chapter4NPCs))
            CaseEq(STORY_CH4_BEGAN_PEACH_MISSION)
                Call(MakeNpcs, false, Ref(PostChapter4NPCs))
            CaseLt(STORY_CH5_RETURNED_TO_TOAD_TOWN)
                Call(MakeNpcs, false, Ref(DefaultNPCs))
            CaseLt(STORY_CH7_BEGAN_PEACH_MISSION)
                Call(MakeNpcs, false, Ref(Chapter7NPCs))
            CaseDefault
                Call(MakeNpcs, false, Ref(DefaultNPCs))
        EndSwitch
    EndIf
    Set(AF_MAC04_Unread_31, false)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupRooms)
    Exec(EVS_SetupFoliage)
    Exec(EVS_SetupShop)
    ExecWait(EVS_Toybox_SetupTrainPrompt)
    IfEq(GB_StoryProgress, STORY_CH4_BEGAN_PEACH_MISSION)
        Call(SetMusic, 0, SONG_STAR_SPIRIT_THEME, BGM_VARIATION_1, VOL_LEVEL_FULL)
    Else
        Exec(EVS_SetupMusic)
    EndIf
    Exec(EVS_EnterMap)
    Call(GetEntryID, LVar0)
    IfEq(LVar0, mac_04_ENTRY_5)
        Wait(65)
    Else
        Wait(1)
    EndIf
    Set(GF_MAC01_RowfBadgesChosen, false)
    Return
    End
};
