#include "arn_05.h"

EvtScript EVS_ExitWalk_arn_03_1 = EVT_EXIT_WALK(60, arn_05_ENTRY_0, "arn_03", arn_03_ENTRY_1);
EvtScript EVS_ExitWalk_arn_02_0 = EVT_EXIT_WALK(60, arn_05_ENTRY_1, "arn_02", arn_02_ENTRY_0);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitWalk_arn_03_1), TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(Ref(EVS_ExitWalk_arn_02_0), TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetLoadType, LVar1)
    IfEq(LVar1, LOAD_FROM_FILE_SELECT)
        Exec(EnterSavePoint)
        Exec(EVS_BindExitTriggers)
        Return
    EndIf
    Set(LVar0, Ref(EVS_BindExitTriggers))
    Exec(EnterWalk)
    Wait(1)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_GUSTY_GULCH)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    IfLt(GB_StoryProgress, STORY_CH3_DEFEATED_TUBBA_BLUBBA)
        Call(MakeNpcs, false, Ref(BeforeNPCs))
    Else
        Call(MakeNpcs, false, Ref(AfterNPCs))
    EndIf
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupTubbaRaid)
    Exec(EVS_SetupMusic)
    Exec(EVS_EnterMap)
    Return
    End
};
