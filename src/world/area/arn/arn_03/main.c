#include "arn_03.h"
#include "world/area/arn/arn_05.h"
#include "world/area/arn/arn_07.h"

EvtScript EVS_ExitWalk_arn_07_1 = EVT_EXIT_WALK(60, $Arn07, $arn_07.Arn03);
EvtScript EVS_ExitWalk_arn_05_0 = EVT_EXIT_WALK(60, $Arn05, $arn_05.Arn03);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_arn_07_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_arn_05_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
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
    IfLt(GB_StoryProgress, STORY_CH3_ARRIVED_AT_GHOST_TOWN)
        Call(SetPlayerPos, -175, 165, 160)
        Call(InterpPlayerYaw, 90, 0)
        Call(SetNpcPos, NPC_PARTNER, -175, 165, 160)
        Call(InterpNpcYaw, NPC_PARTNER, 90, 0)
#if VERSION_PAL
        Call(SetPlayerSpeed, 4 / DT)
#else
        Call(SetPlayerSpeed, 4)
#endif
        Call(PlayerMoveTo, -55, 160, 0)
        Exec(EVS_BindExitTriggers)
        Return
    EndIf
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_GUSTY_GULCH)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Set(AF_ARN03_ToggleDialogue_Boo2, false)
    Set(AF_ARN03_ToggleDialogue_Boo3, false)
    Set(AF_ARN03_ToggleDialogue_Boo4, false)
    IfLt(GB_StoryProgress, STORY_CH3_DEFEATED_TUBBA_BLUBBA)
        Call(MakeNpcs, false, BeforeNPCs)
    Else
        Call(MakeNpcs, false, AfterNPCs)
    EndIf
    IfEq(GF_ARN03_WaitingForPackage, true)
        Set(MV_Koot_Time, 450)
        Set(MV_Koot_WaitLength, 450)
    EndIf
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMusic)
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
