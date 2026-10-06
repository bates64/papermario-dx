#include "jan_02.h"

#include "foliage.h"

FoliageModelList Tree1_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o240);
FoliageModelList Tree1_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o239);

ShakeTreeConfig ShakeTree_Tree1 = {
    .leaves = &Tree1_LeafModels,
    .trunk = &Tree1_TrunkModels,
};

BombTrigger BombPos_Tree1 = {
    .pos = { -220.0f, 15.0f, 292.0f },
    .diameter = 0.0f
};

FoliageModelList Tree2_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o260, MODEL_o261);
FoliageModelList Tree2_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o259);

FoliageDropList Tree2_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_COCONUT,
            .pos = { -596, 75, -190 },
            .spawnMode = ITEM_SPAWN_MODE_FALL_SPAWN_ONCE,
            .spawnFlag = AF_JAN02_TreeDrop2,
        },
    }
};

ShakeTreeConfig ShakeTree_Tree2 = {
    .leaves = &Tree2_LeafModels,
    .trunk = &Tree2_TrunkModels,
    .drops = &Tree2_Drops,
};

BombTrigger BombPos_Tree2 = {
    .pos = { -586.0f, 0.0f, -215.0f },
    .diameter = 0.0f
};

FoliageModelList Tree3_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o281, MODEL_o282);
FoliageModelList Tree3_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o280);


FoliageDropList Tree3_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_COCONUT,
            .pos = { 591, 75, -220 },
            .spawnMode = ITEM_SPAWN_MODE_FALL_SPAWN_ONCE,
            .spawnFlag = AF_JAN02_TreeDrop3,
        },
    }
};

ShakeTreeConfig ShakeTree_Tree3 = {
    .leaves = &Tree3_LeafModels,
    .trunk = &Tree3_TrunkModels,
    .drops = &Tree3_Drops,
};

BombTrigger BombPos_Tree3 = {
    .pos = { 581.0f, 0.0f, -240.0f },
    .diameter = 0.0f
};

FoliageModelList Tree4_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o257);
FoliageModelList Tree4_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o256);

ShakeTreeConfig ShakeTree_Tree4 = {
    .leaves = &Tree4_LeafModels,
    .trunk = &Tree4_TrunkModels,
};

BombTrigger BombPos_Tree4 = {
    .pos = { -636.0f, 0.0f, -235.0f },
    .diameter = 0.0f
};

EvtScript EVS_SetupFoliage = {
    Set(AF_JAN02_TreeDrop2, false)
    Set(AF_JAN02_TreeDrop3, false)
    Set(LVar0, Ref(ShakeTree_Tree1))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o239, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree1), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree2))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o259, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree2), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree3))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o343, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree3), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree4))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o364, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree4), 1, 0)
    Return
    End
};
