#include "omo_08.h"

EvtScript EVS_ExitWalk_omo_09_0 = EVT_EXIT_WALK(60, omo_08_ENTRY_0, "omo_09", omo_09_ENTRY_0);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitWalk_omo_09_0), TRIGGER_FLOOR_ABOVE, COLLIDER_deili3, 1, 0)
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
    IfEq(LVar0, omo_08_ENTRY_0)
        Set(LVar0, Ref(EVS_BindExitTriggers))
        Exec(EnterWalk)
        Wait(1)
    Else
        Exec(EVS_BindExitTriggers)
        Wait(3)
    EndIf
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
    Call(MakeNpcs, true, Ref(DefaultNPCs))
    ExecWait(EVS_MakeEntities)
    ExecWait(EVS_SetupMusic)
    ExecWait(EVS_SetupTrain)
    ExecWait(EVS_SetupBoxes)
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
