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
    if (targetX > camera->confined.xLimit) {
        targetX = camera->confined.xLimit;
    }
    if (targetX < -camera->confined.xLimit) {
        targetX = -camera->confined.xLimit;
    }
    camera->lookAt_obj_target.x = targetX;

    targetZ = camera->targetPos.z;
    if (targetZ > camera->confined.zLimit) {
        targetZ = camera->confined.zLimit;
    }
    if (targetZ < -camera->confined.zLimit) {
        targetZ = -camera->confined.zLimit;
    }
    camera->lookAt_obj_target.z = targetZ;

    camera->interpYaw = 0.0f;
    camera->curBoomPitch = 0.0f;
    camera->curBoomYaw = 0.0f;
    camera->curBoomLength = camera->confined.auxBoomLength * D_8009A5EC;
    camera->targetOffsetY = camera->confined.offsetY * D_8009A5EC;

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
