#include "hos_03.h"
#include "foliage.h"

FoliageModelList Tree1_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o37, MODEL_o38, MODEL_o39);
FoliageModelList Tree1_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o32, MODEL_o35, MODEL_o36);

FoliageVectorList Tree1_Effects = {
    .count = 2,
    .vectors = {
        { -669.0f, 60.0f, 296.0f },
        { -584.0f, 60.0f, 286.0f },
    }
};

ShakeTreeConfig ShakeTree_Tree1 = {
    .leaves = &Tree1_LeafModels,
    .trunk = &Tree1_TrunkModels,
    .vectors = &Tree1_Effects,
    .type = TREE_TYPE_SPARKLY,
};

BombTrigger BombPos_Tree1 = {
    .pos = { -629.0f, 35.0f, 296.0f },
    .diameter = 0.0f
};

FoliageModelList Tree2_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o43, MODEL_o44, MODEL_o45);
FoliageModelList Tree2_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o40, MODEL_o41, MODEL_o42);

FoliageVectorList Tree2_Effects = {
    .count = 2,
    .vectors = {
        { -528.0f, 60.0f, 324.0f },
        { -443.0f, 60.0f, 314.0f },
    }
};

ShakeTreeConfig ShakeTree_Tree2 = {
    .leaves = &Tree2_LeafModels,
    .trunk = &Tree2_TrunkModels,
    .vectors = &Tree2_Effects,
    .type = TREE_TYPE_SPARKLY,
};

BombTrigger BombPos_Tree2 = {
    .pos = { -488.0f, 35.0f, 324.0f },
    .diameter = 0.0f
};

EvtScript EVS_SetupFoliage = {
    Set(LVar0, Ref(ShakeTree_Tree1))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o35, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree1), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree2))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o32, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree2), 1, 0)
    Return
    End
};
