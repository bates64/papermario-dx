#include "sbk_36.h"

#include "foliage.h"

FoliageModelList Tree1_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o73);
FoliageModelList Tree1_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o72);

FoliageDropList Tree1_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_COIN,
            .pos = { -422, 100, 116 },
            .spawnMode = ITEM_SPAWN_MODE_FALL_SPAWN_ONCE,
            .pickupFlag = GF_SBK36_Tree1_Coin,
        },
    }
};

ShakeTreeConfig ShakeTree_Tree1 = {
    .leaves = &Tree1_LeafModels,
    .trunk = &Tree1_TrunkModels,
    .drops = &Tree1_Drops,
};

BombTrigger BombPos_Tree1 = {
    .pos = { -422.0f, 0.0f, 91.0f },
    .diameter = 0.0f
};

FoliageModelList Tree2_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o71);
FoliageModelList Tree2_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o70);

FoliageDropList Tree2_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_COIN,
            .pos = { -322, 100, -86 },
            .spawnMode = ITEM_SPAWN_MODE_FALL_SPAWN_ONCE,
            .pickupFlag = GF_SBK36_Tree2_Coin,
        },
    }
};

ShakeTreeConfig ShakeTree_Tree2 = {
    .leaves = &Tree2_LeafModels,
    .trunk = &Tree2_TrunkModels,
    .drops = &Tree2_Drops,
};

BombTrigger BombPos_Tree2 = {
    .pos = { -322.0f, 0.0f, -111.0f },
    .diameter = 0.0f
};

FoliageModelList Tree3_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o75);
FoliageModelList Tree3_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o74);

ShakeTreeConfig ShakeTree_Tree3 = {
    .leaves = &Tree3_LeafModels,
    .trunk = &Tree3_TrunkModels,
};

BombTrigger BombPos_Tree3 = {
    .pos = { -244.0f, 0.0f, 77.0f },
    .diameter = 0.0f
};

FoliageModelList Tree4_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o69);
FoliageModelList Tree4_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o68);

ShakeTreeConfig ShakeTree_Tree4 = {
    .leaves = &Tree4_LeafModels,
    .trunk = &Tree4_TrunkModels,
};

BombTrigger BombPos_Tree4 = {
    .pos = { -128.0f, 0.0f, -111.0f },
    .diameter = 0.0f
};

FoliageModelList Tree5_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o57);
FoliageModelList Tree5_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o56);

ShakeTreeConfig ShakeTree_Tree5 = {
    .leaves = &Tree5_LeafModels,
    .trunk = &Tree5_TrunkModels,
};

BombTrigger BombPos_Tree5 = {
    .pos = { 58.0f, 0.0f, 101.0f },
    .diameter = 0.0f
};

FoliageModelList Tree6_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o59);
FoliageModelList Tree6_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o58);

FoliageDropList Tree6_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_COIN,
            .pos = { 158, 100, -76 },
            .spawnMode = ITEM_SPAWN_MODE_FALL_SPAWN_ONCE,
            .pickupFlag = GF_SBK36_Tree6_Coin,
        },
    }
};

ShakeTreeConfig ShakeTree_Tree6 = {
    .leaves = &Tree6_LeafModels,
    .trunk = &Tree6_TrunkModels,
    .drops = &Tree6_Drops,
};

BombTrigger BombPos_Tree6 = {
    .pos = { 158.0f, 0.0f, -101.0f },
    .diameter = 0.0f
};

FoliageModelList Tree7_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o67);
FoliageModelList Tree7_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o66);

ShakeTreeConfig ShakeTree_Tree7 = {
    .leaves = &Tree7_LeafModels,
    .trunk = &Tree7_TrunkModels,
};

BombTrigger BombPos_Tree7 = {
    .pos = { 236.0f, 0.0f, 87.0f },
    .diameter = 0.0f
};

FoliageModelList Tree8_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o63);
FoliageModelList Tree8_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o62);

ShakeTreeConfig ShakeTree_Tree8 = {
    .leaves = &Tree8_LeafModels,
    .trunk = &Tree8_TrunkModels,
};

BombTrigger BombPos_Tree8 = {
    .pos = { 351.0f, 0.0f, -101.0f },
    .diameter = 0.0f
};

FoliageModelList Tree9_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o65);
FoliageModelList Tree9_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o64);

FoliageDropList Tree9_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_LETTER_TO_MORT_T,
            .pos = { 366, 92, 101 },
            .spawnMode = ITEM_SPAWN_MODE_FALL_NEVER_VANISH,
            .pickupFlag = GF_SBK36_Tree9_Letter03,
            .spawnFlag = MF_TreeDrop_Letter,
        },
    }
};

ShakeTreeConfig ShakeTree_Tree9 = {
    .leaves = &Tree9_LeafModels,
    .trunk = &Tree9_TrunkModels,
    .drops = &Tree9_Drops,
};

BombTrigger BombPos_Tree9 = {
    .pos = { 438.0f, 0.0f, 101.0f },
    .diameter = 0.0f
};

EvtScript EVS_SetupFoliage = {
    Set(LVar0, Ref(ShakeTree_Tree1))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o205, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree1), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree2))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o203, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree2), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree3))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o207, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree3), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree4))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o201, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree4), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree5))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o199, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree5), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree6))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o197, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree6), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree7))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o191, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree7), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree8))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o195, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree8), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree9))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o193, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree9), 1, 0)
    Return
    End
};
