#include "hos_10.h"

EvtScript EVS_Main = {
    Call(GetEntryID, LVar0)
    IfEq(LVar0, hos_10_ENTRY_1)
        Wait(75)
    EndIf
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(hos_10_ENTRY_1)
            Call(MakeNpcs, false, Ref(NpcGroup_Descent))
        CaseEq(hos_10_ENTRY_2)
            Call(MakeNpcs, false, Ref(NpcGroup_FlyAway))
        CaseDefault
    EndSwitch
    IfNe(GB_StoryProgress, STORY_INTRO)
        Call(EnableModel, MODEL_mario_o, false)
    EndIf
    Exec(EVS_SetupMusic)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(hos_10_ENTRY_1)
            Wait(50)
            Exec(EVS_Scene_CastleDescending)
        CaseEq(hos_10_ENTRY_2)
            Exec(EVS_Scene_SpiritsFlyingAway)
        CaseEq(hos_10_ENTRY_3)
            ExecWait(EVS_Scene_RisingAboveClouds)
        CaseEq(hos_10_ENTRY_4)
            ExecWait(EVS_Scene_UnusedWhiteScreen)
        CaseEq(hos_10_ENTRY_5)
            Wait(30)
            Exec(EVS_Scene_PreTitle)
    EndSwitch
#if VERSION_JP
    Exec(EVS_SetupNarrator)
#endif
    Return
    End
};
