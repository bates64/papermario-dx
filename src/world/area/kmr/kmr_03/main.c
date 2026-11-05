#include "kmr_03.h"
#include "world/area/kmr/kmr_04.h"
#include "world/area/kmr/kmr_05.h"

EvtScript EVS_ExitWalk_kmr_04_0 = EVT_EXIT_WALK(60, $JrTroopasPlayground, $kmr_04.CliffBottom);
EvtScript EVS_ExitWalk_kmr_05_0 = EVT_EXIT_WALK(60, $BehindVillage, $kmr_05.CliffBottom);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_kmr_04_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    BindTrigger(EVS_ExitWalk_kmr_05_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deili2, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Call(MakeNpcs, false, DefaultNPCs)
    Call(ClearDefeatedEnemies)
    ExecWait(EVS_MakeEntities)
    ExecWait(EVS_SetupFoliage)
    Exec(EVS_SetupMusic)
    Call(GetEntryID, LVar0)
    IfNe(LVar0, $FallFromVillage.index)
        Set(LVar0, EVS_BindExitTriggers)
        Exec(EnterWalk)
    Else
        Exec(EVS_BindExitTriggers)
        Exec(EVS_Scene_FallingDown)
    EndIf
    Wait(1)
    Return
    End
};
