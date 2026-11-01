#include "kpa_114.h"
#include "world/area/kpa/kpa_113.h"
#include "world/area/kpa/kpa_115.h"
#include "sprite.h"

export s32 map_init(void) {
    use_map_geometry("kpa_112");
    return false;
}

EvtScript EVS_ExitWalk_kpa_113_2 = EVT_EXIT_WALK(60, $HiddenDoorRoom2, $kpa_113.HiddenPassage2);
EvtScript EVS_ExitWalk_kpa_115_0 = EVT_EXIT_WALK(40, $HiddenDoorRoom3, $kpa_115.HiddenPassage2);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_kpa_113_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deilis, 1, 0)
    BindTrigger(EVS_ExitWalk_kpa_115_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetLoadType, LVar0)
    IfEq(LVar0, LOAD_FROM_FILE_SELECT)
        Exec(EnterSavePoint)
        Exec(EVS_BindExitTriggers)
        Return
    EndIf
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalkShort)
    Wait(1)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_BOWSERS_CASTLE)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMusic)
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
