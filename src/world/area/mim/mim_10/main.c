#include "mim_10.h"
#include "world/area/kmr/kmr_22.h"
#include "world/area/mac/mac_02.h"
#include "world/area/mim/mim_01.h"

EvtScript EVS_ExitWalk_mac_02_1 = EVT_EXIT_WALK(60, $ToadTown, $mac_02.ForeverForest);

EvtScript EVS_ExitWalk_mim_01_1 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(UseExitHeading, 60, $ForeverForest.index)
    Exec(ExitWalk)
    IfEq(GB_StoryProgress, STORY_CH3_INVITED_TO_BOOS_MANSION)
        IfEq(GF_StartedChapter3, false)
            Set(GF_StartedChapter3, true)
            Call(FadeOutMusic, 0, 1500)
            Call(GotoMapSpecial, $kmr_22.Chapter3, TRANSITION_BEGIN_OR_END_CHAPTER)
            Wait(100)
            Return
        EndIf
    EndIf
    Call(GotoMap, $mim_01.West)
    Wait(100)
    Return
    End
};

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_mac_02_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_mim_01_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
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
    Return
    End
};

EvtScript EVS_Main = {
    Call(MakeNpcs, true, DefaultNPCs)
    Exec(EVS_SetupBootlerTrigger)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMusic)
    Exec(EVS_EnterMap)
    Wait(1)
    Set(GF_MAC01_RowfBadgesChosen, false)
    Return
    End
};
