#include "sam_04.h"
#include "foliage.h"
#include "effects.h"

EvtScript EVS_ExitWalk_sam_03_1 = EVT_EXIT_WALK(60, sam_04_ENTRY_0, "sam_03", sam_03_ENTRY_1);
EvtScript EVS_ExitWalk_sam_05_0 = EVT_EXIT_WALK(60, sam_04_ENTRY_1, "sam_05", sam_05_ENTRY_0);
EvtScript EVS_ExitWalk_sam_07_0 = EVT_EXIT_WALK(60, sam_04_ENTRY_2, "sam_07", sam_07_ENTRY_0);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitWalk_sam_03_1), TRIGGER_FLOOR_ABOVE, COLLIDER_deilisw, 1, 0)
    BindTrigger(Ref(EVS_ExitWalk_sam_05_0), TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    BindTrigger(Ref(EVS_ExitWalk_sam_07_0), TRIGGER_FLOOR_ABOVE, COLLIDER_deilin, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    IfLt(LVar0, sam_04_ENTRY_3)
        Set(LVar0, Ref(EVS_BindExitTriggers))
        Exec(EnterWalk)
    Else
    EndIf
    Return
    End
};

EvtScript EVS_KnockAwayTreePart = {
    Call(MakeLerp, 0, 255, 20, EASING_QUARTIC_IN)
    Loop(0)
        Call(UpdateLerp)
        Call(TranslateModel, LVar2, 0, LVar0, 0)
        Wait(1)
        IfEq(LVar1, 0)
            BreakLoop
        EndIf
    EndLoop
    Call(EnableModel, LVar2, false)
    Return
    End
};

API_CALLABLE(CheckItemExists) {
    Bytecode* args = script->ptrReadPos;
    s32 itemIdx = evt_get_variable(script, *args++);
    s32 outVar = *args++;
    ItemEntity* itemEntity = get_item_entity(itemIdx);

    evt_set_variable(script, outVar, (s32)itemEntity);
    return ApiStatus_DONE2;
}

EvtScript EVS_TetherItemToDummyNpc = {
    Loop(0)
        Call(GetNpcPos, NPC_LetterDummy, LVar0, LVar1, LVar2)
        Call(CheckItemExists, MV_LetterItemID, LVarA)
        IfEq(LVarA, 0)
            // prevent crash from player picking up the item before it is killed
            BreakLoop
        EndIf
        Call(SetItemPos, MV_LetterItemID, LVar0, LVar1, LVar2)
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript EVS_OnShakeTree2 = {
    Switch(MV_TreeHitCount)
        CaseEq(0)
            Add(MV_TreeHitCount, 1)
            Set(LVar2, MODEL_ki2_1)
            ExecWait(EVS_KnockAwayTreePart)
        CaseEq(1)
            Add(MV_TreeHitCount, 1)
            Set(LVar2, MODEL_ki2_2)
            ExecWait(EVS_KnockAwayTreePart)
        CaseEq(2)
            Add(MV_TreeHitCount, 1)
            Set(LVar2, MODEL_ki2_3)
            ExecWait(EVS_KnockAwayTreePart)
        CaseEq(3)
            IfEq(GF_SAM04_Item_Letter05, false)
                IfEq(MV_DroppedLetter, false)
                    Set(MV_DroppedLetter, true)
                    Call(GetPlayerPos, LVar0, LVar1, LVar2)
                    Call(SetNpcPos, NPC_LetterDummy, -290, 70, 110)
                    ExecGetTID(EVS_TetherItemToDummyNpc, LVarA)
                    IfLe(LVar0, -295)
                        Set(LVar0, -268)
                    Else
                        Set(LVar0, -316)
                    EndIf
                    Call(SetNpcJumpscale, NPC_LetterDummy, Float(2.0))
                    Call(NpcJump0, NPC_LetterDummy, LVar0, 0, 141, 20)
                    KillThread(LVarA)
                    Wait(1)
                    Call(SetNpcPos, NPC_LetterDummy, NPC_DISPOSE_LOCATION)
                EndIf
            EndIf
    EndSwitch
    Return
    End
};

FoliageModelList Tree1_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_ki1);
FoliageModelList Tree1_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_miki1);

ShakeTreeConfig ShakeTree_Tree1 = {
    .leaves = &Tree1_LeafModels,
    .trunk = &Tree1_TrunkModels,
};

BombTrigger BombPos_Tree1 = {
    .pos = { -411.0f, 0.0f, 163.0f },
    .diameter = 0.0f
};

FoliageModelList Tree2_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_miki2);

ShakeTreeConfig ShakeTree_Tree2 = {
    .trunk = &Tree2_TrunkModels,
    .callback = &EVS_OnShakeTree2,
};

FoliageModelList Tree3_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_ki3);
FoliageModelList Tree3_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_miki3);

ShakeTreeConfig ShakeTree_Tree3 = {
    .leaves = &Tree3_LeafModels,
    .trunk = &Tree3_TrunkModels,
};

BombTrigger BombPos_Tree3 = {
    .pos = { 426.0f, 0.0f, -105.0f },
    .diameter = 0.0f
};

FoliageModelList Tree4_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_ki4);
FoliageModelList Tree4_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_miki4);

ShakeTreeConfig ShakeTree_Tree4 = {
    .leaves = &Tree4_LeafModels,
    .trunk = &Tree4_TrunkModels,
};

BombTrigger BombPos_Tree4 = {
    .pos = { 315.0f, 0.0f, -115.0f },
    .diameter = 0.0f
};

FoliageModelList Tree5_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_ki5);
FoliageModelList Tree5_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_mili5);

ShakeTreeConfig ShakeTree_Tree5 = {
    .leaves = &Tree5_LeafModels,
    .trunk = &Tree5_TrunkModels,
};

BombTrigger BombPos_Tree5 = {
    .pos = { 314.0f, 0.0f, -114.0f },
    .diameter = 0.0f
};

FoliageModelList Tree6_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_ki6);
FoliageModelList Tree6_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_miki6);

ShakeTreeConfig ShakeTree_Tree6 = {
    .leaves = &Tree6_LeafModels,
    .trunk = &Tree6_TrunkModels,
};

BombTrigger BombPos_Tree6 = {
    .pos = { -294.0f, 0.0f, -213.0f },
    .diameter = 0.0f
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_SHIVER_SNOWFIELD)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, false, Ref(DefaultNPCs))
    ExecWait(EVS_MakeEntities)
    ExecWait(EVS_SetupMusic)
    PlayEffect(EFFECT_SNOWFALL, 0, 40)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_ground, SURFACE_TYPE_SNOW)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_deilie, SURFACE_TYPE_SNOW)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_deilin, SURFACE_TYPE_SNOW)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_deilisw, SURFACE_TYPE_SNOW)
    ExecWait(EVS_SetupSnowmen)
    Set(LVar0, Ref(ShakeTree_Tree1))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_miki1, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree1), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree2))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_miki2, 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree3))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_miki3, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree3), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree4))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_miki4, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree4), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree5))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_miki5, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree5), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree6))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_miki6, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree6), 1, 0)
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
