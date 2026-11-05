#include "sam_10.h"
#include "world/area/pra/pra_01.h"
#include "world/area/sam/sam_09.h"
#include "world/area/sam/sam_12.h"

EvtScript EVS_ExitWalk_sam_09_1 = EVT_EXIT_WALK(60, $MountainTunnel, $sam_09.MountainPeaks);
EvtScript EVS_ExitWalk_pra_01_0 = EVT_EXIT_WALK(60, $CrystalPalace, $pra_01.MountainPeaks);
EvtScript EVS_ExitWalk_sam_12_0 = EVT_EXIT_WALK(60, $MerlarsSanctuary, $sam_12.MountainPeaks);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_sam_09_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_pra_01_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    BindTrigger(EVS_ExitWalk_sam_12_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilia, 1, 0)
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
    IfLt(LVar0, $Entry3.index)
        Set(LVar0, EVS_BindExitTriggers)
        Exec(EnterWalk)
    Else
    EndIf
    Return
    End
};

EvtScript EVS_Main = {
    Call(MakeNpcs, false, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    ExecWait(EVS_SetupMusic)
    ExecWait(EVS_SetupStairs)
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
