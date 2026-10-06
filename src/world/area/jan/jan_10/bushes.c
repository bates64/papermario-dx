#include "jan_10.h"
#include "foliage.h"

FoliageModelList Bush1_BushModels = FOLIAGE_MODEL_LIST(MODEL_o29);

FoliageVectorList Bush1_Effects = {
    .count = 1,
    .vectors = {
        { -527.0f, 20.0f, 124.0f },
    }
};

SearchBushConfig SearchBush_Bush1 = {
    .bush = &Bush1_BushModels,
    .vectors = &Bush1_Effects,
};

FoliageModelList Bush2_BushModels = FOLIAGE_MODEL_LIST(MODEL_o30);

FoliageVectorList Bush2_Effects = {
    .count = 1,
    .vectors = {
        { -368.0f, 22.0f, 145.0f },
    }
};

SearchBushConfig SearchBush_Bush2 = {
    .bush = &Bush2_BushModels,
    .vectors = &Bush2_Effects,
};

FoliageModelList Bush3_BushModels = FOLIAGE_MODEL_LIST(MODEL_o37);

FoliageVectorList Bush3_Effects = {
    .count = 1,
    .vectors = {
        { -305.0f, 20.0f, -10.0f },
    }
};

SearchBushConfig SearchBush_Bush3 = {
    .bush = &Bush3_BushModels,
    .vectors = &Bush3_Effects,
};

FoliageModelList Bush4_BushModels = FOLIAGE_MODEL_LIST(MODEL_o38);

FoliageVectorList Bush4_Effects = {
    .count = 1,
    .vectors = {
        { -261.0f, 20.0f, -14.0f },
    }
};

SearchBushConfig SearchBush_Bush4 = {
    .bush = &Bush4_BushModels,
    .vectors = &Bush4_Effects,
};

FoliageModelList Bush5_BushModels = FOLIAGE_MODEL_LIST(MODEL_o33);

FoliageVectorList Bush5_Effects = {
    .count = 1,
    .vectors = {
        { 35.0f, 22.0f, -70.0f },
    }
};

SearchBushConfig SearchBush_Bush5 = {
    .bush = &Bush5_BushModels,
    .vectors = &Bush5_Effects,
};

FoliageModelList Bush6_BushModels = FOLIAGE_MODEL_LIST(MODEL_o34);

FoliageVectorList Bush6_Effects = {
    .count = 1,
    .vectors = {
        { 75.0f, 20.0f, -47.0f },
    }
};

SearchBushConfig SearchBush_Bush6 = {
    .bush = &Bush6_BushModels,
    .vectors = &Bush6_Effects,
};

EvtScript EVS_SetupBushes = {
    Set(LVar0, Ref(SearchBush_Bush1))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o94, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush2))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o95, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush3))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o96, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush4))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o97, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush5))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o98, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush6))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o99, 1, 0)
    Return
    End
};
