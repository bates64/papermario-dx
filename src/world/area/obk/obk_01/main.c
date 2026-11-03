#include "obk_01.h"
#include "world/area/mim/mim_11.h"
#include "world/area/obk/obk_02.h"
#include "world/area/obk/obk_05.h"
#include "world/area/obk/obk_07.h"
#include "world/area/obk/obk_08.h"
#include "world/area/obk/obk_09.h"

EvtScript EVS_ExitDoors_mim_11_2 = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(
    $ForeverForest, $mim_11.BoosMansion, COLLIDER_tt1, MODEL_door1_2, MODEL_door1_1, DOOR_SOUNDS_CREAKY
);

EvtScript EVS_ExitDoor_obk_02_0 = {
    IfLt(GB_StoryProgress, STORY_CH3_WEIGHED_DOWN_CHANDELIER)
        Return
    EndIf
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
    Set(LVar0, $BasementStairs.index)
    Set(LVar1, COLLIDER_tt2)
    Set(LVar2, MODEL_door2)
    Set(LVar3, DOOR_SWING_IN)
    Exec(ExitSingleDoor)
    Wait(17)
    Call(GotoMap, $obk_02.Foyer)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitDoor_obk_05_0 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    IfLt(GB_StoryProgress, STORY_CH3_TRIGGERED_DOOR_JUMP_SCARE)
        Exec(EVS_Scene_JumpScareBoo)
        Return
    EndIf
    Call(DisablePlayerInput, true)
    Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
    Set(LVar0, $PotRoom.index)
    Set(LVar1, COLLIDER_tt3)
    Set(LVar2, MODEL_door3)
    Set(LVar3, DOOR_SWING_IN)
    Exec(ExitSingleDoor)
    Wait(17)
    Call(GotoMap, $obk_05.Foyer)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitDoor_obk_07_0 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    IfLt(GB_StoryProgress, STORY_CH3_TRIGGERED_DOOR_JUMP_SCARE)
        Exec(EVS_Scene_JumpScareBoo)
        Return
    EndIf
    Call(DisablePlayerInput, true)
    Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
    Set(LVar0, $RecordPlayerRoom.index)
    Set(LVar1, COLLIDER_tt4)
    Set(LVar2, MODEL_door4)
    Set(LVar3, DOOR_SWING_IN)
    Exec(ExitSingleDoor)
    Wait(17)
    Call(GotoMap, $obk_07.Foyer)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitDoor_obk_08_0 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    IfLt(GB_StoryProgress, STORY_CH3_TRIGGERED_DOOR_JUMP_SCARE)
        Exec(EVS_Scene_JumpScareBoo)
        Return
    EndIf
    Call(DisablePlayerInput, true)
    Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
    Set(LVar0, $RecordRoom.index)
    Set(LVar1, COLLIDER_tt5)
    Set(LVar2, MODEL_door5)
    Set(LVar3, DOOR_SWING_IN)
    Exec(ExitSingleDoor)
    Wait(17)
    Call(GotoMap, $obk_08.Foyer)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitDoor_obk_09_0 = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(
    $LadyBowsRoomWest, $obk_09.FoyerWest, COLLIDER_tt6, MODEL_door6_1, MODEL_door6_2, DOOR_SOUNDS_CREAKY
);

EvtScript EVS_ExitDoor_obk_09_1 = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(
    $LadyBowsRoomEast, $obk_09.FoyerEast, COLLIDER_tt6_1, MODEL_door7_1, MODEL_door7_2, DOOR_SOUNDS_CREAKY
);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitDoors_mim_11_2, TRIGGER_WALL_PRESS_A, COLLIDER_tt1, 1, 0)
    BindTrigger(EVS_ExitDoor_obk_02_0, TRIGGER_WALL_PRESS_A, COLLIDER_tt2, 1, 0)
    BindTrigger(EVS_ExitDoor_obk_05_0, TRIGGER_WALL_PRESS_A, COLLIDER_tt3, 1, 0)
    BindTrigger(EVS_ExitDoor_obk_07_0, TRIGGER_WALL_PRESS_A, COLLIDER_tt4, 1, 0)
    BindTrigger(EVS_ExitDoor_obk_08_0, TRIGGER_WALL_PRESS_A, COLLIDER_tt5, 1, 0)
    BindTrigger(EVS_ExitDoor_obk_09_0, TRIGGER_WALL_PRESS_A, COLLIDER_tt6, 1, 0)
    BindTrigger(EVS_ExitDoor_obk_09_1, TRIGGER_WALL_PRESS_A, COLLIDER_tt6_1, 1, 0)
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
    Exec(EVS_BindExitTriggers)
    Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($ForeverForest.index)
            IfEq(GF_OBK01_Visited, false)
                Set(GF_OBK01_Visited, true)
                Set(GB_StoryProgress, STORY_CH3_ENTERED_BOOS_MANSION)
            EndIf
            Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
            Set(LVar2, MODEL_door1_2)
            Set(LVar3, MODEL_door1_1)
            ExecWait(EnterDoubleDoor)
        CaseEq($BasementStairs.index)
            Set(LVar2, MODEL_door2)
            Set(LVar3, DOOR_SWING_IN)
            ExecWait(EnterSingleDoor)
        CaseEq($PotRoom.index)
            Set(LVar2, MODEL_door3)
            Set(LVar3, DOOR_SWING_IN)
            ExecWait(EnterSingleDoor)
        CaseEq($RecordPlayerRoom.index)
            Set(LVar2, MODEL_door4)
            Set(LVar3, DOOR_SWING_IN)
            ExecWait(EnterSingleDoor)
        CaseEq($RecordRoom.index)
            Set(LVar2, MODEL_door5)
            Set(LVar3, DOOR_SWING_IN)
            ExecWait(EnterSingleDoor)
        CaseEq($LadyBowsRoomWest.index)
            Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
            Set(LVar2, MODEL_door6_1)
            Set(LVar3, MODEL_door6_2)
            ExecWait(EnterDoubleDoor)
        CaseEq($LadyBowsRoomEast.index)
            Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
            Set(LVar2, MODEL_door7_1)
            Set(LVar3, MODEL_door7_2)
            ExecWait(EnterDoubleDoor)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_BOOS_MANSION)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Set(GF_MAP_BoosMansion, true)
    Call(MakeNpcs, false, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupChandelier)
    Exec(EVS_SetupPortrait)
    Exec(EVS_SetupMusic)
    Exec(EVS_EnterMap)
    Return
    End
};
