#include "mac_04.h"

#include "foliage.h"

FoliageModelList Tree1_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o287);
FoliageModelList Tree1_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o286);

FoliageVectorList Tree1_Effects = {
    .count = 2,
    .vectors = {
        { 436.0f, 135.0f, -246.0f },
        { 476.0f, 135.0f, -256.0f },
    }
};

ShakeTreeConfig ShakeTree_Tree1 = {
    .leaves = &Tree1_LeafModels,
    .trunk = &Tree1_TrunkModels,
    .vectors = &Tree1_Effects,
};

BombTrigger BombPos_Tree1 = {
    .pos = { 470.0f, 20.0f, -242.0f },
    .diameter = 0.0f
};

FoliageModelList Tree2_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o290);
FoliageModelList Tree2_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o291);

FoliageVectorList Tree2_Effects = {
    .count = 2,
    .vectors = {
        { 41.0f, 110.0f, -149.0f },
        { 81.0f, 110.0f, -159.0f },
    }
};

ShakeTreeConfig ShakeTree_Tree2 = {
    .leaves = &Tree2_LeafModels,
    .trunk = &Tree2_TrunkModels,
    .vectors = &Tree2_Effects,
};

BombTrigger BombPos_Tree2 = {
    .pos = { 50.0f, 20.0f, -141.0f },
    .diameter = 0.0f
};

FoliageModelList Tree3_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o288);
FoliageModelList Tree3_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o289);

FoliageVectorList Tree3_Effects = {
    .count = 2,
    .vectors = {
        { -313.0f, 133.0f, 80.0f },
        { -273.0f, 133.0f, 70.0f },
    }
};

ShakeTreeConfig ShakeTree_Tree3 = {
    .leaves = &Tree3_LeafModels,
    .trunk = &Tree3_TrunkModels,
    .vectors = &Tree3_Effects,
};

BombTrigger BombPos_Tree3 = {
    .pos = { -293.0f, 20.0f, 86.0f },
    .diameter = 0.0f
};

EvtScript EVS_SetupFoliage = {
    Set(LVar0, Ref(ShakeTree_Tree1))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o452, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree1), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree2))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o446, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree2), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree3))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o435, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree3), 1, 0)
    Return
    End
};
