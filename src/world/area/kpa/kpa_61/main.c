#include "kpa_61.h"

EvtScript EVS_ExitDoors_kpa_82_1 = EVT_EXIT_DOUBLE_DOOR(kpa_61_ENTRY_0, "kpa_82", kpa_82_ENTRY_1, COLLIDER_tts, MODEL_o34, MODEL_o33);
EvtScript EVS_ExitDoors_kpa_33_1 = EVT_EXIT_DOUBLE_DOOR(kpa_61_ENTRY_1, "kpa_33", kpa_33_ENTRY_1, COLLIDER_ttsw, MODEL_o37, MODEL_o38);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitDoors_kpa_82_1), TRIGGER_WALL_PRESS_A, COLLIDER_tts, 1, 0)
    BindTrigger(Ref(EVS_ExitDoors_kpa_33_1), TRIGGER_WALL_PRESS_A, COLLIDER_ttsw, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(kpa_61_ENTRY_0)
            Set(LVar0, kpa_61_ENTRY_0)
            Set(LVar2, MODEL_o34)
            Set(LVar3, MODEL_o33)
            Exec(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq(kpa_61_ENTRY_1)
            Set(LVar0, kpa_61_ENTRY_1)
            Set(LVar2, MODEL_o37)
            Set(LVar3, MODEL_o38)
            Exec(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
    EndSwitch
    Return
    End
};

EvtScript EVS_TexPan_Clouds = {
    Call(SetTexPanner, MODEL_kumo1, TEX_PANNER_1)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_1)
        TEX_PAN_PARAMS_STEP(  -90,    0,    0,    0)
        TEX_PAN_PARAMS_FREQ(    1,    1,    1,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Call(SetTexPanner, MODEL_kumo2, TEX_PANNER_2)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_2)
        TEX_PAN_PARAMS_STEP( -130,    0,    0,    0)
        TEX_PAN_PARAMS_FREQ(    1,    1,    1,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Call(SetTexPanner, MODEL_kumo3, TEX_PANNER_3)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_3)
        TEX_PAN_PARAMS_STEP( -120,    0,    0,    0)
        TEX_PAN_PARAMS_FREQ(    1,    1,    1,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Call(SetTexPanner, MODEL_kumo4, TEX_PANNER_4)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_4)
        TEX_PAN_PARAMS_STEP(  -70,    0,    0,    0)
        TEX_PAN_PARAMS_FREQ(    1,    1,    1,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_BOWSERS_CASTLE)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Call(MakeNpcs, true, Ref(DefaultNPCs))
    ExecWait(EVS_MakeEntities)
    Exec(EVS_EnterMap)
    Wait(1)
    Exec(EVS_TexPan_Clouds)
    Exec(EVS_SetupMusic)
    Return
    End
};
