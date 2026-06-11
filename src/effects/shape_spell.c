#include "common.h"
#include "effects_internal.h"

typedef struct ShapeSpellElement {
    /* 0x00 */ u8 phase;
    /* 0x01 */ Color_RGB8 color;
    /* 0x04 */ Gfx* parentGfx;
    /* 0x08 */ Gfx* childGfx;
} ShapeSpellElement; // size = 0xC

extern Gfx D_09001080_33AFE0[];
extern Gfx D_09001128_33B088[];
extern Gfx D_09001150_33B0B0[];
extern Gfx D_09001178_33B0D8[];
extern Gfx D_090011A0_33B100[];
extern Gfx D_090011C8_33B128[];
extern Gfx D_090011F0_33B150[];

ShapeSpellElement D_E0024CC0[] = {
    {   0, { 255, 208,  26 }, D_09001128_33B088, D_090011A0_33B100 },
    { 120, {  77, 208, 254 }, D_09001150_33B0B0, D_090011C8_33B128 },
    { 240, { 254,  76, 110 }, D_09001178_33B0D8, D_090011F0_33B150 }
};

void shape_spell_appendGfx(void* effect);
void shape_spell_init(EffectInstance* effect);
void shape_spell_update(EffectInstance* effect);
void shape_spell_render(EffectInstance* effect);

EffectInstance* shape_spell_main(
    s32 isChild,
    f32 startX, f32 startY, f32 startZ,
    f32 endX, f32 endY, f32 endZ,
    s32 duration
) {
    EffectBlueprint bp;
    EffectBlueprint* bpPtr = &bp;
    EffectInstance* effect;
    ShapeSpellFXData* data;
    s32 numParts = 1;

    bp.init = shape_spell_init;
    bp.update = shape_spell_update;
    bp.renderScene = shape_spell_render;
    bp.unk_00 = 0;
    bp.renderUI = nullptr;
    bp.effectID = EFFECT_SHAPE_SPELL;

    effect = create_effect_instance(bpPtr);
    effect->numParts = numParts;
    data = effect->data.shapeSpell = general_heap_malloc(numParts * sizeof(*data));

    ASSERT(effect->data.shapeSpell != nullptr);

    data->age = 0;
    data->isChild = isChild;
    data->alpha = 255;
    data->pos.x = startX;
    data->pos.y = startY;
    data->pos.z = startZ;
    data->scale = 1.0f;
    if (!isChild) {
        data->offset.x = 0;
        data->offset.y = 0.0f;
        data->offset.z = 0.0f;
        data->timeLeft = duration;
        data->vel.x = (endX - startX) * (1.0f / duration);
        data->vel.y = (endY - startY) * (1.0f / duration);
        data->vel.z = (endZ - startZ) * (1.0f / duration);
    } else {
        data->offset.x = 29.f;
        data->offset.y = 0.0f;
        data->offset.z = 0.0f;
        data->vel.x = 6.2f;
        data->vel.y = 0.0f;
        data->vel.z = 0.0f;
        data->timeLeft = 24;
    }

    return effect;
}

void shape_spell_init(EffectInstance* effect) {
}

void shape_spell_update(EffectInstance* effect) {
    s32 flags = effect->flags;
    ShapeSpellFXData* data = effect->data.shapeSpell;
    s32 isChild;

    if (flags & FX_INSTANCE_FLAG_DISMISS) {
        effect->flags = flags & ~FX_INSTANCE_FLAG_DISMISS;
        data->timeLeft = 0;
    }

    data->timeLeft--;
    data->age++;

    if (data->timeLeft < 0) {
        remove_effect(effect);
        return;
    }

    isChild = data->isChild;

    if (!isChild && data->timeLeft == 0) {
        // parent projectiles leave a short radial burst at the endpoint.
        ShapeSpellFXData* newPart = shape_spell_main(
            1,
            data->pos.x + data->offset.x,
            data->pos.y + data->offset.y,
            data->pos.z + data->offset.z,
            0.0f, 0.0f, 0.0f, 24
        )->data.shapeSpell;
        newPart->scale = data->scale;
    }

    if (isChild == true) {
        data->alpha = data->alpha * 0.9;
        data->vel.x = data->vel.x * 0.83;
    }
    data->offset.x += data->vel.x;
    data->offset.y += data->vel.y;
    data->offset.z += data->vel.z;
}

void shape_spell_render(EffectInstance* effect) {
    RenderTask renderTask;
    RenderTask* retTask;

    renderTask.appendGfx = shape_spell_appendGfx;
    renderTask.appendGfxArg = effect;
    renderTask.dist = 0;
    renderTask.renderMode = RENDER_MODE_CLOUD_NO_ZCMP;

    retTask = queue_render_task(&renderTask);
    retTask->renderMode |= RENDER_TASK_FLAG_REFLECT_FLOOR;
}

s32 shape_spell_get_env_component(s32 base, s32 phase) {
    s32 absTime = gGameStatusPtr->frameCounter * 32;

    return (f32)(base + (sin_deg(absTime + phase) * (255 - base) + (255 - base)) * 0.5f);
}

s32 shape_spell_get_prim_component(s32 base, s32 phase) {
    s32 absTime = gGameStatusPtr->frameCounter * 32;

    return (f32)(base - (sin_deg(absTime + phase + 180) * base + base) * 0.5f);
}

