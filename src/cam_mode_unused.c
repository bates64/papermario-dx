#include "common.h"

// unused camera similar to CAM_UPDATE_BATTLE
void update_camera_mode_unused(Camera* camera) {
    f32 yawAngle, sinYaw, cosYaw;
    f32 pitchAngle, sinPitch, cosPitch;
    f32 dx, dy, dz, dr;

    if (camera->needsInit || camera->clearPrevZoneSettings) {
        camera->needsInit = FALSE;
        camera->clearPrevZoneSettings = FALSE;
        camera->battle.skipRecalc = FALSE;
        camera->battle.auxBoomLength = 100;
        camera->battle.auxFovScale = 100;
        camera->battle.auxBoomPitch = 0;
        camera->battle.auxBoomYaw = 0;

        camera->lookAt_obj.x = camera->lookAt_obj_target.x;
        camera->lookAt_obj.y = camera->lookAt_obj_target.y;
        camera->lookAt_obj.z = camera->lookAt_obj_target.z;
    }

    if (!(gPlayerStatus.flags & (PS_FLAG_FALLING | PS_FLAG_JUMPING))) {
        camera->lookAt_obj_target.y = gPlayerStatus.pos.y + 60.0f;
    }
    camera->lookAt_obj_target.x = gPlayerStatus.pos.x;
    camera->lookAt_obj_target.z = gPlayerStatus.pos.z + 400.0f;

    if (!camera->battle.skipRecalc) {
        camera->lookAt_obj.x = camera->lookAt_obj_target.x;
        camera->lookAt_obj.y = camera->lookAt_obj_target.y;
        camera->lookAt_obj.z = camera->lookAt_obj_target.z;

        camera->curBoomYaw = camera->battle.auxBoomYaw;
        camera->curBoomPitch = camera->battle.auxBoomPitch;
        camera->curBoomLength = camera->battle.auxBoomLength;
        camera->vfov = (10000 / camera->battle.auxFovScale) / 4;

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
}
