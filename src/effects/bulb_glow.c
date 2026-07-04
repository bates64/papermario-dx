#include "common.h"
#include "nu/nusys.h"
#include "effects_internal.h"

typedef struct BulbGlowResamplePreset {
    /* 0x00 */ s32 texWidth;
    /* 0x04 */ s32 texHeight;
    /* 0x08 */ f32 texScaleX;
    /* 0x0C */ f32 texScaleY;
    /* 0x10 */ s32 screenRadius;
    /* 0x14 */ s32 stripHeight;
} BulbGlowResamplePreset; // size = 0x18

extern Gfx D_09001400_37C1D0[];
extern Gfx D_090014B8_37C288[];
extern Gfx D_09001570_37C340[];
extern Gfx D_09001618_37C3E8[];
extern Gfx D_090016C0_37C490[];

Gfx* D_E0078900[] = {
    D_09001400_37C1D0, D_090014B8_37C288, D_09001570_37C340, D_09001618_37C3E8, D_090016C0_37C490, D_09001570_37C340
};

BulbGlowResamplePreset BulbGlowPresets[] = {
    { 128, 128, 0.5f, 0.5f,  64,  4 },
    {  64,  64, 2.0f, 2.0f,  32, 16 },
    {  64,  64, 1.0f, 1.0f,  64,  8 },
    {  64,  64, 2.0f, 2.0f,  16, 16 },
    {  64,  64, 1.0f, 1.0f,  32, 16 },
    {  64,  64, 1.0f, 1.0f,  64,  8 },
};

s32 D_E00789A8 = 0;

Color_RGB8 D_E00789AC[] = {
    { 255, 255, 255 },
    { 255, 255, 128 },
    { 255, 128, 255 },
    { 128, 255, 255 },
    { 255, 128, 128 },
    { 128, 255, 128 },
    { 128, 128, 255 },
};

void bulb_glow_init(EffectInstance* effect);
void bulb_glow_update(EffectInstance* effect);
void bulb_glow_render(EffectInstance* effect);
void bulb_glow_appendGfx(void* effect);

void bulb_glow_main(s32 type, f32 posX, f32 posY, f32 posZ, f32 unusedScale, EffectInstance** outEffect) {
    EffectBlueprint bp;
    EffectInstance* effect;
    BulbGlowFXData* data;
    s32 numParts = 1;

    bp.init = bulb_glow_init;
    bp.update = bulb_glow_update;
    bp.renderScene = bulb_glow_render;
    bp.unk_00 = 0;
    bp.renderUI = nullptr;
    bp.effectID = EFFECT_BULB_GLOW;

    effect = create_effect_instance(&bp);
    effect->numParts = numParts;
    data = effect->data.bulbGlow = general_heap_malloc(numParts * sizeof(*data));
    ASSERT(effect->data.bulbGlow != nullptr);

    data->type = type & 255;
    if (type < 256) {
        data->timeLeft = 100;
    } else {
        data->timeLeft = 80;
    }
    data->lifetime = 0;
    data->brightness = 127;
    data->pos.x = posX;
    data->pos.y = posY;
    data->pos.z = posZ;
    data->depthQueryID = D_E00789A8;

    D_E00789A8++;
    if (D_E00789A8 >= 16) {
        D_E00789A8 = 0;
    }

    data->colorIdx = rand_int(7);
    *outEffect = effect;
}

void bulb_glow_init(EffectInstance* effect) {
}

void bulb_glow_update(EffectInstance* effect) {
    BulbGlowFXData* data = effect->data.bulbGlow;
    s32 time;

    if (effect->flags & FX_INSTANCE_FLAG_DISMISS) {
        effect->flags &= ~FX_INSTANCE_FLAG_DISMISS;
        data->timeLeft = 10;
    }

    data->lifetime++;

    if (data->timeLeft < 100) {
        data->timeLeft--;
    }
    if (data->timeLeft < 0) {
        remove_effect(effect);
        return;
    }

    time = data->lifetime;
    if (data->type == 0) {
        // type 0 is Watt's flicker. after the pulse it becomes a steady type 4 glow.
        if (time < 11) {
            data->brightness = (time * 6) + 4;
        } else {
            data->brightness = 64;
        }

        if (time & 1) {
            data->brightness *= 0.6;
        }

        if (time >= 15) {
            data->type = 4;
            data->brightness = 127;
        }
    }
}

