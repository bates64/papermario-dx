#include "common.h"
#include "sprite.h"

BSS KnockdownData* N(KnockDownDataPtr);

void N(worker_draw_knocked_down_player)(void) {
    KnockdownData* data = N(KnockDownDataPtr);
    ImgFXTexture ifxImg;
    SpriteRasterInfo rasterInfo;
    Matrix4f sp40, sp80;

    gDPPipeSync(gMainGfxPos++);
    gDPSetCycleType(gMainGfxPos++, G_CYC_1CYCLE);
    gSPClearGeometryMode(gMainGfxPos++,
                         G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                         G_SHADING_SMOOTH);
    gSPSetGeometryMode(gMainGfxPos++, G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH);
    gSPTexture(gMainGfxPos++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gDPSetTextureLOD(gMainGfxPos++, G_TL_TILE);
    gDPSetTexturePersp(gMainGfxPos++, G_TP_PERSP);
    gDPSetTextureFilter(gMainGfxPos++, G_TF_BILERP);
    gDPSetColorDither(gMainGfxPos++, G_CD_DISABLE);
    gDPSetTextureDetail(gMainGfxPos++, G_TD_CLAMP);
    gDPSetTextureConvert(gMainGfxPos++, G_TC_FILT);
    gDPSetCombineKey(gMainGfxPos++, G_CK_NONE);
    gDPSetAlphaCompare(gMainGfxPos++, G_AC_NONE);

    guTranslateF(sp40, data->pos.x, data->pos.y, data->pos.z);
    guRotateF(sp80, data->rot.y, 0.0f, 1.0f, 0.0f);
    guMtxCatF(sp80, sp40, sp40);
    guRotateF(sp80, data->rot.z, 0.0f, 0.0f, 1.0f);
    guMtxCatF(sp80, sp40, sp40);
    guRotateF(sp80, data->rot.x, 1.0f, 0.0f, 0.0f);
    guMtxCatF(sp80, sp40, sp40);
    guScaleF(sp80, data->scale.x, data->scale.y, data->scale.z);
    guMtxCatF(sp80, sp40, sp40);
    guMtxF2L(sp40, &gDisplayContext->matrixStack[gMatrixListPos]);
    gSPMatrix(gMainGfxPos++,
              OS_K0_TO_PHYSICAL(&gDisplayContext->matrixStack[gMatrixListPos++]),
              G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    spr_get_player_raster_info(&rasterInfo, data->spriteIndex, data->rasterIndex);
    ifxImg.raster = rasterInfo.raster;
    ifxImg.palette = rasterInfo.defaultPal;
    data->width = ifxImg.width = rasterInfo.width;
    data->height = ifxImg.height = rasterInfo.height;
    ifxImg.xOffset = -(s32) (rasterInfo.width * 0.5f);
    ifxImg.yOffset = rasterInfo.height;
    ifxImg.alpha = 255;

    imgfx_appendGfx_component(data->imgfxIdx, &ifxImg, 0, sp40);
    gSPPopMatrix(gMainGfxPos++, G_MTX_MODELVIEW);
}

API_CALLABLE(N(KnockdownCreate)) {
    Bytecode* args = script->ptrReadPos;
    s32 spriteIndex = evt_get_variable(script, *args++);
    s32 rasterIndex = evt_get_variable(script, *args++);

    N(KnockDownDataPtr) = heap_malloc(sizeof(*N(KnockDownDataPtr)));
    N(KnockDownDataPtr)->spriteIndex = spriteIndex;
    N(KnockDownDataPtr)->rasterIndex = rasterIndex;
    N(KnockDownDataPtr)->width = gPlayerStatus.colliderHeight;
    N(KnockDownDataPtr)->height = gPlayerStatus.colliderDiameter;
    N(KnockDownDataPtr)->pos.x = gPlayerStatus.pos.x;
    N(KnockDownDataPtr)->pos.y = gPlayerStatus.pos.y;
    N(KnockDownDataPtr)->pos.z = gPlayerStatus.pos.z;
    N(KnockDownDataPtr)->rot.x = 0.0f;
    N(KnockDownDataPtr)->rot.y = 0.0f;
    N(KnockDownDataPtr)->rot.z = 0.0f;
    N(KnockDownDataPtr)->scale.x = SPRITE_WORLD_SCALE_F;
    N(KnockDownDataPtr)->scale.y = SPRITE_WORLD_SCALE_F;
    N(KnockDownDataPtr)->scale.z = SPRITE_WORLD_SCALE_F;
    N(KnockDownDataPtr)->imgfxIdx = imgfx_get_free_instances(1);
    N(KnockDownDataPtr)->workerID = create_worker_scene(nullptr, N(worker_draw_knocked_down_player));
    return ApiStatus_DONE2;
}

API_CALLABLE(N(KnockdownDestroy)) {
    imgfx_release_instance(N(KnockDownDataPtr)->imgfxIdx);
    free_worker(N(KnockDownDataPtr)->workerID);
    heap_free(N(KnockDownDataPtr));
    return ApiStatus_DONE2;
}

API_CALLABLE(N(KnockdownSetPos)) {
    Bytecode* args = script->ptrReadPos;
    s32 x = evt_get_float_variable(script, *args++);
    s32 y = evt_get_float_variable(script, *args++);
    s32 z = evt_get_float_variable(script, *args++);

    N(KnockDownDataPtr)->pos.x = x;
    N(KnockDownDataPtr)->pos.y = y;
    N(KnockDownDataPtr)->pos.z = z;
    return ApiStatus_DONE2;
}

API_CALLABLE(N(KnockdownSetRot)) {
    Bytecode* args = script->ptrReadPos;
    s32 x = evt_get_float_variable(script, *args++);
    s32 y = evt_get_float_variable(script, *args++);
    s32 z = evt_get_float_variable(script, *args++);

    N(KnockDownDataPtr)->rot.x = x;
    N(KnockDownDataPtr)->rot.y = y;
    N(KnockDownDataPtr)->rot.z = z;
    return ApiStatus_DONE2;
}

API_CALLABLE(N(KnockdownSetScale)) {
    Bytecode* args = script->ptrReadPos;
    s32 x = evt_get_float_variable(script, *args++);
    s32 y = evt_get_float_variable(script, *args++);
    s32 z = evt_get_float_variable(script, *args++);

    N(KnockDownDataPtr)->scale.x = x;
    N(KnockDownDataPtr)->scale.y = y;
    N(KnockDownDataPtr)->scale.z = z;
    return ApiStatus_DONE2;
}

API_CALLABLE(N(KnockdownSetRaster)) {
    Bytecode* args = script->ptrReadPos;
    s32 spriteIndex = evt_get_variable(script, *args++);
    s32 rasterIndex = evt_get_variable(script, *args++);

    N(KnockDownDataPtr)->spriteIndex = spriteIndex;
    N(KnockDownDataPtr)->rasterIndex = rasterIndex;
    return ApiStatus_DONE2;
}
