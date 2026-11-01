#include "sbk_25.h"

#include "foliage.h"

FoliageModelList Tree1_LeafModels = FOLIAGE_MODEL_LIST(MODEL_o58);
FoliageModelList Tree1_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o57);

ShakeTreeConfig ShakeTree_Tree1 = {
    .leaves = &Tree1_LeafModels,
    .trunk = &Tree1_TrunkModels,
};

BombTrigger BombPos_Tree1 = {
    .pos = $BombPos_Tree1.pos,
    .diameter = 2.0f * $BombPos_Tree1.radius,
};

FoliageModelList Tree2_LeafModels = FOLIAGE_MODEL_LIST(MODEL_o60);
FoliageModelList Tree2_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o59);

ShakeTreeConfig ShakeTree_Tree2 = {
    .leaves = &Tree2_LeafModels,
    .trunk = &Tree2_TrunkModels,
};

BombTrigger BombPos_Tree2 = {
    .pos = $BombPos_Tree2.pos,
    .diameter = 2.0f * $BombPos_Tree2.radius,
};

EvtScript EVS_SetupFoliage = {
    Set(LVar0, ShakeTree_Tree1)
    BindTrigger(EVS_ShakeTree, TRIGGER_WALL_HAMMER, COLLIDER_o197, 1, 0)
    BindTrigger(EVS_ShakeTree, TRIGGER_POINT_BOMB, BombPos_Tree1, 1, 0)
    Set(LVar0, ShakeTree_Tree2)
    BindTrigger(EVS_ShakeTree, TRIGGER_WALL_HAMMER, COLLIDER_o199, 1, 0)
    BindTrigger(EVS_ShakeTree, TRIGGER_POINT_BOMB, BombPos_Tree2, 1, 0)
    Return
    End
};
