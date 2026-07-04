#include "common.h"
#include "effects_internal.h"

extern Gfx D_09000240_37D3C0[];
extern Gfx D_090002E8_37D468[];

void effect_3D_init(EffectInstance* effect);
void effect_3D_update(EffectInstance* effect);
void effect_3D_render(EffectInstance* effect);
void effect_3D_appendGfx(void* effect);

void effect_3D_main(s32 type, f32 x, f32 y, f32 z, f32 vx, f32 vy, f32 vz, s32 count, EffectInstance** outEffect) {
    EffectBlueprint bp;
    EffectBlueprint* bpPtr = &bp;
    EffectInstance* effect;
    Effect3DFXData* part;
    f32 vel;
    f32 temp_f28;
    f32 temp_f30;
    f32 sp70;
    Matrix4f sp30;
    s32 i;

    if (count != 0) {
        count++;

        vel = SQ(vx) + SQ(vy) + SQ(vz);
        if (vel != 0.0f) {
            vel = -1.0f / sqrtf(vel);

            vx *= vel;
            vy *= vel;
            vz *= vel;

            if (vx != 0.0f) {
                sp70 = 1.0f;
                temp_f30 = -vy / vx;
                temp_f28 = 0.0f;
            } else if (vy != 0.0f) {
                sp70 = -vx / vy;
                temp_f30 = 1.0f;
                temp_f28 = 0.0f;
            } else {
                sp70 = 0.0f;
                temp_f30 = 1.0f;
                temp_f28 = -vx / vz;
            }

            vel = SQ(temp_f30) + SQ(sp70) + SQ(temp_f28);
            if (vel != 0.0f) {
                vel = 1.0f / sqrtf(vel);

                temp_f30 *= vel;
                sp70 *= vel;
                temp_f28 *= vel;

                temp_f30 *=  8.0f;
                sp70 *= 8.0f;
                temp_f28 *= 8.0f;
                vx *= 8.0f;
                vy *= 8.0f;
                vz *= 8.0f;

                bpPtr->unk_00 = 0;
                bpPtr->init = effect_3D_init;
                bpPtr->update = effect_3D_update;
                bpPtr->renderScene = effect_3D_render;
                bpPtr->renderUI = nullptr;
                bpPtr->effectID = EFFECT_3D;

                effect = create_effect_instance(bpPtr);
                effect->numParts = count;
                part = effect->data.whaleSpout = general_heap_malloc(count * sizeof(*part));
                ASSERT(effect->data.whaleSpout != nullptr);

                part->unk_04 = 0;
                part->unk_00 = type;
                part->pos.x = x;
                part->pos.y = y;
                part->pos.z = z;
                part->timeLeft = 10;
                part->lifetime = 0;

                part++;
                for (i = 1; i < count; i++, part++) {
                    part->pos.x = 0;
                    part->pos.y = 0;
                    part->pos.z = 0;
                    guRotateF(sp30, i * 72, vx, vy, vz);
                    part->vel.x = part->unk_20 = 2.0f * vx;
                    part->vel.y = part->unk_24 = 2.0f * vy;
                    part->vel.z = part->unk_28 = 2.0f * vz;
                    part->unk_38 = -vx * 0.05 * 4.0;
                    part->unk_3C = -vy * 0.05 * 4.0;
                    part->unk_40 = -vz * 0.05 * 4.0;
                    part->unk_2C = (sp30[0][0] * temp_f30 + sp30[1][0] * sp70 + sp30[2][0] * temp_f28) * 0.1 * 4.0;
                    part->unk_30 = (sp30[0][1] * temp_f30 + sp30[1][1] * sp70 + sp30[2][1] * temp_f28) * 0.1 * 4.0;
                    part->unk_34 = (sp30[0][2] * temp_f30 + sp30[1][2] * sp70 + sp30[2][2] * temp_f28) * 0.1 * 4.0;
                    part->unk_44 = 0.5f;
                    part->unk_48 = 4.0f;
                    part->unk_50 = 20.0f;
                    part->unk_4C = part->unk_54 = effect_rand_int(360);
                    part->unk_58 = 255;
                    part->unk_64 = ((i - 1) / 5) * 2;
                    part->timeLeft = 10;
                }

                *outEffect = effect;
            }
        }
    }
}

void effect_3D_init(EffectInstance* effect) {
}

