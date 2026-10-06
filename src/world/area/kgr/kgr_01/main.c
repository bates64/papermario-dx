#include "kgr_01.h"

extern EvtScript EVS_Main;
extern EvtScript EVS_StartTongueWiggle;
extern EvtScript EVS_MonitorFriendlyFire;

EntryList Entrances = {
    [kgr_01_ENTRY_0]    {   -4.0,    8.0,    0.0,   90.0 },
    [kgr_01_ENTRY_1]    {   80.0,    0.0,   10.0,  270.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kgr_01 },
    .sfxReverb = 1,
};

#include "world/common/util/CreateDarkness.inc.c"

EvtScript EVS_ExitWalk_kgr_02_0 = EVT_EXIT_WALK(60, kgr_01_ENTRY_1, "kgr_02", kgr_02_ENTRY_0);
EvtScript EVS_ExitWalk_mac_05_3 = EVT_EXIT_WALK(60, kgr_01_ENTRY_0, "mac_05", mac_05_ENTRY_3);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_kgr_02_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    BindTrigger(EVS_ExitWalk_mac_05_3, TRIGGER_WALL_PUSH, COLLIDER_o50, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_TOAD_TOWN)
    Call(SetSpriteShading, SHADING_NONE)
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
