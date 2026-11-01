#include "arn_05.h"
#include "world/area/arn/arn_02.h"
#include "world/area/arn/arn_03.h"

EvtScript EVS_ExitWalk_arn_03_1 = EVT_EXIT_WALK(60, $Arn03, $arn_03.Arn05);
EvtScript EVS_ExitWalk_arn_02_0 = EVT_EXIT_WALK(60, $Arn02, $arn_02.Arn05);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_arn_03_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_arn_02_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
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
    Set(LVar0, EVS_BindExitTriggers)
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
        Call(MakeNpcs, false, BeforeNPCs)
    Else
        Call(MakeNpcs, false, AfterNPCs)
    EndIf
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupTubbaRaid)
    Exec(EVS_SetupMusic)
    Exec(EVS_EnterMap)
    Return
    End
};
