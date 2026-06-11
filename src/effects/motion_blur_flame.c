#include "common.h"
#include "effects_internal.h"
#include "nu/nusys.h"

#define NAMESPACE motion_blur_flame

extern Gfx D_09000200_3A35D0[];
extern Gfx D_090002A8_3A3678[];
extern Gfx D_09000358_3A3728[];

Gfx* D_E00A29D0[] = { D_09000200_3A35D0, D_090002A8_3A3678, D_09000358_3A3728 };

// create a feedback blur effect by sampling small framebuffer regions around the current and
// recent screen space positions of orbs, then rendering those regions back with reduced alpha.
// NOTE: must resample and draw via strips small enough to respect texture memory limitations.

typedef struct ScreenResamplePreset {
    /* 0x00 */ s32 texWidth;
    /* 0x04 */ s32 texHeight;
    /* 0x08 */ f32 texScaleX;
    /* 0x0C */ f32 texScaleY;
    /* 0x10 */ s32 screenRadius;
    /* 0x14 */ s32 stripHeight;
} ScreenResamplePreset; // size = 0x18

ScreenResamplePreset N(ScreenResamplePresets)[] = {
    { 16, 16, 1.0f, 1.0f, 8, 8 },
    { 16, 16, 1.0f, 1.0f, 8, 8 },
    { 16, 16, 1.0f, 1.0f, 8, 8 },
};

s32 N(SampleAlphaPct)[MOTION_BLUR_FLAME_SAMPLES] = { 100, 60, 30, 10 };

void motion_blur_flame_init(EffectInstance* effect);
void motion_blur_flame_update(EffectInstance* effect);
void motion_blur_flame_render(EffectInstance* effect);
void motion_blur_flame_appendGfx(void* effect);

EffectInstance* motion_blur_flame_main(s32 type, f32 x, f32 y, f32 z, f32 scale, s32 duration) {
    EffectBlueprint bp;
    EffectInstance* effect;
    MotionBlurFlameFXData* data;
    s32 numParts = 1;

    bp.init = motion_blur_flame_init;
    bp.update = motion_blur_flame_update;
    bp.renderScene = motion_blur_flame_render;
    bp.unk_00 = 0;
    bp.renderUI = nullptr;
    bp.effectID = EFFECT_MOTION_BLUR_FLAME;

    effect = create_effect_instance(&bp);
    effect->numParts = numParts;
    data = effect->data.motionBlurFlame = general_heap_malloc(numParts * sizeof(*data));
    ASSERT(effect->data.motionBlurFlame != nullptr);

    data->type = type;
    if (duration < 0) {
        data->timeLeft = FX_TIME_FOREVER;
    } else {
        data->timeLeft = duration;
    }
    data->alpha = 127;
    data->lifetime = 0;
    data->basePos.x = x;
    data->basePos.y = y;
    data->basePos.z = z;
    data->posOffset.x = 0;
    data->posOffset.y = 0;
    data->posOffset.z = 0;
    data->color.r = 255;
    data->color.g = 255;
    data->color.b = 255;
    data->sampleVisible[1] = 0;
    data->sampleVisible[2] = 0;
    data->sampleVisible[3] = 0;

    return effect;
}

void motion_blur_flame_init(EffectInstance* effect) {
}

void motion_blur_flame_update(EffectInstance* effect) {
    MotionBlurFlameFXData* data = effect->data.motionBlurFlame;

    if (effect->flags & FX_INSTANCE_FLAG_DISMISS) {
        effect->flags &= ~FX_INSTANCE_FLAG_DISMISS;
        data->timeLeft = 30;
    }

    data->lifetime++;

    if (data->timeLeft < FX_TIME_FOREVER) {
        data->timeLeft--;
    }

    if (data->timeLeft < 0) {
        remove_effect(effect);
        return;
    }

    if (data->lifetime <= 16) {
        data->alpha = (data->lifetime * 8) - 1;
    }
    if (data->timeLeft < 16) {
        data->alpha = data->timeLeft * 8;
    }

    data->worldPos.x = data->basePos.x + data->posOffset.x;
    data->worldPos.y = data->basePos.y + data->posOffset.y;
    data->worldPos.z = data->basePos.z + data->posOffset.z;
}

void motion_blur_flame_render(EffectInstance* effect) {
    RenderTask renderTask;
    RenderTask* retTask;

    renderTask.appendGfx = motion_blur_flame_appendGfx;
    renderTask.appendGfxArg = effect;
    renderTask.dist = 100;
    renderTask.renderMode = RENDER_MODE_CLOUD_NO_ZCMP;

    retTask = queue_render_task(&renderTask);
    retTask->renderMode |= RENDER_TASK_FLAG_REFLECT_FLOOR;
}

