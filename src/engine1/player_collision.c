#include "common.h"

HitID player_raycast_down(f32*, f32*, f32*, f32*);
HitID player_raycast_up_corner(f32* x, f32* y, f32* z, f32* length);
HitID player_raycast_general(s32, f32, f32, f32, f32, f32, f32, f32*, f32*, f32*, f32*, f32*, f32*, f32*);
void player_get_slip_vector(f32* outX, f32* outY, f32 x, f32 y, f32 nX, f32 nY);

HitID player_raycast_below(f32 yaw, f32 diameter, f32* outX, f32* outY, f32* outZ, f32* outLength,
    f32* hitRx, f32* hitRz, f32* hitDirX, f32* hitDirZ
) {
    f32 x, y, z, length;
    f32 inputX, inputY, inputZ, inputLength;
    f32 cosTheta;
    f32 sinTheta;
    f32 temp_f20;
    f32 cosTemp;
    f32 sinTemp;
    s32 hitID;
    s32 ret;

    *hitRx = 0.0f;
    *hitRz = 0.0f;
    *hitDirX = 0.0f;
    *hitDirZ = 0.0f;
    inputLength = *outLength;
    temp_f20 = diameter * 0.28f;
    sin_cos_rad(DEG_TO_RAD(yaw), &sinTheta, &cosTheta);
    sinTemp = temp_f20 * sinTheta;
    cosTemp = -temp_f20 * cosTheta;
    inputX = *outX;
    inputY = *outY;
    inputZ = *outZ;

    x = inputX + sinTemp;
    y = inputY;
    z = inputZ + cosTemp;
    length = inputLength;
    hitID = player_raycast_down(&x, &y, &z, &length);
    ret = NO_COLLIDER;
    if (hitID > NO_COLLIDER && length <= fabsf(*outLength)) {
        *hitRx = -gGameStatusPtr->playerGroundTraceAngles.x;
        *hitRz = -gGameStatusPtr->playerGroundTraceAngles.z;
        *outX = x;
        *outY = y;
        *outZ = z;
        *outLength = length;
        *hitDirX = sinTemp;
        *hitDirZ = cosTemp;
        ret = hitID;
    }

    x = inputX - sinTemp;
    y = inputY;
    z = inputZ - cosTemp;
    length = inputLength;
    hitID = player_raycast_down(&x, &y, &z, &length);
    if (hitID > NO_COLLIDER && length <= fabsf(*outLength)) {
        *hitRx = -gGameStatusPtr->playerGroundTraceAngles.x;
        *hitRz = -gGameStatusPtr->playerGroundTraceAngles.z;
        *outX = x;
        *outY = y;
        *outZ = z;
        *outLength = length;
        *hitDirX = -sinTemp;
        *hitDirZ = -cosTemp;
        ret = hitID;
    }

    // @bug duplicate test -- same as first one. should be +/-?
    x = inputX + cosTemp;
    y = inputY;
    z = inputZ + sinTemp;
    length = inputLength;
    hitID = player_raycast_down(&x, &y, &z, &length);
    if (hitID > NO_COLLIDER && length <= fabsf(*outLength)) {
        *hitRx = -gGameStatusPtr->playerGroundTraceAngles.x;
        *hitRz = -gGameStatusPtr->playerGroundTraceAngles.z;
        *outX = x;
        *outY = y;
        *outZ = z;
        *outLength = length;
        *hitDirX = sinTemp;
        *hitDirZ = cosTemp;
        ret = hitID;
    }

    // @bug duplicate test -- same as second one. should be -/+?
    x = inputX - cosTemp;
    y = inputY;
    z = inputZ - sinTemp;
    length = inputLength;
    hitID = player_raycast_down(&x, &y, &z, &length);
    if (hitID > NO_COLLIDER && length <= fabsf(*outLength)) {
        *hitRx = -gGameStatusPtr->playerGroundTraceAngles.x;
        *hitRz = -gGameStatusPtr->playerGroundTraceAngles.z;
        *outX = x;
        *outY = y;
        *outZ = z;
        *outLength = length;
        *hitDirX = -sinTemp;
        *hitDirZ = -cosTemp;
        ret = hitID;
    }

    x = inputX;
    y = inputY;
    z = inputZ;
    length = inputLength;
    hitID = player_raycast_down(&x, &y, &z, &length);
    if (hitID > NO_COLLIDER && length <= fabsf(*outLength)) {
        *hitRx = -gGameStatusPtr->playerGroundTraceAngles.x;
        *hitRz = -gGameStatusPtr->playerGroundTraceAngles.z;
        *outX = x;
        *outY = y;
        *outZ = z;
        *outLength = length;
        *hitDirX = 0.0f;
        *hitDirZ = 0.0f;
        ret = hitID;
    }

    if (ret <= NO_COLLIDER) {
        *outX = x;
        *outY = y;
        *outZ = z;
    }

    return ret;
}

