#include "common.h"
#include "camera.h"

#define YSCALE (1.0f / 5.0f)
#define LEN_SCALE (100 / CamLengthScale)

// implements CAM_UPDATE_UNUSED_RADIAL
// this camera tracks lookAtObjTarget in a circular region centered on targetPos. the camera does not update
// unless lookAtObjTarget is greater than a minimum distance from targetPos to prevent wild movements.
//
// control parameters:
// dist -- length of the camera boom arm
// pitch -- rising angle of the boom arm, up toward the y-axis
// offsetY -- offset of the base of the boom arm above the target point
// minRadius -- do not update camera if lookAtObjTarget is closer than this distance from targetPos
void update_camera_unused_radial(Camera* camera) {
    f32 yawAngle, sinYaw, cosYaw;
    f32 pitchAngle, sinPitch, cosPitch;
    f32 dx, dy, dz, dr;
    f32 x1, z1, x2, z2;
    f32 dist, angle;

    if (camera->needsInit) {
        camera->needsInit = false;

        x1 = camera->lookAtObjTarget.x;
        z1 = camera->lookAtObjTarget.z;
        x2 = camera->targetPos.x;
        z2 = camera->targetPos.z;

        camera->curBoomPitch = camera->params.radial.pitch;
        camera->curBoomLength = camera->params.radial.dist * LEN_SCALE;
        camera->targetOffsetY = camera->params.radial.offsetY * YSCALE * LEN_SCALE;

        angle = atan2(x1, z1, x2, z2);
        dist = dist2D(x1, z1, x2, z2);
        if (dist >= camera->params.radial.minRadius * LEN_SCALE) {
            camera->curBoomYaw = angle;
        }
        camera->targetBoomYaw = camera->curBoomYaw;

        camera->lookAtObj.x = camera->lookAtObjTarget.x;
        camera->lookAtObj.y = camera->lookAtObjTarget.y + camera->targetOffsetY;
        camera->lookAtObj.z = camera->lookAtObjTarget.z;

        pitchAngle = DEG_TO_RAD(camera->curBoomPitch);
        sinPitch = sin_rad(pitchAngle);
        cosPitch = cos_rad(pitchAngle);

        yawAngle = DEG_TO_RAD(angle);
        sinYaw = sin_rad(yawAngle);
        cosYaw = cos_rad(yawAngle);

        dy = camera->curBoomLength * sinPitch;
        dx = camera->curBoomLength * cosPitch * -sinYaw;
        dz = camera->curBoomLength * cosPitch * cosYaw;

        camera->lookAtEye.x = camera->lookAtObj.x + dx;
        camera->lookAtEye.y = camera->lookAtObj.y + dy;
        camera->lookAtEye.z = camera->lookAtObj.z + dz;
    }

    camera->curBoomPitch = camera->params.radial.pitch;
    camera->curBoomLength = camera->params.radial.dist * LEN_SCALE;
    camera->targetOffsetY = camera->params.radial.offsetY * YSCALE * LEN_SCALE;

    dx = camera->lookAtObjTarget.x - camera->lookAtObj.x;
    dy = camera->lookAtObjTarget.y - camera->lookAtObj.y + camera->targetOffsetY;
    dz = camera->lookAtObjTarget.z - camera->lookAtObj.z;

    camera->lookAtObj.x += dx * 0.5f;
    camera->lookAtObj.y += dy * YSCALE * 0.5f;
    camera->lookAtObj.z += dz * 0.5f;

    x1 = camera->lookAtObjTarget.x;
    z1 = camera->lookAtObjTarget.z;
    x2 = camera->targetPos.x;
    z2 = camera->targetPos.z;

    angle = atan2(x1, z1, x2, z2);
    dist = dist2D(x1, z1, x2, z2);
    if (dist >= camera->params.radial.minRadius * LEN_SCALE) {
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

    camera->lookAtEye.x = camera->lookAtObj.x + dx;
    camera->lookAtEye.y = camera->lookAtObj.y + dy;
    camera->lookAtEye.z = camera->lookAtObj.z + dz;

    dx = camera->lookAtObj.x - camera->lookAtEye.x;
    dy = camera->lookAtObj.y - camera->lookAtEye.y;
    dz = camera->lookAtObj.z - camera->lookAtEye.z;
    dr = sqrtf(SQ(dx) + SQ(dz));

    camera->lookAtYaw = -atan2(0.0f, 0.0f, dx, dz);
    camera->lookAtPitch = atan2(0.0f, 0.0f, dy, -dr);
    camera->curYaw = atan2(camera->lookAtEye.x, camera->lookAtEye.z, camera->lookAtObj.x, camera->lookAtObj.z);
}
