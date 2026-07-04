#include "common.h"
#include "effects_internal.h"

#define NAMESPACE water_fountain

typedef struct DropletFrame {
    /* 0x00 */ s8 offsetX;
    /* 0x01 */ s8 offsetY;
    /* 0x02 */ s16 scaleX;
    /* 0x04 */ s16 scaleY;
    /* 0x06 */ s16 angleOffset;
    /* 0x08 */ u8 alpha;
    /* 0x09 */ PAD(1);
} DropletFrame; // size = 0xA

extern Gfx D_09000280_3B8AE0[];
extern Gfx D_09000328_3B8B88[];
extern Gfx D_09000348_3B8BA8[];

DropletFrame N(InkDropletAnim)[] = {
    {   0,  0,  30, 140,    0, 255 },
    {   0,  6,  30, 120,    0, 250 },
    {   1, 12,  30, 110,   -5, 240 },
    {   1, 17,  50, 100,  -20, 240 },
    {   2, 22,  60,  90,  -30, 240 },
    {   2, 26,  70,  90,  -40, 240 },
    {   3, 28,  80,  85,  -50, 240 },
    {   4, 32,  90,  90,  -60, 240 },
    {   5, 35, 100, 100,  -70, 240 },
    {   7, 38, 110, 110,  -80, 240 },
    {   8, 40, 120, 120,  -90, 240 },
    {  11, 42, 130, 130, -100, 240 },
    {  14, 43, 150, 150, -110, 240 },
    {  18, 44, 190, 190, -120, 240 },
    {  21, 45, 230, 230, -130, 240 },
    {  24, 46, 270, 270, -140, 240 },
    {  27, 47, 310, 310, -150, 240 },
    {  30, 48, 350, 350, -160, 200 },
    {  33, 49, 380, 380, -170, 140 },
    {  36, 50, 400, 400, -180,  40 },
    {   0,  0,  30, 140,    0, 255 },
    {   0,  6,  30, 120,    0, 240 },
    {  -1, 12,  30, 110,    5, 230 },
    {  -1, 17,  50, 100,   20, 220 },
    {  -2, 22,  60,  90,   30, 210 },
    {  -2, 26,  70,  90,   40, 200 },
    {  -3, 28,  80,  85,   50, 190 },
    {  -4, 32,  90,  80,   60, 180 },
    {  -5, 35, 100,  77,   70, 170 },
    {  -7, 38, 110,  65,   80, 160 },
    {  -8, 40, 120,  54,   90, 150 },
    { -11, 42, 130,  60,  100, 140 },
    { -14, 43, 140,  70,  110, 130 },
    { -18, 44, 150,  80,  120, 120 },
    { -21, 45, 160,  90,  130, 110 },
    { -24, 46, 170, 100,  140,  90 },
    { -27, 47, 180, 110,  150,  80 },
    { -30, 48, 190, 120,  160,  70 },
    { -33, 49, 200, 130,  170,  30 },
    { -36, 50, 210, 140,  180,  10 },
    {   0,  0,  30, 140,    0, 255 },
    {   0,  6,  30, 120,    0, 240 },
    {   0, 12,  30, 110,    5, 230 },
    {   0, 17,  50, 100,   20, 220 },
    {   0, 22,  60,  90,   30, 210 },
    {   0, 26,  70,  90,   40, 200 },
    {   0, 28,  80,  85,   50, 190 },
    {   0, 32,  90,  80,   60, 180 },
    {   0, 35, 100,  77,   70, 170 },
    {   0, 38, 110,  65,   80, 160 },
    {   0, 40, 120,  54,   90, 150 },
    {   0, 42, 130,  60,  100, 140 },
    {   0, 43, 140,  70,  110, 130 },
    {   0, 44, 150,  80,  120, 120 },
    {   0, 45, 160,  90,  130, 110 },
    {   0, 46, 170, 100,  140,  90 },
    {   0, 47, 180, 110,  150,  80 },
    {   0, 48, 190, 120,  160,  70 },
    {   0, 49, 200, 130,  170,  30 },
    {   0, 50, 210, 140,  180,  10 }
};

