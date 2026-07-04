#include "common.h"
#include "effects_internal.h"

extern Gfx D_09001000_3A5320[];
extern Gfx D_090010A8_3A53C8[];
extern Gfx D_090011D0_3A54F0[];
extern Gfx D_090011F0_3A5510[];
extern Gfx D_09001210_3A5530[];

enum EnergyOrbWaveModes {
    ENERGY_ORB_WAVE_MODE_GREEN_PULSE  = 0,
    ENERGY_ORB_WAVE_MODE_GREEN_BRIGHT = 1,
    ENERGY_ORB_WAVE_MODE_PINK_PULSE   = 2,
    ENERGY_ORB_WAVE_MODE_PINK_BRIGHT  = 3,
    ENERGY_ORB_WAVE_MODE_PALE_PULSE   = 4,
    ENERGY_ORB_WAVE_MODE_PALE_BRIGHT  = 5,
    ENERGY_ORB_WAVE_MODE_GREEN_WAVE   = 6,
    ENERGY_ORB_WAVE_MODE_PALE_WAVE    = 7,
    ENERGY_ORB_WAVE_MODE_PINK_WAVE    = 8,
    ENERGY_ORB_WAVE_MODE_GRAY_WAVE    = 9,
    ENERGY_ORB_WAVE_MODE_BLUE_SHRINK  = 10,
};

void energy_orb_wave_init(EffectInstance* effect);
void energy_orb_wave_update(EffectInstance* effect);
void energy_orb_wave_render(EffectInstance* effect);
void energy_orb_wave_appendGfx(void* effect);

EffectInstance* energy_orb_wave_main(s32 type, f32 x, f32 y, f32 z, f32 scale, s32 duration) {
    EffectBlueprint bp;
    EffectInstance* effect;
    EnergyOrbWaveFXData* data;
    s32 numParts = 1;

    bp.init = energy_orb_wave_init;
    bp.update = energy_orb_wave_update;
    bp.renderScene = energy_orb_wave_render;
    bp.unk_00 = 0;
    bp.renderUI = nullptr;
    bp.effectID = EFFECT_ENERGY_ORB_WAVE;

    effect = create_effect_instance(&bp);
    effect->numParts = numParts;
    data = effect->data.energyOrbWave = general_heap_malloc(numParts * sizeof(*data));
    ASSERT(effect->data.energyOrbWave != nullptr);

    data->type = type;
    data->lifetime = 0;
    if (duration <= 0) {
        data->timeLeft = 100;
    } else {
        data->timeLeft = duration;
    }
    data->alpha = 0;
    data->pos.x = x;
    data->pos.y = y;
    data->pos.z = z;
    data->scale = scale;

    switch (type) {
        case FX_ENERGY_ORB_WAVE_GREEN_ORB:
            data->mode = ENERGY_ORB_WAVE_MODE_GREEN_PULSE;
            break;
        case FX_ENERGY_ORB_WAVE_PINK_ORB:
            data->mode = ENERGY_ORB_WAVE_MODE_PINK_PULSE;
            break;
        case FX_ENERGY_ORB_WAVE_PALE_ORB:
            data->mode = ENERGY_ORB_WAVE_MODE_PALE_PULSE;
            break;
        case FX_ENERGY_ORB_WAVE_GREEN_WAVE:
            data->mode = ENERGY_ORB_WAVE_MODE_GREEN_WAVE;
            break;
        case FX_ENERGY_ORB_WAVE_PALE_WAVE:
            data->mode = ENERGY_ORB_WAVE_MODE_PALE_WAVE;
            break;
        case FX_ENERGY_ORB_WAVE_PINK_WAVE:
            data->mode = ENERGY_ORB_WAVE_MODE_PINK_WAVE;
            break;
        case FX_ENERGY_ORB_WAVE_GRAY_WAVE:
            data->mode = ENERGY_ORB_WAVE_MODE_GRAY_WAVE;
            break;
        case FX_ENERGY_ORB_WAVE_UNUSED_7:
        case FX_ENERGY_ORB_WAVE_UNUSED_8:
        case FX_ENERGY_ORB_WAVE_BLUE_SHRINK:
        default:
            data->mode = ENERGY_ORB_WAVE_MODE_BLUE_SHRINK;
            data->scaleDelta = -(scale - 0.1) / duration;
            break;
    }

    return effect;
}

