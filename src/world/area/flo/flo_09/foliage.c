#include "flo_09.h"

#include "foliage.h"

EvtScript EVS_SpawnBzzap = {
    Call(GetNpcPos, NPC_Bzzap_02, LVar0, LVar1, LVar2)
    IfLt(LVar1, 0)
        Call(GetModelCenter, LVar9)
        Add(LVar2, 35)
        Call(SetNpcPos, NPC_Bzzap_02, LVar0, LVar1, LVar2)
    EndIf
    Return
    End
};

EvtScript EVS_OnShakeTree1 = {
    IfEq(GF_FLO09_Item_HappyFlowerB, false)
        IfEq(AB_FLO_TreePuzzle_SecondCorrect, 1)
            Call(MakeItemEntity, ITEM_HAPPY_FLOWER_B, -250, 100, 0, ITEM_SPAWN_MODE_FALL_NEVER_VANISH, GF_FLO09_Item_HappyFlowerB)
        Else
            Set(LVar9, MODEL_o10)
            Exec(EVS_SpawnBzzap)
        EndIf
        Set(AB_FLO_TreePuzzle_FirstCorrect, 0)
        Set(AB_FLO_TreePuzzle_SecondCorrect, 0)
    EndIf
    Return
    End
};

EvtScript EVS_OnShakeTree2 = {
    IfEq(GF_FLO09_Item_HappyFlowerB, false)
        Set(AB_FLO_TreePuzzle_FirstCorrect, 1)
        Set(AB_FLO_TreePuzzle_SecondCorrect, 0)
    EndIf
    Return
    End
};

EvtScript EVS_OnShakeTree3 = {
    IfEq(GF_FLO09_Item_HappyFlowerB, false)
        IfEq(AB_FLO_TreePuzzle_FirstCorrect, 1)
            IfEq(AB_FLO_TreePuzzle_SecondCorrect, 0)
                Set(AB_FLO_TreePuzzle_SecondCorrect, 1)
                Return
            EndIf
        EndIf
        Set(LVar9, MODEL_o13)
        Exec(EVS_SpawnBzzap)
        Set(AB_FLO_TreePuzzle_FirstCorrect, 0)
        Set(AB_FLO_TreePuzzle_SecondCorrect, 0)
    EndIf
    Return
    End
};

FoliageModelList Tree1_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o11, MODEL_o12);
FoliageModelList Tree1_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o10);

ShakeTreeConfig ShakeTree_Tree1 = {
    .leaves = &Tree1_LeafModels,
    .trunk = &Tree1_TrunkModels,
    .callback = &EVS_OnShakeTree1,
};

BombTrigger BombPos_Tree1 = {
    .pos = { -200.0f, 0.0f, 1.0f },
    .diameter = 0.0f
};

FoliageModelList Tree2_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o4, MODEL_o5);
FoliageModelList Tree2_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o3);

ShakeTreeConfig ShakeTree_Tree2 = {
    .leaves = &Tree2_LeafModels,
    .trunk = &Tree2_TrunkModels,
    .callback = &EVS_OnShakeTree2,
};

BombTrigger BombPos_Tree2 = {
    .pos = { 0.0f, 0.0f, 1.0f },
    .diameter = 0.0f
};

FoliageModelList Tree3_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_o14, MODEL_o15);
FoliageModelList Tree3_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_o13);

ShakeTreeConfig ShakeTree_Tree3 = {
    .leaves = &Tree3_LeafModels,
    .trunk = &Tree3_TrunkModels,
    .callback = &EVS_OnShakeTree3,
};

BombTrigger BombPos_Tree3 = {
    .pos = { 200.0f, 0.0f, 1.0f },
    .diameter = 0.0f
};

EvtScript EVS_SetupFoliage = {
    Set(AB_FLO_TreePuzzle_FirstCorrect, 0)
    Set(AB_FLO_TreePuzzle_SecondCorrect, 0)
    Set(LVar0, Ref(ShakeTree_Tree1))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o10, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree1), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree2))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o3, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree2), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree3))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o13, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree3), 1, 0)
    Return
    End
};
