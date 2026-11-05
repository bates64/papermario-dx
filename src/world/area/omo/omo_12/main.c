#include "omo_12.h"
#include "world/area/omo/omo_11.h"

EvtScript EVS_ExitWalk_omo_11_0 = EVT_EXIT_WALK(60, $Omo11, $omo_11.Omo12);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_omo_11_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Call(MakeNpcs, true, DefaultNPCs)
    ExecWait(EVS_SetupMusic)
    ExecWait(EVS_SetupLightSource)
    Switch(GB_StoryProgress)
        CaseLt(STORY_CH4_DEFEATED_LANTERN_GHOST)
            Exec(EVS_BindExitTriggers)
            Exec(EVS_EnterScene)
            Wait(1)
        CaseLt(STORY_CH4_WATT_JOINED_PARTY)
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
            Wait(1)
        CaseGe(STORY_CH4_WATT_JOINED_PARTY)
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
            Wait(1)
    EndSwitch
    Return
    End
};
