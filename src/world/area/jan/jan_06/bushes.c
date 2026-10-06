#include "jan_06.h"
#include "foliage.h"

FoliageModelList Bush1_BushModels = FOLIAGE_MODEL_LIST(MODEL_o136);

FoliageVectorList Bush1_Effects = {
    .count = 1,
    .vectors = {
        { -469.0f, 20.0f, -117.0f },
    }
};

SearchBushConfig SearchBush_Bush1 = {
    .bush = &Bush1_BushModels,
    .vectors = &Bush1_Effects,
};

FoliageModelList Bush2_BushModels = FOLIAGE_MODEL_LIST(MODEL_o135);

FoliageVectorList Bush2_Effects = {
    .count = 1,
    .vectors = {
        { -451.0f, 22.0f, -145.0f },
    }
};

SearchBushConfig SearchBush_Bush2 = {
    .bush = &Bush2_BushModels,
    .vectors = &Bush2_Effects,
};

FoliageModelList Bush3_BushModels = FOLIAGE_MODEL_LIST(MODEL_o130);

FoliageVectorList Bush3_Effects = {
    .count = 1,
    .vectors = {
        { -256.0f, 22.0f, -422.0f },
    }
};

SearchBushConfig SearchBush_Bush3 = {
    .bush = &Bush3_BushModels,
    .vectors = &Bush3_Effects,
};

FoliageModelList Bush4_BushModels = FOLIAGE_MODEL_LIST(MODEL_o127);

FoliageVectorList Bush4_Effects = {
    .count = 1,
    .vectors = {
        { -141.0f, 20.0f, -484.0f },
    }
};

SearchBushConfig SearchBush_Bush4 = {
    .bush = &Bush4_BushModels,
    .vectors = &Bush4_Effects,
};

FoliageModelList Bush5_BushModels = FOLIAGE_MODEL_LIST(MODEL_o128);

FoliageVectorList Bush5_Effects = {
    .count = 1,
    .vectors = {
        { -80.0f, 20.0f, -490.0f },
    }
};

SearchBushConfig SearchBush_Bush5 = {
    .bush = &Bush5_BushModels,
    .vectors = &Bush5_Effects,
};

FoliageModelList Bush6_BushModels = FOLIAGE_MODEL_LIST(MODEL_o129);

FoliageVectorList Bush6_Effects = {
    .count = 1,
    .vectors = {
        { 84.0f, 22.0f, -490.0f },
    }
};

SearchBushConfig SearchBush_Bush6 = {
    .bush = &Bush6_BushModels,
    .vectors = &Bush6_Effects,
};

FoliageModelList Bush7_BushModels = FOLIAGE_MODEL_LIST(MODEL_o132);

FoliageVectorList Bush7_Effects = {
    .count = 1,
    .vectors = {
        { 200.0f, 20.0f, -464.0f },
    }
};

SearchBushConfig SearchBush_Bush7 = {
    .bush = &Bush7_BushModels,
    .vectors = &Bush7_Effects,
};

FoliageModelList Bush8_BushModels = FOLIAGE_MODEL_LIST(MODEL_o125);

FoliageVectorList Bush8_Effects = {
    .count = 1,
    .vectors = {
        { 114.0f, 20.0f, -7.0f },
    }
};

SearchBushConfig SearchBush_Bush8 = {
    .bush = &Bush8_BushModels,
    .vectors = &Bush8_Effects,
};

FoliageModelList Bush9_BushModels = FOLIAGE_MODEL_LIST(MODEL_o126);

FoliageVectorList Bush9_Effects = {
    .count = 1,
    .vectors = {
        { 164.0f, 22.0f, -25.0f },
    }
};

SearchBushConfig SearchBush_Bush9 = {
    .bush = &Bush9_BushModels,
    .vectors = &Bush9_Effects,
};

FoliageModelList Bush10_BushModels = FOLIAGE_MODEL_LIST(MODEL_o123);

FoliageVectorList Bush10_Effects = {
    .count = 1,
    .vectors = {
        { -124.0f, 22.0f, 372.0f },
    }
};

SearchBushConfig SearchBush_Bush10 = {
    .bush = &Bush10_BushModels,
    .vectors = &Bush10_Effects,
};

FoliageModelList Bush11_BushModels = FOLIAGE_MODEL_LIST(MODEL_o124);

FoliageVectorList Bush11_Effects = {
    .count = 1,
    .vectors = {
        { -87.0f, 20.0f, 341.0f },
    }
};

SearchBushConfig SearchBush_Bush11 = {
    .bush = &Bush11_BushModels,
    .vectors = &Bush11_Effects,
};

FoliageModelList Bush12_BushModels = FOLIAGE_MODEL_LIST(MODEL_o137);

FoliageVectorList Bush12_Effects = {
    .count = 1,
    .vectors = {
        { 150.0f, 20.0f, 486.0f },
    }
};

SearchBushConfig SearchBush_Bush12 = {
    .bush = &Bush12_BushModels,
    .vectors = &Bush12_Effects,
};

FoliageModelList Bush13_BushModels = FOLIAGE_MODEL_LIST(MODEL_o131);

FoliageVectorList Bush13_Effects = {
    .count = 1,
    .vectors = {
        { 396.0f, 20.0f, -90.0f },
    }
};

SearchBushConfig SearchBush_Bush13 = {
    .bush = &Bush13_BushModels,
    .vectors = &Bush13_Effects,
};

FoliageModelList Bush14_BushModels = FOLIAGE_MODEL_LIST(MODEL_o139);

FoliageVectorList Bush14_Effects = {
    .count = 1,
    .vectors = {
        { 439.0f, 22.0f, 140.0f },
    }
};

SearchBushConfig SearchBush_Bush14 = {
    .bush = &Bush14_BushModels,
    .vectors = &Bush14_Effects,
};

EvtScript EVS_SetupBushes = {
    Set(LVar0, Ref(SearchBush_Bush1))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o232, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush2))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o233, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush3))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o234, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush4))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o235, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush5))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o236, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush6))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o237, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush7))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o238, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush8))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o239, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush9))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o240, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush10))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o241, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush11))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o242, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush12))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o243, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush13))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o244, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush14))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o245, 1, 0)
    Return
    End
};
