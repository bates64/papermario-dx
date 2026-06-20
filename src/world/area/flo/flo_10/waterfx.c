#include "flo_10.h"
#include "nu/nusys.h"
#include "model.h"

s32 N(ReflectionWavePhase) = {
    0
};

/// Reflects the framebuffer above the waterline into the given screen region.
/// The reflection is drawn in horizontal strips which fade out and ripple with distance from the waterline.
void N(draw_wavy_water_reflection)(s32 left, s32 top, s32 right, s32 bottom) {
    s32 i;
    s32 numStrips;
    s32 remainder;
    u16* framebuffer;
    s32 alpha;

    N(ReflectionWavePhase) += 5;

    if (left >= right || top >= bottom) {
        return;
    }

    if (left < 0) {
        left = 0;
    }
    if (top < 0) {
        top = 0;
    }
    if (right < 0) {
        right = 0;
    }
    if (bottom < 0) {
        bottom = 0;
    }

    if (left >= SCREEN_WIDTH) {
        left = SCREEN_WIDTH - 1;
    }
    if (top >= SCREEN_HEIGHT) {
        top = SCREEN_HEIGHT - 1;
    }
    if (right >= SCREEN_WIDTH) {
        right = SCREEN_WIDTH - 1;
    }
    if (bottom >= SCREEN_HEIGHT) {
        bottom = SCREEN_HEIGHT - 1;
    }

    if (left == right || top == bottom) {
        return;
    }

    left = left / 4 * 4;
    right = right / 4 * 4 + 4;

    numStrips = (bottom - top) / 6;
    remainder = (bottom - top) % 6;
    framebuffer = nuGfxCfb_ptr;

    for (i = 0; i < numStrips; i++) {
        alpha = (top - 6 * i - 6) * 2;
        if (top - 6 * i - 6 >= 0) {
            if (alpha > 255) {
                alpha = 255;
            }
            gDPSetPrimColor(gMainGfxPos++, 0, 0, 255, 255, 255, alpha);
            gDPLoadTextureTile(gMainGfxPos++, osVirtualToPhysical(framebuffer), G_IM_FMT_RGBA, G_IM_SIZ_16b,
                            SCREEN_WIDTH, 6,
                            left, top - 6 * i - 6, right - 1, top - 6 * i - 1, 0,
                            G_TX_WRAP, G_TX_WRAP, 9, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle(gMainGfxPos++, left * 4, (top + i * 6) * 4, right * 4, (top + i * 6 + 6) * 4,
                                G_TX_RENDERTILE, left * 32, (top - i * 6) * 32, 1024,
                                (s32)(sin_deg(N(ReflectionWavePhase) + i * 30) * 500.0f) - 500);
        }
    }

    if (remainder != 0) {
        alpha = (top - 6 * i - 6) * 2;
        if (top - 6 * i - 6 >= 0) {
            if (alpha > 255) {
                alpha = 255;
            }
            gDPSetPrimColor(gMainGfxPos++, 0, 0, 255, 255, 255, alpha);
            gDPLoadTextureTile(gMainGfxPos++, osVirtualToPhysical(framebuffer), G_IM_FMT_RGBA, G_IM_SIZ_16b,
                            SCREEN_WIDTH, 6,
                            left, top - 6 * i - remainder, right - 1, top - 6 * i - 1, 0,
                            G_TX_WRAP, G_TX_WRAP, 9, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle(gMainGfxPos++, left * 4, (top + i * 6) * 4, right * 4,
                                (top + i * 6 + remainder) * 4,
                                G_TX_RENDERTILE, left * 32, (top - i * 6) * 32, 1024, -1024);
        }
    }
}

/// Projects the water-edge model onto the screen and masks a wavy reflection to its shape.
void N(build_gfx_water_reflection)(void) {
    Camera* camera = &gCameras[gCurrentCameraID];
    Model* waterEdge = get_model_from_list_index(get_model_list_index_from_tree_index(MODEL_o40));
    ModelBoundingBox* bounds = (ModelBoundingBox*) waterEdge->modelNode->propertyList;
    f32 bbHalfX = bounds->halfSizeX;
    f32 bbHalfZ = bounds->halfSizeZ;
    f32 outX, outY, outZ, outW;
    f32 minScreenX;
    f32 minScreenY;
    f32 maxScreenX;
    f32 maxScreenY;

    // find the screen bounds of the water-edge model
    transform_point(camera->mtxPerspective,
                    waterEdge->center.x - bbHalfX, waterEdge->center.y, waterEdge->center.z - bbHalfZ, 1.0f,
                    &outX, &outY, &outZ, &outW);

    outX *= 1.0f / outW;
    outY *= -(1.0f / outW);
    outZ *= 1.0f / outW;
    outW = 1.0f / outW;

    if (outW < 0.0f) {
        outX = 0.0f;
        outY = 1.0f;
    }
    maxScreenX = outX;
    maxScreenY = outY;

    transform_point(camera->mtxPerspective,
                    waterEdge->center.x - bbHalfX, waterEdge->center.y, waterEdge->center.z + bbHalfZ, 1.0f,
                    &outX, &outY, &outZ, &outW);

    outX *= 1.0f / outW;
    outY *= -(1.0f / outW);
    outZ *= 1.0f / outW;
    outW = 1.0f / outW;

    minScreenX = maxScreenX;
    minScreenY = maxScreenY;
    if (outW < 0.0f) {
        outX = 0.0f;
        outY = 1.0f;
    }

    if (minScreenX > outX) {
        minScreenX = outX;
    }

    if (minScreenY > outY) {
        minScreenY = outY;
    }

    if (maxScreenX < outX) {
        maxScreenX = outX;
    }

    if (maxScreenY < outY) {
        maxScreenY = outY;
    }

    transform_point(camera->mtxPerspective,
                    waterEdge->center.x + bbHalfX, waterEdge->center.y, waterEdge->center.z + bbHalfZ, 1.0f,
                    &outX, &outY, &outZ, &outW);

    outX *= 1.0f / outW;
    outY *= -(1.0f / outW);
    outZ *= 1.0f / outW;
    outW = 1.0f / outW;

    if (outW < 0.0f) {
        outX = 1.0f;
        outY = 1.0f;
    }

    if (minScreenX > outX) {
        minScreenX = outX;
    }

    if (minScreenY > outY) {
        minScreenY = outY;
    }

    if (maxScreenX < outX) {
        maxScreenX = outX;
    }

    if (maxScreenY < outY) {
        maxScreenY = outY;
    }

    transform_point(camera->mtxPerspective,
                    waterEdge->center.x + bbHalfX, waterEdge->center.y, waterEdge->center.z - bbHalfZ, 1.0f,
                    &outX, &outY, &outZ, &outW);

    outX *= 1.0f / outW;
    outY *= -(1.0f / outW);
    outZ *= 1.0f / outW;
    outW = 1.0f / outW;

    if (outW < 0.0f) {
        outX = 1.0f;
        outY = 1.0f;
    }

    if (minScreenX > outX) {
        minScreenX = outX;
    }

    if (minScreenY > outY) {
        minScreenY = outY;
    }

    if (maxScreenX < outX) {
        maxScreenX = outX;
    }

    if (maxScreenY < outY) {
        maxScreenY = outY;
    }

    if (minScreenX != maxScreenX || minScreenY != maxScreenY) {
        minScreenX = ((minScreenX * camera->viewportW) + camera->viewportW) * 0.5f;
        minScreenY = ((minScreenY * camera->viewportH) + camera->viewportH) * 0.5f;
        maxScreenX = ((maxScreenX * camera->viewportW) + camera->viewportW) * 0.5f;
        maxScreenY = ((maxScreenY * camera->viewportH) + camera->viewportH) * 0.5f;

        minScreenX += camera->viewportStartX;
        minScreenY += camera->viewportStartY;
        maxScreenX += camera->viewportStartX;
        maxScreenY += camera->viewportStartY;

        // draw the water edge into the depth buffer to use as a mask
        gDPSetCycleType(gMainGfxPos++, G_CYC_1CYCLE);
        gDPSetRenderMode(gMainGfxPos++, Z_CMP | CVG_DST_CLAMP | ZMODE_OPA | FORCE_BL | G_RM_PASS,
                         Z_CMP | CVG_DST_CLAMP | ZMODE_OPA | FORCE_BL | GBL_c2(G_BL_CLR_IN, G_BL_0, G_BL_CLR_IN, G_BL_1));
        gDPSetColorImage(gMainGfxPos++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, osVirtualToPhysical(nuGfxZBuffer));
        gDPSetCombineMode(gMainGfxPos++, PM_CC_PRIM_NO_ALPHA, PM_CC_PRIM_NO_ALPHA);
        gDPSetPrimColor(gMainGfxPos++, 0, 0, 248, 240, 240, 0);
        gDPPipeSync(gMainGfxPos++);

        gSPDisplayList(gMainGfxPos++, waterEdge->modelNode->displayData->displayList);
        gDPPipeSync(gMainGfxPos++);

        gDPSetColorImage(gMainGfxPos++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, osVirtualToPhysical(nuGfxCfb_ptr));
        gDPSetDepthSource(gMainGfxPos++, G_ZS_PRIM);
        gDPSetPrimDepth(gMainGfxPos++, 32734, 0);
        gDPSetRenderMode(gMainGfxPos++, G_RM_ZB_XLU_DECAL, G_RM_ZB_XLU_DECAL2);
        gDPSetTextureFilter(gMainGfxPos++, G_TF_POINT);
        gDPSetTexturePersp(gMainGfxPos++, G_TP_NONE);
        gSPTexture(gMainGfxPos++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
        gDPSetTextureLUT(gMainGfxPos++, G_TT_NONE);
        gDPSetTextureDetail(gMainGfxPos++, G_TD_CLAMP);
        gDPSetTextureLOD(gMainGfxPos++, G_TL_TILE);
        gDPSetCombineMode(gMainGfxPos++, PM_CC_10, PM_CC_10);
        gDPPipeSync(gMainGfxPos++);

        // draw the reflection over the model's screen bounds
        N(draw_wavy_water_reflection)(minScreenX, minScreenY, maxScreenX, maxScreenY);

        gDPPipeSync(gMainGfxPos++);
        gDPSetCycleType(gMainGfxPos++, G_CYC_2CYCLE);
        gDPSetDepthSource(gMainGfxPos++, G_ZS_PIXEL);
    }
}

EvtScript N(EVS_SetupWaterEffect) = {
    // assumed method to get these working, doesn't seem to work though?
    //Call(SetCustomGfxBuilders, CUSTOM_GFX_1, Ref(N(build_gfx_water_reflection)), nullptr)
    //Call(SetModelCustomGfx, MODEL_o40, CUSTOM_GFX_1, ENV_TINT_UNCHANGED)
    Return
    End
};
