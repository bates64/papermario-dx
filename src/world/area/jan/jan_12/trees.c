#include "jan_12.h"
#include "foliage.h"

FoliageModelList Tree1_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o6, MODEL_o62, MODEL_o63);
FoliageModelList Tree1_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o35);

FoliageDropList Tree1_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_COIN,
            .pos = { -245, 100, -85 },
            .spawnMode = ITEM_SPAWN_MODE_FALL_SPAWN_ONCE,
            .pickupFlag = GF_JAN12_Tree1_Coin,
        },
    }
};

FoliageVectorList Tree1_Effects = {
    .count = 2,
    .vectors = {
        { -254.0f, 144.0f, -81.0f },
        { -169.0f, 144.0f, -91.0f },
    }
};

ShakeTreeConfig ShakeTree_Tree1 = {
    .leaves = &Tree1_LeafModels,
    .trunk = &Tree1_TrunkModels,
    .drops = &Tree1_Drops,
    .vectors = &Tree1_Effects,
};

BombTrigger BombPos_Tree1 = {
    .pos = { -214.0f, 30.0f, -111.0f },
    .diameter = 0.0f
};

FoliageModelList Tree2_LeafModels = FOLIAGE_MODEL_LIST(MODEL_o65, MODEL_o66, MODEL_o67);
FoliageModelList Tree2_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o64);

FoliageVectorList Tree2_Effects = {
    .count = 2,
    .vectors = {
        { 320.0f, 114.0f, -65.0f },
        { 405.0f, 114.0f, -75.0f },
    }
};

ShakeTreeConfig ShakeTree_Tree2 = {
    .leaves = &Tree2_LeafModels,
    .trunk = &Tree2_TrunkModels,
    .vectors = &Tree2_Effects,
};

BombTrigger BombPos_Tree2 = {
    .pos = { 360.0f, 0.0f, -95.0f },
    .diameter = 0.0f
};

EvtScript EVS_SetupTrees = {
    Set(LVar0, Ref(ShakeTree_Tree1))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o96, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree1), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree2))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o97, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree2), 1, 0)
    Return
    End
};