void energy_orb_wave_init(EffectInstance* effect) {
}

void energy_orb_wave_update(EffectInstance* effect) {
    EnergyOrbWaveFXData* data = effect->data.energyOrbWave;
    f32 alphaPulse;
    s32 lifetime;
    s32 linearFadeAlpha;
    s32 fadeAlpha;
    s32 mode;
    u16 baseAlpha;
    s32 fullAlpha;

    if (effect->flags & FX_INSTANCE_FLAG_DISMISS) {
        effect->flags &= ~FX_INSTANCE_FLAG_DISMISS;
        data->timeLeft = 30;
    }

    if (data->timeLeft < 100) {
        data->timeLeft--;
    }
    data->lifetime++;

    if (data->timeLeft < 0) {
        remove_effect(effect);
        return;
    }

    lifetime = data->lifetime;
    mode = data->mode;
    fadeAlpha = 0xFF;
    linearFadeAlpha = 0xFF;

    if (lifetime < 16) {
        fadeAlpha = (lifetime * 16) - 1;
    }
    if (data->timeLeft < 16) {
        fadeAlpha = fadeAlpha * data->timeLeft / 16;
        linearFadeAlpha = data->timeLeft * 16;
    }

    switch (mode) {
        case ENERGY_ORB_WAVE_MODE_GREEN_PULSE:
            data->color.r = 70;
            data->color.g = 180;
            data->color.b = 120;
            alphaPulse = sin_deg(lifetime * 2) * 10.0f + 190.0f;
            data->alpha = ((s32) alphaPulse * fadeAlpha) / 255;
            break;
        case ENERGY_ORB_WAVE_MODE_GREEN_BRIGHT:
            fullAlpha = 255;
            data->color.r = 70;
            data->color.g = 255;
            data->color.b = 230;
            data->alpha = (fadeAlpha * fullAlpha) / 255;
            break;
        case ENERGY_ORB_WAVE_MODE_PINK_PULSE:
            data->color.r = 170;
            data->color.g = 40;
            data->color.b = 110;
            alphaPulse = sin_deg(lifetime * 2) * 10.0f + 190.0f;
            data->alpha = ((s32) alphaPulse * fadeAlpha) / 255;
            break;
        case ENERGY_ORB_WAVE_MODE_PINK_BRIGHT:
            baseAlpha = 255;
            data->color.r = 220;
            data->color.g = 40;
            data->color.b = 170;
            data->alpha = (fadeAlpha * baseAlpha) / 255;
            break;
        case ENERGY_ORB_WAVE_MODE_PALE_PULSE:
            data->color.r = 235;
            data->color.g = 235;
            data->color.b = 200;
            alphaPulse = sin_deg(lifetime * 2) * 15.0f + 215.0f;
            data->alpha = ((s32) alphaPulse * fadeAlpha) / 255;
            break;
        case ENERGY_ORB_WAVE_MODE_PALE_BRIGHT:
            baseAlpha = 255;
            data->color.r = 235;
            data->color.g = 235;
            data->color.b = 200;
            data->alpha = (fadeAlpha * baseAlpha) / 255;
            break;
        case ENERGY_ORB_WAVE_MODE_GREEN_WAVE:
            baseAlpha = 127;
            data->color.r = 70;
            data->color.g = 180;
            data->color.b = 120;
            data->alpha = (linearFadeAlpha * baseAlpha) / 255;
            data->scale *= 1.1;
            break;
        case ENERGY_ORB_WAVE_MODE_PALE_WAVE:
            baseAlpha = 160;
            data->color.r = 162;
            data->color.g = 189;
            data->color.b = 174;
            data->alpha = (linearFadeAlpha * baseAlpha) / 255;
            data->scale *= 1.1;
            break;
        case ENERGY_ORB_WAVE_MODE_PINK_WAVE:
            baseAlpha = 127;
            data->color.r = 170;
            data->color.g = 40;
            data->color.b = 110;
            data->alpha = (linearFadeAlpha * baseAlpha) / 255;
            data->scale *= 1.1;
            break;
        case ENERGY_ORB_WAVE_MODE_GRAY_WAVE:
            baseAlpha = 160;
            data->color.r = 180;
            data->color.g = 178;
            data->color.b = 174;
            data->alpha = (linearFadeAlpha * baseAlpha) / 255;
            data->scale *= 1.1;
            break;
        case ENERGY_ORB_WAVE_MODE_BLUE_SHRINK:
        default:
            baseAlpha = 160;
            data->color.r = 50;
            data->color.g = 50;
            data->color.b = 255;
            data->alpha = (linearFadeAlpha * baseAlpha) / 255;
            data->scale += data->scaleDelta;
            break;
    }
}

