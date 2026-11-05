#include "dgb_04.h"
#include "world/area/dgb/dgb_03.h"
#include "world/area/dgb/dgb_06.h"

EvtScript EVS_ExitDoor_dgb_06_0 = EVT_EXIT_SINGLE_DOOR_SET_SOUNDS(
    $Dgb03, $dgb_06.Dgb04, COLLIDER_deilittse, MODEL_o206, DOOR_SWING_OUT, DOOR_SOUNDS_BASIC
);

EvtScript EVS_ExitDoors_dgb_03_0 = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(
    $Dgb06, $dgb_03.Dgb04, COLLIDER_deilittne, MODEL_o102, MODEL_o101, DOOR_SOUNDS_CREAKY
);

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($Dgb03.index)
            Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
            Set(LVar2, MODEL_o102)
            Set(LVar3, MODEL_o101)
            ExecWait(EnterDoubleDoor)
        CaseEq($Dgb06.index)
            Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
            Set(LVar2, MODEL_o206)
            Set(LVar3, DOOR_SWING_OUT)
            ExecWait(EnterSingleDoor)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    IfLt(GB_StoryProgress, STORY_CH3_STAR_SPIRIT_RESCUED)
        Call(MakeNpcs, true, DefaultNPCs)
    EndIf
    ExecWait(EVS_MakeEntities)
    BindTrigger(EVS_ExitDoor_dgb_06_0, TRIGGER_WALL_PRESS_A, COLLIDER_deilittse, 1, 0)
    BindTrigger(EVS_ExitDoors_dgb_03_0, TRIGGER_WALL_PRESS_A, COLLIDER_deilittne, 1, 0)
    Exec(EVS_SetupMusic)
    Exec(EVS_EnterMap)
    Return
    End
};
