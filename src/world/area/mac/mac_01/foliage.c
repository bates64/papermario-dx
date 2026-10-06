#include "mac_01.h"

#include "foliage.h"

FoliageDropList Tree1_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_STAR_PIECE,
            .pos = { -480, 120, -174 },
            .spawnMode = ITEM_SPAWN_MODE_FALL_NEVER_VANISH,
            .pickupFlag = GF_MAC01_Tree1_StarPiece,
            .spawnFlag = MF_SpawnFlag_Tree1,
        },
    }
};

FoliageModelList Tree1_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o362);
FoliageModelList Tree1_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o365);

FoliageVectorList Tree1_Effects = {
    .count = 2,
    .vectors = {
        { -532.0f, 135.0f, -174.0f },
        { -492.0f, 135.0f, -184.0f },
    }
};

ShakeTreeConfig ShakeTree_Tree1 = {
    .leaves = &Tree1_LeafModels,
    .trunk = &Tree1_TrunkModels,
    .drops = &Tree1_Drops,
    .vectors = &Tree1_Effects,
};

BombTrigger BombPos_Tree1 = {
    .pos = { -512.0f, 20.0f, -154.0f },
    .diameter = 0.0f
};

FoliageModelList Tree2_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o115);
FoliageModelList Tree2_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o116);

FoliageVectorList Tree2_Effects = {
    .count = 2,
    .vectors = {
        { -177.0f, 104.0f, -478.0f },
        { -137.0f, 104.0f, -488.0f },
    }
};

ShakeTreeConfig ShakeTree_Tree2 = {
    .leaves = &Tree2_LeafModels,
    .trunk = &Tree2_TrunkModels,
    .vectors = &Tree2_Effects,
};

BombTrigger BombPos_Tree2 = {
    .pos = { -157.0f, 20.0f, -458.0f },
    .diameter = 0.0f
};

EvtScript EVS_SetupFoliage = {
    Set(LVar0, Ref(ShakeTree_Tree1))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o393, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree1), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree2))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o237, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree2), 1, 0)
    Return
    End
};