HitID player_raycast_below_cam_relative(PlayerStatus* playerStatus, f32* outX, f32* outY, f32* outZ, f32* outLength,
    f32* hitRx, f32* hitRz, f32* hitDirX, f32* hitDirZ
) {
    f32 yaw = 0.0f;

    if (playerStatus->spriteFacingAngle >= 90.0f && playerStatus->spriteFacingAngle < 270.0f) {
        yaw = 180.0f;
    }

    return player_raycast_below(yaw - 90.0f + gCameras[gCurrentCameraID].curYaw, playerStatus->colliderDiameter,
        outX, outY, outZ, outLength, hitRx, hitRz, hitDirX, hitDirZ);
}

HitID player_raycast_down(f32* x, f32* y, f32* z, f32* length) {
    f32 hitX;
    f32 hitY;
    f32 hitZ;
    f32 hitDepth;
    f32 hitNx;
    f32 hitNy;
    f32 hitNz;
    s32 entityID, colliderID;
    Entity* entity;
    s32 ret = NO_COLLIDER;

    hitDepth = *length;
    entityID = test_ray_entities(*x, *y, *z, 0.0f, -1.0f, 0.0f, &hitX, &hitY, &hitZ, &hitDepth, &hitNx, &hitNy, &hitNz);
    if (entityID > NO_COLLIDER) {
        entity = get_entity_by_index(entityID);
        if (entity->alpha < 255) {
            entity->collisionTimer = 4;
            entity->flags |= ENTITY_FLAG_CONTINUOUS_COLLISION;
        } else {
            ret = entityID | COLLISION_WITH_ENTITY_BIT;
        }
    }

    colliderID = test_ray_colliders(COLLIDER_FLAG_IGNORE_PLAYER, *x, *y, *z, 0, -1.0f, 0, &hitX, &hitY, &hitZ, &hitDepth, &hitNx, &hitNy, &hitNz);
    if (colliderID > NO_COLLIDER) {
        ret = colliderID;
    }

    if (ret > NO_COLLIDER) {
        *length = hitDepth;
        *x = hitX;
        *y = hitY;
        *z = hitZ;
        gGameStatusPtr->playerGroundTraceNormal.x = hitNx;
        gGameStatusPtr->playerGroundTraceNormal.y = hitNy;
        gGameStatusPtr->playerGroundTraceNormal.z = hitNz;
        PlayerNormalYaw = get_player_normal_yaw();
        PlayerNormalPitch = get_player_normal_pitch();
        gGameStatusPtr->playerGroundTraceAngles.x = atan2(0.0f, 0.0f, hitNz * 100.0, hitNy * 100.0);
        gGameStatusPtr->playerGroundTraceAngles.y = 0.0f;
        gGameStatusPtr->playerGroundTraceAngles.z = atan2(0.0f, 0.0f, hitNx * 100.0, hitNy * 100.0);
    } else {
        gGameStatusPtr->playerGroundTraceAngles.x = 0.0f;
        gGameStatusPtr->playerGroundTraceAngles.y = 0.0f;
        gGameStatusPtr->playerGroundTraceAngles.z = 0.0f;
    }
    return ret;
}

