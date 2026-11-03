#include "kpa_13.h"
#include "world/area/kpa/kpa_12.h"
#include "world/area/kpa/kpa_14.h"
#include "world/area/kpa/kpa_15.h"

EvtScript EVS_ExitWalk_kpa_12_1 = EVT_EXIT_WALK(60, $LavaChannel1, $kpa_12.LavaChannel2);
EvtScript EVS_ExitWalk_kpa_15_0 = EVT_EXIT_WALK(60, $LavaKeyRoom, $kpa_15.LavaChannel2);
EvtScript EVS_ExitWalk_kpa_14_0 = EVT_EXIT_WALK(60, $LavaChannel3, $kpa_14.LavaChannel2);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_kpa_12_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_kpa_15_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilin, 1, 0)
    BindTrigger(EVS_ExitWalk_kpa_14_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
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
    Call(SetTexPanner, MODEL_o926, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_o927, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_o928, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_o925, TEX_PANNER_0)
    Return
    End
};

LavaReset SafeFloorColliders[] = {
    { .colliderID = COLLIDER_o1043, .pos = $LavaReset_o1043.pos },
    { .colliderID = COLLIDER_o1047, .pos = $LavaReset_o1047.pos },
    { .colliderID = COLLIDER_o1048, .pos = $LavaReset_o1048.pos },
    { .colliderID = COLLIDER_o1041, .pos = $LavaReset_o1041.pos },
    { .colliderID = COLLIDER_o1051, .pos = $LavaReset_o1051.pos },
    { .colliderID = COLLIDER_o1040, .pos = $LavaReset_o1040.pos },
    { .colliderID = COLLIDER_o1050, .pos = $LavaReset_o1050.pos },
    { .colliderID = COLLIDER_o1062, .pos = $LavaReset_o1062.pos },
    { .colliderID = COLLIDER_o1064, .pos = $LavaReset_o1064.pos },
    { .colliderID = COLLIDER_o1066, .pos = $LavaReset_o1066.pos },
    { .colliderID = COLLIDER_o1068, .pos = $LavaReset_o1068.pos },
    { .colliderID = COLLIDER_o1042, .pos = $LavaReset_o1042.pos },
    { .colliderID = NO_COLLIDER }
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_BOWSERS_CASTLE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    ExecWait(EVS_MakeEntities)
    IfEq(GF_KPA16_ShutOffLava, false)
        Call(EnableGroup, MODEL_after, false)
        Exec(EVS_TexPan_Lava)
    Else
        Call(EnableGroup, MODEL_before, false)
    EndIf
    Exec(EVS_SetupMusic)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    IfEq(GF_KPA16_ShutOffLava, false)
        Exec(EVS_SetupPlatforms)
    EndIf
    IfEq(GF_KPA16_ShutOffLava, false)
        Thread
            Wait(2)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o1039, SURFACE_TYPE_LAVA)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o805, SURFACE_TYPE_LAVA)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o1028, SURFACE_TYPE_LAVA)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o1029, SURFACE_TYPE_LAVA)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o1030, SURFACE_TYPE_LAVA)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o1031, SURFACE_TYPE_LAVA)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o1032, SURFACE_TYPE_LAVA)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o1033, SURFACE_TYPE_LAVA)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o1034, SURFACE_TYPE_LAVA)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o1035, SURFACE_TYPE_LAVA)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o1036, SURFACE_TYPE_LAVA)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o1037, SURFACE_TYPE_LAVA)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o1038, SURFACE_TYPE_LAVA)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o1074, SURFACE_TYPE_LAVA)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o1075, SURFACE_TYPE_LAVA)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_deilin, SURFACE_TYPE_LAVA)
            Thread
                Call(ResetFromLava, SafeFloorColliders)
            EndThread
        EndThread
    EndIf
    Return
    End
};
