#include "jan_00.h"
#include "effects.h"

#include "foliage.h"

FoliageModelList Tree1_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o241, MODEL_o242);
FoliageModelList Tree1_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o240);

FoliageDropList Tree1_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_COCONUT,
            .pos = { 485, 95, -145 },
            .spawnMode = ITEM_SPAWN_MODE_FALL_SPAWN_ONCE,
            .spawnFlag = AF_JAN00_TreeDrop1,
        },
    }
};

ShakeTreeConfig ShakeTree_Tree1 = {
    .leaves = &Tree1_LeafModels,
    .trunk = &Tree1_TrunkModels,
    .drops = &Tree1_Drops,
};

BombTrigger BombPos_Tree1 = {
    .pos = { 481.0f, 0.0f, -165.0f },
    .diameter = 0.0f
};

EvtScript EVS_SetupFoliage = {
    Set(AF_JAN00_TreeDrop1, false)
    Set(LVar0, Ref(ShakeTree_Tree1))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o282, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree1), 1, 0)
    Return
    End
};
