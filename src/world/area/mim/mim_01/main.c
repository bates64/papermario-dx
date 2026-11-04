#include "mim_01.h"
#include "world/area/mim/mim_02.h"
#include "world/area/mim/mim_10.h"

#include "../common/SetForeverForestFog.inc.c"

EvtScript EVS_ExitWalk_n = EVT_EXIT_WALK(60, $North, $West);
EvtScript EVS_ExitWalk_w = EVT_EXIT_WALK(60, $West, $mim_10.ForeverForest);
EvtScript EVS_ExitWalk_s = EVT_EXIT_WALK(60, $South, $West);
EvtScript EVS_ExitWalk_e = EVT_EXIT_WALK(60, $East, $mim_02.West);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_n, TRIGGER_FLOOR_ABOVE, COLLIDER_deilin, 1, 0)
    BindTrigger(EVS_ExitWalk_w, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_s, TRIGGER_FLOOR_ABOVE, COLLIDER_deilis, 1, 0)
    BindTrigger(EVS_ExitWalk_e, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_FOREVER_FOREST)
    EVT_SETUP_CAMERA_MIM()
    Set(GF_MAP_ForeverForest, true)
    Set(AB_MIM_PrevMapID, GB_MIM_CurrentMapID)
    Call(GetMapID, GB_MIM_CurrentMapID)
    ExecWait(EVS_SetupGates)
    Call(MakeNpcs, true, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    ExecWait(EVS_SetupExitHint)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    Call(SetForeverForestFog)
    Exec(EVS_SetupMusic)
    Call(SetCamSpeed, CAM_DEFAULT, 3.0)
    Return
    End
};
