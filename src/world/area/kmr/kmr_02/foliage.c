#include "kmr_02.h"

#include "foliage.h"

FoliageModelList Bush1_BushModels = FOLIAGE_MODEL_LIST(MODEL_kusa1);

FoliageVectorList Bush1_Effects = {
    .count = 1,
    .vectors = {
        { -418.0f, 16.0f, 237.0f },
    }
};

SearchBushConfig SearchBush_Bush1 = {
    .bush = &Bush1_BushModels,
    .vectors = &Bush1_Effects,
};

FoliageModelList Bush2_BushModels = FOLIAGE_MODEL_LIST(MODEL_kusa2);

FoliageDropList Bush2_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_COIN,
            .pos = { 124, 16, 443 },
            .spawnMode = ITEM_SPAWN_MODE_TOSS,
            .pickupFlag = GF_KMR02_Bush2_Coin,
            .spawnFlag = MF_SpawnFlag_BushCoin,
        },
    }
};

FoliageVectorList Bush2_Effects = {
    .count = 1,
    .vectors = {
        { 124.0f, 16.0f, 443.0f },
    }
};

SearchBushConfig SearchBush_Bush2 = {
    .bush = &Bush2_BushModels,
    .drops = &Bush2_Drops,
    .vectors = &Bush2_Effects,
};

FoliageModelList Bush3_BushModels = FOLIAGE_MODEL_LIST(MODEL_kusa3);

FoliageVectorList Bush3_Effects = {
    .count = 1,
    .vectors = {
        { -34.0f, 21.0f, -188.0f },
    }
};

SearchBushConfig SearchBush_Bush3 = {
    .bush = &Bush3_BushModels,
    .vectors = &Bush3_Effects,
};

FoliageModelList Tree1_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_midori);
FoliageModelList Tree1_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_kiki);

FoliageDropList Tree1_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_GOOMNUT,
            .pos = { 309, 145, 66 },
            .spawnMode = ITEM_SPAWN_MODE_FALL,
            .pickupFlag = GF_KMR02_Tree1_Goomnut,
            .spawnFlag = MF_SpawnFlag_Goomnut,
        },
    }
};

FoliageVectorList Tree1_Effects = {
    .count = 2,
    .vectors = {
        { 355.0f, 160.0f, 65.0f },
        { 440.0f, 160.0f, 137.0f },
    }
};

ShakeTreeConfig ShakeTree_Tree1 = {
    .leaves = &Tree1_LeafModels,
    .trunk = &Tree1_TrunkModels,
    .drops = &Tree1_Drops,
    .vectors = &Tree1_Effects,
};

BombTrigger BombPos_Tree1 = {
    .pos = { 387.0f, 0.0f, 92.0f },
    .diameter = 0.0f
};

EvtScript EVS_SetupFoliage = {
    Set(LVar0, Ref(SearchBush_Bush1))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o356, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush2))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o357, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush3))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o414, 1, 0)
    Set(GF_KMR02_Tree1_Goomnut, false)
    Set(LVar0, Ref(ShakeTree_Tree1))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o570, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree1), 1, 0)
    Return
    End
};
