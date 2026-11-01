#include "obk_02.h"
#include "effects.h"

BombTrigger BombPos_Wall = {
    .pos = $BombPos_Wall.pos,
    .diameter = 2.0f * $BombPos_Wall.radius,
};

EvtScript EVS_OnBlast_Wall = {
    PlayEffect(EFFECT_BOMBETTE_BREAKING, 1, $BombetteBreakingPos_1.pos.x, $BombetteBreakingPos_1.pos.y, $BombetteBreakingPos_1.pos.z, 10, 30)
    Loop(10)
        Call(EnableModel, MODEL_bomu_ato, false)
        Call(EnableModel, MODEL_bom_mae, true)
        Wait(1)
        Call(EnableModel, MODEL_bomu_ato, true)
        Call(EnableModel, MODEL_bom_mae, false)
        Wait(1)
    EndLoop
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_tt3, COLLIDER_FLAGS_UPPER_MASK)
    Set(GF_OBK06_BombedWall, true)
    Unbind
    Return
    End
};

EvtScript EVS_SetupBombableWall = {
    IfEq(GF_OBK06_BombedWall, false)
        BindTrigger(EVS_OnBlast_Wall, TRIGGER_POINT_BOMB, BombPos_Wall, 1, 0)
        Call(EnableModel, MODEL_bomu_ato, false)
    Else
        Call(EnableModel, MODEL_bom_mae, false)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_tt3, COLLIDER_FLAGS_UPPER_MASK)
    EndIf
    Return
    End
};
