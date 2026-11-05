#include "tst_02.h"
#include "world/area/tst/tst_01.h"
#include "world/area/tst/tst_03.h"

extern EvtScript EVS_Main;
extern EvtScript EVS_MakeEntities;

EvtScript EVS_GotoMap_tst_01_1 = {
    Call(GotoMap, $tst_01.JumpHeightTest)
    Wait(100)
    Return
    End
};

EvtScript EVS_GotoMap_tst_03_0 = {
    Call(GotoMap, $tst_03.JumpHeightTest)
    Wait(100)
    Return
    End
};

EvtScript EVS_Main = {
    ExecWait(EVS_MakeEntities)
    BindTrigger(EVS_GotoMap_tst_01_1, TRIGGER_WALL_PUSH, COLLIDER_deilitw, 1, 0)
    BindTrigger(EVS_GotoMap_tst_03_0, TRIGGER_WALL_PUSH, COLLIDER_deilite, 1, 0)
    Return
    End
};
