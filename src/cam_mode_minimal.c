#include "common.h"
#include "camera.h"

// implements CAM_UPDATE_MINIMAL
// simple camera based on lookAtEye and lookAtObj with no blending or interpolation
// control this camera by directly setting these positions
//
// no control parameters
void update_camera_minimal(Camera* camera) {
    f32 dx, dy, dz, dr;

    if (camera->needsInit) {
        camera->needsInit = false;

        camera->lookAtObj.x = 0.0f;
        camera->lookAtObj.y = 0.0f;
        camera->lookAtObj.z = 0.0f;

        camera->lookAtEye.x = camera->lookAtObj.x;
        camera->lookAtEye.y = camera->lookAtObj.y;
        camera->lookAtEye.z = camera->lookAtObj.z - (1000.0f / CamLengthScale);
    }

    dx = camera->lookAtObj.x - camera->lookAtEye.x;
    dy = camera->lookAtObj.y - camera->lookAtEye.y;
    dz = camera->lookAtObj.z - camera->lookAtEye.z;
    dr = sqrtf(SQ(dx) + SQ(dz));

    camera->lookAtYaw = -atan2(0.0f, 0.0f, dx, dz);
    camera->lookAtPitch = atan2(0.0f, 0.0f, dy, -dr);
    camera->curYaw = atan2(camera->lookAtEye.x, camera->lookAtEye.z, camera->lookAtObj.x, camera->lookAtObj.z);
}
