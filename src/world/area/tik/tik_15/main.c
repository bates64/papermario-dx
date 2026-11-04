#include "tik_15.h"
#include "world/area/mac/mac_02.h"
#include "world/area/tik/tik_14.h"

#include "world/common/entity/Pipe.inc.c"

EvtScript EVS_ExitWalk_tik_14_1 = EVT_EXIT_WALK(60, $RipCheatoAntechamber, $tik_14.RipCheatosHome);

EvtScript EVS_GotoMap_mac_02_5 = {
    Call(GotoMap, $mac_02.RipCheatoPipe)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitPipe_mac_02_5 = EVT_EXIT_PIPE_HORIZONTAL($SouthernDistrict, COLLIDER_o59, EVS_GotoMap_mac_02_5);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_tik_14_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    BindTrigger(EVS_ExitPipe_mac_02_5, TRIGGER_WALL_PUSH, COLLIDER_o59, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_TOAD_TOWN_TUNNELS)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, true, DefaultNPCs)
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
    ExecWait(EVS_MakeEntities)
    Call(GetEntryID, LVar0)
    IfEq(LVar0, $SouthernDistrict.index)
        EVT_ENTER_PIPE_HORIZONTAL(COLLIDER_o59, EVS_BindExitTriggers)
    Else
        Set(LVar0, EVS_BindExitTriggers)
        Exec(EnterWalk)
    EndIf
    Wait(1)
    Return
    End
};
