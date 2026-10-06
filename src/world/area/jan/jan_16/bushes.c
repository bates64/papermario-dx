#include "jan_16.h"
#include "foliage.h"

FoliageModelList Bush1_BushModels = FOLIAGE_MODEL_LIST(MODEL_o63);

FoliageVectorList Bush1_Effects = {
    .count = 1,
    .vectors = {
        { -273.0f, 17.0f, 390.0f },
    }
};

SearchBushConfig SearchBush_Bush1 = {
    .bush = &Bush1_BushModels,
    .vectors = &Bush1_Effects,
};

FoliageModelList Bush2_BushModels = FOLIAGE_MODEL_LIST(MODEL_o109);

FoliageVectorList Bush2_Effects = {
    .count = 1,
    .vectors = {
        { 181.0f, 16.0f, 222.0f },
    }
};

SearchBushConfig SearchBush_Bush2 = {
    .bush = &Bush2_BushModels,
    .vectors = &Bush2_Effects,
};

FoliageModelList Bush3_BushModels = FOLIAGE_MODEL_LIST(MODEL_o110);

FoliageVectorList Bush3_Effects = {
    .count = 1,
    .vectors = {
        { 308.0f, 17.0f, 223.0f },
    }
};

SearchBushConfig SearchBush_Bush3 = {
    .bush = &Bush3_BushModels,
    .vectors = &Bush3_Effects,
};

FoliageModelList Bush4_BushModels = FOLIAGE_MODEL_LIST(MODEL_o111);

FoliageVectorList Bush4_Effects = {
    .count = 1,
    .vectors = {
        { 461.0f, 19.0f, -59.0f },
    }
};

SearchBushConfig SearchBush_Bush4 = {
    .bush = &Bush4_BushModels,
    .vectors = &Bush4_Effects,
};

EvtScript EVS_SetupBushes = {
    Set(LVar0, Ref(SearchBush_Bush1))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o126, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush2))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o127, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush3))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o128, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush4))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o129, 1, 0)
    Return
    End
};
