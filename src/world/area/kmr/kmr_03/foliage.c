#include "kmr_03.h"

#include "foliage.h"

FoliageModelList Bush1_BushModels = FOLIAGE_MODEL_LIST(MODEL_km);

FoliageVectorList Bush1_Effects = {
    .count = 1,
    .vectors = {
        { 143.0f, 16.0f, 462.0f },
    }
};

SearchBushConfig SearchBush_Bush1 = {
    .bush = &Bush1_BushModels,
    .vectors = &Bush1_Effects,
};

FoliageModelList Tree1_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_ue);
FoliageModelList Tree1_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_sita);

FoliageVectorList Tree1_Effects = {
    .count = 2,
    .vectors = {
        { -80.0f, 130.0f, 18.0f },
        { 28.0f, 130.0f, 39.0f },
    }
};

EvtScript EVS_OnShakeTree1 = {
    IfEq(GF_KMR03_Tree1_Mushroom, true)
        Return
    EndIf
    IfEq(MF_Tree1_Mushroom, true)
        Return
    EndIf
    Wait(10)
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    IfLt(LVar0, -30)
        Call(MakeItemEntity, ITEM_MUSHROOM, -23, 100, 35, ITEM_SPAWN_MODE_FALL_NEVER_VANISH, GF_KMR03_Tree1_Mushroom)
    Else
        Call(MakeItemEntity, ITEM_MUSHROOM, -85, 100, 16, ITEM_SPAWN_MODE_FALL_NEVER_VANISH, GF_KMR03_Tree1_Mushroom)
    EndIf
    Set(MF_Tree1_Mushroom, true)
    Return
    End
};

ShakeTreeConfig ShakeTree_Tree1 = {
    .leaves = &Tree1_LeafModels,
    .trunk = &Tree1_TrunkModels,
    .vectors = &Tree1_Effects,
    .callback = &EVS_OnShakeTree1,
};

BombTrigger BombPos_Tree1 = {
    .pos = { -42.0f, 0.0f, -13.0f },
    .diameter = 0.0f
};

EvtScript EVS_SetupFoliage = {
    Set(LVar0, Ref(SearchBush_Bush1))
    BindTrigger(Ref(EVS_SearchBush), TRIGGER_WALL_PRESS_A, COLLIDER_km, 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree1))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_ki, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree1), 1, 0)
    Return
    End
};
