#include "flo_25.h"

#include "foliage.h"

FoliageModelList Tree1_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o43, MODEL_o44, MODEL_o45);
FoliageModelList Tree1_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o42);

FoliageDropList Tree1_Drops = {
    .count = 2,
    .drops = {
        {
            .itemID = ITEM_YELLOW_BERRY,
            .pos = { -432, 84, -44 },
            .spawnMode = ITEM_SPAWN_MODE_FALL_SPAWN_ALWAYS,
            .spawnFlag = AF_FLO_TreeDrop_YellowBerry1,
        },
        {
            .itemID = ITEM_YELLOW_BERRY,
            .pos = { -346, 72, -114 },
            .spawnMode = ITEM_SPAWN_MODE_FALL_SPAWN_ALWAYS,
            .spawnFlag = AF_FLO_TreeDrop_YellowBerry2,
        },
    }
};

ShakeTreeConfig ShakeTree_Tree1 = {
    .leaves = &Tree1_LeafModels,
    .trunk = &Tree1_TrunkModels,
    .drops = &Tree1_Drops,
};

BombTrigger BombPos_Tree1 = {
    .pos = { -388.0f, 0.0f, -92.0f },
    .diameter = 0.0f
};

EvtScript EVS_SetupFoliage = {
    Set(AF_FLO_TreeDrop_YellowBerry1, false)
    Set(AF_FLO_TreeDrop_YellowBerry2, false)
    Set(LVar0, Ref(ShakeTree_Tree1))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o42, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree1), 1, 0)
    Return
    End
};
