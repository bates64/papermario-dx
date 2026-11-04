#include "kkj_11.h"
#include "world/area/kkj/kkj_10.h"
#include "world/area/kkj/kkj_12.h"
#include "world/area/kkj/kkj_14.h"
#include "world/area/kkj/kkj_15.h"
#include "world/area/kkj/kkj_16.h"
#include "world/area/kkj/kkj_17.h"
#include "world/area/kkj/kkj_18.h"

API_CALLABLE(DisableAllLightSources) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gSpriteShadingProfile->sources); i++) {
        gSpriteShadingProfile->sources[i].flags = LIGHT_SOURCE_DISABLED;
    }

    return ApiStatus_DONE2;
}

EvtScript EVS_ExitDoors_kkj_10_1 = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(
    $EntryHall, $kkj_10.UpperHall, COLLIDER_tts, MODEL_door2, MODEL_door1, DOOR_SOUNDS_LARGE
);

EvtScript EVS_ExitDoors_kkj_12_0 = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(
    $StairsHallway, $kkj_12.UpperHall, COLLIDER_ttn, MODEL_door3, MODEL_door4, DOOR_SOUNDS_LARGE
);

EvtScript EVS_ExitDoor_kkj_14_0 = EVT_EXIT_SINGLE_DOOR_SET_SOUNDS(
    $PeachsRoom, $kkj_14.UpperHall, COLLIDER_ttn2, MODEL_door7, DOOR_SWING_OUT, DOOR_SOUNDS_BASIC
);

EvtScript EVS_ExitDoor_kkj_16_0 = EVT_EXIT_SINGLE_DOOR_SET_SOUNDS(
    $Library, $kkj_16.UpperHall, COLLIDER_ttsw, MODEL_door5, DOOR_SWING_OUT, DOOR_SOUNDS_BASIC
);

EvtScript EVS_ExitDoor_kkj_15_0 = EVT_EXIT_SINGLE_DOOR_SET_SOUNDS(
    $PassageOutlet, $kkj_15.UpperHall, COLLIDER_ttw, MODEL_door6, DOOR_SWING_OUT, DOOR_SOUNDS_BASIC
);

EvtScript EVS_ExitDoor_kkj_17_0 = EVT_EXIT_SINGLE_DOOR_SET_SOUNDS(
    $Storeroom, $kkj_17.UpperHall, COLLIDER_tte, MODEL_door8, DOOR_SWING_IN, DOOR_SOUNDS_BASIC
);

EvtScript EVS_ExitDoor_kkj_18_0 = EVT_EXIT_SINGLE_DOOR_SET_SOUNDS(
    $DiningRoom, $kkj_18.UpperHall, COLLIDER_ttse, MODEL_door9, DOOR_SWING_IN, DOOR_SOUNDS_BASIC
);

EvtScript EVS_BindExitTriggers = {
    IfGt(GB_StoryProgress, STORY_CH4_BEGAN_PEACH_MISSION)
        BindTrigger(EVS_ExitDoors_kkj_10_1, TRIGGER_WALL_PRESS_A, COLLIDER_tts, 1, 0)
    EndIf
    IfGt(GB_StoryProgress, STORY_CH7_BEGAN_PEACH_MISSION)
        BindTrigger(EVS_ExitDoors_kkj_12_0, TRIGGER_WALL_PRESS_A, COLLIDER_ttn, 1, 0)
        BindTrigger(EVS_ExitDoor_kkj_14_0, TRIGGER_WALL_PRESS_A, COLLIDER_ttn2, 1, 0)
    EndIf
    BindTrigger(EVS_ExitDoor_kkj_17_0, TRIGGER_WALL_PRESS_A, COLLIDER_tte, 1, 0)
    BindTrigger(EVS_ExitDoor_kkj_16_0, TRIGGER_WALL_PRESS_A, COLLIDER_ttsw, 1, 0)
    BindTrigger(EVS_ExitDoor_kkj_15_0, TRIGGER_WALL_PRESS_A, COLLIDER_ttw, 1, 0)
    BindTrigger(EVS_ExitDoor_kkj_18_0, TRIGGER_WALL_PRESS_A, COLLIDER_ttse, 1, 0)
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
        CaseEq($Library.index)
            Set(LVar2, MODEL_door5)
            Set(LVar3, DOOR_SWING_OUT)
            ExecWait(EnterSingleDoor)
        CaseEq($PassageOutlet.index)
            Set(LVar2, MODEL_door6)
            Set(LVar3, DOOR_SWING_OUT)
            ExecWait(EnterSingleDoor)
        CaseEq($PeachsRoom.index)
            Set(LVar2, MODEL_door7)
            Set(LVar3, DOOR_SWING_OUT)
            ExecWait(EnterSingleDoor)
        CaseEq($Storeroom.index)
            Set(LVar2, MODEL_door8)
            Set(LVar3, DOOR_SWING_IN)
            ExecWait(EnterSingleDoor)
        CaseEq($DiningRoom.index)
            Set(LVar2, MODEL_door9)
            Set(LVar3, DOOR_SWING_IN)
            ExecWait(EnterSingleDoor)
        CaseEq($PassageOutletFirst.index)
            ExecWait(EVS_FirstTimeEnterHall)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_PEACHS_CASTLE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Switch(GB_StoryProgress)
        CaseOrEq(STORY_CH1_BEGAN_PEACH_MISSION)
        CaseOrEq(STORY_CH2_BEGAN_PEACH_MISSION)
        CaseOrEq(STORY_CH3_BEGAN_PEACH_MISSION)
        CaseOrEq(STORY_CH4_BEGAN_PEACH_MISSION)
        CaseOrEq(STORY_CH5_BEGAN_PEACH_MISSION)
            Call(MakeNpcs, false, EarlyNPCs)
        EndCaseGroup
        CaseEq(STORY_CH6_BEGAN_PEACH_MISSION)
            Call(SetAvailableDisguise, PEACH_DISGUISE_KOOPATROL)
            Call(EnableModel, MODEL_o364, false)
            Call(EnableModel, MODEL_o365, false)
            Call(EnableModel, MODEL_o366, false)
            Call(DisableAllLightSources)
            Call(MakeNpcs, false, LaterNPCs)
        CaseDefault
            Call(EnableModel, MODEL_o364, false)
            Call(EnableModel, MODEL_o365, false)
            Call(EnableModel, MODEL_o366, false)
            Call(DisableAllLightSources)
    EndSwitch
    ExecWait(EVS_MakeEntities)
    Call(GetDemoState, LVar0)
    IfNe(LVar0, DEMO_STATE_NONE)
        ExecWait(EVS_PlayDemoScene)
        Return
    EndIf
    IfLt(GB_StoryProgress, STORY_CH8_REACHED_PEACHS_CASTLE)
        Call(SetMusic, 0, SONG_PEACH_SNEAKING, 0, VOL_LEVEL_FULL)
    EndIf
    Exec(EVS_BindExitTriggers)
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
