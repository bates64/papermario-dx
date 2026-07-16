#include "common.h"
#include "dx/overlay.h"
#include "effects.h"
#include "ld_addrs.h"

BSS EffectSharedData gEffectSharedData[EFFECT_OVERLAY_SLOT_COUNT];
EffectInstance* gEffectInstances[96];

void reset_effect_utils(void);

#define FX_ENTRY(name, gfx_name) { \
    .overlayName = #name, \
    .entryPointName = #name "_main", \
    .graphicsDmaStart = gfx_name##_ROM_START, \
    .graphicsDmaEnd = gfx_name##_ROM_END, \
}

#include "effects/effect_table.c"

/// Used for unbound function points in effect structs.
void stub_effect_delegate(EffectInstance* effect) {
}

void clear_effect_data(void) {
    s32 i;

    ovl_unload_type(OVL_EFFECT);

    for (i = 0; i < ARRAY_COUNT(gEffectTable); i++) {
        EffectTableEntry* effectEntry = &gEffectTable[i];

        effectEntry->overlay = nullptr;
        effectEntry->entryPoint = nullptr;
    }

    memset(gEffectSharedData, 0, sizeof(gEffectSharedData));
    memset(gEffectInstances, 0, sizeof(gEffectInstances));

    reset_effect_utils();
}

void update_effects(void) {
    if (!(gOverrideFlags & (GLOBAL_OVERRIDES_800 | GLOBAL_OVERRIDES_400))) {
        EffectSharedData* sharedData;
        s32 i;

        // reset free delay for each EffectSharedData touched in previous update
        for (i = 0, sharedData = gEffectSharedData; i < ARRAY_COUNT(gEffectSharedData); i++, sharedData++) {
            if (sharedData->flags & FX_SHARED_DATA_LOADED) {
                if (!(sharedData->flags & FX_SHARED_DATA_CAN_FREE)) {
                    sharedData->flags |= FX_SHARED_DATA_CAN_FREE;
                    sharedData->freeDelay = 3;
                }
            }
        }

        // update each EffectInstances
        for (i = 0; i < ARRAY_COUNT(gEffectInstances); i++) {
            EffectInstance* effectInstance = gEffectInstances[i];

            if (effectInstance != nullptr && (effectInstance->flags & FX_INSTANCE_FLAG_ENABLED)) {
                effectInstance->shared->flags &= ~FX_SHARED_DATA_CAN_FREE;

                if (gGameStatusPtr->context != CONTEXT_WORLD) {
                    if (effectInstance->flags & FX_INSTANCE_FLAG_BATTLE) {
                        effectInstance->shared->update(effectInstance);
                        effectInstance->flags |= FX_INSTANCE_FLAG_HAS_UPDATED;
                    }
                } else {
                    if (!(effectInstance->flags & FX_INSTANCE_FLAG_BATTLE)) {
                        effectInstance->shared->update(effectInstance);
                        effectInstance->flags |= FX_INSTANCE_FLAG_HAS_UPDATED;
                    }
                }
            }
        }

        // free any EffectSharedData which haven't been used recently
        for (i = 0, sharedData = gEffectSharedData; i < ARRAY_COUNT(gEffectSharedData); i++, sharedData++) {
            if (sharedData->flags & FX_SHARED_DATA_LOADED) {
                if (sharedData->flags & FX_SHARED_DATA_CAN_FREE) {
                    if (sharedData->freeDelay != 0) {
                        sharedData->freeDelay--;
                    } else {
                        if (sharedData->graphics != nullptr) {
                            general_heap_free(sharedData->graphics);
                            sharedData->graphics = nullptr;
                        }
                        EffectTableEntry* effectEntry = &gEffectTable[sharedData->effectIndex];

                        ovl_unload(effectEntry->overlay);
                        effectEntry->overlay = nullptr;
                        effectEntry->entryPoint = nullptr;
                        memset(sharedData, 0, sizeof(*sharedData));
                    }
                }
            }
        }
    }
}

