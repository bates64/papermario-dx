#include "iwa_10.h"

#include "foliage.h"

FoliageModelList Bush1_BushModels = FOLIAGE_MODEL_LIST(MODEL_k4);

FoliageDropList Bush1_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_COIN,
            .pos = { -839, 15, 521 },
            .spawnMode = ITEM_SPAWN_MODE_TOSS,
            .pickupFlag = GF_IWA10_Bush1_Coin,
            .spawnFlag = MF_DropBush1,
        },
    }
};

FoliageVectorList Bush1_Effects = {
    .count = 1,
    .vectors = {
        { -839.0f, 15.0f, 521.0f },
    }
};

SearchBushConfig SearchBush_Bush1 = {
    .bush = &Bush1_BushModels,
    .drops = &Bush1_Drops,
    .vectors = &Bush1_Effects,
};

FoliageModelList Bush2_BushModels = FOLIAGE_MODEL_LIST(MODEL_k5);

FoliageDropList Bush2_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_COIN,
            .pos = { -691, 22, 384 },
            .spawnMode = ITEM_SPAWN_MODE_TOSS,
            .pickupFlag = GF_IWA10_Bush2_Coin,
            .spawnFlag = MF_DropBush2,
        },
    }
};

FoliageVectorList Bush2_Effects = {
    .count = 1,
    .vectors = {
        { -691.0f, 22.0f, 384.0f },
    }
};

SearchBushConfig SearchBush_Bush2 = {
    .bush = &Bush2_BushModels,
    .drops = &Bush2_Drops,
    .vectors = &Bush2_Effects,
};

FoliageModelList Bush3_BushModels = FOLIAGE_MODEL_LIST(MODEL_k6);

FoliageDropList Bush3_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_COIN,
            .pos = { -932, 21, 405 },
            .spawnMode = ITEM_SPAWN_MODE_TOSS,
            .pickupFlag = GF_IWA10_Bush3_Coin,
            .spawnFlag = MF_DropBush3,
        },
    }
};

FoliageVectorList Bush3_Effects = {
    .count = 1,
    .vectors = {
        { -932.0f, 21.0f, 405.0f },
    }
};

SearchBushConfig SearchBush_Bush3 = {
    .bush = &Bush3_BushModels,
    .drops = &Bush3_Drops,
    .vectors = &Bush3_Effects,
};

FoliageModelList Bush4_BushModels = FOLIAGE_MODEL_LIST(MODEL_k7);

FoliageDropList Bush4_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_EGG,
            .pos = { -800, 23, 280 },
            .spawnMode = ITEM_SPAWN_MODE_TOSS,
            .spawnFlag = MF_DropBush4,
        },
    }
};

FoliageVectorList Bush4_Effects = {
    .count = 1,
    .vectors = {
        { -800.0f, 23.0f, 280.0f },
    }
};

SearchBushConfig SearchBush_Bush4 = {
    .bush = &Bush4_BushModels,
    .drops = &Bush4_Drops,
    .vectors = &Bush4_Effects,
};

EvtScript EVS_SetupFoliage = {
    Set(LVar0, Ref(SearchBush_Bush1))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_k4, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush2))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_k5, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush3))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_k6, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush4))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_k7, 1, 0)
    Return
    End
};
