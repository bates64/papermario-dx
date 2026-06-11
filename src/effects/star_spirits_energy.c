#include "common.h"
#include "effects_internal.h"

#define NAMESPACE star_spirit_energy

extern Gfx D_09004E00_412090[];
extern Gfx D_09005168_4123F8[];
extern Gfx D_090051C8_412458[];
extern Gfx D_09005370_412600[];
extern Gfx D_090053D0_412660[];
extern Gfx D_09005440_4126D0[];

Gfx* EnergyLayerGfx[] = {
    D_09005168_4123F8, D_090051C8_412458, D_09005370_412600, D_090053D0_412660
};

typedef struct EnergyRingFrame {
    /* 0x00 */ u16 scale; // values in percent
    /* 0x02 */ u8 alpha;
    /* 0x03 */ PAD(1);
} EnergyRingFrame; // size = 0x4

EnergyRingFrame RingExpandFrames[] = {
    {  100, 255 },
    {  200, 255 },
    {  300, 255 },
    {  400, 255 },
    {  500, 245 },
    {  600, 235 },
    {  700, 225 },
    {  800, 215 },
    {  900, 205 },
    { 1000, 195 },
    { 1100, 185 },
    { 1200, 175 },
    { 1300, 165 },
    { 1400, 155 },
    { 1500, 145 },
    { 1600, 135 },
    { 1700, 125 },
    { 1800, 115 },
    { 1900, 105 },
    { 2000,  95 },
    { 2100,  85 },
    { 2200,  75 },
    { 2300,  65 },
    { 2400,  55 },
    { 2500,  45 },
    { 2600,  30 },
    { 2700,  20 },
    { 2800,  10 },
    { 2900,   5 },
    { 3000,   0 },
};

EnergyRingFrame RingContractFrames[] = {
    { 3000,   0 },
    { 2900,   5 },
    { 2800,  10 },
    { 2700,  20 },
    { 2600,  30 },
    { 2500,  45 },
    { 2400,  55 },
    { 2300,  65 },
    { 2200,  75 },
    { 2100,  85 },
    { 2000,  95 },
    { 1900, 105 },
    { 1800, 115 },
    { 1700, 125 },
    { 1600, 135 },
    { 1500, 145 },
    { 1400, 155 },
    { 1300, 165 },
    { 1200, 175 },
    { 1100, 185 },
    { 1000, 195 },
    {  900, 205 },
    {  800, 215 },
    {  700, 225 },
    {  600, 235 },
    {  500, 245 },
    {  400, 255 },
    {  300, 255 },
    {  200, 255 },
    {  100, 255 },
};

void star_spirits_energy_init(EffectInstance* effect);
void star_spirits_energy_update(EffectInstance* effect);
void star_spirits_energy_render(EffectInstance* effect);
void star_spirits_energy_appendGfx(void* effect);

EffectInstance* star_spirits_energy_main(s32 type, f32 x, f32 y, f32 z, f32 scale, s32 duration) {
    EffectBlueprint bp;
    EffectInstance* effect;
    StarSpiritsEnergyFXData* data;
    s32 numParts = 1;

    bp.init = star_spirits_energy_init;
    bp.update = star_spirits_energy_update;
    bp.renderScene = star_spirits_energy_render;
    bp.unk_00 = 0;
    bp.renderUI = nullptr;
    bp.effectID = EFFECT_STAR_SPIRITS_ENERGY;

    effect = create_effect_instance(&bp);
    effect->numParts = numParts;
    data = effect->data.starSpiritsEnergy = general_heap_malloc(numParts * sizeof(*data));
    ASSERT(effect->data.starSpiritsEnergy != nullptr);

    data->moveMode = type & 0xFF00;
    type &= 0xFF;
    data->type = type;

    data->lifetime = 0;
    if (duration <= 0) {
        data->timeLeft = 1000;
    } else {
        data->timeLeft = duration;
    }

    data->fadeAlpha = 255;

    data->pos.x = x;
    data->pos.y = y;
    data->pos.z = z;
    data->scale = scale;

    data->primColor.r = 255;
    data->primColor.g = 255;
    data->primColor.b = 255;

    data->envColor.r = 255;
    data->envColor.g = 255;
    data->envColor.b = 255;
    data->envColor.a = 255;

    data->layerScale[0] = 1.0f;
    data->layerScale[1] = 0;
    data->layerScale[2] = 0;
    data->layerScale[3] = 0;
    data->layerAlpha[0] = 255;
    data->layerAlpha[1] = 0;
    data->layerAlpha[2] = 0;
    data->layerAlpha[3] = 0;

    if (type == 3) {
        data->state = STAR_SPIRITS_ENERGY_STATE_EXPAND;
    } else {
        data->state = STAR_SPIRITS_ENERGY_STATE_PULSE;
    }
    data->stateTime = 0;

    return effect;
}

