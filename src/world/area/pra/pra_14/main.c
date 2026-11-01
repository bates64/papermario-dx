#include "pra_14.h"
#include "world/area/pra/pra_13.h"

#include "../common/Reflection.inc.c"
#include "../common/Reflection.data.inc.c"
#include "../common/GlassShimmer.inc.c"

EvtScript EVS_ExitWalk_pra_13_1 = EVT_EXIT_WALK(60, $BlueMirrorHall1South, $pra_13.BlueMirrorHall2South);
EvtScript EVS_ExitWalk_pra_13_2 = EVT_EXIT_WALK(60, $BlueMirrorHall1North, $pra_13.BlueMirrorHall2North);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_pra_13_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deilisw, 1, 0)
    BindTrigger(EVS_ExitWalk_pra_13_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deilinw, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Return
    End
};

BombTrigger BombPos_WallA = {
    .pos = $BombPos_WallA.pos,
    .diameter = 2.0f * $BombPos_WallA.radius,
};

BombTrigger BombPos_WallB = {
    .pos = $BombPos_WallB.pos,
    .diameter = 2.0f * $BombPos_WallB.radius,
};

EvtScript EVS_BlastWallA = {
    Call(EnableModel, MODEL_g289, false)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilittsw, COLLIDER_FLAGS_UPPER_MASK)
    Set(GF_PRA13_BombedWallA, true)
    Unbind
    Return
    End
};

EvtScript EVS_BlastWallB = {
    Call(EnableModel, MODEL_g260, false)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilittnw, COLLIDER_FLAGS_UPPER_MASK)
    Set(GF_PRA13_BombedWallB, true)
    Unbind
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_CRYSTAL_PALACE)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(24, 24, 40)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMusic)
    Set(LVar0, 40)
    Set(LVar1, 40)
    Set(LVar2, TEX_PANNER_0)
    Exec(EVS_GlassShimmer)
    Set(LVar0, REFLECTION_WALL_ONLY)
    Set(LVar1, true) // always disable reflections in this room
    Exec(EVS_SetupReflections)
    Exec(EVS_EnterMap)
    Wait(1)
    IfEq(GF_PRA13_BombedWallA, false)
        BindTrigger(EVS_BlastWallA, TRIGGER_POINT_BOMB, BombPos_WallA, 1, 0)
    Else
        Call(EnableModel, MODEL_g289, false)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilittsw, COLLIDER_FLAGS_UPPER_MASK)
    EndIf
    IfEq(GF_PRA13_BombedWallB, false)
        BindTrigger(EVS_BlastWallB, TRIGGER_POINT_BOMB, BombPos_WallB, 1, 0)
    Else
        Call(EnableModel, MODEL_g260, false)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilittnw, COLLIDER_FLAGS_UPPER_MASK)
    EndIf
    Return
    End
};
