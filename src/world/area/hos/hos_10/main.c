#include "hos_10.h"

EvtScript EVS_Main = {
    Call(GetEntryID, LVar0)
    IfEq(LVar0, $Descent.index)
        Wait(75)
    EndIf
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($Descent.index)
            Call(MakeNpcs, false, NpcGroup_Descent)
        CaseEq($FlyAway.index)
            Call(MakeNpcs, false, NpcGroup_FlyAway)
        CaseDefault
    EndSwitch
    IfNe(GB_StoryProgress, STORY_INTRO)
        Call(EnableModel, MODEL_mario_o, false)
    EndIf
    Exec(EVS_SetupMusic)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($Descent.index)
            Wait(50)
            Exec(EVS_Scene_CastleDescending)
        CaseEq($FlyAway.index)
            Exec(EVS_Scene_SpiritsFlyingAway)
        CaseEq($Entry3.index)
            ExecWait(EVS_Scene_RisingAboveClouds)
        CaseEq($Entry4.index)
            ExecWait(EVS_Scene_UnusedWhiteScreen)
        CaseEq($PreTitle.index)
            Wait(30)
            Exec(EVS_Scene_PreTitle)
    EndSwitch
#if VERSION_JP
    Exec(EVS_SetupNarrator)
#endif
    Return
    End
};
