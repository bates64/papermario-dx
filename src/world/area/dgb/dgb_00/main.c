#include "dgb_00.h"
#include "world/area/arn/arn_04.h"
#include "world/area/dgb/dgb_01.h"

export s32 map_init(void) {
    use_map_geometry("arn_20");
    return false;
}

EvtScript EVS_ExitWalk_arn_04_1 = EVT_EXIT_WALK(60, $GustyGulch, $arn_04.TubbasManor);

EvtScript EVS_ExitDoors_dgb_01_0 =
    EVT_EXIT_DOUBLE_DOOR_SET_SOUNDS($Dgb01, $dgb_01.Dgb00, COLLIDER_deiliwt, MODEL_d1, MODEL_d2, DOOR_SOUNDS_CREAKY);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_arn_04_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deilie, 1, 0)
    Switch(GB_StoryProgress)
        CaseLt(STORY_CH3_TUBBA_SMASHED_THE_BRIDGES)
            BindTrigger(EVS_ExitDoors_dgb_01_0, TRIGGER_WALL_PRESS_A, COLLIDER_deiliwt, 1, 0)
        CaseLt(STORY_CH3_ESCAPED_TUBBAS_MANOR)
        CaseLt(STORY_CH3_DEFEATED_TUBBA_BLUBBA)
            Exec(EVS_TubbaTaunting)
            ExecWait(EVS_SetBoosBracingDoor)
        CaseDefault
            BindTrigger(EVS_ExitDoors_dgb_01_0, TRIGGER_WALL_PRESS_A, COLLIDER_deiliwt, 1, 0)
    EndSwitch
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
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($GustyGulch.index)
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
            Wait(1)
        CaseEq($Dgb01.index)
            IfGe(GB_StoryProgress, STORY_CH3_TUBBA_SMASHED_THE_BRIDGES)
                IfLt(GB_StoryProgress, STORY_CH3_ESCAPED_TUBBAS_MANOR)
                    Exec(EVS_BindExitTriggers)
                    Thread
                        ExecWait(EVS_Scene_BoosApproachManor)
                        ExecWait(EVS_Scene_EscapeFromTubba)
                    EndThread
                    Return
                EndIf
            EndIf
            Call(UseDoorSounds, DOOR_SOUNDS_CREAKY)
            Set(LVar2, MODEL_d1)
            Set(LVar3, MODEL_d2)
            ExecWait(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq(2)
            Exec(EVS_BindExitTriggers)
            Exec(EVS_Scene_ThrownOutBySentinel)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_TUBBAS_MANOR)
    Set(GF_MAP_TubbasManor, true)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Call(GetEntryID, LVar0)
    IfEq(LVar0, 2)
        Call(MakeNpcs, false, DefaultNPCs)
    Else
        Call(MakeNpcs, false, BooNPCs)
    EndIf
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMusic)
    Exec(EVS_EnterMap)
    Return
    End
};
