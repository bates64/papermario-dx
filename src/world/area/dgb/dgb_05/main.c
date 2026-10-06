#include "dgb_05.h"

EvtScript EVS_ExitDoor_dgb_03_2 = EVT_EXIT_SINGLE_DOOR_SET_SOUNDS(dgb_05_ENTRY_0, "dgb_03", dgb_03_ENTRY_2,
    COLLIDER_deilittn, MODEL_o158, DOOR_SWING_IN, DOOR_SOUNDS_BASIC);

EvtScript EVS_EnterMap = {
    Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(dgb_05_ENTRY_0)
            Set(LVar2, MODEL_o158)
            Set(LVar3, DOOR_SWING_IN)
            ExecWait(EnterSingleDoor)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_TUBBAS_MANOR)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    IfLt(GB_StoryProgress, STORY_CH3_STAR_SPIRIT_RESCUED)
        Call(MakeNpcs, true, Ref(DefaultNPCs))
    EndIf
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupHole)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitts, COLLIDER_FLAGS_UPPER_MASK)
    Call(EnableModel, MODEL_o297, false)
    BindTrigger(Ref(EVS_ExitDoor_dgb_03_2), TRIGGER_WALL_PRESS_A, COLLIDER_deilittn, 1, 0)
    Exec(EVS_SetupMusic)
    Exec(EVS_EnterMap)
    Return
    End
};
