#include "nok_15.h"

#include "foliage.h"

FoliageModelList Tree1_LeafModels = FOLIAGE_MODEL_LIST(MODEL_ha);
FoliageModelList Tree1_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_moku);

FoliageDropList Tree1_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_STAR_PIECE,
            .pos = { -523, 100, -110 },
            .spawnMode = ITEM_SPAWN_MODE_FALL_NEVER_VANISH,
            .pickupFlag = GF_NOK15_Tree1_StarPiece,
            .spawnFlag = MF_TreeDrop_StarPiece,
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
    BindTrigger(EVS_ShakeTree, TRIGGER_WALL_HAMMER, COLLIDER_o677, 1, 0)
    BindTrigger(EVS_ShakeTree, TRIGGER_POINT_BOMB, BombPos_Tree1, 1, 0)
    Return
    End
};
