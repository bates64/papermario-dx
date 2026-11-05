#include "kgr_01.h"
#include "world/area/kgr/kgr_02.h"
#include "world/area/mac/mac_05.h"

extern EvtScript EVS_Main;
extern EvtScript EVS_StartTongueWiggle;
extern EvtScript EVS_MonitorFriendlyFire;

#include "world/common/util/CreateDarkness.inc.c"

EvtScript EVS_ExitWalk_kgr_02_0 = EVT_EXIT_WALK(60, $WhaleStomach, $kgr_02.WhaleMouth);
EvtScript EVS_ExitWalk_mac_05_3 = EVT_EXIT_WALK(60, $PortDistrict, $mac_05.WhaleMouth);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_kgr_02_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    BindTrigger(EVS_ExitWalk_mac_05_3, TRIGGER_WALL_PUSH, COLLIDER_o50, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_TOAD_TOWN)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(HidePlayerShadow, true)
    Call(EnableNpcShadow, NPC_PARTNER, false)
    Exec(EVS_StartTongueWiggle)
    Call(GetEntryID, LVar0)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Exec(EVS_CreateDarkness)
    Exec(EVS_MonitorFriendlyFire)
    Return
    End
};
