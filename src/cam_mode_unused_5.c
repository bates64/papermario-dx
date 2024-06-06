#include "common.h"

void func_8003034C(Camera* camera) {
    if (fabsf(get_clamped_angle_diff(gPlayerStatus.curYaw, 90.0f)) < 45.0f) {
        if (camera->unk_556 == 0) {
            if (camera->unk_554 <= 0) {
                camera->unk_550 = 35.0f;
            } else {
                camera->unk_554--;
            }
        } else {
            camera->unk_554 = 15;
            camera->unk_556 = 0;
        }
    } else if (fabsf(get_clamped_angle_diff(gPlayerStatus.curYaw, 270.0f)) < 45.0f) {
        if (camera->unk_556 == 1) {
            if (camera->unk_554 <= 0) {
                camera->unk_550 = -35.0f;
            } else {
                camera->unk_554--;
            }
        } else {
            camera->unk_554 = 15;
            camera->unk_556 = 1;
        }
    }
}

void cam_interp_lookat_pos(Camera* camera, f32 interpAmtXZ, f32 maxDeltaXZ, s16 lockPosY) {
    f32 pitchAngle, sinPitch, cosPitch;
    f32 deltaX, deltaZ;

    deltaX = (camera->lookAt_obj_target.x - camera->lookAt_obj.x) * interpAmtXZ;
    deltaZ = (camera->lookAt_obj_target.z - camera->lookAt_obj.z) * interpAmtXZ;

    if (deltaX < -maxDeltaXZ) {
        deltaX = -maxDeltaXZ;
    }
    if (deltaX > maxDeltaXZ) {
        deltaX = maxDeltaXZ;
    }

    camera->lookAt_obj.x += deltaX;
    camera->lookAt_obj.z += deltaZ;

    pitchAngle = DEG_TO_RAD(camera->curBoomPitch);
    sinPitch = sin_rad(pitchAngle);
    cosPitch = cos_rad(pitchAngle);

    camera->lookAt_eye.x = camera->lookAt_obj.x;
    camera->lookAt_eye.z = camera->lookAt_obj.z + (camera->curBoomLength * cosPitch);

    if (!lockPosY) {
        camera->lookAt_obj.y += (camera->lookAt_obj_target.y - camera->lookAt_obj.y) * 0.125f;
        camera->lookAt_eye.y = camera->lookAt_obj.y + (camera->curBoomLength * sinPitch);
    }
}

// implementation for CAM_UPDATE_UNUSED_5
void update_camera_mode_5(Camera* camera) {
    f32 dx, dy, dz, dr;

    camera->curBoomPitch = 18.0f;
    camera->curBoomLength = 690.0f;
    camera->curYOffset = 47.0f;

    if (camera->needsInit) {
        camera->unk_550 = 0.0f;
        camera->unk_70 = 0.0f;
        camera->curBoomYaw = 0.0f;
        camera->needsInit = FALSE;
        camera->unk_554 = 0;
        camera->lookAt_obj.x = camera->targetPos.x;
        camera->lookAt_obj.y = camera->targetPos.y + camera->curYOffset;
        camera->lookAt_obj.z = camera->targetPos.z;
        cam_interp_lookat_pos(camera, 0.0f, 0.0f, FALSE);
    } else {
        f32 maxInterpSpeed = (gPlayerStatus.curSpeed * 1.5f) + 1.0f;
        f32 interpRate = (gPlayerStatus.curSpeed * 0.05f) + 0.05f;

        camera->lookAt_obj_target.x = camera->targetPos.x + camera->unk_550;
        camera->lookAt_obj_target.y = camera->targetPos.y + camera->curYOffset;
        camera->lookAt_obj_target.z = camera->targetPos.z;
        func_8003034C(camera);
        if (!(camera->moveFlags & CAMERA_MOVE_IGNORE_PLAYER_Y)) {
            cam_interp_lookat_pos(camera, interpRate, maxInterpSpeed, FALSE);
        } else {
            cam_interp_lookat_pos(camera, interpRate, maxInterpSpeed, TRUE);
        }
    }

    dx = camera->lookAt_obj.x - camera->lookAt_eye.x;
    dy = camera->lookAt_obj.y - camera->lookAt_eye.y;
    dz = camera->lookAt_obj.z - camera->lookAt_eye.z;
    dr = sqrtf(SQ(dx) + SQ(dz));

    camera->lookAt_yaw = -atan2(0.0f, 0.0f, dx, dz);
    camera->curPitch = atan2(0.0f, 0.0f, dy, -dr);
    camera->curYaw = atan2(camera->lookAt_eye.x, camera->lookAt_eye.z, camera->lookAt_obj.x, camera->lookAt_obj.z);
}

