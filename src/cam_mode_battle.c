#include "common.h"
#include "dx/debug_menu.h"

// implementation for CAM_UPDATE_BATTLE
void update_camera_battle(Camera* camera) {
    f32 pitchAngle, sinPitch, cosPitch;
    f32 yawAngle, sinYaw, cosYaw;
    f32 dx, dy, dz, dr;

    if (camera->needsInit || camera->clearPrevZoneSettings) {
        camera->needsInit = FALSE;
        camera->clearPrevZoneSettings = FALSE;
        camera->auxPitch = 0;
        camera->auxBoomLength = 100;
        camera->lookAt_dist = 100;
        camera->auxBoomPitch = 0;
        camera->auxBoomYaw = 0;
        camera->auxBoomZOffset = 0;

        camera->targetPos.x = 0.0f;
        camera->targetPos.y = 0.0f;
        camera->targetPos.z = 0.0f;

        camera->lookAt_obj.x = camera->lookAt_obj_target.x;
        camera->lookAt_obj.y = camera->lookAt_obj_target.y;
        camera->lookAt_obj.z = camera->lookAt_obj_target.z;
    }

    if (camera->auxPitch == 0) {
        camera->lookAt_obj.x = camera->lookAt_obj_target.x + camera->targetPos.x;
        camera->lookAt_obj.y = camera->lookAt_obj_target.y + camera->targetPos.y + camera->auxBoomZOffset / 256.0;
        camera->lookAt_obj.z = camera->lookAt_obj_target.z + camera->targetPos.z;

        camera->curBoomLength = camera->auxBoomLength;
        camera->curBoomPitch = camera->auxBoomPitch;
        camera->curBoomYaw = camera->auxBoomYaw;
        camera->vfov = (10000 / camera->lookAt_dist) / 4;

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
