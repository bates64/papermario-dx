#include "common.h"
#include "effects_internal.h"

#define CARD_RING_ANGLE_SPACING (360.0f / 7)

extern Gfx D_09003F98_3FE448[];
extern Gfx D_09004010_3FE4C0[];
extern Gfx D_09004088_3FE538[];
extern Gfx D_09004100_3FE5B0[];
extern Gfx D_09004178_3FE628[];
extern Gfx D_090041F0_3FE6A0[];
extern Gfx D_09004268_3FE718[];
extern Gfx D_090042E0_3FE790[];
extern Gfx D_09004360_3FE810[];
extern Gfx D_09004458_3FE908[];
extern Gfx D_09004508_3FE9B8[];
extern Gfx D_09004600_3FEAB0[];

Gfx* D_E0116C60[] = { D_09004458_3FE908 };

Gfx* D_E0116C64[] = { D_09004600_3FEAB0 };

Gfx* D_E0116C68[] = { D_09004360_3FE810 };

Gfx* D_E0116C6C[] = { D_09004508_3FE9B8 };

Gfx* D_E0116C70[] = {
    D_09003F98_3FE448, D_09004010_3FE4C0, D_09004088_3FE538,
    D_09004100_3FE5B0, D_09004178_3FE628, D_090041F0_3FE6A0,
    D_09004268_3FE718
};

Color_RGB8 CardRingSpiritColors[] = {
    { 255, 224,  65 },
    { 244, 227,  72 },
    { 211, 220,  22 },
    { 152, 214, 222 },
    { 211, 138, 239 },
    { 231, 174, 219 },
    { 255, 200,  11 },
};

s16 CardRingSpinAngles[] = {
    0, 60, 120, 180, 240, 300,
    0, 60, 120, 180, 240, 300,
    0, 60, 120, 180, 240, 300,
    0, 60, 120, 180, 240, 300,
    0, 30, 60, 90, 120, 150, 180, 210, 240, 270, 300, 330, 345, 353, 357, 359,
    0
};

u8 CardRingPrimAlphas[] = {
    2, 20, 40, 60, 80, 100, 120, 160, 180, 200, 220, 240, 255
};

u8 CardRingEnvAlphas[] = {
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
     20,  40,  60,  80, 100, 120, 160, 180, 200, 220,
    240, 255,
};

u8 CardRingColorScales[] = {
    255, 255, 255, 255, 255, 255, 255, 225, 185, 165, 148, 128,
    255, 255, 255, 255, 255, 255, 255, 225, 185, 165, 148, 128,
    255, 255, 255, 255, 255, 255, 255, 225, 185, 165, 148, 128,
    255, 255, 255, 255, 255, 255, 255, 225, 185, 165, 148, 128,
};

u8 CardRingScales[] = {
    50, 80, 100, 105, 107, 108, 108, 108, 108, 108, 108, 107, 105, 100, 95, 90, 85, 80, 75, 70, 65, 60, 55, 50
};

void something_rotating_init(EffectInstance* effect);
void something_rotating_update(EffectInstance* effect);
void something_rotating_render(EffectInstance* effect);
void something_rotating_appendGfx(void* effect);

EffectInstance* something_rotating_main(
    s32 type,
    f32 x,
    f32 y,
    f32 z,
    f32 scale,
    s32 duration
) {
    EffectBlueprint bp;
    EffectInstance* effect;
    SomethingRotatingFXData* part;
    s32 numParts = 8;
    s32 i;

    bp.init = something_rotating_init;
    bp.update = something_rotating_update;
    bp.renderScene = something_rotating_render;
    bp.unk_00 = 0;
    bp.renderUI = nullptr;
    bp.effectID = EFFECT_SOMETHING_ROTATING;

    effect = create_effect_instance(&bp);
    effect->numParts = numParts;
    part = effect->data.somethingRotating = general_heap_malloc(numParts * sizeof(*part));
    ASSERT(effect->data.somethingRotating != nullptr);

    part->type = type;
    part->lifetime = 0;
    if (duration <= 0) {
        part->timeLeft = 1000;
    } else {
        part->timeLeft = duration;
    }
    part->pos.x = x;
    part->pos.y = y;
    part->pos.z = z;
    part->scale = scale;
    part->tiltAngle = 30.0f;
    part->spinAngle = 0.0f;

    part++;
    for (i = 1; i < numParts; i++, part++) {
        part->primAlpha = 0;
        part->scale = scale * 0.5;
        part->env.r = 255;
        part->env.g = 255;
        part->env.b = 0;
        part->envAlpha = 0;
        part->tiltAngle = 30.0f;
        part->spinAngle = 0.0f;
        part->state = CARD_RING_STATE_IDLE;
        part->radius = 50.0f;
    }

    return effect;
}

