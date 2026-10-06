#include "sam_06.h"
#include "effects.h"

#include "foliage.h"

FoliageModelList Tree1_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_ki2);
FoliageModelList Tree1_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_miki2);

ShakeTreeConfig ShakeTree_Tree1 = {
    .leaves = &Tree1_LeafModels,
    .trunk = &Tree1_TrunkModels,
};

BombTrigger BombPos_Tree1 = {
    .pos = { -185.0f, 90.0f, -225.0f },
    .diameter = 0.0f
};

FoliageModelList Tree2_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_ki3);
FoliageModelList Tree2_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_miki3);

ShakeTreeConfig ShakeTree_Tree2 = {
    .leaves = &Tree2_LeafModels,
    .trunk = &Tree2_TrunkModels,
};

BombTrigger BombPos_Tree2 = {
    .pos = { -451.0f, 60.0f, 80.0f },
    .diameter = 0.0f
};

FoliageModelList Tree3_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_ki5b);
FoliageModelList Tree3_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_muki5);

ShakeTreeConfig ShakeTree_Tree3 = {
    .leaves = &Tree3_LeafModels,
    .trunk = &Tree3_TrunkModels,
};

BombTrigger BombPos_Tree3 = {
    .pos = { -405.0f, 0.0f, 228.0f },
    .diameter = 0.0f
};

FoliageModelList Tree4_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_ki6b);
FoliageModelList Tree4_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_miki6);

ShakeTreeConfig ShakeTree_Tree4 = {
    .leaves = &Tree4_LeafModels,
    .trunk = &Tree4_TrunkModels,
};

BombTrigger BombPos_Tree4 = {
    .pos = { 291.0f, 0.0f, 385.0f },
    .diameter = 0.0f
};

FoliageModelList Tree5_LeafModels  = FOLIAGE_MODEL_LIST(MODEL_ki10);
FoliageModelList Tree5_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_miki10);

ShakeTreeConfig ShakeTree_Tree5 = {
    .leaves = &Tree5_LeafModels,
    .trunk = &Tree5_TrunkModels,
};

BombTrigger BombPos_Tree5 = {
    .pos = { 108.0f, 83.0f, 115.0f },
    .diameter = 0.0f
};

EvtScript EVS_ExitWalk_sam_05_1 = EVT_EXIT_WALK(60, sam_06_ENTRY_0, "sam_05", sam_05_ENTRY_1);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitWalk_sam_05_1), TRIGGER_FLOOR_ABOVE, COLLIDER_deilisw, 1, 0)
    Return
    End
};

#include "../common/ManageSnowfall.inc.c"

EvtScript EVS_TexPan_Fire = {
    Call(SetTexPanner, MODEL_hi1, TEX_PANNER_1)
    Call(SetTexPanner, MODEL_hi2, TEX_PANNER_1)
    Call(SetTexPanner, MODEL_hi3, TEX_PANNER_1)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_1)
        TEX_PAN_PARAMS_STEP(   50,   50,  -70,  300)
        TEX_PAN_PARAMS_FREQ(    1,    1,    1,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_STARBORN_VALLEY)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Set(GF_MAP_StarbornValley, true)
    Call(MakeNpcs, false, Ref(DefaultNPCs))
    Call(ClearDefeatedEnemies)
    ExecWait(EVS_MakeEntities)
    ExecWait(EVS_SetupMusic)
    Exec(EVS_ManageSnowfall)
    Exec(EVS_TexPan_Fire)
    ExecWait(EVS_SetupRooms)
    Call(SetRenderMode, MODEL_h_yuki2, RENDER_MODE_SURFACE_XLU_ZB_ZUPD)
    Call(SetRenderMode, MODEL_khm_y2, RENDER_MODE_SURFACE_XLU_ZB_ZUPD)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_ground, SURFACE_TYPE_SNOW)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_deilisw, SURFACE_TYPE_SNOW)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_kabe, SURFACE_TYPE_SNOW)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o262, SURFACE_TYPE_SNOW)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o263, SURFACE_TYPE_SNOW)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o264, SURFACE_TYPE_SNOW)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o265, SURFACE_TYPE_SNOW)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o266, SURFACE_TYPE_SNOW)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o267, SURFACE_TYPE_SNOW)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o268, SURFACE_TYPE_SNOW)
    Set(LVar0, Ref(ShakeTree_Tree1))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree1), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree2))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree2), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree3))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree3), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree4))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree4), 1, 0)
    Set(LVar0, Ref(ShakeTree_Tree5))
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_WALL_HAMMER, COLLIDER_o225, 1, 0)
    BindTrigger(Ref(EVS_ShakeTree), TRIGGER_POINT_BOMB, Ref(BombPos_Tree5), 1, 0)
    Call(GetLoadType, LVar1)
    IfEq(LVar1, LOAD_FROM_FILE_SELECT)
        Exec(EnterSavePoint)
        Exec(EVS_BindExitTriggers)
        Wait(1)
    Else
        Set(LVar0, Ref(EVS_BindExitTriggers))
        Exec(EnterWalk)
        Wait(1)
    EndIf
    Thread
        Set(LVar2, 0)
        Label(0)
            Call(MakeLerp, 100, 90, 5, EASING_LINEAR)
            Label(1)
                Call(UpdateLerp)
                MulF(LVar0, Float(0.01))
                Add(LVar2, 8)
                Mod(LVar2, 360)
                Wait(1)
                IfEq(LVar1, 1)
                    Goto(1)
                EndIf
            Call(MakeLerp, 90, 100, 5, EASING_LINEAR)
            Label(2)
                Call(UpdateLerp)
                MulF(LVar0, Float(0.01))
                Add(LVar2, 8)
                Mod(LVar2, 360)
                Wait(1)
                IfEq(LVar1, 1)
                    Goto(2)
                EndIf
            Goto(0)
    EndThread
    Return
    End
};
