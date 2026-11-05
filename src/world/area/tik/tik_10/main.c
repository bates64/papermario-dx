#include "tik_10.h"
#include "world/area/tik/tik_09.h"

EvtScript EVS_ExitWalk_tik_09_0 = EVT_EXIT_WALK(60, $WarpZone2, $tik_09.BlockPuzzleRoom);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_tik_09_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMusic)
    Call(PlaySound, SOUND_LOOP_TIK10_WATER)
    Exec(EVS_SetupDrips)
    Call(SetTexPanner, MODEL_nagare, TEX_PANNER_1)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_1)
        TEX_PAN_PARAMS_STEP(   50,  200,  110,  500)
        TEX_PAN_PARAMS_FREQ(    1,    1,    1,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    Return
    End
};
