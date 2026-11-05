#include "omo_10.h"
#include "world/area/omo/omo_02.h"
#include "world/area/omo/omo_11.h"

EvtScript EVS_ExitWalk_omo_11_1 = EVT_EXIT_WALK(60, $Omo11, $omo_11.Omo10);
EvtScript EVS_ExitWalk_omo_02_0 = EVT_EXIT_WALK(60, $Omo02, $omo_02.Omo10);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_omo_11_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deili4, 1, 0)
    BindTrigger(EVS_ExitWalk_omo_02_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
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
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseRange($Omo11.index, $Omo02.index)
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
            Wait(1)
        CaseDefault
            Exec(EVS_BindExitTriggers)
            Wait(3)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
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
        Call(MakeNpcs, true, DefaultNPCs)
        ExecWait(EVS_MakeEntities)
        ExecWait(EVS_SetupGizmos)
        ExecWait(EVS_SetupMusic)
        ExecWait(EVS_SetupTrain)
        Exec(EVS_EnterMap)
        Wait(1)
        Return
        End
};
