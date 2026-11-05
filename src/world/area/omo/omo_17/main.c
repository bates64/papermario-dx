#include "omo_17.h"
#include "world/area/omo/omo_05.h"
#include "world/area/omo/omo_06.h"

EvtScript EVS_ExitWalk_omo_05_0 = EVT_EXIT_WALK(60, $Omo05South, $omo_05.Omo17South);
EvtScript EVS_ExitWalk_omo_05_1 = EVT_EXIT_WALK(60, $Omo05North, $omo_05.Omo17North);
EvtScript EVS_ExitWalk_omo_06_0 = EVT_EXIT_WALK(60, $Omo06South, $omo_06.Omo17South);
EvtScript EVS_ExitWalk_omo_06_1 = EVT_EXIT_WALK(60, $Omo06North, $omo_06.Omo17North);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_omo_05_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    BindTrigger(EVS_ExitWalk_omo_05_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deili5, 1, 0)
    BindTrigger(EVS_ExitWalk_omo_06_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deili2, 1, 0)
    BindTrigger(EVS_ExitWalk_omo_06_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deili6, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Call(MakeNpcs, true, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    ExecWait(EVS_SetupGizmos)
    Call(SetMusic, 0, SONG_SHY_GUY_TOYBOX, 0, VOL_LEVEL_FULL)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseRange($TrainLeft.index, $TrainRight.index)
            ExecWait(EVS_EnterTrain)
            Wait(3)
        CaseDefault
            Call(SetGroupVisibility, MODEL_popo, MODEL_GROUP_HIDDEN)
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
            Wait(1)
    EndSwitch
    Return
    End
};
