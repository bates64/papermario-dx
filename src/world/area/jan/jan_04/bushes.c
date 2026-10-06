#include "jan_04.h"
#include "foliage.h"

FoliageModelList Bush1_BushModels = FOLIAGE_MODEL_LIST(MODEL_o82);

FoliageVectorList Bush1_Effects = {
    .count = 1,
    .vectors = {
        { -400.0f, 20.0f, -120.0f },
    }
};

SearchBushConfig SearchBush_Bush1 = {
    .bush = &Bush1_BushModels,
    .vectors = &Bush1_Effects,
};

FoliageModelList Bush2_BushModels = FOLIAGE_MODEL_LIST(MODEL_o81);

FoliageVectorList Bush2_Effects = {
    .count = 1,
    .vectors = {
        { -353.0f, 22.0f, -81.0f },
    }
};

SearchBushConfig SearchBush_Bush2 = {
    .bush = &Bush2_BushModels,
    .vectors = &Bush2_Effects,
};

FoliageModelList Bush3_BushModels = FOLIAGE_MODEL_LIST(MODEL_o83);

FoliageVectorList Bush3_Effects = {
    .count = 1,
    .vectors = {
        { -264.0f, 20.0f, -402.0f },
    }
};

SearchBushConfig SearchBush_Bush3 = {
    .bush = &Bush3_BushModels,
    .vectors = &Bush3_Effects,
};

FoliageModelList Bush4_BushModels = FOLIAGE_MODEL_LIST(MODEL_o85);

FoliageVectorList Bush4_Effects = {
    .count = 1,
    .vectors = {
        { -211.0f, 22.0f, -420.0f },
    }
};

SearchBushConfig SearchBush_Bush4 = {
    .bush = &Bush4_BushModels,
    .vectors = &Bush4_Effects,
};

FoliageModelList Bush5_BushModels = FOLIAGE_MODEL_LIST(MODEL_o89);

FoliageVectorList Bush5_Effects = {
    .count = 1,
    .vectors = {
        { -111.0f, 22.0f, -62.0f },
    }
};

SearchBushConfig SearchBush_Bush5 = {
    .bush = &Bush5_BushModels,
    .vectors = &Bush5_Effects,
};

FoliageModelList Bush6_BushModels = FOLIAGE_MODEL_LIST(MODEL_o91);

FoliageVectorList Bush6_Effects = {
    .count = 1,
    .vectors = {
        { 258.0f, 20.0f, -286.0f },
    }
};

SearchBushConfig SearchBush_Bush6 = {
    .bush = &Bush6_BushModels,
    .vectors = &Bush6_Effects,
};

FoliageModelList Bush7_BushModels = FOLIAGE_MODEL_LIST(MODEL_o92);

FoliageVectorList Bush7_Effects = {
    .count = 1,
    .vectors = {
        { 315.0f, 20.0f, -289.0f },
    }
};

SearchBushConfig SearchBush_Bush7 = {
    .bush = &Bush7_BushModels,
    .vectors = &Bush7_Effects,
};

FoliageModelList Bush8_BushModels = FOLIAGE_MODEL_LIST(MODEL_o86);

FoliageVectorList Bush8_Effects = {
    .count = 1,
    .vectors = {
        { 284.0f, 20.0f, 181.0f },
    }
};

SearchBushConfig SearchBush_Bush8 = {
    .bush = &Bush8_BushModels,
    .vectors = &Bush8_Effects,
};

FoliageModelList Bush9_BushModels = FOLIAGE_MODEL_LIST(MODEL_o88);

FoliageVectorList Bush9_Effects = {
    .count = 1,
    .vectors = {
        { 378.0f, 22.0f, 185.0f },
    }
};

SearchBushConfig SearchBush_Bush9 = {
    .bush = &Bush9_BushModels,
    .vectors = &Bush9_Effects,
};

FoliageModelList Bush10_BushModels = FOLIAGE_MODEL_LIST(MODEL_o87);

FoliageVectorList Bush10_Effects = {
    .count = 1,
    .vectors = {
        { 435.0f, 20.0f, 205.0f },
    }
};

SearchBushConfig SearchBush_Bush10 = {
    .bush = &Bush10_BushModels,
    .vectors = &Bush10_Effects,
};

EvtScript EVS_SetupBushes = {
    Set(LVar0, Ref(SearchBush_Bush1))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o118, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush2))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o162, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush3))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o119, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush4))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o163, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush5))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o121, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush6))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o122, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush7))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o166, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush8))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o120, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush9))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o164, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush10))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o165, 1, 0)
    Return
    End
};
