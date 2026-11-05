#include "osr_00.h"
#include "world/area/kkj/kkj_00.h"
#include "world/area/mac/mac_01.h"
#include "effects.h"

EvtScript EVS_ExitWalk_mac_01_2 = EVT_EXIT_WALK(60, $ToadTown, $mac_01.PeachsCastle);
EvtScript EVS_ExitDoors_kkj_00_6 =
    EVT_EXIT_DOUBLE_DOOR($CastleDoor, $kkj_00.Ending, COLLIDER_deilitn, MODEL_d2, MODEL_d1);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_mac_01_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deilis, 1, 0)
    BindTrigger(EVS_ExitDoors_kkj_00_6, TRIGGER_WALL_PRESS_A, COLLIDER_deilitn, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($CastleDoor.index)
            Set(LVar2, MODEL_d2)
            Set(LVar3, MODEL_d1)
            ExecWait(EnterDoubleDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq($Invitation.index)
            Exec(EVS_Scene_ShowInvitation)
        CaseEq($ApproachParty.index)
            Exec(EVS_Scene_ApproachParty)
        CaseDefault
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
    EndSwitch
    Return
    End
};

EvtScript EVS_TexPan_Fountain = {
    SetGroup(EVT_GROUP_NEVER_PAUSE)
    Call(SetTexPanner, MODEL_fw1, TEX_PANNER_1)
    Call(SetTexPanner, MODEL_w2, TEX_PANNER_2)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_1)
        TEX_PAN_PARAMS_STEP(    0, -200,    0,    0)
        TEX_PAN_PARAMS_FREQ(    0,    1,    0,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_2)
        TEX_PAN_PARAMS_STEP(    0,    0,    0,  300)
        TEX_PAN_PARAMS_FREQ(    0,    0,    0,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Return
    End
};

EvtScript EVS_Main = {
    Switch(GB_StoryProgress)
        CaseEq(STORY_INTRO)
            Call(SpawnSunEffect, FX_SUN_FROM_RIGHT)
            Call(MakeNpcs, false, IntroNPCs)
        CaseGe(STORY_EPILOGUE)
            Call(SpawnSunEffect, FX_SUN_FROM_LEFT)
            Call(MakeNpcs, false, EpilogueNPCs)
    EndSwitch
    Call(GetEntryID, LVar0)
    IfNe(LVar0, $Invitation.index)
        Exec(EVS_SetupMusic)
    EndIf
    Call(GetEntryID, LVar0)
    IfNe(LVar0, $Invitation.index)
        Exec(EVS_TexPan_Fountain)
        Call(PlaySoundAtF, SOUND_LOOP_OSR_FOUNTAIN_INTACT, SOUND_SPACE_WITH_DEPTH, 300, 0, 400)
    EndIf
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
