#include "nok_01.h"

#include "foliage.h"

FoliageModelList Bush5_BushModels = FOLIAGE_MODEL_LIST(MODEL_o315);

FoliageDropList Bush5_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_COIN,
            .pos = { -113, 16, 430 },
            .spawnMode = ITEM_SPAWN_MODE_TOSS_SPAWN_ONCE,
            .pickupFlag = GF_NOK01_Bush1_Coin,
        },
    }
};

SearchBushConfig SearchBush_Bush5 = {
    .bush = &Bush5_BushModels,
    .drops = &Bush5_Drops,
};

FoliageModelList Bush4_BushModels = FOLIAGE_MODEL_LIST(MODEL_o322, MODEL_o320);

FoliageDropList Bush3_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_KOOT_GLASSES,
            .pos = { -39, 16, 404 },
            .spawnMode = ITEM_SPAWN_MODE_TOSS_NEVER_VANISH,
            .pickupFlag = GF_NOK01_Bush6_Glasses,
            .spawnFlag = MF_Bush3_Drop,
        },
    }
};

SearchBushConfig SearchBush_Bush4 = {
    .bush = &Bush4_BushModels,
};

SearchBushConfig SearchBush_Bush3 = {
    .bush = &Bush4_BushModels,
    .drops = &Bush3_Drops,
};

FoliageModelList Bush6_BushModels = FOLIAGE_MODEL_LIST(MODEL_o390, MODEL_o396, MODEL_o397, MODEL_o398);

EvtScript EVS_Bush6_HideFlowers = {
    Call(EnableModel, MODEL_o396, false)
    Call(EnableModel, MODEL_o397, false)
    Call(EnableModel, MODEL_o398, false)
    Return
    End
};

EvtScript EVS_OnSearchBush6 = {
    Call(EnableModel, MODEL_o396, true)
    Wait(10)
    Call(EnableModel, MODEL_o398, true)
    Wait(10)
    Call(EnableModel, MODEL_o397, true)
    Return
    End
};

SearchBushConfig SearchBush_Bush6 = {
    .bush = &Bush6_BushModels,
    .callback = &EVS_OnSearchBush6,
};

FoliageModelList Bush7_BushModels = FOLIAGE_MODEL_LIST(MODEL_o391);

FoliageDropList Bush7_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_DRIED_SHROOM,
            .pos = { 43, 16, 443 },
            .spawnMode = ITEM_SPAWN_MODE_TOSS_SPAWN_ONCE,
            .pickupFlag = GF_NOK01_Bush3_DriedShroom,
        },
    }
};

SearchBushConfig SearchBush_Bush7 = {
    .bush = &Bush7_BushModels,
    .drops = &Bush7_Drops,
};

FoliageModelList Bush8_BushModels = FOLIAGE_MODEL_LIST(MODEL_o392);

FoliageDropList Bush8_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_KOOPA_LEAF,
            .pos = { 329, 16, 245 },
            .spawnMode = ITEM_SPAWN_MODE_TOSS,
            .pickupFlag = GF_NOK01_Bush4_KoopaLeaf,
            .spawnFlag = MF_Bush8_Drop,
        },
    }
};

SearchBushConfig SearchBush_Bush8 = {
    .bush = &Bush8_BushModels,
    .drops = &Bush8_Drops,
};

FoliageModelList Bush9_BushModels = FOLIAGE_MODEL_LIST(MODEL_o393, MODEL_o402);

FoliageDropList Bush9_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_COIN,
            .pos = { 364, 16, 102 },
            .spawnMode = ITEM_SPAWN_MODE_TOSS,
            .pickupFlag = GF_NOK01_Bush5_Coin,
            .spawnFlag = MF_Bush9_Drop,
        },
    }
};

SearchBushConfig SearchBush_Bush9 = {
    .bush = &Bush9_BushModels,
    .drops = &Bush9_Drops,
};

FoliageModelList Bush2_BushModels = FOLIAGE_MODEL_LIST(MODEL_o394, MODEL_o399, MODEL_o400, MODEL_o401);

FoliageDropList Bush1_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_KOOT_EMPTY_WALLET,
            .pos = { 441, 16, 57 },
            .spawnMode = ITEM_SPAWN_MODE_TOSS_NEVER_VANISH,
            .pickupFlag = GF_NOK01_Bush7_EmptyWallet,
            .spawnFlag = MF_Bush1_Drop,
        },
    }
};

EvtScript EVS_Bush2_HideFlowers = {
    Call(EnableModel, MODEL_o399, false)
    Call(EnableModel, MODEL_o400, false)
    Call(EnableModel, MODEL_o401, false)
    Return
    End
};

EvtScript EVS_OnSearchBush2 = {
    Call(EnableModel, MODEL_o399, true)
    Wait(10)
    Call(EnableModel, MODEL_o401, true)
    Wait(10)
    Call(EnableModel, MODEL_o400, true)
    Return
    End
};

SearchBushConfig SearchBush_Bush2 = {
    .bush = &Bush2_BushModels,
    .callback = &EVS_OnSearchBush2,
};

SearchBushConfig SearchBush_Bush1 = {
    .bush = &Bush2_BushModels,
    .drops = &Bush1_Drops,
    .callback = &EVS_OnSearchBush2,
};

FoliageModelList Tree1_LeafModels = FOLIAGE_MODEL_LIST(MODEL_o300);

FoliageModelList Tree1_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o299);

ShakeTreeConfig ShakeTree_Tree1 = {
    .leaves = &Tree1_LeafModels,
    .trunk = &Tree1_TrunkModels,
};

BombTrigger BombPos_Tree1 = {
    .pos = { 198.0f, 0.0f, 147.0f },
    .diameter = 0.0f
};

EvtScript EVS_SetupFoliage = {
    Set(LVar0, Ref(SearchBush_Bush5))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o312, 1, 0)
    IfEq(GB_KootFavor_Current, KOOT_FAVOR_CH6_2)
        Set(LVar0, Ref(SearchBush_Bush3))
    Else
        Set(LVar0, Ref(SearchBush_Bush4))
    EndIf
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o313, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush6))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o419, 1, 0)
    Exec(EVS_Bush6_HideFlowers)
    Set(LVar0, Ref(SearchBush_Bush7))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o420, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush8))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o421, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush9))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o422, 1, 0)
    IfEq(GB_KootFavor_Current, KOOT_FAVOR_CH3_2)
        Set(LVar0, Ref(SearchBush_Bush1))
    Else
        Set(LVar0, Ref(SearchBush_Bush2))
    EndIf
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o423, 1, 0)
    Exec(EVS_Bush2_HideFlowers)
    Set(LVar0, Ref(ShakeTree_Tree1))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o323, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree1), 1, 0)
    // bind the same tree a second time for the koopa shell stuck inside
    BindTrigger(Ref(EVS_Scene_RecoverTreeShell), TRIGGER_WALL_HAMMER, COLLIDER_o323, 1, 0)
    BindTrigger(Ref(EVS_Scene_RecoverTreeShell), TRIGGER_POINT_BOMB, Ref(BombPos_Tree1), 1, 0)
    Return
    End
};
