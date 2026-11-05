#include "pra_03.h"
#include "world/area/pra/pra_02.h"
#include "world/area/pra/pra_09.h"
#include "world/area/pra/pra_38.h"

EvtScript EVS_ExitDoors_pra_02_1 =
    EVT_EXIT_SINGLE_DOOR($EntryHall, $pra_02.SaveRoom, COLLIDER_deilittnnw, MODEL_o774, DOOR_SWING_IN);

EvtScript EVS_ExitDoors_pra_38_0 =
    EVT_EXIT_DOUBLE_DOOR($BlueKeyHall, $pra_38.SaveRoom, COLLIDER_deilittne, MODEL_o880, MODEL_o878);
EvtScript EVS_ExitDoors_pra_09_0 =
    EVT_EXIT_DOUBLE_DOOR($RedKeyHall, $pra_09.SaveRoom, COLLIDER_deilittnne, MODEL_o989, MODEL_o988);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitDoors_pra_02_1, TRIGGER_WALL_PRESS_A, COLLIDER_deilittnnw, 1, 0)
    BindTrigger(EVS_ExitDoors_pra_38_0, TRIGGER_WALL_PRESS_A, COLLIDER_deilittne, 1, 0)
    BindTrigger(EVS_ExitDoors_pra_09_0, TRIGGER_WALL_PRESS_A, COLLIDER_deilittnne, 1, 0)
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
        CaseEq($EntryHall.index)
            Set(LVar2, MODEL_o774)
            Set(LVar3, DOOR_SWING_IN)
            ExecWait(EnterSingleDoor)
        CaseEq($BlueKeyHall.index)
            Set(LVar2, MODEL_o880)
            Set(LVar3, MODEL_o878)
            ExecWait(EnterDoubleDoor)
        CaseEq($RedKeyHall.index)
            Set(LVar2, MODEL_o989)
            Set(LVar3, MODEL_o988)
            ExecWait(EnterDoubleDoor)
    EndSwitch
    Exec(EVS_BindExitTriggers)
    Return
    End
};

EvtScript EVS_Main = {
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMusic)
    IfEq(GF_PRA04_BoardedFloor, true)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilittn, COLLIDER_FLAGS_UPPER_MASK)
        Call(EnableModel, MODEL_g286, false)
    Else
        Call(EnableModel, MODEL_o998, false)
    EndIf
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
