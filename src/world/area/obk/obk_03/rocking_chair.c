#include "obk_03.h"

#include "../common/RockingChair.inc.c"

EvtScript N(EVS_SetupRockingChair) = {
    Call(ParentColliderToModel, COLLIDER_i1, MODEL_i1)
    Call(ParentColliderToModel, COLLIDER_i2, MODEL_i3)
    Call(ParentColliderToModel, COLLIDER_i3, MODEL_i3)
    Call(N(UpdateRockingChair), -170, MODEL_i1, MODEL_i2, MODEL_i3, COLLIDER_i1, COLLIDER_i2, COLLIDER_i3)
    Return
    End
};
