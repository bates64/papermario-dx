#include "sam_11.h"
#include "world/area/sam/sam_02.h"
#include "world/area/sam/sam_03.h"

EvtScript EVS_LoadPondAnimation = {
    Call(LoadAnimatedModel, 0, ShatterPondSkeleton)
    Call(PlayModelAnimation, 0, AS_ShatterPond)
    Call(SetAnimatedModelRootPosition, 0, 0, 0, 0)
    Call(SetAnimatedModelRenderMode, 0, RENDER_MODE_SURFACE_OPA)
    Return
    End
};

#include "foliage.h"

FoliageModelList Tree1_LeafModels = FOLIAGE_MODEL_LIST(MODEL_o558);
FoliageModelList Tree1_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_miki3);

ShakeTreeConfig ShakeTree_Tree1 = {
    .leaves = &Tree1_LeafModels,
    .trunk = &Tree1_TrunkModels,
};

BombTrigger BombPos_Tree1 = {
    .pos = $BombPos_Tree1.pos,
    .diameter = 2.0f * $BombPos_Tree1.radius,
};

FoliageModelList Tree2_LeafModels = FOLIAGE_MODEL_LIST(MODEL_o192);
FoliageModelList Tree2_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_miki4);

ShakeTreeConfig ShakeTree_Tree2 = {
    .leaves = &Tree2_LeafModels,
    .trunk = &Tree2_TrunkModels,
};

BombTrigger BombPos_Tree2 = {
    .pos = $BombPos_Tree2.pos,
    .diameter = 2.0f * $BombPos_Tree2.radius,
};

FoliageModelList Tree3_LeafModels = FOLIAGE_MODEL_LIST(MODEL_o190);
FoliageModelList Tree3_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_miki5);

ShakeTreeConfig ShakeTree_Tree3 = {
    .leaves = &Tree3_LeafModels,
    .trunk = &Tree3_TrunkModels,
};

BombTrigger BombPos_Tree3 = {
    .pos = $BombPos_Tree3.pos,
    .diameter = 2.0f * $BombPos_Tree3.radius,
};

EvtScript EVS_ExitWalk_sam_02_1 = {
    IfEq(MV_ThrownOut, 1)
        Return
    EndIf
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(UseExitHeading, 60, $ShiverCityCenter.index)
    Exec(ExitWalk)
    Call(GotoMap, $sam_02.PondArea)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitWalk_sam_03_0 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    IfLt(GB_StoryProgress, STORY_CH7_MAYOR_MURDER_SOLVED)
        Return
    EndIf
    Set(GF_SAM11_LeftTown, true)
    Call(UseExitHeading, 60, $SnowfieldRoad.index)
    Exec(ExitWalk)
    Call(GotoMap, $sam_03.PondArea)
    Wait(100)
    Return
    End
};

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_sam_02_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_sam_03_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

#include "../common/ManageSnowfall.inc.c"

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_SHIVER_CITY)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(GetEntryID, LVar0)
    IfNe(LVar0, $Epilogue.index)
        Goto(10)
    EndIf
    Call(MakeNpcs, false, EpilogueNPCs)
    Call(FadeInMusic, 0, SONG_SHIVER_CITY, 0, 3000, 0, 127)
    Return
    Label(10)
    Switch(GB_StoryProgress)
        CaseLt(STORY_CH7_MAYOR_MURDER_MYSTERY)
            Call(MakeNpcs, false, BeforeNPCs)
        CaseLt(STORY_CH7_MAYOR_MURDER_SOLVED)
            Call(MakeNpcs, false, MysteryNPCs)
        CaseGe(STORY_CH7_MAYOR_MURDER_SOLVED)
            Call(MakeNpcs, false, AfterNPCs)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o621, COLLIDER_FLAGS_UPPER_MASK)
    EndSwitch
    ExecWait(EVS_MakeEntities)
    Call(SetRenderMode, MODEL_o583, RENDER_MODE_SURFACE_XLU_LAYER2)
    ExecWait(EVS_SetupMusic)
    Exec(EVS_ManageSnowfall)
    ExecWait(EVS_SetupRooms)
    ExecWait(EVS_SetupPond)
    ExecWait(EVS_SetupStaircase)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o595, SURFACE_TYPE_SNOW)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o653, SURFACE_TYPE_SNOW)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o664, SURFACE_TYPE_SNOW)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o677, SURFACE_TYPE_SNOW)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o678, SURFACE_TYPE_SNOW)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_tumori, SURFACE_TYPE_SNOW)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_g_yuki2, SURFACE_TYPE_SNOW)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_suimen, SURFACE_TYPE_SNOW)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_deilie, SURFACE_TYPE_SNOW)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_deiliw, SURFACE_TYPE_SNOW)
    Set(LVar0, ShakeTree_Tree1)
    BindTrigger(EVS_ShakeTree, TRIGGER_POINT_BOMB, BombPos_Tree1, 1, 0)
    Set(LVar0, ShakeTree_Tree2)
    BindTrigger(EVS_ShakeTree, TRIGGER_WALL_HAMMER, COLLIDER_miki4, 1, 0)
    BindTrigger(EVS_ShakeTree, TRIGGER_POINT_BOMB, BombPos_Tree2, 1, 0)
    Set(LVar0, ShakeTree_Tree3)
    BindTrigger(EVS_ShakeTree, TRIGGER_WALL_HAMMER, COLLIDER_miki5, 1, 0)
    BindTrigger(EVS_ShakeTree, TRIGGER_POINT_BOMB, BombPos_Tree3, 1, 0)
    Call(InitAnimatedModels)
    Call(GetEntryID, LVar0)
    IfNe(LVar0, $Epilogue.index)
        Set(LVar0, EVS_BindExitTriggers)
        Exec(EnterWalk)
        Wait(1)
    EndIf
    Return
    End
};
