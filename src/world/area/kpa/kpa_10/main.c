#include "kpa_10.h"
#include "world/area/kpa/kpa_12.h"
#include "world/area/kpa/kpa_17.h"
#include "world/area/kpa/kpa_62.h"

EvtScript EVS_ExitWalk_kpa_62_1 = EVT_EXIT_WALK(60, $FrontDoorUpper, $kpa_62.OutsideJailUpper);
EvtScript EVS_ExitWalk_kpa_12_0 = EVT_EXIT_WALK(60, $LavaChannel1Upper, $kpa_12.OutsideJailUpper);
EvtScript EVS_ExitWalk_kpa_17_1 = EVT_EXIT_WALK(60, $LowerJail, $kpa_17.OutsideJail);
EvtScript EVS_ExitWalk_kpa_62_2 = EVT_EXIT_WALK(60, $FrontDoorLower, $kpa_62.OutsideJailLower);
EvtScript EVS_ExitWalk_kpa_12_2 = EVT_EXIT_WALK(60, $LavaChannel1Lower, $kpa_12.OutsideJailLower);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_kpa_62_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_kpa_12_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    BindTrigger(EVS_ExitWalk_kpa_17_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiline, 1, 0)
    BindTrigger(EVS_ExitWalk_kpa_62_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deilisw, 1, 0)
    BindTrigger(EVS_ExitWalk_kpa_12_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deilise, 1, 0)
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
    Exec(EnterWalk)
    Wait(1)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_BOWSERS_CASTLE)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Call(MakeNpcs, true, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_EnterMap)
    Wait(1)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilittne, COLLIDER_FLAGS_UPPER_MASK)
    Exec(EVS_SetupMusic)
    Return
    End
};
