#include "kmr_05.h"

#include "foliage.h"

FoliageModelList Tree1_LeafModels = FOLIAGE_MODEL_LIST(MODEL_ha2_1, MODEL_ha2_2, MODEL_ha2_3);
FoliageModelList Tree1_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o1065, MODEL_miki2_1, MODEL_miki2_2);

FoliageVectorList Tree1_Effects = {
    .count = 2,
    .vectors = {
        { 439.0f, 314.0f, -181.0f },
        { 524.0f, 314.0f, -210.0f },
    }
};

EvtScript EVS_OnShakeTree1 = {
    IfEq(GF_KMR05_Tree1_Coin, true)
        Return
    EndIf
    IfEq(MF_Tree1CoinDropped, true)
        Return
    EndIf
    Wait(10)
    Call(GetPlayerPos, LVar0, LVar1, LVar2)
    IfLt(LVar0, 490)
        Call(MakeMarkerEntity, $Item_Coin_1)
    Else
        Call(MakeMarkerEntity, $Item_Coin_2)
    EndIf
    Set(MF_Tree1CoinDropped, true)
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
    .pos = $BombPos_Tree1.pos,
    .diameter = 2.0f * $BombPos_Tree1.radius,
};

EvtScript EVS_SetupFoliage = {
    Set(LVar0, ShakeTree_Tree1)
    BindTrigger(EVS_ShakeTree, TRIGGER_WALL_HAMMER, COLLIDER_o1238, 1, 0)
    BindTrigger(EVS_ShakeTree, TRIGGER_POINT_BOMB, BombPos_Tree1, 1, 0)
    Return
    End
};