HitID player_raycast_up_corners(PlayerStatus* player, f32* posX, f32* posY, f32* posZ, f32* hitDepth, f32 yaw) {
    f32 startX;
    f32 startY;
    f32 startZ;
    f32 depth;
    f32 theta;
    f32 deltaZ;
    f32 deltaX;
    f32 x,y,z;
    s32 ret;
    s32 hitID;
    f32 radius;

    radius = player->colliderDiameter * 0.3f;
    theta = DEG_TO_RAD(yaw);
    deltaX = radius * sin_rad(theta);
    deltaZ = -radius * cos_rad(theta);

    x = *posX;
    y = *posY;
    z = *posZ;

    depth = *hitDepth;
    startX = x + deltaX;
    startY = y;
    startZ = z + deltaZ;

    ret = NO_COLLIDER;
    hitID = player_raycast_up_corner(&startX, &startY, &startZ, &depth);

    if (hitID <= NO_COLLIDER) {
        startX = x - deltaX;
        startY = y;
        startZ = z - deltaZ;
        hitID = player_raycast_up_corner(&startX, &startY, &startZ, &depth);
    }

    if (hitID <= NO_COLLIDER) {
        startX = x + deltaZ;
        startY = y;
        startZ = z + deltaX;
        hitID = player_raycast_up_corner(&startX, &startY, &startZ, &depth);
    }

    if (hitID <= NO_COLLIDER) {
        startX = x - deltaZ;
        startY = y;
        startZ = z - deltaX;
        hitID = player_raycast_up_corner(&startX, &startY, &startZ, &depth);
    }

    if (hitID > NO_COLLIDER) {
        *posX = startX;
        *posY = startY;
        *posZ = startZ;
        *hitDepth = depth;
        ret = hitID;
    }

    if (ret <= NO_COLLIDER) {
        *posX = startX;
        *posY = startY;
        *posZ = startZ;
        *hitDepth = 0;
    }

    return ret;
}

HitID player_raycast_up_corner(f32* x, f32* y, f32* z, f32* length) {
    f32 hitX;
    f32 hitY;
    f32 hitZ;
    f32 hitDepth;
    f32 hitNx;
    f32 hitNy;
    f32 hitNz;
    s32 hitID;
    s32 ret;
    f32 sx, sy, sz;
    f32 sx2, sy2, sz2;

    ret = NO_COLLIDER;

     // needed to match
    sx2 = sx = *x;
    sy2 = sy = *y;
    sz2 = sz = *z;
    hitDepth = *length;
    hitID = test_ray_colliders(COLLIDER_FLAG_IGNORE_PLAYER, sx, sy, sz, 0.0f, 1.0f, 0.0f, &hitX, &hitY, &hitZ, &hitDepth, &hitNx, &hitNy, &hitNz);
    if (hitID > NO_COLLIDER && *length > hitDepth) {
        *length = hitDepth;
        ret = hitID;
        *x = sx = sx2;
        *y = sy = sy2;
        *z = sz = sz2;
    }

    hitDepth = 10.0f;
    hitID = test_ray_entities(*x, *y, *z, 0.0f, 1.0f, 0.0f, &hitX, &hitY, &hitZ, &hitDepth, &hitNx, &hitNy, &hitNz);
    sx = sx2;
    sy = sy2;
    sz = sz2;
    if (hitID > NO_COLLIDER && *length > hitDepth) {
        get_entity_by_index(hitID);
        ret = hitID | COLLISION_WITH_ENTITY_BIT;
        *length = hitDepth;
        *x = sx;
        *y = sy;
        *z = sz;
    }

    return ret;
}

HitID player_test_lateral_overlap(s32 mode, PlayerStatus* playerStatus, f32* x, f32* y, f32* z, f32 length, f32 yaw) {
    f32 sinTheta;
    f32 cosTheta;
    f32 hitX;
    f32 hitY;
    f32 hitZ;
    f32 hitDepth;
    f32 hitNx;
    f32 hitNy;
    f32 hitNz;
    f32 slipDx;
    f32 slipDz;
    f32 depthDiff;
    f32 radius;
    f32 originalDepth;
    s32 hitID;
    f32 height;
    f32 targetDx;
    f32 targetDz;
    f32 dx;
    f32 dz;
    s32 ret;

    radius = playerStatus->colliderDiameter * 0.5f;
    ret = NO_COLLIDER;

    if (!(playerStatus->flags & (PS_FLAG_FALLING | PS_FLAG_JUMPING))) {
        height = playerStatus->colliderHeight * 0.286f;
    } else {
        height = 1.0f;
    }

    sin_cos_rad(DEG_TO_RAD(yaw), &sinTheta, &cosTheta);
    cosTheta = -cosTheta;
    hitDepth = length + radius;
    hitID = player_raycast_general(mode, *x, *y + height, *z, sinTheta, 0, cosTheta, &hitX, &hitY, &hitZ, &hitDepth, &hitNx, &hitNy, &hitNz);

    if (mode == PLAYER_COLLISION_HAMMER) {
        targetDx = 0.0f;
        targetDz = 0.0f;
    } else {
        targetDx = length * sinTheta;
        targetDz = length * cosTheta;
    }

    if (hitID > NO_COLLIDER) {
        originalDepth = length + radius;
        if (hitDepth <= originalDepth) {
            depthDiff = hitDepth - originalDepth;
            dx = depthDiff * sinTheta;
            dz = depthDiff * cosTheta;

            player_get_slip_vector(&slipDx, &slipDz, targetDx, targetDz, hitNx, hitNz);
            *x += dx + slipDx;
            *z += dz + slipDz;
            ret = hitID;
        }
    }

    *x += targetDx;
    *z += targetDz;
    return ret;
}

