#include "common.h"
#include "hud_element.h"
#include "nu/nusys.h"
#include "ld_addrs.h"

#define MAX_HUD_CACHE_ENTRIES 192

typedef struct HudElementSize {
    s16 width;
    s16 height;
    s16 size;
} HudElementSize;

u8* HudElemAuxCache = NULL;
s32 HudElemCacheCapacity = 0x11000;

HudScript HES_Empty = {
    hs_End
};

HudElementSize HudElemSizes[] = {
    { 8, 8, 32 },
    { 16, 16, 128 },
    { 24, 24, 288 },
    { 32, 32, 512 },
    { 48, 48, 1152 },
    { 64, 64, 2048 },
    { 8, 16, 64 },
    { 16, 8, 64 },
    { 16, 24, 192 },
    { 16, 32, 256 },
    { 64, 32, 1024 },
    { 32, 16, 256 },
    { 12, 12, 72 },
    { 48, 24, 576 },
    { 32, 8, 128 },
    { 24, 8, 96 },
    { 64, 16, 512 },
    { 16, 64, 512 },
    { 192, 32, 3072 },
    { 40, 40, 800 },
    { 24, 16, 192 },
    { 32, 40, 640 },
    { 40, 16, 320 },
    { 40, 24, 480 },
    { 32, 24, 384 },
    { 20, 32, 0 }
};

Gfx HudElemBackInitGfx[] = {
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT),
    gsDPPipeSync(),
    gsSPSetOtherMode(G_SETOTHERMODE_H, G_MDSFT_ALPHADITHER, 18, G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsSPEndDisplayList()
};
Gfx HudElemFrontInitGfx[] = {
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT),
    gsDPPipeSync(),
    gsSPSetOtherMode(G_SETOTHERMODE_H, G_MDSFT_ALPHADITHER, 18, G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsSPEndDisplayList()
};

Vtx HudElemTemplateQuad[] = {
    {
        .v = {
            .ob = { -12, 0, 0},
            .flag = 0,
            .tc = { 0x800, 0x800 },
            .cn = { 0, 0, 0, 255}
        }
    },
    {
        .v = {
            .ob = { 51, 0, 0},
            .flag = 0,
            .tc = { 0, 0x800 },
            .cn = { 0, 0, 0, 255}
        }
    },
    {
        .v = {
            .ob = { 51, 63, 0},
            .flag = 0,
            .tc = { 0, 0 },
            .cn = { 0, 0, 0, 255}
        }
    },
    {
        .v = {
            .ob = { -12, 63, 0},
            .flag = 0,
            .tc = { 0x800, 0 },
            .cn = { 0, 0, 0, 255}
        }
    }
};

Lights1 HudElemLights = gdSPDefLights1(255, 255, 255, 0, 0, 0, 0, 0, 0);

s32 HudElemCount;
HudCacheEntry* gHudElementCacheTableRaster;
HudCacheEntry* gHudElementCacheTablePalette;
s32* gHudElementCacheSize;
u8* gHudElementCacheBuffer;

BSS HudElementList gHudElementsWorld;
BSS HudElementList gHudElementsBattle;
BSS HudElementList* gHudElements;
BSS u8* gHudElementCacheBufferWorld;
BSS s32 gHudElementCacheSizeWorld;
BSS HudCacheEntry gHudElementCacheTableRasterWorld[MAX_HUD_CACHE_ENTRIES];
BSS HudCacheEntry gHudElementCacheTablePaletteWorld[MAX_HUD_CACHE_ENTRIES];
BSS u8* gHudElementCacheBufferBattle;
BSS s32 gHudElementCacheSizeBattle;
BSS HudCacheEntry gHudElementCacheTableRasterBattle[MAX_HUD_CACHE_ENTRIES];
BSS HudCacheEntry gHudElementCacheTablePaletteBattle[MAX_HUD_CACHE_ENTRIES];
BSS s32 FrameQuadIndex;

void hud_element_setup_cam(void);

void hud_element_load_script(HudElement* hudElement, HudScript* anim) {
    s32* pos = (s32*)anim;
    s32 raster;
    s32 palette;
    s32 preset;
    HudCacheEntry* entry;
    s32 i;
    s32 capacity;

    if (pos == NULL) {
        return;
    }

    preset = 0;

    while (TRUE) {
        switch (*pos++) {
            case HUD_ELEMENT_OP_End:
                return;
            case HUD_ELEMENT_OP_SetCI:
                pos += 3;
                break;
            case HUD_ELEMENT_OP_SetTileSize:
                preset = *pos++;
                hudElement->drawSizePreset = hudElement->tileSizePreset = preset;
                break;
            case HUD_ELEMENT_OP_SetSizesAutoScale:
            case HUD_ELEMENT_OP_SetSizesFixedScale:
                preset = *pos;
                pos += 2;
                hudElement->drawSizePreset = hudElement->tileSizePreset = preset;
                break;
            case HUD_ELEMENT_OP_SetCustomSize:
                hudElement->customDrawSize.x = hudElement->customImageSize.x = *pos++;
                hudElement->customDrawSize.y = hudElement->customImageSize.y = *pos++;
                hudElement->flags |= HUD_ELEMENT_FLAG_CUSTOM_SIZE;
                break;
            case HUD_ELEMENT_OP_AddTexelOffsetX:
            case HUD_ELEMENT_OP_AddTexelOffsetY:
            case HUD_ELEMENT_OP_SetScale:
            case HUD_ELEMENT_OP_SetAlpha:
            case HUD_ELEMENT_OP_SetVariable:
            case HUD_ELEMENT_OP_RandomBranch:
            case HUD_ELEMENT_OP_SetFlags:
            case HUD_ELEMENT_OP_ClearFlags:
            case HUD_ELEMENT_OP_PlaySound:
                pos++;
                break;
            case HUD_ELEMENT_OP_SetRGBA:
            case HUD_ELEMENT_OP_SetTexelOffset:
            case HUD_ELEMENT_OP_RandomDelay:
            case HUD_ELEMENT_OP_RandomRestart:
            case HUD_ELEMENT_OP_SetPivot:
                pos += 2;
                break;
            case HUD_ELEMENT_OP_SetImage:
                pos++;
                raster = *pos++;
                palette = *pos++;

                i = 0;
                entry = gHudElementCacheTableRaster;
                while (TRUE) {
                    if (entry->id == -1) {
                        entry->id = raster;
                        entry->data = &gHudElementCacheBuffer[*gHudElementCacheSize];
                        if (gGameStatusPtr->context == CONTEXT_WORLD) {
                            capacity = HudElemCacheCapacity;
                        } else {
                            capacity = HudElemCacheCapacity / 2;
                        }
                        ASSERT(capacity > *gHudElementCacheSize + HudElemSizes[preset].size);
                        nuPiReadRom((s32)icon_ROM_START + raster, entry->data, HudElemSizes[preset].size);
                        *gHudElementCacheSize += HudElemSizes[preset].size;
                        if (gGameStatusPtr->context == CONTEXT_WORLD) {
                            *pos = i;
                        } else {
                            *pos = (u16)(*pos) | (i << 16);
                        }
                        i++;
                        break;
                    } else if (entry->id == raster) {
                        if (gGameStatusPtr->context == CONTEXT_WORLD) {
                            *pos = i;
                        } else {
                            *pos = (u16)(*pos) | (i << 16);
                        }
                        break;
                    }
                    entry++;
                    i++;
                }

                pos++;
                ASSERT(i < MAX_HUD_CACHE_ENTRIES);

                entry = gHudElementCacheTablePalette;
                i = 0;
                while (TRUE) {
                    if (entry->id == -1) {
                        entry->id = palette;
                        entry->data = &gHudElementCacheBuffer[*gHudElementCacheSize];
                        if (gGameStatusPtr->context == CONTEXT_WORLD) {
                            capacity = HudElemCacheCapacity;
                        } else {
                            capacity = HudElemCacheCapacity / 2;
                        }
                        ASSERT(capacity > *gHudElementCacheSize + 32);
                        nuPiReadRom((s32)icon_ROM_START + palette, entry->data, 32);
                        *gHudElementCacheSize += 32;
                        if (gGameStatusPtr->context == CONTEXT_WORLD) {
                            *pos = i;
                        } else {
                            *pos = (u16)(*pos) | (i << 16);
                        }
                        i++;
                        break;
                    } else if (entry->id == palette) {
                        if (gGameStatusPtr->context == CONTEXT_WORLD) {
                            *pos = i;
                        } else {
                            *pos = (u16)(*pos) | (i << 16);
                        }
                        break;
                    }
                    entry++;
                    i++;
                }

                pos++;
                ASSERT(i < MAX_HUD_CACHE_ENTRIES);
                break;
        }
    }
}

