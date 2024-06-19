#include "common.h"
#include "camera.h"

#define YSCALE (1.0f / 5.0f)
#define LEN_SCALE (100 / CamLengthScale)

// implements CAM_UPDATE_UNUSED_RADIAL
// this camera tracks lookAt_obj_target in a circular region centered on targetPos. the camera does not update
// unless lookAt_obj_target is greater than a minimum distance from targetPos to prevent wild movements.
void update_camera_unused_radial(Camera* camera) {
    f32 yawAngle, sinYaw, cosYaw;
    f32 pitchAngle, sinPitch, cosPitch;
    f32 dx, dy, dz, dr;
    f32 x1, z1, x2, z2;
    f32 dist, angle;

    if (camera->needsInit) {
        camera->needsInit = FALSE;

        x1 = camera->lookAt_obj_target.x;
        z1 = camera->lookAt_obj_target.z;
        x2 = camera->targetPos.x;
        z2 = camera->targetPos.z;

        camera->curBoomPitch = camera->params.radial.auxPitch;
        camera->curBoomLength = camera->params.radial.auxBoomLength * LEN_SCALE;
        camera->targetOffsetY = camera->params.radial.offsetY * YSCALE * LEN_SCALE;

        angle = atan2(x1, z1, x2, z2);
        dist = dist2D(x1, z1, x2, z2);
        if (dist >= camera->params.radial.auxDistThreshold * LEN_SCALE) {
            camera->curBoomYaw = angle;
        }
        camera->targetBoomYaw = camera->curBoomYaw;

        camera->lookAt_obj.x = camera->lookAt_obj_target.x;
        camera->lookAt_obj.y = camera->lookAt_obj_target.y + camera->targetOffsetY;
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

    camera->curBoomPitch = camera->params.radial.auxPitch;
    camera->curBoomLength = camera->params.radial.auxBoomLength * LEN_SCALE;
    camera->targetOffsetY = camera->params.radial.offsetY * YSCALE * LEN_SCALE;

    dx = camera->lookAt_obj_target.x - camera->lookAt_obj.x;
    dy = camera->lookAt_obj_target.y - camera->lookAt_obj.y + camera->targetOffsetY;
    dz = camera->lookAt_obj_target.z - camera->lookAt_obj.z;

    camera->lookAt_obj.x += dx * 0.5f;
    camera->lookAt_obj.y += dy * YSCALE * 0.5f;
    camera->lookAt_obj.z += dz * 0.5f;

    x1 = camera->lookAt_obj_target.x;
    z1 = camera->lookAt_obj_target.z;
    x2 = camera->targetPos.x;
    z2 = camera->targetPos.z;

    angle = atan2(x1, z1, x2, z2);
    dist = dist2D(x1, z1, x2, z2);
    if (dist >= camera->params.radial.auxDistThreshold * LEN_SCALE) {
        camera->curBoomYaw = angle;
    }
    camera->targetBoomYaw -= get_clamped_angle_diff(camera->curBoomYaw, camera->targetBoomYaw) / 10.0f;

    pitchAngle = DEG_TO_RAD(camera->curBoomPitch);
    sinPitch = sin_rad(pitchAngle);
    cosPitch = cos_rad(pitchAngle);

    yawAngle = DEG_TO_RAD((camera->targetBoomYaw));
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
