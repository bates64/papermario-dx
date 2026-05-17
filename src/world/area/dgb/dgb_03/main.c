#include "dgb_03.h"

EvtScript N(EVS_ExitDoors_dgb_02_0) = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(dgb_03_ENTRY_1, "dgb_02", dgb_02_ENTRY_0,
    COLLIDER_deilittse, MODEL_o102, MODEL_o101, DOOR_SOUNDS_CREAKY);

EvtScript N(EVS_ExitDoors_dgb_09_0) = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(dgb_03_ENTRY_4, "dgb_09", dgb_09_ENTRY_0,
    COLLIDER_deilittne, MODEL_o106, MODEL_o105, DOOR_SOUNDS_CREAKY);

EvtScript N(EVS_ExitDoors_dgb_04_0) = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(dgb_03_ENTRY_0, "dgb_04", dgb_04_ENTRY_0,
    COLLIDER_deilittsw, MODEL_o30, MODEL_o31, DOOR_SOUNDS_CREAKY);

EvtScript N(EVS_ExitWalk_dgb_13_0) = EVT_EXIT_WALK(26, dgb_03_ENTRY_2, "dgb_13", dgb_13_ENTRY_0);

EvtScript N(EVS_ExitDoors_dgb_05_0) = EVT_EXIT_SINGLE_DOOR_SET_SOUNDS(dgb_03_ENTRY_2, "dgb_05", dgb_05_ENTRY_0,
    COLLIDER_deilitts, MODEL_o76, DOOR_SWING_OUT, DOOR_SOUNDS_BASIC);

EvtScript N(EVS_ExitDoors_dgb_14_0) = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(dgb_03_ENTRY_3, "dgb_14", dgb_14_ENTRY_0,
    COLLIDER_deilittnw, MODEL_o103, MODEL_o104, DOOR_SOUNDS_CREAKY);

EvtScript N(EVS_BindExitTriggers) = {
    BindTrigger(Ref(N(EVS_ExitWalk_dgb_13_0)), TRIGGER_FLOOR_ABOVE, COLLIDER_deilin, 1, 0)
    Return
    End
};

EvtScript N(EVS_EnterMap) = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(dgb_03_ENTRY_0)
            Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
            Set(LVar2, MODEL_o30)
            Set(LVar3, MODEL_o31)
            ExecWait(EnterDoubleDoor)
            Exec(N(EVS_BindExitTriggers))
        CaseEq(dgb_03_ENTRY_1)
            Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
            Set(LVar2, MODEL_o102)
            Set(LVar3, MODEL_o101)
            ExecWait(EnterDoubleDoor)
            Exec(N(EVS_BindExitTriggers))
        CaseEq(dgb_03_ENTRY_2)
            Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
            Set(LVar2, MODEL_o76)
            Set(LVar3, DOOR_SWING_OUT)
            ExecWait(EnterSingleDoor)
            Exec(N(EVS_BindExitTriggers))
        CaseEq(dgb_03_ENTRY_3)
            Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
            Set(LVar2, MODEL_o103)
            Set(LVar3, MODEL_o104)
            ExecWait(EnterDoubleDoor)
            Exec(N(EVS_BindExitTriggers))
        CaseEq(dgb_03_ENTRY_4)
            Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
            Set(LVar2, MODEL_o106)
            Set(LVar3, MODEL_o105)
            ExecWait(EnterDoubleDoor)
            Exec(N(EVS_BindExitTriggers))
        CaseEq(dgb_03_ENTRY_5)
            Set(LVar0, Ref(N(EVS_BindExitTriggers)))
            Exec(EnterWalkShort)
            Wait(1)
    EndSwitch
    Return
    End
};

s32 N(KeyList_UpperDoor)[] = {
    ITEM_TUBBA_CASTLE_KEY,
    ITEM_NONE
};

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_TUBBAS_MANOR)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    IfLt(GB_StoryProgress, STORY_CH3_STAR_SPIRIT_RESCUED)
        Call(MakeNpcs, true, Ref(N(DefaultNPCs)))
    EndIf
    ExecWait(N(EVS_MakeEntities))
    Exec(N(EVS_SetupClock))
    BindTrigger(Ref(N(EVS_ExitDoors_dgb_02_0)), TRIGGER_WALL_PRESS_A, COLLIDER_deilittse, 1, 0)
    BindTrigger(Ref(N(EVS_ExitDoors_dgb_09_0)), TRIGGER_WALL_PRESS_A, COLLIDER_deilittne, 1, 0)
    BindTrigger(Ref(N(EVS_ExitDoors_dgb_04_0)), TRIGGER_WALL_PRESS_A, COLLIDER_deilittsw, 1, 0)
    BindTrigger(Ref(N(EVS_ExitDoors_dgb_05_0)), TRIGGER_WALL_PRESS_A, COLLIDER_deilitts, 1, 0)
    IfEq(GF_DGB03_UnlockedThirdFloor, false)
        BindPadlock(Ref(N(EVS_UnlockPrompt_UpperDoor)), TRIGGER_WALL_PRESS_A, EVT_ENTITY_INDEX(0), Ref(N(KeyList_UpperDoor)), 0, 1)
    Else
        BindTrigger(Ref(N(EVS_ExitDoors_dgb_14_0)), TRIGGER_WALL_PRESS_A, COLLIDER_deilittnw, 1, 0)
    EndIf
    Exec(N(EVS_SetupMusic))
    Exec(N(EVS_EnterMap))
    Return
    End
};
