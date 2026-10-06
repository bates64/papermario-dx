#include "nok_02.h"

#include "foliage.h"

FoliageModelList Bush1_BushModels = FOLIAGE_MODEL_LIST(MODEL_o443, MODEL_o460);

FoliageDropList Bush1_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_KOOPA_LEAF,
            .pos = { -407, 16, 90 },
            .spawnMode = ITEM_SPAWN_MODE_TOSS_SPAWN_ONCE,
            .pickupFlag = GF_NOK02_Bush1_KoopaLeaf,
            .spawnFlag = MF_Bush1_Drop,
        },
    }
};

SearchBushConfig SearchBush_Bush1 = {
    .bush = &Bush1_BushModels,
    .drops = &Bush1_Drops,
};

FoliageModelList Bush2_BushModels = FOLIAGE_MODEL_LIST(MODEL_o444, MODEL_o461);

SearchBushConfig SearchBush_Bush2 = {
    .bush = &Bush2_BushModels,
};

FoliageModelList Bush3_BushModels = FOLIAGE_MODEL_LIST(MODEL_o445, MODEL_o462);

SearchBushConfig SearchBush_Bush3 = {
    .bush = &Bush3_BushModels,
};

FoliageModelList Bush4_BushModels = FOLIAGE_MODEL_LIST(MODEL_o446, MODEL_o454, MODEL_o455, MODEL_o456);

EvtScript EVS_Bush4_HideFlowers = {
    Call(EnableModel, MODEL_o454, false)
    Call(EnableModel, MODEL_o455, false)
    Call(EnableModel, MODEL_o456, false)
    Return
    End
};

EvtScript EVS_OnSearchBush4 = {
    Call(EnableModel, MODEL_o454, true)
    Wait(10)
    Call(EnableModel, MODEL_o456, true)
    Wait(10)
    Call(EnableModel, MODEL_o455, true)
    Return
    End
};

SearchBushConfig SearchBush_Bush4 = {
    .bush = &Bush4_BushModels,
    .callback = &EVS_OnSearchBush4,
};

FoliageModelList Bush5_BushModels = FOLIAGE_MODEL_LIST(MODEL_o447, MODEL_o457, MODEL_o458, MODEL_o459);

EvtScript EVS_Bush5_HideFlowers = {
    Call(EnableModel, MODEL_o457, false)
    Call(EnableModel, MODEL_o458, false)
    Call(EnableModel, MODEL_o459, false)
    Return
    End
};

EvtScript EVS_OnSearchBush5 = {
    Call(EnableModel, MODEL_o457, true)
    Wait(10)
    Call(EnableModel, MODEL_o459, true)
    Wait(10)
    Call(EnableModel, MODEL_o458, true)
    Return
    End
};

SearchBushConfig SearchBush_Bush5 = {
    .bush = &Bush5_BushModels,
    .callback = &EVS_OnSearchBush5,
};

FoliageModelList Bush6_BushModels = FOLIAGE_MODEL_LIST(MODEL_o448, MODEL_o314);

FoliageDropList Bush6_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_COIN,
            .pos = { 387, 16, 202 },
            .spawnMode = ITEM_SPAWN_MODE_TOSS_SPAWN_ONCE,
            .pickupFlag = GF_NOK01_Bush5_Coin,
        },
    }
};

SearchBushConfig SearchBush_Bush6 = {
    .bush = &Bush6_BushModels,
    .drops = &Bush6_Drops,
};

FoliageModelList Tree1_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o284);
FoliageModelList Tree1_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o283);

EvtScript EVS_OnShakeTree1 = {
    Wait(15)
    Set(AF_NOK02_FuzzyTreeHit, true)
    Return
    End
};

ShakeTreeConfig ShakeTree_Tree1 = {
    .leaves = &Tree1_LeafModels,
    .trunk = &Tree1_TrunkModels,
    .callback = &EVS_OnShakeTree1,
};

BombTrigger BombPos_Tree1 = {
    .pos = { 443.0f, 0.0f, 68.0f },
    .diameter = 0.0f
};

EvtScript EVS_SetupFoliage = {
    Set(LVar0, Ref(SearchBush_Bush1))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o332, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush2))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o427, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush3))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o458, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush4))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o459, 1, 0)
    Exec(EVS_Bush4_HideFlowers)
    Set(LVar0, Ref(SearchBush_Bush5))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o460, 1, 0)
    Exec(EVS_Bush5_HideFlowers)
    Set(LVar0, Ref(SearchBush_Bush6))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o461, 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree1))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o346, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree1), 1, 0)
    Return
    End
};
