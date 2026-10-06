#include "sbk_66.h"

#include "foliage.h"

FoliageModelList Tree1_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o62);
FoliageModelList Tree1_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o61);

ShakeTreeConfig ShakeTree_Tree1 = {
    .leaves = &Tree1_LeafModels,
    .trunk = &Tree1_TrunkModels,
};

BombTrigger BombTrigger_Tree1 = {
    .pos = { -326.0f, 0.0f, -204.0f },
    .diameter = 0.0f
};

FoliageModelList Tree2_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o58);
FoliageModelList Tree2_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o57);

ShakeTreeConfig ShakeTree_Tree2 = {
    .leaves = &Tree2_LeafModels,
    .trunk = &Tree2_TrunkModels,
};

BombTrigger BombTrigger_Tree2 = {
    .pos = { 116.0f, 0.0f, -394.0f },
    .diameter = 0.0f
};

FoliageModelList Tree3_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o56);
FoliageModelList Tree3_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o55);

FoliageDropList Tree3_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_COIN,
            .pos = { 398, 100, -91 },
            .spawnMode = ITEM_SPAWN_MODE_FALL_SPAWN_ONCE,
            .pickupFlag = GF_SBK66_Tree3_Coin,
        },
    }
};

ShakeTreeConfig ShakeTree_Tree3 = {
    .leaves = &Tree3_LeafModels,
    .trunk = &Tree3_TrunkModels,
    .drops = &Tree3_Drops,
};

BombTrigger BombTrigger_Tree3 = {
    .pos = { 398.0f, 0.0f, -116.0f },
    .diameter = 0.0f
};

EvtScript EVS_SetupFoliage = {
    Set(LVar0, Ref(ShakeTree_Tree1))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o180, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombTrigger_Tree1), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree2))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o182, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombTrigger_Tree2), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree3))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o184, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombTrigger_Tree3), 1, 0)
    Return
    End
};
