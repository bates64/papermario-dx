#include "kmr_07.h"
#include "world/area/kmr/kmr_06.h"
#include "world/area/kmr/kmr_12.h"

EvtScript EVS_ExitWalk_kmr_06_1 = EVT_EXIT_WALK(60, $GoombaRoad2, $kmr_06.GoombaRoad3);
EvtScript EVS_ExitWalk_kmr_12_0 = EVT_EXIT_WALK(60, $GoombaRoad4, $kmr_12.GoombaRoad3);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_kmr_06_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    BindTrigger(EVS_ExitWalk_kmr_12_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deili2, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetLoadType, LVar1)
    IfEq(LVar1, LOAD_FROM_FILE_SELECT)
        Exec(EnterSavePoint)
        Exec(EVS_BindExitTriggers)
        Return
    EndIf
    Call(GetEntryID, LVar0)
    IfNe(LVar0, $Entry10.index)
        Set(LVar0, EVS_BindExitTriggers)
        Exec(EnterWalk)
    Else
        Exec(EnterPostPipe)
        Exec(EVS_BindExitTriggers)
    EndIf
    Return
    End
};

EvtScript EVS_Main = {
    Call(MakeNpcs, false, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMusic)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilit1, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilit2, COLLIDER_FLAGS_UPPER_MASK)
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
