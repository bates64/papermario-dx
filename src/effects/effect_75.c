#include "common.h"
#include "effects_internal.h"

extern Gfx D_09001910_3E4270[];
extern Gfx D_09001A00_3E4360[];
extern Gfx D_09001A20_3E4380[];

Gfx* D_E00EAA50[2] = { D_09001A00_3E4360, D_09001A20_3E4380 };
Gfx* D_E00EAA58[2] = { D_09001910_3E4270, nullptr };

void effect_75_init(EffectInstance* effect);
void effect_75_update(EffectInstance* effect);
void effect_75_render(EffectInstance* effect);
void effect_75_appendGfx(void* effect);

EffectInstance* effect_75_main(s32 type, f32 posX, f32 posY, f32 posZ, f32 scale, s32 duration) {
    EffectBlueprint bp;
    EffectInstance* effect;
    StarWarpFXData* data;
    s32 numParts = 1;

    bp.init = effect_75_init;
    bp.update = effect_75_update;
    bp.renderScene = effect_75_render;
    bp.unk_00 = 0;
    bp.renderUI = nullptr;
    bp.effectID = EFFECT_75;

    effect = create_effect_instance(&bp);
    effect->numParts = numParts;
    data = effect->data.starWarp = general_heap_malloc(numParts * sizeof(*data));
    ASSERT(effect->data.starWarp != nullptr);

    data->type = type;
    data->lifetime = 0;
    if (duration <= 0) {
        data->timeLeft = FX_TIME_FOREVER;
    } else {
        data->timeLeft = duration;
    }
    data->fadeAlpha = 0;
    data->pos.x = posX;
    data->pos.y = posY;
    data->pos.z = posZ;
    data->scale = scale;
    data->primCol.r = 0;
    data->primCol.g = 180;
    data->primCol.b = 220;
    data->envCol.r = 0;
    data->envCol.g = 0;
    data->envCol.b = 0;
    data->curPrimAlpha = 0;
    data->masterAlpha = 0;
    data->texPanMain.x = 0;
    data->texPanMain.y = 0;
    data->texPanAux.x = 0;
    data->texPanAux.y = 0;
    data->texVelMain.x = 1.0f;
    data->targetTexVelMain.x = 1.0f;
    data->texVelMain.y = 0.9f;
    data->targetTexVelMain.y = 0.9f;
    data->texVelAux.x = -2.0f;
    data->targetTexVelAux.x = -2.0f;
    data->texVelAux.y = 1.25f;
    data->targetTexVelAux.y = 1.25f;
    data->minPrimAlpha = 190.0f;
    data->targetMinPrimAlpha = 190.0f;
    data->maxPrimAlpha = 220.0f;
    data->targetMaxPrimAlpha = 220.0f;

    return effect;
}

void effect_75_init(EffectInstance* effect) {
}

void effect_75_update(EffectInstance* effect) {
    StarWarpFXData* data = effect->data.starWarp;
    s32 lifetime;

    if (effect->flags & FX_INSTANCE_FLAG_DISMISS) {
        effect->flags &= ~FX_INSTANCE_FLAG_DISMISS;
        data->timeLeft = 16;
    }

    if (data->timeLeft < FX_TIME_FOREVER) {
        data->timeLeft--;
    }

    data->lifetime++;
    if (data->lifetime > 30*60*60) {
        data->lifetime = 0;
    }

    if (data->timeLeft < 0) {
        remove_effect(effect);
        return;
    }

    lifetime = data->lifetime;

    if (data->timeLeft < 16) {
        data->fadeAlpha = data->timeLeft * 16;
    }

    if (lifetime < 16) {
        data->fadeAlpha = lifetime * 16 + 15;
    }

    data->texVelMain.x += (data->targetTexVelMain.x - data->texVelMain.x) * 0.1;
    data->texVelMain.y += (data->targetTexVelMain.y - data->texVelMain.y) * 0.1;
    data->texVelAux.x += (data->targetTexVelAux.x - data->texVelAux.x) * 0.1;
    data->texVelAux.y += (data->targetTexVelAux.y - data->texVelAux.y) * 0.1;
    data->minPrimAlpha += (data->targetMinPrimAlpha - data->minPrimAlpha) * 0.1;
    data->maxPrimAlpha += (data->targetMaxPrimAlpha - data->maxPrimAlpha) * 0.1;

    data->texPanMain.x += 2.0f * data->texVelMain.x;
    data->texPanMain.y += 2.0f * data->texVelMain.y;
    data->texPanAux.x += 2.0f * data->texVelAux.x;
    data->texPanAux.y += 2.0f * data->texVelAux.y;

    if (data->texPanMain.x < 0.0f) {
        data->texPanMain.x += 256.0f;
    }
    if (data->texPanMain.y < 0.0f) {
        data->texPanMain.y += 256.0f;
    }
    if (data->texPanAux.x < 0.0f) {
        data->texPanAux.x += 256.0f;
    }
    if (data->texPanAux.y < 0.0f) {
        data->texPanAux.y += 256.0f;
    }

    if (data->texPanMain.x > 256.0f) {
        data->texPanMain.x -= 256.0f;
    }
    if (data->texPanMain.y > 256.0f) {
        data->texPanMain.y -= 256.0f;
    }
    if (data->texPanAux.x > 256.0f) {
        data->texPanAux.x -= 256.0f;
    }
    if (data->texPanAux.y > 256.0f) {
        data->texPanAux.y -= 256.0f;
    }

    data->curPrimAlpha = data->minPrimAlpha
        + (sin_deg(lifetime * 20) * (data->maxPrimAlpha - data->minPrimAlpha)
        + (data->maxPrimAlpha - data->minPrimAlpha)) * 0.5;
}

