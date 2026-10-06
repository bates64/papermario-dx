#include "dgb_15.h"

ITEM_LIST(KeyList, ITEM_TUBBA_CASTLE_KEY);

EvtScript EVS_ExitDoors_dgb_14_1 = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(dgb_15_ENTRY_0, "dgb_14", dgb_14_ENTRY_1,
    COLLIDER_deilittw, MODEL_o135, MODEL_o136, DOOR_SOUNDS_CREAKY);

EvtScript EVS_ExitDoors_dgb_17_0 = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(dgb_15_ENTRY_1, "dgb_17", dgb_17_ENTRY_0,
    COLLIDER_deilitte, MODEL_o102, MODEL_o101, DOOR_SOUNDS_CREAKY);

EvtScript EVS_ExitDoors_dgb_16_0 = EVT_EXIT_SINGLE_DOOR_SET_SOUNDS(dgb_15_ENTRY_2, "dgb_16", dgb_16_ENTRY_0,
    COLLIDER_deilittne, MODEL_o123, DOOR_SWING_OUT, DOOR_SOUNDS_BASIC);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitDoors_dgb_14_1), TRIGGER_WALL_PRESS_A, COLLIDER_deilittw, 1, 0)
    BindTrigger(Ref(EVS_ExitDoors_dgb_16_0), TRIGGER_WALL_PRESS_A, COLLIDER_deilittne, 1, 0)
    IfEq(GF_DGB15_UnlockedUpperFoyer, false)
        BindPadlock(Ref(EVS_UnlockPrompt_Door), TRIGGER_WALL_PRESS_A, EVT_ENTITY_INDEX(0), Ref(KeyList), 0, 1)
    Else
        BindTrigger(Ref(EVS_ExitDoors_dgb_17_0), TRIGGER_WALL_PRESS_A, COLLIDER_deilitte, 1, 0)
    EndIf
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(dgb_15_ENTRY_0)
            Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
            Set(LVar2, MODEL_o135)
            Set(LVar3, MODEL_o136)
            ExecWait(EnterDoubleDoor)
        CaseEq(dgb_15_ENTRY_1)
            Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
            Set(LVar2, MODEL_o102)
            Set(LVar3, MODEL_o101)
            ExecWait(EnterDoubleDoor)
        CaseEq(dgb_15_ENTRY_2)
            Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
            Set(LVar2, MODEL_o123)
            Set(LVar3, DOOR_SWING_OUT)
            ExecWait(EnterSingleDoor)
    EndSwitch
    Exec(EVS_BindExitTriggers)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_TUBBAS_MANOR)
    Call(SetSpriteShading, SHADING_NONE)
    Set(AF_DGB_CloseCallWithTubba, false)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    IfEq(GF_DGB16_EscapedFromTubba, false)
        Call(MakeNpcs, true, Ref(DefaultNPCs))
    EndIf
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMusic)
    Exec(EVS_EnterMap)
    Return
    End
};
