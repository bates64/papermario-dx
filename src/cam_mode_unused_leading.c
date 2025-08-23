#include "common.h"

void update_unused_lead_amt(Camera* camera) {
    // moving left? (along +x axis)
    if (fabsf(get_clamped_angle_diff(gPlayerStatus.curYaw, 90.0f)) < 45.0f) {
        if (camera->unusedLeadDir == 0) {
            if (camera->unusedLeadCounter <= 0) {
                camera->unusedLeadAmt = 35.0f;
            } else {
                camera->unusedLeadCounter--;
            }
        } else {
            camera->unusedLeadCounter = 15;
            camera->unusedLeadDir = 0;
        }
    // moving right? (along -x axis)
    } else if (fabsf(get_clamped_angle_diff(gPlayerStatus.curYaw, 270.0f)) < 45.0f) {
        if (camera->unusedLeadDir == 1) {
            if (camera->unusedLeadCounter <= 0) {
                camera->unusedLeadAmt = -35.0f;
            } else {
                camera->unusedLeadCounter--;
            }
        } else {
            camera->unusedLeadCounter = 15;
            camera->unusedLeadDir = 1;
        }
    }
}

void interp_lookat_pos(Camera* camera, f32 interpAmtXZ, f32 maxDeltaXZ, s16 lockPosY) {
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

// implements CAM_UPDATE_UNUSED_LEADING
// this camera tracks player position and adds basic 'leading' in the x-direction only
// camera yaw is fixed at zero and the lead direction is determined by player world yaw
// thus, this only works for '2D' style maps where left is -x and right is +x
//
// no control parameters
void update_camera_unused_leading(Camera* camera) {
    f32 dx, dy, dz, dr;

    camera->curBoomPitch = 18.0f;
    camera->curBoomLength = 690.0f;
    camera->targetOffsetY = 47.0f;

    if (camera->needsInit) {
        camera->needsInit = FALSE;
        camera->unusedLeadAmt = 0.0f;
        camera->unusedLeadCounter = 0;
        camera->interpYaw = 0.0f;
        camera->curBoomYaw = 0.0f;
        camera->needsInit = false;
        camera->unusedLeadCounter = 0;
        camera->lookAt_obj.x = camera->targetPos.x;
        camera->lookAt_obj.y = camera->targetPos.y + camera->targetOffsetY;
        camera->lookAt_obj.z = camera->targetPos.z;
        interp_lookat_pos(camera, 0.0f, 0.0f, false);
    } else {
        f32 maxInterpSpeed = (gPlayerStatus.curSpeed * 1.5f) + 1.0f;
        f32 interpRate = (gPlayerStatus.curSpeed * 0.05f) + 0.05f;

        camera->lookAt_obj_target.x = camera->targetPos.x + camera->unusedLeadAmt;
        camera->lookAt_obj_target.y = camera->targetPos.y + camera->targetOffsetY;
        camera->lookAt_obj_target.z = camera->targetPos.z;
        update_unused_lead_amt(camera);
        if (!(camera->moveFlags & CAMERA_MOVE_IGNORE_PLAYER_Y)) {
            interp_lookat_pos(camera, interpRate, maxInterpSpeed, false);
        } else {
            lookXDelta = maxInterpSpeed; // needed to match

            interp_lookat_pos(camera, interpRate, lookXDelta, true);
        }
    }

    dx = camera->lookAt_obj.x - camera->lookAt_eye.x;
    dy = camera->lookAt_obj.y - camera->lookAt_eye.y;
    dz = camera->lookAt_obj.z - camera->lookAt_eye.z;
    dr = sqrtf(SQ(dx) + SQ(dz));

    camera->lookAt_yaw = -atan2(0.0f, 0.0f, dx, dz);
    camera->lookAt_pitch = atan2(0.0f, 0.0f, dy, -dr);
    camera->curYaw = atan2(camera->lookAt_eye.x, camera->lookAt_eye.z, camera->lookAt_obj.x, camera->lookAt_obj.z);
}