DropletFrame N(WaterDropletAnim)[] = {
    {  0,  0,  30, 140,   0, 255 },
    {  0,  6,  30, 120,   0, 240 },
    {  1, 12,  30, 110,  -5, 230 },
    {  1, 17,  50, 100, -20, 220 },
    {  2, 22,  60,  90, -30, 210 },
    {  2, 26,  70,  90, -40, 200 },
    {  3, 28,  80,  85, -50, 190 },
    {  4, 32,  90,  80, -60, 180 },
    {  5, 35, 100,  77, -70, 120 },
    {  7, 38, 110,  65, -80,  80 },
    {  8, 40, 120,  54, -90,  40 },
    {  0,  0,  30, 140,   0, 255 },
    {  0,  6,  30, 120,   0, 240 },
    { -1, 12,  30, 110,   5, 230 },
    { -1, 17,  50, 100,  20, 220 },
    { -2, 22,  60,  90,  30, 210 },
    { -2, 26,  70,  90,  40, 200 },
    { -3, 28,  80,  85,  50, 190 },
    { -4, 32,  90,  80,  60, 180 },
    { -5, 35, 100,  77,  70, 120 },
    { -7, 38, 110,  65,  80,  80 },
    { -8, 40, 120,  54,  90,  40 },
    {  0,  0,  30, 140,   0, 255 },
    {  0,  6,  30, 120,   0, 240 },
    {  0, 12,  30, 110,   5, 230 },
    {  0, 17,  50, 100,  20, 220 },
    {  0, 22,  60,  90,  30, 210 },
    {  0, 26,  70,  90,  40, 200 },
    {  0, 28,  80,  85,  50, 190 },
    {  0, 32,  90,  80,  60, 180 },
    {  0, 36, 100,  77,  70, 120 },
    {  0, 39, 110,  65,  80,  80 },
    {  0, 42, 120,  54,  90,  40 }
};

s32 N(DropletAngles)[] = { 0, 40, 55, 190, 20, 130, 270, 300 };

void water_fountain_init(EffectInstance* effect);
void water_fountain_update(EffectInstance* effect);
void water_fountain_render(EffectInstance* effect);
void water_fountain_appendGfx(void* effect);

EffectInstance* water_fountain_main(s32 type, f32 x, f32 y, f32 z, f32 scale, s32 duration) {
    EffectBlueprint effectBp;
    EffectInstance* effect;
    WaterFountainFXData* data;
    s32 numParts = 1;

    effectBp.init = water_fountain_init;
    effectBp.update = water_fountain_update;
    effectBp.renderScene = water_fountain_render;
    effectBp.unk_00 = 0;
    effectBp.renderUI = nullptr;
    effectBp.effectID = EFFECT_WATER_FOUNTAIN;

    effect = create_effect_instance(&effectBp);
    effect->numParts = numParts;

    data = effect->data.waterFountain = general_heap_malloc(numParts * sizeof(*data));
    ASSERT(data != nullptr);

    data->type = type;
    data->lifetime = 0;
    if (duration <= 0) {
        data->timeLeft = 1000;
    } else {
        data->timeLeft = duration;
    }
    data->alpha = 255;
    data->pos.x = x;
    data->pos.y = y;
    data->pos.z = z;
    data->scale = scale;
    data->primColor.r = 70;
    data->primColor.g = 180;
    data->primColor.b = 255;
    data->envColor.r = 255;
    data->envColor.g = 255;
    data->envColor.b = 255;
    data->angle = 0;
    data->scaleX = 1.0f;
    data->scaleY = 1.0f;

    return effect;
}

void water_fountain_init(EffectInstance* effect) {
}

void water_fountain_update(EffectInstance* effect) {
    WaterFountainFXData* data = effect->data.waterFountain;

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
    if (data->lifetime < 8) {
        data->alpha = (data->lifetime * 32) + 31;
    }
}

void water_fountain_render(EffectInstance* effect) {
    RenderTask renderTask;
    RenderTask* retTask;

    renderTask.appendGfx = water_fountain_appendGfx;
    renderTask.appendGfxArg = effect;
    renderTask.dist = 10;
    renderTask.renderMode = RENDER_MODE_CLOUD_NO_ZCMP;

    retTask = queue_render_task(&renderTask);
    retTask->renderMode |= RENDER_TASK_FLAG_REFLECT_FLOOR;
}