// render a basic rect for a non-transformed hud element
void hud_element_draw_rect(HudElement* hudElement, s16 texSizeX, s16 texSizeY, s16 drawSizeX, s16 drawSizeY,
                           s16 offsetX, s16 offsetY, s32 clamp, s32 dropShadow) {
    s32 flipX, flipY;
    s32 fmt;
    s32 widthScale, heightScale;
    s32 texStartX, texStartY;
    b32 isLastTileX, isLastTileY;
    s32 uls, ult, lrs, lrt;
    s32 uly, lry, ulx, lrx;
    s32 masks, maskt;
    s32 screenPosOffsetScaledX, screenPosOffsetScaledY;
    IMG_PTR imageAddr;
    PAL_PTR paletteAddr;
    s16 baseX, baseY;
    s32 tileMode;
    u16 renderPosX, renderPosY;

    imageAddr = hudElement->imageAddr;
    paletteAddr = hudElement->paletteAddr;

    screenPosOffsetScaledX = hudElement->screenPosOffset.x * 1024;
    screenPosOffsetScaledY = hudElement->screenPosOffset.y * 1024;
    widthScale = hudElement->widthScale;
    screenPosOffsetScaledX /= widthScale;
    heightScale = hudElement->heightScale;
    screenPosOffsetScaledY /= heightScale;

    renderPosX = hudElement->worldPosOffset.x;
    renderPosY = hudElement->worldPosOffset.y;
    renderPosX += hudElement->renderPosX + screenPosOffsetScaledX;
    renderPosY += hudElement->renderPosY + screenPosOffsetScaledY;

    baseX = offsetX + renderPosX;
    baseY = offsetY + renderPosY;

    if (dropShadow) {
        baseX += 2;
        baseY += 2;
    }

    flipX = (hudElement->flags & HUD_ELEMENT_FLAG_FLIPX) != 0;
    flipY = (hudElement->flags & HUD_ELEMENT_FLAG_FLIPY) != 0;

    fmt = 0; // RGBA
    if (hudElement->flags & HUD_ELEMENT_FLAG_FMT_CI4) {
        fmt = 1; // CI
    }
    if (hudElement->flags & HUD_ELEMENT_FLAG_FMT_IA8) {
        fmt = 2; // IA
    }

    masks = 6;
    maskt = 5;
    if (!(hudElement->flags & HUD_ELEMENT_FLAG_SCALED)) {
        switch (drawSizeX) {
            case 8:
                masks = 3;
                break;
            case 16:
                masks = 4;
                break;
            case 32:
                masks = 5;
                break;
        }

        switch (drawSizeY) {
            case 8:
                maskt = 3;
                break;
            case 16:
                maskt = 4;
                break;
            case 32:
                maskt = 5;
                break;
        }
    }

    switch (fmt) {
        case 0:
            gDPSetRenderMode(gMainGfxPos++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
            gDPSetTextureLUT(gMainGfxPos++, G_TT_NONE);
            break;
        case 1:
            if (hudElement->flags & HUD_ELEMENT_FLAG_TRANSPARENT) {
                if (hudElement->flags & HUD_ELEMENT_FLAG_ANTIALIASING) {
                    gDPSetRenderMode(gMainGfxPos++, G_RM_CLD_SURF | AA_EN, G_RM_CLD_SURF2 | AA_EN);
                } else {
                    gDPSetRenderMode(gMainGfxPos++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
                }
            } else {
                if (hudElement->flags & HUD_ELEMENT_FLAG_ANTIALIASING) {
                    gDPSetRenderMode(gMainGfxPos++, G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2);
                } else {
                    gDPSetRenderMode(gMainGfxPos++, G_RM_TEX_EDGE, G_RM_TEX_EDGE2);
                }
            }
            gDPSetTextureLUT(gMainGfxPos++, G_TT_RGBA16);
            gDPLoadTLUT_pal16(gMainGfxPos++, 0, paletteAddr);
            break;
        case 2:
            gDPSetRenderMode(gMainGfxPos++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
            gDPSetTextureLUT(gMainGfxPos++, G_TT_NONE);
            break;
    }

    if (hudElement->flags & HUD_ELEMENT_FLAG_FILTER_TEX) {
        gDPSetTextureFilter(gMainGfxPos++, G_TF_AVERAGE);
    } else {
        gDPSetTextureFilter(gMainGfxPos++, G_TF_POINT);
    }

    ult = 0;
    isLastTileY = FALSE;
    uly = baseY;
    while (TRUE) {
        lry = uly + 1024.0 / heightScale * 32.0;
        lrt = ult + 31;
        if (flipY) {
            texStartY = texSizeY;
        } else {
            texStartY = 0;
        }

        if (lry < 0 || uly > SCREEN_HEIGHT) {
            break;
        }

        if (lry >= SCREEN_HEIGHT) {
            lrt = SCREEN_HEIGHT - baseY - 1;
            lry = SCREEN_HEIGHT;
            isLastTileY = TRUE;
        }

        if (lrt + 1 >= texSizeY) {
            lrt = texSizeY - 1;
            if (texSizeY > 16) {
                lry = baseY + drawSizeY - 1;
            } else {
                lry = baseY + drawSizeY;
            }
            isLastTileY = TRUE;
        }

        isLastTileX = FALSE;
        uls = 0;
        ulx = baseX;
        while (TRUE) {
            lrx = ulx + 1024.0 / widthScale * 64.0;
            lrs = uls + 63;
            if (flipX) {
                texStartX = texSizeX;
            } else {
                texStartX = 0;
            }

            if (lrx < 0  || ulx > SCREEN_WIDTH) {
                break;
            }

            if (lrx >= SCREEN_WIDTH) {
                lrs = SCREEN_WIDTH - baseX - 1;
                lrx = SCREEN_WIDTH;
                isLastTileX = TRUE;
            }

            if (lrs + 1 >= texSizeX) {
                lrs = texSizeX - 1;
                if (texSizeX > 16) {
                    lrx = baseX + drawSizeX - 1;
                } else {
                    lrx = baseX + drawSizeX;
                }
                isLastTileX = TRUE;
            }

            gDPPipeSync(gMainGfxPos++);

            if (!isLastTileX && !isLastTileY) {
                tileMode = 0; // middle tile
            }
            if (isLastTileX && !isLastTileY) {
                tileMode = 1; // horizontal edge tile
            }
            if (!isLastTileX && isLastTileY) {
                tileMode = 2; // vertical edge tile
            }
            if (isLastTileX && isLastTileY) {
                tileMode = 3; // corner tile
            }

            switch (fmt) {
                case 0:
                    if (hudElement->flags & HUD_ELEMENT_FLAG_TRANSPARENT) {
                        gDPSetCombineMode(gMainGfxPos++, PM_CC_01, PM_CC_02);
                    } else {
                        gDPSetCombineMode(gMainGfxPos++, G_CC_DECALRGBA, G_CC_DECALRGBA);
                    }

                    if (hudElement->flags & HUD_ELEMENT_FLAG_TRANSPARENT) {
                        gDPSetPrimColor(gMainGfxPos++, 0, 0, 0, 0, 0, hudElement->opacity);
                    }

                    if (!flipX && !flipY) {
                        gDPLoadTextureTile(gMainGfxPos++, imageAddr, G_IM_FMT_RGBA, G_IM_SIZ_32b, texSizeX, texSizeY, uls, ult, lrs, lrt, 0,
                                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
                    } else {
                        gDPLoadTextureTile(gMainGfxPos++, imageAddr, G_IM_FMT_RGBA, G_IM_SIZ_32b, texSizeX, texSizeY, uls, ult, lrs, lrt, 0,
                                            G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP, masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
                    }
                    break;
                case 1:
                    if (!dropShadow) {
                        if (hudElement->flags & HUD_ELEMENT_FLAG_TRANSPARENT) {
                            gDPSetCombineMode(gMainGfxPos++, PM_CC_2F, PM_CC_32);
                        } else {
                            gDPSetCombineMode(gMainGfxPos++, PM_CC_2F, PM_CC_32);
                        }

                        if (hudElement->flags & HUD_ELEMENT_FLAG_TRANSPARENT) {
                            gDPSetPrimColor(gMainGfxPos++, 0, 0, hudElement->tint.r, hudElement->tint.g, hudElement->tint.b, hudElement->opacity);
                        } else {
                            gDPSetPrimColor(gMainGfxPos++, 0, 0, hudElement->tint.r, hudElement->tint.g, hudElement->tint.b, 255);
                        }
                    } else {
                        gDPSetRenderMode(gMainGfxPos++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
                        gDPSetCombineMode(gMainGfxPos++, PM_CC_07, PM_CC_07);
                        gDPSetPrimColor(gMainGfxPos++, 0, 0, 40, 40, 40, 72);
                    }

                    if (!flipX && !flipY) {
                        if (!clamp) {
                            gDPLoadTextureTile_4b(gMainGfxPos++, imageAddr, G_IM_FMT_CI, texSizeX, texSizeY, uls, ult, lrs, lrt, 0,
                                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
                        } else {
                            switch (tileMode) {
                                case 0:
                                    gDPLoadTextureTile_4b(gMainGfxPos++, imageAddr, G_IM_FMT_CI, texSizeX, texSizeY, uls, ult, lrs, lrt, 0,
                                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
                                    break;
                                case 1:
                                    gDPLoadTextureTile_4b(gMainGfxPos++, imageAddr, G_IM_FMT_CI, texSizeX, texSizeY, uls, ult, lrs, lrt, 0,
                                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
                                    break;
                                case 2:
                                    gDPLoadTextureTile_4b(gMainGfxPos++, imageAddr, G_IM_FMT_CI, texSizeX, texSizeY, uls, ult, lrs, lrt, 0,
                                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
                                    break;
                                case 3:
                                    gDPLoadTextureTile_4b(gMainGfxPos++, imageAddr, G_IM_FMT_CI, texSizeX, texSizeY, uls, ult, lrs, lrt, 0,
                                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
                                    break;
                            }
                        }
                    } else {
                        gDPLoadTextureTile_4b(gMainGfxPos++, imageAddr, G_IM_FMT_CI, texSizeX, texSizeY, uls, ult, lrs, lrt, 0,
                                            G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP, masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
                    }
                    break;
                case 2:
                    gDPSetCombineMode(gMainGfxPos++, PM_CC_47, PM_CC_47);
                    gDPSetPrimColor(gMainGfxPos++, 0, 0, hudElement->tint.r, hudElement->tint.g, hudElement->tint.b, hudElement->opacity);

                    if (!flipX && !flipY) {
                        if (!clamp) {
                            switch (tileMode) {
                                case 0:
                                    gDPLoadTextureTile(gMainGfxPos++, imageAddr, G_IM_FMT_IA, G_IM_SIZ_8b, texSizeX, texSizeY, uls, ult, lrs, lrt, 0,
                                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
                                    break;
                                case 1:
                                    gDPLoadTextureTile(gMainGfxPos++, imageAddr, G_IM_FMT_IA, G_IM_SIZ_8b, texSizeX, texSizeY, uls, ult, lrs, lrt, 0,
                                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
                                    break;
                                case 2:
                                    gDPLoadTextureTile(gMainGfxPos++, imageAddr, G_IM_FMT_IA, G_IM_SIZ_8b, texSizeX, texSizeY, uls, ult, lrs, lrt, 0,
                                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
                                    break;
                                case 3:
                                    gDPLoadTextureTile(gMainGfxPos++, imageAddr, G_IM_FMT_IA, G_IM_SIZ_8b, texSizeX, texSizeY, uls, ult, lrs, lrt, 0,
                                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
                                    break;
                            }
                        } else {
                            gDPLoadTextureTile(gMainGfxPos++, imageAddr, G_IM_FMT_IA, G_IM_SIZ_8b, texSizeX, texSizeY, uls, ult, lrs, lrt, 0,
                                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
                        }
                    } else {
                        gDPLoadTextureTile(gMainGfxPos++, imageAddr, G_IM_FMT_IA, G_IM_SIZ_8b, texSizeX, texSizeY, uls, ult, lrs, lrt, 0,
                                            G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP, masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
                    }
                    break;
            }

            if (hudElement->flags & HUD_ELEMENT_FLAG_FILTER_TEX) {
                gSPScisTextureRectangle(gMainGfxPos++, ulx * 4, uly * 4, lrx * 4, lry * 4, 0, texStartX * 32 + 16, texStartY * 32 + 16, widthScale, heightScale);
            } else {
                gSPScisTextureRectangle(gMainGfxPos++, ulx * 4, uly * 4, lrx * 4, lry * 4, 0, texStartX * 32, texStartY * 32, widthScale, heightScale);
            }
            if (isLastTileX) {
                break;
            }
            ulx += 1024.0 / widthScale * 64.0;
            uls += 64;
        }

        if (isLastTileY) {
            break;
        }

        ult += 32;
        uly += 1024.0 / heightScale * 32.0;
    }

    gDPPipeSync(gMainGfxPos++);
}

void hud_element_clear_cache(void) {
    HudCacheEntry* entryRaster;
    HudCacheEntry* entryPalette;
    s32 i;

    if (gGameStatusPtr->context == CONTEXT_WORLD) {
        gHudElements = &gHudElementsWorld;
        gHudElementCacheSize = &gHudElementCacheSizeWorld;
        gHudElementCacheTableRaster = gHudElementCacheTableRasterWorld;
        gHudElementCacheTablePalette = gHudElementCacheTablePaletteWorld;
    } else {
        gHudElements = &gHudElementsBattle;
        gHudElementCacheSize = &gHudElementCacheSizeBattle;
        gHudElementCacheTableRaster = gHudElementCacheTableRasterBattle;
        gHudElementCacheTablePalette = gHudElementCacheTablePaletteBattle;
    }

    if (gGameStatusPtr->context == CONTEXT_WORLD) {
        gHudElementCacheBuffer = general_heap_malloc(HudElemCacheCapacity);
        ASSERT(gHudElementCacheBuffer);
        gHudElementCacheBufferWorld = gHudElementCacheBuffer;
        *gHudElementCacheSize = 0;
        entryRaster = gHudElementCacheTableRaster;
        entryPalette = gHudElementCacheTablePalette;
        for (i = 0; i < MAX_HUD_CACHE_ENTRIES; i++) {
            entryRaster[i].id = -1;
            entryPalette[i].id = -1;
        }
    } else {
        if (HudElemAuxCache == NULL) {
            gHudElementCacheBuffer = general_heap_malloc(HudElemCacheCapacity / 2);
            ASSERT(gHudElementCacheBuffer);
        } else {
            gHudElementCacheBuffer = HudElemAuxCache;
        }
        gHudElementCacheBufferBattle = gHudElementCacheBuffer;
        *gHudElementCacheSize = 0;
        entryRaster = gHudElementCacheTableRaster;
        entryPalette = gHudElementCacheTablePalette;
        for (i = 0; i < MAX_HUD_CACHE_ENTRIES; i++) {
            entryRaster[i].id = -1;
            entryPalette[i].id = -1;
        }
    }

    for (i = 0; i < ARRAY_COUNT(*gHudElements); i++) {
        (*gHudElements)[i] = NULL;
    }

    HudElemCount = 0;
    FrameQuadIndex = 0;
    hud_element_setup_cam();
}

#if VERSION_PAL
extern Addr D_80200000;
#endif

void init_hud_element_list(void) {
    if (gGameStatusPtr->context == CONTEXT_WORLD) {
        if (gHudElementCacheBufferBattle != NULL) {
#if VERSION_PAL
            if (gHudElementCacheBufferBattle != D_80200000) {
                general_heap_free(gHudElementCacheBufferBattle);
            }
#else
            general_heap_free(gHudElementCacheBufferBattle);
#endif
            gHudElementCacheBufferBattle = NULL;
        }

        gHudElements = &gHudElementsWorld;
        gHudElementCacheSize = &gHudElementCacheSizeWorld;
        gHudElementCacheTableRaster = gHudElementCacheTableRasterWorld;
        gHudElementCacheTablePalette = gHudElementCacheTablePaletteWorld;
        gHudElementCacheBuffer = gHudElementCacheBufferWorld;
    } else {
        gHudElements = &gHudElementsBattle;
        gHudElementCacheSize = &gHudElementCacheSizeBattle;
        gHudElementCacheTableRaster = gHudElementCacheTableRasterBattle;
        gHudElementCacheTablePalette = gHudElementCacheTablePaletteBattle;
        gHudElementCacheBuffer = gHudElementCacheBufferBattle;
    }

    HudElemCount = 0;
    FrameQuadIndex = 0;
}

void hud_element_setup_cam(void) {
    gCameras[CAM_HUD].updateMode = CAM_UPDATE_INTERP_POS;
    gCameras[CAM_HUD].needsInit = TRUE;
    gCameras[CAM_HUD].nearClip = CAM_NEAR_CLIP;
    gCameras[CAM_HUD].farClip = 0x4000;
    gCameras[CAM_HUD].vfov = 1.0f;
    set_cam_viewport(CAM_HUD, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);

    gCameras[CAM_HUD].params.interp.pitch = 0;
    gCameras[CAM_HUD].params.interp.yaw = 0;
    gCameras[CAM_HUD].params.interp.offsetY = 0;
    gCameras[CAM_HUD].params.interp.dist = 15551;

    gCameras[CAM_HUD].lookAt_obj_target.x = SCREEN_WIDTH / 2.0f;
    gCameras[CAM_HUD].lookAt_obj_target.y = -(SCREEN_HEIGHT / 2.0f);
    gCameras[CAM_HUD].lookAt_obj_target.z = 0;

    gCameras[CAM_HUD].bgColor[0] = 0;
    gCameras[CAM_HUD].bgColor[1] = 0;
    gCameras[CAM_HUD].bgColor[2] = 0;

    gCameras[CAM_HUD].flags &= ~(CAMERA_FLAG_DISABLED | CAMERA_FLAG_LEAD_PLAYER);
}

s32 hud_element_create(HudScript* anim) {
    HudElement* hudElement;
    s32 id;

    for (id = 0; id < ARRAY_COUNT(*gHudElements); id++) {
        if ((*gHudElements)[id] == NULL) {
            break;
        }
    }

    ASSERT(id < ARRAY_COUNT(*gHudElements));

    (*gHudElements)[id] = hudElement = heap_malloc(sizeof(*hudElement));
    HudElemCount++;

    ASSERT(hudElement != NULL);

    hudElement->flags = HUD_ELEMENT_FLAG_INITIALIZED;
    hudElement->readPos = anim;
    if (anim == NULL) {
        hudElement->readPos = &HES_Empty;
    }
    hudElement->updateTimer = 1;
    hudElement->drawSizePreset = -1;
    hudElement->tileSizePreset = -1;
    hudElement->renderPosX = 0;
    hudElement->renderPosY = 0;
    hudElement->loopStartPos = anim;
    hudElement->widthScale = X10(1.0f);
    hudElement->heightScale = X10(1.0f);
    hudElement->anim = hudElement->readPos;
    hudElement->uniformScale = 1.0f;
    hudElement->screenPosOffset.x = 0;
    hudElement->screenPosOffset.y = 0;
    hudElement->worldPosOffset.x = 0;
    hudElement->worldPosOffset.y = 0;
    hudElement->worldPosOffset.z = 0;
    hudElement->opacity = 255;
    hudElement->tint.r = 255;
    hudElement->tint.g = 255;
    hudElement->tint.b = 255;

    if (gGameStatusPtr->context != CONTEXT_WORLD) {
        hudElement->flags |= HUD_ELEMENT_FLAG_BATTLE;
        id |= HUD_ELEMENT_BATTLE_ID_MASK;
    }

    hud_element_load_script(hudElement, hudElement->readPos);
    while (hud_element_update(hudElement) != 0);

    return id;
}

void update_hud_elements(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(*gHudElements); i++) {
        HudElement* elem = (*gHudElements)[i];

        if (elem == NULL || elem->flags == 0 || elem->flags & HUD_ELEMENT_FLAG_DISABLED) {
            continue;
        }

        if (elem->flags & HUD_ELEMENT_FLAG_DELETE) {
            hud_element_free(i);
            continue;
        }

        if (elem->readPos == NULL) {
            // bail out and skip updating any subsequent elements
            break;
        }

        // update the current element
        elem->updateTimer--;
        if (elem->updateTimer == 0) {
            while (hud_element_update(elem) != 0);
        }
        if (elem->flags & HUD_ELEMENT_FLAG_RESIZING) {
            elem->dynamicSize.x += elem->deltaSize.x;
            elem->dynamicSize.y += elem->deltaSize.y;
        }
    }
}

s32 hud_element_update(HudElement* hudElement) {
    HudCacheEntry* entryRaster;
    HudCacheEntry* entryPalette;
    s32 i;
    s32 drawSizePreset;
    s32 tileSizePreset;
    u8 sizePreset;
    f32 xScaled, yScaled;
    s32 imageWidth, imageHeight, drawWidth, drawHeight;
    u32 flags;
    s32 s1, s2;
    s32 arg1, arg2;
    f32 uniformScale;
    HudScript* newReadPos;

    HudTransform* hudTransform = hudElement->hudTransform;
    s32* nextPos = (s32*)hudElement->readPos;

    switch (*nextPos++) {
        case HUD_ELEMENT_OP_End:
            hudElement->updateTimer = 60;
            flags = hudElement->flags;
            hudElement->flags = flags | HUD_ELEMENT_FLAG_ANIMATION_FINISHED;
            break;
        case HUD_ELEMENT_OP_Delete:
            hudElement->updateTimer = 60;
            hudElement->flags |= HUD_ELEMENT_FLAG_DELETE;
            break;
        case HUD_ELEMENT_OP_UseIA8:
            hudElement->readPos = (HudScript*)nextPos;
            hudElement->flags |= HUD_ELEMENT_FLAG_FMT_IA8;
            return TRUE;
        case HUD_ELEMENT_OP_SetVisible:
            hudElement->readPos = (HudScript*)nextPos;
            hudElement->flags |= HUD_ELEMENT_FLAG_FMT_CI4;
            return TRUE;
        case HUD_ELEMENT_OP_SetHidden:
            hudElement->readPos = (HudScript*)nextPos;
            hudElement->flags &= ~HUD_ELEMENT_FLAG_FMT_CI4;
            return TRUE;
        case HUD_ELEMENT_OP_SetFlags:
            s1 = *nextPos++;
            hudElement->readPos = (HudScript*)nextPos;
            hudElement->flags |= s1;
            return TRUE;
        case HUD_ELEMENT_OP_ClearFlags:
            s1 = *nextPos++;
            hudElement->readPos = (HudScript*)nextPos;
            hudElement->flags &= ~s1;
            return TRUE;
        case HUD_ELEMENT_OP_SetRGBA:
            hudElement->updateTimer = *nextPos++;
            hudElement->imageAddr = (u8*)*nextPos++;
            hudElement->readPos = (HudScript*)nextPos;

            if (hudElement->flags & HUD_ELEMENT_FLAG_MEMOFFSET) {
                hudElement->imageAddr += hudElement->memOffset;
            }

            if (hudElement->flags & HUD_ELEMENT_FLAG_RESIZING) {
                if (hudElement->flags & HUD_ELEMENT_FLAG_CUSTOM_SIZE) {
                    imageWidth = hudElement->customImageSize.x;
                    imageHeight = hudElement->customImageSize.y;
                    drawWidth = hudElement->customDrawSize.x;
                    drawHeight = hudElement->customDrawSize.y;
                } else {
                    tileSizePreset = hudElement->tileSizePreset;
                    drawSizePreset = hudElement->drawSizePreset;
                    imageWidth = HudElemSizes[tileSizePreset].width;
                    imageHeight = HudElemSizes[tileSizePreset].height;
                    drawWidth = HudElemSizes[drawSizePreset].width;
                    drawHeight = HudElemSizes[drawSizePreset].height;
                }

                if (hudElement->flags & HUD_ELEMENT_FLAG_RESIZE_DIR) {
                    hudElement->flags &= ~HUD_ELEMENT_FLAG_RESIZE_DIR;
                    hudElement->dynamicSize.x = drawWidth;
                    hudElement->dynamicSize.y = drawHeight;
                    hudElement->deltaSize.x = ((f32)imageWidth - (f32)drawWidth) / (f32)hudElement->updateTimer;
                    hudElement->deltaSize.y = ((f32)imageHeight - (f32)drawHeight) / (f32)hudElement->updateTimer;
                } else {
                    hudElement->flags |= HUD_ELEMENT_FLAG_RESIZE_DIR;
                    hudElement->dynamicSize.x = imageWidth;
                    hudElement->dynamicSize.y = imageHeight;
                    hudElement->deltaSize.x = ((f32)drawWidth - (f32)imageWidth) / (f32)hudElement->updateTimer;
                    hudElement->deltaSize.y = ((f32)drawHeight - (f32)imageHeight) / (f32)hudElement->updateTimer;
                }
            }
            break;
        case HUD_ELEMENT_OP_SetCI:
            hudElement->updateTimer = *nextPos++;
            hudElement->imageAddr = (IMG_PTR)*nextPos++;
            hudElement->paletteAddr = (PAL_PTR)*nextPos++;
            hudElement->readPos = (HudScript*)nextPos;

            if (hudElement->flags & HUD_ELEMENT_FLAG_MEMOFFSET) {
                hudElement->imageAddr += hudElement->memOffset;
                hudElement->paletteAddr += hudElement->memOffset;
            }

            if (hudElement->flags & HUD_ELEMENT_FLAG_RESIZING) {
                if (hudElement->flags & HUD_ELEMENT_FLAG_CUSTOM_SIZE) {
                    imageWidth = hudElement->customImageSize.x;
                    imageHeight = hudElement->customImageSize.y;
                    drawWidth = hudElement->customDrawSize.x;
                    drawHeight = hudElement->customDrawSize.y;
                } else {
                    tileSizePreset = hudElement->tileSizePreset;
                    drawSizePreset = hudElement->drawSizePreset;
                    imageWidth = HudElemSizes[tileSizePreset].width;
                    imageHeight = HudElemSizes[tileSizePreset].height;
                    drawWidth = HudElemSizes[drawSizePreset].width;
                    drawHeight = HudElemSizes[drawSizePreset].height;
                }

                if (hudElement->flags & HUD_ELEMENT_FLAG_RESIZE_DIR) {
                    hudElement->flags &= ~HUD_ELEMENT_FLAG_RESIZE_DIR;
                    hudElement->dynamicSize.x = drawWidth;
                    hudElement->dynamicSize.y = drawHeight;
                    hudElement->deltaSize.x = ((f32)imageWidth - (f32)drawWidth) / (f32)hudElement->updateTimer;
                    hudElement->deltaSize.y = ((f32)imageHeight - (f32)drawHeight) / (f32)hudElement->updateTimer;
                } else {
                    hudElement->flags |= HUD_ELEMENT_FLAG_RESIZE_DIR;
                    hudElement->dynamicSize.x = imageWidth;
                    hudElement->dynamicSize.y = imageHeight;
                    hudElement->deltaSize.x = ((f32)drawWidth - (f32)imageWidth) / (f32)hudElement->updateTimer;
                    hudElement->deltaSize.y = ((f32)drawHeight - (f32)imageHeight) / (f32)hudElement->updateTimer;
                }
            }
            break;
        case HUD_ELEMENT_OP_SetImage:
            hudElement->updateTimer = *nextPos++;

            if (hudElement->flags & HUD_ELEMENT_FLAG_BATTLE) {
                entryRaster = gHudElementCacheTableRasterBattle;
                entryPalette = gHudElementCacheTablePaletteBattle;
            } else {
                entryRaster = gHudElementCacheTableRasterWorld;
                entryPalette = gHudElementCacheTablePaletteWorld;
            }

            i = 0;
            while (TRUE) {
                if (entryRaster[i].id == *nextPos) {
                    break;
                }
                ASSERT(++i < MAX_HUD_CACHE_ENTRIES);
            }

            nextPos++;
            hudElement->imageAddr = entryRaster[i].data;

            i = 0;
            while (TRUE) {
                if (entryPalette[i].id == *nextPos) {
                    break;
                }
                ASSERT(++i < MAX_HUD_CACHE_ENTRIES);
            }
            hudElement->paletteAddr = entryPalette[i].data;
            nextPos += 3;
            hudElement->readPos = (HudScript*)nextPos;

            if (hudElement->flags & HUD_ELEMENT_FLAG_RESIZING) {
                if (hudElement->flags & HUD_ELEMENT_FLAG_CUSTOM_SIZE) {
                    imageWidth = hudElement->customImageSize.x;
                    imageHeight = hudElement->customImageSize.y;
                    drawWidth = hudElement->customDrawSize.x;
                    drawHeight = hudElement->customDrawSize.y;
                } else {
                    tileSizePreset = hudElement->tileSizePreset;
                    drawSizePreset = hudElement->drawSizePreset;
                    imageWidth = HudElemSizes[tileSizePreset].width;
                    imageHeight = HudElemSizes[tileSizePreset].height;
                    drawWidth = HudElemSizes[drawSizePreset].width;
                    drawHeight = HudElemSizes[drawSizePreset].height;
                }

                if (hudElement->flags & HUD_ELEMENT_FLAG_RESIZE_DIR) {
                    hudElement->flags &= ~HUD_ELEMENT_FLAG_RESIZE_DIR;
                    hudElement->dynamicSize.x = drawWidth;
                    hudElement->dynamicSize.y = drawHeight;
                    hudElement->deltaSize.x = ((f32)imageWidth - (f32)drawWidth) / (f32)hudElement->updateTimer;
                    hudElement->deltaSize.y = ((f32)imageHeight - (f32)drawHeight) / (f32)hudElement->updateTimer;
                } else {
                    hudElement->flags |= HUD_ELEMENT_FLAG_RESIZE_DIR;
                    hudElement->dynamicSize.x = imageWidth;
                    hudElement->dynamicSize.y = imageHeight;
                    hudElement->deltaSize.x = ((f32)drawWidth - (f32)imageWidth) / (f32)hudElement->updateTimer;
                    hudElement->deltaSize.y = ((f32)drawHeight - (f32)imageHeight) / (f32)hudElement->updateTimer;
                }
            }
            break;
        case HUD_ELEMENT_OP_Restart:
            hudElement->readPos = hudElement->loopStartPos;
            return TRUE;
        case HUD_ELEMENT_OP_Loop:
            hudElement->loopStartPos = (HudScript*)nextPos;
            hudElement->readPos = (HudScript*)nextPos;
            return TRUE;
        case HUD_ELEMENT_OP_RandomRestart:
            s1 = *nextPos++;
            s2 = *nextPos++;
            if (rand_int(s1) < s2) {
                hudElement->readPos = hudElement->loopStartPos;
            } else {
                hudElement->readPos = (HudScript*)nextPos;
            }
            return TRUE;
        case HUD_ELEMENT_OP_SetTileSize:
            sizePreset = *nextPos++;
            hudElement->widthScale = X10(1);
            hudElement->heightScale = X10(1);
            hudElement->readPos = (HudScript*)nextPos;
            hudElement->drawSizePreset = sizePreset;
            hudElement->tileSizePreset = sizePreset;
            hudElement->flags &= ~HUD_ELEMENT_FLAG_RESIZING;
            hudElement->flags &= ~HUD_ELEMENT_FLAG_REPEATED;
            return TRUE;
        case HUD_ELEMENT_OP_SetSizesAutoScale:
            tileSizePreset = *nextPos++;
            drawSizePreset = *nextPos++;

            hudElement->readPos = (HudScript*)nextPos;
            hudElement->tileSizePreset = tileSizePreset;
            hudElement->drawSizePreset = drawSizePreset;

            imageWidth = HudElemSizes[tileSizePreset].width;
            imageHeight = HudElemSizes[tileSizePreset].height;
            drawWidth = HudElemSizes[drawSizePreset].width;
            drawHeight = HudElemSizes[drawSizePreset].height;

            xScaled = (f32) drawWidth / (f32) imageWidth;
            yScaled = (f32) drawHeight / (f32) imageHeight;

            xScaled = 1.0f / xScaled;
            yScaled = 1.0f / yScaled;

            hudElement->widthScale = X10(xScaled);
            hudElement->heightScale = X10(yScaled);

            hudElement->flags &= ~HUD_ELEMENT_FLAG_RESIZING;
            hudElement->flags |= HUD_ELEMENT_FLAG_REPEATED;
            return TRUE;
        case HUD_ELEMENT_OP_SetSizesFixedScale:
            tileSizePreset = *nextPos++;
            drawSizePreset = *nextPos++;

            hudElement->widthScale = X10(1);
            hudElement->heightScale = X10(1);
            hudElement->readPos = (HudScript*)nextPos;
            hudElement->tileSizePreset = tileSizePreset;
            hudElement->drawSizePreset = drawSizePreset;
            hudElement->flags |= HUD_ELEMENT_FLAG_RESIZING;
            hudElement->flags &= ~HUD_ELEMENT_FLAG_REPEATED;
            hudElement->flags &= ~HUD_ELEMENT_FLAG_RESIZE_DIR;
            return TRUE;
        case HUD_ELEMENT_OP_AddTexelOffsetX:
            s1 = *nextPos++;
            hudElement->readPos = (HudScript*)nextPos;
            hudElement->screenPosOffset.x += s1;
            return TRUE;
        case HUD_ELEMENT_OP_AddTexelOffsetY:
            s2 = *nextPos++;
            if (hudElement->flags & HUD_ELEMENT_FLAG_FLIPY) {
                hudElement->screenPosOffset.y -= s2;
            } else {
                hudElement->screenPosOffset.y += s2;
            }
            hudElement->readPos = (HudScript*)nextPos;
            return TRUE;
        case HUD_ELEMENT_OP_SetTexelOffset:
            s1 = *nextPos++;
            s2 = *nextPos++;
            hudElement->screenPosOffset.x = s1;
            if (hudElement->flags & HUD_ELEMENT_FLAG_FLIPY) {
                hudElement->screenPosOffset.y = -s2;
            } else {
                hudElement->screenPosOffset.y = s2;
            }
            hudElement->readPos = (HudScript*)nextPos;
            return TRUE;
        case HUD_ELEMENT_OP_SetScale:
            uniformScale = (f32)*nextPos++;
            uniformScale /= 65536;
            hudElement->uniformScale = uniformScale;
            if (hudElement->flags & HUD_ELEMENT_FLAG_CUSTOM_SIZE) {
                imageWidth = hudElement->customImageSize.x;
                imageHeight = hudElement->customImageSize.y;
                drawWidth = hudElement->customDrawSize.x;
                drawHeight = hudElement->customDrawSize.y;
            } else {
                imageWidth = HudElemSizes[hudElement->tileSizePreset].width;
                imageHeight = HudElemSizes[hudElement->tileSizePreset].height;
                drawWidth = HudElemSizes[hudElement->drawSizePreset].width;
                drawHeight = HudElemSizes[hudElement->drawSizePreset].height;
            }

            hudElement->sizeX = drawWidth * uniformScale;
            hudElement->sizeY = drawHeight * uniformScale;

            xScaled = (f32) drawWidth / (f32) imageWidth * uniformScale;
            yScaled = (f32) drawHeight / (f32) imageHeight * uniformScale;

            xScaled = 1.0f / xScaled;
            yScaled = 1.0f / yScaled;

            hudElement->widthScale = X10(xScaled);
            hudElement->heightScale = X10(yScaled);

            hudElement->readPos = (HudScript*)nextPos;
            hudElement->flags &= ~HUD_ELEMENT_FLAG_RESIZING;
            hudElement->flags |= HUD_ELEMENT_FLAG_REPEATED | HUD_ELEMENT_FLAG_SCALED;
            return TRUE;
        case HUD_ELEMENT_OP_SetAlpha:
            s1 = *nextPos++;
            hudElement->opacity = s1;
            hudElement->flags |= HUD_ELEMENT_FLAG_TRANSPARENT;
            if (hudElement->opacity == 255) {
                hudElement->flags &= ~HUD_ELEMENT_FLAG_TRANSPARENT;
            }
            hudElement->readPos = (HudScript*)nextPos;
            return TRUE;
        case HUD_ELEMENT_OP_RandomDelay:
            s1 = *nextPos++;
            s2 = *nextPos++;
            hudElement->updateTimer = rand_int(s2 - s1) + s1;
            hudElement->readPos = (HudScript*)nextPos;
            break;
        case HUD_ELEMENT_OP_SetCustomSize:
            hudElement->customDrawSize.x = hudElement->customImageSize.x = *nextPos++;
            hudElement->customDrawSize.y = hudElement->customImageSize.y = *nextPos++;
            hudElement->readPos = (HudScript*)nextPos;
            hudElement->widthScale = X10(1);
            hudElement->heightScale = X10(1);
            hudElement->drawSizePreset = 0;
            hudElement->tileSizePreset = 0;
            hudElement->flags &= ~HUD_ELEMENT_FLAG_RESIZING;
            hudElement->flags &= ~HUD_ELEMENT_FLAG_REPEATED;
            hudElement->flags |= HUD_ELEMENT_FLAG_CUSTOM_SIZE;
            return TRUE;
        case HUD_ELEMENT_OP_SetVariable:
            s1 = *nextPos++;
            hudElement->readPos = (HudScript*)nextPos;
            hudElement->flags &= ~HUD_ELEMENT_VARIABLE_MASK;
            hudElement->flags |= s1 << 24;
            return TRUE;
        case HUD_ELEMENT_OP_RandomBranch:
            s1 = *nextPos++;
            newReadPos = (HudScript*)nextPos[rand_int(s1 - 1)];
            hudElement->readPos = newReadPos;
            hud_element_load_script(hudElement, newReadPos);
            return TRUE;
        case HUD_ELEMENT_OP_PlaySound:
            arg2 = *nextPos++;
            sfx_play_sound(arg2);
            hudElement->readPos = (HudScript*)nextPos;
            return TRUE;
        case HUD_ELEMENT_OP_SetPivot:
            arg1 = *nextPos++;
            arg2 = *nextPos++;
            hudElement->readPos = (HudScript*)nextPos;
            if (hudElement->flags & HUD_ELEMENT_FLAG_TRANSFORM) {
                hudTransform->pivot.x = arg1;
                hudTransform->pivot.y = arg2;
            }
            return TRUE;
        case HUD_ELEMENT_OP_op_16:
            break;
    }

    return FALSE;
}

void render_hud_elements_backUI(void) {
    s32 i, count, j;
    s32 sortedElements[ARRAY_COUNT(*gHudElements)];
    s32 el1, el2;
    s32 texSizeX, texSizeY;
    s32 drawSizeX, drawSizeY, offsetX, offsetY;
    HudElement* elem;

    FrameQuadIndex++;
    if (FrameQuadIndex >= ARRAY_COUNT(elem->hudTransform->quadBuffers)) {
        FrameQuadIndex = 0;
    }
    gSPDisplayList(gMainGfxPos++, VIRTUAL_TO_PHYSICAL(HudElemBackInitGfx));

    // gather appropriate hud elements
    count = 0;
    for (i = 0; i < ARRAY_COUNT(*gHudElements); i++) {
        elem = (*gHudElements)[i];
        if (elem == NULL) {
            continue;
        }

        if (elem->flags == 0 || elem->flags & HUD_ELEMENT_FLAG_DISABLED) {
            continue;
        }

        if (elem->flags & (HUD_ELEMENT_FLAG_INVISIBLE | HUD_ELEMENT_FLAG_HIDDEN)) {
            continue;
        }

        if (elem->flags & HUD_ELEMENT_FLAG_MANUAL_RENDER) {
            continue;
        }

        if (elem->flags & HUD_ELEMENT_FLAG_TRANSFORM) {
            continue;
        }

        if (elem->flags & (HUD_ELEMENT_FLAG_BATTLE_CAM)) {
            continue;
        }

        if (elem->flags & HUD_ELEMENT_FLAG_FRONTUI || elem->drawSizePreset < 0) {
            continue;
        }

        // add element to list
        sortedElements[count++] = i;
    }

    // sort elements by depth
    for (i = 0; i < count - 1; i++) {
        for (j = i + 1; j < count; j++) {
            el1 = sortedElements[i];
            el2 = sortedElements[j];
            if ((*gHudElements)[el1]->worldPosOffset.z < (*gHudElements)[el2]->worldPosOffset.z) {
                sortedElements[i] = el2;
                sortedElements[j] = el1;
            }
        }
    }

    // render the sorted elements
    for (i = 0; i < count; i++) {
        elem = (*gHudElements)[sortedElements[i]];

        if (elem->readPos == NULL) {
            break;
        }

        if (!(elem->flags & HUD_ELEMENT_FLAG_RESIZING)) {
            if (elem->flags & HUD_ELEMENT_FLAG_CUSTOM_SIZE) {
                texSizeX = elem->customImageSize.x;
                texSizeY = elem->customImageSize.y;
            } else {
                texSizeX = HudElemSizes[elem->tileSizePreset].width;
                texSizeY = HudElemSizes[elem->tileSizePreset].height;
            }

            if (elem->flags & HUD_ELEMENT_FLAG_SCALED) {
                drawSizeX = elem->sizeX;
                drawSizeY = elem->sizeY;
            } else if (elem->flags & HUD_ELEMENT_FLAG_CUSTOM_SIZE) {
                drawSizeX = elem->customDrawSize.x;
                drawSizeY = elem->customDrawSize.y;
            } else {
                drawSizeX = HudElemSizes[elem->drawSizePreset].width;
                drawSizeY = HudElemSizes[elem->drawSizePreset].height;
            }

            offsetX = -drawSizeX / 2;
            offsetY = -drawSizeY / 2;

            if (elem->flags & HUD_ELEMENT_FLAG_REPEATED) {
                if (elem->flags & HUD_ELEMENT_FLAG_DROP_SHADOW) {
                    hud_element_draw_rect(elem, texSizeX, texSizeY, drawSizeX, drawSizeY, offsetX, offsetY, FALSE, TRUE);
                }
                hud_element_draw_rect(elem, texSizeX, texSizeY, drawSizeX, drawSizeY, offsetX, offsetY, FALSE, FALSE);
            } else {
                if (elem->flags & HUD_ELEMENT_FLAG_DROP_SHADOW) {
                    hud_element_draw_rect(elem, texSizeX, texSizeY, drawSizeX, drawSizeY, offsetX, offsetY, TRUE, TRUE);
                }
                hud_element_draw_rect(elem, texSizeX, texSizeY, drawSizeX, drawSizeY, offsetX, offsetY, TRUE, FALSE);
            }
        } else {
            f32 xScaled, yScaled;

            if (elem->flags & HUD_ELEMENT_FLAG_CUSTOM_SIZE) {
                texSizeX = elem->customImageSize.x;
                texSizeY = elem->customImageSize.y;
            } else {
                texSizeX = HudElemSizes[elem->tileSizePreset].width;
                texSizeY = HudElemSizes[elem->tileSizePreset].height;
            }

            drawSizeX = elem->dynamicSize.x;
            drawSizeY = elem->dynamicSize.y;

            offsetX = -elem->dynamicSize.x / 2;
            offsetY = -elem->dynamicSize.y / 2;

            xScaled = (f32) drawSizeX / (f32) texSizeX;
            yScaled = (f32) drawSizeY / (f32) texSizeY;

            xScaled = 1.0f / xScaled;
            yScaled = 1.0f / yScaled;

            elem->widthScale = X10(xScaled);
            elem->heightScale = X10(yScaled);

            if (elem->flags & HUD_ELEMENT_FLAG_DROP_SHADOW) {
                hud_element_draw_rect(elem, texSizeX, texSizeY, drawSizeX, drawSizeY, offsetX, offsetY, FALSE, TRUE);
            }
            hud_element_draw_rect(elem, texSizeX, texSizeY, drawSizeX, drawSizeY, offsetX, offsetY, FALSE, FALSE);
        }
    }
}

void render_hud_elements_frontUI(void) {
    s32 i, count, j;
    s32 sortedElements[ARRAY_COUNT(*gHudElements)];
    s32 el1, el2;
    s32 texSizeX, texSizeY;
    s32 drawSizeX, drawSizeY, offsetX, offsetY;
    HudElement* elem;

    gSPDisplayList(gMainGfxPos++, VIRTUAL_TO_PHYSICAL(HudElemFrontInitGfx));

    // gather appropriate hud elements
    count = 0;
    for (i = 0; i < ARRAY_COUNT(*gHudElements); i++) {
        elem = (*gHudElements)[i];
        if (elem == NULL) {
            continue;
        }

        if (elem->flags == 0 || elem->flags & HUD_ELEMENT_FLAG_DISABLED) {
            continue;
        }

        if (elem->flags & (HUD_ELEMENT_FLAG_INVISIBLE | HUD_ELEMENT_FLAG_HIDDEN)) {
            continue;
        }

        if (elem->flags & HUD_ELEMENT_FLAG_MANUAL_RENDER) {
            continue;
        }

        if (elem->flags & HUD_ELEMENT_FLAG_TRANSFORM) {
            continue;
        }

        if (!(elem->flags & HUD_ELEMENT_FLAG_FRONTUI) || elem->drawSizePreset < 0) {
            continue;
        }

        // add element to list
        sortedElements[count++] = i;
    }

    // sort elements by depth
    for (i = 0; i < count - 1; i++) {
        for (j = i + 1; j < count; j++) {
            el1 = sortedElements[i];
            el2 = sortedElements[j];
            if ((*gHudElements)[el1]->worldPosOffset.z < (*gHudElements)[el2]->worldPosOffset.z) {
                sortedElements[i] = el2;
                sortedElements[j] = el1;
            }
        }
    }

    // render the sorted elements
    for (i = 0; i < count; i++) {
        elem = (*gHudElements)[sortedElements[i]];
        if (!(elem->flags & HUD_ELEMENT_FLAG_RESIZING)) {
            if (elem->flags & HUD_ELEMENT_FLAG_CUSTOM_SIZE) {
                texSizeX = elem->customImageSize.x;
                texSizeY = elem->customImageSize.y;
            } else {
                texSizeX = HudElemSizes[elem->tileSizePreset].width;
                texSizeY = HudElemSizes[elem->tileSizePreset].height;
            }

            if (elem->flags & HUD_ELEMENT_FLAG_SCALED) {
                drawSizeX = elem->sizeX;
                drawSizeY = elem->sizeY;
                offsetX = -drawSizeX / 2;
                offsetY = -drawSizeY / 2;
            } else if (elem->flags & HUD_ELEMENT_FLAG_CUSTOM_SIZE) {
                drawSizeX = elem->customDrawSize.x;
                drawSizeY = elem->customDrawSize.y;
                offsetX = -drawSizeX / 2;
                offsetY = -drawSizeY / 2;
            } else {
                drawSizeX = HudElemSizes[elem->drawSizePreset].width;
                drawSizeY = HudElemSizes[elem->drawSizePreset].height;
                offsetX = -drawSizeX / 2;
                offsetY = -drawSizeY / 2;
            }

            if (elem->flags & HUD_ELEMENT_FLAG_REPEATED) {
                if (elem->flags & HUD_ELEMENT_FLAG_DROP_SHADOW) {
                    hud_element_draw_rect(elem, texSizeX, texSizeY, drawSizeX, drawSizeY, offsetX, offsetY, FALSE, TRUE);
                }
                hud_element_draw_rect(elem, texSizeX, texSizeY, drawSizeX, drawSizeY, offsetX, offsetY, FALSE, FALSE);
            } else {
                if (elem->flags & HUD_ELEMENT_FLAG_DROP_SHADOW) {
                    hud_element_draw_rect(elem, texSizeX, texSizeY, drawSizeX, drawSizeY, offsetX, offsetY, TRUE, TRUE);
                }
                hud_element_draw_rect(elem, texSizeX, texSizeY, drawSizeX, drawSizeY, offsetX, offsetY, TRUE, FALSE);
            }
        } else {
            f32 xScaled, yScaled;

            if (elem->flags & HUD_ELEMENT_FLAG_CUSTOM_SIZE) {
                texSizeX = elem->customImageSize.x;
                texSizeY = elem->customImageSize.y;
            } else {
                texSizeX = HudElemSizes[elem->drawSizePreset].width;
                texSizeY = HudElemSizes[elem->drawSizePreset].height;
            }

            drawSizeX = elem->dynamicSize.x;
            drawSizeY = elem->dynamicSize.y;

            offsetX = -elem->dynamicSize.x / 2;
            offsetY = -elem->dynamicSize.y / 2;

            xScaled = (f32) drawSizeX / (f32) texSizeX;
            yScaled = (f32) drawSizeY / (f32) texSizeY;

            xScaled = 1.0f / xScaled;
            yScaled = 1.0f / yScaled;

            elem->widthScale = X10(xScaled);
            elem->heightScale = X10(yScaled);

            if (elem->flags & HUD_ELEMENT_FLAG_DROP_SHADOW) {
                hud_element_draw_rect(elem, texSizeX, texSizeY, drawSizeX, drawSizeY, offsetX, offsetY, FALSE, TRUE);
            }
            hud_element_draw_rect(elem, texSizeX, texSizeY, drawSizeX, drawSizeY, offsetX, offsetY, FALSE, FALSE);
        }
    }
}

void render_complex_hud_element(HudElement* elem) {
    Matrix4f mtxTemp;
    Matrix4f mtxOut;
    Matrix4f mtxRot;
    Matrix4f mtxRotX;
    Matrix4f mtxRotY;
    Matrix4f mtxRotZ;
    Matrix4f mtxTrans;
    Matrix4f mtxPivotOn;
    Matrix4f mtxPivotOff;
    Matrix4f mtxScale;
    ImgFXTexture ifxImg;
    f32 xScaleFactor, yScaleFactor;
    s32 height, width;
    HudTransform* transform;
    s32 mode;
    PAL_PTR palette;
    Vtx* vtx;

    if (elem->flags & HUD_ELEMENT_FLAG_FILTER_TEX) {
        gDPSetTextureFilter(gMainGfxPos++, G_TF_AVERAGE);
    } else {
        gDPSetTextureFilter(gMainGfxPos++, G_TF_POINT);
    }

    if (elem->flags & HUD_ELEMENT_FLAG_RESIZING) {
        if (elem->flags & HUD_ELEMENT_FLAG_CUSTOM_SIZE) {
            xScaleFactor = elem->customImageSize.x;
            yScaleFactor = elem->customImageSize.y;
        } else {
            xScaleFactor = HudElemSizes[elem->tileSizePreset].width;
            yScaleFactor = HudElemSizes[elem->tileSizePreset].height;
        }
        xScaleFactor = elem->dynamicSize.x / xScaleFactor;
        yScaleFactor = elem->dynamicSize.y / yScaleFactor;
    } else {
        xScaleFactor = 1.0f;
        yScaleFactor = 1.0f;
    }

    if (elem->flags & HUD_ELEMENT_FLAG_CUSTOM_SIZE) {
        width = elem->customImageSize.x;
        height = elem->customImageSize.y;
    } else {
        width = HudElemSizes[elem->tileSizePreset].width;
        height = HudElemSizes[elem->tileSizePreset].height;
    }

    transform = elem->hudTransform;

    guTranslateF(mtxPivotOn, transform->pivot.x, -transform->pivot.y, 0.0f);
    guTranslateF(mtxPivotOff, -transform->pivot.x, transform->pivot.y, 0.0f);
    guTranslateF(
        mtxTrans,
        transform->pos.x + elem->worldPosOffset.x + elem->renderPosX + elem->screenPosOffset.x,
        transform->pos.y + elem->worldPosOffset.y - elem->renderPosY - elem->screenPosOffset.y,
        transform->pos.z - (elem->worldPosOffset.z / 10.0)
    );
    guScaleF(mtxScale, elem->uniformScale * xScaleFactor * transform->scale.x,
                    elem->uniformScale * yScaleFactor * transform->scale.y,
                    transform->scale.z);
    guRotateF(mtxRotX, transform->rot.x, 1.0f, 0.0f, 0.0f);
    guRotateF(mtxRotY, transform->rot.y, 0.0f, 1.0f, 0.0f);
    guRotateF(mtxRotZ, transform->rot.z, 0.0f, 0.0f, 1.0f);
    // combine rotations (possibly with pivot) and scale
    guMtxCatF(mtxRotZ, mtxRotX, mtxTemp);
    guMtxCatF(mtxTemp, mtxRotY, mtxRot);
    guMtxCatF(mtxScale, mtxPivotOn, mtxTemp);
    guMtxCatF(mtxTemp, mtxRot, mtxOut);
    guMtxCatF(mtxOut, mtxPivotOff, mtxTemp);
    // add translation
    guMtxCatF(mtxTemp, mtxTrans, mtxOut);
    guMtxF2L(mtxOut, &gDisplayContext->matrixStack[gMatrixListPos]);
    gSPMatrix(gMainGfxPos++, VIRTUAL_TO_PHYSICAL(&gDisplayContext->matrixStack[gMatrixListPos++]),
              G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    mode = 0;
    if (elem->flags & HUD_ELEMENT_FLAG_FMT_CI4) {
        mode = 1;
    }
    if (elem->flags & HUD_ELEMENT_FLAG_FMT_IA8) {
        mode = 2;
    }

    switch (mode) {
        case 1:
            if (elem->flags & HUD_ELEMENT_FLAG_NO_FOLD) {
                if (elem->flags & HUD_ELEMENT_FLAG_TRANSPARENT) {
                    imgfx_update(0, IMGFX_SET_ALPHA, 255, 255, 255, elem->opacity, 0);
                } else {
                    imgfx_update(0, IMGFX_CLEAR, 0, 0, 0, 0, 0);
                }
            } else {
                if (elem->flags & HUD_ELEMENT_FLAG_TRANSPARENT) {
                    imgfx_update(transform->imgfxIdx, IMGFX_SET_ALPHA, 255, 255, 255, elem->opacity, 0);
                } else {
                    imgfx_update(transform->imgfxIdx, IMGFX_CLEAR, 0, 0, 0, 0, 0);
                }
            }

            ifxImg.raster = elem->imageAddr;
            palette = elem->paletteAddr;
            ifxImg.width = width;
            ifxImg.height = height;
            ifxImg.xOffset = -width / 2;
            ifxImg.yOffset = height / 2;
            ifxImg.alpha = 255;
            ifxImg.palette = palette;

            if (elem->flags & HUD_ELEMENT_FLAG_NO_FOLD) {
                if (elem->flags & HUD_ELEMENT_FLAG_ANTIALIASING) {
                    imgfx_appendGfx_component(0, &ifxImg, IMGFX_FLAG_40, mtxOut);
                } else {
                    imgfx_appendGfx_component(0, &ifxImg, IMGFX_FLAG_40, mtxOut);
                }
            } else {
                imgfx_appendGfx_component(transform->imgfxIdx, &ifxImg, IMGFX_FLAG_40, mtxOut);
            }
            break;
        case 2:
            transform->quadBuffers[FrameQuadIndex].vtx[0] = HudElemTemplateQuad[0];
            transform->quadBuffers[FrameQuadIndex].vtx[1] = HudElemTemplateQuad[1];
            transform->quadBuffers[FrameQuadIndex].vtx[2] = HudElemTemplateQuad[2];
            transform->quadBuffers[FrameQuadIndex].vtx[3] = HudElemTemplateQuad[3];

            vtx = transform->quadBuffers[FrameQuadIndex].vtx;

            vtx[0].v.ob[0] = -width / 2;
            vtx[0].v.ob[1] = -height / 2;
            vtx[0].v.ob[2] = 0;
            vtx[0].v.tc[0] = 0;
            vtx[0].v.tc[1] = height * 32;

            vtx[1].v.ob[0] = (width / 2) - 1;
            vtx[1].v.ob[1] = -height / 2;
            vtx[1].v.ob[2] = 0;
            vtx[1].v.tc[0] = width * 32;
            vtx[1].v.tc[1] = height * 32;

            vtx[2].v.ob[0] = (width / 2) - 1;
            vtx[2].v.ob[1] = (height / 2) - 1;
            vtx[2].v.ob[2] = 0;
            vtx[2].v.tc[0] = width * 32;
            vtx[2].v.tc[1] = 0;

            vtx[3].v.ob[0] = -width / 2;
            vtx[3].v.ob[1] = (height / 2) - 1;
            vtx[3].v.ob[2] = 0;
            vtx[3].v.tc[0] = 0;
            vtx[3].v.tc[1] = 0;

            gDPPipeSync(gMainGfxPos++);
            gDPSetCombineMode(gMainGfxPos++, PM_CC_47, PM_CC_47);
            gDPSetPrimColor(gMainGfxPos++, 0, 0, elem->tint.r, elem->tint.g, elem->tint.b, elem->opacity);

            if (elem->flags & HUD_ELEMENT_FLAG_TRANSPARENT) {
                if (elem->flags & HUD_ELEMENT_FLAG_ANTIALIASING) {
                    gDPSetRenderMode(gMainGfxPos++, AA_EN | G_RM_CLD_SURF, AA_EN | G_RM_CLD_SURF2);
                } else {
                    gDPSetRenderMode(gMainGfxPos++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
                }
            } else {
                if (elem->flags & HUD_ELEMENT_FLAG_ANTIALIASING) {
                    gDPSetRenderMode(gMainGfxPos++, G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2);
                } else {
                    gDPSetRenderMode(gMainGfxPos++, G_RM_TEX_EDGE, G_RM_TEX_EDGE2);
                }
            }

            gDPLoadTextureBlock(gMainGfxPos++, elem->imageAddr, G_IM_FMT_IA, G_IM_SIZ_8b, width, height, 0,
                                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);

            gDPSetTextureLUT(gMainGfxPos++, G_TT_NONE);
            gSPVertex(gMainGfxPos++, &transform->quadBuffers[FrameQuadIndex], 4, 0);
            gSP1Triangle(gMainGfxPos++, 0, 1, 2, 0);
            gSP1Triangle(gMainGfxPos++, 0, 2, 3, 0);
            break;
    }

    gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
    gDPPipeSync(gMainGfxPos++);
}

s32 gather_and_sort_hud_elements(s32* sortedElements, b32 isBattle)
{
    HudElement* elem;
    s32 el1, el2;
    s32 count;
    s32 i, j;

    count = 0;
    for (i = 0; i < ARRAY_COUNT(*gHudElements); i++) {
        elem = (*gHudElements)[i];
        if (elem == NULL) {
            continue;
        }

        if (elem->flags == 0 || elem->flags & HUD_ELEMENT_FLAG_DISABLED) {
            continue;
        }

        if (elem->flags & (HUD_ELEMENT_FLAG_INVISIBLE | HUD_ELEMENT_FLAG_HIDDEN)) {
            continue;
        }

        if (elem->flags & HUD_ELEMENT_FLAG_MANUAL_RENDER) {
            continue;
        }

        if (!(elem->flags & HUD_ELEMENT_FLAG_TRANSFORM)) {
            continue;
        }

        if (!isBattle) {
            if (elem->flags & HUD_ELEMENT_FLAG_BATTLE_CAM) {
                continue;
            }
        } else {
            if (!(elem->flags & HUD_ELEMENT_FLAG_BATTLE_CAM)) {
                continue;
            }
        }

        if (elem->flags & HUD_ELEMENT_FLAG_FRONTUI || elem->drawSizePreset < 0) {
            continue;
        }

        // add element to list
        sortedElements[count++] = i;
    }

    // sort elements by depth
    if (count != 0) {
        for (i = 0; i < count - 1; i++) {
            for (j = i + 1; j < count; j++) {
                el1 = sortedElements[i];
                el2 = sortedElements[j];

                if ((*gHudElements)[el1]->worldPosOffset.z < (*gHudElements)[el2]->worldPosOffset.z) {
                    sortedElements[i] = el2;
                    sortedElements[j] = el1;
                }
            }
        }
    }

    return count;
}

void render_transformed_hud_elements(void) {
    s32 sortedElements[ARRAY_COUNT(*gHudElements)];
    HudElement* hudElement;
    s32 flags;
    s32 count, i;

    if (gCurrentCamID == CAM_HUD) {
        count = gather_and_sort_hud_elements(sortedElements, FALSE);

        if (count != 0) {
            gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, SCREEN_XMIN, SCREEN_YMIN, SCREEN_XMAX, SCREEN_YMAX);
            gDPPipeSync(gMainGfxPos++);
            gSPClearGeometryMode(gMainGfxPos++, G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH);
            gSPSetGeometryMode(gMainGfxPos++, G_ZBUFFER | G_SHADE | G_LIGHTING | G_SHADING_SMOOTH);
            gSPSetLights1(gMainGfxPos++, HudElemLights);
            gSPTexture(gMainGfxPos++, -1, -1, 0, G_TX_RENDERTILE, G_ON);
            gDPSetAlphaCompare(gMainGfxPos++, G_AC_NONE);
            gSPSetOtherMode(gMainGfxPos++, G_SETOTHERMODE_H, G_MDSFT_ALPHADITHER, 18, G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE);

            for (i = 0; i < count; i++) {
                render_complex_hud_element((*gHudElements)[sortedElements[i]]);
            }
        }
    }

    if (gCurrentCamID == CAM_BATTLE) {
        count = gather_and_sort_hud_elements(sortedElements, TRUE);

        if (count != 0) {
            gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, SCREEN_XMIN, SCREEN_YMIN, SCREEN_XMAX, SCREEN_YMAX);
            gDPPipeSync(gMainGfxPos++);
            gSPClearGeometryMode(gMainGfxPos++, G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH);
            gSPSetGeometryMode(gMainGfxPos++, G_ZBUFFER | G_SHADE | G_LIGHTING | G_SHADING_SMOOTH);
            gSPSetLights1(gMainGfxPos++, HudElemLights);
            gSPTexture(gMainGfxPos++, -1, -1, 0, G_TX_RENDERTILE, G_ON);
            gDPSetAlphaCompare(gMainGfxPos++, G_AC_NONE);
            gSPSetOtherMode(gMainGfxPos++, G_SETOTHERMODE_H, G_MDSFT_ALPHADITHER, 18, G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE);

            for (i = 0; i < count; i++) {
                render_complex_hud_element((*gHudElements)[sortedElements[i]]);
            }
        }
    }
}

void immediately_render_complex_hud_element(s32 elemID, b32 includeSetup, s32 camID) {
    Camera* camera = &gCameras[camID];

    if (includeSetup) {
        if (camera->flags == 0 || (camera->flags & CAMERA_FLAG_DISABLED)) {
            return;
        }

        gCurrentCamID = camID;

        gSPViewport(gMainGfxPos++, &camera->vp);
        gSPClearGeometryMode(gMainGfxPos++, G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN |
                                                G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH);
        gSPTexture(gMainGfxPos++, 0, 0, 0, G_TX_RENDERTILE, G_OFF);
        gDPPipelineMode(gMainGfxPos++, G_PM_NPRIMITIVE);
        gDPSetTextureLUT(gMainGfxPos++, G_TT_NONE);
        gDPSetTextureFilter(gMainGfxPos++, G_TF_BILERP);
        gDPSetCombineMode(gMainGfxPos++, G_CC_SHADE, G_CC_SHADE);
        gDPSetRenderMode(gMainGfxPos++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
        gSPClipRatio(gMainGfxPos++, FRUSTRATIO_2);
        gDPPipeSync(gMainGfxPos++);
        //clear Z buffer inside camera viewport
        gDPSetCycleType(gMainGfxPos++, G_CYC_FILL);
        gDPSetColorImage(gMainGfxPos++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, osVirtualToPhysical(nuGfxZBuffer));
        gDPSetFillColor(gMainGfxPos++, GPACK_ZDZ(G_MAXFBZ, 0)<<16 | GPACK_ZDZ(G_MAXFBZ, 0));
        gDPFillRectangle(gMainGfxPos++, camera->viewportStartX, camera->viewportStartY,
                         camera->viewportStartX + camera->viewportW - 1,
                         camera->viewportStartY + camera->viewportH - 1);
        gDPPipeSync(gMainGfxPos++);

        gDPSetColorImage(gMainGfxPos++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, osVirtualToPhysical(nuGfxCfb_ptr));
        gDPPipeSync(gMainGfxPos++);

        guOrthoF(camera->mtxPerspective, 0.0f, 320.0f, -240.0f, 0.0f, -1000.0f, 1000.0f, 1.0f);
        guMtxF2L(camera->mtxPerspective, &gDisplayContext->camPerspMatrix[gCurrentCamID]);

        gSPMatrix(gMainGfxPos++, &gDisplayContext->camPerspMatrix[gCurrentCamID], G_MTX_NOPUSH | G_MTX_LOAD |
                                                                                    G_MTX_PROJECTION);
        // scissor to insets
        gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, SCREEN_XMIN, SCREEN_YMIN, SCREEN_XMAX, SCREEN_YMAX);
        gDPPipeSync(gMainGfxPos++);
        gDPSetCycleType(gMainGfxPos++, G_CYC_1CYCLE);
        gSPClearGeometryMode(gMainGfxPos++, G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING |
                                                G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH);
        gSPSetGeometryMode(gMainGfxPos++, G_ZBUFFER | G_SHADE | G_LIGHTING | G_SHADING_SMOOTH);
        gSPSetLights1(gMainGfxPos++, HudElemLights);
        gSPTexture(gMainGfxPos++, -1, -1, 0, G_TX_RENDERTILE, G_ON);
        gDPSetTextureLOD(gMainGfxPos++, G_TL_TILE);
        gDPSetTexturePersp(gMainGfxPos++, G_TP_PERSP);
        gDPSetColorDither(gMainGfxPos++, G_CD_DISABLE);
        gDPSetTextureDetail(gMainGfxPos++, G_TD_CLAMP);
        gDPSetTextureConvert(gMainGfxPos++, G_TC_FILT);
        gDPSetCombineKey(gMainGfxPos++, G_CK_NONE);
        gDPSetAlphaCompare(gMainGfxPos++, G_AC_NONE);
    }

    if (elemID >= 0) {
        HudElement* elem;

        elemID &= ~HUD_ELEMENT_BATTLE_ID_MASK;
        elem = (*gHudElements)[elemID];

        if (elem == NULL) {
            return;
        }

        if (elem->flags == 0 || elem->flags & HUD_ELEMENT_FLAG_DISABLED) {
            return;
        }

        if (elem->flags & (HUD_ELEMENT_FLAG_INVISIBLE | HUD_ELEMENT_FLAG_HIDDEN)) {
            return;
        }

        if (!(elem->flags & HUD_ELEMENT_FLAG_MANUAL_RENDER)) {
            return;
        }

        if (!(elem->flags & HUD_ELEMENT_FLAG_TRANSFORM)) {
            return;
        }

        if (elem->flags & HUD_ELEMENT_FLAG_FRONTUI || elem->drawSizePreset < 0) {
            return;
        }

        render_complex_hud_element(elem);
    }
}

void hud_element_draw_complex_hud_first(s32 hid) {
    immediately_render_complex_hud_element(hid, TRUE, CAM_HUD);
}

void hud_element_draw_complex_hud_next(s32 hid) {
    immediately_render_complex_hud_element(hid, FALSE, CAM_HUD);
}

void hud_element_draw_complex_battle_first(s32 hid) {
    immediately_render_complex_hud_element(hid, TRUE, CAM_BATTLE);
}

void hud_element_draw_complex_battle_next(s32 hid) {
    immediately_render_complex_hud_element(hid, FALSE, CAM_BATTLE);
}

void draw_hud_element_internal(s32 id, s32 clipMode) {
    HudElement* elem = (*gHudElements)[id & ~HUD_ELEMENT_BATTLE_ID_MASK];
    s32 texSizeX, texSizeY;
    s32 drawSizeX, drawSizeY;
    s32 offsetX, offsetY;

    if (elem->flags == 0 || elem->flags & HUD_ELEMENT_FLAG_DISABLED) {
        return;
    }

    if (elem->flags & (HUD_ELEMENT_FLAG_INVISIBLE | HUD_ELEMENT_FLAG_HIDDEN)) {
        return;
    }

    if (elem->drawSizePreset >= 0) {
        if (clipMode != HUD_ELEMENT_DRAW_NEXT) {
            if (clipMode == HUD_ELEMENT_DRAW_FIRST_WITH_CLIPPING) {
                gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, SCREEN_XMIN, SCREEN_YMIN, SCREEN_XMAX, SCREEN_YMAX);
            }
            gDPPipeSync(gMainGfxPos++);
            gDPSetCycleType(gMainGfxPos++, G_CYC_1CYCLE);
            gDPSetTexturePersp(gMainGfxPos++, G_TP_NONE);
            gDPSetTextureLOD(gMainGfxPos++, G_TL_TILE);
            gDPSetTextureDetail(gMainGfxPos++, G_TD_CLAMP);
            gDPSetTextureConvert(gMainGfxPos++, G_TC_FILT);
            gDPSetCombineKey(gMainGfxPos++, G_CK_NONE);
            gDPSetAlphaCompare(gMainGfxPos++, G_AC_NONE);
            gDPNoOp(gMainGfxPos++);
            gDPSetColorDither(gMainGfxPos++, G_CD_DISABLE);
            gDPSetAlphaDither(gMainGfxPos++, G_AD_DISABLE);
            gSPTexture(gMainGfxPos++, -1, -1, 0, G_TX_RENDERTILE, G_ON);
        }

        if (!(elem->flags & HUD_ELEMENT_FLAG_RESIZING)) {
            if (elem->flags & HUD_ELEMENT_FLAG_CUSTOM_SIZE) {
                texSizeX = elem->customImageSize.x;
                texSizeY = elem->customImageSize.y;
            } else {
                texSizeX = HudElemSizes[elem->tileSizePreset].width;
                texSizeY = HudElemSizes[elem->tileSizePreset].height;
            }

            if (elem->flags & HUD_ELEMENT_FLAG_SCALED) {
                drawSizeX = elem->sizeX;
                drawSizeY = elem->sizeY;
            } else if (elem->flags & HUD_ELEMENT_FLAG_CUSTOM_SIZE) {
                drawSizeX = elem->customDrawSize.x;
                drawSizeY = elem->customDrawSize.y;
            } else {
                drawSizeX = HudElemSizes[elem->drawSizePreset].width;
                drawSizeY = HudElemSizes[elem->drawSizePreset].height;
            }

            offsetX = -drawSizeX / 2;
            offsetY = -drawSizeY / 2;

            if (elem->flags & HUD_ELEMENT_FLAG_REPEATED) {
                if (elem->flags & HUD_ELEMENT_FLAG_DROP_SHADOW) {
                    hud_element_draw_rect(elem, texSizeX, texSizeY, drawSizeX, drawSizeY, offsetX, offsetY, FALSE, TRUE);
                }
                hud_element_draw_rect(elem, texSizeX, texSizeY, drawSizeX, drawSizeY, offsetX, offsetY, FALSE, FALSE);
            } else {
                if (elem->flags & HUD_ELEMENT_FLAG_DROP_SHADOW) {
                    hud_element_draw_rect(elem, texSizeX, texSizeY, drawSizeX, drawSizeY, offsetX, offsetY, TRUE, TRUE);
                }
                hud_element_draw_rect(elem, texSizeX, texSizeY, drawSizeX, drawSizeY, offsetX, offsetY, TRUE, FALSE);
            }
        } else {
            f32 xScaled, yScaled;

            if (elem->flags & HUD_ELEMENT_FLAG_CUSTOM_SIZE) {
                texSizeX = elem->customImageSize.x;
                texSizeY = elem->customImageSize.y;
            } else {
                texSizeX = HudElemSizes[elem->tileSizePreset].width;
                texSizeY = HudElemSizes[elem->tileSizePreset].height;
            }

            drawSizeX = elem->dynamicSize.x;
            drawSizeY = elem->dynamicSize.y;

            offsetX = -elem->dynamicSize.x / 2;
            offsetY = -elem->dynamicSize.y / 2;

            xScaled = (f32) drawSizeX / (f32) texSizeX;
            yScaled = (f32) drawSizeY / (f32) texSizeY;

            xScaled = 1.0f / xScaled;
            yScaled = 1.0f / yScaled;

            elem->widthScale = X10(xScaled);
            elem->heightScale = X10(yScaled);

            if (elem->flags & HUD_ELEMENT_FLAG_DROP_SHADOW) {
                hud_element_draw_rect(elem, texSizeX, texSizeY, drawSizeX, drawSizeY, offsetX, offsetY, FALSE, TRUE);
            }
            hud_element_draw_rect(elem, texSizeX, texSizeY, drawSizeX, drawSizeY, offsetX, offsetY, FALSE, FALSE);
        }
    }
}

void hud_element_draw_clipped(s32 id) {
    draw_hud_element_internal(id, HUD_ELEMENT_DRAW_FIRST_WITH_CLIPPING);
}

void hud_element_draw_next(s32 id) {
    draw_hud_element_internal(id, HUD_ELEMENT_DRAW_NEXT);
}

void hud_element_draw_without_clipping(s32 id) {
    draw_hud_element_internal(id, HUD_ELEMENT_DRAW_FIRST_WITHOUT_CLIPPING);
}

void hud_element_set_script(s32 id, HudScript* anim) {
    HudElement* hudElement = (*gHudElements)[id & ~HUD_ELEMENT_BATTLE_ID_MASK];

    if (anim == NULL) {
        anim = &HES_Empty;
    }

    hudElement->updateTimer = 1;
    hudElement->widthScale = X10(1.0f);
    hudElement->heightScale = X10(1.0f);
    hudElement->readPos = anim;
    hudElement->anim = anim;
    hudElement->loopStartPos = anim;
    hudElement->screenPosOffset.x = 0;
    hudElement->screenPosOffset.y = 0;
    hudElement->worldPosOffset.x = 0;
    hudElement->worldPosOffset.y = 0;
    hudElement->flags &= ~HUD_ELEMENT_FLAG_ANIMATION_FINISHED;
    hudElement->uniformScale = 1.0f;
    hudElement->flags &= ~(HUD_ELEMENT_FLAG_SCALED | HUD_ELEMENT_FLAG_TRANSPARENT | HUD_ELEMENT_FLAG_RESIZING | HUD_ELEMENT_FLAG_REPEATED);
    hud_element_load_script(hudElement, anim);

    while (hud_element_update(hudElement) != 0) {}
}

HudScript* hud_element_get_script(s32 id) {
    return (*gHudElements)[id & ~HUD_ELEMENT_BATTLE_ID_MASK]->anim;
}

HudElement* get_hud_element(s32 id) {
    return (*gHudElements)[id & ~HUD_ELEMENT_BATTLE_ID_MASK];
}

void hud_element_free(s32 id) {
    if ((*gHudElements)[id & ~HUD_ELEMENT_BATTLE_ID_MASK]->flags & HUD_ELEMENT_FLAG_TRANSFORM) {
        hud_element_free_transform(id & ~HUD_ELEMENT_BATTLE_ID_MASK);
    }

    heap_free((*gHudElements)[id & ~HUD_ELEMENT_BATTLE_ID_MASK]);
    (*gHudElements)[id & ~HUD_ELEMENT_BATTLE_ID_MASK] = NULL;
    HudElemCount--;
}

void hud_element_set_render_pos(s32 id, s32 x, s32 y) {
    HudElement* hudElement = (*gHudElements)[id & ~HUD_ELEMENT_BATTLE_ID_MASK];

    hudElement->renderPosX = x;
    hudElement->renderPosY = y;
}

void hud_element_get_render_pos(s32 id, s32* x, s32* y) {
    HudElement* hudElement = (*gHudElements)[id & ~HUD_ELEMENT_BATTLE_ID_MASK];

    *x = hudElement->renderPosX;
    *y = hudElement->renderPosY;
}

void hud_element_set_render_depth(s32 id, s32 z) {
    (*gHudElements)[id & ~HUD_ELEMENT_BATTLE_ID_MASK]->worldPosOffset.z = z;
}

void hud_element_set_flags(s32 id, s32 flags) {
    (*gHudElements)[id & ~HUD_ELEMENT_BATTLE_ID_MASK]->flags |= flags;
}

void hud_element_clear_flags(s32 id, s32 flags) {
    (*gHudElements)[id & ~HUD_ELEMENT_BATTLE_ID_MASK]->flags &= ~flags;
}

void ALT_clear_hud_element_cache(void) {
    s32 i;

    if (gGameStatusPtr->context == CONTEXT_WORLD) {
        heap_free(gHudElementCacheBuffer);
        gHudElementCacheBuffer = heap_malloc(HudElemCacheCapacity);
        ASSERT(gHudElementCacheBuffer);
        gHudElementCacheBufferWorld = gHudElementCacheBuffer;
        *gHudElementCacheSize = 0;
        gHudElementCacheSize = &gHudElementCacheSizeWorld;
        gHudElementCacheTableRaster = gHudElementCacheTableRasterWorld;
        gHudElementCacheTablePalette = gHudElementCacheTablePaletteWorld;
        gHudElementCacheBuffer = gHudElementCacheBufferWorld;

        for (i = 0; i < MAX_HUD_CACHE_ENTRIES; i++) {
            gHudElementCacheTableRasterWorld[i].id = -1;
            gHudElementCacheTablePaletteWorld[i].id = -1;
        }
    } else {
        if (HudElemAuxCache == NULL) {
            heap_free(gHudElementCacheBuffer);
            gHudElementCacheBuffer = heap_malloc(HudElemCacheCapacity / 2);
            ASSERT(gHudElementCacheBuffer);
        } else {
            gHudElementCacheBuffer = HudElemAuxCache;
        }
        gHudElementCacheBufferBattle = gHudElementCacheBuffer;
        *gHudElementCacheSize = 0;
        gHudElementCacheSize = &gHudElementCacheSizeBattle;
        gHudElementCacheTableRaster = gHudElementCacheTableRasterBattle;
        gHudElementCacheTablePalette = gHudElementCacheTablePaletteBattle;
        gHudElementCacheBuffer = gHudElementCacheBufferBattle;

        for (i = 0; i < MAX_HUD_CACHE_ENTRIES; i++) {
            gHudElementCacheTableRasterBattle[i].id = -1;
            gHudElementCacheTablePaletteBattle[i].id = -1;
        }
    }
}

void hud_element_set_scale(s32 index, f32 scale) {
    HudElement* elem = (*gHudElements)[index & ~HUD_ELEMENT_BATTLE_ID_MASK];
    s32 drawSizeX;
    s32 drawSizeY;
    s32 imgSizeX;
    s32 imgSizeY;
    f32 xScaled, yScaled;

    elem->uniformScale = scale;
    if (elem->flags & HUD_ELEMENT_FLAG_CUSTOM_SIZE) {
        imgSizeX = elem->customImageSize.x;
        imgSizeY = elem->customImageSize.y;
        drawSizeX = elem->customDrawSize.x;
        drawSizeY = elem->customDrawSize.y;
    } else {
        imgSizeX = HudElemSizes[elem->tileSizePreset].width;
        imgSizeY = HudElemSizes[elem->tileSizePreset].height;
        drawSizeX = HudElemSizes[elem->drawSizePreset].width;
        drawSizeY = HudElemSizes[elem->drawSizePreset].height;
    }
    elem->sizeX = drawSizeX * scale;
    elem->sizeY = drawSizeY * scale;
    elem->flags &= ~HUD_ELEMENT_FLAG_RESIZING;
    elem->flags |= HUD_ELEMENT_FLAG_REPEATED | HUD_ELEMENT_FLAG_SCALED;

    xScaled = ((f32) drawSizeX / (f32) imgSizeX) * scale;
    yScaled = ((f32) drawSizeY / (f32) imgSizeY) * scale;

    xScaled = 1.0f / xScaled;
    yScaled = 1.0f / yScaled;

    elem->widthScale = X10(xScaled);
    elem->heightScale = X10(yScaled);
}

void hud_element_use_preset_size(s32 id, s8 sizePreset) {
    HudElement* hudElement = (*gHudElements)[id & ~HUD_ELEMENT_BATTLE_ID_MASK];

    hudElement->widthScale = X10(1.0f);
    hudElement->heightScale = X10(1.0f);
    hudElement->tileSizePreset = sizePreset;
    hudElement->drawSizePreset = sizePreset;
    hudElement->uniformScale = 1.0f;
    hudElement->flags &= ~HUD_ELEMENT_FLAG_RESIZING;
    hudElement->flags &= ~(HUD_ELEMENT_FLAG_SCALED | HUD_ELEMENT_FLAG_REPEATED);
}

s32 hud_element_get_variable(s32 id) {
    return ((*gHudElements)[id & ~HUD_ELEMENT_BATTLE_ID_MASK]->flags >> 24) & 0xF;
}

void hud_element_set_variable(s32 id, s32 value) {
    HudElement* hudElement = (*gHudElements)[id & ~HUD_ELEMENT_BATTLE_ID_MASK];

    hudElement->flags &= ~HUD_ELEMENT_VARIABLE_MASK;
    hudElement->flags |= value << 24;
}

void hud_element_set_alpha(s32 id, s32 opacity) {
    HudElement* hudElement = (*gHudElements)[id & ~HUD_ELEMENT_BATTLE_ID_MASK];

    hudElement->flags |= HUD_ELEMENT_FLAG_TRANSPARENT;
    hudElement->opacity = opacity;

    if (opacity == 255) {
        hudElement->flags &= ~HUD_ELEMENT_FLAG_TRANSPARENT;
    }
}

void hud_element_set_tint(s32 id, s32 r, s32 g, s32 b) {
    HudElement* hudElement = (*gHudElements)[id & ~HUD_ELEMENT_BATTLE_ID_MASK];

    hudElement->tint.r = r;
    hudElement->tint.g = g;
    hudElement->tint.b = b;
}

void hud_element_create_transform_A(s32 id) {
    HudElement* element = (*gHudElements)[id & ~HUD_ELEMENT_BATTLE_ID_MASK];
    HudTransform* transform = general_heap_malloc(sizeof(*transform));

    element->hudTransform = transform;
    ASSERT(transform != NULL);
    element->flags |= HUD_ELEMENT_FLAG_TRANSFORM;
    transform->imgfxIdx = imgfx_get_free_instances(1);
    transform->pos.x = 0.0f;
    transform->pos.y = 0.0f;
    transform->pos.z = 0.0f;
    transform->rot.x = 0.0f;
    transform->rot.y = 0.0f;
    transform->rot.z = 0.0f;
    transform->scale.x = 1.0f;
    transform->scale.y = 1.0f;
    transform->scale.z = 1.0f;
    transform->pivot.x = 0;
    transform->pivot.y = 0;
    hud_element_setup_cam();
}

void hud_element_create_transform_B(s32 id) {
    HudElement* element = (*gHudElements)[id & ~HUD_ELEMENT_BATTLE_ID_MASK];
    HudTransform* transform = general_heap_malloc(sizeof(*transform));

    element->hudTransform = transform;
    ASSERT(transform != NULL);
    element->flags |= HUD_ELEMENT_FLAG_TRANSFORM | HUD_ELEMENT_FLAG_NO_FOLD;
    transform->imgfxIdx = 0;
    transform->pos.x = 0.0f;
    transform->pos.y = 0.0f;
    transform->pos.z = 0.0f;
    transform->rot.x = 0.0f;
    transform->rot.y = 0.0f;
    transform->rot.z = 0.0f;
    transform->scale.x = 1.0f;
    transform->scale.y = 1.0f;
    transform->scale.z = 1.0f;
    hud_element_setup_cam();
}

void hud_element_create_transform_C(s32 id) {
    HudElement* element = (*gHudElements)[id & ~HUD_ELEMENT_BATTLE_ID_MASK];
    HudTransform* transform = general_heap_malloc(sizeof(*transform));

    element->hudTransform = transform;
    ASSERT(transform != NULL);
    element->flags |= HUD_ELEMENT_FLAG_BATTLE_CAM | HUD_ELEMENT_FLAG_NO_FOLD | HUD_ELEMENT_FLAG_TRANSFORM;
    transform->imgfxIdx = 0;
    transform->pos.x = 0.0f;
    transform->pos.y = 0.0f;
    transform->pos.z = 0.0f;
    transform->rot.x = 0.0f;
    transform->rot.y = 0.0f;
    transform->rot.z = 0.0f;
    transform->scale.x = 1.0f;
    transform->scale.y = 1.0f;
    transform->scale.z = 1.0f;
    hud_element_setup_cam();
}

void hud_element_free_transform(s32 id) {
    HudElement* hudElement = (*gHudElements)[id & ~HUD_ELEMENT_BATTLE_ID_MASK];
    HudTransform* hudTransform = hudElement->hudTransform;

    if (!(hudElement->flags & HUD_ELEMENT_FLAG_NO_FOLD)) {
        imgfx_release_instance(hudTransform->imgfxIdx);
    }

    heap_free(hudElement->hudTransform);
    hudElement->hudTransform = NULL;
    hudElement->flags &= ~(HUD_ELEMENT_FLAG_BATTLE_CAM | HUD_ELEMENT_FLAG_NO_FOLD | HUD_ELEMENT_FLAG_TRANSFORM);
}

void hud_element_set_transform_pos(s32 id, f32 x, f32 y, f32 z) {
    HudElement* element = (*gHudElements)[id & ~HUD_ELEMENT_BATTLE_ID_MASK];
    HudTransform* transform = element->hudTransform;

    if (element->flags & HUD_ELEMENT_FLAG_TRANSFORM) {
        transform->pos.x = x;
        transform->pos.y = y;
        transform->pos.z = z;
    }
}

void hud_element_set_transform_scale(s32 id, f32 x, f32 y, f32 z) {
    HudElement* element = (*gHudElements)[id & ~HUD_ELEMENT_BATTLE_ID_MASK];
    HudTransform* transform = element->hudTransform;

    if (element->flags & HUD_ELEMENT_FLAG_TRANSFORM) {
        transform->scale.x = x;
        transform->scale.y = y;
        transform->scale.z = z;
    }
}

void hud_element_set_transform_rotation(s32 id, f32 x, f32 y, f32 z) {
    HudElement* element = (*gHudElements)[id & ~HUD_ELEMENT_BATTLE_ID_MASK];
    HudTransform* transform = element->hudTransform;

    if (element->flags & HUD_ELEMENT_FLAG_TRANSFORM) {
        transform->rot.x = x;
        transform->rot.y = y;
        transform->rot.z = z;
    }
}

void hud_element_set_transform_rotation_pivot(s32 id, s32 dx, s32 dy) {
    HudElement* element = (*gHudElements)[id & ~HUD_ELEMENT_BATTLE_ID_MASK];
    HudTransform* transform = element->hudTransform;

    if (element->flags & HUD_ELEMENT_FLAG_TRANSFORM) {
        transform->pivot.x = dx;
        transform->pivot.y = dy;
    }
}

void copy_world_hud_element_ref_to_battle(s32 worldID, s32 battleID) {
    gHudElementsBattle[battleID & ~HUD_ELEMENT_BATTLE_ID_MASK] = gHudElementsWorld[worldID & ~HUD_ELEMENT_BATTLE_ID_MASK];
}

void hud_element_set_aux_cache(void* base, s32 size) {
    HudElemAuxCache = (u8*)base;
    if (base == NULL) {
        HudElemCacheCapacity = 0x11000;
    } else {
        HudElemCacheCapacity = size;
    }
}
