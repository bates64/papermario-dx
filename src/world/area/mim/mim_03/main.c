#include "mim_03.h"
#include "world/area/mim/mim_01.h"
#include "world/area/mim/mim_02.h"
#include "world/area/mim/mim_04.h"

#include "../common/SetForeverForestFog.inc.c"

API_CALLABLE(GetPlayerDistFromMapCenter) {
    script->varTable[0] = get_xz_dist_to_player(0.0f, 0.0f);
    return ApiStatus_DONE2;
}

EvtScript EVS_ExitWalk_n = EVT_EXIT_WALK(60, $North, $mim_01.West);
EvtScript EVS_ExitWalk_w = EVT_EXIT_WALK(60, $West, $mim_04.East);
EvtScript EVS_ExitWalk_s = EVT_EXIT_WALK(60, $South, $mim_02.North);
EvtScript EVS_ExitWalk_e = EVT_EXIT_WALK(60, $East, $mim_01.West);

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
    Set(AF_MIM03_ToggleDialogue_Oaklie, false)
    ExecWait(EVS_SetupGates)
    Call(MakeNpcs, true, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    Exec(EVS_SetupMusic)
    ExecWait(EVS_SetupExitHint)
    Call(SetForeverForestFog)
    Thread
        Label(0)
        Call(WaitForCam, CAM_DEFAULT, 1.0)
        Call(GetPlayerDistFromMapCenter)
        IfLt(LVar0, 350)
            Call(SetCamSpeed, CAM_DEFAULT, 1.0)
        Else
            Call(SetCamSpeed, CAM_DEFAULT, 3.0)
        EndIf
        Goto(0)
    EndThread
    Return
    End
};
