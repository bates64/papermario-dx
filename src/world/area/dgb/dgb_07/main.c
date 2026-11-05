#include "dgb_07.h"
#include "world/area/dgb/dgb_02.h"

EvtScript EVS_ExitDoor_dgb_02_2 = EVT_EXIT_SINGLE_DOOR_SET_SOUNDS(
    $Dgb02, $dgb_02.Dgb07, COLLIDER_deilits, MODEL_o158, DOOR_SWING_IN, DOOR_SOUNDS_BASIC
);

EvtScript EVS_EnterMap = {
    Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($Dgb02.index)
            Set(LVar2, MODEL_o158)
            Set(LVar3, DOOR_SWING_IN)
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
    BindTrigger(EVS_ExitDoor_dgb_02_2, TRIGGER_WALL_PRESS_A, COLLIDER_deilits, 1, 0)
    Exec(EVS_SetupMusic)
    Exec(EVS_EnterMap)
    Return
    End
};