void something_rotating_init(EffectInstance* effect) {
}

void something_rotating_update(EffectInstance* effect) {
    SomethingRotatingFXData* part = effect->data.somethingRotating;
    f32 x = part->pos.x;
    f32 y = part->pos.y;
    f32 z = part->pos.z;
    s32 baseTime; // time for base part
    s32 time;
    f32 factor;
    f32 pitch;
    s32 i;

    if (effect->flags & FX_INSTANCE_FLAG_DISMISS) {
        effect->flags &= ~FX_INSTANCE_FLAG_DISMISS;
        part->timeLeft = 32;
    }

    if (part->timeLeft < 1000) {
        part->timeLeft--;
    }

    part->lifetime++;

    if (part->timeLeft < 0) {
        remove_effect(effect);
        return;
    }

    part->spinAngle = 90.0f;
    pitch = 90.0f;
    baseTime = part->lifetime;

    part++;
    for (i = 1; i < effect->numParts; i++, part++) {
        f32 roll = baseTime * 4.0f + i * CARD_RING_ANGLE_SPACING;
        f32 radial = sin_deg(roll); // xz component
        f32 radius = part->radius;

        part->pos.x = x + radius * sin_deg(pitch) * radial;
        part->pos.y = y + radius * cos_deg(roll);
        part->pos.z = z + radius * cos_deg(pitch) * radial;

        switch (part->state) {
            case CARD_RING_STATE_CAPTURE_INIT:
                part->lifetime = 0;
                part->state = CARD_RING_STATE_CAPTURE;
                // fallthrough
            case CARD_RING_STATE_CAPTURE:
                time = part->lifetime;

                if (time < ARRAY_COUNT(CardRingSpinAngles)) {
                    part->spinAngle = CardRingSpinAngles[time];
                } else {
                    part->spinAngle = CardRingSpinAngles[ARRAY_COUNT(CardRingSpinAngles) - 1];
                }
                if (time < ARRAY_COUNT(CardRingPrimAlphas)) {
                    part->primAlpha = CardRingPrimAlphas[time];
                } else {
                    part->primAlpha = CardRingPrimAlphas[ARRAY_COUNT(CardRingPrimAlphas) - 1];
                }
                if (time < ARRAY_COUNT(CardRingEnvAlphas)) {
                    part->envAlpha = CardRingEnvAlphas[time];
                } else {
                    part->envAlpha = CardRingEnvAlphas[ARRAY_COUNT(CardRingEnvAlphas) - 1];
                }

                if (time < ARRAY_COUNT(CardRingColorScales)) {
                    factor = CardRingColorScales[time];
                } else {
                    factor = CardRingColorScales[ARRAY_COUNT(CardRingColorScales) - 1];
                }

                factor /= 255.0f;
                part->env.r = factor * CardRingSpiritColors[i - 1].r;
                part->env.g = factor * CardRingSpiritColors[i - 1].g;
                part->env.b = factor * CardRingSpiritColors[i - 1].b;

                if (time < ARRAY_COUNT(CardRingScales)) {
                    part->scale = (f32) CardRingScales[time] * 0.01;
                } else {
                    part->scale = (f32) CardRingScales[ARRAY_COUNT(CardRingScales) - 1] * 0.01;
                }
                break;
            case CARD_RING_STATE_GATHER_INIT:
                part->lifetime = 0;
                part->state = CARD_RING_STATE_GATHER;
                // fallthrough
            case CARD_RING_STATE_GATHER:
                time = part->lifetime;

                if (time < 18) {
                    part->radius = (sin_deg(90 - time * 10) + 1.0f) * 50.0f * 0.5;
                } else {
                    part->radius = 0.0f;
                    part->state = CARD_RING_STATE_DONE;
                }

                break;
            case CARD_RING_STATE_DONE:
                break;
        }

        part->lifetime++;
    }
}

