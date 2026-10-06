#include "flo_08.h"
#include "foliage.h"

FoliageModelList Tree1_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o133);
FoliageModelList Tree1_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o132);

FoliageDropList Tree1_Drops = {
    .count = 2,
    .drops = {
        {
            .itemID = ITEM_BLUE_BERRY,
            .pos = { 340, 102, -89 },
            .spawnMode = ITEM_SPAWN_MODE_FALL_SPAWN_ALWAYS,
            .spawnFlag = AF_FLO_TreeDrop_BlueBerry1,
        },
        {
            .itemID = ITEM_BLUE_BERRY,
            .pos = { 440, 102, -89 },
            .spawnMode = ITEM_SPAWN_MODE_FALL_SPAWN_ALWAYS,
            .spawnFlag = AF_FLO_TreeDrop_BlueBerry2,
        },
    }
};

ShakeTreeConfig ShakeTree_Tree1 = {
    .leaves = &Tree1_LeafModels,
    .trunk = &Tree1_TrunkModels,
    .drops = &Tree1_Drops,
};

BombTrigger BombPos_Tree1 = {
    .pos = { 391.0f, 0.0f, -102.0f },
    .diameter = 0.0f
};

EvtScript EVS_SetupFoliage = {
    Set(AF_FLO_TreeDrop_BlueBerry1, false)
    Set(AF_FLO_TreeDrop_BlueBerry2, false)
    Set(LVar0, Ref(ShakeTree_Tree1))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o172, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree1), 1, 0)
    Return
    End
};