void star_spirits_energy_init(EffectInstance* effect) {
}

void star_spirits_energy_update(EffectInstance* effect) {
    StarSpiritsEnergyFXData* data = effect->data.starSpiritsEnergy;
    s32 type = data->type;
    s32 lifetime;
    s32 i;
    s32 ringFrameIdx;
    f32 ringScale;
    u8 ringAlpha;

    if (effect->flags & FX_INSTANCE_FLAG_DISMISS) {
        effect->flags &= ~FX_INSTANCE_FLAG_DISMISS;
        data->timeLeft = 16;
    }

    if (data->timeLeft < 1000) {
        data->timeLeft--;
    }

    data->lifetime++;

    if (data->timeLeft < 0) {
        remove_effect(effect);
        return;
    }

    lifetime = data->lifetime;

    if (data->timeLeft < 16) {
        data->fadeAlpha = data->timeLeft * 16;
    }

    switch (data->state) {
        case STAR_SPIRITS_ENERGY_STATE_PULSE:
            data->layerAlpha[0] = (lifetime & 3) * 30 + 200;
            data->layerScale[0] = sin_deg(lifetime * 20) * 0.04 + 0.5;
            data->stateTime++;

            if (data->moveMode != 0) {
                data->pos.x += sin_deg(lifetime);
                data->pos.y += cos_deg(lifetime * 1.235631);
                if (data->stateTime > 50) {
                    data->stateTime = 0;
                    if (type == 3) {
                        data->state = STAR_SPIRITS_ENERGY_STATE_EXPAND_LONG;
                    } else {
                        data->state = STAR_SPIRITS_ENERGY_STATE_EXPAND;
                    }
                }
            }
            break;
        case STAR_SPIRITS_ENERGY_STATE_EXPAND_LONG:
            switch (data->stateTime) {
                case 0:
                    data->layerScale[3] = 4.0f;
                    data->layerAlpha[3] = 255;
                    break;
                case 1:
                    data->layerScale[3] = 8.0f;
                    data->layerAlpha[3] = 255;
                    break;
                default:
                    data->layerScale[3] = 0.0f;
                    data->layerAlpha[3] = 0;
                    break;
            }

            // after reaching the end of the table, hold on the final frame
            if (data->stateTime < ARRAY_COUNT(RingExpandFrames)) {
                ringFrameIdx = data->stateTime;
            } else {
                ringFrameIdx = ARRAY_COUNT(RingExpandFrames) - 1;
            }

            ringScale = RingExpandFrames[ringFrameIdx].scale * 0.01f + data->stateTime * 0.3f;
            ringAlpha = RingExpandFrames[ringFrameIdx].alpha;

            data->layerScale[0] = 0;
            data->layerAlpha[0] = 0;

            data->layerScale[1] = ringScale;
            data->layerAlpha[1] = ringAlpha;

            data->layerScale[2] = ringScale + 0.6;
            data->layerAlpha[2] = ringAlpha;

            data->stateTime++;
            break;
        case STAR_SPIRITS_ENERGY_STATE_EXPAND:
            switch (data->stateTime) {
                case 0:
                    data->layerScale[3] = 4.0f;
                    data->layerAlpha[3] = 255;
                    break;
                case 1:
                    data->layerScale[3] = 8.0f;
                    data->layerAlpha[3] = 255;
                    break;
                default:
                    data->layerScale[3] = 0.0f;
                    data->layerAlpha[3] = 0;
                    break;
            }

            ringScale = RingExpandFrames[data->stateTime].scale * 0.01;
            ringAlpha = RingExpandFrames[data->stateTime].alpha;

            data->layerScale[0] = 0;
            data->layerAlpha[0] = 0;

            data->layerScale[1] = ringScale;
            data->layerAlpha[1] = ringAlpha;

            data->layerScale[2] = ringScale * 1.2 + 4.0;
            data->layerAlpha[2] = ringAlpha;

            data->stateTime++;

            if (data->stateTime >= ARRAY_COUNT(RingExpandFrames)) {
                data->stateTime = 0;
                data->state = STAR_SPIRITS_ENERGY_STATE_CONTRACT;
            }
            break;
        case STAR_SPIRITS_ENERGY_STATE_CONTRACT:
            switch (ARRAY_COUNT(RingContractFrames) - 1 - data->stateTime) {
                case 0:
                    data->layerScale[3] = 4.0f;
                    data->layerAlpha[3] = 255;
                    break;
                case 1:
                    data->layerScale[3] = 8.0f;
                    data->layerAlpha[3] = 255;
                    break;
                default:
                    data->layerScale[3] = 0;
                    data->layerAlpha[3] = 0;
                    break;
            }
            ringScale = RingContractFrames[data->stateTime].scale * 0.01;
            ringAlpha = RingContractFrames[data->stateTime].alpha;

            data->layerScale[0] = 0;
            data->layerAlpha[0] = 0;

            data->layerScale[1] = ringScale;
            data->layerAlpha[1] = ringAlpha;

            data->layerScale[2] = 0.0f;
            data->layerAlpha[2] = 0;

            data->stateTime++;

            if (data->stateTime >= ARRAY_COUNT(RingContractFrames)) {
                data->stateTime = 0;
                data->state = STAR_SPIRITS_ENERGY_STATE_DONE;
            }
            break;
        case STAR_SPIRITS_ENERGY_STATE_DONE:
        default:
            data->layerScale[0] = 0.0f;
            data->layerAlpha[0] = 0;

            data->layerScale[1] = 0.0f;
            data->layerAlpha[1] = 0;

            data->layerScale[2] = 0.0f;
            data->layerAlpha[2] = 0;

            data->layerScale[3] = 0;
            data->layerAlpha[3] = 0;

            data->stateTime++;
            break;
    }

    for (i = 0; i < 4; i++) {
        if (data->layerAlpha[i] > 255) {
            data->layerAlpha[i] = 255;
        }
        if (data->layerAlpha[i] < 0) {
            data->layerAlpha[i] = 0;
        }
        if (data->layerScale[i] < 0.0f) {
            data->layerScale[i] = 0.0f;
        }
    }
}

