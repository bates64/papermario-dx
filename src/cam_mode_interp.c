#include "common.h"
#include "camera.h"

// implements CAM_UPDATE_UNUSED_CONFINED
// this camera tracks targetPos, clamped within the rectangular region given by +/- xLimit and +/- zLimit
// y-position is drawn from lookAt_obj_target
// does not use easing or interpolation
// uses a boom arm, but pitch and yaw are always zero
//
// control parameters:
// dist -- length of the camera boom arm
// offsetY -- offset of the base of the boom arm above the target point
// xLimit -- confine x position of target from -xLimit to +xLimit
// zLimit -- confine z position of target from -zLimit to +zLimit
void update_camera_unused_confined(Camera* camera) {
    f32 sinBoom;
    f32 cosBoom;
    f32 deltaX;
    f32 deltaY;
    f32 deltaZ;
    f32 deltaX2;
    f32 deltaY2;
    f32 deltaZ2;
    f32 boomYaw;
    f32 boomLength;
    f32 f0;
    f32 f4;
    f32 new_var;

    f0 = camera->targetPos.x;
    deltaX = camera->params.confined.xLimit;
    if (f0 > deltaX) {
        f0 = deltaX;
    }
    if (f0 < -deltaX) {
        f0 = -deltaX;
    }
    camera->lookAt_obj_target.x = f0;
    f4 = camera->targetPos.z;
    deltaZ = camera->params.confined.zLimit;
    if (f4 > deltaZ) {
        f4 = deltaZ;
    }
    if (f4 < -deltaZ) {
        f4 = -deltaZ;
    }
    camera->lookAt_obj_target.z = f4;
    camera->interpYaw = 0.0f;
    camera->curBoomPitch = 0.0f;
    camera->curBoomYaw = camera->interpYaw;
    camera->curBoomLength = camera->params.confined.dist * CamLengthScale;
    camera->targetOffsetY = camera->params.confined.offsetY * CamLengthScale;
    if (camera->needsInit) {
        camera->needsInit = false;
        camera->unk_98 = 0.0f;
        camera->unk_9C = 0.0f;
        camera->lookAt_obj.x = camera->lookAt_obj_target.x;
        camera->lookAt_obj.y = camera->lookAt_obj_target.y + camera->targetOffsetY;
        camera->lookAt_obj.z = camera->lookAt_obj_target.z;
        boomYaw = DEG_TO_RAD(camera->curBoomPitch);
        sinBoom = sin_rad(boomYaw);
        cosBoom = cos_rad(boomYaw);
        deltaX = 0.0f;
        deltaY = 0.0f;
        deltaZ = camera->curBoomLength;
        deltaX2 = deltaX;
        deltaY2 = deltaY;
        boomYaw = deltaX = -deltaY2;
        deltaZ2 = deltaZ;
        new_var = boomYaw;
        deltaX = deltaX2;
        deltaY = cosBoom * deltaY2 + deltaZ2 * sinBoom;
        deltaZ = sinBoom * new_var + deltaZ2 * cosBoom;
        boomYaw = DEG_TO_RAD(camera->interpYaw);
        sinBoom = sin_rad(boomYaw);
        cosBoom = cos_rad(boomYaw);
        deltaX2 = cosBoom * deltaX - deltaZ * sinBoom;
        deltaY2 = deltaY;
        deltaZ2 = sinBoom * deltaX + deltaZ * cosBoom;
        camera->lookAt_eye.x = camera->lookAt_obj.x + deltaX2;
        camera->lookAt_eye.y = camera->lookAt_obj.y + deltaY2;
        camera->lookAt_eye.z = camera->lookAt_obj.z + deltaZ2;
    }
    camera->lookAt_obj.x = camera->lookAt_obj_target.x;
    camera->lookAt_obj.y = camera->lookAt_obj_target.y + camera->targetOffsetY;
    camera->lookAt_obj.z = camera->lookAt_obj_target.z;
    boomYaw = DEG_TO_RAD(camera->curBoomPitch);
    sinBoom = sin_rad(boomYaw);
    cosBoom = cos_rad(boomYaw);
    deltaX = 0.0f;
    deltaY = 0.0f;
    deltaZ = camera->curBoomLength;
    deltaX2 = deltaX;
    deltaY2 = deltaY;
    boomYaw = deltaX = -deltaY2;
    deltaZ2 = deltaZ;
    new_var = boomYaw;
    deltaX = deltaX2;
    deltaY = cosBoom * deltaY2 + deltaZ2 * sinBoom;
    deltaZ = sinBoom * new_var + deltaZ2 * cosBoom;
    boomYaw = DEG_TO_RAD(camera->interpYaw);
    sinBoom = sin_rad(boomYaw);
    cosBoom = cos_rad(boomYaw);
    deltaX2 = cosBoom * deltaX - deltaZ * sinBoom;
    deltaY2 = deltaY;
    deltaZ2 = sinBoom * deltaX + deltaZ * cosBoom;
    camera->lookAt_eye.x = camera->lookAt_obj.x + deltaX2;
    camera->lookAt_eye.y = camera->lookAt_obj.y + deltaY2;
    camera->lookAt_eye.z = camera->lookAt_obj.z + deltaZ2;
    camera->curYaw = atan2(camera->lookAt_eye.x, camera->lookAt_eye.z, camera->lookAt_obj.x, camera->lookAt_obj.z);
    deltaX = camera->lookAt_obj.x - camera->lookAt_eye.x;
    deltaY = camera->lookAt_obj.y - camera->lookAt_eye.y;
    deltaZ = camera->lookAt_obj.z - camera->lookAt_eye.z;
    camera->lookAt_yaw = -atan2(0.0f, 0.0f, deltaX, deltaZ);
    camera->lookAt_pitch = atan2(0.0f, 0.0f, deltaY, -sqrtf(SQ(deltaX) + SQ(deltaZ)));
}

