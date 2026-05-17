#include "dgb_08.h"

EvtScript N(EVS_ExitDoors_dgb_01_2) = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(dgb_08_ENTRY_0, "dgb_01", dgb_01_ENTRY_2,
    COLLIDER_deilittse, MODEL_o142, MODEL_o143, DOOR_SOUNDS_CREAKY);

EvtScript N(EVS_ExitDoors_dgb_01_4) = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(dgb_08_ENTRY_1, "dgb_01", dgb_01_ENTRY_4,
    COLLIDER_deilittne, MODEL_o140, MODEL_o141, DOOR_SOUNDS_CREAKY);

EvtScript N(EVS_EnterMap) = {
    Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(dgb_08_ENTRY_0)
            Set(LVar2, MODEL_o142)
            Set(LVar3, MODEL_o143)
            ExecWait(EnterDoubleDoor)
        CaseEq(dgb_08_ENTRY_1)
            Set(LVar2, MODEL_o140)
            Set(LVar3, MODEL_o141)
            ExecWait(EnterDoubleDoor)
    EndSwitch
    Return
    End
};

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_TUBBAS_MANOR)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Switch(GB_StoryProgress)
        CaseLt(STORY_CH3_TUBBA_SMASHED_THE_BRIDGES)
            Call(MakeNpcs, true, Ref(N(BeforeNPCs)))
        CaseLt(STORY_CH3_DEFEATED_TUBBA_BLUBBA)
            Call(MakeNpcs, true, Ref(N(TubbaNPCs)))
        CaseLt(STORY_CH6_RETURNED_TO_TOAD_TOWN)
            Call(MakeNpcs, true, Ref(N(AfterNPCs)))
    EndSwitch
    ExecWait(N(EVS_MakeEntities))
    BindTrigger(Ref(N(EVS_ExitDoors_dgb_01_2)), TRIGGER_WALL_PRESS_A, COLLIDER_deilittse, 1, 0)
    BindTrigger(Ref(N(EVS_ExitDoors_dgb_01_4)), TRIGGER_WALL_PRESS_A, COLLIDER_deilittne, 1, 0)
    Exec(N(EVS_SetupMusic))
    Exec(N(EVS_EnterMap))
    Return
    End
};
