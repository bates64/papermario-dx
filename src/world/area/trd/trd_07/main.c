#include "trd_07.h"

extern EvtScript EVS_SetupMagicDoors;
extern EvtScript EVS_SetupMusic;
extern NpcGroupList DefaultNPCs;

EvtScript EVS_ExitWalk_trd_08_0 = EVT_EXIT_WALK(60, trd_07_ENTRY_1, "trd_08", trd_08_ENTRY_0);
EvtScript EVS_ExitWalk_trd_04_4 = EVT_EXIT_WALK(60, trd_07_ENTRY_0, "trd_04", trd_04_ENTRY_4);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitWalk_trd_08_0), TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(Ref(EVS_ExitWalk_trd_04_4), TRIGGER_FLOOR_ABOVE, COLLIDER_tte, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_KOOPA_BROS_FORTRESS)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, true, Ref(DefaultNPCs))
    Exec(EVS_SetupMusic)
    ExecWait(EVS_SetupMagicDoors)
    Set(LVar0, Ref(EVS_BindExitTriggers))
    ExecGetTID(EnterWalk, MV_EnterWalkScriptID)
    Wait(1)
    Call(SetTexPanner, MODEL_suimen2, TEX_PANNER_1)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_1)
        TEX_PAN_PARAMS_STEP(  100,    0, -100,    0)
        TEX_PAN_PARAMS_FREQ(    1,    0,    1,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Return
    End
};
