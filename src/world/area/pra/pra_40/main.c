#include "pra_40.h"

#include "../common/Reflection.inc.c"
#include "../common/Reflection.data.inc.c"

EvtScript EVS_ExitDoors_pra_31_1 = EVT_EXIT_DOUBLE_DOOR(pra_40_ENTRY_0, "pra_31", pra_31_ENTRY_1, COLLIDER_deilitt1, MODEL_o1055, MODEL_o1053);
EvtScript EVS_ExitDoors_pra_32_0 = EVT_EXIT_DOUBLE_DOOR(pra_40_ENTRY_1, "pra_32", pra_32_ENTRY_0, COLLIDER_deilitt2, MODEL_o880, MODEL_o878);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitDoors_pra_31_1), TRIGGER_WALL_PRESS_A, COLLIDER_deilitt1, 1, 0)
    BindTrigger(Ref(EVS_ExitDoors_pra_32_0), TRIGGER_WALL_PRESS_A, COLLIDER_deilitt2, 1, 0)
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
        CaseEq(pra_40_ENTRY_0)
            Set(LVar2, MODEL_o1055)
            Set(LVar3, MODEL_o1053)
            ExecWait(EnterDoubleDoor)
        CaseEq(pra_40_ENTRY_1)
            Set(LVar2, MODEL_o880)
            Set(LVar3, MODEL_o878)
            ExecWait(EnterDoubleDoor)
    EndSwitch
    Exec(EVS_BindExitTriggers)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_CRYSTAL_PALACE)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(24, 24, 40)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMusic)
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
