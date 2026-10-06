#include "tik_04.h"

#include "world/common/entity/Pipe.inc.c"

EvtScript EVS_ExitWalk_tik_05_0 = EVT_EXIT_WALK(60, tik_04_ENTRY_0, "tik_05", tik_05_ENTRY_0);
EvtScript EVS_ExitWalk_tik_07_0 = EVT_EXIT_WALK(60, tik_04_ENTRY_1, "tik_07", tik_07_ENTRY_0);

EvtScript EVS_GotoMap_tik_03_1 = {
    Call(GotoMap, Ref("tik_03"), tik_03_ENTRY_1)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitPipe_tik_03_1 = EVT_EXIT_PIPE_HORIZONTAL(tik_04_ENTRY_2, COLLIDER_ttd, EVS_GotoMap_tik_03_1);

EvtScript EVS_GotoMap_tik_12_0 = {
    Call(GotoMap, Ref("tik_12"), tik_12_ENTRY_0)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitPipe_tik_12_0 = EVT_EXIT_PIPE_VERTICAL(tik_04_ENTRY_3, COLLIDER_ttd2, EVS_GotoMap_tik_12_0);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitWalk_tik_05_0), TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(Ref(EVS_ExitWalk_tik_07_0), TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    BindTrigger(Ref(EVS_ExitPipe_tik_03_1), TRIGGER_WALL_PUSH, COLLIDER_ttd, 1, 0)
    BindTrigger(Ref(EVS_ExitPipe_tik_12_0), TRIGGER_FLOOR_TOUCH, COLLIDER_ttd2, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_TOAD_TOWN_TUNNELS)
    Call(SetSpriteShading, SHADING_TIK_04)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, true, Ref(DefaultNPCs))
    Exec(EVS_SetupMusic)
    Exec(EVS_SetupDrips)
    // water leaking
    Call(SetTexPanner, MODEL_mizu, TEX_PANNER_2)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_2)
        TEX_PAN_PARAMS_STEP(    0, -200, -100, -500)
        TEX_PAN_PARAMS_FREQ(    1,    1,    1,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Exec(EVS_SetupPlatforms)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(tik_04_ENTRY_2)
            EVT_ENTER_PIPE_HORIZONTAL(COLLIDER_ttd, EVS_BindExitTriggers)
        CaseEq(tik_04_ENTRY_3)
            EVT_ENTER_PIPE_VERTICAL(EVS_BindExitTriggers)
        CaseDefault
            Set(LVar0, Ref(EVS_BindExitTriggers))
            Exec(EnterWalk)
    EndSwitch
    Wait(1)
    Return
    End
};
