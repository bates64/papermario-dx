#include "isk_19.h"
#include "world/area/isk/isk_11.h"
#include "world/area/isk/isk_16.h"

EvtScript EVS_ExitWalk_isk_11_3 = EVT_EXIT_WALK(40, $StonePuzzleRoom, $isk_11.BossAntechamber);
EvtScript EVS_ExitWalk_isk_16_0 = EVT_EXIT_WALK(40, $TutankoopaRoom, $isk_16.BossAntechamber);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_isk_11_3, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_isk_16_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
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
    Set(GB_WorldLocation, LOCATION_DRY_DRY_RUINS)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMusic)
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
