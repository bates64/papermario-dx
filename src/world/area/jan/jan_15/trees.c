#include "jan_15.h"
#include "foliage.h"

FoliageModelList Tree1_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o73, MODEL_o74, MODEL_o75);
FoliageModelList Tree1_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o72);

FoliageVectorList Tree1_Effects = {
    .count = 2,
    .vectors = {
        { -134.0f, 114.0f, -72.0f },
        { -49.0f, 114.0f, -82.0f },
    }
};

ShakeTreeConfig ShakeTree_Tree1 = {
    .leaves = &Tree1_LeafModels,
    .trunk = &Tree1_TrunkModels,
    .vectors = &Tree1_Effects,
};

BombTrigger BombPos_Tree1 = {
    .pos = { -94.0f, 0.0f, -102.0f },
    .diameter = 0.0f
};

FoliageModelList Tree2_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o65, MODEL_o66, MODEL_o67);
FoliageModelList Tree2_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o64);

FoliageDropList Tree2_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_COIN,
            .pos = { 170, 100, -80 },
            .spawnMode = ITEM_SPAWN_MODE_FALL_SPAWN_ONCE,
            .pickupFlag = GF_JAN15_Tree2_Coin,
        },
    }
};

FoliageVectorList Tree2_Effects = {
    .count = 2,
    .vectors = {
        { 164.0f, 114.0f, -71.0f },
        { 249.0f, 114.0f, -81.0f },
    }
};

ShakeTreeConfig ShakeTree_Tree2 = {
    .leaves = &Tree2_LeafModels,
    .trunk = &Tree2_TrunkModels,
    .drops = &Tree2_Drops,
    .vectors = &Tree2_Effects,
};

BombTrigger BombPos_Tree2 = {
    .pos = { 204.0f, 0.0f, -101.0f },
    .diameter = 0.0f
};

EvtScript EVS_SetupTrees = {
    Set(LVar0, Ref(ShakeTree_Tree1))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o97, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree1), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree2))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o98, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree2), 1, 0)
    Return
    End
};