void star_spirits_energy_render(EffectInstance* effect) {
    RenderTask renderTask;
    RenderTask* retTask;

    renderTask.appendGfx = star_spirits_energy_appendGfx;
    renderTask.appendGfxArg = effect;
    renderTask.dist = 10;
    renderTask.renderMode = RENDER_MODE_CLOUD_NO_ZCMP;

    retTask = queue_render_task(&renderTask);
    retTask->renderMode |= RENDER_TASK_FLAG_REFLECT_FLOOR;
}

void star_spirits_energy_appendGfx(void* effect) {
    StarSpiritsEnergyFXData* data = ((EffectInstance*)effect)->data.starSpiritsEnergy;
    s32 type = data->type;
    s32 alpha;
    Matrix4f sp20;
    s32 i;

    gDPPipeSync(gMainGfxPos++);
    gSPSegment(gMainGfxPos++, 0x09, VIRTUAL_TO_PHYSICAL(((EffectInstance*)effect)->shared->graphics));

    guPositionF(sp20, 0.0f, -gCameras[gCurrentCameraID].curYaw, 0.0f,
                     data->scale, data->pos.x, data->pos.y, data->pos.z);
    guMtxF2L(sp20, &gDisplayContext->matrixStack[gMatrixListPos]);

    gSPMatrix(gMainGfxPos++, &gDisplayContext->matrixStack[gMatrixListPos++],
              G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gMainGfxPos++, D_09004E00_412090);
    gDPSetEnvColor(gMainGfxPos++, data->envColor.r, data->envColor.g, data->envColor.b, data->envColor.a);

    for (i = 0; i < 4; i++) {
        if (type != 1 || i != 2) {
            if (data->layerScale[i] != 0.0f && data->layerAlpha[i] != 0) {
                guPositionF(sp20, 0.0f, 0.0f, 0.0f, data->layerScale[i], 0.0f, 0.0f, 0.0f);
                guMtxF2L(sp20, &gDisplayContext->matrixStack[gMatrixListPos]);

                gSPMatrix(gMainGfxPos++, &gDisplayContext->matrixStack[gMatrixListPos++],
                          G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
                gDPSetPrimColor(gMainGfxPos++, 0, 0,
                    data->primColor.r, data->primColor.g, data->primColor.b, data->layerAlpha[i]);
                gSPDisplayList(gMainGfxPos++, EnergyLayerGfx[i]);
                gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
            }
        }
    }

    gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);

    if (type == 2 || type == 3) {
        alpha = 0;

        if ((data->state == STAR_SPIRITS_ENERGY_STATE_EXPAND
                || data->state == STAR_SPIRITS_ENERGY_STATE_EXPAND_LONG)
            && data->stateTime > 2 && data->stateTime < 11) {
            alpha = 255 - (data->stateTime - 2) * 30;
        }

        if (data->state == STAR_SPIRITS_ENERGY_STATE_DONE && data->stateTime > 0 && data->stateTime < 9) {
            alpha = 255 - data->stateTime * 30;
        }

        if (alpha > 0) {
            gDPSetPrimColor(gMainGfxPos++, 0, 0, 208, 208, 208, alpha);
            gSPDisplayList(gMainGfxPos++, D_09005440_4126D0);
        }
    }

    gDPPipeSync(gMainGfxPos++);
}
