#include "common.h"

// implements CAM_UPDATE_UNUSED_AHEAD
// this mode is completely unused in vanilla; it doesn't even have a case in update_cameras
// seems to be based on CAM_UPDATE_NO_INTERP (the one used for battle cam)
// tracks a point 400 units ahead of player position in the z-direction and 60 units above
// defaults to a relatively short boom length and no pitch angle, resulting in a head-on direct view
//
// control parameters:
// dist -- length of the camera boom arm
// pitch -- rising angle of the boom arm, up toward the y-axis
// yaw -- yaw angle for the boom arm in the xz-plane
// skipRecalc -- do not calculate lookAtObj and lookAtEye from params
void update_camera_unused_ahead(Camera* camera) {
    f32 yawAngle, sinYaw, cosYaw;
    f32 pitchAngle, sinPitch, cosPitch;
    f32 dx, dy, dz, dr;

    if (camera->needsInit || camera->needsReinit) {
        camera->needsInit = false;
        camera->needsReinit = false;
        camera->params.basic.skipRecalc = false;
        camera->params.basic.dist = 100;
        camera->params.basic.pitch = 0;
        camera->params.basic.yaw = 0;
        camera->params.basic.fovScale = 100;

        camera->lookAtObj.x = camera->lookAtObjTarget.x;
        camera->lookAtObj.y = camera->lookAtObjTarget.y;
        camera->lookAtObj.z = camera->lookAtObjTarget.z;
    }

    if (!(gPlayerStatus.flags & (PS_FLAG_FALLING | PS_FLAG_JUMPING))) {
        camera->lookAtObjTarget.y = gPlayerStatus.pos.y + 60.0f;
    }
    camera->lookAtObjTarget.x = gPlayerStatus.pos.x;
    camera->lookAtObjTarget.z = gPlayerStatus.pos.z + 400.0f;

    if (!camera->params.basic.skipRecalc) {
        camera->lookAtObj.x = camera->lookAtObjTarget.x;
        camera->lookAtObj.y = camera->lookAtObjTarget.y;
        camera->lookAtObj.z = camera->lookAtObjTarget.z;

        camera->curBoomYaw = camera->params.basic.yaw;
        camera->curBoomPitch = camera->params.basic.pitch;
        camera->curBoomLength = camera->params.basic.dist;
        camera->vfov = (10000 / camera->params.basic.fovScale) / 4;

        pitchAngle = DEG_TO_RAD(camera->curBoomPitch);
        sinPitch = sin_rad(pitchAngle);
        cosPitch = cos_rad(pitchAngle);

        yawAngle = DEG_TO_RAD(camera->curBoomYaw);
        sinYaw = sin_rad(yawAngle);
        cosYaw = cos_rad(yawAngle);

        dy = camera->curBoomLength * sinPitch;
        dx = camera->curBoomLength * cosPitch * -sinYaw;
        dz = camera->curBoomLength * cosPitch * cosYaw;

        camera->lookAtEye.x = camera->lookAtObj.x + dx;
        camera->lookAtEye.y = camera->lookAtObj.y + dy;
        camera->lookAtEye.z = camera->lookAtObj.z + dz;
    }

    dx = camera->lookAtObj.x - camera->lookAtEye.x;
    dy = camera->lookAtObj.y - camera->lookAtEye.y;
    dz = camera->lookAtObj.z - camera->lookAtEye.z;
    dr = sqrtf(SQ(dx) + SQ(dz));

    camera->lookAtYaw = -atan2(0.0f, 0.0f, dx, dz);
    camera->lookAtPitch = atan2(0.0f, 0.0f, dy, -dr);
    camera->curYaw = atan2(camera->lookAtEye.x, camera->lookAtEye.z, camera->lookAtObj.x, camera->lookAtObj.z);
}
