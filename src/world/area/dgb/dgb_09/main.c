#include "dgb_09.h"

EvtScript exitDoubleDoor_80243920 = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(dgb_09_ENTRY_0, "dgb_03", dgb_03_ENTRY_4,
    COLLIDER_deilittw, MODEL_o30, MODEL_o31, DOOR_SOUNDS_CREAKY);

EvtScript exitDoubleDoor_802439D4 = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(dgb_09_ENTRY_1, "dgb_01", dgb_01_ENTRY_3,
    COLLIDER_deilitte, MODEL_o102, MODEL_o101, DOOR_SOUNDS_CREAKY);

EvtScript exitSingleDoor_80243A88 = EVT_EXIT_SINGLE_DOOR_SET_SOUNDS(dgb_09_ENTRY_2, "dgb_12", dgb_12_ENTRY_0,
    COLLIDER_deilittnw, MODEL_o76, DOOR_SWING_OUT, DOOR_SOUNDS_BASIC);

EvtScript exitWalk_80243B3C = EVT_EXIT_WALK(40, dgb_09_ENTRY_3, "dgb_10", dgb_10_ENTRY_0);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(exitWalk_80243B3C), TRIGGER_FLOOR_ABOVE, COLLIDER_deiline, 1, 0)
    Return
    End
};

EvtScript enterWalk_80243BC4 = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(dgb_09_ENTRY_0)
            Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
            Set(LVar2, MODEL_o30)
            Set(LVar3, MODEL_o31)
            ExecWait(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq(dgb_09_ENTRY_1)
            Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
            Set(LVar2, MODEL_o102)
            Set(LVar3, MODEL_o101)
            ExecWait(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq(dgb_09_ENTRY_2)
            Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
            Set(LVar2, MODEL_o76)
            Set(LVar3, DOOR_SWING_OUT)
            ExecWait(EnterSingleDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq(dgb_09_ENTRY_3)
            Set(LVar0, Ref(EVS_BindExitTriggers))
            Exec(EnterWalk)
            Wait(1)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_TUBBAS_MANOR)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    IfLt(GB_StoryProgress, STORY_CH3_STAR_SPIRIT_RESCUED)
        Call(MakeNpcs, true, Ref(DefaultNPCs))
    EndIf
    Exec(EVS_SetupBreakable)
    BindTrigger(Ref(exitDoubleDoor_80243920), TRIGGER_WALL_PRESS_A, COLLIDER_deilittw, 1, 0)
    BindTrigger(Ref(exitDoubleDoor_802439D4), TRIGGER_WALL_PRESS_A, COLLIDER_deilitte, 1, 0)
    BindTrigger(Ref(exitSingleDoor_80243A88), TRIGGER_WALL_PRESS_A, COLLIDER_deilittnw, 1, 0)
    Exec(EVS_SetupMusic)
    Exec(enterWalk_80243BC4)
    Return
    End
};
