#include "kkj_14.h"
#include "world/area/kkj/kkj_01.h"
#include "world/area/kkj/kkj_11.h"
#include "world/area/kkj/kkj_15.h"
#include "world/area/kkj/kkj_26.h"
#include "world/area/kkj/kkj_27.h"
#include "world/area/pra/pra_01.h"

#include "../common/RestoreFromPeachState.inc.c"

API_CALLABLE(EnableParasol) {
    gGameStatusPtr->peachFlags |= PEACH_FLAG_HAS_PARASOL;
    return ApiStatus_DONE2;
}

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

EvtScript EVS_EndPeachChapter7 = {
    Set(LVar0, GB_KKJ_LastPartner)
    Call(RestoreFromPeachState)
    Call(PlaySound, SOUND_SLIDE_WHISTLE_OUT)
    Call(GotoMapSpecial, $pra_01.PeachInterlude, TRANSITION_END_PEACH_INTERLUDE)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitDoor_GrandHall = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Set(AF_KKJ14_CaughtUsingDoor, true)
    Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
    Set(LVar0, $UpperHall.index)
    Set(LVar1, COLLIDER_ttw)
    Set(LVar2, MODEL_o4)
    Set(LVar3, DOOR_SWING_IN)
    Exec(ExitSingleDoor)
    Wait(17)
    IfEq(GB_StoryProgress, STORY_INTRO)
        Call(GotoMap, $kkj_01.PeachsRoom)
    Else
        Call(GotoMap, $kkj_11.PeachsRoom)
    EndIf
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitDoors_Balcony = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Call(DisablePlayerInput, true)
    Set(AF_KKJ14_CaughtUsingDoor, false)
    Call(UseDoorSounds, DOOR_SOUNDS_DOOR)
    Set(LVar0, $Balcony.index)
    Set(LVar1, COLLIDER_tte)
    Set(LVar2, MODEL_o83)
    Set(LVar3, MODEL_o85)
    Set(LVar4, MODEL_o84)
    Set(LVar5, MODEL_o86)
    Exec(ExitSplitDoubleDoor)
    Wait(17)
    Call(GotoMap, $kkj_26.PeachsRoom)
    Wait(100)
    Return
    End
};

EvtScript EVS_ExitWalk_SecretPassage = {
    SetGroup(EVT_GROUP_EXIT_MAP)
    Set(AF_KKJ14_CaughtUsingDoor, false)
    Call(UseExitHeading, 60, $SecretPassage.index)
    Exec(ExitWalk)
    IfEq(GF_KKJ14_SkipSecretPassage, false)
        Call(GotoMap, $kkj_27.PeachsRoom)
    Else
        Call(GotoMap, $kkj_15.SecretPassage)
    EndIf
    Wait(100)
    Return
    End
};

EvtScript EVS_ShowMessage_CantOpen = {
    Call(DisablePlayerInput, true)
    Call(ShowMessageAtScreenPos, MSG_Menus_Inspect_DoesntOpen, 160, 40)
    Call(DisablePlayerInput, false)
    Return
    End
};

