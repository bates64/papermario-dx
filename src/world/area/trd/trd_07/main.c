#include "trd_07.h"
#include "world/area/trd/trd_04.h"
#include "world/area/trd/trd_08.h"

extern EvtScript EVS_SetupMagicDoors;
extern EvtScript EVS_SetupMusic;
extern NpcGroupList DefaultNPCs;

EvtScript EVS_ExitWalk_trd_08_0 = EVT_EXIT_WALK(60, $Trd08, $trd_08.Trd07);
EvtScript EVS_ExitWalk_trd_04_4 = EVT_EXIT_WALK(60, $Trd04, $trd_04.Trd07);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_trd_08_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_trd_04_4, TRIGGER_FLOOR_ABOVE, COLLIDER_tte, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_KOOPA_BROS_FORTRESS)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, true, DefaultNPCs)
    Exec(EVS_SetupMusic)
    ExecWait(EVS_SetupMagicDoors)
    Set(LVar0, EVS_BindExitTriggers)
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
