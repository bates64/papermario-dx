#include "trd_09.h"

extern EvtScript EVS_PlayDemoScene;
extern EvtScript EVS_SetupMusic;
extern EvtScript EVS_MakeEntities;
extern NpcGroupList DemoNPCs;
extern NpcGroupList DefaultNPCs;

EvtScript EVS_ExitDoors_trd_01_3 = EVT_EXIT_DOUBLE_DOOR(trd_09_ENTRY_0, "trd_01", trd_01_ENTRY_3,
    COLLIDER_tt5, MODEL_o67, MODEL_o63);
EvtScript EVS_ExitDoors_trd_10_0 = EVT_EXIT_DOUBLE_DOOR(trd_09_ENTRY_1, "trd_10", trd_10_ENTRY_0,
    COLLIDER_tt4, MODEL_o60, MODEL_o65);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitDoors_trd_01_3), TRIGGER_WALL_PRESS_A, COLLIDER_tt5, 1, 0)
    BindTrigger(Ref(EVS_ExitDoors_trd_10_0), TRIGGER_WALL_PRESS_A, COLLIDER_tt4, 1, 0)
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
    SetGroup(EVT_GROUP_NEVER_PAUSE)
    SuspendGroup(EVT_GROUP_FLAG_INTERACT)
    Exec(EVS_BindExitTriggers)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(trd_09_ENTRY_0)
            Set(LVar2, MODEL_o67)
            Set(LVar3, MODEL_o63)
            ExecWait(EnterDoubleDoor)
        CaseEq(trd_09_ENTRY_1)
            Set(LVar2, MODEL_o60)
            Set(LVar3, MODEL_o65)
            ExecWait(EnterDoubleDoor)
    EndSwitch
    ResumeGroup(EVT_GROUP_FLAG_INTERACT)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_KOOPA_BROS_FORTRESS)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Call(GetDemoState, LVar0)
    IfNe(LVar0, DEMO_STATE_NONE)
        Call(MakeNpcs, true, Ref(DemoNPCs))
        ExecWait(EVS_MakeEntities)
        ExecWait(EVS_PlayDemoScene)
        Return
    EndIf
    IfLe(GB_StoryProgress, STORY_CH1_DEFEATED_KOOPA_BROS)
        Call(MakeNpcs, true, Ref(DefaultNPCs))
    EndIf
    IfEq(GF_TRD09_Defeated_BillBlasters, true)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o85, COLLIDER_FLAGS_UPPER_MASK)
    EndIf
    ExecWait(EVS_MakeEntities)
    Exec(EVS_SetupMusic)
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
