#include "kmr_04.h"
#include "world/area/kmr/kmr_03.h"

EvtScript EVS_ExitWalk_kmr_03_0 = EVT_EXIT_WALK(60, $CliffBottom, $kmr_03.JrTroopasPlayground);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_kmr_03_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
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
    Set(GB_WorldLocation, LOCATION_GOOMBA_VILLAGE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Set(AF_KMR04_DollyDropped, false)
    Call(MakeNpcs, false, DefaultNPCs)
    Call(ClearDefeatedEnemies)
    ExecWait(EVS_MakeEntities)
    ExecWait(EVS_SetupFoliage)
    Exec(EVS_SetNormalMusic)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilit1, COLLIDER_FLAGS_UPPER_MASK)
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