void effect_75_render(EffectInstance* effect) {
    StarWarpFXData* data = effect->data.starWarp;
    RenderTask renderTask;
    RenderTask* renderTaskPtr = &renderTask;
    RenderTask* retTask;
    s32 outDist;
    f32 outX;
    f32 outY;
    f32 outZ;
    f32 outS;

    transform_point(gCameras[gCurrentCameraID].mtxPerspective,
        data->pos.x, data->pos.y, data->pos.z, 1.0f,
        &outX, &outY, &outZ, &outS);

    outDist = outZ + 5000;
    if (outDist < 0) {
        outDist = 0;
    } else if (outDist > 10000) {
        outDist = 10000;
    }

    if (outS < 0.01 && -0.01 < outS) {
        outDist = 0;
    }

    renderTaskPtr->appendGfx = effect_75_appendGfx;
    renderTaskPtr->dist = -outDist;
    renderTaskPtr->appendGfxArg = effect;
    renderTaskPtr->renderMode = RENDER_MODE_SURFACE_XLU_LAYER1;

    retTask = queue_render_task(renderTaskPtr);
    retTask->renderMode |= RENDER_TASK_FLAG_REFLECT_FLOOR;
}

void func_E00EA664(void) {
}

void effect_75_appendGfx(void* effect) {
    StarWarpFXData* data = ((EffectInstance*)effect)->data.starWarp;
    Camera* camera = &gCameras[gCurrentCameraID];
    s32 variation = data->type;
    s32 uls0 = data->texPanMain.x * 4.0f;
    s32 ult0 = data->texPanMain.y * 4.0f;
    s32 uls1 = data->texPanAux.x * 4.0f;
    s32 ult1 = data->texPanAux.y * 4.0f;
    Matrix4f mtxTransfrom;
    Matrix4f mtxTemp;

    gDPPipeSync(gMainGfxPos++);
    gSPSegment(gMainGfxPos++, 0x09, VIRTUAL_TO_PHYSICAL(((EffectInstance*)effect)->shared->graphics));

    guTranslateF(mtxTransfrom, data->pos.x, data->pos.y, data->pos.z);
    guScaleF(mtxTemp, data->scale, data->scale, data->scale);
    guMtxCatF(mtxTemp, mtxTransfrom, mtxTransfrom);
    if (variation == 1) {
        guRotateF(mtxTemp, 180.0f, 0.0f, 0.0f, 1.0f);
        guMtxCatF(mtxTemp, mtxTransfrom, mtxTransfrom);
    }
    guMtxF2L(mtxTransfrom, &gDisplayContext->matrixStack[gMatrixListPos]);

    gSPMatrix(gMainGfxPos++, &gDisplayContext->matrixStack[gMatrixListPos++], G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPMatrix(gMainGfxPos++, camera->mtxBillboard, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);
    gDPSetPrimColor(gMainGfxPos++, 0, 0, data->primCol.r, data->primCol.g, data->primCol.b, data->curPrimAlpha);
    gDPSetEnvColor(gMainGfxPos++, data->envCol.r, data->envCol.g, data->envCol.b,
        data->fadeAlpha * data->masterAlpha / 255);
    gSPDisplayList(gMainGfxPos++, D_E00EAA58[0]);
    gDPSetTileSize(gMainGfxPos++, G_TX_RENDERTILE, uls0, ult0, uls0 + 252, ult0 + 252);
    gDPSetTileSize(gMainGfxPos++, G_TX_EXTRA_TILE, uls1, ult1, uls1 + 252, ult1 + 252);
    gSPDisplayList(gMainGfxPos++, D_E00EAA50[variation]);
    gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
}
