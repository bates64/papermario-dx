#include "common.h"

// implements CAM_UPDATE_NO_INTERP
// this camera uses a set of control parameters to calculate its lookAt_obj and lookAt_eye positions,
// which are only updated if skipRecalc = FALSE
// the ultimate target is given by lookAt_obj_target, with an offset given by targetPos (?!)
// in practice, this is used for CAM_BATTLE and CAM_TATTLE, with skipRecalc almost always set to FALSE
//
// control parameters:
// dist -- length of the camera boom arm
// pitch -- rising angle of the boom arm, up toward the y-axis
// yaw -- yaw angle for the boom arm in the xz-plane
// offsetY -- offset of the base of the boom arm above the target point
// fovScale -- adjusts vertical fov, with 100 being normal (=25). scales as 1/x so larger values mean smaller vfov.
// skipRecalc -- do not calculate lookAt_obj and lookAt_eye from params
void update_camera_no_interp(Camera* camera) {
    f32 yawAngle, sinYaw, cosYaw;
    f32 pitchAngle, sinPitch, cosPitch;
    f32 dx, dy, dz, dr;

    if (camera->needsInit || camera->needsReinit) {
        camera->needsInit = FALSE;
        camera->needsReinit = FALSE;
        camera->params.basic.skipRecalc = FALSE;
        camera->params.basic.dist = 100;
        camera->params.basic.pitch = 0;
        camera->params.basic.yaw = 0;
        camera->params.basic.offsetY = 0;
        camera->params.basic.fovScale = 100;

        camera->targetPos.x = 0.0f;
        camera->targetPos.y = 0.0f;
        camera->targetPos.z = 0.0f;

        camera->lookAt_obj.x = camera->lookAt_obj_target.x;
        camera->lookAt_obj.y = camera->lookAt_obj_target.y;
        camera->lookAt_obj.z = camera->lookAt_obj_target.z;
    }

    if (!camera->params.basic.skipRecalc) {
        camera->lookAt_obj.x = camera->lookAt_obj_target.x + camera->targetPos.x;
        camera->lookAt_obj.y = camera->lookAt_obj_target.y + camera->targetPos.y + camera->params.basic.offsetY / 256.0;
        camera->lookAt_obj.z = camera->lookAt_obj_target.z + camera->targetPos.z;

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

        camera->lookAt_eye.x = camera->lookAt_obj.x + dx;
        camera->lookAt_eye.y = camera->lookAt_obj.y + dy;
        camera->lookAt_eye.z = camera->lookAt_obj.z + dz;
    }

    dx = camera->lookAt_obj.x - camera->lookAt_eye.x;
    dy = camera->lookAt_obj.y - camera->lookAt_eye.y;
    dz = camera->lookAt_obj.z - camera->lookAt_eye.z;
    dr = sqrtf(SQ(dx) + SQ(dz));

    camera->lookAt_yaw = -atan2(0.0f, 0.0f, dx, dz);
    camera->lookAt_pitch = atan2(0.0f, 0.0f, dy, -dr);
    camera->curYaw = atan2(camera->lookAt_eye.x, camera->lookAt_eye.z, camera->lookAt_obj.x, camera->lookAt_obj.z);

    gBattleStatus.camLookatObjPos.x = camera->lookAt_obj.x;
    gBattleStatus.camLookatObjPos.y = camera->lookAt_obj.y;
    gBattleStatus.camLookatObjPos.z = camera->lookAt_obj.z;
}