void bulb_glow_render(EffectInstance* effect) {
    BulbGlowFXData* data = effect->data.bulbGlow;
    RenderTask renderTask;
    RenderTask* renderTaskPtr = &renderTask;
    RenderTask* retTask;

    renderTask.appendGfxArg = effect;
    renderTask.appendGfx = bulb_glow_appendGfx;
    if (data->type == 5) {
        renderTask.dist = 0;
        renderTaskPtr->renderMode = RENDER_MODE_SURFACE_OPA;
    } else {
        renderTask.dist = -100;
        renderTaskPtr->renderMode = RENDER_MODE_CLOUD_NO_ZCMP;
    }

    retTask = queue_render_task(renderTaskPtr);
    retTask->renderMode |= RENDER_TASK_FLAG_REFLECT_FLOOR;
}

void func_E0078274(void) {
}

#define TMEM_ADDR(x) (x / sizeof(u64))

void bulb_glow_appendGfx(void* effect) {
    BulbGlowFXData* data = ((EffectInstance*)effect)->data.bulbGlow;
    f32 centerX;
    f32 centerY;
    s32 xMin;
    s32 numRects;
    s32 yMin;
    s32 type;
    s32 rectHeight;
    s32 glowExtent;
    s32 colorScale;
    s32 brightness;
    s32 yMax;
    s32 xStart;
    s32 xMax;
    s32 isPointVisible;
    s32 yStart;
    BulbGlowResamplePreset* preset;
    Color_RGB8* color;
    s32 i;
    s32 j;
    u8 r, g, b;

    brightness = data->brightness;
    type = data->type;
    if (brightness > 127) {
        brightness = 127;
    }

    gDPPipeSync(gMainGfxPos++);
    gSPSegment(gMainGfxPos++, 0x09, VIRTUAL_TO_PHYSICAL(((EffectInstance*)effect)->shared->graphics));

    preset = &BulbGlowPresets[type];
    glowExtent = preset->screenRadius;
    rectHeight = preset->stripHeight;

    isPointVisible = is_point_visible(data->pos.x, data->pos.y, data->pos.z, data->depthQueryID, &centerX, &centerY);

    // type 5 is already in screen space, so it skips the depth query and only uses the bounds check below
    if (type == 5) {
        isPointVisible = true;
    }

    if (!isPointVisible || centerX < 0.0f || centerY < 0.0f || centerX >= SCREEN_WIDTH || centerY >= SCREEN_HEIGHT) {
        return;
    }

    gSPDisplayList(gMainGfxPos++, D_E0078900[type]);
    color = &D_E00789AC[data->colorIdx];
    colorScale = brightness * 2;
    r = color->r * colorScale / 255;
    g = color->g * colorScale / 255;
    b = color->b * colorScale / 255;

    gDPSetPrimColor(gMainGfxPos++, 0, 0, r, g, b, 127);

    xMin = centerX - glowExtent;
    xMax = xMin + glowExtent * 2;
    yMin = centerY - glowExtent;
    yMax = yMin + glowExtent * 2;

    xStart = 0;
    if (xMin < 0) {
        xStart = -xMin;
    }
    yStart = 0;
    if (yMin < 0) {
        yStart = -yMin;
    }
    if (xMax > SCREEN_WIDTH) {
        xMax = SCREEN_WIDTH - 1;
    }
    if (yMax > SCREEN_HEIGHT) {
        yMax = SCREEN_HEIGHT - 1;
    }

    numRects = (yMax - yMin) / rectHeight;

    for (i = yStart / rectHeight; i < numRects; i++) {
        s32 y = yMin + i * rectHeight;
        if (y + rectHeight >= SCREEN_HEIGHT) {
            break;
        }

        gDPSetTileSize(gMainGfxPos++, G_TX_RENDERTILE,
            (s32) (xMin * preset->texScaleX) * 4,
            (s32) (preset->texHeight * 20 - i * preset->stripHeight * preset->texScaleY) * 4,
            (s32) (xMin * preset->texScaleX + preset->texWidth) * 4,
            (s32) (preset->texHeight * 21 - i * preset->stripHeight * preset->texScaleY) * 4);

        for (j = 0; j < 1; j++) {
            gDPLoadMultiTile(gMainGfxPos++,
                VIRTUAL_TO_PHYSICAL(nuGfxCfb_ptr + y * SCREEN_WIDTH),
                TMEM_ADDR(TMEM_SIZE/2), G_TX_RENDERTILE + 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, 0,
                xMin + xStart, 0, xMax - 1, rectHeight - 1,
                0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 9, 8, G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle(gMainGfxPos++,
                (xMin + xStart) * 4, y * 4,
                xMax * 4, (y + rectHeight) * 4,
                G_TX_RENDERTILE,
                ((xMin + xStart) & 0x1FF) << 5, 0,
                1 << 10, 1 << 10);
            gDPPipeSync(gMainGfxPos++);
        }
    }
}
