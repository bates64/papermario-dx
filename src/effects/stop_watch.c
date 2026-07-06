#include "common.h"
#include "effects_internal.h"

#define NAMESPACE stop_watch

#define STOP_WATCH_STRIP_VTX_COUNT (32)

// we will build the models for the clock glyphs dynamically and inline them
// within the display list, so we need to calculate their size in units of Gfx
#define STOP_WATCH_STRIP_VTX_GFX_SIZE (sizeof(Vtx_t) * STOP_WATCH_STRIP_VTX_COUNT / sizeof(Gfx))

extern Gfx D_09001000_3CC890[];

typedef struct GlyphLocation {
    /* 0x00 */ Vec2i pos;
    /* 0x08 */ s32 delay;
} GlyphLocation; // size = 0xC

u8 N(GlyphScales)[] = { 120, 80, 40, 60 };

Color_RGB8 N(GlyphColors)[] = {
    { 255, 130, 130 },
    { 255, 130, 196 },
    { 255, 130, 255 },
    { 198, 130, 255 },
    { 138, 130, 255 },
    { 130, 165, 255 },
    { 130, 213, 255 },
    { 130, 255, 255 },
    { 130, 255, 202 },
    { 130, 255, 144 },
    { 175, 255, 130 },
    { 215, 255, 130 },
    { 250, 255, 130 },
    { 255, 225, 130 },
    { 255, 198, 130 },
    { 255, 159, 130 },
    { 255, 130, 130 },
};

GlyphLocation N(GlyphLocations)[] = {
    { .pos = { -50, -70 }, .delay =  5 },
    { .pos = {  80, -90 }, .delay = 20 },
    { .pos = {  20, -50 }, .delay = 45 },
    { .pos = { -80,  30 }, .delay = 10 },
    { .pos = {  30,   0 }, .delay = 35 },
    { .pos = { 120, -30 }, .delay = 50 },
    { .pos = {  10,  50 }, .delay = 30 },
    { .pos = { 100,  30 }, .delay = 15 },
    { .pos = {  40, 100 }, .delay = 40 },
    { .pos = { 140,  90 }, .delay = 25 },
};

void stop_watch_init(EffectInstance* effect);
void stop_watch_update(EffectInstance* effect);
void stop_watch_render(EffectInstance* effect);
void stop_watch_appendGfx(void* effect);

EffectInstance* stop_watch_main(s32 type, f32 x, f32 y, f32 z, f32 scale, s32 duration) {
    EffectBlueprint bp;
    StopWatchFXData* data;
    EffectInstance* effect;
    s32 numParts = 1;
    s32 i;

    bp.init = stop_watch_init;
    bp.update = stop_watch_update;
    bp.renderScene = stop_watch_render;
    bp.unk_00 = 0;
    bp.renderUI = nullptr;
    bp.effectID = EFFECT_STOP_WATCH;

    effect = create_effect_instance(&bp);
    effect->numParts = numParts;
    data = effect->data.stopWatch = general_heap_malloc(numParts * sizeof(*data));
    ASSERT(effect->data.stopWatch != nullptr);

    data->type = type;
    data->lifetime = 0;
    if (duration <= 0) {
        data->timeLeft = 1000;
    } else {
        data->timeLeft = duration;
    }
    data->masterAlpha = 0;
    data->pos.x = x;
    data->pos.y = y;
    data->pos.z = z;
    data->scale = scale;
    data->unusedColor.r = 70;
    data->unusedColor.g = 180;
    data->unusedColor.b = 120;
    data->envAlpha = 0;
    data->rippleAmplitude = 1.0f;

    for (i = 0; i < 10; i++) {
        data->glyphPosX[i] = N(GlyphLocations)[i].pos.x;
        data->glyphPosY[i] = N(GlyphLocations)[i].pos.y;
        data->glyphPosZ[i] = 0;
        data->glyphRotX[i] = 0;
        data->glyphRotY[i] = 0;
        data->glyphRotZ[i] = 0;
        data->glyphAlpha[i] = 0;
        data->glyphDelay[i] = N(GlyphLocations)[i].delay;
    }

    return effect;
}

void stop_watch_init(EffectInstance* effect) {
}

void stop_watch_update(EffectInstance* effect) {
    StopWatchFXData* data = effect->data.stopWatch;
    s32 timeleft;
    s32 time;
    s32 i;

    if (effect->flags & FX_INSTANCE_FLAG_DISMISS) {
        effect->flags &= ~FX_INSTANCE_FLAG_DISMISS;
        data->timeLeft = 64;
    }

    if (data->timeLeft < 1000) {
        data->timeLeft--;
    }

    data->lifetime++;

    if (data->timeLeft < 0) {
        remove_effect(effect);
        return;
    }

    timeleft = data->timeLeft;
    time = data->lifetime;

    // fade out ripple
    if (timeleft < 64) {
        data->rippleAmplitude -= 0.05;
        if (data->rippleAmplitude < 0.0f) {
            data->rippleAmplitude = 0.0f;
        }
    }

    // remove screen darkening
    if (timeleft < 32) {
        data->envAlpha += 128;
        if (data->envAlpha > 255) {
            data->envAlpha = 255;
        }
        data->rippleAmplitude = 0.0f;
    }

    // fade out
    if (timeleft < 16) {
        data->masterAlpha = timeleft * 16;
    }
    // fade in
    if (time < 16) {
        data->masterAlpha = time * 16 + 15;
    }

    // start each glyph after its delay, then ramp up alpha
    for (i = 0; i < 10; i++) {
        if (data->glyphDelay[i] != 0) {
            data->glyphDelay[i]--;
        }
        if (data->glyphDelay[i] == 0) {
            data->glyphAlpha[i] += 8;
            if (data->glyphAlpha[i] > 255) {
                data->glyphAlpha[i] = 255;
            }
        }
    }
}

