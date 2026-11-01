#include "kpa_12.h"
#include "world/area/kpa/kpa_10.h"
#include "world/area/kpa/kpa_11.h"
#include "world/area/kpa/kpa_13.h"

EvtScript EVS_ExitWalk_kpa_1X_Upper = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(UseExitHeading, 60, $OutsideJailUpper.index)
    Exec(ExitWalk)
    IfEq(GF_KPA16_ShutOffLava, false)
        Call(GotoMap, $kpa_11.LavaChannel1Upper)
    Else
        Call(GotoMap, $kpa_10.LavaChannel1Upper)
    EndIf
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitWalk_kpa_1X_Lower = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(UseExitHeading, 60, $OutsideJailLower.index)
    Exec(ExitWalk)
    IfEq(GF_KPA16_ShutOffLava, false)
        Call(GotoMap, $kpa_11.LavaChannel1Lower)
    Else
        Call(GotoMap, $kpa_10.LavaChannel1Lower)
    EndIf
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitWalk_kpa_13_0 = EVT_EXIT_WALK(60, $LavaChannel2, $kpa_13.LavaChannel1);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_kpa_1X_Upper, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_kpa_1X_Lower, TRIGGER_FLOOR_ABOVE, COLLIDER_deilisw, 1, 0)
    BindTrigger(EVS_ExitWalk_kpa_13_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript EVS_TexPan_Lava = {
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_0)
        TEX_PAN_PARAMS_STEP( -400,    0, -800,    0)
        TEX_PAN_PARAMS_FREQ(    1,    0,    1,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Call(SetTexPanner, MODEL_o319, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_o555, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_o516, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_o526, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_o557, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_o558, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_o513, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_o561, TEX_PANNER_0)
    Return
    End
};

LavaReset SafeFloorColliders[] = {
    { .colliderID = COLLIDER_o179, .pos = $LavaReset_o179.pos },
    { .colliderID = COLLIDER_o171, .pos = $LavaReset_o171.pos },
    { .colliderID = COLLIDER_o174, .pos = $LavaReset_o174.pos },
    { .colliderID = COLLIDER_o175, .pos = $LavaReset_o175.pos },
    { .colliderID = COLLIDER_o144, .pos = $LavaReset_o144.pos },
    { .colliderID = COLLIDER_o305, .pos = $LavaReset_o305.pos },
    { .colliderID = NO_COLLIDER }
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_BOWSERS_CASTLE)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    IfEq(GF_KPA16_ShutOffLava, false)
        Call(EnableGroup, MODEL_after, false)
        Exec(EVS_TexPan_Lava)
    Else
        Call(EnableGroup, MODEL_before, false)
    EndIf
    Exec(EVS_SetupMusic)
    IfEq(GF_KPA16_ShutOffLava, false)
        Exec(EVS_SetupPlatforms)
    EndIf
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    IfEq(GF_KPA16_ShutOffLava, false)
        Thread
            Wait(2)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o356, SURFACE_TYPE_LAVA)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o358, SURFACE_TYPE_LAVA)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o359, SURFACE_TYPE_LAVA)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o360, SURFACE_TYPE_LAVA)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o361, SURFACE_TYPE_LAVA)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o362, SURFACE_TYPE_LAVA)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o363, SURFACE_TYPE_LAVA)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o364, SURFACE_TYPE_LAVA)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o365, SURFACE_TYPE_LAVA)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o370, SURFACE_TYPE_LAVA)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o371, SURFACE_TYPE_LAVA)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o419, SURFACE_TYPE_LAVA)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o420, SURFACE_TYPE_LAVA)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_deilisw, SURFACE_TYPE_LAVA)
            Thread
                Call(ResetFromLava, SafeFloorColliders)
            EndThread
        EndThread
    EndIf
    Wait(1)
    Return
    End
};
