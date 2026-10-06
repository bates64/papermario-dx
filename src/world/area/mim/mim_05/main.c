#include "mim_05.h"

#include "../common/SetForeverForestFog.inc.c"

EvtScript EVS_ExitWalk_n = EVT_EXIT_WALK(60, mim_05_ENTRY_0, "mim_01", mim_01_ENTRY_1);
EvtScript EVS_ExitWalk_w = EVT_EXIT_WALK(60, mim_05_ENTRY_1, "mim_06", mim_06_ENTRY_3);
EvtScript EVS_ExitWalk_s = EVT_EXIT_WALK(60, mim_05_ENTRY_2, "mim_04", mim_04_ENTRY_0);
EvtScript EVS_ExitWalk_e = EVT_EXIT_WALK(60, mim_05_ENTRY_3, "mim_08", mim_08_ENTRY_1);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitWalk_n), TRIGGER_FLOOR_ABOVE, COLLIDER_deilin, 1, 0)
    BindTrigger(Ref(EVS_ExitWalk_w), TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(Ref(EVS_ExitWalk_s), TRIGGER_FLOOR_ABOVE, COLLIDER_deilis, 1, 0)
    BindTrigger(Ref(EVS_ExitWalk_e), TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_FOREVER_FOREST)
    Call(SetSpriteShading, SHADING_MIM_05)
    EVT_SETUP_CAMERA_MIM()
    Set(AB_MIM_PrevMapID, GB_MIM_CurrentMapID)
    Call(GetMapID, GB_MIM_CurrentMapID)
    ExecWait(EVS_SetupGates)
    Call(MakeNpcs, true, Ref(DefaultNPCs))
    Set(LVar0, Ref(EVS_BindExitTriggers))
    Exec(EnterWalk)
    Wait(1)
    Exec(EVS_SetupMusic)
    ExecWait(EVS_SetupExitHint)
    Call(SetForeverForestFog)
    Call(SetCamSpeed, CAM_DEFAULT, Float(3.0))
    Return
    End
};