void stop_watch_render(EffectInstance* effect) {
    RenderTask renderTask;

    renderTask.appendGfx = stop_watch_appendGfx;
    renderTask.appendGfxArg = effect;
    renderTask.dist = 10;
    renderTask.renderMode = RENDER_MODE_CLOUD_NO_ZCMP;

    queue_render_task(&renderTask);
}

void stop_watch_appendGfx(void* effect) {
    StopWatchFXData* data = ((EffectInstance*)effect)->data.stopWatch;
    Camera* camera = &gCameras[gCurrentCameraID];
    s32 masterAlpha = data->masterAlpha;
    s32 time = data->lifetime;
    Vtx_t* vtxBuffer;
    Gfx* drawMeshGfxPos;
    Matrix4f transformMtx;
    Matrix4f tempMtx;
    s32 i;

    gDPPipeSync(gMainGfxPos++);
    gSPSegment(gMainGfxPos++, 0x09, VIRTUAL_TO_PHYSICAL(((EffectInstance*)effect)->shared->graphics));

    guTranslateF(transformMtx, data->pos.x, data->pos.y, data->pos.z);
    guScaleF(tempMtx, data->scale, data->scale, data->scale);
    guMtxCatF(tempMtx, transformMtx, transformMtx);
    guMtxF2L(transformMtx, &gDisplayContext->matrixStack[gMatrixListPos]);

    gSPMatrix(gMainGfxPos++, &gDisplayContext->matrixStack[gMatrixListPos++], G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPMatrix(gMainGfxPos++, camera->mtxBillboard, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);
    gSPDisplayList(gMainGfxPos++, D_09001000_3CC890);
    gDPSetEnvColor(gMainGfxPos++, 0, 0, 0, data->envAlpha);

    // this is where we will inline the vertex table. first insert a branch command
    // to jump over the table (the +1 is needed to include the jump itself)
    gSPBranchList(gMainGfxPos, &gMainGfxPos[STOP_WATCH_STRIP_VTX_GFX_SIZE + 1]);
    // save vertex table position
    vtxBuffer = (Vtx_t*) (gMainGfxPos + 1);
    // advance the main display list
    gMainGfxPos = &gMainGfxPos[STOP_WATCH_STRIP_VTX_GFX_SIZE + 1];

    // build the mesh for the clocks, including the bobbing and wavy motion
    for (i = 0; i < STOP_WATCH_STRIP_VTX_COUNT / 2; i++) {
        Vtx_t* vtx = &vtxBuffer[i * 2];
        s32 xoffset = sin_deg(time * 10 + i * 60) * 500.0f * data->rippleAmplitude; // horizontal waves
        s32 yoffset = sin_deg(time * 10 + i *  6) * 200.0f * data->rippleAmplitude; // vertical bobbing

        vtx[0].ob[0] = xoffset - 3200;
        vtx[0].ob[1] = i * 400 + yoffset - 3000;
        vtx[0].ob[2] = 0;
        vtx[0].tc[0] = 0;
        vtx[0].tc[1] = i * 128;

        vtx[1].ob[0] = xoffset + 3200;
        vtx[1].ob[1] = i * 400 + yoffset - 3000;
        vtx[1].ob[2] = 0;
        vtx[1].tc[0] = 2048;
        vtx[1].tc[1] = i * 128;
    }

    // next we inline a reusable display list for drawing the mesh
    // how do we know how far to jump?
    //  1 command for the branch
    //  2 commands for gSPMatrix and gSPVertex
    //  15 for the gSP2Triangles commands
    //  2 more commands for gSPPopMatrix and gSPEndDisplayList
    // or 20 commands in total
    gSPBranchList(gMainGfxPos, &gMainGfxPos[20]);

    gMainGfxPos++;
    drawMeshGfxPos = gMainGfxPos;

    guScaleF(transformMtx, 0.01f, 0.01f, 0.01f);
    guMtxF2L(transformMtx, &gDisplayContext->matrixStack[gMatrixListPos]);

    gSPMatrix(gMainGfxPos++, &gDisplayContext->matrixStack[gMatrixListPos++], G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
    gSPVertex(gMainGfxPos++, vtxBuffer, 32, 0);

    for (i = 0; i < 15; i++) {
        s32 i2 = i * 2;
        gSP2Triangles(gMainGfxPos++,
            i2    , i2 + 2, i2 + 1, i2,
            i2 + 1, i2 + 2, i2 + 3, i2);
    }

    gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
    gSPEndDisplayList(gMainGfxPos++);

    // now draw the ten clock glyphs with 10 calls to the drawMesh display list we just inlined
    for (i = 0; i < 10; i++) {
        guPositionF(transformMtx, data->glyphRotX[i], data->glyphRotY[i], data->glyphRotZ[i], N(GlyphScales)[i % 4] * 0.01, data->glyphPosX[i], data->glyphPosY[i], data->glyphPosZ[i]);
        guMtxF2L(transformMtx, &gDisplayContext->matrixStack[gMatrixListPos]);

        gSPMatrix(gMainGfxPos++, &gDisplayContext->matrixStack[gMatrixListPos++], G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
        gDPSetPrimColor(gMainGfxPos++, 0, 0, N(GlyphColors)[i].r, N(GlyphColors)[i].g, N(GlyphColors)[i].b, masterAlpha * data->glyphAlpha[i] / 255);
        gSPDisplayList(gMainGfxPos++, drawMeshGfxPos);
        gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
    }

    gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
}
