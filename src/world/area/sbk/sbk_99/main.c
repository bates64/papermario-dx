#include "sbk_99.h"

extern EvtScript EVS_Main;
extern EvtScript EVS_MakeEntities;

EntryList Entrances = {
    [sbk_99_ENTRY_0]    { -484.0,  100.0,    5.0,   90.0 },
    [sbk_99_ENTRY_1]    {  346.0,    0.0, -342.0,  220.0 },
};

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &Entrances,
    .entryCount = ENTRY_COUNT(Entrances),
    .bgName = "sbk_bg",
    .tattle = { MSG_MapTattle_sbk_99 },
};

EvtScript EVS_ExitWalk_iwa_04_1 = EVT_EXIT_WALK(60, sbk_99_ENTRY_0, "iwa_04", iwa_04_ENTRY_1);
EvtScript EVS_ExitWalk_sbk_30_0 = EVT_EXIT_WALK(60, sbk_99_ENTRY_1, "sbk_30", sbk_30_ENTRY_0);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitWalk_iwa_04_1), TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(Ref(EVS_ExitWalk_sbk_30_0), TRIGGER_FLOOR_ABOVE, COLLIDER_deiline, 1, 0)
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
    Set(LVar0, Ref(EVS_BindExitTriggers))
    Exec(EnterWalk)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_DRY_DRY_DESERT)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Set(GF_MAP_DryDryDesert, true)
    ExecWait(EVS_MakeEntities)
    Call(SetMusic, 0, SONG_MT_RUGGED, 0, VOL_LEVEL_FULL)
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
