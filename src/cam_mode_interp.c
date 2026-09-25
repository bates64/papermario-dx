#include "common.h"
#include "camera.h"

// implements CAM_UPDATE_INTERP_POS
// this camera uses a set of control parameters to calculate its target lookAtObj and lookAtEye positions,
// then interpolates current positions toward those targets, moving up to half the remaining distance each frame
// position of the camera is determined with a boom and the ultimate target is given by lookAtObjTarget
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

        camera->lookAtObj.x = camera->lookAtObjTarget.x;
        camera->lookAtObj.y = camera->lookAtObjTarget.y + camera->targetOffsetY;
        camera->lookAtObj.z = camera->lookAtObjTarget.z;

        pitchAngle = DEG_TO_RAD(camera->curBoomPitch);
        sinPitch = sin_rad(pitchAngle);
        cosPitch = cos_rad(pitchAngle);

        yawAngle = DEG_TO_RAD(camera->interpYaw);
        sinYaw = sin_rad(yawAngle);
        cosYaw = cos_rad(yawAngle);

        dy = camera->curBoomLength * sinPitch;
        dx = camera->curBoomLength * cosPitch * -sinYaw;
        dz = camera->curBoomLength * cosPitch * cosYaw;

        camera->lookAtEye.x = camera->lookAtObj.x + dx;
        camera->lookAtEye.y = camera->lookAtObj.y + dy;
        camera->lookAtEye.z = camera->lookAtObj.z + dz;
    }

    // interpolate lookAtObj toward lookAtObjTarget by stepping half the difference each frame

    dx = camera->lookAtObjTarget.x - camera->lookAtObj.x;
    dy = camera->lookAtObjTarget.y - camera->lookAtObj.y + camera->targetOffsetY;
    dz = camera->lookAtObjTarget.z - camera->lookAtObj.z;

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

    camera->lookAtObj.x += dx * 0.5f;
    camera->lookAtObj.y += dy * 0.5f;
    camera->lookAtObj.z += dz * 0.5f;

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

    x = camera->lookAtObj.x + dx;
    y = camera->lookAtObj.y + dy;
    z = camera->lookAtObj.z + dz;

    // interpolate lookAtEye toward new eye position by stepping half the difference each frame

    dx = (x - camera->lookAtEye.x) * 0.5f;
    dy = (y - camera->lookAtEye.y) * 0.5f;
    dz = (z - camera->lookAtEye.z) * 0.5f;

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

    camera->lookAtEye.x += dx;
    camera->lookAtEye.y += dy;
    camera->lookAtEye.z += dz;

    // calculate final position and orientation for camera

    dx = camera->lookAtObj.x - camera->lookAtEye.x;
    dy = camera->lookAtObj.y - camera->lookAtEye.y;
    dz = camera->lookAtObj.z - camera->lookAtEye.z;
    dr = sqrtf(SQ(dx) + SQ(dz));

    camera->lookAtYaw = -atan2(0.0f, 0.0f, dx, dz);
    camera->lookAtPitch = atan2(0.0f, 0.0f, dy, -dr);
    camera->curYaw = atan2(camera->lookAtEye.x, camera->lookAtEye.z, camera->lookAtObj.x, camera->lookAtObj.z);
}
