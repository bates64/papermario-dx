#include "jan_03.h"

#include "foliage.h"

FoliageModelList Tree1_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o351, MODEL_o352);
FoliageModelList Tree1_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o350);

FoliageDropList Tree1_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_COCONUT,
            .pos = { 586, 75, -115 },
            .spawnMode = ITEM_SPAWN_MODE_FALL_SPAWN_ONCE,
            .spawnFlag = AF_JAN03_TreeDrop1,
        },
    }
};

ShakeTreeConfig ShakeTree_Tree1 = {
    .leaves = &Tree1_LeafModels,
    .trunk = &Tree1_TrunkModels,
    .drops = &Tree1_Drops,
};

BombTrigger BombPos_Tree1 = {
    .pos = { 576.0f, 0.0f, -135.0f },
    .diameter = 0.0f
};

EvtScript EVS_SetupFoliage = {
    Set(AF_JAN03_TreeDrop1, false)
    Set(LVar0, Ref(ShakeTree_Tree1))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o440, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree1), 1, 0)
    Return
    End
};
