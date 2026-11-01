#include "kmr_22.h"
#include "world/area/flo/flo_00.h"
#include "world/area/iwa/iwa_10.h"
#include "world/area/jan/jan_00.h"
#include "world/area/kmr/kmr_00.h"
#include "world/area/kpa/kpa_63.h"
#include "world/area/mim/mim_01.h"
#include "world/area/nok/nok_11.h"
#include "world/area/omo/omo_03.h"
#include "world/area/sam/sam_02.h"
#include "effects.h"
#include "sprite/player.h"

BSS EffectInstance* ChapterEffect;
BSS s32 ChapterEffectTime;

#if VERSION_PAL
#define CHUNK_SIZE (8)
#else
#define CHUNK_SIZE (10)
#endif

s16 AnimTextOffsets[CHUNK_SIZE * 2] = {
#if VERSION_PAL
    310, 270, 240, 210,
    180, 150, 120, 100,
     80,  50,  24,  12,
      5,   3,   2,   1,
#else
    310, 290, 270, 250, 230,
    210, 190, 170, 150, 130,
    110,  90,  70,  50,  32,
     16,   8,   4,   2,   1,
#endif
};

API_CALLABLE(ManageEffects) {
    s32 type = script->varTable[0];
    s32 x, y;
    s32 xOffset = 0;

    if (type == 0) {
        type = 9;
        xOffset = 38;
    }

    if (isInitialCall) {
        set_curtain_scale_goal(1.0f);
        ChapterEffect = fx_chapter_change(type, 100.0f, 100.0f, 0.0f, 1.0f, 0);
        ChapterEffectTime = 0;
    }

    x = xOffset + 117;
    if (ChapterEffectTime >= 0) {
        if (ChapterEffectTime < 2 * CHUNK_SIZE) {
            x -= AnimTextOffsets[ChapterEffectTime];
        }
    } else {
        x = xOffset - 193;
    }
    y = 58;
    ChapterEffect->data.chapterChange->chapterPos.x = x;
    ChapterEffect->data.chapterChange->chapterPos.y = y;

    x = xOffset + 117;
    if (ChapterEffectTime >= CHUNK_SIZE) {
        if (ChapterEffectTime < 3 * CHUNK_SIZE) {
            y -= AnimTextOffsets[ChapterEffectTime - CHUNK_SIZE];
        }
    } else {
        y = -252;
    }
    ChapterEffect->data.chapterChange->endOfPos.x = x;
    ChapterEffect->data.chapterChange->endOfPos.y = y;

    x = 280;
    if (ChapterEffectTime >= 2 * CHUNK_SIZE) {
        if (ChapterEffectTime < 4 * CHUNK_SIZE) {
            x += AnimTextOffsets[ChapterEffectTime - 2 * CHUNK_SIZE];
        }
    } else {
        x = 590;
    }
    y = 90;
    ChapterEffect->data.chapterChange->msgPos.x = x;
    ChapterEffect->data.chapterChange->msgPos.y = y;
    ChapterEffectTime++;

    return ApiStatus_BLOCK;
}

API_CALLABLE(DismissCurtains) {
    set_curtain_scale_goal(2.0f);
    return ApiStatus_DONE2;
}

API_CALLABLE(WaitForContinueInput) {
    ApiStatus ret;

    if (gGameStatusPtr->pressedButtons[0] & BUTTON_START) {
        ret = ApiStatus_DONE2;
    } else {
        ret = ApiStatus_BLOCK;
    }

    if (gGameStatusPtr->pressedButtons[0] & BUTTON_A) {
        ret = ApiStatus_DONE2;
        script->varTable[0] = -1;
    }
    return ret;
}

