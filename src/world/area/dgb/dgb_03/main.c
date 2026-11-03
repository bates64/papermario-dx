#include "dgb_03.h"
#include "world/area/dgb/dgb_02.h"
#include "world/area/dgb/dgb_04.h"
#include "world/area/dgb/dgb_05.h"
#include "world/area/dgb/dgb_09.h"
#include "world/area/dgb/dgb_13.h"
#include "world/area/dgb/dgb_14.h"

EvtScript EVS_ExitDoors_dgb_02_0 = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(
    $Dgb02, $dgb_02.Dgb03, COLLIDER_deilittse, MODEL_o102, MODEL_o101, DOOR_SOUNDS_CREAKY
);

EvtScript EVS_ExitDoors_dgb_09_0 = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(
    $Dgb09, $dgb_09.Dgb03, COLLIDER_deilittne, MODEL_o106, MODEL_o105, DOOR_SOUNDS_CREAKY
);

EvtScript EVS_ExitDoors_dgb_04_0 = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(
    $Dgb04, $dgb_04.Dgb03, COLLIDER_deilittsw, MODEL_o30, MODEL_o31, DOOR_SOUNDS_CREAKY
);

EvtScript EVS_ExitWalk_dgb_13_0 = EVT_EXIT_WALK(26, $Dgb05, $dgb_13.Dgb03);

EvtScript EVS_ExitDoors_dgb_05_0 = EVT_EXIT_SINGLE_DOOR_SET_SOUNDS(
    $Dgb05, $dgb_05.Dgb03, COLLIDER_deilitts, MODEL_o76, DOOR_SWING_OUT, DOOR_SOUNDS_BASIC
);

EvtScript EVS_ExitDoors_dgb_14_0 = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(
    $Dgb14, $dgb_14.Dgb03, COLLIDER_deilittnw, MODEL_o103, MODEL_o104, DOOR_SOUNDS_CREAKY
);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_dgb_13_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilin, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($Dgb04.index)
            Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
            Set(LVar2, MODEL_o30)
            Set(LVar3, MODEL_o31)
            ExecWait(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq($Dgb02.index)
            Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
            Set(LVar2, MODEL_o102)
            Set(LVar3, MODEL_o101)
            ExecWait(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq($Dgb05.index)
            Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
            Set(LVar2, MODEL_o76)
            Set(LVar3, DOOR_SWING_OUT)
            ExecWait(EnterSingleDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq($Dgb14.index)
            Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
            Set(LVar2, MODEL_o103)
            Set(LVar3, MODEL_o104)
            ExecWait(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq($Dgb09.index)
            Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
            Set(LVar2, MODEL_o106)
            Set(LVar3, MODEL_o105)
            ExecWait(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq($Dgb13.index)
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalkShort)
            Wait(1)
    EndSwitch
    Return
    End
};

ITEM_LIST(KeyList_UpperDoor, ITEM_TUBBA_CASTLE_KEY);

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_TUBBAS_MANOR)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    IfLt(GB_StoryProgress, STORY_CH3_STAR_SPIRIT_RESCUED)
        Call(MakeNpcs, true, DefaultNPCs)
    EndIf
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupClock)
    BindTrigger(EVS_ExitDoors_dgb_02_0, TRIGGER_WALL_PRESS_A, COLLIDER_deilittse, 1, 0)
    BindTrigger(EVS_ExitDoors_dgb_09_0, TRIGGER_WALL_PRESS_A, COLLIDER_deilittne, 1, 0)
    BindTrigger(EVS_ExitDoors_dgb_04_0, TRIGGER_WALL_PRESS_A, COLLIDER_deilittsw, 1, 0)
    BindTrigger(EVS_ExitDoors_dgb_05_0, TRIGGER_WALL_PRESS_A, COLLIDER_deilitts, 1, 0)
    IfEq(GF_DGB03_UnlockedThirdFloor, false)
        BindPadlock(EVS_UnlockPrompt_UpperDoor, TRIGGER_WALL_PRESS_A, EVT_ENTITY_INDEX(0), KeyList_UpperDoor, 0, 1)
    Else
        BindTrigger(EVS_ExitDoors_dgb_14_0, TRIGGER_WALL_PRESS_A, COLLIDER_deilittnw, 1, 0)
    EndIf
    Exec(EVS_SetupMusic)
    Exec(EVS_EnterMap)
    Return
    End
};
