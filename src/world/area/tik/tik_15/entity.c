#include "tik_15.h"
#include "entity.h"
#include "effects.h"

BombTrigger BombPos_Wall = {
    .pos = $BombPos_Wall.pos,
    .diameter = 2.0f * $BombPos_Wall.radius,
};

EvtScript EVS_OnBlast_Wall = {
    PlayEffect(EFFECT_BOMBETTE_BREAKING, 0, $BombetteBreakingPos_1.pos.x, $BombetteBreakingPos_1.pos.y, $BombetteBreakingPos_1.pos.z, 10, 30)
    Loop(10)
        Call(EnableModel, MODEL_a_kabe, true)
        Wait(1)
        Call(EnableModel, MODEL_a_kabe, false)
        Wait(1)
    EndLoop
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_tte, COLLIDER_FLAGS_UPPER_MASK)
    Set(GF_TIK14_BombedWall, true)
    Unbind
    Return
    End
};

EvtScript EVS_MakeEntities = {
    IfEq(GF_TIK14_BombedWall, true)
        Call(EnableModel, MODEL_a_kabe, false)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_tte, COLLIDER_FLAGS_UPPER_MASK)
    Else
        BindTrigger(EVS_OnBlast_Wall, TRIGGER_POINT_BOMB, BombPos_Wall, 1, 0)
    EndIf
    Return
    End
};
