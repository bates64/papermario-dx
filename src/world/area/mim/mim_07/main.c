#include "mim_07.h"
#include "world/area/mim/mim_01.h"
#include "world/area/mim/mim_06.h"
#include "world/area/mim/mim_09.h"
#include "world/area/mim/mim_11.h"

#include "../common/SetForeverForestFog.inc.c"

EvtScript EVS_ExitWalk_n = EVT_EXIT_WALK(60, $North, $mim_09.South);
EvtScript EVS_ExitWalk_w = EVT_EXIT_WALK(60, $West, $mim_01.West);
EvtScript EVS_ExitWalk_s = EVT_EXIT_WALK(60, $South, $mim_06.North);
EvtScript EVS_ExitWalk_e = EVT_EXIT_WALK(60, $East, $mim_11.Mim07);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_n, TRIGGER_FLOOR_ABOVE, COLLIDER_deilin, 1, 0)
    BindTrigger(EVS_ExitWalk_w, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_s, TRIGGER_FLOOR_ABOVE, COLLIDER_deilis, 1, 0)
    BindTrigger(EVS_ExitWalk_e, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(AB_MIM_PrevMapID, GB_MIM_CurrentMapID)
    Call(GetMapID, GB_MIM_CurrentMapID)
    ExecWait(EVS_SetupGates)
    Call(MakeNpcs, true, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    Exec(EVS_PlayForestMusic)
    ExecWait(EVS_SetupExitHint)
    Call(SetForeverForestFog)
    Call(GetEntryID, LVar0)
    IfEq(LVar0, $East.index)
        Call(UseSettingsFrom, CAM_DEFAULT, 500, -100, 0)
        Call(SetPanTarget, CAM_DEFAULT, 530, 0, 0)
        Call(SetCamSpeed, CAM_DEFAULT, 90.0)
        Call(PanToTarget, CAM_DEFAULT, 0, true)
        Wait(1)
        Thread
            Call(PanToTarget, CAM_DEFAULT, 0, false)
            Call(SetCamSpeed, CAM_DEFAULT, 3.0)
        EndThread
    Else
        Call(SetCamSpeed, CAM_DEFAULT, 3.0)
    EndIf
    Return
    End
};
