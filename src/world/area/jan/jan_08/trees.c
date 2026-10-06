#include "jan_08.h"
#include "foliage.h"

FoliageModelList Tree1_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o144, MODEL_o145, MODEL_o146, MODEL_o147, MODEL_o148);
FoliageModelList Tree1_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o143);

FoliageVectorList Tree1_Effects = {
    .count = 2,
    .vectors = {
        { -397.0f, 114.0f, -240.0f },
        { -312.0f, 114.0f, -250.0f },
    }
};

ShakeTreeConfig ShakeTree_Tree1 = {
    .leaves = &Tree1_LeafModels,
    .trunk = &Tree1_TrunkModels,
    .vectors = &Tree1_Effects,
};

BombTrigger BombPos_Tree1 = {
    .pos = { -357.0f, 0.0f, -270.0f },
    .diameter = 0.0f
};

FoliageModelList Tree2_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o138, MODEL_o139, MODEL_o140, MODEL_o141, MODEL_o142);
FoliageModelList Tree2_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o137);

FoliageDropList Tree2_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_COIN,
            .pos = { -73, 76, -474 },
            .spawnMode = ITEM_SPAWN_MODE_FALL_SPAWN_ONCE,
            .pickupFlag = GF_JAN08_Tree2_Coin,
        },
    }
};

FoliageVectorList Tree2_Effects = {
    .count = 2,
    .vectors = {
        { -185.0f, 114.0f, -430.0f },
        { -100.0f, 114.0f, -440.0f },
    }
};

ShakeTreeConfig ShakeTree_Tree2 = {
    .leaves = &Tree2_LeafModels,
    .trunk = &Tree2_TrunkModels,
    .drops = &Tree2_Drops,
    .vectors = &Tree2_Effects,
};

BombTrigger BombPos_Tree2 = {
    .pos = { -145.0f, 0.0f, -460.0f },
    .diameter = 0.0f
};

FoliageModelList Tree3_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o150, MODEL_o151, MODEL_o152, MODEL_o153, MODEL_o154);
FoliageModelList Tree3_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o149);

FoliageDropList Tree3_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_COIN,
            .pos = { 380, 100, -95 },
            .spawnMode = ITEM_SPAWN_MODE_FALL_SPAWN_ONCE,
            .pickupFlag = GF_JAN08_Tree3_Coin,
        },
    }
};

FoliageVectorList Tree3_Effects = {
    .count = 2,
    .vectors = {
        { 301.0f, 114.0f, -94.0f },
        { 386.0f, 114.0f, -104.0f },
    }
};

ShakeTreeConfig ShakeTree_Tree3 = {
    .leaves = &Tree3_LeafModels,
    .trunk = &Tree3_TrunkModels,
    .drops = &Tree3_Drops,
    .vectors = &Tree3_Effects,
};

BombTrigger BombPos_Tree3 = {
    .pos = { 341.0f, 0.0f, -124.0f },
    .diameter = 0.0f
};

EvtScript EVS_SetupTrees = {
    Set(LVar0, Ref(ShakeTree_Tree1))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o202, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree1), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree2))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o203, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree2), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree3))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o204, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree3), 1, 0)
    Return
    End
};
