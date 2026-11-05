#include "pra_10.h"
#include "world/area/pra/pra_04.h"
#include "world/area/pra/pra_12.h"

#include "../common/Reflection.inc.c"
#include "../common/Reflection.data.inc.c"

EvtScript EVS_ExitDoors_pra_04_2 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Set(LVar0, $ReflectedSaveRoom.index)
    Set(LVar1, COLLIDER_deilittsw)
    Set(LVar2, MODEL_o772)
    Set(LVar3, MODEL_o768)
    Set(LVar4, MODEL_o844)
    Set(LVar5, MODEL_o846)
    Exec(ExitSplitDoubleDoor)
    Wait(17)
    Call(GotoMap, $pra_04.PDownDUpHall)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitDoors_pra_12_0 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Set(LVar0, $PDownDUpRoom.index)
    Set(LVar1, COLLIDER_deilittse)
    Set(LVar2, MODEL_o1019)
    Set(LVar3, MODEL_o1021)
    Set(LVar4, MODEL_o1020)
    Set(LVar5, MODEL_o1022)
    Exec(ExitSplitDoubleDoor)
    Wait(17)
    Call(GotoMap, $pra_12.PDownDUpHall)
    Wait(100)
    Return
    End
};

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitDoors_pra_04_2, TRIGGER_WALL_PRESS_A, COLLIDER_deilittsw, 1, 0)
    BindTrigger(EVS_ExitDoors_pra_12_0, TRIGGER_WALL_PRESS_A, COLLIDER_deilittse, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($ReflectedSaveRoom.index)
            Set(LVar2, MODEL_o772)
            Set(LVar3, MODEL_o768)
            Set(LVar4, MODEL_o844)
            Set(LVar5, MODEL_o846)
            ExecWait(EnterSplitDoubleDoor)
        CaseEq($PDownDUpRoom.index)
            Set(LVar2, MODEL_o1019)
            Set(LVar3, MODEL_o1021)
            Set(LVar4, MODEL_o1020)
            Set(LVar5, MODEL_o1022)
            ExecWait(EnterSplitDoubleDoor)
    EndSwitch
    Exec(EVS_BindExitTriggers)
    Return
    End
};

EvtScript EVS_Main = {
    Call(MakeNpcs, true, DefaultNPCs)
    Exec(EVS_SetupMusic)
    Set(LVar0, REFLECTION_FLOOR_ONLY)
    Set(LVar1, GF_PRA_BrokeIllusion)
    Exec(EVS_SetupReflections)
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
