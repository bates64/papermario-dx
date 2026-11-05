#include "tst_10.h"
#include "entity.h"

extern EvtScript EVS_Main;
extern EvtScript EVS_MakeEntities;

// note: sets DisablePlayerInput, but does not use EVT_GROUP_EXIT_MAP
EvtScript EVS_ExitWalk_tst_10_2 = {
    Call(DisablePlayerInput, true)
    Call(UseExitHeading, 60, $North.index)
    Exec(ExitWalk)
    Call(GotoMap, $South)
    Wait(100)
    Return
    End
};

// note: sets DisablePlayerInput, but does not use EVT_GROUP_EXIT_MAP
EvtScript EVS_ExitWalk_tst_10_3 = {
    Call(DisablePlayerInput, true)
    Call(UseExitHeading, 60, $West.index)
    Exec(ExitWalk)
    Call(GotoMap, $East)
    Wait(100)
    Return
    End
};

// note: sets DisablePlayerInput, but does not use EVT_GROUP_EXIT_MAP
EvtScript EVS_ExitWalk_tst_10_0 = {
    Call(DisablePlayerInput, true)
    Call(UseExitHeading, 60, $South.index)
    Exec(ExitWalk)
    Call(GotoMap, $North)
    Wait(100)
    Return
    End
};

// note: sets DisablePlayerInput, but does not use EVT_GROUP_EXIT_MAP
EvtScript EVS_ExitWalk_tst_10_1 = {
    Call(DisablePlayerInput, true)
    Call(UseExitHeading, 60, $East.index)
    Exec(ExitWalk)
    Call(GotoMap, $West)
    Wait(100)
    Return
    End
};

EvtScript EVS_DisableExitCameraZones = {
    Call(SetZoneEnabled, ZONE_north, false)
    Call(SetZoneEnabled, ZONE_west,  false)
    Call(SetZoneEnabled, ZONE_south, false)
    Call(SetZoneEnabled, ZONE_east,  false)
    Set(AF_TST10_DisabledExitCameras, false)
    Return
    End
};

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_tst_10_2, TRIGGER_FLOOR_TOUCH, COLLIDER_deilin, 1, 0)
    BindTrigger(EVS_ExitWalk_tst_10_3, TRIGGER_FLOOR_TOUCH, COLLIDER_deiliw, 1, 0)
    BindTrigger(EVS_ExitWalk_tst_10_0, TRIGGER_FLOOR_TOUCH, COLLIDER_deilis, 1, 0)
    BindTrigger(EVS_ExitWalk_tst_10_1, TRIGGER_FLOOR_TOUCH, COLLIDER_deilie, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    ExecWait(EVS_MakeEntities)
    IfEq(AF_TST10_DisabledExitCameras, true)
        Call(SetZoneEnabled, ZONE_north, false)
        Call(SetZoneEnabled, ZONE_west,  false)
        Call(SetZoneEnabled, ZONE_south, false)
        Call(SetZoneEnabled, ZONE_east,  false)
        Set(AF_TST10_DisabledExitCameras, false)
    Else
        Set(AF_TST10_DisabledExitCameras, true)
        BindTrigger(EVS_DisableExitCameraZones, TRIGGER_FLOOR_TOUCH, COLLIDER_change, 1, 0)
    EndIf
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    Return
    End
};

EvtScript EVS_MakeEntities = {
    Call(MakeMarkerEntity, $HeartBlock_1)
    Call(MakeMarkerEntity, $HiddenPanel_1)
    Return
    End
};
