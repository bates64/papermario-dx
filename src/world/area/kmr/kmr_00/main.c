#include "kmr_00.h"
#include "world/area/kmr/kmr_02.h"

EvtScript EVS_ExitWalk_kmr_02_1 = EVT_EXIT_WALK(60, $GoombaVillage, $kmr_02.ForestClearing);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_kmr_02_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GF_MAP_GoombaVillage, true)
    IfLt(GB_StoryProgress, STORY_CH0_MET_INNKEEPER)
        Call(MakeNpcs, false, DefaultNPCs)
        Call(ClearDefeatedEnemies)
    EndIf
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMusic)
    Exec(EVS_Scene_MarioRevived)
    Switch(GB_StoryProgress)
        CaseEq(STORY_INTRO)
            Call(EnableModel, MODEL_ji_3, false)
            Exec(EVS_BindExitTriggers)
        CaseGe(STORY_CH0_WAKE_UP)
            Call(EnableModel, MODEL_ji_1, false)
            Call(EnableModel, MODEL_ji_2, false)
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
    EndSwitch
    Wait(1)
    Return
    End
};
