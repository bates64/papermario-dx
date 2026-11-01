#include "dgb_16.h"
#include "world/area/dgb/dgb_15.h"

EvtScript EVS_ExitDoors_dgb_15_2 = EVT_EXIT_SINGLE_DOOR_SET_SOUNDS(
    $Dgb15, $dgb_15.Dgb16, COLLIDER_deilittne, MODEL_o123, DOOR_SWING_IN, DOOR_SOUNDS_BASIC
);

EvtScript EVS_EnterMap = {
    Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($Dgb15.index)
            IfEq(GF_DGB16_EscapedFromTubba, false)
                Set(GF_DGB16_EscapedFromTubba, true)
                Set(GB_ARN_Tubba_MapID, 18)
            EndIf
            Set(LVar2, MODEL_o123)
            Set(LVar3, DOOR_SWING_IN)
            ExecWait(EnterSingleDoor)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_TUBBAS_MANOR)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    IfLt(GB_StoryProgress, STORY_CH3_STAR_SPIRIT_RESCUED)
        Call(MakeNpcs, true, DefaultNPCs)
    EndIf
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMusic)
    BindTrigger(EVS_ExitDoors_dgb_15_2, TRIGGER_WALL_PRESS_A, COLLIDER_deilittne, 1, 0)
    Exec(EVS_EnterMap)
    Return
    End
};
