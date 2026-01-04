#include "common.h"
#include "camera.h"

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
