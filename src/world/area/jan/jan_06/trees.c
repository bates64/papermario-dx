#include "jan_06.h"
#include "foliage.h"

FoliageModelList Tree1_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_g35);
FoliageModelList Tree1_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o97);

FoliageDropList Tree1_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_COIN,
            .pos = { -225, 80, -380 },
            .spawnMode = ITEM_SPAWN_MODE_FALL_SPAWN_ONCE,
            .pickupFlag = GF_JAN06_Tree1_Coin,
            .spawnFlag = MF_TreeDrop_Coin,
        },
    }
};

FoliageVectorList Tree1_Effects = {
    .count = 2,
    .vectors = {
        { -325.0f, 114.0f, -330.0f },
        { -240.0f, 114.0f, -340.0f },
    }
};

ShakeTreeConfig ShakeTree_Tree1 = {
    .leaves = &Tree1_LeafModels,
    .trunk = &Tree1_TrunkModels,
    .drops = &Tree1_Drops,
    .vectors = &Tree1_Effects,
};

BombTrigger BombPos_Tree1 = {
    .pos = { -285.0f, 0.0f, -360.0f },
    .diameter = 0.0f
};

FoliageModelList Tree2_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_g36);
FoliageModelList Tree2_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o103);

FoliageVectorList Tree2_Effects = {
    .count = 2,
    .vectors = {
        { 412.0f, 114.0f, -105.0f },
        { 497.0f, 114.0f, -115.0f },
    }
};

ShakeTreeConfig ShakeTree_Tree2 = {
    .leaves = &Tree2_LeafModels,
    .trunk = &Tree2_TrunkModels,
    .vectors = &Tree2_Effects,
};

BombTrigger BombPos_Tree2 = {
    .pos = { 452.0f, 0.0f, -135.0f },
    .diameter = 0.0f
};

EvtScript EVS_SetupTrees = {
    Set(LVar0, Ref(ShakeTree_Tree1))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o183, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree1), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree2))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o185, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree2), 1, 0)
    Return
    End
};
