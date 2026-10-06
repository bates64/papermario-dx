#include "omo_03.h"

EvtScript EVS_ExitWalk_omo_13_1 = EVT_EXIT_WALK(60, omo_03_ENTRY_0, "omo_13", omo_13_ENTRY_1);
EvtScript EVS_ExitWalk_omo_04_0 = EVT_EXIT_WALK(60, omo_03_ENTRY_1, "omo_04", omo_04_ENTRY_0);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitWalk_omo_13_1), TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    BindTrigger(Ref(EVS_ExitWalk_omo_04_0), TRIGGER_FLOOR_ABOVE, COLLIDER_deili2, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Set(AF_OMO03_EnteringViaSpring, false)
    Call(GetLoadType, LVar1)
    IfEq(LVar1, LOAD_FROM_FILE_SELECT)
        Exec(EnterSavePoint)
        Exec(EVS_BindExitTriggers)
        Return
    EndIf
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseRange(omo_03_ENTRY_0, omo_03_ENTRY_1)
            Set(LVar0, Ref(EVS_BindExitTriggers))
            Exec(EnterWalk)
            Wait(1)
        CaseEq(omo_03_ENTRY_4)
            Set(AF_OMO03_EnteringViaSpring, true)
            Exec(EVS_BindExitTriggers)
            Exec(EVS_Scene_EnterSpring)
        CaseEq(omo_03_ENTRY_5)
            Exec(EVS_Scene_Epilogue)
        CaseEq(omo_03_ENTRY_6)
            Exec(EVS_Scene_TrainDropped)
        CaseDefault
            Exec(EVS_BindExitTriggers)
            Wait(3)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    IfLt(GB_StoryProgress, STORY_CH4_ENTERED_THE_TOY_BOX)
        Set(GB_StoryProgress, STORY_CH4_ENTERED_THE_TOY_BOX)
    EndIf
    Set(GB_WorldLocation, LOCATION_SHY_GUYS_TOYBOX)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
#if VERSION_PAL
    Call(GetLanguage, LVar0)
    Switch(LVar0)
        IfGe(LVar0, LANGUAGE_FR) // or LANGUAGE_ES
            Sub(LVar0, LANGUAGE_FR - LANGUAGE_EN)
        EndIf
        Call(SetModelTexVariant, MODEL_s, LVar0)
        Call(SetModelTexVariant, MODEL_a, LVar0)
        Call(SetModelTexVariant, MODEL_t, LVar0)
        Call(SetModelTexVariant, MODEL_i, LVar0)
        Call(SetModelTexVariant, MODEL_o, LVar0)
        Call(SetModelTexVariant, MODEL_n, LVar0)
#endif
    Set(AF_OMO03_ToggleDialogue_Conductor, false)
    Set(GF_MAP_ShyGuysToybox, true)
    Call(GetEntryID, LVar0)
    IfNe(LVar0, omo_03_ENTRY_5)
        Call(MakeNpcs, true, Ref(DefaultNPCs))
    Else
        Call(MakeNpcs, true, Ref(EpilogueNPCs))
    EndIf
    ExecWait(EVS_MakeEntities)
    ExecWait(EVS_SetupGizmos)
    ExecWait(EVS_SetupMusic)
    ExecWait(EVS_SetupTrain)
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
