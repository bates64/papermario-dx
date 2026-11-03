#include "dgb_08.h"
#include "world/area/dgb/dgb_01.h"

EvtScript EVS_ExitDoors_dgb_01_2 = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(
    $Dgb01Lower, $dgb_01.Dgb08Lower, COLLIDER_deilittse, MODEL_o142, MODEL_o143, DOOR_SOUNDS_CREAKY
);

EvtScript EVS_ExitDoors_dgb_01_4 = EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS(
    $Dgb01Upper, $dgb_01.Dgb08Upper, COLLIDER_deilittne, MODEL_o140, MODEL_o141, DOOR_SOUNDS_CREAKY
);

EvtScript EVS_EnterMap = {
    Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($Dgb01Lower.index)
            Set(LVar2, MODEL_o142)
            Set(LVar3, MODEL_o143)
            ExecWait(EnterDoubleDoor)
        CaseEq($Dgb01Upper.index)
            Set(LVar2, MODEL_o140)
            Set(LVar3, MODEL_o141)
            ExecWait(EnterDoubleDoor)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_TUBBAS_MANOR)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Switch(GB_StoryProgress)
        CaseLt(STORY_CH3_TUBBA_SMASHED_THE_BRIDGES)
            Call(MakeNpcs, true, BeforeNPCs)
        CaseLt(STORY_CH3_DEFEATED_TUBBA_BLUBBA)
            Call(MakeNpcs, true, TubbaNPCs)
        CaseLt(STORY_CH6_RETURNED_TO_TOAD_TOWN)
            Call(MakeNpcs, true, AfterNPCs)
    EndSwitch
    ExecWait(EVS_MakeEntities)
    BindTrigger(EVS_ExitDoors_dgb_01_2, TRIGGER_WALL_PRESS_A, COLLIDER_deilittse, 1, 0)
    BindTrigger(EVS_ExitDoors_dgb_01_4, TRIGGER_WALL_PRESS_A, COLLIDER_deilittne, 1, 0)
    Exec(EVS_SetupMusic)
    Exec(EVS_EnterMap)
    Return
    End
};
