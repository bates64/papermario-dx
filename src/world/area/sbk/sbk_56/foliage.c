#include "sbk_56.h"

#include "foliage.h"

FoliageModelList Tree1_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_ki);
FoliageModelList Tree1_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_miki);

FoliageDropList Tree1_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_LEMON,
            .pos = { -304, 92, -176 },
            .spawnMode = ITEM_SPAWN_MODE_FALL,
            .pickupFlag = GF_SBK56_Tree1_Lemon,
            .spawnFlag = MF_TreeDrop_Lemon,
        },
    }
};

ShakeTreeConfig ShakeTree_Tree1 = {
    .leaves = &Tree1_LeafModels,
    .trunk = &Tree1_TrunkModels,
    .drops = &Tree1_Drops,
};

BombTrigger BombPos_Tree1 = {
    .pos = { -259.0f, 0.0f, -160.0f },
    .diameter = 0.0f
};

FoliageModelList Tree2_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_ki);
FoliageModelList Tree2_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_miki);

FoliageDropList Tree2_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_LIME,
            .pos = { 230, 77, -304 },
            .spawnMode = ITEM_SPAWN_MODE_FALL,
            .pickupFlag = GF_SBK56_Tree2_Lime,
            .spawnFlag = MF_TreeDrop_Lime,
        },
    }
};

ShakeTreeConfig ShakeTree_Tree2 = {
    .leaves = &Tree2_LeafModels,
    .trunk = &Tree2_TrunkModels,
    .drops = &Tree2_Drops,
};

BombTrigger BombPos_Tree2 = {
    .pos = { 171.0f, 0.0f, -291.0f },
    .diameter = 0.0f
};

FoliageModelList Tree3_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o52);
FoliageModelList Tree3_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_y_miki);

FoliageDropList Tree3_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_COIN,
            .pos = { -436, 100, 249 },
            .spawnMode = ITEM_SPAWN_MODE_FALL_SPAWN_ONCE,
            .pickupFlag = GF_SBK56_Tree3_Coin,
        },
    }
};

ShakeTreeConfig ShakeTree_Tree3 = {
    .leaves = &Tree3_LeafModels,
    .trunk = &Tree3_TrunkModels,
    .drops = &Tree3_Drops,
};

BombTrigger BombPos_Tree3 = {
    .pos = { -436.0f, 0.0f, 224.0f },
    .diameter = 0.0f
};

FoliageModelList Tree4_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_y_ha);
FoliageModelList Tree4_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o51);

ShakeTreeConfig ShakeTree_Tree4 = {
    .leaves = &Tree4_LeafModels,
    .trunk = &Tree4_TrunkModels,
};

BombTrigger BombPos_Tree4 = {
    .pos = { -320.0f, 0.0f, -21.0f },
    .diameter = 0.0f
};

FoliageModelList Tree5_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o54);
FoliageModelList Tree5_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o53);

ShakeTreeConfig ShakeTree_Tree5 = {
    .leaves = &Tree5_LeafModels,
    .trunk = &Tree5_TrunkModels,
};

BombTrigger BombPos_Tree5 = {
    .pos = { -242.0f, 0.0f, 88.0f },
    .diameter = 0.0f
};

FoliageModelList Tree6_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o56);
FoliageModelList Tree6_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o55);

ShakeTreeConfig ShakeTree_Tree6 = {
    .leaves = &Tree6_LeafModels,
    .trunk = &Tree6_TrunkModels,
};

BombTrigger BombPos_Tree6 = {
    .pos = { -203.0f, 0.0f, -214.0f },
    .diameter = 0.0f
};

FoliageModelList Tree7_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o58);
FoliageModelList Tree7_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o57);

ShakeTreeConfig ShakeTree_Tree7 = {
    .leaves = &Tree7_LeafModels,
    .trunk = &Tree7_TrunkModels,
};

BombTrigger BombPos_Tree7 = {
    .pos = { -101.0f, 0.0f, -376.0f },
    .diameter = 0.0f
};

FoliageModelList Tree8_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o60);
FoliageModelList Tree8_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o59);

ShakeTreeConfig ShakeTree_Tree8 = {
    .leaves = &Tree8_LeafModels,
    .trunk = &Tree8_TrunkModels,
};

BombTrigger BombPos_Tree8 = {
    .pos = { 104.0f, 0.0f, -386.0f },
    .diameter = 0.0f
};

FoliageModelList Tree9_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o62);
FoliageModelList Tree9_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o61);

FoliageDropList Tree9_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_COIN,
            .pos = { 266, 100, 149 },
            .spawnMode = ITEM_SPAWN_MODE_FALL_SPAWN_ONCE,
            .pickupFlag = GF_SBK56_Tree9_Coin,
        },
    }
};

ShakeTreeConfig ShakeTree_Tree9 = {
    .leaves = &Tree9_LeafModels,
    .trunk = &Tree9_TrunkModels,
    .drops = &Tree9_Drops,
};

BombTrigger BombPos_Tree9 = {
    .pos = { 266.0f, 0.0f, 124.0f },
    .diameter = 0.0f
};

FoliageModelList Tree10_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o64);
FoliageModelList Tree10_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o63);

ShakeTreeConfig ShakeTree_Tree10 = {
    .leaves = &Tree10_LeafModels,
    .trunk = &Tree10_TrunkModels,
};

BombTrigger BombPos_Tree10 = {
    .pos = { 362.0f, 0.0f, -74.0f },
    .diameter = 0.0f
};

EvtScript EVS_SetupFoliage = {
    Set(GF_SBK56_Tree1_Lemon, false)
    Set(GF_SBK56_UnusedA, false)
    Set(GF_SBK56_Tree2_Lime, false)
    Set(GF_SBK56_UnusedB, false)
    Set(LVar0, Ref(ShakeTree_Tree1))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_remon, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree1), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree2))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_rim, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree2), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree3))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_y_miki, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree3), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree4))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o67, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree4), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree5))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o68, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree5), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree6))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o69, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree6), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree7))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o70, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree7), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree8))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o71, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree8), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree9))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o72, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree9), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree10))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o73, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree10), 1, 0)
    Return
    End
};
