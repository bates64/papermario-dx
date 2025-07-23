#include "dgb_17.h"

EvtScript N(EVS_ExitDoors_dgb_15_1) = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(dgb_17_ENTRY_0, "dgb_15", dgb_15_ENTRY_1,
    COLLIDER_deilittw, MODEL_o142, MODEL_o143, DOOR_SOUNDS_CREAKY);

EvtScript N(EVS_ExitDoors_dgb_01_5) = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(dgb_17_ENTRY_1, "dgb_01", dgb_01_ENTRY_5,
    COLLIDER_deilitte, MODEL_o199, MODEL_o198, DOOR_SOUNDS_CREAKY);

EvtScript N(EVS_BindExitTriggers) = {
    BindTrigger(Ref(N(EVS_ExitDoors_dgb_15_1)), TRIGGER_WALL_PRESS_A, COLLIDER_deilittw, 1, 0)
    BindTrigger(Ref(N(EVS_ExitDoors_dgb_01_5)), TRIGGER_WALL_PRESS_A, COLLIDER_deilitte, 1, 0)
    Return
    End
};

EvtScript N(EVS_EnterMap) = {
    Call(GetLoadType, LVar1)
    IfEq(LVar1, LOAD_FROM_FILE_SELECT)
        Exec(EnterSavePoint)
        Exec(N(EVS_BindExitTriggers))
        Return
    EndIf
    Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(dgb_17_ENTRY_0)
            Set(LVar2, MODEL_o142)
            Set(LVar3, MODEL_o143)
            ExecWait(EnterDoubleDoor)
        CaseEq(dgb_17_ENTRY_1)
            Set(LVar2, MODEL_o199)
            Set(LVar3, MODEL_o198)
            ExecWait(EnterDoubleDoor)
    EndSwitch
    Exec(N(EVS_BindExitTriggers))
    Return
    End
};

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_TUBBAS_MANOR)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    ExecWait(N(EVS_MakeEntities))
    Exec(N(EVS_SetupMusic))
    Exec(N(EVS_EnterMap))
    Return
    End
};