void shape_spell_appendGfx(void* effect) {
    ShapeSpellFXData* data = ((EffectInstance*)effect)->data.shapeSpell;
    s32 isChild;
    Gfx* inlineGfxPos;
    Gfx* branchGfxPos;
    f32 scale = data->scale;
    s32 primA;
    f32 offsetX;
    f32 offsetY;
    f32 offsetZ;
    f32 angle;
    f32 orbitRadius;
    f32 yaw;
    s32 timeLeft;
    Matrix4f sp20;
    Mtx* orbitMtx[3];
    Mtx* mtx;
    s32 i;
    s32 j;

    gDPPipeSync(gMainGfxPos++);
    gSPSegment(gMainGfxPos++, 0x09, VIRTUAL_TO_PHYSICAL(((EffectInstance*)effect)->shared->graphics));
    gSPDisplayList(gMainGfxPos++, D_09001080_33AFE0);

    // reserve a spot for the branch
    branchGfxPos = gMainGfxPos++;

    // build a tiny reusable display list for three colored elements orbiting the primary offset
    // the parent draws it once; a child burst will reuse it 12 times
    inlineGfxPos = gMainGfxPos;
    isChild = data->isChild;
    primA = data->alpha;
    offsetX = data->offset.x;
    offsetY = data->offset.y;
    offsetZ = data->offset.z;
    timeLeft = data->timeLeft;

    if (isChild == 0) {
        angle = timeLeft * 35;
        orbitRadius = 9.0f;
        yaw = -gCameras[gCurrentCameraID].curYaw;
    } else {
        angle = timeLeft * 25;
        orbitRadius = 6.0f;
        yaw = 0.0f;
        offsetX *= scale;
    }

    for (i = 0; i < 3; i++) {
        if (i > 0) {
            if (!isChild) {
                angle -= 70.0f;
                offsetX -= 2.0f * data->vel.x;
                offsetY -= 2.0f * data->vel.y;
                offsetZ -= 2.0f * data->vel.z;
            } else {
                angle -= 50.0f;
                offsetX -= data->vel.x * (100.0 / 83) * 2.0;
            }
            primA = data->alpha * 100 / 255;
        }

        guPositionF(sp20, 0.0f, yaw, 0.0f, scale, offsetX, offsetY, offsetZ);
        guMtxF2L(sp20, &gDisplayContext->matrixStack[gMatrixListPos]);

        gSPMatrix(gMainGfxPos++, &gDisplayContext->matrixStack[gMatrixListPos++], G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);

        guTranslateF(sp20,
            sin_deg(angle) * orbitRadius,
            cos_deg(angle) * orbitRadius, 0.0f);

        angle += 120.0f;
        orbitMtx[0] = &gDisplayContext->matrixStack[gMatrixListPos++];

        guMtxF2L(sp20, orbitMtx[0]);
        guTranslateF(sp20,
            sin_deg(angle) * orbitRadius,
            cos_deg(angle) * orbitRadius, 0.0f);

        angle += 120.0f;
        orbitMtx[1] = &gDisplayContext->matrixStack[gMatrixListPos++];

        guMtxF2L(sp20, orbitMtx[1]);
        guTranslateF(sp20,
            sin_deg(angle) * orbitRadius,
            cos_deg(angle) * orbitRadius, 0.0f);

        orbitMtx[2] = &gDisplayContext->matrixStack[gMatrixListPos++];

        guMtxF2L(sp20, orbitMtx[2]);

        for (j = 0; j < 3; j++) {
            gSPMatrix(gMainGfxPos++, orbitMtx[j], G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
            gDPSetPrimColor(gMainGfxPos++, 0, 0,
                shape_spell_get_prim_component(D_E0024CC0[j].color.r, D_E0024CC0[j].phase),
                shape_spell_get_prim_component(D_E0024CC0[j].color.g, D_E0024CC0[j].phase),
                shape_spell_get_prim_component(D_E0024CC0[j].color.b, D_E0024CC0[j].phase),
                primA);
            gDPSetEnvColor(gMainGfxPos++,
                shape_spell_get_env_component(D_E0024CC0[j].color.r, D_E0024CC0[j].phase),
                shape_spell_get_env_component(D_E0024CC0[j].color.g, D_E0024CC0[j].phase),
                shape_spell_get_env_component(D_E0024CC0[j].color.b, D_E0024CC0[j].phase),
                255);
            gSPDisplayList(gMainGfxPos++, isChild ? D_E0024CC0[j].childGfx : D_E0024CC0[j].parentGfx);
            gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
        }

        gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
    }

    gSPEndDisplayList(gMainGfxPos++);

    // done, now write the branch
    gSPBranchList(branchGfxPos, gMainGfxPos);

    if (!isChild) {
        yaw = 0.0f;
    } else {
        yaw = -gCameras[gCurrentCameraID].curYaw;
    }

    // and write the main display list
    guPositionF(sp20, 0.0f, yaw, 0.0f, 1.0f, data->pos.x, data->pos.y, data->pos.z);
    guMtxF2L(sp20, &gDisplayContext->matrixStack[gMatrixListPos]);

    gSPMatrix(gMainGfxPos++, &gDisplayContext->matrixStack[gMatrixListPos++], G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);

    if (!isChild) {
        gSPDisplayList(gMainGfxPos++, inlineGfxPos);
    } else {
        guRotateF(sp20, 30.0f, 0.0f, 0.0f, 1.0f);

        mtx = &gDisplayContext->matrixStack[gMatrixListPos++];
        guMtxF2L(sp20, mtx);

        for (i = 0; i < 12; i++) {
            gSPMatrix(gMainGfxPos++, mtx, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);
            gSPDisplayList(gMainGfxPos++, inlineGfxPos);
        }
    }

    gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
    gDPPipeSync(gMainGfxPos++);
}
