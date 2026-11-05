
#include "kmr_09.h"
#include "world/area/kmr/kmr_02.h"
#include "world/area/kmr/kmr_06.h"

EvtScript EVS_ExitWalk_kmr_02_0 = EVT_EXIT_WALK(60, $GoombaVillage, $kmr_02.GoombaRoad);
EvtScript EVS_ExitWalk_kmr_06_0 = EVT_EXIT_WALK(60, $GoombaRoad2, $kmr_06.GoombaRoad1);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_kmr_02_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    BindTrigger(EVS_ExitWalk_kmr_06_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deili2, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GF_MAP_GoombaRoad, true)
    Call(MakeNpcs, false, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMusic)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilit1, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilit2, COLLIDER_FLAGS_UPPER_MASK)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    BindTrigger(EVS_OnReadBillboard, TRIGGER_WALL_PRESS_A, COLLIDER_kan, 1, 0)
    Return
    End
};
