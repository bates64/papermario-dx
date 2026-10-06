#include "mim_11.h"

#include "foliage.h"

FoliageModelList Bush1_BushModels = FOLIAGE_MODEL_LIST(MODEL_o182);

FoliageDropList Bush1_Drops = {
    .count = 1,
    .drops = {
        {
            .itemID = ITEM_STRANGE_LEAF,
            .pos = { 357, 16, 315 },
            .spawnMode = ITEM_SPAWN_MODE_TOSS_NEVER_VANISH,
            .spawnFlag = MF_Drop_Bush1,
        },
    }
};

SearchBushConfig SearchBush_Bush1 = {
    .bush = &Bush1_BushModels,
    .drops = &Bush1_Drops,
};

FoliageModelList Bush2_BushModels = FOLIAGE_MODEL_LIST(MODEL_o183);

SearchBushConfig SearchBush_Bush2 = {
    .bush = &Bush2_BushModels,
};

FoliageModelList Bush3_BushModels = FOLIAGE_MODEL_LIST(MODEL_o184);

SearchBushConfig SearchBush_Bush3 = {
    .bush = &Bush3_BushModels,
};

FoliageModelList Bush4_BushModels = FOLIAGE_MODEL_LIST(MODEL_o185);

SearchBushConfig SearchBush_Bush4 = {
    .bush = &Bush4_BushModels,
};

EvtScript EVS_SetupFoliage = {
    Set(LVar0, Ref(SearchBush_Bush1))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o207, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush2))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o208, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush3))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o209, 1, 0)
    Set(LVar0, Ref(SearchBush_Bush4))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_o210, 1, 0)
    Return
    End
};
