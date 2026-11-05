#include "nok_02.h"
#include "world/area/nok/nok_01.h"
#include "world/area/nok/nok_03.h"

#include "world/common/entity/Pipe.inc.c"

EvtScript EVS_ExitWalk_nok_01_1 = EVT_EXIT_WALK(60, $Nok01, $nok_01.Nok02);

EvtScript EVS_ExitWalk_nok_03_0 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    IfEq(GB_KootFavor_State, KOOT_FAVOR_STATE_2)
        Set(GF_KootFavor_LeftKoopaVillage, true)
    EndIf
    Call(UseExitHeading, 60, $Nok03.index)
    Exec(ExitWalk)
    Call(GotoMap, $nok_03.Nok02)
    Wait(100)
    Return
    End
};

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_nok_01_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_nok_03_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilin, 1, 0)
    Return
    End
};

EvtScript EVS_TexPan_Flowers = {
    SetGroup(EVT_GROUP_NEVER_PAUSE)
    Call(SetTexPanner, MODEL_o312, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_o460, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_o461, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_o462, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_o454, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_o455, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_o456, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_o457, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_o458, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_o459, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_o314, TEX_PANNER_0)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_0)
        TEX_PAN_PARAMS_MAX(0x8000)
        TEX_PAN_PARAMS_STEP(0x4000,    0,    0,    0)
        TEX_PAN_PARAMS_FREQ(    12,    0,    0,    0)
        TEX_PAN_PARAMS_INIT(     0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($Pipe.index)
            IfEq(GF_NOK02_WarpPipe, false)
                Call(DisablePlayerInput, true)
                Call(DisablePlayerPhysics, true)
                Call(GetPlayerPos, LVar0, LVar1, LVar2)
                Call(SetNpcPos, NPC_PARTNER, LVar0, LVar1, LVar2)
                Call(SetPlayerPos, LVar0, NPC_DISPOSE_POS_Y, LVar2)
                Wait(30)
                Call(PlaySound, SOUND_GROW)
                Set(GF_NOK02_WarpPipe, true)
                Wait(30)
                Call(SetPlayerActionState, ACTION_STATE_IDLE)
                Call(SetPlayerPos, LVar0, LVar1, LVar2)
                Call(SetNpcPos, NPC_PARTNER, LVar0, LVar1, LVar2)
                Call(DisablePlayerPhysics, false)
                Call(DisablePlayerInput, false)
            EndIf
            Set(LVarA, EVS_BindExitTriggers)
            ExecWait(EVS_Pipe_EnterVertical)
        CaseEq($Entry4.index)
        CaseDefault
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Call(GetEntryID, LVar0)
    IfEq(LVar0, $Entry3.index)
        Call(MakeNpcs, false, EpilogueNPCs)
        ExecWait(EVS_MakeEntities)
        Exec(EVS_TexPan_Flowers)
        Exec(EVS_Scene_Epilogue)
        Call(FadeInMusic, 0, SONG_KOOPA_VILLAGE, 0, 3000, 0, 127)
        Wait(1)
        Return
    EndIf
    Set(AF_NOK02_DeclinedBobombInvite, false)
    Set(AF_NOK02_InsideKoopersHouse, false)
    Set(AF_NOK02_PauseKooperFightSounds, false)
    Set(GF_NOK02_Bush1_KoopaLeaf, false)
    Set(AF_NOK02_FuzzyTreeHit, false)
    IfGe(GB_StoryProgress, STORY_CH1_KOOPER_JOINED_PARTY)
        Set(GF_NOK02_RecoveredShellA, true)
        Set(GF_NOK02_RecoveredShellB, true)
    EndIf
    IfLt(GB_StoryProgress, STORY_CH1_KOOPER_JOINED_PARTY)
        Call(MakeNpcs, false, CrisisNPCs)
    Else
        Call(MakeNpcs, false, NormalNPCs)
    EndIf
    Call(ClearDefeatedEnemies)
    ExecWait(EVS_MakeEntities)
    ExecWait(EVS_SetupFoliage)
    Exec(EVS_TexPan_Flowers)
    BindTrigger(EVS_Setup_Bookshelf, TRIGGER_WALL_PRESS_A, COLLIDER_o236, 1, 0)
    ExecWait(EVS_SetupRooms)
    Call(GetDemoState, LVar0)
    IfNe(LVar0, DEMO_STATE_NONE)
        ExecWait(EVS_SetupDemo)
        Return
    EndIf
    Exec(EVS_SetupMusic)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitw, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitn, COLLIDER_FLAGS_UPPER_MASK)
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