void render_effects_scene(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffectInstances); i++) {
        EffectInstance* effectInstance = gEffectInstances[i];

        if (effectInstance != nullptr) {
            if (effectInstance->flags & FX_INSTANCE_FLAG_ENABLED) {
                if (effectInstance->flags & FX_INSTANCE_FLAG_HAS_UPDATED) {
                    if (gGameStatusPtr->context != CONTEXT_WORLD) {
                        if (effectInstance->flags & FX_INSTANCE_FLAG_BATTLE) {
                            effectInstance->shared->renderScene(effectInstance);
                        }
                    } else {
                        if (!(effectInstance->flags & FX_INSTANCE_FLAG_BATTLE)) {
                            effectInstance->shared->renderScene(effectInstance);
                        }
                    }
                }
            }
        }
    }
}

void render_effects_UI(void) {
    s32 cond = true;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffectInstances); i++) {
        EffectInstance* effectInstance = gEffectInstances[i];

        if (effectInstance != nullptr) {
            if (effectInstance->flags & FX_INSTANCE_FLAG_ENABLED) {
                if (effectInstance->flags & FX_INSTANCE_FLAG_HAS_UPDATED) {
                    void (*renderUI)(EffectInstance* effect);

                    if (gGameStatusPtr->context != CONTEXT_WORLD && !(effectInstance->flags & FX_INSTANCE_FLAG_BATTLE)) {
                        continue;
                    }

                    if (gGameStatusPtr->context == CONTEXT_WORLD && effectInstance->flags & FX_INSTANCE_FLAG_BATTLE) {
                        continue;
                    }

                    renderUI = effectInstance->shared->renderUI;
                    if (renderUI != stub_effect_delegate) {
                        if (cond) {
                            Camera* camera = &gCameras[gCurrentCameraID];

                            gDPPipeSync(gMainGfxPos++);
                            gSPViewport(gMainGfxPos++, &camera->vp);
                            gSPClearGeometryMode(gMainGfxPos++, G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG |
                                                G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                                                G_SHADING_SMOOTH | G_CLIPPING | 0x40F9FA);
                            gSPSetGeometryMode(gMainGfxPos++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
                            gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE,
                                              camera->viewportStartX,
                                              camera->viewportStartY,
                                              camera->viewportStartX + camera->viewportW,
                                              camera->viewportStartY + camera->viewportH);
                            gSPClipRatio(gMainGfxPos++, FRUSTRATIO_2);

                            cond = false;
                            if (!(camera->flags & CAMERA_FLAG_ORTHO)) {
                                gSPPerspNormalize(gMainGfxPos++, camera->perspNorm);
                                gSPMatrix(gMainGfxPos++, &gDisplayContext->camPerspMatrix[gCurrentCameraID],
                                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
                            }
                        }

                        renderUI(effectInstance);
                    }
                }
            }
        }
    }
}

EffectInstance* create_effect_instance(EffectBlueprint* effectBp) {
    EffectInstance* newEffectInst;
    EffectSharedData* sharedData;
    s32 i;

    // Search for an unused instance
    for (i = 0; i < ARRAY_COUNT(gEffectInstances); i++) {
        if (gEffectInstances[i] == nullptr) {
            break;
        }
    }

    ASSERT(i < ARRAY_COUNT(gEffectInstances));

    // Allocate space for the new instance
    gEffectInstances[i] = newEffectInst = general_heap_malloc(sizeof(*newEffectInst));
    ASSERT(newEffectInst != nullptr);

    sharedData = &gEffectSharedData[0];
    newEffectInst->effectID = effectBp->effectID;
    newEffectInst->flags = FX_INSTANCE_FLAG_ENABLED;

    // Look for a loaded effect of the proper index
    for (i = 0; i < ARRAY_COUNT(gEffectSharedData); i++) {
        if ((sharedData->flags & FX_SHARED_DATA_LOADED) && (sharedData->effectIndex == effectBp->effectID)) {
            break;
        }
        sharedData++;
    }

    ASSERT(i < ARRAY_COUNT(gEffectSharedData));

    sharedData->update = effectBp->update;
    if (sharedData->update == nullptr) {
        sharedData->update = stub_effect_delegate;
    }

    sharedData->renderScene = effectBp->renderScene;
    if (sharedData->renderScene == nullptr) {
        sharedData->renderScene = stub_effect_delegate;
    }

    sharedData->renderUI = effectBp->renderUI;
    if (sharedData->renderUI == nullptr) {
        sharedData->renderUI = stub_effect_delegate;
    }

    newEffectInst->shared = sharedData;

    if (effectBp->init != nullptr) {
        effectBp->init(newEffectInst);
    }

    if (gGameStatusPtr->context != CONTEXT_WORLD) {
        newEffectInst->flags |= FX_INSTANCE_FLAG_BATTLE;
    }
    return newEffectInst;
}

