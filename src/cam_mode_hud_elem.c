#include "common.h"
#include "camera.h"

// implementation for CAM_UPDATE_HUD_ELEM
void update_camera_hud_elem(Camera *camera) {
    f32 pitchAngle, sinPitch, cosPitch;
    f32 yawAngle, sinYaw, cosYaw;
    f32 x, y, z, dx, dy, dz, dr;

    camera->unk_70 = camera->auxBoomLength;
    camera->curBoomLength = camera->lookAt_dist * D_8009A5EC;
    camera->targetOffsetY = camera->auxBoomPitch * D_8009A5EC;
    camera->curBoomPitch = camera->auxPitch;
    camera->curBoomYaw = camera->unk_70;

    if (camera->needsInit) {
        camera->needsInit = FALSE;

        camera->lookAt_obj.x = camera->lookAt_obj_target.x;
        camera->lookAt_obj.y = camera->lookAt_obj_target.y + camera->targetOffsetY;
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

    dx = camera->lookAt_obj_target.x - camera->lookAt_obj.x;
    dy = camera->lookAt_obj_target.y - camera->lookAt_obj.y + camera->targetOffsetY;
    dz = camera->lookAt_obj_target.z - camera->lookAt_obj.z;

    if (fabsf(dx) > 16.0f) {
        if (dx < 0.0f) {
            dx = -16.0f;
        } else {
            dx = 16.0f;
        }
    }
    if (fabsf(dy) > 16.0f) {
        if (dy < 0.0f) {
            dy = -16.0f;
        } else {
            dy = 16.0f;
        }
    }
    if (fabsf(dz) > 16.0f) {
        if (dz < 0.0f) {
            dz = -16.0f;
        } else {
            dz = 16.0f;
        }
    }

    camera->lookAt_obj.x += dx * 0.5f;
    camera->lookAt_obj.y += dy * 0.5f;
    camera->lookAt_obj.z += dz * 0.5f;

    pitchAngle = DEG_TO_RAD(camera->curBoomPitch);
    sinPitch = sin_rad(pitchAngle);
    cosPitch = cos_rad(pitchAngle);

    yawAngle = DEG_TO_RAD(camera->unk_70);
    sinYaw = sin_rad(yawAngle);
    cosYaw = cos_rad(yawAngle);

    dy = camera->curBoomLength * sinPitch;
    dx = camera->curBoomLength * cosPitch * -sinYaw;
    dz = camera->curBoomLength * cosPitch * cosYaw;

    x = camera->lookAt_obj.x + dx;
    y = camera->lookAt_obj.y + dy;
    z = camera->lookAt_obj.z + dz;

    dx = (x - camera->lookAt_eye.x) * 0.5f;
    dy = (y - camera->lookAt_eye.y) * 0.5f;
    dz = (z - camera->lookAt_eye.z) * 0.5f;

    if (fabsf(dx) > 16.0f) {
        if (dx < 0.0f) {
            dx = -16.0f;
        } else {
            dx = 16.0f;
        }
    }
    if (fabsf(dy) > 16.0f) {
        if (dy < 0.0f) {
            dy = -16.0f;
        } else {
            dy = 16.0f;
        }
    }
    if (fabsf(dz) > 16.0f) {
        if (dz < 0.0f) {
            dz = -16.0f;
        } else {
            dz = 16.0f;
        }
    }

    camera->lookAt_eye.x += dx;
    camera->lookAt_eye.y += dy;
    camera->lookAt_eye.z += dz;

    dx = camera->lookAt_obj.x - camera->lookAt_eye.x;
    dy = camera->lookAt_obj.y - camera->lookAt_eye.y;
    dz = camera->lookAt_obj.z - camera->lookAt_eye.z;
    dr = sqrtf(SQ(dx) + SQ(dz));

    camera->lookAt_yaw = -atan2(0.0f, 0.0f, dx, dz);
    camera->lookAt_pitch = atan2(0.0f, 0.0f, dy, -dr);
    camera->curYaw = atan2(camera->lookAt_eye.x, camera->lookAt_eye.z, camera->lookAt_obj.x, camera->lookAt_obj.z);
}
