#include "kmr_11.h"

#include "foliage.h"

FoliageModelList Bush2_BushModels = FOLIAGE_MODEL_LIST(MODEL_kusa1);

FoliageVectorList Bush2_Effects = {
    .count = 1,
    .vectors = {
        { -257.0f, 13.0f, 32.0f },
    }
};

SearchBushConfig SearchBush_Bush2 = {
    .bush = &Bush2_BushModels,
    .vectors = &Bush2_Effects,
};

FoliageModelList Bush3_BushModels = FOLIAGE_MODEL_LIST(MODEL_kusa2);

FoliageVectorList Bush3_Effects = {
    .count = 1,
    .vectors = {
        { 415.0f, 21.0f, -208.0f },
    }
};

SearchBushConfig SearchBush_Bush3 = {
    .bush = &Bush3_BushModels,
    .vectors = &Bush3_Effects,
};

FoliageModelList Bush4_BushModels = FOLIAGE_MODEL_LIST(MODEL_o517);

FoliageVectorList Bush4_Effects = {
    .count = 1,
    .vectors = {
        { -905.0f, 21.0f, 72.0f },
    }
};

SearchBushConfig SearchBush_Bush4 = {
    .bush = &Bush4_BushModels,
    .vectors = &Bush4_Effects,
};

FoliageModelList Tree1_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o349);
FoliageModelList Tree1_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o352);

FoliageDropList Tree1_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_STAR_PIECE,
            .pos = { -711, 121, -105 },
            .spawnMode = ITEM_SPAWN_MODE_FALL_NEVER_VANISH,
            .pickupFlag = GF_KMR11_Tree1_StarPiece,
            .spawnFlag = MF_SpawnFlag_StarPiece,
        },
    }
};

FoliageVectorList Tree1_Effects = {
    .count = 2,
    .vectors = {
        { -725.0f, 117.0f, -137.0f },
        { -617.0f, 108.0f, -137.0f },
    }
};

ShakeTreeConfig ShakeTree_Tree1 = {
    .leaves = &Tree1_LeafModels,
    .trunk = &Tree1_TrunkModels,
    .drops = &Tree1_Drops,
    .vectors = &Tree1_Effects,
};

BombTrigger BombPos_Tree1 = {
    .pos = { -665.0f, 0.0f, -149.0f },
    .diameter = 0.0f
};

FoliageModelList Tree2_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o458);
FoliageModelList Tree2_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o461);

FoliageDropList Tree2_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_COIN,
            .pos = { 307, 115, -462 },
            .spawnMode = ITEM_SPAWN_MODE_FALL_SPAWN_ONCE,
            .pickupFlag = GF_KMR11_Tree2_Coin,
        },
    }
};

FoliageVectorList Tree2_Effects = {
    .count = 2,
    .vectors = {
        { 259.0f, 77.0f, -443.0f },
        { 354.0f, 96.0f, -500.0f },
    }
};

ShakeTreeConfig ShakeTree_Tree2 = {
    .leaves = &Tree2_LeafModels,
    .trunk = &Tree2_TrunkModels,
    .drops = &Tree2_Drops,
    .vectors = &Tree2_Effects,
};

BombTrigger BombPos_Tree2 = {
    .pos = { 320.0f, 0.0f, -496.0f },
    .diameter = 0.0f
};

EvtScript EVS_SetupFoliage = {
    Set(LVar0, Ref(SearchBush_Bush2))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_kusa1, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush3))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_kusa2, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush4))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o419, 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree1))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_tree1, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree1), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree2))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_tree2, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree2), 1, 0)
    Return
    End
};