void remove_effect(EffectInstance* effectInstance) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffectInstances); i++) {
        if (gEffectInstances[i] == effectInstance) {
            break;
        }
    }

    ASSERT(i < ARRAY_COUNT(gEffectInstances));

    if (effectInstance->data.any != nullptr) {
        general_heap_free(effectInstance->data.any);
    }

    general_heap_free(effectInstance);
    gEffectInstances[i] = nullptr;
}

void remove_all_effects(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffectInstances); i++) {
        EffectInstance* effect = gEffectInstances[i];

        if (effect != nullptr && effect->flags & FX_INSTANCE_FLAG_BATTLE) {
            if (effect->data.any != nullptr) {
                general_heap_free(effect->data.any);
            }
            general_heap_free(effect);
            gEffectInstances[i] = nullptr;
        }
    }
}

void* load_effect(s32 effectIndex) {
    if ((u32)effectIndex >= ARRAY_COUNT(gEffectTable) || gEffectTable[effectIndex].overlayName == nullptr) {
        PANIC_MSG("Invalid effect index %d", (int)effectIndex);
        return nullptr;
    }

    EffectTableEntry* effectEntry = &gEffectTable[effectIndex];
    EffectSharedData* sharedData;
    s32 i;

    // Look for a loaded effect matching the desired index
    for (i = 0, sharedData = &gEffectSharedData[0]; i < ARRAY_COUNT(gEffectSharedData); i++) {
        if ((sharedData->flags & FX_SHARED_DATA_LOADED) && sharedData->effectIndex == effectIndex) {
            break;
        }
        sharedData++;
    }

    // return the cached entrypoint
    if (i < ARRAY_COUNT(gEffectSharedData)) {
        sharedData->effectIndex = effectIndex;
        sharedData->flags = FX_SHARED_DATA_LOADED;
        return effectEntry->entryPoint;
    }

    // If a loaded effect wasn't found, look for the first empty space
    for (i = 0, sharedData = &gEffectSharedData[0]; i < ARRAY_COUNT(gEffectSharedData); i++) {
        if (!(sharedData->flags & FX_SHARED_DATA_LOADED)) {
            break;
        }
        sharedData++;
    }

    // If no empty space was found, panic
    ASSERT(i < ARRAY_COUNT(gEffectSharedData));

    // load and relocate the implementation into the dedicated effect pool
    effectEntry->overlay = ovl_load(effectEntry->overlayName, OVL_EFFECT);
    effectEntry->entryPoint = ovl_import(effectEntry->overlay, effectEntry->entryPointName);
    ASSERT_MSG(effectEntry->entryPoint != nullptr, "Effect '%s' does not export '%s'",
               effectEntry->overlayName, effectEntry->entryPointName);

    // If there's graphics data for the effect, allocate space and copy into the new space
    if (effectEntry->graphicsDmaStart != nullptr) {
        void* graphics = general_heap_malloc(effectEntry->graphicsDmaEnd - effectEntry->graphicsDmaStart);
        sharedData->graphics = graphics;
        ASSERT(graphics != nullptr);
        dma_copy(effectEntry->graphicsDmaStart, effectEntry->graphicsDmaEnd, sharedData->graphics);
    }

    // Initialize the newly loaded effect data
    sharedData->effectIndex = effectIndex;
    sharedData->flags = FX_SHARED_DATA_LOADED;
    return effectEntry->entryPoint;
}
