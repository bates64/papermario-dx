#include "osr_00.h"
#include "ld_addrs.h"
#include "charset/charset.h"
#include "model.h"

#include "sprite/npc/Luigi.h"


API_CALLABLE(SetModelRemapTint) {
    Bytecode* args = script->ptrReadPos;
    s32 primR = *args++;
    s32 primG = *args++;
    s32 primB = *args++;
    s32 envR = *args++;
    s32 envG = *args++;
    s32 envB = *args++;
    mdl_set_remap_tint_params(primR, primG, primB, envR, envG, envB);
    return ApiStatus_DONE2;
}

BSS IMG_BIN PeachLetterImg[charset_peach_letter_png_width * charset_peach_letter_png_height];
BSS PAL_BIN PeachLetterPal[0x100];

BSS MessageImageData MsgImage;

API_CALLABLE(LoadPeachLetterImage) {
    u8* romStart = charset_ROM_START;
    u8* rasterOffset = charset_peach_letter_OFFSET;
    u16* paletteOffset = charset_peach_letter_pal_OFFSET;

    dma_copy(romStart + (s32)rasterOffset, romStart + (s32)rasterOffset + sizeof(PeachLetterImg), &PeachLetterImg);
    dma_copy(romStart + (s32)paletteOffset, romStart + (s32)paletteOffset + sizeof(PeachLetterPal), &PeachLetterPal);

    MsgImage.raster   = PeachLetterImg;
    MsgImage.palette  = PeachLetterPal;
    MsgImage.width    = charset_peach_letter_png_width;
    MsgImage.height   = charset_peach_letter_png_height;
    MsgImage.format   = G_IM_FMT_CI;
    MsgImage.bitDepth = G_IM_SIZ_8b;
    set_message_images(&MsgImage);
    return ApiStatus_DONE2;
}

EvtScript EVS_Scene_ShowInvitation = {
    Call(DisablePlayerInput, true)
    Call(UseSettingsFrom, CAM_DEFAULT, 0, 0, 0)
    Call(SetPanTarget, CAM_DEFAULT, 0, 0, 0)
    Call(SetCamSpeed, CAM_DEFAULT, Float(90.0))
    Call(SetCamDistance, CAM_DEFAULT, 775)
    Call(SetCamPitch, CAM_DEFAULT, 20, -19)
    Call(PanToTarget, CAM_DEFAULT, 0, true)
    Call(SetModelTintMode, APPLY_TINT_BG, nullptr, ENV_TINT_REMAP)
    Call(SetModelTintMode, APPLY_TINT_GROUPS, -1, ENV_TINT_REMAP)
    Call(SetModelRemapTint, 200, 200, 200, 40, 40, 40)
    Call(LoadPeachLetterImage)
    Wait(15 * DT)
    Call(ShowMessageAtScreenPos, MSG_Intro_0022, 160, 40)
    Wait(12 * DT)
    Call(ShowMessageAtScreenPos, MSG_Intro_0023, 160, 40)
    Wait(3)
    Call(GotoMapSpecial, Ref("kmr_20"), kmr_20_ENTRY_1, TRANSITION_SLOW_FADE_TO_WHITE)
    Wait(40 * DT)
    Return
    End
};

EvtScript EVS_Scene_ApproachParty = {
    Call(DisablePlayerInput, true)
    Call(UseSettingsFrom, CAM_DEFAULT, 0, 0, 0)
    Call(SetPanTarget, CAM_DEFAULT, 0, 0, 0)
    Call(SetCamDistance, CAM_DEFAULT, Float(675.0))
    Call(SetCamPitch, CAM_DEFAULT, Float(3.5), Float(-6.0))
    Call(SetCamPosA, CAM_DEFAULT, Float(60.0), 0)
    Call(SetCamSpeed, CAM_DEFAULT, Float(90.0))
    Call(PanToTarget, CAM_DEFAULT, 0, true)
    Thread
        Call(PlayerMoveTo, 0, -250, 150 * DT)
    EndThread
    Thread
        Call(SetNpcAnimation, NPC_Luigi, ANIM_Luigi_RunBack)
        Call(SetNpcPos, NPC_Luigi, 0, 0, 350)
        Call(NpcMoveTo, NPC_Luigi, 0, -200, 150 * DT)
        Call(SetNpcAnimation, NPC_Luigi, ANIM_Luigi_IdleBack)
    EndThread
    Wait(100 * DT)
    Call(GotoMap, Ref("kkj_00"), kkj_00_ENTRY_5)
    Wait(100 * DT)
    Call(DisablePlayerInput, false)
    Return
    End
};
