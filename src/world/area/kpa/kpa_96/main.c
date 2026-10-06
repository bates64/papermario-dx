#include "kpa_96.h"

EvtScript EVS_ExitDoors_kpa_32_3 = EVT_EXIT_DOUBLE_DOOR(kpa_96_ENTRY_0, "kpa_32", kpa_32_ENTRY_3, COLLIDER_deilittw, MODEL_o881, MODEL_o882);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitDoors_kpa_32_3), TRIGGER_WALL_PRESS_A, COLLIDER_deilittw, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Set(LVar0, kpa_96_ENTRY_0)
    Set(LVar2, MODEL_o881)
    Set(LVar3, MODEL_o882)
    Exec(EnterDoubleDoor)
    Exec(EVS_BindExitTriggers)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_BOWSERS_CASTLE)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, true, Ref(DefaultNPCs))
    Exec(EVS_SetupShop)
    Exec(EVS_EnterMap)
    Wait(1)
    Exec(EVS_SetupMusic)
    Return
    End
};
