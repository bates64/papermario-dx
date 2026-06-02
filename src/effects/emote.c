#include "common.h"
#include "effects_internal.h"

extern Gfx D_09002170_336DE0[];
extern Gfx D_09002238_336EA8[];
extern Gfx D_090022E0_336F50[];
extern Gfx D_09002308_336F78[];
extern Gfx D_090023B0_337020[];
extern Gfx D_090023D8_337048[];
extern Gfx D_09002480_3370F0[];
extern Gfx D_090024A8_337118[];
extern Gfx D_09002550_3371C0[];
extern Gfx D_09002578_3371E8[];

Gfx* EmoteGfxDrawModel[] = {
    [EMOTE_EXCLAMATION] D_090022E0_336F50,
    [EMOTE_SHOCK]       nullptr,
    [EMOTE_QUESTION]    D_090023B0_337020,
    [EMOTE_FRUSTRATION] D_09002480_3370F0,
    [EMOTE_ELLIPSIS]    D_09002550_3371C0,
};

Gfx* EmoteGfxSetupTex[] = {
    [EMOTE_EXCLAMATION] D_09002238_336EA8,
    [EMOTE_SHOCK]       nullptr,
    [EMOTE_QUESTION]    D_09002308_336F78,
    [EMOTE_FRUSTRATION] D_090023D8_337048,
    [EMOTE_ELLIPSIS]    D_090024A8_337118,
};

s8 EmoteExclamationFrames[] = {
    0, 0, 1, 2, 3, 5, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5,
    -1
};

s8 EmoteShockFrames[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
    -1
};

s8 EmoteQuestionFrames[] = {
    0, 0, 2, 1, 3, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3,
    -1,
};

s8 EmoteFrustrationFrames[] = {
    0, 0, 1, 1, 2, 2, 3, 3,
    -13
};

s8 EmoteEllipsisFrames[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    -1
};

s8* EmoteAnimFrames[] = {
    [EMOTE_EXCLAMATION] EmoteExclamationFrames,
    [EMOTE_SHOCK]       EmoteShockFrames,
    [EMOTE_QUESTION]    EmoteQuestionFrames,
    [EMOTE_FRUSTRATION] EmoteFrustrationFrames,
    [EMOTE_ELLIPSIS]    EmoteEllipsisFrames,
};

Color_RGB8 EmoteFrustrationColors[] = {
    { 64,  0,  0 },
    { 32,  0, 32 },
    {  0,  0, 64 },
    {  0, 32, 32 },
    {  0, 64,  0 },
    { 32, 32,  0 },
    {  0,  0,  0 },
};

void emote_init(EffectInstance* effect);
void emote_update(EffectInstance* effect);
void emote_render(EffectInstance* effect);
void emote_appendGfx(void* effect);

void emote_compute_world_rotpos(EmoteFXData* part, s32 index) {
    Npc* npc = part->owner;
    f32 radius = part->radius;
    Matrix4f rotMtx;
    f32 sinCam, cosCam;

    part->rotAngle = part->pitch - 20.0f + index * 20;
    part->scale = (radius / 12.0f) * 0.5f + 0.5;

    sinCam = sin_deg(gCameras[gCurrentCameraID].curYaw);
    cosCam = cos_deg(gCameras[gCurrentCameraID].curYaw);
    guRotateF(rotMtx, -part->rotAngle, sinCam, 0.0f, -cosCam);

    if (npc == -1) {
        part->pos.x = gPlayerStatus.pos.x + part->offset.x + rotMtx[1][0] * (radius + 16.0f);
        part->pos.y = gPlayerStatus.pos.y + part->offset.y + rotMtx[1][1] * (radius + 16.0f);
        part->pos.z = gPlayerStatus.pos.z + part->offset.z + rotMtx[1][2] * (radius + 16.0f);
    } else if (npc != nullptr) {
        part->pos.x = npc->pos.x + part->offset.x + rotMtx[1][0] * (radius + 16.0f);
        part->pos.y = npc->pos.y + part->offset.y + rotMtx[1][1] * (radius + 16.0f);
        part->pos.z = npc->pos.z + part->offset.z + rotMtx[1][2] * (radius + 16.0f);
    } else {
        part->pos.x = part->offset.x + rotMtx[1][0] * (radius + 16.0f);
        part->pos.y = part->offset.y + rotMtx[1][1] * (radius + 16.0f);
        part->pos.z = part->offset.z + rotMtx[1][2] * (radius + 16.0f);
    }
}

