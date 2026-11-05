#include "sbk_99.h"
#include "world/area/iwa/iwa_04.h"
#include "world/area/sbk/sbk_30.h"

extern EvtScript EVS_Main;
extern EvtScript EVS_MakeEntities;

EvtScript EVS_ExitWalk_iwa_04_1 = EVT_EXIT_WALK(60, $MtRugged, $iwa_04.DryDryDesert);
EvtScript EVS_ExitWalk_sbk_30_0 = EVT_EXIT_WALK(60, $Sbk30, $sbk_30.MtRugged);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_iwa_04_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_sbk_30_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deiline, 1, 0)
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
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GF_MAP_DryDryDesert, true)
    ExecWait(EVS_MakeEntities)
    Call(SetMusic, 0, SONG_MT_RUGGED, 0, VOL_LEVEL_FULL)
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
