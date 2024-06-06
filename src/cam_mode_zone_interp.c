#include "common.h"
#include "dx/debug_menu.h"

BSS CamConfiguration gCurrentCamConfiguration;
BSS f32 D_800A08DC;
BSS f32 D_800A08E0;
BSS f32 D_800A08E4;
BSS f32 D_800A08E8;
BSS f32 D_800A08EC;

CameraControlSettings* test_ray_zone_aabb(f32 x, f32 y, f32 z) {
    f32 hitX, hitY, hitZ;
    f32 hitDepth = 32767.0f;
    f32 nx, ny, nz;
    s32 zoneID = test_ray_zones(x, y, z, 0.0f, -1.0f, 0.0f, &hitX, &hitY, &hitZ, &hitDepth, &nx, &ny, &nz);

    if (zoneID < 0) {
        return NULL;
    }

    return gZoneCollisionData.colliderList[zoneID].camSettings;
}

enum CameraSettingsPtrType {
    CAMERA_SETTINGS_PTR_MINUS_2     = -2,
    CAMERA_SETTINGS_PTR_MINUS_1     = -1,
    CAMERA_SETTINGS_PTR_NULL        = 0,
};

void apply_fixed_orientation(CameraControlSettings* controller, CamConfiguration* configuration, f32 x, f32 y, f32 z)
{
    f32 Ax = controller->points.two.Ax;
    f32 Az = controller->points.two.Az;
    f32 Bx = controller->points.two.Bx;
    f32 Bz = controller->points.two.Bz;

    f32 ABx = (Bx - Ax);
    f32 ABz = (Bz - Az);

    if (controller->flag) {
        f32 perpdot = ABx * (z - Bz) - ABz * (x - Bx);
        f32 dist2 = SQ(ABx) + SQ(ABz);

        // only move camera along the line perpendicular to AB passing through B
        configuration->targetPos.x = Bx - ABz * (perpdot / dist2);
        configuration->targetPos.y = y;
        configuration->targetPos.z = Bz + ABx * (perpdot / dist2);
    } else {
        configuration->targetPos.x = x;
        configuration->targetPos.y = y;
        configuration->targetPos.z = z;
    }
}

