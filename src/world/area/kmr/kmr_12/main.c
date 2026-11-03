#include "kmr_12.h"
#include "world/area/kmr/kmr_07.h"
#include "world/area/kmr/kmr_11.h"

EvtScript EVS_ExitWalk_kmr_07_1 = EVT_EXIT_WALK(60, $GoombaRoad3, $kmr_07.GoombaRoad4);
EvtScript EVS_ExitWalk_kmr_11_0 = EVT_EXIT_WALK(60, $GoombaKingsCastle, $kmr_11.GoombaRoad4);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_kmr_07_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    BindTrigger(EVS_ExitWalk_kmr_11_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deili2, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_GOOMBA_ROAD)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Call(MakeNpcs, false, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMusic)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    BindTrigger(EVS_OnReadBillboard, TRIGGER_WALL_PRESS_A, COLLIDER_o78, 1, 0)
    Return
    End
};
