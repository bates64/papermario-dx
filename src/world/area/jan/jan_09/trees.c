#include "jan_09.h"
#include "foliage.h"

FoliageModelList Tree1_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o142, MODEL_o143, MODEL_o144, MODEL_o145, MODEL_o146);
FoliageModelList Tree1_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o141);

FoliageVectorList Tree1_Effects = {
    .count = 2,
    .vectors = {
        { -461.0f, 114.0f, -204.0f },
        { -376.0f, 114.0f, -214.0f },
    }
};

ShakeTreeConfig ShakeTree_Tree1 = {
    .leaves = &Tree1_LeafModels,
    .trunk = &Tree1_TrunkModels,
    .vectors = &Tree1_Effects,
};

BombTrigger BombPos_Tree1 = {
    .pos = { -421.0f, 0.0f, -234.0f },
    .diameter = 0.0f
};

FoliageModelList Tree2_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o136, MODEL_o137, MODEL_o138, MODEL_o139, MODEL_o140);
FoliageModelList Tree2_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o135);

FoliageDropList Tree2_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_COIN,
            .pos = { 50, 190, -420 },
            .spawnMode = ITEM_SPAWN_MODE_FALL_SPAWN_ONCE,
            .pickupFlag = GF_JAN09_Tree2_Coin,
        },
    }
};

FoliageVectorList Tree2_Effects = {
    .count = 2,
    .vectors = {
        { -26.0f, 204.0f, -429.0f },
        { 59.0f, 204.0f, -439.0f },
    }
};

ShakeTreeConfig ShakeTree_Tree2 = {
    .leaves = &Tree2_LeafModels,
    .trunk = &Tree2_TrunkModels,
    .drops = &Tree2_Drops,
    .vectors = &Tree2_Effects,
};

BombTrigger BombPos_Tree2 = {
    .pos = { 14.0f, 90.0f, -459.0f },
    .diameter = 0.0f
};

FoliageModelList Tree3_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o130, MODEL_o131, MODEL_o132, MODEL_o133, MODEL_o134);
FoliageModelList Tree3_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o129);

FoliageDropList Tree3_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_FRIGHT_JAR,
            .pos = { 390, 100, -110 },
            .spawnMode = ITEM_SPAWN_MODE_FALL_SPAWN_ONCE,
            .pickupFlag = GF_JAN09_Tree3_FrightJar,
        },
    }
};

FoliageVectorList Tree3_Effects = {
    .count = 2,
    .vectors = {
        { 415.0f, 114.0f, -120.0f },
        { 500.0f, 114.0f, -130.0f },
    }
};

ShakeTreeConfig ShakeTree_Tree3 = {
    .leaves = &Tree3_LeafModels,
    .trunk = &Tree3_TrunkModels,
    .drops = &Tree3_Drops,
    .vectors = &Tree3_Effects,
};

BombTrigger BombPos_Tree3 = {
    .pos = { 455.0f, 0.0f, -150.0f },
    .diameter = 0.0f
};

EvtScript EVS_SetupTrees = {
    Set(LVar0, Ref(ShakeTree_Tree1))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o218, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree1), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree2))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o219, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree2), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree3))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o220, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree3), 1, 0)
    Return
    End
};
