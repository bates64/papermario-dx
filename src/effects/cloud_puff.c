#include "common.h"
#include "effects_internal.h"

extern Gfx D_090000E0_32ED30[];
extern Gfx D_090001B8_32EE08[];

void cloud_puff_init(EffectInstance* effect);
void cloud_puff_update(EffectInstance* effect);
void cloud_puff_render(EffectInstance* effect);
void cloud_puff_appendGfx(void* effect);

void cloud_puff_main(f32 x, f32 y, f32 z, f32 angle) {
    EffectBlueprint bp;
    EffectInstance* effect;
    f32 radialAngle;
    CloudPuffFXData* part;
    s32 numParts = 8;
    s32 i;

    bp.unk_00 = 0;
    bp.init = cloud_puff_init;
    bp.update = cloud_puff_update;
    bp.renderScene = cloud_puff_render;
    bp.renderUI = nullptr;
    bp.effectID = EFFECT_CLOUD_PUFF;

    effect = create_effect_instance(&bp);
    effect->numParts = numParts;
    part = general_heap_malloc(numParts * sizeof(*part));
    effect->data.cloudPuff = part;
    ASSERT(effect->data.cloudPuff != nullptr);

    mem_clear(part, numParts * sizeof(*part));

    for (i = 0; i < numParts; i++, part++) {
        part->alive = true;
        part->unk_40 = 0;
        part->pos.x = x;
        part->pos.y = y;
        part->pos.z = z;
        part->scale.x = 1.0f;
        part->scale.y = 1.0f;
        part->scale.z = 1.0f;
        part->alpha = 255;
        part->rescaleX = (rand_int(10) * 0.03) + 1.0;
        part->rescaleY = (rand_int(10) * 0.03) + 1.7;
        part->rescalePhase = effect_rand_int(60);
        part->timeLeft = 30;
        part->velY = 0.5f;
        part->accelY = -0.02f;
        part->jerkY = 0.00005f;
        part->radialVel = -3.9f;
        radialAngle = clamp_angle(angle + i * 45);
        part->dirX = sin_deg(radialAngle);
        part->dirZ = cos_deg(radialAngle);
    }
}

void cloud_puff_init(EffectInstance* effect) {
}

void cloud_puff_update(EffectInstance* effect) {
    CloudPuffFXData* part = effect->data.cloudPuff;
    s32 cond = false;
    s32 i;

    for (i = 0; i < effect->numParts; i++, part++) {
        if (part->alive) {
            part->timeLeft--;
            if (part->timeLeft <= 0) {
                part->alive = false;
            } else {
                cond = true;
                part->rescalePhase = clamp_angle(part->rescalePhase + 12.0f);
                part->scale.x = part->rescaleX + sin_deg(part->rescalePhase) * 0.1;
                part->scale.y = part->rescaleY + cos_deg(part->rescalePhase) * 0.1;
                part->radialVel *= 0.83;
                part->pos.x += part->radialVel * part->dirX;
                part->pos.z += part->radialVel * part->dirZ;
                part->rescaleX += (7.5 - part->rescaleX) * 0.006;
                part->accelY += part->jerkY;
                part->velY += part->accelY;
                part->pos.y += part->velY;
                part->rescaleY *= 0.98;

                if (part->timeLeft < 10) {
                    part->rescaleY *= 0.9;
                }

                if (part->timeLeft < 15) {
                    part->alpha -= 16;
                }
            }
        }
    }

    if (!cond) {
        remove_effect(effect);
    }
}

void cloud_puff_render(EffectInstance* effect) {
    RenderTask renderTask;
    RenderTask* retTask;

    renderTask.appendGfx = cloud_puff_appendGfx;
    renderTask.appendGfxArg = effect;
    renderTask.dist = 0;
    renderTask.renderMode = RENDER_MODE_PASS_THROUGH;

    retTask = queue_render_task(&renderTask);
    retTask->renderMode |= RENDER_TASK_FLAG_REFLECT_FLOOR;
}

void cloud_puff_appendGfx(void* effect) {
    EffectInstance* effectTemp = effect;
    CloudPuffFXData* part = effectTemp->data.cloudPuff;
    Matrix4f sp20;
    Matrix4f sp60;
    s32 i;

    gDPPipeSync(gMainGfxPos++);
    gSPSegment(gMainGfxPos++, 0x09, VIRTUAL_TO_PHYSICAL(effectTemp->shared->graphics));
    gSPDisplayList(gMainGfxPos++, D_090000E0_32ED30);

    for (i = 0; i < effectTemp->numParts; i++, part++) {
        if (part->alive) {
            guPositionF(sp20, 0.0f, -gCameras[gCurrentCameraID].curYaw, 0.0f, 1.0f,
                             part->pos.x, part->pos.y, part->pos.z);
            guScaleF(sp60, part->scale.x, part->scale.y, part->scale.z);
            guMtxCatF(sp60, sp20, sp20);
            guMtxF2L(sp20, &gDisplayContext->matrixStack[gMatrixListPos]);

            gDPSetPrimColor(gMainGfxPos++, 0, 0, 112, 96, 24, part->alpha);
            gSPMatrix(gMainGfxPos++, &gDisplayContext->matrixStack[gMatrixListPos++],
                        G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
            gSPDisplayList(gMainGfxPos++, D_090001B8_32EE08);
            gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
        }
    }
    gDPPipeSync(gMainGfxPos++);
}
