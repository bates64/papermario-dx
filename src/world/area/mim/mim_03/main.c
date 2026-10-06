#include "mim_03.h"

#include "../common/SetForeverForestFog.inc.c"

API_CALLABLE(GetPlayerDistFromMapCenter) {
    script->varTable[0] = get_xz_dist_to_player(0.0f, 0.0f);
    return ApiStatus_DONE2;
}

EvtScript EVS_ExitWalk_n = EVT_EXIT_WALK(60, mim_03_ENTRY_0, "mim_01", mim_01_ENTRY_1);
EvtScript EVS_ExitWalk_w = EVT_EXIT_WALK(60, mim_03_ENTRY_1, "mim_04", mim_04_ENTRY_3);
EvtScript EVS_ExitWalk_s = EVT_EXIT_WALK(60, mim_03_ENTRY_2, "mim_02", mim_02_ENTRY_0);
EvtScript EVS_ExitWalk_e = EVT_EXIT_WALK(60, mim_03_ENTRY_3, "mim_01", mim_01_ENTRY_1);

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
    Call(SetSpriteShading, SHADING_MIM_03)
    EVT_SETUP_CAMERA_MIM()
    Set(AB_MIM_PrevMapID, GB_MIM_CurrentMapID)
    Call(GetMapID, GB_MIM_CurrentMapID)
    Set(AF_MIM03_ToggleDialogue_Oaklie, false)
    ExecWait(EVS_SetupGates)
    Call(MakeNpcs, true, Ref(DefaultNPCs))
    ExecWait(EVS_MakeEntities)
    Set(LVar0, Ref(EVS_BindExitTriggers))
    Exec(EnterWalk)
    Wait(1)
    Exec(EVS_SetupMusic)
    ExecWait(EVS_SetupExitHint)
    Call(SetForeverForestFog)
    Thread
        Label(0)
        Call(WaitForCam, CAM_DEFAULT, Float(1.0))
        Call(GetPlayerDistFromMapCenter)
        IfLt(LVar0, 350)
            Call(SetCamSpeed, CAM_DEFAULT, Float(1.0))
        Else
            Call(SetCamSpeed, CAM_DEFAULT, Float(3.0))
        EndIf
        Goto(0)
    EndThread
    Return
    End
};
