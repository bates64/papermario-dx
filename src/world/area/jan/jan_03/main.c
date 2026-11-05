#include "jan_03.h"
#include "world/area/jan/jan_02.h"
#include "world/area/jan/jan_05.h"
#include "world/area/jan/jan_22.h"
#include "effects.h"

#include "world/common/entity/Pipe.inc.c"

EvtScript EVS_ExitWalk_jan_02_1 = EVT_EXIT_WALK(60, $Jan02, $jan_02.Jan03);
EvtScript EVS_ExitWalk_jan_05_0 = EVT_EXIT_WALK(60, $Jan05, $jan_05.YoshisVillage);
EvtScript EVS_ExitWalk_jan_22_0 = EVT_EXIT_WALK(60, $Jan22, $jan_22.YoshisVillage);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_jan_02_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_jan_05_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilinw, 1, 0)
    BindTrigger(EVS_ExitWalk_jan_22_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
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
    IfNe(LVar0, $Pipe.index)
        Set(LVar0, EVS_BindExitTriggers)
        Exec(EnterWalk)
    Else
        IfEq(GF_JAN03_WarpPipe, false)
            Call(DisablePlayerInput, true)
            Call(DisablePlayerPhysics, true)
            Call(GetPlayerPos, LVar0, LVar1, LVar2)
            Call(SetNpcPos, NPC_PARTNER, LVar0, LVar1, LVar2)
            Call(SetPlayerPos, LVar0, NPC_DISPOSE_POS_Y, LVar2)
            Wait(30)
            Call(PlaySound, SOUND_GROW)
            Set(GF_JAN03_WarpPipe, true)
            Wait(30)
            Call(SetPlayerActionState, ACTION_STATE_IDLE)
            Call(SetPlayerPos, LVar0, LVar1, LVar2)
            Call(SetNpcPos, NPC_PARTNER, LVar0, LVar1, LVar2)
            Call(DisablePlayerPhysics, false)
            Call(DisablePlayerInput, false)
        EndIf
        Set(LVarA, EVS_BindExitTriggers)
        ExecWait(EVS_Pipe_EnterVertical)
        Wait(1)
    EndIf
    Return
    End
};

EvtScript EVS_Main = {
    Switch(GB_StoryProgress)
        CaseLt(STORY_CH5_YOSHI_CHILDREN_ARE_MISSING)
            Call(MakeNpcs, false, CrisisNPCs)
        CaseLt(STORY_CH5_ZIP_LINE_READY)
            Call(MakeNpcs, false, ChapterNPCs)
        CaseEq(STORY_CH5_STAR_SPIRIT_DEPARTED)
            Call(MakeNpcs, false, ChapterNPCs)
        CaseGt(STORY_CH5_STAR_SPIRIT_DEPARTED)
            Call(MakeNpcs, false, AfterNPCs)
        CaseDefault
            Call(MakeNpcs, false, DefaultNPCs)
    EndSwitch
    ExecWait(EVS_MakeEntities)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitw, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitnw, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilite, COLLIDER_FLAGS_UPPER_MASK)
    Exec(EVS_EnterMap)
    Wait(1)
    Exec(EVS_SetupMusic)
    Call(PlaySound, SOUND_LOOP_JAN_BEACH_WAVES)
    Exec(EVS_SetupRooms)
    Exec(EVS_SetupFoliage)
    // waves
    Call(SetTexPanner, MODEL_o121, TEX_PANNER_1)
    Call(SetTexPanner, MODEL_o371, TEX_PANNER_1)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_1)
        TEX_PAN_PARAMS_STEP(    0,  400,    0,    0)
        TEX_PAN_PARAMS_FREQ(    0,    1,    0,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    // water surface
    Call(SetTexPanner, MODEL_o119, TEX_PANNER_2)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_2)
        TEX_PAN_PARAMS_STEP( -100,  200,    0,    0)
        TEX_PAN_PARAMS_FREQ(    1,    1,    0,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Call(SetModelFlags, MODEL_o189, MODEL_FLAG_BILLBOARD, true)
    Call(SetModelFlags, MODEL_o186, MODEL_FLAG_BILLBOARD, true)
    Call(SetModelFlags, MODEL_o192, MODEL_FLAG_BILLBOARD, true)
    Call(SetModelFlags, MODEL_o195, MODEL_FLAG_BILLBOARD, true)
    Exec(EVS_SetupShop)
    Return
    End
};
