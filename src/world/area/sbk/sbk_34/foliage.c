#include "sbk_34.h"

#include "foliage.h"

FoliageModelList Tree1_LeafModels = FOLIAGE_MODEL_LIST(MODEL_o63);
FoliageModelList Tree1_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o62);

FoliageDropList Tree1_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_COIN,
            .pos = { 105, 100, -89 },
            .spawnMode = ITEM_SPAWN_MODE_FALL_SPAWN_ONCE,
            .pickupFlag = GF_SBK34_Tree1_Coin,
        },
    }
};

ShakeTreeConfig ShakeTree_Tree1 = {
    .leaves = &Tree1_LeafModels,
    .trunk = &Tree1_TrunkModels,
    .drops = &Tree1_Drops,
};

BombTrigger BombPos_Tree1 = {
    .pos = $BombPos_Tree1.pos,
    .diameter = 2.0f * $BombPos_Tree1.radius,
};

EvtScript EVS_SetupFoliage = {
    Set(LVar0, ShakeTree_Tree1)
    BindTrigger(EVS_ShakeTree, TRIGGER_WALL_HAMMER, COLLIDER_o201, 1, 0)
    BindTrigger(EVS_ShakeTree, TRIGGER_POINT_BOMB, BombPos_Tree1, 1, 0)
    Return
    End
};