HitID player_raycast_general(s32 mode, f32 startX, f32 startY, f32 startZ, f32 dirX, f32 dirY, f32 dirZ, f32* hitX,
                            f32* hitY, f32* hitZ, f32* hitDepth, f32*hitNx, f32* hitNy, f32* hitNz) {
    f32 nAngleX;
    f32 nAngleZ;
    s32 entityID;
    s32 colliderID;
    Entity* entity;
    s32 ignoreFlags;
    s32 ret;

    #if DX_DEBUG_MENU
    if (dx_debug_is_cheat_enabled(DEBUG_CHEAT_IGNORE_WALLS)) {
        return NO_COLLIDER;
    }
    #endif

    entityID = test_ray_entities(startX, startY, startZ, dirX, dirY, dirZ, hitX, hitY, hitZ, hitDepth, hitNx, hitNy,
                                hitNz);
    ret = NO_COLLIDER;
    if (entityID > NO_COLLIDER) {
        entity = get_entity_by_index(entityID);
        if (entity->alpha < 255) {
            entity->collisionTimer = 0;
            entity->flags |= ENTITY_FLAG_CONTINUOUS_COLLISION;
        } else {
            ret = entityID | COLLISION_WITH_ENTITY_BIT;
        }
    } else if (mode == PLAYER_COLLISION_HAMMER) {
        ret = test_ray_colliders(COLLIDER_FLAG_IGNORE_SHELL, startX, startY, startZ, dirX, dirY, dirZ,
            hitX, hitY, hitZ, hitDepth, hitNx, hitNy, hitNz);
    }

    if (mode == PLAYER_COLLISION_1 || mode == PLAYER_COLLISION_HAMMER) {
        return ret;
    }

    if (mode == PLAYER_COLLISION_4) {
        ignoreFlags = COLLIDER_FLAG_DOCK_WALL;
    } else {
        ignoreFlags = COLLIDER_FLAG_IGNORE_PLAYER;
    }

    colliderID = test_ray_colliders(ignoreFlags, startX, startY, startZ, dirX, dirY, dirZ,
        hitX, hitY, hitZ, hitDepth, hitNx, hitNy, hitNz);

    if (ret <= NO_COLLIDER) {
        ret = colliderID;
    }

    if (ret > NO_COLLIDER) {
        nAngleZ = 180.0f - atan2(0, 0, *hitNz * 100.0, *hitNy * 100.0);
        nAngleX = 180.0f - atan2(0, 0, *hitNx * 100.0, *hitNy * 100.0);

        if (!((nAngleZ == 90.0f && nAngleX == 90.0f) || fabs(nAngleZ) >= 30.0 || fabs(nAngleX) >= 30.0)) {
            ret = NO_COLLIDER;
        }
    }

    return ret;
}

