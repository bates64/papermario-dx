#include "kgr_02.h"

extern EvtScript EVS_Main;
extern EvtScript EVS_Dummy;
extern EvtScript EVS_StartTongueWiggle;
extern EvtScript EVS_MonitorFriendlyFire;
extern NpcGroupList DefaultNPCs;

EntryList Entrances = {
    [kgr_02_ENTRY_0]    { -175.0,   10.0,    0.0,   90.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .tattle = { MSG_MapTattle_kgr_02 },
    .sfxReverb = 1,
};

#include "world/common/util/CreateDarkness.inc.c"

EvtScript EVS_ExitWalk_kgr_01_1 = EVT_EXIT_WALK(60, kgr_02_ENTRY_0, "kgr_01", kgr_01_ENTRY_1);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_kgr_01_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_TOAD_TOWN)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, false, Ref(DefaultNPCs))
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Exec(EVS_Dummy)
    Exec(EVS_CreateDarkness)
    Exec(EVS_MonitorFriendlyFire)
    Return
    End
};
