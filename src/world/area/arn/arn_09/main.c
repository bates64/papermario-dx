#include "arn_09.h"
#include "world/area/arn/arn_10.h"

EvtScript EVS_ExitDoor_arn_10_0 =
    EVT_EXIT_SPLIT_SINGLE_DOOR($Arn10, $arn_10.Arn09, COLLIDER_tte, MODEL_doa, MODEL_o37, DOOR_SWING_OUT);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitDoor_arn_10_0, TRIGGER_WALL_PRESS_A, COLLIDER_tte, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($Arn10.index)
            Set(LVar2, MODEL_doa)
            Set(LVar4, MODEL_o37)
            Set(LVar3, DOOR_SWING_OUT)
            ExecWait(EnterSplitSingleDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq($Well.index)
            Exec(EVS_BindExitTriggers)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Call(MakeNpcs, false, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_EnterMap)
    Exec(EVS_LandFromWell)
    Exec(EVS_SetupMusic)
    Return
    End
};
