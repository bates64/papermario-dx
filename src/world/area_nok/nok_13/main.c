#include "nok_13.h"

#include "world/common/atomic/TexturePan.inc.c"

EvtScript N(EVS_ExitWalk_nok_12_1) = {
    Call(UseExitHeading, 60, nok_13_ENTRY_0)
    Exec(ExitWalk)
    Call(GotoMap, Ref("nok_12"), nok_12_ENTRY_1)
    Wait(100)
    Return
    End
};

EvtScript N(EVS_ExitWalk_nok_01_0) = {
    Call(UseExitHeading, 60, nok_13_ENTRY_1)
    Exec(ExitWalk)
    Call(GotoMap, Ref("nok_01"), nok_01_ENTRY_0)
    Wait(100)
    Return
    End
};

EvtScript N(EVS_ExitWalk_nok_14_0) = {
    Call(UseExitHeading, 60, nok_13_ENTRY_2)
    Exec(ExitWalk)
    Call(GotoMap, Ref("nok_14"), nok_14_ENTRY_0)
    Wait(100)
    Return
    End
};

EvtScript N(EVS_SetupTexPan) = {
    // flowers
    Call(SetTexPanner, MODEL_hana1, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_hana2, TEX_PANNER_0)
    Call(SetTexPanner, MODEL_hanahana, TEX_PANNER_0)
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
    BindTrigger(Ref(N(EVS_ExitWalk_nok_12_1)), TRIGGER_FLOOR_ABOVE, COLLIDER_deili2, 1, 0)
    BindTrigger(Ref(N(EVS_ExitWalk_nok_01_0)), TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    BindTrigger(Ref(N(EVS_ExitWalk_nok_14_0)), TRIGGER_FLOOR_ABOVE, COLLIDER_deili3, 1, 0)
    Return
    End
};

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_PLEASANT_PATH)
    Call(SetSpriteShading, SHADING_NONE)
    SetUP_CAMERA_ALT_NO_LEAD()
    Call(MakeNpcs, false, Ref(N(DefaultNPCs)))
    ExecWait(N(EVS_MakeEntities))
    Exec(N(EVS_SetupTexPan))
    Exec(N(EVS_SetupMusic))
    Exec(N(EVS_SetupMusicalHill))
    Set(LVar0, Ref(N(EVS_BindExitTriggers)))
    Exec(EnterWalk)
    Wait(1)
    Return
    End
};