void emote_main(s32 type, Npc* npc, f32 x, f32 y, f32 z, f32 radius, f32 pitch, s32 duration, EffectInstance** outPtr) {
    EffectBlueprint bp;
    EffectBlueprint* bpPtr = &bp;
    EmoteFXData* data;
    EffectInstance* effect;
    s32 numParts;

    if (type == EMOTE_SHOCK) {
        numParts = 3;
    } else {
        numParts = 1;
    }

    bp.unk_00 = 0;
    bp.init = emote_init;
    bp.update = emote_update;
    bp.renderScene = emote_render;
    bp.renderUI = nullptr;
    bp.effectID = EFFECT_EMOTE;

    effect = create_effect_instance(bpPtr);
    effect->numParts = numParts;
    data = effect->data.emote = general_heap_malloc(numParts * sizeof(*data));

    ASSERT(effect->data.emote != nullptr);
    data->owner = npc;
    data->type = type;
    data->animType = type;

    if (duration <= 0) {
        duration = 10000;
    }
    data->timeLeft = duration;
    data->animTime = 0;

    if (type == EMOTE_SHOCK) {
        s32 i;

        for (i = 0; i < numParts; i++, data++) {
            data->offset.x = x;
            data->offset.y = y;
            data->offset.z = z;
            data->pitch = pitch;
            data->radius = radius;
            data->owner = npc;
            emote_compute_world_rotpos(data, i);
        }
    } else {
        data->offset.x = x;
        data->offset.y = y;
        data->offset.z = z;
        data->pitch = pitch;
        data->radius = radius;
        data->owner = npc;
        emote_compute_world_rotpos(data, 1);
    }

    if (outPtr != nullptr) {
        *outPtr = effect;
    }
}

void emote_init(EffectInstance* effect) {
}

void emote_update(EffectInstance* effect) {
    EmoteFXData* part = effect->data.emote;
    s32 type = part->type;

    part->frame = EmoteAnimFrames[part->animType][part->animTime];
    part->animTime++;

    if (part->frame < 0) {
        if (part->frame != -1) {
            part->animType = -part->frame - 10;
            part->animTime = 0;
            part->frame = EmoteAnimFrames[part->animType][0];
            part->animTime = 1;
        } else {
            remove_effect(effect);
            return;
        }
    }

    if (part->timeLeft < 10000) {
        part->timeLeft--;
    }

    if (part->timeLeft < 0) {
        remove_effect(effect);
        return;
    }

    if (part->owner != nullptr) {
        if (type == EMOTE_SHOCK) {
            s32 i;

            for (i = 0; i < effect->numParts; i++, part++) {
                emote_compute_world_rotpos(part, i);
            }
        } else {
            emote_compute_world_rotpos(part, 1);
        }
    }
}

void emote_render(EffectInstance* effect) {
    RenderTask renderTask;
    RenderTask* retTask;

    renderTask.appendGfx = emote_appendGfx;
    renderTask.appendGfxArg = effect;
    renderTask.dist = 0;
    renderTask.renderMode = RENDER_MODE_CLOUD_NO_ZCMP;

    retTask = queue_render_task(&renderTask);
    retTask->renderMode |= RENDER_TASK_FLAG_REFLECT_FLOOR;
}

