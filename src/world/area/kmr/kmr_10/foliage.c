#include "kmr_10.h"

#include "foliage.h"

FoliageModelList Bush1_BushModels = FOLIAGE_MODEL_LIST(MODEL_o1056);

FoliageVectorList Bush1_Effects = {
    .count = 1,
    .vectors = {
        { -305.0f, 163.0f, 3.0f },
    }
};

SearchBushConfig SearchBush_Bush1 = {
    .bush = &Bush1_BushModels,
    .vectors = &Bush1_Effects,
};

FoliageModelList Tree1_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_ha1_1, MODEL_ha1_2, MODEL_ha1_3);
FoliageModelList Tree1_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o1066, MODEL_miki1_1, MODEL_miki1_2);

FoliageVectorList Tree1_Effects = {
    .count = 2,
    .vectors = {
        { 291.0f, 103.0f, -27.0f },
        { 368.0f, 96.0f, -18.0f },
    }
};

ShakeTreeConfig ShakeTree_Tree1 = {
    .leaves = &Tree1_LeafModels,
    .trunk = &Tree1_TrunkModels,
    .vectors = &Tree1_Effects,
    .callback = &EVS_OnShakeTree1,
};

BombTrigger BombPos_Tree1 = {
    .pos = { 328.0f, 10.0f, -36.0f },
    .diameter = 0.0f
};

EvtScript EVS_SetupFoliage = {
    Set(LVar0, Ref(SearchBush_Bush1))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_k1, 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree1))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_ki_a, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree1), 1, 0)
    Return
    End
};
