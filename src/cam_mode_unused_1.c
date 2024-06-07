#include "common.h"
#include "camera.h"

// implementation for CAM_UPDATE_UNUSED_1
void update_camera_mode_1(Camera* camera) {
    f32 yawAngle, sinYaw, cosYaw;
    f32 pitchAngle, sinPitch, cosPitch;
    f32 dx, dy, dz, dr;
    f32 x0, x1, z0, z1;
    f32 angle;

    if (camera->needsInit) {
        camera->needsInit = FALSE;

        x0 = camera->lookAt_obj_target.x;
        z0 = camera->lookAt_obj_target.z;
        x1 = camera->targetPos.x;
        z1 = camera->targetPos.z;

        camera->curBoomPitch = camera->auxPitch;
        camera->curBoomLength = camera->lookAt_dist * 100 / D_8009A5EC;
        camera->curYOffset = camera->auxBoomPitch * 20 / D_8009A5EC;

        angle = atan2(x0, z0, x1, z1);
        if ((dist2D(x0, z0, x1, z1) >= camera->auxBoomLength * 100 / D_8009A5EC)) {
            camera->curBoomYaw = angle;
        }
        camera->unk_88 = camera->curBoomYaw;

        camera->lookAt_obj.x = camera->lookAt_obj_target.x;
        camera->lookAt_obj.y = camera->lookAt_obj_target.y + camera->curYOffset;
        camera->lookAt_obj.z = camera->lookAt_obj_target.z;

        pitchAngle = DEG_TO_RAD(camera->curBoomPitch);
        sinPitch = sin_rad(pitchAngle);
        cosPitch = cos_rad(pitchAngle);

        yawAngle = DEG_TO_RAD(angle);
        sinYaw = sin_rad(yawAngle);
        cosYaw = cos_rad(yawAngle);

        dy = camera->curBoomLength * sinPitch;
        dx = camera->curBoomLength * cosPitch * -sinYaw;
        dz = camera->curBoomLength * cosPitch * cosYaw;

        camera->lookAt_eye.x = camera->lookAt_obj.x + dx;
        camera->lookAt_eye.y = camera->lookAt_obj.y + dy;
        camera->lookAt_eye.z = camera->lookAt_obj.z + dz;
    }

    camera->curBoomPitch = camera->auxPitch;
    camera->curBoomLength = camera->lookAt_dist * 100 / D_8009A5EC;
    camera->curYOffset = camera->auxBoomPitch * 20 / D_8009A5EC;

    dx = camera->lookAt_obj_target.x - camera->lookAt_obj.x;
    dy = camera->lookAt_obj_target.y - camera->lookAt_obj.y + camera->curYOffset;
    dz = camera->lookAt_obj_target.z - camera->lookAt_obj.z;

    camera->lookAt_obj.x += dx * 0.5f;
    camera->lookAt_obj.y += dy / 10.0f;
    camera->lookAt_obj.z += dz * 0.5f;

    x0 = camera->lookAt_obj_target.x;
    z0 = camera->lookAt_obj_target.z;
    x1 = camera->targetPos.x;
    z1 = camera->targetPos.z;

    angle = atan2(x0, z0, x1, z1);
    if ((dist2D(x0, z0, x1, z1) >= camera->auxBoomLength * 100 / D_8009A5EC)) {
        camera->curBoomYaw = angle;
    }
    camera->unk_88 -= get_clamped_angle_diff(camera->curBoomYaw, camera->unk_88) / 10.0f;

    pitchAngle = DEG_TO_RAD(camera->curBoomPitch);
    sinPitch = sin_rad(pitchAngle);
    cosPitch = cos_rad(pitchAngle);

    yawAngle = DEG_TO_RAD((camera->unk_88));
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