void update_camera_from_controller(
    Camera* camera,
    CamConfiguration* oldConfiguration, CameraControlSettings** prevController,
    CamConfiguration* newConfiguration, CameraControlSettings** newController,
    f32 x1, f32 y1, f32 z1,
    f32 tX, f32 tY, f32 tZ, b32 changingMap,
    f32* interpAlpha, b32 changingZone)
{
    CameraControlSettings* prevSettings;
    CameraControlSettings* curSettings;
    CamConfiguration* configuration;
    f32 dx, dz;
    f32 x, y, z;

    configuration = oldConfiguration;
    curSettings = *prevController;
    x = x1;
    y = y1;
    z = z1;

    if ((s32)curSettings != CAMERA_SETTINGS_PTR_MINUS_2 && (s32)curSettings != CAMERA_SETTINGS_PTR_MINUS_1) {
        if (curSettings == CAMERA_SETTINGS_PTR_NULL) {
            configuration->targetPos.x = x;
            configuration->targetPos.y = y;
            configuration->targetPos.z = z;
        } else {
            switch (curSettings->type) {
                case CAM_CONTROL_FOLLOW_PLAYER:
                    configuration->targetPos.x = x;
                    configuration->targetPos.y = y;
                    configuration->targetPos.z = z;
                    break;
                case CAM_CONTROL_FIXED_POS_AND_ORIENTATION:
                    break;
                case CAM_CONTROL_FIXED_ORIENTATION:
                    if (curSettings->flag) {
                        f32 Ax = curSettings->points.two.Ax;
                        f32 Az = curSettings->points.two.Az;
                        f32 Bx = curSettings->points.two.Bx;
                        f32 Bz = curSettings->points.two.Bz;

                        f32 ABx = (Bx - Ax);
                        f32 ABz = (Bz - Az);

                        f32 perpdot = ABx * (z - Bz) - ABz * (x - Bx);
                        f32 dist2 = SQ(ABx) + SQ(ABz);

                        // only move camera along the line perpendicular to AB passing through B
                        configuration->targetPos.x = Bx - ABz * (perpdot / dist2);
                        configuration->targetPos.y = y;
                        configuration->targetPos.z = Bz + ABx * (perpdot / dist2);
                    } else {
                        configuration->targetPos.x = x;
                        configuration->targetPos.y = y;
                        configuration->targetPos.z = z;
                    }
                    break;
                case CAM_CONTROL_CONSTAIN_BETWEEN_POINTS:
                    {
                        f32 Ax = curSettings->points.two.Ax;
                        f32 Az = curSettings->points.two.Az;
                        f32 Bx = curSettings->points.two.Bx;
                        f32 Bz = curSettings->points.two.Bz;

                        f32 ABx = Bx - Ax;
                        f32 ABz = Bz - Az;

                        // project point onto line
                        f32 t = (ABx * (x - Ax) + ABz * (z - Az)) / (SQ(ABx) + SQ(ABz));
                        f32 Px = Ax + t * ABx;
                        f32 Pz = Az + t * ABz;

                        // vector giving orthogonal part (i.e., x = orthoX + Px)
                        f32 orthoX = x - Px;
                        f32 orthoZ = z - Pz;

                        // clamp to end points
                        if (t < 0.0f) {
                            Px = Ax;
                            Pz = Az;
                        } else if (t > 1.0f) {
                            Px = Bx;
                            Pz = Bz;
                        }
                        if (!curSettings->flag) {
                            Px += orthoX;
                            Pz += orthoZ;
                        }

                        configuration->targetPos.x = Px;
                        configuration->targetPos.y = y;
                        configuration->targetPos.z = Pz;
                    }
                    break;
                case CAM_CONTROL_LOOK_AT_POINT:
                    if (curSettings->flag) {
                        f32 Ax = curSettings->points.two.Ax;
                        f32 Az = curSettings->points.two.Az;
                        f32 Bx = curSettings->points.two.Bx;
                        f32 Bz = curSettings->points.two.Bz;

                        f32 ABx = Bx - Ax;
                        f32 ABz = Bz - Az;
                        f32 camRadius = sqrtf(SQ(ABx) + SQ(ABz));

                        // find radius of a circle containing the sample point centered on point A
                        f32 dx = x - Ax;
                        f32 dz = z - Az;
                        f32 curRadius = sqrtf(SQ(dx) + SQ(dz));

                        if (curRadius != 0.0f) {
                            // rescale the radius to equal the length of segment AB
                            configuration->targetPos.x = Ax + dx * (camRadius / curRadius);
                            configuration->targetPos.y = y;
                            configuration->targetPos.z = Az + dz * (camRadius / curRadius);
                        }
                    } else {
                        configuration->targetPos.x = x;
                        configuration->targetPos.y = y;
                        configuration->targetPos.z = z;
                    }
                    break;
                case CAM_CONTROL_CONSTRAIN_TO_LINE:
                case CAM_CONTROL_LOOK_AT_POINT_CONSTAIN_TO_LINE:
                    *prevController = (CameraControlSettings*) CAMERA_SETTINGS_PTR_MINUS_1;
                    break;
            }
        }
    }

    configuration = newConfiguration;
    curSettings = *newController;
    x = tX;
    y = tY;
    z = tZ;

    if (curSettings == NULL) {
        configuration->targetPos.x = x;
        configuration->targetPos.y = y;
        configuration->targetPos.z = z;
    } else {
        switch (curSettings->type) {
            case CAM_CONTROL_FOLLOW_PLAYER:
                configuration->targetPos.x = x;
                configuration->targetPos.y = y;
                configuration->targetPos.z = z;
                break;
            case CAM_CONTROL_FIXED_POS_AND_ORIENTATION:
                {
                    f32 Ax = curSettings->points.two.Ax;
                    f32 Az = curSettings->points.two.Az;
                    f32 Bx = curSettings->points.two.Bx;
                    f32 By = curSettings->points.two.By;
                    f32 Bz = curSettings->points.two.Bz;

                    f32 ABx = Bx - Ax;
                    f32 ABz = Bz - Az;

                    configuration->boomLength = fabsf(curSettings->boomLength);
                    configuration->boomYaw = atan2(0.0f, 0.0f, ABx, ABz);
                    configuration->boomPitch = curSettings->boomPitch;
                    configuration->viewPitch = curSettings->viewPitch;
                    configuration->targetPos.x = Bx;
                    configuration->targetPos.y = By;
                    configuration->targetPos.z = Bz;
                    *prevController = (CameraControlSettings*) CAMERA_SETTINGS_PTR_MINUS_2;
                }
                break;
            case CAM_CONTROL_FIXED_ORIENTATION:
                dx = curSettings->points.two.Bx - curSettings->points.two.Ax;
                dz = curSettings->points.two.Bz - curSettings->points.two.Az;
                configuration->boomLength = fabsf(curSettings->boomLength);
                configuration->boomYaw = atan2(0.0f, 0.0f, dx, dz);
                configuration->boomPitch = curSettings->boomPitch;
                configuration->viewPitch = curSettings->viewPitch;

                if (curSettings->flag) {
                    f32 Ax = curSettings->points.two.Ax;
                    f32 Az = curSettings->points.two.Az;
                    f32 Bx = curSettings->points.two.Bx;
                    f32 Bz = curSettings->points.two.Bz;

                    f32 ABx = Bx - Ax;
                    f32 ABz = Bz - Az;

                    f32 perpdot = ABx * (z - Bz) - ABz * (x - Bx);
                    f32 dist2 = SQ(ABx) + SQ(ABz);

                    // only move camera along the line perpendicular to AB passing through B
                    configuration->targetPos.x = Bx - ABz * (perpdot / dist2);
                    configuration->targetPos.y = y;
                    configuration->targetPos.z = Bz + ABx * (perpdot / dist2);
                } else {
                    configuration->targetPos.x = x;
                    configuration->targetPos.y = y;
                    configuration->targetPos.z = z;
                }

                if (changingZone) {
                    if (*interpAlpha != 1.0f) {
                        prevSettings = *prevController;
                        if (((s32)prevSettings != CAMERA_SETTINGS_PTR_MINUS_2
                                && (s32)prevSettings != CAMERA_SETTINGS_PTR_MINUS_1
                                && (s32)prevSettings != CAMERA_SETTINGS_PTR_NULL)
                            && prevSettings->type == curSettings->type
                            && prevSettings->boomLength == curSettings->boomLength
                            && prevSettings->boomPitch == curSettings->boomPitch
                            && prevSettings->viewPitch == curSettings->viewPitch
                            && prevSettings->flag != curSettings->flag
                        ) {
                            *interpAlpha = 1.0f;
                        }
                    }
                }
                break;
            case CAM_CONTROL_CONSTAIN_BETWEEN_POINTS:
                {
                    f32 Ax = curSettings->points.two.Ax;
                    f32 Az = curSettings->points.two.Az;
                    f32 Bx = curSettings->points.two.Bx;
                    f32 Bz = curSettings->points.two.Bz;

                    f32 ABx = Bx - Ax;
                    f32 ABz = Bz - Az;

                    configuration->boomLength = fabsf(curSettings->boomLength);
                    configuration->boomYaw = atan2(0.0f, 0.0f, ABz, -ABx);
                    configuration->boomPitch = curSettings->boomPitch;
                    configuration->viewPitch = curSettings->viewPitch;

                    // project point onto line
                    f32 t = (ABx * (x - Ax) + ABz * (z - Az)) / (SQ(ABx) + SQ(ABz));
                    f32 Px = Ax + t * ABx;
			        f32 Pz = Az + t * ABz;

                    // vector giving orthogonal part (i.e., x = orthoX + Px)
                    f32 orthoX = x - Px;
                    f32 orthoZ = z - Pz;

                    // clamp to end points
                    if (t < 0.0f) {
                        Px = Ax;
                        Pz = Az;
                    } else if (t > 1.0f) {
                        Px = Bx;
                        Pz = Bz;
                    }
                    if (!curSettings->flag) {
                        Px += orthoX;
                        Pz += orthoZ;
                    }

                    configuration->targetPos.x = Px;
                    configuration->targetPos.y = y;
                    configuration->targetPos.z = Pz;

                    if (changingZone) {
                        if (*interpAlpha != 1.0f) {
                            prevSettings = *prevController;
                            if (((s32)prevSettings != CAMERA_SETTINGS_PTR_MINUS_2
                                    && (s32)prevSettings != CAMERA_SETTINGS_PTR_MINUS_1
                                    && (s32)prevSettings != CAMERA_SETTINGS_PTR_NULL)
                                && (prevSettings->type == curSettings->type)
                                && (prevSettings->boomLength == curSettings->boomLength)
                                && (prevSettings->boomPitch == curSettings->boomPitch)
                                && (prevSettings->viewPitch == curSettings->viewPitch)
                                && (prevSettings->flag != curSettings->flag)
                            ) {
                                *interpAlpha = 1.0f;
                            }
                        }
                    }
                }
                break;
            case CAM_CONTROL_LOOK_AT_POINT:
                {
                    f32 Ax = curSettings->points.two.Ax;
                    f32 Az = curSettings->points.two.Az;
                    f32 Bx = curSettings->points.two.Bx;
                    f32 Bz = curSettings->points.two.Bz;

                    f32 ABx = Bx - Ax;
                    f32 ABz = Bz - Az;
                    f32 camRadius = sqrtf(SQ(ABx) + SQ(ABz));
                    f32 curRadius, dx, dz;

                    if (curSettings->boomLength < 0.0f) {
                        // negative boom length means look *away* from point
                        dx = x - Ax;
                        dz = z - Az;
                        configuration->boomLength = -curSettings->boomLength;
                    } else {
                        dx = Ax - x;
                        dz = Az - z;
                        configuration->boomLength = curSettings->boomLength;
                    }
                    configuration->boomYaw = atan2(0.0f, 0.0f, dx, dz);
                    configuration->boomPitch = curSettings->boomPitch;
                    configuration->viewPitch = curSettings->viewPitch;

                    if (curSettings->flag) {
                        // find radius of a circle containing the sample point centered on point A
                        dx = x - Ax;
                        dz = z - Az;
                        curRadius = sqrtf(SQ(dx) + SQ(dz));

                        if (curRadius != 0.0f) {
                            // rescale the radius to equal the length of segment AB
                            configuration->targetPos.x = Ax + dx * (camRadius / curRadius);
                            configuration->targetPos.y = y;
                            configuration->targetPos.z = Az + dz * (camRadius / curRadius);
                        }
                    } else {
                        configuration->targetPos.x = x;
                        configuration->targetPos.y = y;
                        configuration->targetPos.z = z;
                    }

                    if (changingZone) {
                        if (*interpAlpha != 1.0f) {
                            prevSettings = *prevController;
                            if (((s32)prevSettings != CAMERA_SETTINGS_PTR_MINUS_2
                                    && (s32)prevSettings != CAMERA_SETTINGS_PTR_MINUS_1
                                    && (s32)prevSettings != CAMERA_SETTINGS_PTR_NULL)
                                && (prevSettings->type == curSettings->type)
                                && (prevSettings->boomLength == curSettings->boomLength)
                                && (prevSettings->boomPitch == curSettings->boomPitch)
                                && (prevSettings->viewPitch == curSettings->viewPitch)
                                && (prevSettings->flag != curSettings->flag)
                                && (prevSettings->points.two.Ax == curSettings->points.two.Ax)
                                && (prevSettings->points.two.Az == curSettings->points.two.Az)
                            ) {
                                *interpAlpha = 1.0f;
                            }
                        }
                    }
                }
                break;
            case CAM_CONTROL_CONSTRAIN_TO_LINE:
                {
                    f32 Ax = curSettings->points.three.Ax;
                    f32 Az = curSettings->points.three.Az;
                    f32 Bx = curSettings->points.three.Bx;
                    f32 Bz = curSettings->points.three.Bz;
                    f32 Cx = curSettings->points.three.Cx;
                    f32 Cz = curSettings->points.three.Cz;

                    if (!curSettings->flag) {
                        f32 Tx, Tz;

                        if (Ax == Bx && Az == Bz) {
                            Ax = Cx;
                            Az = Cz;
                        }

                        f32 ABx = Bx - Ax;
                        f32 BAz = Az - Bz;
                        f32 CBx = Bx - Cx;
                        f32 CBz = Bz - Cz;

                        if (CBx == 0.0f) {
                            f32 Q = CBx * ABx / CBz + BAz;
                            f32 V = (x - Bx) - (z - Bz) * CBx / CBz;

                            Tx = x - BAz * V / Q;
                            Tz = z + ABx * V / Q;
                        } else {
                            f32 Q = BAz * CBz / CBx + ABx;
                            f32 V = (z - Bz) - (x - Bx) * CBz / CBx;

                            Tx = x + BAz * V / Q;
                            Tz = z + ABx * V / Q;
                        }

                        configuration->targetPos.x = Tx;
                        configuration->targetPos.y = y;
                        configuration->targetPos.z = Tz;

                        if (changingMap) {
                            dx = Bx - Ax;
                            dz = Bz - Az;
                            configuration->boomLength = fabsf(curSettings->boomLength);
                            configuration->boomYaw = atan2(0.0f, 0.0f, dx, dz);
                            configuration->boomPitch = curSettings->boomPitch;
                            configuration->viewPitch = curSettings->viewPitch;
                        }
                    } else {
                        if (changingMap) {
                            dx = Bx - Ax;
                            dz = Bz - Az;
                            configuration->boomLength = fabsf(curSettings->boomLength);
                            configuration->boomYaw = atan2(0.0f, 0.0f, dx, dz);
                            configuration->boomPitch = curSettings->boomPitch;
                            configuration->viewPitch = curSettings->viewPitch;
                            configuration->targetPos.x = Bx;
                            configuration->targetPos.y = y;
                            configuration->targetPos.z = Bz;
                        } else if (changingZone) {
                            configuration->targetPos.x = oldConfiguration->targetPos.x;
                            configuration->targetPos.y = y;
                            configuration->targetPos.z = oldConfiguration->targetPos.z;
                        }
                    }
                    *prevController = (CameraControlSettings*) CAMERA_SETTINGS_PTR_MINUS_1;
                }
                break;
            case CAM_CONTROL_LOOK_AT_POINT_CONSTAIN_TO_LINE:
                {
                    // camera position is projected onto a line defined by BC, while the yaw faces point A
                    f32 Ax = curSettings->points.three.Ax;
                    f32 Az = curSettings->points.three.Az;
                    f32 Bx = curSettings->points.three.Bx;
                    f32 Bz = curSettings->points.three.Bz;
                    f32 Cx = curSettings->points.three.Cx;
                    f32 Cz = curSettings->points.three.Cz;

                    if (!curSettings->flag) {
                        f32 CBx = Bx - Cx;
                        f32 CBz = Bz - Cz;
                        f32 dist2 = SQ(CBx) + SQ(CBz);
                        dist2 = (CBx * (x - Cx) + CBz * (z - Cz)) / dist2;
                        f32 Px = Cx + dist2 * CBx;
                        f32 Pz = Cz + dist2 * CBz;

                        configuration->targetPos.x = Px;
                        configuration->targetPos.y = y;
                        configuration->targetPos.z = Pz;

                        if (curSettings->boomLength < 0.0f) {
                            dx = Px - Ax;
                            dz = Pz - Az;
                            configuration->boomLength = -curSettings->boomLength;
                        } else {
                            dx = Ax - Px;
                            dz = Az - Pz;
                            configuration->boomLength = curSettings->boomLength;
                        }
                        configuration->boomYaw = atan2(0.0f, 0.0f, dx, dz);
                        configuration->boomPitch = curSettings->boomPitch;
                        configuration->viewPitch = curSettings->viewPitch;
                    } else {
                        if (changingMap) {
                            if (curSettings->boomLength < 0.0f) {
                                dx = Bx - Ax;
                                dz = Bz - Az;
                                configuration->boomLength = -curSettings->boomLength;
                            } else {
                                dx = Ax - Bx;
                                dz = Az - Bz;
                                configuration->boomLength = curSettings->boomLength;
                            }
                            configuration->boomYaw = atan2(0.0f, 0.0f, dx, dz);
                            configuration->boomPitch = curSettings->boomPitch;
                            configuration->viewPitch = curSettings->viewPitch;
                            configuration->targetPos.x = Bx;
                            configuration->targetPos.y = y;
                            configuration->targetPos.z = Bz;
                        } else if (changingZone) {
                            configuration->targetPos.x = Bx;
                            configuration->targetPos.y = y;
                            configuration->targetPos.z = Bz;
                        }
                    }
                    *prevController = (CameraControlSettings*) CAMERA_SETTINGS_PTR_MINUS_1;
                }
                break;
        }

        if (changingZone
            && ((curSettings->type == CAM_CONTROL_LOOK_AT_POINT_CONSTAIN_TO_LINE) || (oldConfiguration->boomYaw != newConfiguration->boomYaw))
            && (fabsf(oldConfiguration->boomYaw - newConfiguration->boomYaw) < 3.0f)
            && (fabsf(oldConfiguration->boomLength - newConfiguration->boomLength) < 10.0f)
            && (fabsf(oldConfiguration->boomPitch - newConfiguration->boomPitch) < 1.0f)
            && (fabsf(oldConfiguration->viewPitch - newConfiguration->viewPitch) < 1.0f)
            && (fabsf(oldConfiguration->targetPos.x - newConfiguration->targetPos.x) < 10.0f)
            && (fabsf(oldConfiguration->targetPos.y - newConfiguration->targetPos.y) < 10.0f)
            && (fabsf(oldConfiguration->targetPos.z - newConfiguration->targetPos.z) < 10.0f)
        ) {
            *interpAlpha = 1.0f;
        }
    }

    if (*prevController == (CameraControlSettings*) CAMERA_SETTINGS_PTR_MINUS_1) {
        if (changingZone) {
            D_800A08E4 = oldConfiguration->targetPos.x - newConfiguration->targetPos.x;
            D_800A08E8 = oldConfiguration->targetPos.y - newConfiguration->targetPos.y;
            D_800A08EC = oldConfiguration->targetPos.z - newConfiguration->targetPos.z;
        }
        oldConfiguration->targetPos.x = newConfiguration->targetPos.x + D_800A08E4;
        oldConfiguration->targetPos.y = newConfiguration->targetPos.y + D_800A08E8;
        oldConfiguration->targetPos.z = newConfiguration->targetPos.z + D_800A08EC;
    }
}

