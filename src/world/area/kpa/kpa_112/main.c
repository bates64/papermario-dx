#include "kpa_112.h"
#include "world/area/kpa/kpa_111.h"
#include "world/area/kpa/kpa_113.h"
#include "sprite.h"

EvtScript EVS_ExitWalk_kpa_111_1 = EVT_EXIT_WALK(40, $HiddenDoorRoom1, $kpa_111.HiddenPassage1);
EvtScript EVS_ExitWalk_kpa_113_0 = EVT_EXIT_WALK(40, $HiddenDoorRoom2, $kpa_113.HiddenPassage1);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_kpa_111_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deilis, 1, 0)
    BindTrigger(EVS_ExitWalk_kpa_113_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_BOWSERS_CASTLE)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Exec(EVS_SetupMusic)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    Return
    End
};
