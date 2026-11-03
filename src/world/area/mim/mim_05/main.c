#include "mim_05.h"
#include "world/area/mim/mim_01.h"
#include "world/area/mim/mim_04.h"
#include "world/area/mim/mim_06.h"
#include "world/area/mim/mim_08.h"

#include "../common/SetForeverForestFog.inc.c"

EvtScript EVS_ExitWalk_n = EVT_EXIT_WALK(60, $North, $mim_01.West);
EvtScript EVS_ExitWalk_w = EVT_EXIT_WALK(60, $West, $mim_06.East);
EvtScript EVS_ExitWalk_s = EVT_EXIT_WALK(60, $South, $mim_04.North);
EvtScript EVS_ExitWalk_e = EVT_EXIT_WALK(60, $East, $mim_08.West);

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
    Call(SetSpriteShading, $SpriteShading)
    EVT_SETUP_CAMERA_MIM()
    Set(AB_MIM_PrevMapID, GB_MIM_CurrentMapID)
    Call(GetMapID, GB_MIM_CurrentMapID)
    ExecWait(EVS_SetupGates)
    Call(MakeNpcs, true, DefaultNPCs)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    Exec(EVS_SetupMusic)
    ExecWait(EVS_SetupExitHint)
    Call(SetForeverForestFog)
    Call(SetCamSpeed, CAM_DEFAULT, 3.0)
    Return
    End
};
