#include "kmr_06.h"
#include "world/area/kmr/kmr_07.h"
#include "world/area/kmr/kmr_09.h"

EvtScript EVS_ExitWalk_kmr_09_1 = EVT_EXIT_WALK(60, $GoombaRoad1, $kmr_09.GoombaRoad2);
EvtScript EVS_ExitWalk_kmr_07_0 = EVT_EXIT_WALK(60, $GoombaRoad3, $kmr_07.GoombaRoad2);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_kmr_09_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    BindTrigger(EVS_ExitWalk_kmr_07_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deili2, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Call(MakeNpcs, false, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMusic)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilit1, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilit2, COLLIDER_FLAGS_UPPER_MASK)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    ExecWait(EVS_SetupStickerSign)
    Return
    End
};
