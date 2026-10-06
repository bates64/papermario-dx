#include "mac_02.h"

#include "foliage.h"

FoliageModelList Tree1_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o417);
FoliageModelList Tree1_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o213);

FoliageVectorList Tree1_Effects = {
    .count = 2,
    .vectors = {
        { 83.0f, 130.0f, -541.0f },
        { 123.0f, 130.0f, -551.0f },
    }
};

ShakeTreeConfig ShakeTree_Tree1 = {
    .leaves = &Tree1_LeafModels,
    .trunk = &Tree1_TrunkModels,
    .vectors = &Tree1_Effects,
};

BombTrigger BombPos_Tree1 = {
    .pos = { 98.0f, 20.0f, -531.0f },
    .diameter = 0.0f
};

FoliageModelList Tree2_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o115);
FoliageModelList Tree2_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o423);

FoliageVectorList Tree2_Effects = {
    .count = 2,
    .vectors = {
        { -337.0f, 104.0f, -198.0f },
        { -297.0f, 104.0f, -208.0f },
    }
};

ShakeTreeConfig ShakeTree_Tree2 = {
    .leaves = &Tree2_LeafModels,
    .trunk = &Tree2_TrunkModels,
    .vectors = &Tree2_Effects,
};

BombTrigger BombPos_Tree2 = {
    .pos = { -323.0f, 20.0f, -190.0f },
    .diameter = 0.0f
};

FoliageModelList Tree3_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o415);
FoliageModelList Tree3_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o420);

FoliageVectorList Tree3_Effects = {
    .count = 2,
    .vectors = {
        { 584.0f, 125.0f, -70.0f },
        { 624.0f, 125.0f, -80.0f },
    }
};

ShakeTreeConfig ShakeTree_Tree3 = {
    .leaves = &Tree3_LeafModels,
    .trunk = &Tree3_TrunkModels,
    .vectors = &Tree3_Effects,
};

BombTrigger BombPos_Tree3 = {
    .pos = { 598.0f, 0.0f, -67.0f },
    .diameter = 0.0f
};

FoliageModelList UnusedTree_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o419);
FoliageModelList UnusedTree_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o116);

FoliageVectorList UnusedTree_Effects = {
    .count = 2,
    .vectors = {
        { -624.0f, 80.0f, -166.0f },
        { -584.0f, 80.0f, -176.0f },
    }
};

ShakeTreeConfig ShakeTree_UnusedTree = {
    .leaves = &UnusedTree_LeafModels,
    .trunk  = &UnusedTree_TrunkModels,
    .vectors = &UnusedTree_Effects,
};

BombTrigger BombPos_UnusedTree = {
    .pos = { -608.0f, 20.0f, -156.0f },
    .diameter = 0.0f
};

FoliageModelList Tree4_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o414);
FoliageModelList Tree4_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o421);

FoliageVectorList Tree4_Effects = {
    .count = 2,
    .vectors = {
        { 235.0f, 80.0f, 543.0f },
        { 275.0f, 80.0f, 533.0f },
    }
};

ShakeTreeConfig ShakeTree_Tree4 = {
    .leaves = &Tree4_LeafModels,
    .trunk  = &Tree4_TrunkModels,
    .vectors = &Tree4_Effects,
};

BombTrigger BombPos_Tree4 = {
    .pos = { 351.0f, 20.0f, 555.0f },
    .diameter = 0.0f
};

EvtScript EVS_SetupFoliage = {
    Set(LVar0, Ref(ShakeTree_Tree1))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o409, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree1), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree2))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o361, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree2), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree3))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o370, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree3), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree4))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o378, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree4), 1, 0)
    Return
    End
};
