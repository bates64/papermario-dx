#include "dgb_01.h"
#include "world/area/dgb/dgb_00.h"
#include "world/area/dgb/dgb_02.h"
#include "world/area/dgb/dgb_08.h"
#include "world/area/dgb/dgb_09.h"
#include "world/area/dgb/dgb_17.h"
#include "world/area/dgb/dgb_18.h"

EvtScript EVS_ExitDoors_dgb_00_1 = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(
    $Dgb00, $dgb_00.Dgb01, COLLIDER_deilitts, MODEL_o380, MODEL_o381, DOOR_SOUNDS_CREAKY
);

EvtScript EVS_ExitDoors_dgb_02_1 = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(
    $Dgb02, $dgb_02.Dgb01, COLLIDER_deilittsw, MODEL_o163, MODEL_o164, DOOR_SOUNDS_CREAKY
);

EvtScript EVS_ExitDoors_dgb_08_0 = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(
    $Dgb08Lower, $dgb_08.Dgb01Lower, COLLIDER_deilittse, MODEL_o168, MODEL_o167, DOOR_SOUNDS_CREAKY
);

EvtScript EVS_ExitDoors_dgb_09_1 = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(
    $Dgb09, $dgb_09.Dgb01, COLLIDER_deilittw, MODEL_o165, MODEL_o166, DOOR_SOUNDS_CREAKY
);

EvtScript EVS_ExitDoors_dgb_08_1 = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(
    $Dgb08Upper, $dgb_08.Dgb01Upper, COLLIDER_deilitte, MODEL_o299, MODEL_o298, DOOR_SOUNDS_CREAKY
);

EvtScript EVS_ExitDoors_dgb_17_1 = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(
    $Dgb17, $dgb_17.Dgb01, COLLIDER_deilittnw, MODEL_o161, MODEL_o162, DOOR_SOUNDS_CREAKY
);

EvtScript EVS_ExitDoors_dgb_18_0 = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(
    $Dgb18, $dgb_18.Dgb01, COLLIDER_deilittne, MODEL_o301, MODEL_o300, DOOR_SOUNDS_CREAKY
);

EvtScript EVS_EnterMap = {
    Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($Dgb00.index)
            IfEq(GF_DGB01_Visited, false)
                Set(GF_DGB01_Visited, true)
                Set(GB_StoryProgress, STORY_CH3_ARRIVED_AT_TUBBAS_MANOR)
            EndIf
            Set(LVar2, MODEL_o380)
            Set(LVar3, MODEL_o381)
            ExecWait(EnterDoubleDoor)
        CaseEq($Dgb02.index)
            Set(LVar2, MODEL_o163)
            Set(LVar3, MODEL_o164)
            ExecWait(EnterDoubleDoor)
        CaseEq($Dgb08Lower.index)
            Set(LVar2, MODEL_o168)
            Set(LVar3, MODEL_o167)
            ExecWait(EnterDoubleDoor)
        CaseEq($Dgb09.index)
            Set(LVar2, MODEL_o165)
            Set(LVar3, MODEL_o166)
            ExecWait(EnterDoubleDoor)
        CaseEq($Dgb08Upper.index)
            Set(LVar2, MODEL_o299)
            Set(LVar3, MODEL_o298)
            ExecWait(EnterDoubleDoor)
        CaseEq($Dgb17.index)
            Set(LVar2, MODEL_o161)
            Set(LVar3, MODEL_o162)
            ExecWait(EnterDoubleDoor)
        CaseEq($Dgb18.index)
            Set(LVar2, MODEL_o301)
            Set(LVar3, MODEL_o300)
            ExecWait(EnterDoubleDoor)
    EndSwitch
    Return
    End
};

ITEM_LIST(KeyList, ITEM_TUBBA_CASTLE_KEY);

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_TUBBAS_MANOR)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Set(GF_MAP_TubbasManor, true)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupBridges)
    Exec(EVS_SetupMusic)
    BindTrigger(EVS_ExitDoors_dgb_00_1, TRIGGER_WALL_PRESS_A, COLLIDER_deilitts, 1, 0)
    BindTrigger(EVS_ExitDoors_dgb_02_1, TRIGGER_WALL_PRESS_A, COLLIDER_deilittsw, 1, 0)
    BindTrigger(EVS_ExitDoors_dgb_09_1, TRIGGER_WALL_PRESS_A, COLLIDER_deilittw, 1, 0)
    BindTrigger(EVS_ExitDoors_dgb_08_1, TRIGGER_WALL_PRESS_A, COLLIDER_deilitte, 1, 0)
    BindTrigger(EVS_ExitDoors_dgb_17_1, TRIGGER_WALL_PRESS_A, COLLIDER_deilittnw, 1, 0)
    BindTrigger(EVS_ExitDoors_dgb_18_0, TRIGGER_WALL_PRESS_A, COLLIDER_deilittne, 1, 0)
    IfEq(GF_DGB01_UnlockedEastWing, false)
        BindPadlock(EVS_UnlockPrompt_Door, TRIGGER_WALL_PRESS_A, EVT_ENTITY_INDEX(0), KeyList, 0, 1)
    Else
        BindTrigger(EVS_ExitDoors_dgb_08_0, TRIGGER_WALL_PRESS_A, COLLIDER_deilittse, 1, 0)
    EndIf
    Switch(GB_StoryProgress)
        CaseLt(STORY_CH3_TUBBA_WOKE_UP)
            Call(MakeNpcs, true, DefaultNPCs)
        CaseLt(STORY_CH3_DEFEATED_TUBBA_BLUBBA)
            Call(GetEntryID, LVar0)
            Switch(LVar0)
                CaseEq($Dgb08Lower.index)
                    Call(MakeNpcs, true, FirstFloorEscapeNPCs)
                CaseEq($Dgb08Upper.index)
                    Call(MakeNpcs, true, SecondFloorEscapeNPCs)
                CaseEq($Dgb18.index)
                    Call(MakeNpcs, true, ThirdFloorEscapeNPCs)
            EndSwitch
    EndSwitch
    Exec(EVS_EnterMap)
    Return
    End
};