EvtScript EVS_BindExitTriggers = {
    IfEq(GB_StoryProgress, STORY_INTRO)
        BindTrigger(EVS_ShowMessage_CantOpen, TRIGGER_WALL_PRESS_A, COLLIDER_tte, 1, 0)
    Else
        BindTrigger(EVS_ExitDoors_Balcony, TRIGGER_WALL_PRESS_A, COLLIDER_tte, 1, 0)
        BindTrigger(EVS_ExitWalk_SecretPassage, TRIGGER_FLOOR_ABOVE, COLLIDER_o119, 1, 0)
    EndIf
    BindTrigger(EVS_ExitDoor_GrandHall, TRIGGER_WALL_PRESS_A, COLLIDER_ttw, 1, 0)
    Return
    End
};

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($UpperHall.index)
            Call(UseDoorSounds, DOOR_SOUNDS_BASIC)
            Set(LVar2, MODEL_o4)
            Set(LVar3, DOOR_SWING_IN)
            ExecWait(EnterSingleDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq($Balcony.index)
            Call(UseDoorSounds, DOOR_SOUNDS_DOOR)
            Set(LVar2, MODEL_o83)
            Set(LVar3, MODEL_o85)
            Set(LVar4, MODEL_o84)
            Set(LVar5, MODEL_o86)
            ExecWait(EnterSplitDoubleDoor)
            Exec(EVS_BindExitTriggers)
        CaseEq($SecretPassage.index)
            Set(LVar0, EVS_BindExitTriggers)
            Exec(EnterWalk)
        CaseEq($Chapter0.index)
            Exec(EVS_Scene_Chapter0)
        CaseEq($Chapter1.index)
            Exec(EVS_Scene_Chapter1)
            Exec(EVS_BindExitTriggers)
        CaseEq($Chapter2.index)
            Exec(EVS_Scene_Chapter2)
            Exec(EVS_BindExitTriggers)
        CaseEq($Chapter3.index)
            Exec(EVS_Scene_Chapter3)
            Exec(EVS_BindExitTriggers)
        CaseEq($Chapter4.index)
            Exec(EVS_Scene_Chapter4)
            Exec(EVS_BindExitTriggers)
        CaseEq($Chapter5.index)
            Exec(EVS_Scene_Chapter5)
            Exec(EVS_BindExitTriggers)
        CaseEq($Chapter6.index)
            Exec(EVS_Scene_Chapter6)
            Exec(EVS_BindExitTriggers)
        CaseEq($Chapter7.index)
            Exec(EVS_Scene_Chapter7)
        CaseEq($TossedBack.index)
            Exec(EVS_Scene_TossedBackInRoom)
            Exec(EVS_BindExitTriggers)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_PEACHS_CASTLE)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Call(GetEntryID, LVar0)
    IfGe(LVar0, $Chapter0.index)
        IfNe(LVar0, $TossedBack.index)
            Set(GF_KKJ14_RevealedButton, false)
            Set(GF_KKJ14_OpenedPassage, false)
        EndIf
        Switch(LVar0)
            CaseEq($Chapter0.index)
                Set(GB_StoryProgress, STORY_CH0_BEGAN_PEACH_MISSION)
                Set(GB_KKJ_CaughtCount, 0)
                Set(GF_KKJ14_SkipSecretPassage, false)
                Call(MakeNpcs, false, Chapter0NPCs)
            CaseEq($Chapter1.index)
                Set(GB_StoryProgress, STORY_CH1_BEGAN_PEACH_MISSION)
                Set(GB_KKJ_CaughtCount, 0)
                Set(GF_KKJ14_SkipSecretPassage, false)
            CaseEq($Chapter2.index)
                Set(GB_StoryProgress, STORY_CH2_BEGAN_PEACH_MISSION)
                Set(GB_KKJ_CaughtCount, 0)
                Set(GF_KKJ14_SkipSecretPassage, false)
                Set(AF_KKJ_PeachSawGrandHall, false)
                Call(MakeNpcs, false, Chapter2NPCs)
            CaseEq($Chapter3.index)
                Set(GB_StoryProgress, STORY_CH3_BEGAN_PEACH_MISSION)
                Set(GB_KKJ_CaughtCount, 0)
                Set(GF_KKJ14_SkipSecretPassage, false)
            CaseEq($Chapter4.index)
                Set(GB_StoryProgress, STORY_CH4_BEGAN_PEACH_MISSION)
                Set(GB_KKJ_CaughtCount, 0)
                Set(GF_KKJ14_SkipSecretPassage, true)
            CaseEq($Chapter5.index)
                Set(GB_StoryProgress, STORY_CH5_BEGAN_PEACH_MISSION)
                Set(GB_KKJ_CaughtCount, 0)
                Set(GF_KKJ14_SkipSecretPassage, true)
            CaseEq($Chapter6.index)
                Call(EnableParasol)
                Set(GB_StoryProgress, STORY_CH6_BEGAN_PEACH_MISSION)
                Set(GB_KKJ_CaughtCount, 0)
                Set(GF_KKJ14_SkipSecretPassage, true)
            CaseEq($Chapter7.index)
                Call(MakeNpcs, false, Chapter7NPCs)
            CaseEq($TossedBack.index)
                Add(GB_KKJ_CaughtCount, 1)
                Call(MakeNpcs, false, TossBackNPCs)
        EndSwitch
    EndIf
    Exec(EVS_SetupInteractables)
    Call(GetEntryID, LVar0)
    IfNe(LVar0, $Chapter2.index)
        Exec(EVS_SetupMusic)
    EndIf
    Exec(EVS_EnterMap)
    Call(SetTexPanner, MODEL_o154, TEX_PANNER_0)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_0)
        TEX_PAN_PARAMS_STEP(    0,    0,   40,  900)
        TEX_PAN_PARAMS_FREQ(    1,    1,    1,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Call(SetModelCustomGfx, MODEL_o154, CUSTOM_GFX_0, ENV_TINT_UNCHANGED)
    Call(SetCustomGfx, CUSTOM_GFX_0, setup_gfx_candle_lights, nullptr)
    Return
    End
};
