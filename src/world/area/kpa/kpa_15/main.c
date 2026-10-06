#include "kpa_15.h"

EvtScript EVS_ExitWalk_kpa_13_2 = EVT_EXIT_WALK(40, kpa_15_ENTRY_0, "kpa_13", kpa_13_ENTRY_2);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitWalk_kpa_13_2), TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Set(LVar0, Ref(EVS_BindExitTriggers))
    Exec(EnterWalk)
    Return
    End
};

EvtScript EVS_SetupTexPanners = {
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_0)
        TEX_PAN_PARAMS_STEP( -400,    0, -800,    0)
        TEX_PAN_PARAMS_FREQ(    1,    0,    1,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Call(SetTexPanner, MODEL_o811, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_o813, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_o814, TEX_PANNER_0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_BOWSERS_CASTLE)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    ExecWait(EVS_MakeEntities)
    IfEq(GF_KPA16_ShutOffLava, false)
        Call(EnableGroup, MODEL_after, false)
        Exec(EVS_SetupTexPanners)
    Else
        Call(EnableGroup, MODEL_before, false)
    EndIf
    Exec(EVS_EnterMap)
    Exec(EVS_SetupMusic)
    IfEq(GF_KPA16_ShutOffLava, false)
        Thread
            Wait(2)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o781, SURFACE_TYPE_LAVA)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_deiliw, SURFACE_TYPE_LAVA)
        EndThread
    EndIf
    Return
    End
};
