#include "dgb_02.h"

EvtScript N(EVS_ExitDoors_dgb_03_1) = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(dgb_02_ENTRY_0, "dgb_03", dgb_03_ENTRY_1,
    COLLIDER_deilittw, MODEL_o30, MODEL_o31, DOOR_SOUNDS_CREAKY);

EvtScript N(EVS_ExitDoors_dgb_01_1) = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(dgb_02_ENTRY_1, "dgb_01", dgb_01_ENTRY_1,
    COLLIDER_deilitte, MODEL_o102, MODEL_o101, DOOR_SOUNDS_CREAKY);

EvtScript N(EVS_ExitDoor_dgb_07_0) = EVT_EXIT_SINGLE_DOOR_SET_SOUNDS(dgb_02_ENTRY_2, "dgb_07", dgb_07_ENTRY_0,
    COLLIDER_deilittnw, MODEL_o76, DOOR_SWING_OUT, DOOR_SOUNDS_BASIC);

EvtScript N(EVS_ExitDoor_dgb_11_0) = EVT_EXIT_SINGLE_DOOR_SET_SOUNDS(dgb_02_ENTRY_3, "dgb_11", dgb_11_ENTRY_0,
    COLLIDER_deilittne, MODEL_o123, DOOR_SWING_OUT, DOOR_SOUNDS_BASIC);

EvtScript N(EVS_EnterMap) = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(dgb_02_ENTRY_0)
            Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
            Set(LVar2, MODEL_o30)
            Set(LVar3, MODEL_o31)
            ExecWait(EnterDoubleDoor)
        CaseEq(dgb_02_ENTRY_1)
            Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
            Set(LVar2, MODEL_o102)
            Set(LVar3, MODEL_o101)
            ExecWait(EnterDoubleDoor)
        CaseEq(dgb_02_ENTRY_2)
            Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
            Set(LVar2, MODEL_o76)
            Set(LVar3, DOOR_SWING_OUT)
            ExecWait(EnterSingleDoor)
        CaseEq(dgb_02_ENTRY_3)
            Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
            Set(LVar2, MODEL_o123)
            Set(LVar3, DOOR_SWING_OUT)
            ExecWait(EnterSingleDoor)
    EndSwitch
    Return
    End
};

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_TUBBAS_MANOR)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    IfLt(GB_StoryProgress, STORY_CH3_STAR_SPIRIT_RESCUED)
        Call(MakeNpcs, TRUE, Ref(N(DefaultNPCs)))
    EndIf
    BindTrigger(Ref(N(EVS_ExitDoors_dgb_03_1)), TRIGGER_WALL_PRESS_A, COLLIDER_deilittw, 1, 0)
    BindTrigger(Ref(N(EVS_ExitDoors_dgb_01_1)), TRIGGER_WALL_PRESS_A, COLLIDER_deilitte, 1, 0)
    BindTrigger(Ref(N(EVS_ExitDoor_dgb_07_0)), TRIGGER_WALL_PRESS_A, COLLIDER_deilittnw, 1, 0)
    BindTrigger(Ref(N(EVS_ExitDoor_dgb_11_0)), TRIGGER_WALL_PRESS_A, COLLIDER_deilittne, 1, 0)
    Exec(N(EVS_SetupMusic))
    Exec(N(EVS_EnterMap))
    Return
    End
};
