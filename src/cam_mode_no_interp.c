#include "common.h"

// implements CAM_UPDATE_NO_INTERP
// this camera uses a set of control parameters to calculate its lookAtObj and lookAtEye positions,
// which are only updated if skipRecalc = false
// the ultimate target is given by lookAtObjTarget, with an offset given by targetPos (?!)
// in practice, this is used for CAM_BATTLE and CAM_TATTLE, with skipRecalc almost always set to false
//
// control parameters:
// dist -- length of the camera boom arm
// pitch -- rising angle of the boom arm, up toward the y-axis
// yaw -- yaw angle for the boom arm in the xz-plane
// offsetY -- offset of the base of the boom arm above the target point
// fovScale -- adjusts vertical fov, with 100 being normal (=25). scales as 1/x so larger values mean smaller vfov.
// skipRecalc -- do not calculate lookAtObj and lookAtEye from params
void update_camera_no_interp(Camera* camera) {
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
        camera->params.basic.offsetY = 0;
        camera->params.basic.fovScale = 100;

        camera->targetPos.x = 0.0f;
        camera->targetPos.y = 0.0f;
        camera->targetPos.z = 0.0f;

        camera->lookAtObj.x = camera->lookAtObjTarget.x;
        camera->lookAtObj.y = camera->lookAtObjTarget.y;
        camera->lookAtObj.z = camera->lookAtObjTarget.z;
    }

    if (!camera->params.basic.skipRecalc) {
        camera->lookAtObj.x = camera->lookAtObjTarget.x + camera->targetPos.x;
        camera->lookAtObj.y = camera->lookAtObjTarget.y + camera->targetPos.y + camera->params.basic.offsetY / 256.0;
        camera->lookAtObj.z = camera->lookAtObjTarget.z + camera->targetPos.z;

        camera->curBoomLength = camera->params.basic.dist;
        camera->curBoomPitch = camera->params.basic.pitch;
        camera->curBoomYaw = camera->params.basic.yaw;
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

    gBattleStatus.camLookatObjPos.x = camera->lookAtObj.x;
    gBattleStatus.camLookatObjPos.y = camera->lookAtObj.y;
    gBattleStatus.camLookatObjPos.z = camera->lookAtObj.z;
}
