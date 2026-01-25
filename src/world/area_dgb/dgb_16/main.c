#include "dgb_16.h"

EvtScript N(EVS_ExitDoors_dgb_15_2) = EVT_EXIT_SINGLE_DOOR_SET_SOUNDS(dgb_16_ENTRY_0, "dgb_15", dgb_15_ENTRY_2,
    COLLIDER_deilittne, MODEL_o123, DOOR_SWING_IN, DOOR_SOUNDS_BASIC);

EvtScript N(EVS_EnterMap) = {
    Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(dgb_16_ENTRY_0)
            IfEq(GF_DGB16_EscapedFromTubba, FALSE)
                Set(GF_DGB16_EscapedFromTubba, TRUE)
                Set(GB_ARN_Tubba_MapID, 18)
            EndIf
            Set(LVar2, MODEL_o123)
            Set(LVar3, DOOR_SWING_IN)
            ExecWait(EnterSingleDoor)
    EndSwitch
    Return
    End
};

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_TUBBAS_MANOR)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    IfLt(GB_StoryProgress, STORY_CH3_STAR_SPIRIT_RESCUED)
        Call(MakeNpcs, TRUE, Ref(N(DefaultNPCs)))
    EndIf
    ExecWait(N(EVS_MakeEntities))
    Exec(N(EVS_SetupMusic))
    BindTrigger(Ref(N(EVS_ExitDoors_dgb_15_2)), TRIGGER_WALL_PRESS_A, COLLIDER_deilittne, 1, 0)
    Exec(N(EVS_EnterMap))
    Return
    End
};
