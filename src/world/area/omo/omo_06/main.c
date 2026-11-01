#include "omo_06.h"
#include "world/area/omo/omo_07.h"
#include "world/area/omo/omo_17.h"

EvtScript EVS_ExitWalk_omo_17_2 = EVT_EXIT_WALK(60, $Omo17South, $omo_17.Omo06South);
EvtScript EVS_ExitWalk_omo_17_3 = EVT_EXIT_WALK(60, $Omo17North, $omo_17.Omo06North);
EvtScript EVS_ExitWalk_omo_07_0 = EVT_EXIT_WALK(60, $Omo07, $omo_07.Omo06);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_omo_17_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deili3, 1, 0)
    BindTrigger(EVS_ExitWalk_omo_17_3, TRIGGER_FLOOR_ABOVE, COLLIDER_deilit5, 1, 0)
    BindTrigger(EVS_ExitWalk_omo_07_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
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
        CaseRange($TrainLeft.index, $TrainRight.index)
            Exec(EVS_BindExitTriggers)
            Wait(3)
        CaseDefault
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
            Wait(1)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_SHY_GUYS_TOYBOX)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
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