void something_rotating_render(EffectInstance* effect) {
    RenderTask renderTask;
    RenderTask* retTask;

    renderTask.appendGfx = something_rotating_appendGfx;
    renderTask.appendGfxArg = effect;
    renderTask.dist = 10;
    renderTask.renderMode = RENDER_MODE_SURFACE_XLU_LAYER1;

    retTask = queue_render_task(&renderTask);
    retTask->renderMode |= RENDER_TASK_FLAG_REFLECT_FLOOR;
}

void something_rotating_transform_card(b32 ignoreCameraYaw, SomethingRotatingFXData* part) {
    Matrix4f mtxTransform;
    Matrix4f mtxTemp;
    f32 yaw;

    if (!ignoreCameraYaw) {
        yaw = gCameras[gCurrentCameraID].curYaw;
    } else {
        yaw = 0.0f;
    }

    guPositionF(mtxTransform, 0.0f, part->spinAngle - yaw, 0.0f, part->scale,
        part->pos.x + 2.0f,
        part->pos.y,
        part->pos.z + 2.0f
    );
    guRotateF(mtxTemp, part->tiltAngle, 0.0f, 0.0f, 1.0f);
    guMtxCatF(mtxTemp, mtxTransform, mtxTransform);
    guTranslateF(mtxTemp, 0.0f, 0.0f, -2.0f);
    guMtxCatF(mtxTemp, mtxTransform, mtxTransform);
    guMtxF2L(mtxTransform, &gDisplayContext->matrixStack[gMatrixListPos]);

    gSPMatrix(gMainGfxPos++, &gDisplayContext->matrixStack[gMatrixListPos++],
              G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
}

void something_rotating_appendGfx(void* effect) {
    SomethingRotatingFXData* data = ((EffectInstance*)effect)->data.somethingRotating;
    s32 time = data->lifetime;
    s32 l, t;
    s32 i;

    gDPPipeSync(gMainGfxPos++);
    gSPSegment(gMainGfxPos++, 0x09, VIRTUAL_TO_PHYSICAL(((EffectInstance*)effect)->shared->graphics));

    gSPDisplayList(gMainGfxPos++, D_090042E0_3FE790);
    gDPSetEnvColor(gMainGfxPos++, 0, 0, 0, 255);

    data++;
    for (i = 1; i < ((EffectInstance*)effect)->numParts; i++, data++) {
        if (data->state != CARD_RING_STATE_DONE) {
            something_rotating_transform_card(true, data);
            if (data->primAlpha != 255) {
                gDPSetPrimColor(gMainGfxPos++, 0, 0, 0, 0, 0, data->primAlpha);
                gDPSetEnvColor(gMainGfxPos++, data->env.r, data->env.g, data->env.b, 120);
                gSPDisplayList(gMainGfxPos++, D_E0116C6C[0]);

                l = ((time * 4.0f) * 100.0f) * (1.0 / 1024);
                t = ((time * 4.0f) * 40.0f) * (1.0 / 1024);
                gDPSetTileSize(gMainGfxPos++, G_TX_RENDERTILE, l, t, l + 0xFC, t + 0xFC);

                l = ((time * 4.0f) * 200.0f) * (1.0 / 1024);
                t = ((time * 4.0f) * 90.0f) * (1.0 / 1024);
                gDPSetTileSize(gMainGfxPos++, G_TX_EXTRA_TILE, l, t, l + 0xFC, t + 0xFC);
                gSPDisplayList(gMainGfxPos++, D_E0116C64[0]);
            } else {
                gSPDisplayList(gMainGfxPos++, D_E0116C68[0]);
                gDPSetEnvColor(gMainGfxPos++, data->env.r, data->env.g, data->env.b, data->envAlpha);
                gSPDisplayList(gMainGfxPos++, D_E0116C70[i - 1]);
                gSPDisplayList(gMainGfxPos++, D_E0116C60[0]);
            }
            gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
        }
    }
}
