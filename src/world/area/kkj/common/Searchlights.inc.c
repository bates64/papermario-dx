#include "common.h"
#include "npc.h"
#include "model.h"

/// Checks whether the player is within the guard's detection area and has a clear line of sight.
/// @evtapi
/// @param outDetected
/// @param forwardExtent
/// @param centerOffset
/// @param lateralExtent
API_CALLABLE(N(CheckPlayerInSight)) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    Npc* npc = get_npc_unsafe(script->owner1.enemy->npcID);
    Bytecode* args = script->ptrReadPos;
    s32 outDetected = *args++;
    // dimensions and offset of the detection area
    f32 forwardExtent = *args++;
    f32 centerOffset = *args++;
    f32 lateralExtent = *args++;
    f32 x = npc->pos.x;
    f32 z = npc->pos.z;
    f32 y;
    f32 deltaX;
    f32 deltaZ;
    s32 playerDetected;
    s32 ignoreFlags;

    // center the detection area in front of the guard
    add_vec2D_polar(&x, &z, centerOffset, npc->yaw);
    deltaX = dist2D(x, 0.0f, playerStatus->pos.x, 0.0f);
    deltaZ = dist2D(0.0f, z, 0.0f, playerStatus->pos.z);

    // check if the player is within the detection area
    if (npc->yaw == 90.0 || npc->yaw == 270.0) {
        if (deltaX <= forwardExtent && deltaZ <= lateralExtent) {
            playerDetected = true;
        } else {
            playerDetected = false;
        }
    } else {
        if (deltaZ <= forwardExtent && deltaX <= lateralExtent) {
            playerDetected = true;
        } else {
            playerDetected = false;
        }
    }

    // cancel detection if a wall blocks the guard's line of sight
    if (playerDetected) {
        x = npc->pos.x;
        y = npc->pos.y;
        z = npc->pos.z;
        centerOffset = dist2D(npc->pos.x, npc->pos.z, playerStatus->pos.x, playerStatus->pos.z);

        ignoreFlags = COLLISION_IGNORE_ENTITIES
            | COLLIDER_FLAG_IGNORE_NPC
            | COLLIDER_FLAG_IGNORE_PLAYER
            | COLLIDER_FLAG_IGNORE_SHELL;
        if (npc_test_move_taller_with_slipping(ignoreFlags, &x, &y, &z, centerOffset,
                    atan2(npc->pos.x, npc->pos.z, playerStatus->pos.x, playerStatus->pos.z),
                    npc->collisionDiameter, npc->collisionHeight))
        {
            playerDetected = false;
        }
    }
    evt_set_variable(script, outDetected, playerDetected);
    return ApiStatus_DONE2;
}

void N(set_spotlight_pos_scale)(s32 modelID, f32 x, f32 y, f32 z, f32 scale) {
    Matrix4f mtxTemp;
    Model* model = get_model_from_list_index(get_model_list_index_from_tree_index(modelID));

    guTranslateF(model->userTransformMtx, x, y, z);
    guScaleF(mtxTemp, scale, 1.0f, scale);
    guMtxCatF(mtxTemp, model->userTransformMtx, model->userTransformMtx);
    model->flags |= MODEL_FLAG_MATRIX_DIRTY | MODEL_FLAG_HAS_TRANSFORM;
}

enum SearchlightResultFlags {
    SEARCHLIGHT_FLAG_IN_PRIMARY     = 1,
    SEARCHLIGHT_FLAG_IN_EXTRA       = 0x10,
};

/// Updates the NPC's searchlights and checks whether the player is within either one.
/// @evtapi
/// @param outResult combination of SearchlightResultFlags
/// @param spotlightOffset
/// @param spotlightRadius
/// @param extraSpotlightOffset
/// @param extraSpotlightRadius
/// @param spotlightModel
/// @param lightSourceIdx
API_CALLABLE(N(UpdateSearchlight)) {
    SpriteShadingLightSource* lightSource;
    PlayerStatus* playerStatus = &gPlayerStatus;
    Npc* npc = get_npc_unsafe(script->owner1.enemy->npcID);

    Bytecode* args = script->ptrReadPos;
    s32 outResult = *args++;
    f32 spotlightOffset = *args++;
    f32 spotlightRadius = *args++;
    f32 extraSpotlightOffset = *args++;
    f32 extraSpotlightRadius = *args++;
    // spotlight model and sprite shading light source index
    s32 spotlightModel = *args++;
    s32 lightSourceIdx = *args++;

    f32 x = npc->pos.x;
    f32 z = npc->pos.z;
    s32 outVal = 0;
    f32 dist;
    f32 y;

    // place light source 30 units ahead of the flashlight
    add_vec2D_polar(&x, &z, 30.0f, npc->yaw);

    lightSource = &gSpriteShadingProfile->sources[lightSourceIdx];
    lightSource->pos.x = x;
    lightSource->pos.y = npc->pos.y + 20.0f;
    lightSource->pos.z = z;

    // check if player is inside the first spotlight
    x = npc->pos.x;
    z = npc->pos.z;
    add_vec2D_polar(&x, &z, spotlightOffset, npc->yaw);

    if (dist2D(x, z, playerStatus->pos.x, playerStatus->pos.z) <= spotlightRadius) {
        outVal |= SEARCHLIGHT_FLAG_IN_PRIMARY;
    }

    N(set_spotlight_pos_scale)(spotlightModel, x, npc->pos.y, z, (2.0 * spotlightRadius / 100.0) + 0.3);

    // check if player is inside the second spotlight
    x = npc->pos.x;
    z = npc->pos.z;
    add_vec2D_polar(&x, &z, extraSpotlightOffset, npc->yaw);

    if (dist2D(x, z, playerStatus->pos.x, playerStatus->pos.z) <= extraSpotlightRadius) {
        outVal |= SEARCHLIGHT_FLAG_IN_EXTRA;
    }

    // cancel alert if enemy does not have line of sight to player
    if (outVal & SEARCHLIGHT_FLAG_IN_PRIMARY) {
        x = npc->pos.x;
        y = npc->pos.y;
        z = npc->pos.z;

        dist = dist2D(npc->pos.x, npc->pos.z, playerStatus->pos.x, playerStatus->pos.z);
        if (npc_test_move_taller_with_slipping(0, &x, &y, &z, dist,
                atan2(npc->pos.x, npc->pos.z, playerStatus->pos.x, playerStatus->pos.z),
                npc->collisionDiameter, npc->collisionHeight)) {
            outVal = 0;
        }
    }

    evt_set_variable(script, outResult, outVal);
    return ApiStatus_DONE2;
}
