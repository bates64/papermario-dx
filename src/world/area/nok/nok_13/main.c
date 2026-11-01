#include "nok_13.h"
#include "world/area/nok/nok_01.h"
#include "world/area/nok/nok_12.h"
#include "world/area/nok/nok_14.h"

EvtScript EVS_ExitWalk_nok_12_1 = EVT_EXIT_WALK(60, $Nok12, $nok_12.Nok13);

EvtScript EVS_ExitWalk_nok_01_0 = EVT_EXIT_WALK(60, $KoopaVillage, $nok_01.PleasantPath);

EvtScript EVS_ExitWalk_nok_14_0 = EVT_EXIT_WALK(60, $Nok14, $nok_14.Nok13);

EvtScript EVS_SetupTexPan = {
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
        Exec(EVS_UpdateTexturePan)
    EndThread
    // water
    Call(SetTexPanner, MODEL_suimen1, TEX_PANNER_1)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_1)
        TEX_PAN_PARAMS_STEP( -100,    0,  600,    0)
        TEX_PAN_PARAMS_FREQ(    1,    0,    1,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Call(SetTexPanner, MODEL_kabemizu1, TEX_PANNER_2)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_2)
        TEX_PAN_PARAMS_STEP( -100,    0,  400,    0)
        TEX_PAN_PARAMS_FREQ(    1,    0,    1,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Return
    End
};

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_nok_12_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deili2, 1, 0)
    BindTrigger(EVS_ExitWalk_nok_01_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    BindTrigger(EVS_ExitWalk_nok_14_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deili3, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_PLEASANT_PATH)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, false, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupTexPan)
    Exec(EVS_SetupMusic)
    Exec(EVS_SetupMusicalHill)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    Return
    End
};
