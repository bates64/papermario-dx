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
    f32 yawAngle, sinYaw, cosYaw;
    f32 pitchAngle, sinPitch, cosPitch;
    f32 dx, dy, dz, dr;
    f32 targetX;
    f32 targetZ;

    targetX = camera->targetPos.x;
    if (targetX > camera->params.confined.xLimit) {
        targetX = camera->params.confined.xLimit;
    }
    if (targetX < -camera->params.confined.xLimit) {
        targetX = -camera->params.confined.xLimit;
    }
    camera->lookAt_obj_target.x = targetX;

    targetZ = camera->targetPos.z;
    if (targetZ > camera->params.confined.zLimit) {
        targetZ = camera->params.confined.zLimit;
    }
    if (targetZ < -camera->params.confined.zLimit) {
        targetZ = -camera->params.confined.zLimit;
    }
    camera->lookAt_obj_target.z = targetZ;

    camera->interpYaw = 0.0f;
    camera->curBoomPitch = 0.0f;
    camera->curBoomYaw = 0.0f;
    camera->curBoomLength = camera->params.confined.dist * CamLengthScale;
    camera->targetOffsetY = camera->params.confined.offsetY * CamLengthScale;

    if (camera->needsInit) {
        camera->needsInit = FALSE;

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

    dx = camera->lookAt_obj.x - camera->lookAt_eye.x;
    dy = camera->lookAt_obj.y - camera->lookAt_eye.y;
    dz = camera->lookAt_obj.z - camera->lookAt_eye.z;
    dr = sqrtf(SQ(dx) + SQ(dz));

    camera->lookAt_yaw = -atan2(0.0f, 0.0f, dx, dz);
    camera->lookAt_pitch = atan2(0.0f, 0.0f, dy, -dr);
    camera->curYaw = atan2(camera->lookAt_eye.x, camera->lookAt_eye.z, camera->lookAt_obj.x, camera->lookAt_obj.z);
}
