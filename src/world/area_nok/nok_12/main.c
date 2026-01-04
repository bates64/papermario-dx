#include "nok_12.h"

#include "world/common/atomic/TexturePan.inc.c"

API_CALLABLE(N(UpdateEnounterStages)) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    EncounterStatus* encounterStatus = &gCurrentEncounter;
    Bytecode* args = script->ptrReadPos;
    s32 xMin = evt_get_variable(script, *args++);
    s32 xMax = evt_get_variable(script, *args++);
    s32 zMin = evt_get_variable(script, *args++);
    s32 zMax = evt_get_variable(script, *args++);
    s32 stageWithoutBridge = evt_get_variable(script, *args++);
    s32 stageWithBridge = evt_get_variable(script, *args++);
    s32 stage = stageWithoutBridge;
    s32 i;

    if (xMin <= playerStatus->pos.x && playerStatus->pos.x <= xMax &&
        zMin <= playerStatus->pos.z && playerStatus->pos.z <= zMax)
    {
        stage = stageWithBridge;
    }

    for (i = 0; i < encounterStatus->numEncounters; i++) {
        encounterStatus->encounterList[i]->stage = stage;
    }
    return ApiStatus_DONE2;
}

EvtScript N(EVS_ExitWalk_nok_11_1) = EVT_EXIT_WALK_NOK(60, nok_12_ENTRY_0, "nok_11", nok_11_ENTRY_1);
EvtScript N(EVS_ExitWalk_nok_13_0) = EVT_EXIT_WALK_NOK(60, nok_12_ENTRY_1, "nok_13", nok_13_ENTRY_0);

EvtScript N(EVS_UpdateEnounterStages) = {
    Label(0)
        IfGe(GB_StoryProgress, STORY_CH1_MADE_FIRST_BRIDGE)
            Call(N(UpdateEnounterStages), -380, -170, -100, 999, BTL_NOK_STAGE_00, BTL_NOK_STAGE_02)
        EndIf
        Wait(1)
        Goto(0)
    Return
    End
};

EvtScript N(EVS_SetupTexPan) = {
    // flowers
    Call(SetTexPanner, MODEL_hana1, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_hana2, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_hana3, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_hana4, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_hana5, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_hana6, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_hana7, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_hanahna, TEX_PANNER_0)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_0)
        TEX_PAN_PARAMS_MAX(0x8000)
        TEX_PAN_PARAMS_STEP(0x4000,    0,    0,    0)
        TEX_PAN_PARAMS_FREQ(    12,    0,    0,    0)
        TEX_PAN_PARAMS_INIT(     0,    0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    // water
    Call(SetTexPanner, MODEL_suimen1, TEX_PANNER_1)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_1)
        TEX_PAN_PARAMS_STEP( -100,    0,  600,    0)
        TEX_PAN_PARAMS_FREQ(    1,    0,    1,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    Call(SetTexPanner, MODEL_kabemizu1, TEX_PANNER_2)
    Call(SetTexPanner, MODEL_kabemizu2, TEX_PANNER_2)
    Call(SetTexPanner, MODEL_kabemizu3, TEX_PANNER_2)
    Call(SetTexPanner, MODEL_kabemizu4, TEX_PANNER_2)
    Call(SetTexPanner, MODEL_kabemizu5, TEX_PANNER_2)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_2)
        TEX_PAN_PARAMS_STEP( -100,    0,  400,    0)
        TEX_PAN_PARAMS_FREQ(    1,    0,    1,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    Return
    End
};

EvtScript N(EVS_BindExitTriggers) = {
    BindTrigger(Ref(N(EVS_ExitWalk_nok_11_1)), TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    BindTrigger(Ref(N(EVS_ExitWalk_nok_13_0)), TRIGGER_FLOOR_ABOVE, COLLIDER_deili2, 1, 0)
    Return
    End
};

EvtScript N(EVS_EnterMap) = {
    Set(LVar0, Ref(N(EVS_BindExitTriggers)))
    Exec(EnterWalk)
    Return
    End
};

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_PLEASANT_PATH)
    Call(SetSpriteShading, SHADING_NONE)
    Set(AF_NOK12_HitSwitch, false)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Call(GetDemoState, LVar0)
    IfEq(LVar0, DEMO_STATE_NONE)
        Call(MakeNpcs, false, Ref(N(DefaultNPCs)))
    Else
        Call(GetEntryID, LVar0)
        IfEq(LVar0, nok_12_ENTRY_2)
            Call(MakeNpcs, false, Ref(N(DemoNPCs)))
        EndIf
    EndIf
    ExecWait(N(EVS_MakeEntities))
    ExecWait(N(EVS_SetupFoliage))
    Exec(N(EVS_SetupTexPan))
    Exec(N(EVS_SetupBridge))
    Call(GetDemoState, LVar0)
    IfNe(LVar0, DEMO_STATE_NONE)
        Call(GetEntryID, LVar0)
        IfEq(LVar0, nok_12_ENTRY_2)
            ExecWait(N(EVS_PlayDemoScene1))
        Else
            ExecWait(N(EVS_PlayDemoScene2))
        EndIf
        Return
    EndIf
    Exec(N(EVS_UpdateEnounterStages))
    Exec(N(EVS_SetupMusic))
    Exec(N(EVS_EnterMap))
    Wait(1)
    Set(GF_MAC01_RowfBadgesChosen, false)
    Return
    End
};