void update_camera_zone_interp(Camera* camera) {
    CameraControlSettings* currentController;
    CameraControlSettings* cs;
    CameraControlSettings* cs2;
    f32 targetX;
    f32 targetY;
    f32 targetZ;
    f32 deltaX;
    f32 deltaY;
    f32 deltaZ;
    f32 maxDelta;
    f32 delta;
    f32 deltaSqSum;
    f32 panPhase;
    f32 temp_f20_2;
    f32 panRad;
    f32 cosAngle;
    f32 sinAngle;
    f32 temp_f24;
    f32 temp_f24_2;
    f32 temp_f26;
    f32 temp_f4_4;
    f32 interpAlpha;
    f32 interpAlphaInv;
    f32 temp_f8_2;
    f64 temp_f22_2;
    s32 cond2;
    f32 posX;
    f32 posY;
    f32 posZ;
    f32 tX;
    f32 tY;
    f32 tZ;
    s32 changingZone;
    f32 dist;

    targetX = camera->targetPos.x;
    targetY = camera->targetPos.y;
    targetZ = camera->targetPos.z;
    changingZone = FALSE;

    if (camera->isChangingMap) {
        camera->curController = NULL;
        camera->prevController = NULL;
        camera->linearInterp = 0.0f;
        camera->yinterpGoal = 0.0f;
        camera->yinterpCur = targetY;
        camera->unk_98 = 0;
        camera->unk_9C = 0;
        camera->prevTargetPos.x = 0.0f;
        camera->prevTargetPos.y = 0.0f;
        camera->prevTargetPos.z = 0.0f;
        camera->prevPrevFollowPlayer = FALSE;
        camera->prevFollowPlayer = FALSE;
        camera->panPhase = 0.0f;
        D_800A08DC = 0.0f;
        D_800A08E0 = 0.0f;
        camera->interpAlpha = 1.0f;
        camera->yinterpAlpha = 1.0f;
        camera->linearInterpScale = 1.0f;
    }

    if (camera->moveFlags & CAMERA_MOVE_IGNORE_PLAYER_Y) {
        camera->yinterpAlpha = 0.0f;
    } else if (camera->yinterpGoal != targetY) {
        camera->yinterpGoal = targetY;
        camera->yinterpAlpha = 0.0f;
    }

    // always follow player moving down with no interp
    if (targetY < camera->yinterpGoal && targetY <= camera->yinterpCur) {
        camera->yinterpGoal = targetY;
        camera->yinterpAlpha = 1.0f;
    }

    camera->yinterpAlpha += (1.01 - camera->yinterpAlpha) / camera->yinterpRate;

    if (camera->yinterpAlpha > 1.0) {
        camera->yinterpAlpha = 1.0f;
    }

    if (camera->moveFlags & CAMERA_MOVE_ACCEL_INTERP_Y) {
        camera->yinterpAlpha += 0.3;
        if (camera->yinterpAlpha >= 1.0) {
            camera->yinterpAlpha = 1.0f;
        }
    }

    if (!(camera->moveFlags & CAMERA_MOVE_NO_INTERP_Y)) {
        camera->yinterpCur += (camera->yinterpGoal - camera->yinterpCur) * camera->yinterpAlpha;
    }

    if (camera->panActive
        || camera->prevTargetPos.x != targetX
        || camera->prevTargetPos.y != targetY
        || camera->prevTargetPos.z != targetZ
        || camera->isChangingMap
    ) {

        if (camera->followPlayer) {
            cs = &camera->controlSettings;
        } else {
            cs = test_ray_zone_aabb(targetX, targetY + 10.0f, targetZ);
        }

        cond2 = FALSE;
        cs2 = cs;
        currentController = camera->curController;
        if (cs != NULL
            && currentController != NULL
            && cs->type == currentController->type
            && cs->flag == currentController->flag
            && cs->boomLength == currentController->boomLength
            && cs->boomPitch == currentController->boomPitch
            && cs->viewPitch == currentController->viewPitch
        ) {
            switch (cs->type) {
                case CAM_CONTROL_FIXED_ORIENTATION:
                    if (cs->points.two.Ax == currentController->points.two.Ax
                        && cs->points.two.Az == currentController->points.two.Az
                        && cs->points.two.Bx == currentController->points.two.Bx
                        && cs->points.two.Bz == currentController->points.two.Bz
                    ) {
                        cond2 = TRUE;
                    }
                    break;
                case CAM_CONTROL_LOOK_AT_POINT:
                    if (cs->flag) {
                        if (cs->points.two.Ax == currentController->points.two.Ax
                            && cs->points.two.Az == currentController->points.two.Az
                            && cs->points.two.Bx == currentController->points.two.Bx
                            && cs->points.two.Bz == currentController->points.two.Bz
                        ) {
                            cond2 = TRUE;
                        }
                    } else {
                        if (cs->points.two.Ax == currentController->points.two.Ax
                            && cs->points.two.Az == currentController->points.two.Az
                        ) {
                            cond2 = TRUE;
                        }
                    }
                    break;
                default:
                    if (cs2->points.two.Ax == currentController->points.two.Ax
                        && cs2->points.two.Az == currentController->points.two.Az
                        && cs2->points.two.Ay == currentController->points.two.Ay
                        && cs2->points.two.By == currentController->points.two.By
                        && cs2->points.two.Bx == currentController->points.two.Bx
                        && cs2->points.two.Bz == currentController->points.two.Bz
                    ) {
                        cond2 = TRUE;
                    }
                    break;
            }
        }

        if (camera->panActive || (!cond2 && cs2 != currentController)) {
            if (camera->interpAlpha == 1.0f) {
                camera->prevController = camera->curController;
            } else {
                camera->prevController = (CameraControlSettings*) CAMERA_SETTINGS_PTR_MINUS_1;
            }
            changingZone = TRUE;
            camera->prevConfiguration = gCurrentCamConfiguration;
            camera->curController = cs;
            camera->interpAlpha = 0.0f;
            camera->linearInterp = 0.0f;
            camera->panActive = FALSE;
            camera->linearInterpScale = camera->moveSpeed;
            camera->prevPrevFollowPlayer = camera->prevFollowPlayer;
            camera->prevFollowPlayer = camera->followPlayer;
            camera->prevPrevMovePos.x = camera->prevMovePos.x;
            camera->prevPrevMovePos.y = camera->prevMovePos.y;
            camera->prevPrevMovePos.z = camera->prevMovePos.z;
            camera->prevMovePos.x = camera->movePos.x;
            camera->prevMovePos.y = camera->movePos.y;
            camera->prevMovePos.z = camera->movePos.z;
        }
    }

    if (camera->prevPrevFollowPlayer) {
        posX = camera->prevPrevMovePos.x;
        posY = camera->prevPrevMovePos.y;
        posZ = camera->prevPrevMovePos.z;
    } else {
        posX = targetX;
        posY = camera->yinterpCur;
        posZ = targetZ;
    }

    if (camera->prevFollowPlayer) {
        camera->yinterpCur = camera->prevMovePos.y;
        tX = camera->prevMovePos.x;
        tY = camera->yinterpCur;
        tZ = camera->prevMovePos.z;
    } else {
        tX = targetX;
        tY = camera->yinterpCur;
        tZ = targetZ;
    }

    update_camera_from_controller(camera, &camera->prevConfiguration, &camera->prevController,
                                  &camera->goalConfiguration, &camera->curController, posX, posY, posZ, tX, tY, tZ,
                                  camera->isChangingMap, &camera->interpAlpha, changingZone);

    if (camera->isChangingMap) {
        camera->prevConfiguration = camera->goalConfiguration;
        camera->isChangingMap = FALSE;
        camera->interpAlpha = 1.0f;
    }

    if (camera->prevConfiguration.boomYaw - camera->goalConfiguration.boomYaw > 180.0f) {
        camera->prevConfiguration.boomYaw -= 360.0f;
    }
    if (camera->prevConfiguration.boomYaw - camera->goalConfiguration.boomYaw < -180.0f) {
        camera->prevConfiguration.boomYaw += 360.0f;
    }

    delta = fabsf(camera->prevConfiguration.boomYaw - camera->goalConfiguration.boomYaw);
    if (delta > 180.0f) {
        delta = 360.0f - delta;
    }
    maxDelta = delta;

    delta = fabsf(camera->prevConfiguration.boomPitch - camera->goalConfiguration.boomPitch);
    if (delta > 180.0f) {
        delta = 360.0f - delta;
    }
    if (maxDelta < delta) {
        maxDelta = delta;
    }

    delta = fabsf(camera->prevConfiguration.viewPitch - camera->goalConfiguration.viewPitch);
    if (delta > 180.0f) {
        delta = 360.0f - delta;
    }
    if (maxDelta < delta) {
        maxDelta = delta;
    }

    delta = fabsf(camera->prevConfiguration.boomLength - camera->goalConfiguration.boomLength);
    if (maxDelta < delta) {
        maxDelta = delta;
    }

    deltaX = camera->prevConfiguration.targetPos.x - camera->goalConfiguration.targetPos.x;
    deltaY = camera->prevConfiguration.targetPos.y - camera->goalConfiguration.targetPos.y;
    deltaZ = camera->prevConfiguration.targetPos.z - camera->goalConfiguration.targetPos.z;
    delta = SQ(deltaX) + SQ(deltaY) + SQ(deltaZ);

    if (delta != 0.0f) {
        delta = sqrtf(delta) * 0.2;
    }
    if (maxDelta < delta) {
        maxDelta = delta;
    }

    // clamp maxDelta to the interval [20.0, 90.0]
    if (maxDelta > 90.0f) {
        maxDelta = 90.0f;
    }
    if (maxDelta < 20.0f) {
        maxDelta = 20.0f;
    }

    camera->linearInterp += (1.0f / maxDelta) * camera->linearInterpScale;
    if (camera->linearInterp > 1.0f) {
        camera->linearInterp = 1.0f;
    }

    if (camera->interpAlpha < 1.0) {
        panPhase = camera->panPhase;
        panRad = panPhase * PI_D;
        temp_f24 = 2.0f / (cos_rad(panRad) + 1.0f);
        temp_f22_2 = cos_rad((camera->linearInterp * PI_D * (1.0f - panPhase)) + panRad);
        cosAngle = (temp_f22_2 + (1.0 - cos_rad(panRad)) * 0.5) * temp_f24;
        cosAngle = (2.0f - (cosAngle + 1.0f)) * 0.5001;
        camera->interpAlpha = cosAngle;
    }

    if (camera->interpAlpha >= 1.0f) {
        camera->interpAlpha = 1.0f;
        camera->linearInterp = 0.0f;
    }

    camera->prevTargetPos.x = targetX;
    camera->prevTargetPos.y = targetY;
    camera->prevTargetPos.z = targetZ;

    interpAlpha = camera->interpAlpha;
    interpAlphaInv = 1.0f - interpAlpha;
    gCurrentCamConfiguration.boomYaw = (camera->prevConfiguration.boomYaw * interpAlphaInv) + (camera->goalConfiguration.boomYaw * interpAlpha);
    gCurrentCamConfiguration.boomLength = (camera->prevConfiguration.boomLength * interpAlphaInv) + (camera->goalConfiguration.boomLength * interpAlpha);
    gCurrentCamConfiguration.boomPitch = (camera->prevConfiguration.boomPitch * interpAlphaInv) + (camera->goalConfiguration.boomPitch * interpAlpha);
    gCurrentCamConfiguration.viewPitch = (camera->prevConfiguration.viewPitch * interpAlphaInv) + (camera->goalConfiguration.viewPitch * interpAlpha);
    gCurrentCamConfiguration.targetPos.x = (camera->prevConfiguration.targetPos.x * interpAlphaInv) + (camera->goalConfiguration.targetPos.x * interpAlpha);
    gCurrentCamConfiguration.targetPos.y = (camera->prevConfiguration.targetPos.y * interpAlphaInv) + (camera->goalConfiguration.targetPos.y * interpAlpha);
    gCurrentCamConfiguration.targetPos.z = (camera->prevConfiguration.targetPos.z * interpAlphaInv) + (camera->goalConfiguration.targetPos.z * interpAlpha);
    gCurrentCamConfiguration.boomLength *= camera->zoomPercent;
    gCurrentCamConfiguration.boomLength *= 0.01;

    temp_f20_2 = gCurrentCamConfiguration.boomYaw + D_800A08E0;
    temp_f26 = sin_deg(temp_f20_2);
    temp_f24_2 = -cos_deg(temp_f20_2);
    cosAngle = cos_deg(gCurrentCamConfiguration.boomPitch + D_800A08DC);
    sinAngle = sin_deg(gCurrentCamConfiguration.boomPitch + D_800A08DC);

    if (!(camera->moveFlags & CAMERA_MOVE_NO_INTERP_Y)) {
        camera->lookAt_eye.y = gCurrentCamConfiguration.targetPos.y + (gCurrentCamConfiguration.boomLength * sinAngle);
    }

    camera->lookAt_eye.x = gCurrentCamConfiguration.targetPos.x - (temp_f26 * gCurrentCamConfiguration.boomLength * cosAngle);
    camera->lookAt_eye.z = gCurrentCamConfiguration.targetPos.z - (temp_f24_2 * gCurrentCamConfiguration.boomLength * cosAngle);
    cosAngle = cos_deg(-gCurrentCamConfiguration.viewPitch);
    sinAngle = sin_deg(-gCurrentCamConfiguration.viewPitch);

    if (camera->lookAt_eye.x == gCurrentCamConfiguration.targetPos.x && camera->lookAt_eye.z == gCurrentCamConfiguration.targetPos.z) {
        dist = 0.0f;
    } else {
        dist = dist2D(camera->lookAt_eye.x, camera->lookAt_eye.z, gCurrentCamConfiguration.targetPos.x, gCurrentCamConfiguration.targetPos.z);
    }

    temp_f8_2 = gCurrentCamConfiguration.targetPos.y - camera->lookAt_eye.y;
    if (!(camera->moveFlags & CAMERA_MOVE_NO_INTERP_Y)) {
        camera->lookAt_obj.y = camera->lookAt_eye.y + ((dist * sinAngle) + (temp_f8_2 * cosAngle));
    }
    temp_f4_4 = (dist * cosAngle) - (temp_f8_2 * sinAngle);
    camera->lookAt_obj.x = camera->lookAt_eye.x + (temp_f26 * temp_f4_4);
    camera->lookAt_obj.z = camera->lookAt_eye.z + (temp_f24_2 * temp_f4_4);
    camera->curYaw = gCurrentCamConfiguration.boomYaw + D_800A08E0;
    camera->curBoomYaw = camera->curYaw;
    camera->curBoomLength = gCurrentCamConfiguration.boomLength;
    camera->lookAt_yaw = -gCurrentCamConfiguration.boomYaw;
    camera->curPitch = -gCurrentCamConfiguration.boomPitch - gCurrentCamConfiguration.viewPitch;
    camera->lookAt_obj_target.x = camera->lookAt_obj.x;
    camera->lookAt_obj_target.y = camera->lookAt_obj.y;
    camera->lookAt_obj_target.z = camera->lookAt_obj.z;
    camera->curYOffset = 0.0f;
}
