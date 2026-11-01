#include "obk_06.h"
#include "world/area/obk/obk_02.h"

EvtScript EVS_ExitWalk_obk_02_2 = EVT_EXIT_WALK(60, $BasementStairs, $obk_02.Library);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_obk_02_2, TRIGGER_FLOOR_ABOVE, COLLIDER__deili, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($PotRoom.index)
            BindTrigger(EVS_ExitWalk_obk_02_2, TRIGGER_FLOOR_TOUCH, COLLIDER__deili, 1, 0)
        CaseEq($BasementStairs.index)
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_BOOS_MANSION)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupBombables)
    Exec(EVS_SetupMusic)
    Exec(EVS_EnterMap)
    Return
    End
};
