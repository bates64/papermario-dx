#include "sbk_26.h"

#include "foliage.h"

FoliageModelList Tree1_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o60);
FoliageModelList Tree1_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o59);

FoliageDropList Tree1_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_COIN,
            .pos = { -155, 92, 160 },
            .spawnMode = ITEM_SPAWN_MODE_FALL_SPAWN_ONCE,
            .pickupFlag = GF_SBK26_Tree1_Coin,
        },
    }
};

ShakeTreeConfig ShakeTree_Tree1 = {
    .leaves = &Tree1_LeafModels,
    .trunk = &Tree1_TrunkModels,
    .drops = &Tree1_Drops,
};

BombTrigger BombPos_Tree1 = {
    .pos = { -178.0f, 0.0f, 164.0f },
    .diameter = 0.0f
};

EvtScript EVS_SetupFoliage = {
    Set(LVar0, Ref(ShakeTree_Tree1))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o191, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree1), 1, 0)
    Return
    End
};
