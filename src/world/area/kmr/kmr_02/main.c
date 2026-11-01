#include "kmr_02.h"
#include "world/area/kmr/kmr_00.h"
#include "world/area/kmr/kmr_05.h"
#include "world/area/kmr/kmr_09.h"

#include "world/common/entity/Pipe.inc.c"

EvtScript EVS_ExitWalk_kmr_05_1 = EVT_EXIT_WALK(60, $BehindVillage, $kmr_05.GoombaVillage);
EvtScript EVS_ExitWalk_kmr_00_0 = EVT_EXIT_WALK(60, $ForestClearing, $kmr_00.GoombaVillage);
EvtScript EVS_ExitWalk_kmr_09_0 = EVT_EXIT_WALK(60, $GoombaRoad, $kmr_09.GoombaVillage);

EvtScript EVS_SetupGoombaRoadGate = {
    IfGe(GB_StoryProgress, STORY_CH0_TWINK_GAVE_LUCKY_STAR)
        Call(RotateGroup, MODEL_g197, 120, 0, -1, 0)
        Call(RotateGroup, MODEL_g196, 120, 0, 1, 0)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_tt2, COLLIDER_FLAGS_UPPER_MASK)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_CLEAR_BITS, COLLIDER_o757, COLLIDER_FLAGS_UPPER_MASK)
    EndIf
    Return
    End
};

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_kmr_05_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    BindTrigger(EVS_ExitWalk_kmr_00_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deili2, 1, 0)
    BindTrigger(EVS_ExitWalk_kmr_09_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deili3, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetLoadType, LVar1)
    IfEq(LVar1, LOAD_FROM_FILE_SELECT)
        Exec(EnterSavePoint)
        Exec(EVS_BindExitTriggers)
        Exec(EVS_SetupGoombaRoadGate)
        Return
    EndIf
    Call(GetEntryID, LVar0)
    IfNe(LVar0, $GoombaRoad.index)
        Exec(EVS_SetupGoombaRoadGate)
    EndIf
    Switch(LVar0)
        CaseEq($BehindVillage.index)
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
            IfEq(GF_KMR02_ReturnedWithGoompa, false)
                Call(DisablePlayerInput, true)
                Wait(20 * DT)
                Call(DisablePartnerAI, false)
                Call(SpeakToPlayer, NPC_PARTNER, ANIM_Goompa_Talk, ANIM_Goompa_Idle, 4, MSG_CH0_001C)
                Call(EnablePartnerAI)
                Set(GF_KMR02_ReturnedWithGoompa, true)
                Call(DisablePlayerInput, false)
            EndIf
        CaseEq($WarpPipe.index)
            IfEq(GF_KMR02_WarpPipe, false)
                Call(DisablePlayerInput, true)
                Call(DisablePlayerPhysics, true)
                Call(GetPlayerPos, LVar0, LVar1, LVar2)
                Call(SetNpcPos, NPC_PARTNER, LVar0, LVar1, LVar2)
                Call(SetPlayerPos, LVar0, NPC_DISPOSE_POS_Y, LVar2)
                Wait(30)
                Call(PlaySound, SOUND_GROW)
                Set(GF_KMR02_WarpPipe, true)
                Wait(30)
                Call(SetPlayerActionState, ACTION_STATE_IDLE)
                Call(SetPlayerPos, LVar0, LVar1, LVar2)
                Call(SetNpcPos, NPC_PARTNER, LVar0, LVar1, LVar2)
                Call(DisablePlayerPhysics, false)
                Call(DisablePlayerInput, false)
            EndIf
            Set(LVarA, EVS_BindExitTriggers)
            ExecWait(EVS_Pipe_EnterVertical)
        CaseEq($AfterRevival.index)
            Exec(EVS_SetWallsDown_ToadHouse)
            Exec(EVS_BindExitTriggers)
        CaseEq($Entry10.index)
            // beta entrance for 'post' pipe
            Exec(EnterPostPipe)
            Exec(EVS_BindExitTriggers)
        CaseDefault
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
    EndSwitch
    Return
    End
};

