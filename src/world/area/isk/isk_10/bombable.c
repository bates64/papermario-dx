#include "isk_10.h"
#include "effects.h"

BombTrigger BombPos_UpperWall = {
    .pos = $BombPos_UpperWall.pos,
    .diameter = 2.0f * $BombPos_UpperWall.radius,
};

BombTrigger BombPos_LowerWall = {
    .pos = $BombPos_LowerWall.pos,
    .diameter = 2.0f * $BombPos_LowerWall.radius,
};

EvtScript EVS_OnBlast_UpperWall = {
    PlayEffect(EFFECT_BOMBETTE_BREAKING, 0, $BombetteBreakingPos_1.pos.x, $BombetteBreakingPos_1.pos.y, $BombetteBreakingPos_1.pos.z, 10, 30)
    Loop(10)
        Call(EnableModel, MODEL_g328, true)
        Wait(1)
        Call(EnableModel, MODEL_g328, false)
        Wait(1)
    EndLoop
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilittn, COLLIDER_FLAGS_UPPER_MASK)
    Set(GF_ISK_BombedWallFrom10, true)
    Unbind
    Return
    End
};

EvtScript EVS_OnBlast_LowerWall = {
    PlayEffect(EFFECT_BOMBETTE_BREAKING, 0, $BombetteBreakingPos_2.pos.x, $BombetteBreakingPos_2.pos.y, $BombetteBreakingPos_2.pos.z, 10, 30)
    Loop(10)
        Call(EnableModel, MODEL_g327, true)
        Wait(1)
        Call(EnableModel, MODEL_g327, false)
        Wait(1)
    EndLoop
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilittw, COLLIDER_FLAGS_UPPER_MASK)
    Set(GF_ISK10_BombedWall, true)
    Unbind
    Return
    End
};

EvtScript EVS_HideDestroyedWall = {
    Call(EnableModel, MODEL_o2029, false)
    Call(EnableModel, MODEL_o2030, false)
    Call(EnableModel, MODEL_o2031, false)
    Call(EnableModel, MODEL_o2032, false)
    Call(EnableModel, MODEL_o2033, false)
    Call(EnableModel, MODEL_o2034, false)
    Call(EnableModel, MODEL_o2035, false)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o2031, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o2032, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o2034, COLLIDER_FLAGS_UPPER_MASK)
    Return
    End
};

EvtScript EVS_SetupBombableWall = {
    IfEq(GF_ISK_BombedWallFrom08, false)
        BindTrigger(EVS_OnBlast_UpperWall, TRIGGER_POINT_BOMB, BombPos_UpperWall, 1, 0)
    Else
        Call(EnableModel, MODEL_g328, false)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilittn, COLLIDER_FLAGS_UPPER_MASK)
    EndIf
    IfEq(GF_ISK_BombedWallFrom10, false)
        IfEq(GF_ISK_BombedWallFrom08, false)
            BindTrigger(EVS_OnBlast_UpperWall, TRIGGER_POINT_BOMB, BombPos_UpperWall, 1, 0)
            ExecWait(EVS_HideDestroyedWall)
        Else
            Call(EnableModel, MODEL_g328, false)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilittn, COLLIDER_FLAGS_UPPER_MASK)
        EndIf
    Else
        Call(EnableModel, MODEL_g328, false)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilittn, COLLIDER_FLAGS_UPPER_MASK)
        ExecWait(EVS_HideDestroyedWall)
    EndIf
    IfEq(GF_ISK10_BombedWall, false)
        BindTrigger(EVS_OnBlast_LowerWall, TRIGGER_POINT_BOMB, BombPos_LowerWall, 1, 0)
    Else
        Call(EnableModel, MODEL_g327, false)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilittw, COLLIDER_FLAGS_UPPER_MASK)
    EndIf
    Return
    End
};
