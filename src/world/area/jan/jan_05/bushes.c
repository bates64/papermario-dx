#include "jan_05.h"
#include "foliage.h"

#include "../common/MoveBush.inc.c"
#include "../common/MoveBushTemplates.h"

EvtScript EVS_MoveBushes_Separate = EVT_MOVE_BUSHES(COLLIDER_o64,
    MODEL_o64, MODEL_o65, MV_BushOffsetL, MV_BushOffsetR);

EvtScript EVS_MoveBushes = {
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o64, COLLIDER_FLAGS_UPPER_MASK)
    Exec(EVS_MoveBushes_Separate)
    Call(DisablePlayerInput, true)
    Call(MakeLerp, 0, 45, 30, EASING_CUBIC_OUT)
    Label(0)
    Call(UpdateLerp)
    SetF(MV_BushOffsetR, LVar0)
    SetF(MV_BushOffsetL, MV_BushOffsetR)
    MulF(MV_BushOffsetL, -1)
    IfEq(LVar1, 1)
        Wait(1)
        Goto(0)
    EndIf
    Call(DisablePlayerInput, false)
    Return
    End
};

FoliageModelList Bush1_BushModels = FOLIAGE_MODEL_LIST(MODEL_o63);

FoliageDropList Bush1_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_COIN,
            .pos = { 168, 20, 375 },
            .spawnMode = ITEM_SPAWN_MODE_TOSS_SPAWN_ONCE,
            .pickupFlag = GF_JAN05_Bush1_Coin,
        },
    }
};

FoliageVectorList Bush1_Effects = {
    .count = 1,
    .vectors = {
        { 168.0f, 20.0f, 375.0f },
    }
};

SearchBushConfig SearchBush_Bush1 = {
    .bush = &Bush1_BushModels,
    .drops = &Bush1_Drops,
    .vectors = &Bush1_Effects,
};

FoliageModelList Bush2_BushModels = FOLIAGE_MODEL_LIST(MODEL_o141);

FoliageDropList Bush2_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_COIN,
            .pos = { -401, 20, 176 },
            .spawnMode = ITEM_SPAWN_MODE_TOSS,
            .pickupFlag = GF_JAN05_Bush2_Coin,
            .spawnFlag = MF_BushDrop_Coin,
        },
    }
};

FoliageVectorList Bush2_Effects = {
    .count = 1,
    .vectors = {
        { -401.0f, 20.0f, 176.0f },
    }
};

SearchBushConfig SearchBush_Bush2 = {
    .bush = &Bush2_BushModels,
    .drops = &Bush2_Drops,
    .vectors = &Bush2_Effects,
};

FoliageModelList Bush3_BushModels = FOLIAGE_MODEL_LIST(MODEL_o140);

FoliageVectorList Bush3_Effects = {
    .count = 1,
    .vectors = {
        { -242.0f, 22.0f, 205.0f },
    }
};

SearchBushConfig SearchBush_Bush3 = {
    .bush = &Bush3_BushModels,
    .vectors = &Bush3_Effects,
};

FoliageModelList Bush4_BushModels = FOLIAGE_MODEL_LIST(MODEL_o142);

FoliageVectorList Bush4_Effects = {
    .count = 1,
    .vectors = {
        { -206.0f, 20.0f, 248.0f },
    }
};

SearchBushConfig SearchBush_Bush4 = {
    .bush = &Bush4_BushModels,
    .vectors = &Bush4_Effects,
};

FoliageModelList Bush5_BushModels = FOLIAGE_MODEL_LIST(MODEL_o134);

FoliageVectorList Bush5_Effects = {
    .count = 1,
    .vectors = {
        { -462.0f, 20.0f, -207.0f },
    }
};

SearchBushConfig SearchBush_Bush5 = {
    .bush = &Bush5_BushModels,
    .vectors = &Bush5_Effects,
};

FoliageModelList Bush6_BushModels = FOLIAGE_MODEL_LIST(MODEL_o137);

