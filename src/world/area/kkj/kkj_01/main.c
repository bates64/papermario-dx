#include "kkj_01.h"
#include "world/area/kkj/kkj_00.h"
#include "world/area/kkj/kkj_02.h"
#include "world/area/kkj/kkj_14.h"

EvtScript EVS_ExitDoors_kkj_00_1 = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(
    $EntryHall, $kkj_00.UpperHall, COLLIDER_tts, MODEL_door2, MODEL_door1, DOOR_SOUNDS_LARGE
);

EvtScript EVS_ExitDoors_kkj_02_0 = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(
    $StairsHallway, $kkj_02.UpperHall, COLLIDER_ttn, MODEL_door3, MODEL_door4, DOOR_SOUNDS_LARGE
);

EvtScript EVS_ExitDoors_kkj_14_0 = EVT_EXIT_SINGLE_DOOR_SET_SOUNDS(
    $PeachsRoom, $kkj_14.UpperHall, COLLIDER_ttn2, MODEL_door7, DOOR_SWING_OUT, DOOR_SOUNDS_BASIC
);

EvtScript EVS_ShowMessage_CantOpen = {
    Call(DisablePlayerInput, true)
    Call(ShowMessageAtScreenPos, MSG_Menus_Inspect_DoesntOpen, 160, 40)
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript EVS_BindExitTriggers = {
    IfEq(AF_KKJ01_MarioLetIntoBedroom, true)
        BindTrigger(EVS_ExitDoors_kkj_14_0, TRIGGER_WALL_PRESS_A, COLLIDER_ttn2, 1, 0)
    EndIf
    BindTrigger(EVS_ShowMessage_CantOpen, TRIGGER_WALL_PRESS_A, COLLIDER_tte, 1, 0)
    BindTrigger(EVS_ShowMessage_CantOpen, TRIGGER_WALL_PRESS_A, COLLIDER_ttsw, 1, 0)
    BindTrigger(EVS_ShowMessage_CantOpen, TRIGGER_WALL_PRESS_A, COLLIDER_ttw, 1, 0)
    BindTrigger(EVS_ShowMessage_CantOpen, TRIGGER_WALL_PRESS_A, COLLIDER_ttse, 1, 0)
    BindTrigger(EVS_ExitDoors_kkj_00_1, TRIGGER_WALL_PRESS_A, COLLIDER_tts, 1, 0)
    BindTrigger(EVS_ExitDoors_kkj_02_0, TRIGGER_WALL_PRESS_A, COLLIDER_ttn, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($EntryHall.index)
            Call(UseDoorSounds, DOOR_SOUNDS_LARGE)
            Set(LVar2, MODEL_door2)
            Set(LVar3, MODEL_door1)
            ExecWait(EnterDoubleDoor)
        CaseEq($StairsHallway.index)
            Call(UseDoorSounds, DOOR_SOUNDS_LARGE)
            Set(LVar2, MODEL_door3)
            Set(LVar3, MODEL_door4)
            ExecWait(EnterDoubleDoor)
        CaseEq($Entry2.index)
            Set(LVar2, MODEL_door5)
            Set(LVar3, DOOR_SWING_OUT)
            ExecWait(EnterSingleDoor)
        CaseEq($Entry3.index)
            Set(LVar2, MODEL_door6)
            Set(LVar3, DOOR_SWING_OUT)
            ExecWait(EnterSingleDoor)
        CaseEq($PeachsRoom.index)
            Set(LVar2, MODEL_door7)
            Set(LVar3, DOOR_SWING_OUT)
            ExecWait(EnterSingleDoor)
        CaseEq($Entry5.index)
            Set(LVar2, MODEL_door8)
            Set(LVar3, DOOR_SWING_IN)
            ExecWait(EnterSingleDoor)
        CaseEq($Entry6.index)
            Set(LVar2, MODEL_door9)
            Set(LVar3, DOOR_SWING_IN)
            ExecWait(EnterSingleDoor)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_PEACH_CASTLE_GROUNDS)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(MakeNpcs, false, DefaultNPCs)
    IfNe(GB_StoryProgress, STORY_INTRO)
        Call(EnableModel, MODEL_g74, false)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_g77, COLLIDER_FLAGS_UPPER_MASK)
    Else
        Call(EnableModel, MODEL_o321, false)
        Call(EnableModel, MODEL_o337, false)
        Call(EnableModel, MODEL_o330, false)
    EndIf
    Exec(EVS_SetupMusic)
    Exec(EVS_BindExitTriggers)
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
