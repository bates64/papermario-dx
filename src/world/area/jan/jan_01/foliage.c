#include "jan_01.h"

#include "foliage.h"

FoliageModelList Tree1_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o99);
FoliageModelList Tree1_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o98);

ShakeTreeConfig ShakeTree_Tree1 = {
    .leaves = &Tree1_LeafModels,
    .trunk = &Tree1_TrunkModels,
};

BombTrigger BombPos_Tree1 = {
    .pos = { 160.0f, 0.0f, -287.0f },
    .diameter = 0.0f
};

FoliageModelList Tree2_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o85, MODEL_o86);
FoliageModelList Tree2_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o84);

FoliageDropList Tree2_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_COCONUT,
            .pos = { -618, 95, -75 },
            .spawnMode = ITEM_SPAWN_MODE_FALL_SPAWN_ONCE,
            .spawnFlag = AF_JAN01_TreeDrop2,
        },
    }
};

ShakeTreeConfig ShakeTree_Tree2 = {
    .leaves = &Tree2_LeafModels,
    .trunk = &Tree2_TrunkModels,
    .drops = &Tree2_Drops,
};

BombTrigger BombPos_Tree2 = {
    .pos = { -628.0f, 0.0f, -95.0f },
    .diameter = 0.0f
};

FoliageModelList Tree3_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o79, MODEL_o80);
FoliageModelList Tree3_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o78);

FoliageDropList Tree3_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_COCONUT,
            .pos = { -401, 105, -115 },
            .spawnMode = ITEM_SPAWN_MODE_FALL_SPAWN_ONCE,
            .spawnFlag = AF_JAN01_TreeDrop3,
        },
    }
};

ShakeTreeConfig ShakeTree_Tree3 = {
    .leaves = &Tree3_LeafModels,
    .trunk = &Tree3_TrunkModels,
    .drops = &Tree3_Drops,
};

BombTrigger BombPos_Tree3 = {
    .pos = { -391.0f, 0.0f, -135.0f },
    .diameter = 0.0f
};

FoliageModelList Tree4_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o82, MODEL_o83);
FoliageModelList Tree4_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o81);

FoliageDropList Tree4_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_COCONUT,
            .pos = { -351, 75, -95 },
            .spawnMode = ITEM_SPAWN_MODE_FALL_SPAWN_ONCE,
            .spawnFlag = AF_JAN01_TreeDrop4,
        },
    }
};

ShakeTreeConfig ShakeTree_Tree4 = {
    .leaves = &Tree4_LeafModels,
    .trunk = &Tree4_TrunkModels,
    .drops = &Tree4_Drops,
};

BombTrigger BombPos_Tree4 = {
    .pos = { -341.0f, 0.0f, -115.0f },
    .diameter = 0.0f
};

FoliageModelList Tree5_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o88, MODEL_o89);
FoliageModelList Tree5_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o87);

FoliageDropList Tree5_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_COCONUT,
            .pos = { 58, 95, -135 },
            .spawnMode = ITEM_SPAWN_MODE_FALL_SPAWN_ONCE,
            .spawnFlag = AF_JAN01_TreeDrop5,
        },
    }
};

ShakeTreeConfig ShakeTree_Tree5 = {
    .leaves = &Tree5_LeafModels,
    .trunk = &Tree5_TrunkModels,
    .drops = &Tree5_Drops,
};

BombTrigger BombPos_Tree5 = {
    .pos = { 68.0f, 0.0f, -155.0f },
    .diameter = 0.0f
};

FoliageModelList Tree6_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o104, MODEL_o105);
FoliageModelList Tree6_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o103);

FoliageDropList Tree6_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_COCONUT,
            .pos = { 261, 75, -115 },
            .spawnMode = ITEM_SPAWN_MODE_FALL_SPAWN_ONCE,
            .spawnFlag = AF_JAN01_TreeDrop6,
        },
    }
};

ShakeTreeConfig ShakeTree_Tree6 = {
    .leaves = &Tree6_LeafModels,
    .trunk = &Tree6_TrunkModels,
    .drops = &Tree6_Drops,
};

BombTrigger BombPos_Tree6 = {
    .pos = { 251.0f, 0.0f, -135.0f },
    .diameter = 0.0f
};

FoliageModelList Tree7_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o113, MODEL_o114);
FoliageModelList Tree7_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o112);

FoliageDropList Tree7_DropsA = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_STAR_PIECE,
            .pos = { 441, 75, -135 },
            .spawnMode = ITEM_SPAWN_MODE_FALL_NEVER_VANISH,
            .pickupFlag = GF_JAN01_Tree7_StarPiece,
            .spawnFlag = AF_JAN01_TreeDrop_StarPiece,
        },
    }
};

FoliageDropList Tree7_DropsB = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_COCONUT,
            .pos = { 441, 75, -135 },
            .spawnMode = ITEM_SPAWN_MODE_FALL_SPAWN_ONCE,
            .spawnFlag = AF_JAN01_TreeDrop7,
        },
    }
};

ShakeTreeConfig ShakeTree_Tree7A = {
    .leaves = &Tree7_LeafModels,
    .trunk = &Tree7_TrunkModels,
    .drops = &Tree7_DropsA,
};

ShakeTreeConfig ShakeTree_Tree7B = {
    .leaves = &Tree7_LeafModels,
    .trunk = &Tree7_TrunkModels,
    .drops = &Tree7_DropsB,
};

BombTrigger BombPos_Tree7 = {
    .pos = { 431.0f, 0.0f, -155.0f },
    .diameter = 0.0f
};

EvtScript EVS_SetupFoliage = {
    Set(AF_JAN01_TreeDrop2, false)
    Set(AF_JAN01_TreeDrop3, false)
    Set(AF_JAN01_TreeDrop4, false)
    Set(AF_JAN01_TreeDrop5, false)
    Set(AF_JAN01_TreeDrop6, false)
    Set(AF_JAN01_TreeDrop7, false)
    Set(LVar0, Ref(ShakeTree_Tree1))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o204, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree1), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree2))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o84, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree2), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree3))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o203, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree3), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree4))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o152, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree4), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree5))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o155, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree5), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree6))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o103, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree6), 1, 0)
    IfEq(GF_JAN01_Tree7_StarPiece, false)
        Set(LVar0, Ref(ShakeTree_Tree7A))
    Else
        Set(LVar0, Ref(ShakeTree_Tree7B))
    EndIf
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o205, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree7), 1, 0)
    Return
    End
};