void emote_appendGfx(void* effect) {
    EmoteFXData* part = ((EffectInstance*)effect)->data.emote;
    s32 type = part->type;
    s32 frame;
    Gfx* gfxSetupTex;
    Gfx* gfxDrawModel;
    Mtx* matrix;
    s32 w;
    s32 h;
    s32 uls;
    s32 ult;
    s32 idx;
    Matrix4f sp18;
    Matrix4f sp58;
    s32 i;

    gDPPipeSync(gMainGfxPos++);
    gSPSegment(gMainGfxPos++, 0x09, VIRTUAL_TO_PHYSICAL(((EffectInstance*)effect)->shared->graphics));

    if (type != EMOTE_SHOCK) {
        guTranslateF(sp18, part->pos.x, part->pos.y, part->pos.z);
        guRotateF(sp58, -gCameras[gCurrentCameraID].curYaw, 0.0f, 1.0f, 0.0f);
        guMtxCatF(sp58, sp18, sp18);

        matrix = &gDisplayContext->matrixStack[gMatrixListPos];

        guMtxF2L(sp18, &gDisplayContext->matrixStack[gMatrixListPos++]);
        guScaleF(sp58, 1.0f, 0.8f, 1.0f);
        guMtxCatF(sp58, sp18, sp18);
        guRotateF(sp58, part->rotAngle, 0.0f, 0.0f, 1.0f);
        guMtxCatF(sp58, sp18, sp18);
        guMtxF2L(sp18, &gDisplayContext->matrixStack[gMatrixListPos]);

        gSPMatrix(gMainGfxPos++, &gDisplayContext->matrixStack[gMatrixListPos++], G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(gMainGfxPos++, D_09002170_336DE0);
        gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
    } else {
        if (part->frame == 0) {
            for (i = 0; i < 3; i++, part++) {
                guTranslateF(sp18, part->pos.x, part->pos.y, part->pos.z);
                guRotateF(sp58, -gCameras[gCurrentCameraID].curYaw, 0.0f, 1.0f, 0.0f);
                guMtxCatF(sp58, sp18, sp18);
                guRotateF(sp58, part->rotAngle, 0.0f, 0.0f, 1.0f);
                guMtxCatF(sp58, sp18, sp18);
                guScaleF(sp58, part->scale, part->scale, 1.0f);
                guMtxCatF(sp58, sp18, sp18);
                guMtxF2L(sp18, &gDisplayContext->matrixStack[gMatrixListPos]);

                gDPSetPrimColor(gMainGfxPos++, 0, 0, 235, 28, 0, 255);
                gSPMatrix(gMainGfxPos++, &gDisplayContext->matrixStack[gMatrixListPos++], G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(gMainGfxPos++, D_09002578_3371E8);
                gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
            }
        }

        return;
    }

    gSPMatrix(gMainGfxPos++, matrix, G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    frame = part->frame;
    gfxSetupTex = EmoteGfxSetupTex[type];
    gfxDrawModel = EmoteGfxDrawModel[type];

    switch (type) {
        case EMOTE_EXCLAMATION:
            w = 16;
            h = 16;
            uls = 128 - frame * 16;
            ult = 0;
            gDPSetPrimColor(gMainGfxPos++, 0, 0, 220, 0, 0, 255);
            break;
        case EMOTE_QUESTION:
            w = 32;
            h = 48;
            uls = 128 - frame * 32;
            ult = 0;
            gDPSetPrimColor(gMainGfxPos++, 0, 0, 220, 0, 0, 255);
            break;
        case EMOTE_FRUSTRATION:
            w = 32;
            h = 32;
            uls = 128 - frame * 32;
            ult = 0;
            idx = part->timeLeft % ARRAY_COUNT(EmoteFrustrationColors);
            gDPSetPrimColor(gMainGfxPos++, 0, 0, EmoteFrustrationColors[idx].r, EmoteFrustrationColors[idx].g, EmoteFrustrationColors[idx].b, 255);
            break;
        case EMOTE_ELLIPSIS:
            w = 32;
            h = 8;
            uls = 128 - frame * 32;
            ult = 0;
            break;
    }

    if (gfxSetupTex != nullptr) {
        gSPDisplayList(gMainGfxPos++, gfxSetupTex);
    }

    // select the frame
    gDPSetTileSize(gMainGfxPos++, G_TX_RENDERTILE, uls * 4, ult * 4, (uls + w) * 4, (ult + h) * 4);

    if (gfxDrawModel != nullptr) {
        gSPDisplayList(gMainGfxPos++, gfxDrawModel);
    }

    gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
}
