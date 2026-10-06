#include "kpa_04.h"

EvtScript EVS_ExitWalk_kpa_03_1 = EVT_EXIT_WALK(60, kpa_04_ENTRY_0, "kpa_03", kpa_03_ENTRY_1);
EvtScript EVS_ExitWalk_kpa_81_3 = EVT_EXIT_WALK(60, kpa_04_ENTRY_1, "kpa_81", kpa_81_ENTRY_3);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitWalk_kpa_03_1), TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(Ref(EVS_ExitWalk_kpa_81_3), TRIGGER_FLOOR_ABOVE, COLLIDER_deilis, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Set(LVar0, Ref(EVS_BindExitTriggers))
    Exec(EnterWalk)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_BOWSERS_CASTLE)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Exec(EVS_SetupStatues)
    Exec(EVS_EnterMap)
    Wait(1)
    Exec(EVS_SetupMusic)
    Return
    End
};
