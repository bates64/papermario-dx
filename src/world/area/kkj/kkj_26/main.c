#include "kkj_26.h"
#include "world/area/hos/hos_00.h"
#include "world/area/kkj/kkj_14.h"

#include "../common/RestoreFromPeachState.inc.c"

EvtScript EVS_GotoMap_hos_00_1 = {
    Set(LVar0, GB_KKJ_LastPartner)
    Call(RestoreFromPeachState)
    Call(PlaySound, SOUND_SLIDE_WHISTLE_OUT)
    Call(GotoMapSpecial, $hos_00.ShootingStarSummit, TRANSITION_END_PEACH_INTERLUDE)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitDoors_kkj_14_1 = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Set(LVar0, $PeachsRoom.index)
    Set(LVar1, COLLIDER_ttw)
    Set(LVar2, MODEL_o85)
    Set(LVar3, MODEL_o83)
    Set(LVar4, MODEL_o86)
    Set(LVar5, MODEL_o84)
    Exec(ExitSplitDoubleDoor)
    Wait(17)
    Call(GotoMap, $kkj_14.Balcony)
    Wait(100)
    Return
    End
};

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitDoors_kkj_14_1, TRIGGER_WALL_PRESS_A, COLLIDER_ttw, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($PeachsRoom.index)
            Set(LVar2, MODEL_o85)
            Set(LVar3, MODEL_o83)
            Set(LVar4, MODEL_o86)
            Set(LVar5, MODEL_o84)
            ExecWait(EnterSplitDoubleDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq($AllSpiritsRescued.index)
            Exec(EVS_Scene_AfterAllSpiritsRescued)
        CaseEq($WhereIsMario.index)
            Exec(EVS_Scene_WhereIsMario)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Call(GetEntryID, LVar0)
    IfEq(LVar0, $AllSpiritsRescued.index)
        Set(GB_StoryProgress, STORY_CH7_BEGAN_PEACH_MISSION)
    EndIf
    Call(UseDoorSounds, DOOR_SOUNDS_DOOR)
    Call(GetDemoState, LVar0)
    IfNe(LVar0, DEMO_STATE_NONE)
        ExecWait(EVS_PlayDemoScene)
        Return
    EndIf
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
