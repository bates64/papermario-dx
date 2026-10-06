#include "flo_22.h"

#include "foliage.h"

FoliageModelList Tree1_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o45, MODEL_o46, MODEL_o48);

ShakeTreeConfig ShakeTree_Tree1 = {
    .trunk = &Tree1_TrunkModels,
};

BombTrigger BombPos_Tree1 = {
    .pos = { 93.0f, 0.0f, -89.0f },
    .diameter = 0.0f
};

FoliageModelList Tree2_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o52, MODEL_o53, MODEL_o55);

ShakeTreeConfig ShakeTree_Tree2 = {
    .trunk = &Tree2_TrunkModels,
};

BombTrigger BombPos_Tree2 = {
    .pos = { 150.0f, 0.0f, 135.0f },
    .diameter = 0.0f
};

EvtScript EVS_SetupFoliage = {
    Set(LVar0, Ref(ShakeTree_Tree1))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o27, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree1), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree2))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o30, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree2), 1, 0)
    Return
    End
};
