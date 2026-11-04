#include "kkj_13.h"
#include "world/area/kkj/kkj_12.h"
#include "world/area/kkj/kkj_22.h"

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

EvtScript EVS_ExitDoors_kkj_12_1 =
    EVT_EXIT_DOUBLE_DOOR($StairsHallway, $kkj_12.WindowHallway, COLLIDER_deilit1, MODEL_door1, MODEL_door2);
EvtScript EVS_ExitDoors_kkj_22_0 =
    EVT_EXIT_DOUBLE_DOOR($DoubleStaircase, $kkj_22.WindowHallway, COLLIDER_deilit2, MODEL_door4, MODEL_door3);

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($StairsHallway.index)
            Set(LVar2, MODEL_door1)
            Set(LVar3, MODEL_door2)
            ExecWait(EnterDoubleDoor)
            Exec(EVS_Scene_MarioConfrontsBowser)
        CaseEq($DoubleStaircase.index)
            Set(LVar2, MODEL_door4)
            Set(LVar3, MODEL_door3)
            ExecWait(EnterDoubleDoor)
        CaseEq($BowserAttacks.index)
            Exec(EVS_Scene_BowserAttacks)
        CaseEq($PeachCaptured.index)
            Exec(EVS_Scene_PeachCaptured)
    EndSwitch
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_PEACHS_CASTLE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    IfEq(GB_StoryProgress, STORY_INTRO)
        Call(MakeNpcs, false, IntroNPCs)
    EndIf
    IfGe(GB_StoryProgress, STORY_CH8_OPENED_PATH_TO_STAR_WAY)
        Call(MakeNpcs, false, ChapterNPCs)
    EndIf
    Call(GetEntryID, LVar0)
    IfEq(LVar0, $BowserAttacks.index)
        Call(EnableGroup, MODEL_g152, false)
        Call(EnableGroup, MODEL_g154, false)
        Call(EnableGroup, MODEL_g153, false)
    Else
        Call(EnableGroup, MODEL_g133, false)
        Call(EnableGroup, MODEL_g147, false)
        Call(EnableGroup, MODEL_g153, false)
    EndIf
    IfGe(GB_StoryProgress, STORY_CH8_OPENED_PATH_TO_STAR_WAY)
        IfEq(GF_KKJ13_BowserTaunts, false)
            Call(EnableGroup, MODEL_g153, true)
            Call(TranslateGroup, MODEL_g153, 780, 90, 0)
            Call(RotateGroup, MODEL_g153, -60, 0, 1, 0)
        EndIf
    EndIf
    Call(SetTexPanner, MODEL_o685, TEX_PANNER_0)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_0)
        TEX_PAN_PARAMS_STEP(    0,    0,   40,  900)
        TEX_PAN_PARAMS_FREQ(    1,    1,    1,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(EVS_UpdateTexturePan)
    EndThread
    Call(SetModelCustomGfx, MODEL_o685, CUSTOM_GFX_0, ENV_TINT_UNCHANGED)
    Call(SetCustomGfx, CUSTOM_GFX_0, setup_gfx_candle_lights, nullptr)
    Exec(EVS_SetupMusic)
    BindTrigger(EVS_ExitDoors_kkj_12_1, TRIGGER_WALL_PRESS_A, COLLIDER_deilit1, 1, 0)
    BindTrigger(EVS_ExitDoors_kkj_22_0, TRIGGER_WALL_PRESS_A, COLLIDER_deilit2, 1, 0)
    Exec(EVS_EnterMap)
    Wait(1)
    Return
    End
};