/// Only used for Peach physics
HitID player_test_move_without_slipping(PlayerStatus* playerStatus, f32* x, f32* y, f32* z, f32 length, f32 yaw, s32* hasClimbableStep) {
    f32 sinTheta;
    f32 cosTheta;
    f32 hitX;
    f32 hitY;
    f32 hitZ;
    f32 hitDepth;
    f32 hitNx;
    f32 hitNy;
    f32 hitNz;
    f32 slipDx;
    f32 slipDz;
    f32 depth;
    f32 radius;
    f32 depthDiff;
    f32 height;
    s32 ret;
    s32 hitID;
    f32 targetDx;
    f32 targetDz;
    f32 dx, dz;

    radius = playerStatus->colliderDiameter * 0.5f;
    height = playerStatus->colliderHeight * 0.286f;
    sin_cos_rad(DEG_TO_RAD(yaw), &sinTheta, &cosTheta);

    depth = length + radius;
    cosTheta = -cosTheta;
    hitDepth = depth;
    dx = radius * sinTheta;
    ret = NO_COLLIDER;

    hitID = player_raycast_general(PLAYER_COLLISION_0, *x, *y + 0.1, *z, sinTheta, 0, cosTheta, &hitX, &hitY, &hitZ, &hitDepth, &hitNx, &hitNy, &hitNz);
    if (hitID > NO_COLLIDER && hitDepth <= depth) {
        *hasClimbableStep = true;
    }

    depth = length + radius;
    hitDepth = depth;
    dz = radius * cosTheta;

    hitID = player_raycast_general(PLAYER_COLLISION_0, *x, *y + height, *z, sinTheta, 0, cosTheta, &hitX, &hitY, &hitZ, &hitDepth, &hitNx, &hitNy, &hitNz);

    targetDx = 0.0f;
    targetDz = 0.0f;

    if (hitID > NO_COLLIDER && hitDepth <= depth) {
        depthDiff = hitDepth - depth;
        dx = depthDiff * sinTheta;
        dz = depthDiff * cosTheta;
        player_get_slip_vector(&slipDx, &slipDz, 0.0f, 0.0f, hitNx, hitNz);
        *x += dx + slipDx;
        *z += dz + slipDz;
        ret = hitID;
    }
    *x += targetDx;
    *z += targetDz;
    return ret;
}

void player_get_slip_vector(f32* outX, f32* outY, f32 x, f32 y, f32 nX, f32 nY) {
    f32 projectionLength = (x * nX) + (y * nY);

    *outX = (x - projectionLength * nX) * 0.5f;
    *outY = (y - projectionLength * nY) * 0.5f;
}

HitID player_test_move_with_slipping(PlayerStatus* playerStatus, f32* x, f32* y, f32* z, f32 length, f32 yaw) {
    f32 sinTheta;
    f32 cosTheta;
    f32 hitX;
    f32 hitY;
    f32 hitZ;
    f32 hitDepth;
    f32 hitNx;
    f32 hitNy;
    f32 hitNz;
    f32 slipDx;
    f32 slipDz;
    f32 radius;
    f32 height;
    s32 hitID;
    f32 targetDx, targetDz;
    f32 dx, dz;
    f32 depthDiff;
    s32 ret = NO_COLLIDER;

    height = 0.0f;
    if (!(playerStatus->flags & (PS_FLAG_JUMPING | PS_FLAG_FALLING))) {
        height = 10.01f;
    }
    radius = playerStatus->colliderDiameter * 0.5f;

    sin_cos_rad(DEG_TO_RAD(yaw), &sinTheta, &cosTheta);
    cosTheta = -cosTheta;
    hitDepth = length + radius;

    targetDx = length * sinTheta;
    targetDz = length * cosTheta;

    hitID = player_raycast_general(PLAYER_COLLISION_0, *x, *y + height, *z, sinTheta, 0, cosTheta, &hitX, &hitY, &hitZ, &hitDepth, &hitNx, &hitNy, &hitNz);
    if (hitID > NO_COLLIDER && (depthDiff = hitDepth, depthDiff <= length + radius)) {
        depthDiff -= (length + radius);
        dx = depthDiff * sinTheta;
        dz = depthDiff * cosTheta;
        player_get_slip_vector(&slipDx, &slipDz, targetDx, targetDz, hitNx, hitNz);
        *x += dx + slipDx;
        *z += dz + slipDz;
        ret = hitID;
    } else {
        height = playerStatus->colliderHeight * 0.75;
        hitID = player_raycast_general(PLAYER_COLLISION_0, *x, *y + height, *z, sinTheta, 0, cosTheta, &hitX, &hitY, &hitZ, &hitDepth, &hitNx, &hitNy, &hitNz);
        if (hitID > NO_COLLIDER && (depthDiff = hitDepth, depthDiff <= length + radius)) {
            depthDiff -= (length + radius);
            dx = depthDiff * sinTheta;
            dz = depthDiff * cosTheta;
            player_get_slip_vector(&slipDx, &slipDz, targetDx, targetDz, hitNx, hitNz);
            *x += dx + slipDx;
            *z += dz + slipDz;
            ret = hitID;
        }
    }

    *x += targetDx;
    *z += targetDz;
    return ret;
}
