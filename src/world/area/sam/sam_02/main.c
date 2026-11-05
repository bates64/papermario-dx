#include "sam_02.h"
#include "world/area/sam/sam_01.h"
#include "world/area/sam/sam_11.h"
#include "world/area/tik/tik_17.h"
#include "sprite/player.h"

#include "world/common/entity/Pipe.inc.c"

#include "foliage.h"

FoliageModelList Tree1_LeafModels = FOLIAGE_MODEL_LIST(MODEL_o494, MODEL_o495);
FoliageModelList Tree1_TrunkModels = FOLIAGE_MODEL_LIST(MODEL_miki2);

ShakeTreeConfig ShakeTree_Tree1 = {
    .leaves = &Tree1_LeafModels,
    .trunk = &Tree1_TrunkModels,
};

BombTrigger BombPos_Tree1 = {
    .pos = $BombPos_Tree1.pos,
    .diameter = 2.0f * $BombPos_Tree1.radius,
};

FoliageModelList Tree2_LeafModels = FOLIAGE_MODEL_LIST(MODEL_o186);

ShakeTreeConfig ShakeTree_Tree2 = {
    .leaves = &Tree2_LeafModels,
};

BombTrigger BombPos_Tree2 = {
    .pos = $BombPos_Tree2.pos,
    .diameter = 2.0f * $BombPos_Tree2.radius,
};

EvtScript EVS_ExitWalk_sam_01_0 = EVT_EXIT_WALK(60, $MayorArea, $sam_01.ShiverCityCenter);
EvtScript EVS_ExitWalk_sam_11_0 = EVT_EXIT_WALK(60, $PondArea, $sam_11.ShiverCityCenter);

EvtScript EVS_GotoMap_tik_17_1 = {
    Call(GotoMap, $tik_17.ShiverCity)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitPipe_tik_17_1 = EVT_EXIT_PIPE_VERTICAL($Pipe, COLLIDER_ttd, EVS_GotoMap_tik_17_1);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_sam_01_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_sam_11_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    IfLt(GB_StoryProgress, STORY_CH7_MAYOR_MURDER_MYSTERY)
        BindTrigger(EVS_ExitPipe_tik_17_1, TRIGGER_FLOOR_TOUCH, COLLIDER_ttd, 1, 0)
    EndIf
    IfGe(GB_StoryProgress, STORY_CH7_MAYOR_MURDER_SOLVED)
        BindTrigger(EVS_ExitPipe_tik_17_1, TRIGGER_FLOOR_TOUCH, COLLIDER_ttd, 1, 0)
    EndIf
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetLoadType, LVar1)
    IfEq(LVar1, LOAD_FROM_FILE_SELECT)
        Exec(EnterSavePoint)
        Exec(EVS_BindExitTriggers)
        Return
    EndIf
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($Pipe.index)
            IfEq(GF_SAM01_Visited, false)
                Set(GF_SAM01_Visited, true)
                Set(GB_StoryProgress, STORY_CH7_ARRIVED_AT_SHIVER_CITY)
            EndIf
            EVT_ENTER_PIPE_VERTICAL(EVS_BindExitTriggers)
            Wait(1)
        CaseEq($ThrownOut.index)
            Call(DisablePlayerInput, true)
            Call(DisablePlayerPhysics, true)
            Call(SetPlayerJumpscale, 1.0)
            Call(SetPlayerPos, 650, 0, 50)
            Wait(1)
            Thread
                Call(PlaySoundAtPlayer, SOUND_FALL_LONG, SOUND_SPACE_DEFAULT)
                Call(SetPlayerAnimation, ANIM_MarioW2_Thrown)
                Call(PlayerJump1, 450, 0, 50, 30)
                Call(PlaySoundAtPlayer, SOUND_TRIP, SOUND_SPACE_DEFAULT)
                Call(PlayerJump1, 440, 0, 50, 5)
                Call(ShakeCam, CAM_DEFAULT, 0, 3, 1.0)
                Wait(30)
                Call(SetPlayerAnimation, ANIM_Mario1_DustOff)
                Wait(7)
                Call(PlaySoundAtPlayer, SOUND_DUST_OFF, SOUND_SPACE_DEFAULT)
                Wait(8)
                Call(PlaySoundAtPlayer, SOUND_DUST_OFF, SOUND_SPACE_DEFAULT)
                Wait(15)
                Call(SetPlayerAnimation, ANIM_Mario1_Idle)
                Wait(1)
                ExecWait(EVS_BindExitTriggers)
                Call(DisablePlayerInput, false)
                Call(DisablePlayerPhysics, false)
            EndThread
        CaseDefault
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
            Wait(1)
    EndSwitch
    Return
    End
};

#include "../common/ManageSnowfall.inc.c"

EvtScript EVS_TexPan_Fire = {
    Call(SetTexPanner, MODEL_hi1, TEX_PANNER_1)
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
    Set(GF_MAP_ShiverCity, true)
    Switch(GB_StoryProgress)
        CaseLt(STORY_CH7_MAYOR_MURDER_MYSTERY)
            Call(MakeNpcs, false, DefaultNPCs)
        CaseLt(STORY_CH7_MAYOR_MURDER_SOLVED)
            Call(MakeNpcs, false, MysteryNPCs)
        CaseGe(STORY_CH7_MAYOR_MURDER_SOLVED)
            Call(MakeNpcs, false, DefaultNPCs)
    EndSwitch
    ExecWait(EVS_MakeEntities)
    ExecWait(EVS_SetupMusic)
    Exec(EVS_ManageSnowfall)
    Exec(EVS_TexPan_Fire)
    ExecWait(EVS_SetupRooms)
    ExecWait(EVS_SetupShop)
    Set(LVar0, ShakeTree_Tree1)
    BindTrigger(EVS_ShakeTree, TRIGGER_WALL_HAMMER, COLLIDER_ki, 1, 0)
    BindTrigger(EVS_ShakeTree, TRIGGER_POINT_BOMB, BombPos_Tree1, 1, 0)
    Set(LVar0, ShakeTree_Tree2)
    BindTrigger(EVS_ShakeTree, TRIGGER_WALL_HAMMER, COLLIDER_o505, 1, 0)
    BindTrigger(EVS_ShakeTree, TRIGGER_POINT_BOMB, BombPos_Tree2, 1, 0)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_kabe, SURFACE_TYPE_SNOW)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_tumori, SURFACE_TYPE_SNOW)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o506, SURFACE_TYPE_SNOW)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o507, SURFACE_TYPE_SNOW)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o508, SURFACE_TYPE_SNOW)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o523, SURFACE_TYPE_SNOW)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_o524, SURFACE_TYPE_SNOW)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_deilie, SURFACE_TYPE_SNOW)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, COLLIDER_deiliw, SURFACE_TYPE_SNOW)
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