void effect_3D_update(EffectInstance* effect) {
    Effect3DFXData* part = effect->data.whaleSpout;
    s32 unk_04 = part->unk_04;
    s32 unk_5C;
    s32 saved_5C;
    s32 i;

    part->timeLeft--;
    part->lifetime++;

    if (part->timeLeft < 0 && unk_04 == 2) {
        remove_effect(effect);
        return;
    }

    saved_5C = part->timeLeft;

    part++;
    for (i = 1; i < effect->numParts; i++, part++) {
        if (part->unk_64 <= 0 || --part->unk_64 <= 0) {
            unk_5C = --part->timeLeft;
            if (unk_5C < 0) {
                if (unk_04 == 0) {
                    part->unk_58 = 255;
                    part->pos.x = 0.0f;
                    part->pos.y = 0.0f;
                    part->pos.z = 0.0f;
                    part->vel.x = part->unk_20;
                    part->vel.y = part->unk_24;
                    part->vel.z = part->unk_28;
                    part->unk_44 = 0.5f;
                    part->unk_48 = 4.0f;
                    part->unk_50 = 20.0f;
                    part->unk_4C = part->unk_54;
                    part->timeLeft = 9;
                    unk_5C = 9;
                } else {
                    part->pos.x = 0.0f;
                    part->pos.y = 0.0f;
                    part->pos.z = 0.0f;
                    part->vel.x = 0.0f;
                    part->vel.y = 0.0f;
                    part->vel.z = 0.0f;
                    part->unk_58 = 0;
                    part->timeLeft = 0;
                }
            }

            if (unk_5C >= 4 && unk_5C <= 6) {
                part->vel.x += part->unk_2C;
                part->vel.y += part->unk_30;
                part->vel.z += part->unk_34;
            }

            if (unk_5C < 8) {
                part->unk_44 += (3.0 - part->unk_44) * 0.03 * 8.0;
                part->unk_48 += (0.5 - part->unk_48) * 0.03 * 6.0;
            }

            part->vel.x += part->unk_38;
            part->vel.y += part->unk_3C;
            part->vel.z += part->unk_40;

            if (part->vel.y < 0.0f) {
                part->unk_50 *= 0.2;
                part->vel.x *= 0.225;
                part->vel.y *= 0.45;
                part->vel.z *= 0.225;
                part->unk_58 *= 0.8;
            }

            part->pos.x += part->vel.x;
            part->pos.y += part->vel.y;
            part->pos.z += part->vel.z;
            part->unk_4C += part->unk_50;
        }
    }

    if (saved_5C < 0) {
        part = effect->data.whaleSpout;
        part->timeLeft = 10;
        part->lifetime = 0;
    }
}

void effect_3D_render(EffectInstance* effect) {
    RenderTask renderTask;
    RenderTask* retTask;

    renderTask.appendGfx = effect_3D_appendGfx;
    renderTask.appendGfxArg = effect;
    renderTask.dist = 0;
    renderTask.renderMode = RENDER_MODE_CLOUD_NO_ZCMP;

    retTask = queue_render_task(&renderTask);
    retTask->renderMode |= RENDER_TASK_FLAG_REFLECT_FLOOR;
}

void func_E007A884(void) {
}

void effect_3D_appendGfx(void* effect) {
    Effect3DFXData* part = ((EffectInstance*)effect)->data.whaleSpout;
    Matrix4f sp18;
    Matrix4f sp58;
    s32 i;

    gDPPipeSync(gMainGfxPos++);
    gSPSegment(gMainGfxPos++, 0x09, VIRTUAL_TO_PHYSICAL(((EffectInstance*)effect)->shared->graphics));
    gSPDisplayList(gMainGfxPos++, D_09000240_37D3C0);

    guTranslateF(sp18, part->pos.x, part->pos.y, part->pos.z);
    guMtxF2L(sp18, &gDisplayContext->matrixStack[gMatrixListPos]);

    gSPMatrix(gMainGfxPos++, &gDisplayContext->matrixStack[gMatrixListPos++], G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    part++;
    for (i = 1; i < ((EffectInstance*)effect)->numParts; i++, part++) {
        gDPSetPrimColor(gMainGfxPos++, 0, 0, 200, 255, 255, part->unk_58);

        guTranslateF(sp18, part->pos.x, part->pos.y, part->pos.z);
        guRotateF(sp58, -gCameras[gCurrentCameraID].curYaw, 0.0f, 1.0f, 0.0f);
        guMtxCatF(sp58, sp18, sp18);
        guScaleF(sp58, part->unk_44, part->unk_48, part->unk_44);
        guMtxCatF(sp58, sp18, sp18);
        guRotateF(sp58, part->unk_4C, 0.0f, 0.0f, 1.0f);
        guMtxCatF(sp58, sp18, sp18);
        guMtxF2L(sp18, &gDisplayContext->matrixStack[gMatrixListPos]);

        gSPMatrix(gMainGfxPos++, &gDisplayContext->matrixStack[gMatrixListPos++], G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
        gSPDisplayList(gMainGfxPos++, D_090002E8_37D468);
        gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
    }

    gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
    gDPPipeSync(gMainGfxPos++);
}
