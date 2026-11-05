#include "kmr_05.h"
#include "world/area/kmr/kmr_02.h"
#include "world/area/kmr/kmr_03.h"

EvtScript EVS_ExitWalk_kmr_03_1 = EVT_EXIT_WALK(60, $CliffBottom, $kmr_03.BehindVillage);
EvtScript EVS_ExitWalk_kmr_02_2 = EVT_EXIT_WALK(60, $GoombaVillage, $kmr_02.BehindVillage);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_kmr_03_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    BindTrigger(EVS_ExitWalk_kmr_02_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deili2, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    IfEq(GF_KMR02_ReturnedWithGoompa, false)
        Call(MakeNpcs, false, NpcsBefore)
    Else
        Call(MakeNpcs, false, NpcsAfter)
    EndIf
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMusic)
    ExecWait(EVS_SetupFoliage)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilit1, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilit2, COLLIDER_FLAGS_UPPER_MASK)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    Call(GetEntryID, LVar0)
    IfEq(LVar0, $CliffBottom.index)
        IfEq(GF_KMR05_EnemyWarning, false)
            Exec(EVS_GoompaRemark)
            Set(GF_KMR05_EnemyWarning, true)
        EndIf
    EndIf
    Return
    End
};