EvtScript EVS_ShowMessage_ItsLocked = {
    Call(DisablePlayerInput, true)
    Call(ShowMessageAtScreenPos, MSG_Menus_00D8, 160, 40)
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript EVS_OpenGoombaRoadGate = {
    Call(DisablePlayerInput, true)
    Call(PlaySoundAtCollider, COLLIDER_tt2, SOUND_GOOMBA_GATE_OPEN, SOUND_SPACE_DEFAULT)
    Call(MakeLerp, 0, 120, 20, EASING_COS_IN_OUT)
    Label(0)
        Call(UpdateLerp)
        Call(RotateGroup, MODEL_g197, LVar0, 0, -1, 0)
        Call(RotateGroup, MODEL_g196, LVar0, 0, 1, 0)
        Wait(1)
        IfEq(LVar1, 1)
            Goto(0)
        EndIf
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_tt2, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_CLEAR_BITS, COLLIDER_o757, COLLIDER_FLAGS_UPPER_MASK)
    Call(DisablePlayerInput, false)
    Return
    End
};

API_CALLABLE(SetMapChangeFadeSlowest) {
    set_map_change_fade_rate(1); // normally 20
    return ApiStatus_DONE2;
}

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_GOOMBA_VILLAGE)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(GetLoadType, LVar0)
    IfEq(LVar0, LOAD_FROM_FILE_SELECT)
        Goto(10)
    EndIf
    // check for cutscene entry
    Call(GetEntryID, LVar0)
    IfNe(LVar0, $Epilogue.index)
        Goto(10)
    EndIf
    Call(MakeNpcs, false, EpilogueNPCs)
    Exec(EVS_FadeOutMusic)
    Return
    Label(10)
    Switch(GB_StoryProgress)
        CaseEq(STORY_UNUSED_FFFFFF8C)
            Call(MakeNpcs, false, NpcGroup1)
        CaseLt(STORY_UNUSED_FFFFFF8C)
            Call(MakeNpcs, false, PrologueNPCs)
        CaseDefault
            Call(MakeNpcs, false, DefaultNPCs)
    EndSwitch
    Label(20)
    Call(ClearDefeatedEnemies)
    ExecWait(EVS_SetupRooms)
    ExecWait(EVS_SetupToadHouse)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMusic)
    ExecWait(EVS_SetupFoliage)
    Switch(GB_StoryProgress)
        CaseLt(STORY_CH0_FELL_OFF_CLIFF)
            BindTrigger(EVS_ShowMessage_ItsLocked, TRIGGER_WALL_PRESS_A, COLLIDER_mm1, 1, 0)
        CaseLt(STORY_CH0_TWINK_GAVE_LUCKY_STAR)
        CaseDefault
            BindTrigger(EVS_OpenGoombaRoadGate, TRIGGER_WALL_PRESS_A, COLLIDER_tt2, 1, 0)
    EndSwitch
    Switch(GB_StoryProgress)
        CaseLt(STORY_CH0_GATE_CRUSHED)
            Call(EnableGroup, MODEL_2, false)
            Call(EnableGroup, MODEL_4, false)
        CaseLt(STORY_CH0_TWINK_GAVE_LUCKY_STAR)
            Call(EnableGroup, MODEL_1, false)
            Call(EnableGroup, MODEL_4, false)
        CaseDefault
            Call(EnableGroup, MODEL_1, false)
            Call(EnableGroup, MODEL_2, false)
    EndSwitch
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o757, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_tt1, COLLIDER_FLAGS_UPPER_MASK)
    Exec(EVS_EnterMap)
    Wait(1)
    IfNe(GB_StoryProgress, STORY_CH0_WAKE_UP)
        Return
    EndIf
    Call(GetEntryID, LVar0)
    IfEq(LVar0, $AfterRevival.index)
        Wait(30)
        Call(SetMapChangeFadeSlowest)
    EndIf
    Return
    End
};
