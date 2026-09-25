#include "common.h"
#include "camera.h"

// implements CAM_UPDATE_UNUSED_CONFINED
// this camera tracks targetPos, clamped within the rectangular region given by ± xLimit and ± zLimit
// y-position is drawn from lookAtObjTarget
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
    camera->lookAtObjTarget.x = targetX;

    targetZ = camera->targetPos.z;
    if (targetZ > camera->params.confined.zLimit) {
        targetZ = camera->params.confined.zLimit;
    }
    if (targetZ < -camera->params.confined.zLimit) {
        targetZ = -camera->params.confined.zLimit;
    }
    camera->lookAtObjTarget.z = targetZ;

    camera->interpYaw = 0.0f;
    camera->curBoomPitch = 0.0f;
    camera->curBoomYaw = 0.0f;
    camera->curBoomLength = camera->params.confined.dist * CamLengthScale;
    camera->targetOffsetY = camera->params.confined.offsetY * CamLengthScale;

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

    dx = camera->lookAtObj.x - camera->lookAtEye.x;
    dy = camera->lookAtObj.y - camera->lookAtEye.y;
    dz = camera->lookAtObj.z - camera->lookAtEye.z;
    dr = sqrtf(SQ(dx) + SQ(dz));

    camera->lookAtYaw = -atan2(0.0f, 0.0f, dx, dz);
    camera->lookAtPitch = atan2(0.0f, 0.0f, dy, -dr);
    camera->curYaw = atan2(camera->lookAtEye.x, camera->lookAtEye.z, camera->lookAtObj.x, camera->lookAtObj.z);
}
