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

    deltaX = (camera->lookAtObjTarget.x - camera->lookAtObj.x) * interpAmtXZ;
    deltaZ = (camera->lookAtObjTarget.z - camera->lookAtObj.z) * interpAmtXZ;

    if (deltaX < -maxDeltaXZ) {
        deltaX = -maxDeltaXZ;
    }
    if (deltaX > maxDeltaXZ) {
        deltaX = maxDeltaXZ;
    }

    camera->lookAtObj.x += deltaX;
    camera->lookAtObj.z += deltaZ;

    pitchAngle = DEG_TO_RAD(camera->curBoomPitch);
    sinPitch = sin_rad(pitchAngle);
    cosPitch = cos_rad(pitchAngle);

    camera->lookAtEye.x = camera->lookAtObj.x;
    camera->lookAtEye.z = camera->lookAtObj.z + (camera->curBoomLength * cosPitch);

    if (!lockPosY) {
        camera->lookAtObj.y += (camera->lookAtObjTarget.y - camera->lookAtObj.y) * 0.125f;
        camera->lookAtEye.y = camera->lookAtObj.y + (camera->curBoomLength * sinPitch);
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
        camera->needsInit = false;
        camera->unusedLeadAmt = 0.0f;
        camera->unusedLeadCounter = 0;
        camera->interpYaw = 0.0f;
        camera->curBoomYaw = 0.0f;
        camera->lookAtObj.x = camera->targetPos.x;
        camera->lookAtObj.y = camera->targetPos.y + camera->targetOffsetY;
        camera->lookAtObj.z = camera->targetPos.z;
        interp_lookat_pos(camera, 0.0f, 0.0f, false);
    } else {
        f32 maxInterpSpeed = (gPlayerStatus.curSpeed * 1.5f) + 1.0f;
        f32 interpRate = (gPlayerStatus.curSpeed * 0.05f) + 0.05f;

        camera->lookAtObjTarget.x = camera->targetPos.x + camera->unusedLeadAmt;
        camera->lookAtObjTarget.y = camera->targetPos.y + camera->targetOffsetY;
        camera->lookAtObjTarget.z = camera->targetPos.z;
        update_unused_lead_amt(camera);
        if (camera->moveFlags & CAMERA_MOVE_IGNORE_PLAYER_Y) {
            interp_lookat_pos(camera, interpRate, maxInterpSpeed, true);
        } else {
            interp_lookat_pos(camera, interpRate, maxInterpSpeed, false);
        }
    }

    dx = camera->lookAtObj.x - camera->lookAtEye.x;
    dy = camera->lookAtObj.y - camera->lookAtEye.y;
    dz = camera->lookAtObj.z - camera->lookAtEye.z;
    dr = sqrtf(SQ(dx) + SQ(dz));

    camera->lookAtYaw = -atan2(0.0f, 0.0f, dx, dz);
    camera->lookAtPitch = atan2(0.0f, 0.0f, dy, -dr);
    camera->curYaw = atan2(camera->lookAtEye.x, camera->lookAtEye.z, camera->lookAtObj.x, camera->lookAtObj.z);
}
