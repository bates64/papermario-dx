
#include "tst_01.h"
#include "world/area/mac/machi.h"
#include "world/area/tst/tst_02.h"

extern EvtScript EVS_Main;
extern EvtScript EVS_MakeEntities;

OVL_DEF_MAP() = {
    .main = &EVS_Main,
    .entryList = &$Entries,
    .entryCount = ENTRY_COUNT($Entries),
};

EvtScript EVS_GotoMap_machi_7 = {
    Call(GotoMap, $machi.Entry7)
    Wait(100)
    Return
    End
};

EvtScript EVS_GotoMap_tst_02_0 = {
    Call(GotoMap, $tst_02.JumpWidthTest)
    Wait(100)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_TESTING)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    ExecWait(EVS_MakeEntities)
    BindTrigger(EVS_GotoMap_machi_7, TRIGGER_WALL_PUSH, COLLIDER_deilitw, 1, 0)
    BindTrigger(EVS_GotoMap_tst_02_0, TRIGGER_WALL_PUSH, COLLIDER_deilite, 1, 0)
    Return
    End
};
