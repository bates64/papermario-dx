#include "mim_12.h"
#include "world/area/arn/arn_07.h"
#include "world/area/mim/mim_11.h"

EvtScript EVS_ExitWalk_mim_11_1 = EVT_EXIT_WALK(60, $Mim11, $mim_11.Mim12);
EvtScript EVS_ExitWalk_arn_07_2 = EVT_EXIT_WALK(60, $GustyGulch, $arn_07.ForeverForest);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_mim_11_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_arn_07_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Call(SetNpcPos, NPC_GateBoo_01, NPC_DISPOSE_LOCATION)
    Call(SetNpcPos, NPC_GateBoo_02, NPC_DISPOSE_LOCATION)
    SetF(LVar0, 240.0)
    Loop(20)
        SubF(LVar0, 12.0)
        Call(SetNpcImgFXParams, NPC_GateBoo_01, IMGFX_SET_ALPHA, LVar0, 0, 0, 0)
        Call(SetNpcImgFXParams, NPC_GateBoo_02, IMGFX_SET_ALPHA, LVar0, 0, 0, 0)
        Wait(1)
    EndLoop
    Wait(10)
    Return
    End
};

EvtScript EVS_Main = {
    Call(SetCamPerspective, CAM_DEFAULT, CAM_UPDATE_FROM_ZONE, 25, 16, 1024) // far clip distance closer than normal, further than MIM
    Call(SetCamBGColor, CAM_DEFAULT, 0, 0, 0)
    Call(SetCamEnabled, CAM_DEFAULT, true)
    Call(MakeNpcs, true, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMusic)
    Exec(EVS_SetupForestGate)
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
