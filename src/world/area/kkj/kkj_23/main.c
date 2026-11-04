#include "kkj_23.h"
#include "world/area/flo/flo_00.h"
#include "world/area/kkj/kkj_22.h"
#include "world/area/kkj/kkj_24.h"

#include "../common/RestoreFromPeachState.inc.c"

EvtScript EVS_EndPeachChapter6 = {
    Set(LVar0, GB_KKJ_LastPartner)
    Call(RestoreFromPeachState)
    Call(PlaySound, SOUND_SLIDE_WHISTLE_OUT)
    Call(GotoMapSpecial, $flo_00.PeachInterlude, TRANSITION_END_PEACH_INTERLUDE)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitDoors_kkj_22_1 =
    EVT_EXIT_DOUBLE_DOOR($DoubleStaircase, $kkj_22.Rooftop, COLLIDER_tte, MODEL_o5, MODEL_o4);

EvtScript EVS_ExitDoors_kkj_24_0 =
    EVT_EXIT_DOUBLE_DOOR($TowerStaircase, $kkj_24.Rooftop, COLLIDER_ttw, MODEL_o9, MODEL_o10);

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($DoubleStaircase.index)
            Set(LVar2, MODEL_o5)
            Set(LVar3, MODEL_o4)
            ExecWait(EnterDoubleDoor)
            IfEq(GB_StoryProgress, STORY_CH6_BEGAN_PEACH_MISSION)
                Exec(EVS_Scene_KammyUnmasksPeach)
            Else
                Exec(EVS_BowserTauntMario)
            EndIf
        CaseEq($TowerStaircase.index)
            Set(LVar2, MODEL_o9)
            Set(LVar3, MODEL_o10)
            ExecWait(EnterDoubleDoor)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_PEACHS_CASTLE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    IfEq(GB_StoryProgress, STORY_CH6_BEGAN_PEACH_MISSION)
        Call(SetAvailableDisguise, PEACH_DISGUISE_KOOPATROL)
        Call(MakeNpcs, false, PeachNPCs)
    Else
        Call(MakeNpcs, false, FinaleNPCs)
    EndIf
    Exec(EVS_SetupMusic)
    Call(UseDoorSounds, DOOR_SOUNDS_LARGE)
    BindTrigger(EVS_ExitDoors_kkj_24_0, TRIGGER_WALL_PRESS_A, COLLIDER_ttw, 1, 0)
    BindTrigger(EVS_ExitDoors_kkj_22_1, TRIGGER_WALL_PRESS_A, COLLIDER_tte, 1, 0)
    Exec(EVS_EnterMap)
    Return
    End
};