void water_fountain_appendGfx(void* effect) {
    WaterFountainFXData* data = ((EffectInstance*)effect)->data.waterFountain;
    Camera* camera = &gCameras[gCurrentCameraID];
    s32 lifetime = data->lifetime;
    s32 timeLeft = data->timeLeft;
    s32 alpha = data->alpha;
    s32 type = data->type;
    s32 numBursts;
    s32 numFrames;
    s32 currentFrame;
    DropletFrame* frameTable;
    Matrix4f sp18;
    Matrix4f sp58;
    s32 i;
    s32 j;

    if (type == FX_FOUNTAIN_TYPE_INK) {
        numBursts = 3;
        frameTable = N(InkDropletAnim);
        numFrames = 20;
    } else {
        numBursts = 3;
        frameTable = N(WaterDropletAnim);
        numFrames = 11;
    }

    gDPPipeSync(gMainGfxPos++);
    gSPSegment(gMainGfxPos++, 0x09, VIRTUAL_TO_PHYSICAL(((EffectInstance*)effect)->shared->graphics));

    guTranslateF(sp18, data->pos.x, data->pos.y, data->pos.z);
    guScaleF(sp58, data->scale, data->scale, data->scale);
    guMtxCatF(sp58, sp18, sp18);
    guMtxF2L(sp18, &gDisplayContext->matrixStack[gMatrixListPos]);

    gSPMatrix(gMainGfxPos++, &gDisplayContext->matrixStack[gMatrixListPos++], G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPMatrix(gMainGfxPos++, camera->mtxBillboard, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);
    gSPDisplayList(gMainGfxPos++, D_09000280_3B8AE0);

    guRotateF(sp18, data->angle, 0.0f, 0.0f, 1.0f);
    guScaleF(sp58, data->scaleX, data->scaleY, 1.0f);
    guMtxCatF(sp58, sp18, sp18);
    guMtxF2L(sp18, &gDisplayContext->matrixStack[gMatrixListPos]);

    gSPMatrix(gMainGfxPos++, &gDisplayContext->matrixStack[gMatrixListPos++], G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
    gDPSetEnvColor(gMainGfxPos++, data->envColor.r, data->envColor.g, data->envColor.b, alpha);

    currentFrame = lifetime % numFrames;
    if (timeLeft >= numFrames - (currentFrame + 1)) {
        gDPSetPrimColor(gMainGfxPos++, 0, 0,
            data->primColor.r, data->primColor.g, data->primColor.b, alpha);
        gSPDisplayList(gMainGfxPos++, D_09000348_3B8BA8);
    }

    for (i = 0; i < numFrames / 2; i++) {
        for (j = 0; j < numBursts; j++) {
            s32 frameIdx = (lifetime + i * 2) % numFrames;
            DropletFrame* burstFrame = &frameTable[j * numFrames];

            if (lifetime * 5 >= frameIdx) {
                if (timeLeft >= numFrames - (frameIdx + 1)) {
                    guTranslateF(sp18,
                        (f32) burstFrame[frameIdx].offsetX,
                        (f32) burstFrame[frameIdx].offsetY + 10.0f,
                        0.0f);
                    guScaleF(sp58,
                        (f32) burstFrame[frameIdx].scaleX * 0.01,
                        (f32) burstFrame[frameIdx].scaleY * 0.01,
                        1.0f);
                    guMtxCatF(sp58, sp18, sp18);
                    guRotateF(sp58,
                        (f32) burstFrame[frameIdx].angleOffset + N(DropletAngles)[(j + i) & 7],
                        0.0f, 0.0f, 1.0f);
                    guMtxCatF(sp58, sp18, sp18);
                    guMtxF2L(sp18, &gDisplayContext->matrixStack[gMatrixListPos]);

                    gSPMatrix(gMainGfxPos++, &gDisplayContext->matrixStack[gMatrixListPos++], G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
                    gDPSetPrimColor(gMainGfxPos++, 0, 0,
                        data->primColor.r, data->primColor.g, data->primColor.b,
                        (alpha * burstFrame[frameIdx].alpha) >> 8);
                    gSPDisplayList(gMainGfxPos++, D_09000328_3B8B88);
                    gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
                }
            }
        }
    }

    gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
    gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
    gDPPipeSync(gMainGfxPos++);
}