EvtScript EVS_EnterMap = {
    Call(GetEntryID, LVar0)
    Thread
        Call(ManageEffects)
    EndThread
    Wait(50)
    Call(WaitForContinueInput)
    Call(FadeOutMusic, 0, 2000)
    Wait(30)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($Prologue.index)
            Call(GotoMapSpecial, $kmr_00.GoombaVillage, TRANSITION_BEGIN_OR_END_CHAPTER)
        CaseEq($Chapter1.index)
            Call(GotoMapSpecial, $nok_11.ToadTown, TRANSITION_BEGIN_OR_END_CHAPTER)
        CaseEq($Chapter2.index)
            Call(GotoMapSpecial, $iwa_10.Train, TRANSITION_BEGIN_OR_END_CHAPTER)
        CaseEq($Chapter3.index)
            Call(GotoMapSpecial, $mim_01.West, TRANSITION_BEGIN_OR_END_CHAPTER)
        CaseEq($Chapter4.index)
            Call(GotoMapSpecial, $omo_03.ToadTown, TRANSITION_BEGIN_OR_END_CHAPTER)
        CaseEq($Chapter5.index)
            Call(GotoMapSpecial, $jan_00.ToadTown, TRANSITION_BEGIN_OR_END_CHAPTER)
        CaseEq($Chapter6.index)
            Call(GotoMapSpecial, $flo_00.ToadTown, TRANSITION_BEGIN_OR_END_CHAPTER)
        CaseEq($Chapter7.index)
            Call(GotoMapSpecial, $sam_02.Pipe, TRANSITION_BEGIN_OR_END_CHAPTER)
        CaseEq($Chapter8.index)
            Call(GotoMapSpecial, $kpa_63.Starship, TRANSITION_BEGIN_OR_END_CHAPTER)
    EndSwitch
    Call(DismissCurtains)
    Wait(100)
    Return
    End
};

EvtScript EVS_Main = {
    Call(DisablePlayerInput, true)
    Call(DisablePlayerPhysics, true)
    Call(GetEntryID, LVar0)
    IfEq(LVar0, $Prologue.index)
        Call(SetPlayerPos, -200, 0, 0)
    Else
        Call(SetPlayerPos, -95, 0, 0)
    EndIf
    Call(SetPlayerFlagBits, PS_FLAG_NO_FLIPPING, true)
    Call(InterpPlayerYaw, 90, 0)
    Wait(1)
    Call(SetPlayerAnimation, ANIM_Mario1_BeforeJump)
    Call(GetCurrentPartnerID, LVar0)
    IfNe(LVar0, PARTNER_NONE)
        Call(DisablePartnerAI, false)
        Call(SetNpcFlagBits, NPC_PARTNER, NPC_FLAG_GRAVITY, false)
        Call(SetNpcPos, NPC_PARTNER, NPC_DISPOSE_LOCATION)
    EndIf
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(208, 208, 208)
    Call(SetCamType, CAM_DEFAULT, CAM_CONTROL_FIXED_POS_AND_ORIENTATION, false)
    Call(SetCamPitch, CAM_DEFAULT, 0, 0)
    Call(SetCamDistance, CAM_DEFAULT, 440)
    Call(SetCamPosA, CAM_DEFAULT, 0, 100)
    Call(SetCamPosB, CAM_DEFAULT, 0, 0)
    Call(SetCamPosC, CAM_DEFAULT, 0, 65)
    Call(SetPanTarget, CAM_DEFAULT, 0, 0, 0)
    Call(SetCamSpeed, CAM_DEFAULT, 90.0)
    Call(PanToTarget, CAM_DEFAULT, 0, true)
    Call(GetEntryID, LVar0)
    Switch(LVar0)
        CaseEq($Chapter1.index)
            Call(MakeNpcs, false, NpcGroup_Chapter1)
        CaseEq($Chapter2.index)
            Call(MakeNpcs, false, NpcGroup_Chapter2)
        CaseEq($Chapter3.index)
            Call(MakeNpcs, false, NpcGroup_Chapter3)
        CaseEq($Chapter4.index)
            Call(MakeNpcs, false, NpcGroup_Chapter4)
        CaseEq($Chapter5.index)
            Call(MakeNpcs, false, NpcGroup_Chapter5)
        CaseEq($Chapter6.index)
            Call(MakeNpcs, false, NpcGroup_Chapter6)
        CaseEq($Chapter7.index)
            Call(MakeNpcs, false, NpcGroup_Chapter7)
        CaseEq($Chapter8.index)
            Call(MakeNpcs, false, NpcGroup_Chapter8)
    EndSwitch
    Call(DisablePlayerInput, true)
    Call(DisablePlayerPhysics, true)
    Wait(1)
    Exec(EVS_EnterMap)
    Call(SetMusic, 0, SONG_CHAPTER_START, 0, VOL_LEVEL_FULL)
    Call(ClearAmbientSounds, 250)
    Return
    End
};
