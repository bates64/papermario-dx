#include "kmr_20.h"

#include "world/common/entity/Pipe.inc.c"

API_CALLABLE(SetupBeginGameTransition){
    set_map_transition_effect(TRANSITION_BEGIN_OR_END_GAME);
    return ApiStatus_DONE2;
}

EvtScript EVS_GotoMap_mac_00_4 = {
    Exec(EVS_FadeOutAmbientSounds)
    Call(GotoMap, Ref("mac_00"), mac_00_ENTRY_4)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitPipe_mac_00_4 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Set(LVarA, kmr_20_ENTRY_4)
    Set(LVarB, COLLIDER_o244)
    Set(LVarC, Ref(EVS_GotoMap_mac_00_4))
    ExecWait(EVS_Pipe_ExitVertical)
    Return
    End
};

EvtScript EVS_BindExitTriggers = {
    BindTrigger(Ref(EVS_ExitPipe_mac_00_4), TRIGGER_FLOOR_TOUCH, COLLIDER_o244, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_MARIOS_HOUSE)
    Call(GetEntryID, LVar0)
    IfEq(LVar0, kmr_20_ENTRY_2)
        Set(GB_StoryProgress, STORY_EPILOGUE)
    EndIf
    Call(GetEntryID, LVar0)
    IfEq(LVar0, kmr_20_ENTRY_4)
        Set(MF_LuigiWaiting, false)
        IfEq(GF_KMR20_ReunitedWithLuigi, false)
            Set(GF_KMR20_ReunitedWithLuigi, true)
            IfLt(GB_StoryProgress, STORY_CH3_INVITED_TO_BOOS_MANSION)
                Set(MF_LuigiWaiting, true)
            EndIf
        EndIf
    EndIf
    Set(MF_HouseInteriorVisible, false)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Exec(EVS_SetupMusic)
    Call(GetEntryID, LVar0)
    IfLt(LVar0, kmr_20_ENTRY_4)
        Call(MakeNpcs, false, Ref(SceneNPCs))
    Else
        Call(MakeNpcs, false, Ref(DefaultNPCs))
    EndIf
    ExecWait(EVS_MakeEntities)
    Call(EnableGroup, MODEL_g100, false)
    Exec(EVS_SetupTrees)
    Exec(EVS_SetupBushes)
    Exec(EVS_SetupRooms)
    Exec(EVS_Setup_Interactables)
    IfLt(GB_StoryProgress, STORY_EPILOGUE)
        Exec(EVS_SetupBed)
    EndIf
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq(kmr_20_ENTRY_0)
            Call(SetupBeginGameTransition)
            Exec(EVS_Scene_BeginGame)
            Wait(5)
        CaseEq(kmr_20_ENTRY_1)
            Exec(EVS_Scene_SettingOff)
        CaseEq(kmr_20_ENTRY_2)
            Wait(60)
            Exec(EVS_Scene_BeginEpilogue)
        CaseEq(kmr_20_ENTRY_3)
            Exec(EVS_BindExitTriggers)
            Exec(EVS_Scene_EpilogueGetLetter)
        CaseEq(kmr_20_ENTRY_4)
            Set(GF_MAP_MariosHouse, true)
            IfEq(MF_LuigiWaiting, true)
                Exec(EVS_Scene_LuigiWaitingAround)
                Thread
                    Call(DisablePlayerPhysics, true)
                    Call(SetPlayerPos, NPC_DISPOSE_LOCATION)
                    Label(0)
                        IfEq(MF_ReadyForPlayerEntry, false)
                            Wait(1)
                            Goto(0)
                        EndIf
                    Set(LVarA, Ref(EVS_BindExitTriggers))
                    Exec(EVS_Pipe_EnterVertical)
                EndThread
            Else
                Set(LVarA, Ref(EVS_BindExitTriggers))
                Exec(EVS_Pipe_EnterVertical)
            EndIf
    EndSwitch
    Return
    End
};
