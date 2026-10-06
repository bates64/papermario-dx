#include "jan_04.h"
#include "foliage.h"

FoliageModelList Tree1_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o94, MODEL_o95, MODEL_o96, MODEL_o97, MODEL_o98);
FoliageModelList Tree1_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o99);

FoliageVectorList Tree1_Effects = {
    .count = 2,
    .vectors = {
        { -487.0f, 114.0f, -115.0f },
        { -402.0f, 114.0f, -125.0f },
    }
};

ShakeTreeConfig ShakeTree_Tree1 = {
    .leaves = &Tree1_LeafModels,
    .trunk = &Tree1_TrunkModels,
    .vectors = &Tree1_Effects,
};

BombTrigger BombPos_Tree1 = {
    .pos = { -447.0f, 0.0f, -145.0f },
    .diameter = 0.0f
};

FoliageModelList Tree2_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o101, MODEL_o102, MODEL_o103, MODEL_o104, MODEL_o105);
FoliageModelList Tree2_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o100);

FoliageDropList Tree2_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_LETTER_TO_RUSS_T,
            .pos = { 311, 92, -221 },
            .spawnMode = ITEM_SPAWN_MODE_FALL_NEVER_VANISH,
            .pickupFlag = GF_JAN04_Tree2_Letter04,
            .spawnFlag = MF_TreeDrop_Letter,
        },
    }
};

FoliageVectorList Tree2_Effects = {
    .count = 2,
    .vectors = {
        { 327.0f, 114.0f, -230.0f },
        { 412.0f, 114.0f, -240.0f },
    }
};

ShakeTreeConfig ShakeTree_Tree2 = {
    .leaves = &Tree2_LeafModels,
    .trunk = &Tree2_TrunkModels,
    .drops = &Tree2_Drops,
    .vectors = &Tree2_Effects,
};

BombTrigger BombPos_Tree2 = {
    .pos = { 367.0f, 0.0f, -260.0f },
    .diameter = 0.0f
};

FoliageModelList Tree3_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o63, MODEL_o64, MODEL_o65, MODEL_o66, MODEL_o67);
FoliageModelList Tree3_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o34);

FoliageVectorList Tree3_Effects = {
    .count = 2,
    .vectors = {
        { -10.0f, 114.0f, -80.0f },
        { 75.0f, 114.0f, -90.0f },
    }
};

ShakeTreeConfig ShakeTree_Tree3 = {
    .leaves = &Tree3_LeafModels,
    .trunk = &Tree3_TrunkModels,
    .vectors = &Tree3_Effects,
};

BombTrigger BombPos_Tree3 = {
    .pos = { 30.0f, 0.0f, -110.0f },
    .diameter = 0.0f
};

EvtScript EVS_SetupTrees = {
    Set(LVar0, Ref(ShakeTree_Tree1))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o156, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree1), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree2))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o157, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree2), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree3))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o34, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree3), 1, 0)
    Return
    End
};
