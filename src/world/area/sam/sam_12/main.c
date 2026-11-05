#include "sam_12.h"
#include "world/area/sam/sam_10.h"

EvtScript EVS_ExitWalk_sam_10_2 = EVT_EXIT_WALK(60, $MountainPeaks, $sam_10.MerlarsSanctuary);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_sam_10_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deili, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Call(MakeNpcs, false, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    ExecWait(EVS_SetupMusic)
    IfLt(GB_StoryProgress, STORY_CH7_GOT_STAR_STONE)
        Exec(EVS_Scene_MeetMerlar)
    EndIf
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    Call(SetCamSpeed, CAM_DEFAULT, 4.0)
    Return
    End
};
