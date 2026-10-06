#include "kmr_06.h"

EvtScript EVS_ExitWalk_kmr_09_1 = EVT_EXIT_WALK(60, kmr_06_ENTRY_0, "kmr_09", kmr_09_ENTRY_1);
EvtScript EVS_ExitWalk_kmr_07_0 = EVT_EXIT_WALK(60, kmr_06_ENTRY_1, "kmr_07", kmr_07_ENTRY_0);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitWalk_kmr_09_1), TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    BindTrigger(Ref(EVS_ExitWalk_kmr_07_0), TRIGGER_FLOOR_ABOVE, COLLIDER_deili2, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_GOOMBA_ROAD)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Call(MakeNpcs, false, Ref(DefaultNPCs))
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMusic)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilit1, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilit2, COLLIDER_FLAGS_UPPER_MASK)
    Set(LVar0, Ref(EVS_BindExitTriggers))
    Exec(EnterWalk)
    Wait(1)
    ExecWait(EVS_SetupStickerSign)
    Return
    End
};