void energy_orb_wave_render(EffectInstance* effect) {
    EnergyOrbWaveFXData* data = effect->data.energyOrbWave;
    RenderTask renderTask;
    RenderTask* retTask;
    RenderTask* renderTaskPointer = &renderTask;

    renderTask.appendGfx = energy_orb_wave_appendGfx;
    renderTask.dist = 10;
    renderTask.appendGfxArg = effect;
    renderTask.renderMode = RENDER_MODE_CLOUD_NO_ZCMP;
    if (data->type >= FX_ENERGY_ORB_WAVE_GREEN_WAVE) {
        queue_render_task(renderTaskPointer);
        return;
    }

    retTask = queue_render_task(renderTaskPointer);
    retTask->renderMode |= RENDER_TASK_FLAG_REFLECT_FLOOR;
}

void func_E00A4648(void) {
}

void energy_orb_wave_appendGfx(void* effect) {
    EnergyOrbWaveFXData* data = ((EffectInstance*)effect)->data.energyOrbWave;
    Camera* camera = &gCameras[gCurrentCameraID];
    s32 lifetime = data->lifetime;
    s32 alpha = data->alpha;
    s32 type = data->type;
    Matrix4f sp18;
    Matrix4f sp58;

    gDPPipeSync(gMainGfxPos++);
    gSPSegment(gMainGfxPos++, 0x09, VIRTUAL_TO_PHYSICAL(((EffectInstance*)effect)->shared->graphics));

    guTranslateF(sp18, data->pos.x, data->pos.y, data->pos.z);
    guScaleF(sp58, data->scale, data->scale, data->scale);
    guMtxCatF(sp58, sp18, sp18);
    guMtxF2L(sp18, &gDisplayContext->matrixStack[gMatrixListPos]);

    gSPMatrix(gMainGfxPos++, &gDisplayContext->matrixStack[gMatrixListPos++], G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPMatrix(gMainGfxPos++, camera->mtxBillboard, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);
    gDPSetPrimColor(gMainGfxPos++, 0, 0, data->color.r, data->color.g, data->color.b, alpha);
    gDPSetColorDither(gMainGfxPos++, G_CD_BAYER);
    gDPSetAlphaDither(gMainGfxPos++, G_AD_PATTERN);

    if (type <= FX_ENERGY_ORB_WAVE_PALE_ORB) {
        gSPDisplayList(gMainGfxPos++, D_09001000_3A5320);

        guRotateF(sp18, lifetime, 0.0f, 0.0f, 1.0f);
        guMtxF2L(sp18, &gDisplayContext->matrixStack[gMatrixListPos]);

        gSPMatrix(gMainGfxPos++, &gDisplayContext->matrixStack[gMatrixListPos++], G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
        gSPDisplayList(gMainGfxPos++, D_090011D0_3A54F0);
        gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
        gDPSetColorDither(gMainGfxPos++, G_CD_MAGICSQ);

        guRotateF(sp18, -lifetime * 8, 0.0f, 0.0f, 1.0f);
        guMtxF2L(sp18, &gDisplayContext->matrixStack[gMatrixListPos]);

        gSPMatrix(gMainGfxPos++, &gDisplayContext->matrixStack[gMatrixListPos++], G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
        gSPDisplayList(gMainGfxPos++, D_090011F0_3A5510);
        gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
    } else {
        gSPDisplayList(gMainGfxPos++, D_090010A8_3A53C8);
        gSPDisplayList(gMainGfxPos++, D_09001210_3A5530);
    }

    gDPSetColorDither(gMainGfxPos++, G_CD_DISABLE);
    gDPSetAlphaDither(gMainGfxPos++, G_AD_DISABLE);
    gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
}
