#include "kkj_15.h"
#include "world/area/arn/arn_07.h"
#include "world/area/kkj/kkj_11.h"
#include "world/area/kmr/kmr_10.h"
#include "world/area/trd/trd_00.h"

#include "../common/RestoreFromPeachState.inc.c"

Gfx setup_gfx_candle_lights[] = {
    gsDPPipeSync(),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetPrimColor(0, 0, 75, 31, 19, 255),
    gsDPSetEnvColor(255, 118, 77, 0),
    gsDPSetCombineMode(PM_CC_CANDLE_1, PM_CC_CANDLE_2),
    gsDPSetRenderMode(G_RM_PASS, G_RM_ZB_CLD_SURF2),
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

EvtScript EVS_EndPeachChapter0 = {
    Set(LVar0, GB_KKJ_LastPartner)
    Call(RestoreFromPeachState)
    Call(PlaySound, SOUND_SLIDE_WHISTLE_OUT)
    Call(GotoMapSpecial, $kmr_10.GoombaKingsCastle, TRANSITION_END_PEACH_INTERLUDE)
    Wait(100)
    Return
    End
};

EvtScript EVS_EndPeachChapter1 = {
    Set(LVar0, GB_KKJ_LastPartner)
    Call(RestoreFromPeachState)
    Call(PlaySound, SOUND_SLIDE_WHISTLE_OUT)
    Call(GotoMapSpecial, $trd_00.PeachInterlude, TRANSITION_END_PEACH_INTERLUDE)
    Wait(100)
    Return
    End
};

EvtScript EVS_EndPeachChapter3 = {
    Set(LVar0, GB_KKJ_LastPartner)
    Call(RestoreFromPeachState)
    Call(PlaySound, SOUND_SLIDE_WHISTLE_OUT)
    Call(GotoMapSpecial, $arn_07.PeachInterlude, TRANSITION_END_PEACH_INTERLUDE)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitDoor_kkj_11_3 =
    EVT_EXIT_SINGLE_DOOR($UpperHall, $kkj_11.PassageOutlet, COLLIDER_tte, MODEL_o2, DOOR_SWING_IN);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitDoor_kkj_11_3, TRIGGER_WALL_PRESS_A, COLLIDER_tte, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($UpperHall.index)
            Set(LVar2, MODEL_o2)
            Set(LVar3, DOOR_SWING_IN)
            ExecWait(EnterSingleDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq($SecretPassage.index)
            Switch(GB_StoryProgress)
                CaseEq(STORY_CH1_BEGAN_PEACH_MISSION)
                    Exec(EVS_EnterRotatingWall)
                    Exec(EVS_SetupChapter1)
                CaseEq(STORY_CH2_BEGAN_PEACH_MISSION)
                    Exec(EVS_EnterRotatingWall)
                    Exec(EVS_SetupChapter2)
                CaseEq(STORY_CH3_BEGAN_PEACH_MISSION)
                    Exec(EVS_Scene_Chapter3)
                CaseDefault
                    Exec(EVS_EnterRotatingWall)
                    Exec(EVS_BindExitTriggers)
            EndSwitch
        CaseEq($Interlude.index)
            Exec(EVS_Scene_Chapter0_BowserAndKammy)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_PEACHS_CASTLE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($Interlude.index)
            Set(GB_StoryProgress, STORY_CH0_KAMMY_RETURNED_TO_BOWSER)
    EndSwitch
    Switch(GB_StoryProgress)
        CaseEq(STORY_CH0_KAMMY_RETURNED_TO_BOWSER)
            Call(MakeNpcs, false, Chapter0NPCs)
        CaseEq(STORY_CH1_BEGAN_PEACH_MISSION)
            Call(MakeNpcs, false, Chapter1NPCs)
        CaseEq(STORY_CH3_BEGAN_PEACH_MISSION)
            Call(MakeNpcs, false, Chapter3NPCs)
    EndSwitch
    IfNe(GB_StoryProgress, STORY_CH1_BEGAN_PEACH_MISSION)
        Call(EnableModel, MODEL_o76, false)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_o76, COLLIDER_FLAGS_UPPER_MASK)
    EndIf
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_g25, COLLIDER_FLAGS_UPPER_MASK)
    Call(SetTexPanner, MODEL_o151, TEX_PANNER_0)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_0)
        TEX_PAN_PARAMS_STEP(    0,    0,   40,  900)
        TEX_PAN_PARAMS_FREQ(    1,    1,    1,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Call(SetModelCustomGfx, MODEL_o151, CUSTOM_GFX_0, ENV_TINT_UNCHANGED)
    Call(SetCustomGfx, CUSTOM_GFX_0, setup_gfx_candle_lights, nullptr)
    Call(SetTexPanner, MODEL_o152, TEX_PANNER_0)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_0)
        TEX_PAN_PARAMS_STEP(    0,    0,   40,  900)
        TEX_PAN_PARAMS_FREQ(    1,    1,    1,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Call(SetModelCustomGfx, MODEL_o152, CUSTOM_GFX_0, ENV_TINT_UNCHANGED)
    Call(SetCustomGfx, CUSTOM_GFX_0, setup_gfx_candle_lights, nullptr)
    Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
    Exec(EVS_SetupMusic)
    Call(GetEntryID, LVar0)
    IfEq(LVar0, $SecretPassage.index)
        IfEq(GB_StoryProgress, STORY_CH3_BEGAN_PEACH_MISSION)
            Call(StopSound, SOUND_KKJ_ROTATING_WALL)
        Else
            Call(PlaySoundAt, SOUND_KKJ_ROTATING_WALL, SOUND_SPACE_DEFAULT, 50, 5, -200)
        EndIf
        Wait(10)
    EndIf
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
