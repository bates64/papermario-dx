#include "kkj_24.h"
#include "world/area/kkj/kkj_23.h"
#include "world/area/kkj/kkj_25.h"

EvtScript EVS_ExitDoors_kkj_23_1 =
    EVT_EXIT_DOUBLE_DOOR($Rooftop, $kkj_23.TowerStaircase, COLLIDER_tte, MODEL_o58, MODEL_o57);
EvtScript EVS_ExitDoors_kkj_25_0 =
    EVT_EXIT_DOUBLE_DOOR($BossArena, $kkj_25.TowerStaircase, COLLIDER_tte2, MODEL_o78, MODEL_o77);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitDoors_kkj_23_1, TRIGGER_WALL_PRESS_A, COLLIDER_tte, 1, 0)
    BindTrigger(EVS_ExitDoors_kkj_25_0, TRIGGER_WALL_PRESS_A, COLLIDER_tte2, 1, 0)
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
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($Rooftop.index)
            Set(LVar2, MODEL_o58)
            Set(LVar3, MODEL_o57)
            ExecWait(EnterDoubleDoor)
        CaseEq($BossArena.index)
            Set(LVar2, MODEL_o78)
            Set(LVar3, MODEL_o77)
            ExecWait(EnterDoubleDoor)
    EndSwitch
    Exec(EVS_BindExitTriggers)
    Return
    End
};

EvtScript EVS_Main = {
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMusic)
    Call(UseDoorSounds, DOOR_SOUNDS_LARGE)
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