FoliageVectorList Bush6_Effects = {
    .count = 1,
    .vectors = {
        { -417.0f, 20.0f, -261.0f },
    }
};

SearchBushConfig SearchBush_Bush6 = {
    .bush = &Bush6_BushModels,
    .vectors = &Bush6_Effects,
};

FoliageModelList Bush7_BushModels = FOLIAGE_MODEL_LIST(MODEL_o131);

FoliageVectorList Bush7_Effects = {
    .count = 1,
    .vectors = {
        { -32.0f, 22.0f, -364.0f },
    }
};

SearchBushConfig SearchBush_Bush7 = {
    .bush = &Bush7_BushModels,
    .vectors = &Bush7_Effects,
};

FoliageModelList Bush8_BushModels = FOLIAGE_MODEL_LIST(MODEL_o132);

FoliageVectorList Bush8_Effects = {
    .count = 1,
    .vectors = {
        { -91.0f, 20.0f, -485.0f },
    }
};

SearchBushConfig SearchBush_Bush8 = {
    .bush = &Bush8_BushModels,
    .vectors = &Bush8_Effects,
};

FoliageModelList Bush9_BushModels = FOLIAGE_MODEL_LIST(MODEL_o133);

FoliageVectorList Bush9_Effects = {
    .count = 1,
    .vectors = {
        { 94.0f, 22.0f, -485.0f },
    }
};

SearchBushConfig SearchBush_Bush9 = {
    .bush = &Bush9_BushModels,
    .vectors = &Bush9_Effects,
};

FoliageModelList Bush10_BushModels = FOLIAGE_MODEL_LIST(MODEL_o139);

FoliageVectorList Bush10_Effects = {
    .count = 1,
    .vectors = {
        { 9.0f, 20.0f, -90.0f },
    }
};

SearchBushConfig SearchBush_Bush10 = {
    .bush = &Bush10_BushModels,
    .vectors = &Bush10_Effects,
};

FoliageModelList Bush11_BushModels = FOLIAGE_MODEL_LIST(MODEL_o138);

FoliageVectorList Bush11_Effects = {
    .count = 1,
    .vectors = {
        { 53.0f, 20.0f, -63.0f },
    }
};

SearchBushConfig SearchBush_Bush11 = {
    .bush = &Bush11_BushModels,
    .vectors = &Bush11_Effects,
};

FoliageModelList Bush12_BushModels = FOLIAGE_MODEL_LIST(MODEL_o102);

FoliageVectorList Bush12_Effects = {
    .count = 1,
    .vectors = {
        { 339.0f, 22.0f, -151.0f },
    }
};

SearchBushConfig SearchBush_Bush12 = {
    .bush = &Bush12_BushModels,
    .vectors = &Bush12_Effects,
};

FoliageModelList Bush13_BushModels = FOLIAGE_MODEL_LIST(MODEL_o126);

FoliageVectorList Bush13_Effects = {
    .count = 1,
    .vectors = {
        { 144.0f, 22.0f, 490.0f },
    }
};

SearchBushConfig SearchBush_Bush13 = {
    .bush = &Bush13_BushModels,
    .vectors = &Bush13_Effects,
};

FoliageModelList Bush14_BushModels = FOLIAGE_MODEL_LIST(MODEL_o106);

FoliageVectorList Bush14_Effects = {
    .count = 1,
    .vectors = {
        { 209.0f, 20.0f, 471.0f },
    }
};

SearchBushConfig SearchBush_Bush14 = {
    .bush = &Bush14_BushModels,
    .vectors = &Bush14_Effects,
};

EvtScript EVS_SetupBushes = {
    BindTrigger(Ref(EVS_MoveBushes), TRIGGER_WALL_PRESS_A, COLLIDER_o64, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush1))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o135, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush2))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o213, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush3))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o214, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush4))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o215, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush5))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o216, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush6))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o217, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush7))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o218, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush8))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o219, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush9))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o220, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush10))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o221, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush11))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o222, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush12))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o223, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush13))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o224, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush14))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o225, 1, 0)
    Return
    End
};
