#include "common.h"
#include "camera.h"

// implementation for CAM_UPDATE_UNUSED_4
void update_camera_mode_4(Camera* camera) {
    f32 yawAngle, sinYaw, cosYaw;
    f32 pitchAngle, sinPitch, cosPitch;
    f32 dx, dy, dz, dr;
    f32 targetX;
    f32 targetZ;

    targetX = camera->targetPos.x;
    if (targetX > camera->auxPitch) {
        targetX = camera->auxPitch;
    }
    if (targetX < -camera->auxPitch) {
        targetX = -camera->auxPitch;
    }
    camera->lookAt_obj_target.x = targetX;

    targetZ = camera->targetPos.z;
    if (targetZ > camera->auxBoomLength) {
        targetZ = camera->auxBoomLength;
    }
    if (targetZ < -camera->auxBoomLength) {
        targetZ = -camera->auxBoomLength;
    }
    camera->lookAt_obj_target.z = targetZ;

    camera->unk_70 = 0.0f;
    camera->curBoomPitch = 0.0f;
    camera->curBoomYaw = 0.0f;
    camera->curBoomLength = camera->lookAt_dist * D_8009A5EC;
    camera->curYOffset = camera->auxBoomPitch * D_8009A5EC;

    if (camera->needsInit) {
        camera->needsInit = FALSE;
        camera->unk_98 = 0.0f;
        camera->unk_9C = 0.0f;

        camera->lookAt_obj.x = camera->lookAt_obj_target.x;
        camera->lookAt_obj.y = camera->lookAt_obj_target.y + camera->curYOffset;
        camera->lookAt_obj.z = camera->lookAt_obj_target.z;

        pitchAngle = DEG_TO_RAD(camera->curBoomPitch);
        sinPitch = sin_rad(pitchAngle);
        cosPitch = cos_rad(pitchAngle);

        yawAngle = DEG_TO_RAD(camera->unk_70);
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
    camera->lookAt_obj.y = camera->lookAt_obj_target.y + camera->curYOffset;
    camera->lookAt_obj.z = camera->lookAt_obj_target.z;

    pitchAngle = DEG_TO_RAD(camera->curBoomPitch);
    sinPitch = sin_rad(pitchAngle);
    cosPitch = cos_rad(pitchAngle);

    yawAngle = DEG_TO_RAD(camera->unk_70);
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
    camera->curPitch = atan2(0.0f, 0.0f, dy, -dr);
    camera->curYaw = atan2(camera->lookAt_eye.x, camera->lookAt_eye.z, camera->lookAt_obj.x, camera->lookAt_obj.z);
}
