#include "omo_05.h"
#include "world/area/omo/omo_17.h"

EvtScript EVS_ExitWalk_omo_17_0 = EVT_EXIT_WALK(60, $Omo17South, $omo_17.Omo05South);
EvtScript EVS_ExitWalk_omo_17_1 = EVT_EXIT_WALK(60, $Omo17North, $omo_17.Omo05North);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_omo_17_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deili3, 1, 0)
    BindTrigger(EVS_ExitWalk_omo_17_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deili4, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Call(MakeNpcs, true, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    ExecWait(EVS_SetupGizmos)
    Exec(EVS_SetupMusic)
    Call(SetGroupVisibility, MODEL_popo, MODEL_GROUP_HIDDEN)
    IfGe(GB_StoryProgress, STORY_CH4_GAVE_CAKE_TO_GOURMET_GUY)
        Call(RotateModel, MODEL_o331, 105, 0, 1, 0)
        Call(RotateModel, MODEL_o332, 105, 0, 1, 0)
        Call(RotateModel, MODEL_o333, 105, 0, 1, 0)
        Call(RotateModel, MODEL_o328, 105, 0, 1, 0)
        Call(RotateModel, MODEL_o329, 105, 0, 1, 0)
        Call(RotateModel, MODEL_o330, 105, 0, 1, 0)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_tt1, COLLIDER_FLAGS_UPPER_MASK)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_tt2, COLLIDER_FLAGS_UPPER_MASK)
    EndIf
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    Return
    End
};
