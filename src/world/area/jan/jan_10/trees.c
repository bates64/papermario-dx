#include "jan_10.h"
#include "foliage.h"

API_CALLABLE(IsJungleFuzzyAlive) {
    if (get_enemy_safe(NPC_JungleFuzzy) == nullptr) {
        script->varTable[0] = false;
    } else {
        script->varTable[0] = true;
    }
    return ApiStatus_DONE2;
}

EvtScript EVS_OnShakeTree1 = {
    Wait(15)
    Call(IsJungleFuzzyAlive)
    IfEq(LVar0, true)
        Call(SetNpcVar, NPC_JungleFuzzy, 7, 1)
    EndIf
    Return
    End
};

FoliageModelList Tree1_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o59, MODEL_o60, MODEL_o61, MODEL_o62, MODEL_o63);
FoliageModelList Tree1_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o58);

FoliageVectorList Tree1_Effects = {
    .count = 2,
    .vectors = {
        { -597.0f, 114.0f, 59.0f },
        { -512.0f, 114.0f, 49.0f },
    }
};

ShakeTreeConfig ShakeTree_Tree1 = {
    .leaves = &Tree1_LeafModels,
    .trunk = &Tree1_TrunkModels,
    .vectors = &Tree1_Effects,
    .callback = &EVS_OnShakeTree1,
};

BombTrigger BombPos_Tree1 = {
    .pos = { -557.0f, 0.0f, 29.0f },
    .diameter = 0.0f
};

EvtScript EVS_SetupTrees = {
    Set(LVar0, Ref(ShakeTree_Tree1))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o91, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree1), 1, 0)
    Return
    End
};
