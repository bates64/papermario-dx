#include "dgb_17.h"
#include "world/area/dgb/dgb_01.h"
#include "world/area/dgb/dgb_15.h"

EvtScript EVS_ExitDoors_dgb_15_1 = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(
    $Dgb15, $dgb_15.Dgb17, COLLIDER_deilittw, MODEL_o142, MODEL_o143, DOOR_SOUNDS_CREAKY
);

EvtScript EVS_ExitDoors_dgb_01_5 = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(
    $Dgb01, $dgb_01.Dgb17, COLLIDER_deilitte, MODEL_o199, MODEL_o198, DOOR_SOUNDS_CREAKY
);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitDoors_dgb_15_1, TRIGGER_WALL_PRESS_A, COLLIDER_deilittw, 1, 0)
    BindTrigger(EVS_ExitDoors_dgb_01_5, TRIGGER_WALL_PRESS_A, COLLIDER_deilitte, 1, 0)
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
    Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($Dgb15.index)
            Set(LVar2, MODEL_o142)
            Set(LVar3, MODEL_o143)
            ExecWait(EnterDoubleDoor)
        CaseEq($Dgb01.index)
            Set(LVar2, MODEL_o199)
            Set(LVar3, MODEL_o198)
            ExecWait(EnterDoubleDoor)
    EndSwitch
    Exec(EVS_BindExitTriggers)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_TUBBAS_MANOR)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMusic)
    Exec(EVS_EnterMap)
    Return
    End
};