void motion_blur_flame_appendGfx(void* effect) {
    MotionBlurFlameFXData* data = ((EffectInstance*)effect)->data.motionBlurFlame;
    s32 type = data->type;
    s32 alpha = data->alpha;

    ScreenResamplePreset* preset = &N(ScreenResamplePresets)[type];
    s32 stripHeight = preset->stripHeight;
    s32 radius = preset->screenRadius;
    b32 historyIsVisible[MOTION_BLUR_FLAME_SAMPLES];
    f32 historyScreenX[MOTION_BLUR_FLAME_SAMPLES];
    f32 historyScreenY[MOTION_BLUR_FLAME_SAMPLES];
    s32 i;

    s32 envR, envG, envB;
    s32 primR, primG, primB;
    s32 sampleAlpha;

    f32 screenX, screenY;
    b32 isVisible;

    s32 xMin, yMin;
    s32 xMax, yMax;
    s32 xStart;

    s32 numStrips;
    s32 firstStrip;
    s32 stripIdx;
    s32 uly;

    s32 copyPass;

    gDPPipeSync(gMainGfxPos++);
    gSPSegment(gMainGfxPos++, 0x09, VIRTUAL_TO_PHYSICAL(((EffectInstance*)effect)->shared->graphics));
    gSPDisplayList(gMainGfxPos++, D_E00A29D0[type]);

    for (i = 0; i < MOTION_BLUR_FLAME_SAMPLES; i++) {
        // retrieve sample history
        if (i == 0) {
            isVisible = is_point_visible(data->worldPos.x, data->worldPos.y, data->worldPos.z, -1, &screenX, &screenY);
        } else {
            isVisible = data->sampleVisible[i];
            screenX = data->sampleX[i];
            screenY = data->sampleY[i];
        }

        historyIsVisible[i] = isVisible;
        historyScreenX[i] = screenX;
        historyScreenY[i] = screenY;

        if (isVisible && (screenX >= 0) && (screenY >= 0) && (screenX < SCREEN_WIDTH) && (screenY < SCREEN_HEIGHT)) {
            sampleAlpha = (alpha * N(SampleAlphaPct)[i]) / 100;
            primR = (data->color.r * sampleAlpha) >> 9;
            primG = (data->color.g * sampleAlpha) >> 9;
            primB = (data->color.b * sampleAlpha) >> 9;

            gDPSetPrimColor(gMainGfxPos++, 0, 0,
                (primR * sampleAlpha) >> 8,
                (primG * sampleAlpha) >> 8,
                (primB * sampleAlpha) >> 8,
                255
            );

            envR = primR + 32;
            envG = primG + 32;
            envB = primB + 32;
            if (envR > 127) {
                envR = 127;
            }
            if (envG > 127) {
                envG = 127;
            }
            if (envB > 127) {
                envB = 127;
            }

            gDPSetEnvColor(gMainGfxPos++, envR, envG, envB, 0);

            xMin = screenX - radius;
            yMin = screenY - radius;

            xMax = xMin + 2 * radius;
            yMax = yMin + 2 * radius;

            if (xMax > SCREEN_WIDTH) {
                xMax = SCREEN_WIDTH - 1;
            }
            if (yMax > SCREEN_HEIGHT) {
                yMax = SCREEN_HEIGHT - 1;
            }

            xStart = MAX(xMin, 0);

            numStrips = (yMax - yMin) / stripHeight;

            // skip strips that are completely above the framebuffer
            // partially visible strips along the top are still processed
            if (yMin < 0) {
                firstStrip = -yMin / stripHeight;
            } else {
                firstStrip = 0;
            }

            for (stripIdx = firstStrip; stripIdx < numStrips; stripIdx++) {
                uly = yMin + stripIdx * stripHeight;
                if (uly + stripHeight >= SCREEN_HEIGHT) {
                    break;
                }

                gDPSetTileSize(gMainGfxPos++, G_TX_RENDERTILE,
                    (s32) (xMin * preset->texScaleX) * 4,
                    (s32) (preset->texHeight * 20 - stripIdx * preset->stripHeight * preset->texScaleY) * 4,
                    (s32) (xMin * preset->texScaleX + preset->texWidth) * 4,
                    (s32) (preset->texHeight * 21 - stripIdx * preset->stripHeight * preset->texScaleY) * 4);

                // accumulate over several passes to intensify glow
                for (copyPass = 0; copyPass < 2; copyPass++) {
                    // load from the frame buffer
                    gDPLoadMultiTile(gMainGfxPos++, VIRTUAL_TO_PHYSICAL(nuGfxCfb_ptr + uly * SCREEN_WIDTH),
                        0x0100, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, SCREEN_HEIGHT,
                        xStart,
                        0,
                        xMax - 1,
                        stripHeight - 1,
                        0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 9, 8, G_TX_NOLOD, G_TX_NOLOD
                    );
                    // render the strip
                    gSPTextureRectangle(gMainGfxPos++,
                        (xStart) * 4,
                        uly * 4,
                        xMax * 4,
                        (uly + stripHeight) * 4,
                        G_TX_RENDERTILE,
                        (xStart % 0x200) * 32,
                        0,
                        0x0400,
                        0x0400
                    );
                    gDPPipeSync(gMainGfxPos++);
                }
            }
        }
    }

    // advance sample history
    for (i = 0; i < MOTION_BLUR_FLAME_SAMPLES - 1; i++) {
        data->sampleVisible[i + 1] = historyIsVisible[i];
        data->sampleX[i + 1] = historyScreenX[i];
        data->sampleY[i + 1] = historyScreenY[i];
    }
}