// implements CAM_UPDATE_INTERP_POS
// this camera uses a set of control parameters to calculate its target lookAt_obj and lookAt_eye positions,
// then interpolates current positions toward those targets, moving up to half the remaining distance each frame
// position of the camera is determined with a boom and the ultimate target is given by lookAt_obj_target
//
// control parameters:
// dist -- length of the camera boom arm
// pitch -- rising angle of the boom arm, up toward the y-axis
// yaw -- yaw angle for the boom arm in the xz-plane
// offsetY -- offset of the base of the boom arm above the target point
void update_camera_interp_pos(Camera *camera) {
    f32 pitchAngle, sinPitch, cosPitch;
    f32 yawAngle, sinYaw, cosYaw;
    f32 x, y, z, dx, dy, dz, dr;

    camera->curBoomLength = camera->params.interp.dist * CamLengthScale;
    camera->targetOffsetY = camera->params.interp.offsetY * CamLengthScale;
    camera->curBoomPitch = camera->params.interp.pitch;
    camera->interpYaw = camera->params.interp.yaw;
    camera->curBoomYaw = camera->interpYaw;

    if (camera->needsInit) {
        camera->needsInit = false;
        camera->unk_98 = 0.0f;
        camera->unk_9C = 0.0f;

        camera->lookAt_obj.x = camera->lookAt_obj_target.x;
        camera->lookAt_obj.y = camera->lookAt_obj_target.y + camera->targetOffsetY;
        camera->lookAt_obj.z = camera->lookAt_obj_target.z;

        pitchAngle = DEG_TO_RAD(camera->curBoomPitch);
        sinPitch = sin_rad(pitchAngle);
        cosPitch = cos_rad(pitchAngle);

        yawAngle = DEG_TO_RAD(camera->interpYaw);
        sinYaw = sin_rad(yawAngle);
        cosYaw = cos_rad(yawAngle);

        dy = camera->curBoomLength * sinPitch;
        dx = camera->curBoomLength * cosPitch * -sinYaw;
        dz = camera->curBoomLength * cosPitch * cosYaw;

        camera->lookAt_eye.x = camera->lookAt_obj.x + dx;
        camera->lookAt_eye.y = camera->lookAt_obj.y + dy;
        camera->lookAt_eye.z = camera->lookAt_obj.z + dz;
    }

    // interpolate lookAt_obj toward lookAt_obj_target by stepping half the difference each frame

    dx = camera->lookAt_obj_target.x - camera->lookAt_obj.x;
    dy = camera->lookAt_obj_target.y - camera->lookAt_obj.y + camera->targetOffsetY;
    dz = camera->lookAt_obj_target.z - camera->lookAt_obj.z;

    if (fabsf(dx) > 16.0f) {
        if (dx < 0.0f) {
            dx = -16.0f;
        } else {
            dx = 16.0f;
        }
    }
    if (fabsf(dy) > 16.0f) {
        if (dy < 0.0f) {
            dy = -16.0f;
        } else {
            dy = 16.0f;
        }
    }
    if (fabsf(dz) > 16.0f) {
        if (dz < 0.0f) {
            dz = -16.0f;
        } else {
            dz = 16.0f;
        }
    }

    camera->lookAt_obj.x += dx * 0.5f;
    camera->lookAt_obj.y += dy * 0.5f;
    camera->lookAt_obj.z += dz * 0.5f;

    // calculate new camera eye position from distance and angles

    pitchAngle = DEG_TO_RAD(camera->curBoomPitch);
    sinPitch = sin_rad(pitchAngle);
    cosPitch = cos_rad(pitchAngle);

    yawAngle = DEG_TO_RAD(camera->interpYaw);
    sinYaw = sin_rad(yawAngle);
    cosYaw = cos_rad(yawAngle);

    dy = camera->curBoomLength * sinPitch;
    dx = camera->curBoomLength * cosPitch * -sinYaw;
    dz = camera->curBoomLength * cosPitch * cosYaw;

    x = camera->lookAt_obj.x + dx;
    y = camera->lookAt_obj.y + dy;
    z = camera->lookAt_obj.z + dz;

    // interpolate lookAt_eye toward new eye position by stepping half the difference each frame

    dx = (x - camera->lookAt_eye.x) * 0.5f;
    dy = (y - camera->lookAt_eye.y) * 0.5f;
    dz = (z - camera->lookAt_eye.z) * 0.5f;

    if (fabsf(dx) > 16.0f) {
        if (dx < 0.0f) {
            dx = -16.0f;
        } else {
            dx = 16.0f;
        }
    }
    if (fabsf(dy) > 16.0f) {
        if (dy < 0.0f) {
            dy = -16.0f;
        } else {
            dy = 16.0f;
        }
    }
    if (fabsf(dz) > 16.0f) {
        if (dz < 0.0f) {
            dz = -16.0f;
        } else {
            dz = 16.0f;
        }
    }

    camera->lookAt_eye.x += dx;
    camera->lookAt_eye.y += dy;
    camera->lookAt_eye.z += dz;

    // calculate final position and orientation for camera

    dx = camera->lookAt_obj.x - camera->lookAt_eye.x;
    dy = camera->lookAt_obj.y - camera->lookAt_eye.y;
    dz = camera->lookAt_obj.z - camera->lookAt_eye.z;
    dr = sqrtf(SQ(dx) + SQ(dz));

    camera->lookAt_yaw = -atan2(0.0f, 0.0f, dx, dz);
    camera->lookAt_pitch = atan2(0.0f, 0.0f, dy, -dr);
    camera->curYaw = atan2(camera->lookAt_eye.x, camera->lookAt_eye.z, camera->lookAt_obj.x, camera->lookAt_obj.z);
}
