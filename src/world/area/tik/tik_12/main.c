#include "tik_12.h"
#include "world/area/tik/tik_04.h"

#include "world/common/entity/Pipe.inc.c"

EvtScript EVS_GotoMap_tik_04_3 = {
    Call(GotoMap, $tik_04.MetalBlockRoom)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitPipe_tik_04_3 = EVT_EXIT_PIPE_HORIZONTAL($ScalesRoom, COLLIDER_o48, EVS_GotoMap_tik_04_3);

EvtScript EVS_BindExitTriggers = {
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_CLEAR_BITS, COLLIDER_o48, COLLIDER_FLAGS_UPPER_MASK)
    BindTrigger(EVS_ExitPipe_tik_04_3, TRIGGER_WALL_PUSH, COLLIDER_o48, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_TOAD_TOWN_TUNNELS)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, true, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMusic)
    Exec(EVS_SetupDrips)
    Call(SetTexPanner, MODEL_mizu, TEX_PANNER_2)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_2)
        TEX_PAN_PARAMS_STEP(    0, -200, -100, -500)
        TEX_PAN_PARAMS_FREQ(    1,    1,    1,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o48, COLLIDER_FLAGS_UPPER_MASK)
    EVT_ENTER_PIPE_HORIZONTAL(COLLIDER_o48, EVS_BindExitTriggers)
    Wait(1)
    Return
    End
};
