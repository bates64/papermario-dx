#include "omo_03.h"
#include "world/area/omo/omo_04.h"
#include "world/area/omo/omo_13.h"

EvtScript EVS_ExitWalk_omo_13_1 = EVT_EXIT_WALK(60, $Omo13, $omo_13.Omo03);
EvtScript EVS_ExitWalk_omo_04_0 = EVT_EXIT_WALK(60, $Omo04, $omo_04.Omo03);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_omo_13_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    BindTrigger(EVS_ExitWalk_omo_04_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deili2, 1, 0)
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
        CaseRange($Omo13.index, $Omo04.index)
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
            Wait(1)
        CaseEq($ToadTown.index)
            Set(AF_OMO03_EnteringViaSpring, true)
            Exec(EVS_BindExitTriggers)
            Exec(EVS_Scene_EnterSpring)
        CaseEq($Epilogue.index)
            Exec(EVS_Scene_Epilogue)
        CaseEq($TrainReturned.index)
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
        IfNe(LVar0, $Epilogue.index)
            Call(MakeNpcs, true, DefaultNPCs)
        Else
            Call(MakeNpcs, true, EpilogueNPCs)
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
