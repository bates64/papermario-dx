#include "tik_14.h"
#include "entity.h"
#include "effects.h"

BombTrigger BombPos_Wall = {
    .pos = { 35.0f, 0.0f, 45.0f },
    .diameter = 0.0f
};

EvtScript EVS_OnBlast_Wall = {
    PlayEffect(EFFECT_BOMBETTE_BREAKING, 0, 9, 0, 1, 10, 30)
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
        BindTrigger(Ref(EVS_OnBlast_Wall), TRIGGER_POINT_BOMB, Ref(BombPos_Wall), 1, 0)
    EndIf
    Return
    End
};
