#include "common.h"
#include "script_api/battle.h"

// lerp from a to b as alpha goes from 1.0 to 0.0
#define LERP(a, b, alpha) ((a) * (alpha) + (b) * (1.0f-(alpha)))

#define QUADRATIC_SINE_INTERP(alpha) (1.0f - sin_rad(sin_rad((1.0f - alpha) * PI_S / 2) * PI_S / 2))
#define CUBIC_SINE_INTERP(alpha) (1.0f - sin_rad(sin_rad(sin_rad((1.0f - alpha) * PI_S / 2) * PI_S / 2) * PI_S / 2))

static f32 BattleCam_PosX;
static f32 BattleCam_PosY;
static f32 BattleCam_PosZ;
static s16 BattleCam_SubjectActor;
static s16 BattleCam_SubjectActorPart;
static s16 BattleCam_BoomLength;
static s16 BattleCam_BoomYaw;
static s16 BattleCam_BoomPitch;
static s16 BattleCam_BoomOffsetY;
static f32 BattleCam_InitialBoomLength;
static f32 BattleCam_InitialBoomYaw;
static f32 BattleCam_InitialBoomPitch;
static f32 BattleCam_InitialBoomOffsetY;
static b8 BattleCam_DoneMoving;
static s16 BattleCam_MoveTimeLeft;
static s16 BattleCam_MoveTimeTotal;
static s8 BattleCam_AdjustTargetXMode;
static s8 BattleCam_AdjustTargetYMode;
static b8 BattleCam_SetImmediately;
static b8 BattleCam_UseLinearInterp;
static b8 BattleCam_ClampPosX;
static s8 BattleCam_ExtraOffsetX;
static f32 BattleCam_InitialPosX;
static f32 BattleCam_InitialPosY;
static f32 BattleCam_InitialPosZ;
static EvtScript* BattleCam_ControlScript;

s8 BattleCam_IsFrozen = FALSE;
s32 BattleCam_CurrentPresetID = -1;

typedef struct CamSubjects {
    Vec3f actorPos;
    Vec2f actorSize;
    f32 actorSizeAvg;
    Vec3f targetPos;
    Vec2f targetSize;
    f32 targetSizeAvg;
    Vec3f avgPos;
} CamSubjects;

f32 clamp_edge_pos_x(f32 x) {
    if (BattleCam_ClampPosX) {
        f32 upperBound = (500.0f - BattleCam_InitialBoomLength) * 0.4 + 30.0;
        f32 lowerBound = -upperBound;

        if (x < lowerBound) {
            x += (lowerBound - x) / 2;
        }
        if (x > upperBound) {
            x += (upperBound - x) / 2;
        }
    }
    return x;
}

b32 get_cam_subject_properties(CamSubjects* subjects, b32 usePart) {
    s32 actorClass = BattleCam_SubjectActor & ACTOR_CLASS_MASK;
    s32 actorID = BattleCam_SubjectActor & 0xFF;
    ActorPart* part = NULL;
    Actor* actor;
    Actor* targetActor;
    f32 deltaY;

    switch (actorClass) {
        case ACTOR_CLASS_PLAYER:
            actor = gBattleStatus.playerActor;
            break;
        case ACTOR_CLASS_PARTNER:
            actor = gBattleStatus.partnerActor;
            break;
        case ACTOR_CLASS_ENEMY:
            actor = gBattleStatus.enemyActors[actorID];
            if (usePart && actor != NULL) {
                part = get_actor_part(actor, BattleCam_SubjectActorPart);
            }
            break;
        default:
            return FALSE;
    }

    if (actor == NULL) {
        return FALSE;
    }

    if (part != NULL) {
        subjects->actorPos.x = part->absolutePos.x;
        subjects->actorPos.y = part->absolutePos.y + part->size.y / 2 + part->size.y / 4;
        subjects->actorPos.z = part->absolutePos.z;

        subjects->actorSize.x = part->size.x;
        subjects->actorSize.y = part->size.y;
    } else {
        subjects->actorPos.x = actor->curPos.x;
        subjects->actorPos.y = actor->curPos.y + actor->size.y / 2 + actor->size.y / 4;
        subjects->actorPos.z = actor->curPos.z;

        subjects->actorSize.x = actor->size.x;
        subjects->actorSize.y = actor->size.y;
    }
    subjects->actorSizeAvg = (subjects->actorSize.x + subjects->actorSize.y) / 2;

    targetActor = get_actor(actor->targetActorID);
    if (targetActor == NULL) {
        return FALSE;
    }

    subjects->targetPos.x = targetActor->curPos.x;
    subjects->targetPos.y = targetActor->curPos.y + targetActor->size.y / 2 + targetActor->size.y / 4;
    subjects->targetPos.z = targetActor->curPos.z;

    subjects->targetSize.x = targetActor->size.x;
    subjects->targetSize.y = targetActor->size.y;
    subjects->targetSizeAvg = (subjects->targetSize.x + subjects->targetSize.y) / 2;

    subjects->avgPos.x = (subjects->actorPos.x + subjects->targetPos.x) / 2;
    subjects->avgPos.z = (subjects->actorPos.z + subjects->targetPos.z) / 2;
    deltaY = subjects->actorPos.y - subjects->targetPos.y;

    switch (actorClass) {
        case ACTOR_CLASS_PLAYER:
            switch (BattleCam_AdjustTargetYMode) {
                case BTL_CAM_YADJ_SLIGHT:
                    // final position is weighted 75% actor and 25% target:
                    // = a - (a - t) / 4
                    // = (4a - a + t) / 4
                    // = (3a + t) / 4
                    subjects->avgPos.y = subjects->actorPos.y - deltaY / 4;
                    break;
                case BTL_CAM_YADJ_TARGET:
                    subjects->avgPos.y = subjects->targetPos.y;
                    break;
                case BTL_CAM_YADJ_NONE:
                    subjects->avgPos.y = subjects->actorPos.y;
                    break;
                case BTL_CAM_YADJ_AVG:
                    // final position is weighted 66% actor and 33% target:
                    // = t + (a - t) / 2 + (a - t) / 6
                    // = (6t + 3a - 3t + a - t) / 6
                    // = (2t + 4a) / 6
                    subjects->avgPos.y = subjects->targetPos.y + deltaY / 2 + deltaY / 6;
                    break;
            }
            break;
        case ACTOR_CLASS_PARTNER:
            switch (BattleCam_AdjustTargetYMode) {
                case BTL_CAM_YADJ_TARGET:
                    subjects->avgPos.y = subjects->targetPos.y;
                    break;
                case BTL_CAM_YADJ_NONE:
                    subjects->avgPos.y = subjects->actorPos.y;
                    break;
                case BTL_CAM_YADJ_AVG:
                    // same math as ACTOR_CLASS_PLAYER
                    subjects->avgPos.y = subjects->targetPos.y + deltaY / 2 + deltaY / 6;
                    break;
            }
            break;
        case ACTOR_CLASS_ENEMY:
            switch (BattleCam_AdjustTargetYMode) {
                case BTL_CAM_YADJ_SLIGHT:
                    subjects->avgPos.y = subjects->actorPos.y;
                    break;
                case BTL_CAM_YADJ_TARGET:
                    subjects->avgPos.y = subjects->targetPos.y;
                    break;
                case BTL_CAM_YADJ_NONE:
                    subjects->avgPos.y = subjects->actorPos.y;
                    break;
                case BTL_CAM_YADJ_AVG:
                    // same math as ACTOR_CLASS_PLAYER
                    subjects->avgPos.y = subjects->targetPos.y + deltaY / 2 + deltaY / 6;
                    break;
            }
            break;
        default:
            return FALSE;
    }

    return TRUE;
}

API_CALLABLE(BattleCam_Update_Interrupt) {
    BattleCam_DoneMoving = TRUE;
    return ApiStatus_BLOCK;
}

/// Used predominately for enemies executing an attack.
/// Updates the battle camera to focus on midpoint between BattleCam_SubjectActor and its target position.
/// Lerps most battle camera parameters to the new target configuration.
/// Free parameters:
///     BattleCam_BoomLength
///     BattleCam_BoomYaw
///     BattleCam_BoomPitch
///     BattleCam_BoomOffsetY
///     BattleCam_MoveTimeLeft
/// Can be skipped with BattleCam_SetImmediately.
API_CALLABLE(BattleCam_Update_FocusMidpointA) {
    Camera* camera = &gCameras[CAM_BATTLE];
    CamSubjects subjects;
    Vec3f prevPos;
    f32 alpha;
    f32 targetBoomLength;

    if (!get_cam_subject_properties(&subjects, FALSE)) {
        return ApiStatus_BLOCK;
    }

    subjects.avgPos.x = clamp_edge_pos_x(subjects.avgPos.x);

    if (isInitialCall) {
        BattleCam_BoomLength += MAX(0, subjects.actorSize.x - 24.0);
        BattleCam_BoomLength += MAX(0, subjects.actorSize.y - 24.0);

        if (BattleCam_SetImmediately) {
            camera->lookAt_obj_target.x = subjects.avgPos.x;
            camera->lookAt_obj_target.y = subjects.avgPos.y;
            camera->lookAt_obj_target.z = subjects.avgPos.z;

            camera->params.basic.dist = BattleCam_BoomLength;
            camera->params.basic.pitch = BattleCam_BoomPitch;
            camera->params.basic.yaw = BattleCam_BoomYaw;
            camera->params.basic.offsetY = BattleCam_BoomOffsetY * 256;
        }

        BattleCam_InitialPosX = camera->lookAt_obj_target.x;
        BattleCam_InitialPosY = camera->lookAt_obj_target.y;
        BattleCam_InitialPosZ = camera->lookAt_obj_target.z;

        BattleCam_InitialBoomLength = camera->params.basic.dist;
        BattleCam_InitialBoomPitch = camera->params.basic.pitch;
        BattleCam_InitialBoomYaw = camera->params.basic.yaw;
        BattleCam_InitialBoomOffsetY = camera->params.basic.offsetY / 256;

        BattleCam_MoveTimeTotal = BattleCam_MoveTimeLeft;
    }

    alpha = (f32) BattleCam_MoveTimeLeft / BattleCam_MoveTimeTotal;
    if (!BattleCam_UseLinearInterp) {
        alpha = CUBIC_SINE_INTERP(alpha);
    }

    prevPos.x = camera->lookAt_obj_target.x;
    prevPos.y = camera->lookAt_obj_target.y;
    prevPos.z = camera->lookAt_obj_target.z;

    camera->lookAt_obj_target.x = LERP(BattleCam_InitialPosX, subjects.avgPos.x, alpha);
    camera->lookAt_obj_target.y = LERP(BattleCam_InitialPosY, subjects.avgPos.y, alpha);
    camera->lookAt_obj_target.z = LERP(BattleCam_InitialPosZ, subjects.avgPos.z, alpha);

    targetBoomLength = BattleCam_BoomLength;
    targetBoomLength += dist2D(camera->lookAt_obj_target.x, camera->lookAt_obj_target.z, subjects.avgPos.x, subjects.avgPos.z);
    //NOTE division by 8 here is only difference between this and BattleCam_Update_FocusMidpointB
    targetBoomLength += (subjects.actorSizeAvg + subjects.targetSizeAvg) / 8;
    targetBoomLength -= 64.0f;
    targetBoomLength += 0.5f * dist3D(prevPos.z, prevPos.y, prevPos.z, subjects.targetPos.x, subjects.targetPos.y, subjects.targetPos.z);

    camera->params.basic.dist = LERP(BattleCam_InitialBoomLength, targetBoomLength, alpha);
    camera->params.basic.yaw = LERP(BattleCam_InitialBoomYaw, BattleCam_BoomYaw, alpha);
    camera->params.basic.pitch = LERP(BattleCam_InitialBoomPitch, BattleCam_BoomPitch, alpha);
    camera->params.basic.offsetY = LERP(BattleCam_InitialBoomOffsetY, BattleCam_BoomOffsetY, alpha) * 256.0f;

    if (BattleCam_MoveTimeLeft == 0) {
        BattleCam_DoneMoving = TRUE;
    } else {
        BattleCam_MoveTimeLeft--;
    }

    return ApiStatus_BLOCK;
}

/// Used predominately for party members executing an attack.
/// Updates the battle camera to focus on midpoint between BattleCam_SubjectActor and its target position.
/// Lerps most battle camera parameters to the new target configuration.
/// Free parameters:
///     BattleCam_BoomLength
///     BattleCam_BoomYaw
///     BattleCam_BoomPitch
///     BattleCam_BoomOffsetY
///     BattleCam_MoveTimeLeft
/// Can be skipped with BattleCam_SetImmediately.
API_CALLABLE(BattleCam_Update_FocusMidpointB) {
    Camera* camera = &gCameras[CAM_BATTLE];
    CamSubjects subjects;
    Vec3f prevPos;
    f32 alpha;
    f32 targetBoomLength;

    if (!get_cam_subject_properties(&subjects, FALSE)) {
        return ApiStatus_BLOCK;
    }

    subjects.avgPos.x = clamp_edge_pos_x(subjects.avgPos.x);

    if (isInitialCall) {
        BattleCam_BoomLength += MAX(0, subjects.actorSize.x - 24.0);
        BattleCam_BoomLength += MAX(0, subjects.actorSize.y - 24.0);

        if (BattleCam_SetImmediately) {
            camera->lookAt_obj_target.x = subjects.avgPos.x;
            camera->lookAt_obj_target.y = subjects.avgPos.y;
            camera->lookAt_obj_target.z = subjects.avgPos.z;

            camera->params.basic.dist = BattleCam_BoomLength;
            camera->params.basic.pitch = BattleCam_BoomPitch;
            camera->params.basic.yaw = BattleCam_BoomYaw;
            camera->params.basic.offsetY = BattleCam_BoomOffsetY * 256;
        }

        BattleCam_InitialPosX = camera->lookAt_obj_target.x;
        BattleCam_InitialPosY = camera->lookAt_obj_target.y;
        BattleCam_InitialPosZ = camera->lookAt_obj_target.z;

        BattleCam_InitialBoomLength = camera->params.basic.dist;
        BattleCam_InitialBoomPitch = camera->params.basic.pitch;
        BattleCam_InitialBoomYaw = camera->params.basic.yaw;
        BattleCam_InitialBoomOffsetY = camera->params.basic.offsetY / 256;

        BattleCam_MoveTimeTotal = BattleCam_MoveTimeLeft;
    }

    alpha = (f32) BattleCam_MoveTimeLeft / BattleCam_MoveTimeTotal;
    if (!BattleCam_UseLinearInterp) {
        alpha = CUBIC_SINE_INTERP(alpha);
    }

    prevPos.x = camera->lookAt_obj_target.x;
    prevPos.y = camera->lookAt_obj_target.y;
    prevPos.z = camera->lookAt_obj_target.z;

    camera->lookAt_obj_target.x = LERP(BattleCam_InitialPosX, subjects.avgPos.x, alpha);
    camera->lookAt_obj_target.y = LERP(BattleCam_InitialPosY, subjects.avgPos.y, alpha);
    camera->lookAt_obj_target.z = LERP(BattleCam_InitialPosZ, subjects.avgPos.z, alpha);

    targetBoomLength = BattleCam_BoomLength;
    targetBoomLength += dist2D(camera->lookAt_obj_target.x, camera->lookAt_obj_target.z, subjects.avgPos.x, subjects.avgPos.z);
    targetBoomLength += subjects.actorSizeAvg - 32.0f;
    targetBoomLength += subjects.targetSizeAvg - 32.0f;
    targetBoomLength += 0.5f * dist3D(prevPos.z, prevPos.y, prevPos.z, subjects.targetPos.x, subjects.targetPos.y, subjects.targetPos.z);

    camera->params.basic.dist = LERP(BattleCam_InitialBoomLength, targetBoomLength, alpha);
    camera->params.basic.yaw = LERP(BattleCam_InitialBoomYaw, BattleCam_BoomYaw, alpha);
    camera->params.basic.pitch = LERP(BattleCam_InitialBoomPitch, BattleCam_BoomPitch, alpha);
    camera->params.basic.offsetY = LERP(BattleCam_InitialBoomOffsetY, BattleCam_BoomOffsetY, alpha) * 256.0f;

    if (BattleCam_MoveTimeLeft == 0) {
        BattleCam_DoneMoving = TRUE;
    } else {
        BattleCam_MoveTimeLeft--;
    }

    return ApiStatus_BLOCK;
}

/// Updates the battle camera to focus on midpoint between BattleCam_SubjectActorPart and its target position.
/// Lerps most battle camera parameters to the new target configuration.
/// Does NOT adjust boom length using actor size!
/// Free parameters:
///     BattleCam_BoomLength
///     BattleCam_BoomYaw
///     BattleCam_BoomPitch
///     BattleCam_BoomOffsetY
///     BattleCam_MoveTimeLeft
/// Can be skipped with BattleCam_SetImmediately.
API_CALLABLE(BattleCam_Update_FocusActorPart) {
    Camera* camera = &gCameras[CAM_BATTLE];
    CamSubjects subjects;
    f32 alpha;

    if (!get_cam_subject_properties(&subjects, TRUE)) {
        return ApiStatus_BLOCK;
    }

    subjects.avgPos.x = clamp_edge_pos_x(subjects.avgPos.x);

    if (isInitialCall) {
        BattleCam_BoomLength += MAX(0, subjects.actorSize.x - 24.0);
        BattleCam_BoomLength += MAX(0, subjects.actorSize.y - 24.0);

        if (BattleCam_SetImmediately) {
            camera->lookAt_obj_target.x = subjects.avgPos.x;
            camera->lookAt_obj_target.y = subjects.avgPos.y;
            camera->lookAt_obj_target.z = subjects.avgPos.z;

            camera->params.basic.dist = BattleCam_BoomLength;
            camera->params.basic.pitch = BattleCam_BoomPitch;
            camera->params.basic.yaw = BattleCam_BoomYaw;
            camera->params.basic.offsetY = BattleCam_BoomOffsetY * 256;
        }

        BattleCam_InitialPosX = camera->lookAt_obj_target.x;
        BattleCam_InitialPosY = camera->lookAt_obj_target.y;
        BattleCam_InitialPosZ = camera->lookAt_obj_target.z;

        BattleCam_InitialBoomLength = camera->params.basic.dist;
        BattleCam_InitialBoomPitch = camera->params.basic.pitch;
        BattleCam_InitialBoomYaw = camera->params.basic.yaw;
        BattleCam_InitialBoomOffsetY = camera->params.basic.offsetY / 256;

        BattleCam_MoveTimeTotal = BattleCam_MoveTimeLeft;
    }

    alpha = (f32) BattleCam_MoveTimeLeft / BattleCam_MoveTimeTotal;
    if (!BattleCam_UseLinearInterp) {
        alpha = CUBIC_SINE_INTERP(alpha);
    }

    camera->lookAt_obj_target.x = LERP(BattleCam_InitialPosX, subjects.avgPos.x, alpha);
    camera->lookAt_obj_target.y = LERP(BattleCam_InitialPosY, subjects.avgPos.y, alpha);
    camera->lookAt_obj_target.z = LERP(BattleCam_InitialPosZ, subjects.avgPos.z, alpha);

    camera->params.basic.dist = LERP(BattleCam_InitialBoomLength, BattleCam_BoomLength, alpha);
    camera->params.basic.yaw = LERP(BattleCam_InitialBoomYaw, BattleCam_BoomYaw, alpha);
    camera->params.basic.pitch = LERP(BattleCam_InitialBoomPitch, BattleCam_BoomPitch, alpha);
    camera->params.basic.offsetY = LERP(BattleCam_InitialBoomOffsetY, BattleCam_BoomOffsetY, alpha) * 256.0f;

    if (BattleCam_MoveTimeLeft == 0) {
        BattleCam_DoneMoving = TRUE;
    } else {
        BattleCam_MoveTimeLeft--;
    }

    return ApiStatus_BLOCK;
}

/// Updates the battle camera to focus on BattleCam_SubjectActor.
/// Free parameters:
///     BattleCam_BoomLength
///     BattleCam_BoomYaw
///     BattleCam_BoomPitch
///     BattleCam_BoomOffsetY
///     BattleCam_MoveTimeLeft
API_CALLABLE(BattleCam_Update_FocusActor) {
    Camera* camera = &gCameras[CAM_BATTLE];
    Actor* actor;
    f32 actorX, actorY, actorZ;
    f32 actorSize;
    f32 alpha;
    f32 targetBoomLength;
    s32 actorClass = BattleCam_SubjectActor & ACTOR_CLASS_MASK;
    s32 actorID = BattleCam_SubjectActor & 0xFF;

    switch (actorClass) {
        case ACTOR_CLASS_PLAYER:
            actor = gBattleStatus.playerActor;
            if (actor == NULL) {
                btl_cam_use_preset(BTL_CAM_DEFAULT);
                return ApiStatus_BLOCK;
            }
            actorX = actor->curPos.x;
            actorY = actor->curPos.y + gPlayerStatus.colliderHeight / 2;
            actorZ = actor->curPos.z;

            actorSize = (actor->size.x + actor->size.y) / 2;
            break;
        case ACTOR_CLASS_PARTNER:
            actor = gBattleStatus.partnerActor;
            if (actor == NULL) {
                btl_cam_use_preset(BTL_CAM_DEFAULT);
                return ApiStatus_BLOCK;
            }
            actorX = actor->curPos.x;
            actorY = actor->curPos.y + actor->size.y / 2;
            actorZ = actor->curPos.z;

            actorSize = (actor->size.x + actor->size.y) / 2;
            break;
        case ACTOR_CLASS_ENEMY:
            actor = gBattleStatus.enemyActors[actorID];
            if (actor == NULL) {
                btl_cam_use_preset(BTL_CAM_DEFAULT);
                return ApiStatus_BLOCK;
            }
            actorX = actor->curPos.x;
            actorY = actor->curPos.y + actor->size.y / 2;
            actorZ = actor->curPos.z;

            actorSize = (actor->size.x + actor->size.y) / 2;
            break;
        default:
            return ApiStatus_DONE2;
    }

    actorX = clamp_edge_pos_x(actorX);

    if (isInitialCall) {
        BattleCam_BoomLength += MAX(0, actor->size.x - 24.0);
        BattleCam_BoomLength += MAX(0, actor->size.y - 24.0);

        BattleCam_InitialPosX = camera->lookAt_obj_target.x;
        BattleCam_InitialPosY = camera->lookAt_obj_target.y;
        BattleCam_InitialPosZ = camera->lookAt_obj_target.z;

        BattleCam_InitialBoomLength = camera->params.basic.dist;
        BattleCam_InitialBoomPitch = camera->params.basic.pitch;
        BattleCam_InitialBoomYaw = camera->params.basic.yaw;
        BattleCam_InitialBoomOffsetY = camera->params.basic.offsetY / 256;

        BattleCam_MoveTimeTotal = BattleCam_MoveTimeLeft;
    }

    alpha = (f32) BattleCam_MoveTimeLeft / BattleCam_MoveTimeTotal;
    if (!BattleCam_UseLinearInterp) {
        alpha = CUBIC_SINE_INTERP(alpha);
    }

    if (BattleCam_AdjustTargetXMode != BTL_CAM_XADJ_NONE) {
        camera->lookAt_obj_target.x = LERP(BattleCam_InitialPosX, actorX + BattleCam_ExtraOffsetX, alpha);
    }
    if (BattleCam_AdjustTargetYMode != BTL_CAM_YADJ_NONE) {
        camera->lookAt_obj_target.y = LERP(BattleCam_InitialPosY, actorY, alpha);
    }
    camera->lookAt_obj_target.z = LERP(BattleCam_InitialPosZ, actorZ, alpha);

    targetBoomLength = BattleCam_BoomLength;
    targetBoomLength += actorSize - 32.0f;

    camera->params.basic.dist = LERP(BattleCam_InitialBoomLength, targetBoomLength, alpha);
    camera->params.basic.yaw = LERP(BattleCam_InitialBoomYaw, BattleCam_BoomYaw, alpha);
    camera->params.basic.pitch = LERP(BattleCam_InitialBoomPitch, BattleCam_BoomPitch, alpha);
    camera->params.basic.offsetY = LERP(BattleCam_InitialBoomOffsetY, BattleCam_BoomOffsetY, alpha) * 256.0f;

    if (BattleCam_MoveTimeLeft == 0) {
        BattleCam_DoneMoving = TRUE;
    } else {
        BattleCam_MoveTimeLeft--;
    }

    return ApiStatus_BLOCK;
}

/// Updates the battle camera to focus on midpoint between BattleCam_SubjectActor and its goal position.
/// Free parameters:
///     BattleCam_BoomLength
///     BattleCam_BoomYaw
///     BattleCam_BoomPitch
///     BattleCam_BoomOffsetY
///     BattleCam_MoveTimeLeft
API_CALLABLE(BattleCam_Update_FocusGoal) {
    Camera* camera = &gCameras[CAM_BATTLE];
    s32 actorClass = BattleCam_SubjectActor & ACTOR_CLASS_MASK;
    s32 actorID = BattleCam_SubjectActor & 0xFF;
    Actor* actor;
    f32 goalX, goalY, goalZ;
    f32 actorX, actorY;
    f32 actorSizeAvg;
    f32 targetBoomLength;
    f32 alpha;

    switch (actorClass) {
        case ACTOR_CLASS_PLAYER:
            actor = gBattleStatus.playerActor;
            if (actor == NULL) {
                return ApiStatus_BLOCK;
            }
            goalX = actor->state.goalPos.x;
            goalY = actor->state.goalPos.y;
            goalZ = actor->state.goalPos.z;
            actorX = actor->curPos.x;
            actorY = actor->curPos.y + gPlayerStatus.colliderHeight / 2;
            actorSizeAvg = (actor->size.y + actor->size.x) / 2;
            break;
        case ACTOR_CLASS_PARTNER:
            actor = gBattleStatus.partnerActor;
            if (actor == NULL) {
                return ApiStatus_BLOCK;
            }
            goalX = actor->state.goalPos.x;
            goalY = actor->state.goalPos.y;
            goalZ = actor->state.goalPos.z;
            actorX = actor->curPos.x;
            actorY = actor->curPos.y + actor->size.y / 2;
            actorSizeAvg = (actor->size.y + actor->size.x) / 2;
            break;
        case ACTOR_CLASS_ENEMY:
            actor = gBattleStatus.enemyActors[actorID];
            if (actor == NULL) {
                return ApiStatus_BLOCK;
            }
            goalX = actor->state.goalPos.x;
            goalY = actor->state.goalPos.y;
            goalZ = actor->state.goalPos.z;
            actorX = actor->curPos.x;
            actorY = actor->curPos.y + actor->size.y / 2;
            actorSizeAvg = (actor->size.y + actor->size.x) / 2;
            break;
        default:
            return ApiStatus_DONE2;
    }

    if (BattleCam_AdjustTargetYMode != BTL_CAM_YADJ_NONE) {
        f32 delta = actorY - goalY;
        goalY += delta / 2 + delta / 6.0f;
    }

    if (BattleCam_AdjustTargetXMode != BTL_CAM_XADJ_NONE) {
        goalX = (actorX + goalX) / 2;
        if (goalX > 75.0f) {
            goalX -= fabsf(75.0f - goalX);
        }
    }

    goalX = clamp_edge_pos_x(goalX);

    if (isInitialCall) {
        BattleCam_InitialPosX = camera->lookAt_obj_target.x;
        BattleCam_InitialPosY = camera->lookAt_obj_target.y;
        BattleCam_InitialPosZ = camera->lookAt_obj_target.z;

        BattleCam_InitialBoomLength = camera->params.basic.dist;
        BattleCam_InitialBoomPitch = camera->params.basic.pitch;
        BattleCam_InitialBoomYaw = camera->params.basic.yaw;
        BattleCam_InitialBoomOffsetY = camera->params.basic.offsetY / 256;

        BattleCam_MoveTimeTotal = BattleCam_MoveTimeLeft;
    }

    alpha = (f32) BattleCam_MoveTimeLeft / BattleCam_MoveTimeTotal;
    if (!BattleCam_UseLinearInterp) {
        alpha = CUBIC_SINE_INTERP(alpha);
    }

    camera->lookAt_obj_target.x = LERP(BattleCam_InitialPosX, goalX, alpha);
    camera->lookAt_obj_target.y = LERP(BattleCam_InitialPosY, goalY, alpha);
    camera->lookAt_obj_target.z = LERP(BattleCam_InitialPosZ, goalZ, alpha);

    targetBoomLength = BattleCam_BoomLength;
    targetBoomLength += actorSizeAvg - 32.0f;

    camera->params.basic.dist = LERP(BattleCam_InitialBoomLength, targetBoomLength, alpha);
    camera->params.basic.pitch = LERP(BattleCam_InitialBoomPitch, BattleCam_BoomPitch, alpha);
    camera->params.basic.yaw = LERP(BattleCam_InitialBoomYaw, BattleCam_BoomYaw, alpha);
    camera->params.basic.offsetY = LERP(BattleCam_InitialBoomOffsetY, BattleCam_BoomOffsetY, alpha) * 256.0f;

    if (BattleCam_MoveTimeLeft == 0) {
        BattleCam_DoneMoving = TRUE;
    } else {
        BattleCam_MoveTimeLeft--;
    }

    return ApiStatus_BLOCK;
}

/// Lerps all battle camera parameters to target values.
/// Free parameters:
///     BattleCam_PosX, BattleCam_PosY, BattleCam_PosZ
///     BattleCam_BoomLength
///     BattleCam_BoomYaw
///     BattleCam_BoomPitch
///     BattleCam_BoomOffsetY
///     BattleCam_MoveTimeLeft
API_CALLABLE(BattleCam_Update_SimpleLerp_Unskippable) {
    Camera* camera = &gCameras[CAM_BATTLE];
    f32 alpha;

    if (isInitialCall) {
        BattleCam_InitialBoomLength = camera->params.basic.dist;
        BattleCam_InitialBoomPitch = camera->params.basic.pitch;
        BattleCam_InitialBoomYaw = camera->params.basic.yaw;
        BattleCam_InitialBoomOffsetY = camera->params.basic.offsetY / 256;

        BattleCam_InitialPosX = camera->lookAt_obj_target.x;
        BattleCam_InitialPosY = camera->lookAt_obj_target.y;
        BattleCam_InitialPosZ = camera->lookAt_obj_target.z;

        BattleCam_MoveTimeTotal = BattleCam_MoveTimeLeft;
    }

    alpha = (f32) BattleCam_MoveTimeLeft / BattleCam_MoveTimeTotal;
    if (!BattleCam_UseLinearInterp) {
        alpha = CUBIC_SINE_INTERP(alpha);
    }

    camera->lookAt_obj_target.x = LERP(BattleCam_InitialPosX, BattleCam_PosX, alpha);
    camera->lookAt_obj_target.y = LERP(BattleCam_InitialPosY, BattleCam_PosY, alpha);
    camera->lookAt_obj_target.z = LERP(BattleCam_InitialPosZ, BattleCam_PosZ, alpha);

    camera->params.basic.dist = LERP(BattleCam_InitialBoomLength, BattleCam_BoomLength, alpha);
    camera->params.basic.yaw = LERP(BattleCam_InitialBoomYaw, BattleCam_BoomYaw, alpha);
    camera->params.basic.pitch = LERP(BattleCam_InitialBoomPitch, BattleCam_BoomPitch, alpha);
    camera->params.basic.offsetY = LERP(BattleCam_InitialBoomOffsetY, BattleCam_BoomOffsetY, alpha) * 256.0f;

    if (BattleCam_MoveTimeLeft == 0) {
        BattleCam_DoneMoving = TRUE;
    } else {
        BattleCam_MoveTimeLeft--;
    }

    return ApiStatus_BLOCK;
}

/// Lerps all battle camera parameters to default 'neutral' position.
/// Free parameters:
///     BattleCam_BoomLength
///     BattleCam_BoomPitch
///     BattleCam_MoveTimeLeft
/// Can be skipped with BattleCam_SetImmediately.
API_CALLABLE(BattleCam_Update_ResetToNeutral_Skippable) {
    Camera* camera = &gCameras[CAM_BATTLE];
    f32 alpha;

    if (isInitialCall) {
        BattleCam_PosX = 0.0f;
        BattleCam_PosY = 60.0f;
        BattleCam_PosZ = 0.0f;

        BattleCam_BoomYaw = 0;
        BattleCam_BoomOffsetY = 0;

        if (BattleCam_SetImmediately) {
            camera->lookAt_obj_target.x = BattleCam_PosX;
            camera->lookAt_obj_target.y = BattleCam_PosY;
            camera->lookAt_obj_target.z = BattleCam_PosZ;

            camera->params.basic.dist = BattleCam_BoomLength;
            camera->params.basic.pitch = BattleCam_BoomPitch;
            camera->params.basic.yaw = BattleCam_BoomYaw;
            camera->params.basic.offsetY = BattleCam_BoomOffsetY;
        }

        BattleCam_InitialBoomLength = camera->params.basic.dist;
        BattleCam_InitialBoomPitch = camera->params.basic.pitch;
        BattleCam_InitialBoomYaw = camera->params.basic.yaw;
        BattleCam_InitialBoomOffsetY = camera->params.basic.offsetY / 256;

        BattleCam_InitialPosX = camera->lookAt_obj_target.x;
        BattleCam_InitialPosY = camera->lookAt_obj_target.y;
        BattleCam_InitialPosZ = camera->lookAt_obj_target.z;

        BattleCam_MoveTimeTotal = BattleCam_MoveTimeLeft;
    }

    alpha = (f32) BattleCam_MoveTimeLeft / BattleCam_MoveTimeTotal;
    if (!BattleCam_UseLinearInterp) {
        alpha = QUADRATIC_SINE_INTERP(alpha);
    }

    camera->lookAt_obj_target.x = LERP(BattleCam_InitialPosX, BattleCam_PosX, alpha);
    camera->lookAt_obj_target.y = LERP(BattleCam_InitialPosY, BattleCam_PosY, alpha);
    camera->lookAt_obj_target.z = LERP(BattleCam_InitialPosZ, BattleCam_PosZ, alpha);

    camera->params.basic.dist = LERP(BattleCam_InitialBoomLength, BattleCam_BoomLength, alpha);
    camera->params.basic.pitch = LERP(BattleCam_InitialBoomPitch, BattleCam_BoomPitch, alpha);
    camera->params.basic.yaw = LERP(BattleCam_InitialBoomYaw, BattleCam_BoomYaw, alpha);
    camera->params.basic.offsetY = LERP(BattleCam_InitialBoomOffsetY, BattleCam_BoomOffsetY, alpha) * 256.0f;

    if (BattleCam_MoveTimeLeft == 0) {
        BattleCam_DoneMoving = TRUE;
    } else {
        BattleCam_MoveTimeLeft--;
    }

    return ApiStatus_BLOCK;
}

/// Lerps all battle camera parameters to preset position focusing on the enemy side of the field.
/// Free parameters:
///     BattleCam_BoomLength
///     BattleCam_BoomPitch
///     BattleCam_BoomOffsetY
///     BattleCam_MoveTimeLeft
API_CALLABLE(BattleCam_Update_ViewAllEnemies) {
    Camera* camera = &gCameras[CAM_BATTLE];
    f32 alpha;

    if (isInitialCall) {
        BattleCam_PosX = 35.0f;
        BattleCam_PosY = 60.0f;
        BattleCam_PosZ = 0.0f;

        BattleCam_BoomYaw = 0;

        BattleCam_InitialBoomLength = camera->params.basic.dist;
        BattleCam_InitialBoomPitch = camera->params.basic.pitch;
        BattleCam_InitialBoomYaw = camera->params.basic.yaw;
        BattleCam_InitialBoomOffsetY = camera->params.basic.offsetY / 256;

        BattleCam_InitialPosX = camera->lookAt_obj_target.x;
        BattleCam_InitialPosY = camera->lookAt_obj_target.y;
        BattleCam_InitialPosZ = camera->lookAt_obj_target.z;

        BattleCam_MoveTimeTotal = BattleCam_MoveTimeLeft;
    }

    alpha = (f32) BattleCam_MoveTimeLeft / BattleCam_MoveTimeTotal;
    if (!BattleCam_UseLinearInterp) {
        alpha = CUBIC_SINE_INTERP(alpha);
    }

    camera->lookAt_obj_target.x = LERP(BattleCam_InitialPosX, BattleCam_PosX, alpha);
    camera->lookAt_obj_target.y = LERP(BattleCam_InitialPosY, BattleCam_PosY, alpha);
    camera->lookAt_obj_target.z = LERP(BattleCam_InitialPosZ, BattleCam_PosZ, alpha);

    camera->params.basic.dist = LERP(BattleCam_InitialBoomLength, BattleCam_BoomLength, alpha);
    camera->params.basic.yaw = LERP(BattleCam_InitialBoomYaw, BattleCam_BoomYaw, alpha);
    camera->params.basic.pitch = LERP(BattleCam_InitialBoomPitch, BattleCam_BoomPitch, alpha);
    camera->params.basic.offsetY = LERP(BattleCam_InitialBoomOffsetY, BattleCam_BoomOffsetY, alpha) * 256.0f;

    if (BattleCam_MoveTimeLeft == 0) {
        BattleCam_DoneMoving = TRUE;
    } else {
        BattleCam_MoveTimeLeft--;
    }

    return ApiStatus_BLOCK;
}

/// Lerps all battle camera parameters to preset position focusing on the enemy side of the field.
/// Does not set a fixed y-position, but does clamp its minimum to 60.
/// Free parameters:
///     BattleCam_BoomLength
///     BattleCam_BoomPitch
///     BattleCam_BoomOffsetY
///     BattleCam_MoveTimeLeft
API_CALLABLE(BattleCam_Update_ViewAllEnemies_MaintainY) {
    Camera* camera = &gCameras[CAM_BATTLE];
    f32 alpha;

    if (isInitialCall) {
        BattleCam_PosX = 35.0f;
        BattleCam_PosY = MAX(camera->lookAt_obj_target.y, 60.0f);
        BattleCam_PosZ = 0.0f;

        BattleCam_BoomYaw = 0;

        BattleCam_InitialBoomLength = camera->params.basic.dist;
        BattleCam_InitialBoomPitch = camera->params.basic.pitch;
        BattleCam_InitialBoomYaw = camera->params.basic.yaw;
        BattleCam_InitialBoomOffsetY = camera->params.basic.offsetY / 256;

        BattleCam_InitialPosX = camera->lookAt_obj_target.x;
        BattleCam_InitialPosY = camera->lookAt_obj_target.y;
        BattleCam_InitialPosZ = camera->lookAt_obj_target.z;

        BattleCam_MoveTimeTotal = BattleCam_MoveTimeLeft;
    }

    alpha = (f32) BattleCam_MoveTimeLeft / BattleCam_MoveTimeTotal;
    if (!BattleCam_UseLinearInterp) {
        alpha = CUBIC_SINE_INTERP(alpha);
    }

    camera->lookAt_obj_target.x = LERP(BattleCam_InitialPosX, BattleCam_PosX, alpha);
    camera->lookAt_obj_target.y = LERP(BattleCam_InitialPosY, BattleCam_PosY, alpha);
    camera->lookAt_obj_target.z = LERP(BattleCam_InitialPosZ, BattleCam_PosZ, alpha);

    camera->params.basic.dist = LERP(BattleCam_InitialBoomLength, BattleCam_BoomLength, alpha);
    camera->params.basic.yaw = LERP(BattleCam_InitialBoomYaw, BattleCam_BoomYaw, alpha);
    camera->params.basic.pitch = LERP(BattleCam_InitialBoomPitch, BattleCam_BoomPitch, alpha);
    camera->params.basic.offsetY = LERP(BattleCam_InitialBoomOffsetY, BattleCam_BoomOffsetY, alpha) * 256.0f;

    if (BattleCam_MoveTimeLeft == 0) {
        BattleCam_DoneMoving = TRUE;
    } else {
        BattleCam_MoveTimeLeft--;
    }

    return ApiStatus_BLOCK;
}

/// Lerps all battle camera parameters to target values.
/// Can be skipped with BattleCam_SetImmediately.
/// Free parameters:
///     BattleCam_PosX, BattleCam_PosY, BattleCam_PosZ
///     BattleCam_BoomLength
///     BattleCam_BoomYaw
///     BattleCam_BoomPitch
///     BattleCam_BoomOffsetY
///     BattleCam_MoveTimeLeft
API_CALLABLE(BattleCam_Update_SimpleLerp_Skippable) {
    Camera* camera = &gCameras[CAM_BATTLE];
    f32 alpha;

    if (isInitialCall) {
        if (BattleCam_SetImmediately) {
            BattleCam_PosX = camera->lookAt_obj_target.x;
            BattleCam_PosY = camera->lookAt_obj_target.y;
            BattleCam_PosZ = camera->lookAt_obj_target.z;
        }

        BattleCam_InitialBoomLength = camera->params.basic.dist;
        BattleCam_InitialBoomPitch = camera->params.basic.pitch;
        BattleCam_InitialBoomYaw = camera->params.basic.yaw;
        BattleCam_InitialBoomOffsetY = camera->params.basic.offsetY / 256;

        BattleCam_InitialPosX = camera->lookAt_obj_target.x;
        BattleCam_InitialPosY = camera->lookAt_obj_target.y;
        BattleCam_InitialPosZ = camera->lookAt_obj_target.z;

        BattleCam_MoveTimeTotal = BattleCam_MoveTimeLeft;
    }

    alpha = (f32) BattleCam_MoveTimeLeft / BattleCam_MoveTimeTotal;
    if (!BattleCam_UseLinearInterp) {
        alpha = CUBIC_SINE_INTERP(alpha);
    }

    camera->lookAt_obj_target.x = LERP(BattleCam_InitialPosX, BattleCam_PosX, alpha);
    camera->lookAt_obj_target.y = LERP(BattleCam_InitialPosY, BattleCam_PosY, alpha);
    camera->lookAt_obj_target.z = LERP(BattleCam_InitialPosZ, BattleCam_PosZ, alpha);

    camera->params.basic.dist = LERP(BattleCam_InitialBoomLength, BattleCam_BoomLength, alpha);
    camera->params.basic.yaw = LERP(BattleCam_InitialBoomYaw, BattleCam_BoomYaw, alpha);
    camera->params.basic.pitch = LERP(BattleCam_InitialBoomPitch, BattleCam_BoomPitch, alpha);
    camera->params.basic.offsetY = LERP(BattleCam_InitialBoomOffsetY, BattleCam_BoomOffsetY, alpha) * 256.0f;

    if (BattleCam_MoveTimeLeft == 0) {
        BattleCam_DoneMoving = TRUE;
    } else {
        BattleCam_MoveTimeLeft--;
    }

    return ApiStatus_BLOCK;
}

/// Continuously interp camera y-position to match BattleCam_SubjectActor
/// Y position cannot decrease below its initial value
API_CALLABLE(BattleCam_Update_FollowActorY) {
    Camera* camera = &gCameras[CAM_BATTLE];
    s32 screenX, screenY, screenZ;
    f32 delta;
    f32 actorY;
    s32 actorID;
    s32 actorClass;

    if (isInitialCall) {
        BattleCam_PosX = camera->lookAt_obj_target.x;
        BattleCam_PosY = camera->lookAt_obj_target.y;
        BattleCam_PosZ = camera->lookAt_obj_target.z;

        BattleCam_InitialBoomYaw = camera->params.basic.yaw;
        BattleCam_InitialBoomPitch = camera->params.basic.pitch;
    }

    actorClass = BattleCam_SubjectActor & ACTOR_CLASS_MASK;
    actorID = BattleCam_SubjectActor & 0xFF;

    switch (actorClass) {
        case ACTOR_CLASS_PLAYER:
            if (gBattleStatus.playerActor == NULL) {
                return ApiStatus_BLOCK;
            }
            actorY = gBattleStatus.playerActor->curPos.y + (gPlayerStatus.colliderHeight / 2);
            break;
        case ACTOR_CLASS_PARTNER:
            if (gBattleStatus.partnerActor == NULL) {
                return ApiStatus_BLOCK;
            }
            actorY = gBattleStatus.partnerActor->curPos.y;
            break;
        case ACTOR_CLASS_ENEMY:
            if (gBattleStatus.enemyActors[actorID] == NULL) {
                return ApiStatus_BLOCK;
            }
            actorY = gBattleStatus.enemyActors[actorID]->curPos.y;
            break;
    }

    get_screen_coords(CAM_BATTLE, BattleCam_PosX, actorY, BattleCam_PosZ, &screenX, &screenY, &screenZ);

    if (screenY < 100) {
        actorY += 25.0f;
    }

    if (actorY < BattleCam_PosY) {
        actorY = BattleCam_PosY;
    }

    delta = actorY - camera->lookAt_obj_target.y;
    if (fabsf(delta) < 0.01) {
        camera->lookAt_obj_target.y = actorY;
    } else {
        camera->lookAt_obj_target.y += delta / 5.0f;
    }

    return ApiStatus_BLOCK;
}

/// Continuously interp camera position to match BattleCam_SubjectActor
/// X and Y positions cannot decrease below their initial values
API_CALLABLE(BattleCam_Update_FollowActorPos) {
    Camera* camera = &gCameras[CAM_BATTLE];
    s32 actorClass = BattleCam_SubjectActor & ACTOR_CLASS_MASK;
    s32 actorID = BattleCam_SubjectActor & 0xFF;
    f32 actorX, actorY, actorZ;
    s32 screenX, screenY, screenZ;
    f32 delta;

    switch (actorClass) {
        case ACTOR_CLASS_PLAYER:
            if (gBattleStatus.playerActor == NULL) {
                return ApiStatus_BLOCK;
            }
            actorX = gBattleStatus.playerActor->curPos.x;
            actorY = gBattleStatus.playerActor->curPos.y + (gPlayerStatus.colliderHeight / 2);
            actorZ = gBattleStatus.playerActor->curPos.z;
            break;
        case ACTOR_CLASS_PARTNER:
            if (gBattleStatus.partnerActor == NULL) {
                return ApiStatus_BLOCK;
            }
            actorX = gBattleStatus.partnerActor->curPos.x;
            actorY = gBattleStatus.partnerActor->curPos.y;
            actorZ = gBattleStatus.partnerActor->curPos.z;
            break;
        case ACTOR_CLASS_ENEMY:
            if (gBattleStatus.enemyActors[actorID] == NULL) {
                return ApiStatus_BLOCK;
            }
            actorX = gBattleStatus.enemyActors[actorID]->curPos.x;
            actorY = gBattleStatus.enemyActors[actorID]->curPos.y;
            actorZ = gBattleStatus.enemyActors[actorID]->curPos.z;
            break;
    }

    if (isInitialCall) {
        BattleCam_PosX = camera->lookAt_obj_target.x;
        BattleCam_PosY = camera->lookAt_obj_target.y;
        BattleCam_PosZ = camera->lookAt_obj_target.z;

        BattleCam_InitialBoomYaw = camera->params.basic.yaw;
        BattleCam_InitialBoomPitch = camera->params.basic.pitch;
    }

    get_screen_coords(CAM_BATTLE, actorX, actorY, actorZ, &screenX, &screenY, &screenZ);

    if (screenY < 100) {
        actorY += 25.0f;
    }
    if (actorY < BattleCam_PosY) {
        actorY = BattleCam_PosY;
    }

    if (screenX < 100) {
        actorX -= 25.0f;
    }
    if (actorX < BattleCam_PosX) {
        actorX = BattleCam_PosX;
    }
    if (screenX > 220) {
        actorX += 25.0f;
    }

    delta = actorX - camera->lookAt_obj_target.x;
    if (fabsf(delta) < 0.01) {
        camera->lookAt_obj_target.x = actorX;
    } else {
        camera->lookAt_obj_target.x += delta / 5.0f;
    }

    delta = actorY - camera->lookAt_obj_target.y;
    if (fabsf(delta) < 0.01) {
        camera->lookAt_obj_target.y = actorY;
    } else {
        camera->lookAt_obj_target.y += delta / 5.0f;
    }

    delta = actorZ - camera->lookAt_obj_target.z;
    if (fabsf(delta) < 0.01) {
        camera->lookAt_obj_target.z = actorZ;
    } else {
        camera->lookAt_obj_target.z += delta / 5.0f;
    }

    return ApiStatus_BLOCK;
}

API_CALLABLE(BattleCam_Init) {
    Camera* camera = &gCameras[CAM_BATTLE];
    camera->params.basic.yaw = 0;
    camera->params.basic.offsetY = 0;

    BattleCam_BoomPitch = 8;
    BattleCam_BoomYaw = 0;
    BattleCam_BoomOffsetY = 0;

    BattleCam_IsFrozen = FALSE;

    BattleCam_InitialBoomLength = camera->params.basic.dist;
    BattleCam_InitialBoomPitch = camera->params.basic.pitch;
    BattleCam_InitialBoomOffsetY = BattleCam_InitialBoomYaw = 0.0f;
    return ApiStatus_DONE2;
}

EvtScript EVS_BattleCam_Interrupt = {
    Call(BattleCam_Update_Interrupt)
    Return
    End
};

EvtScript EVS_BattleCam_FocusMidpointA = {
    Call(BattleCam_Update_FocusMidpointA)
    Return
    End
};

EvtScript EVS_BattleCam_FocusMidpointB = {
    Call(BattleCam_Update_FocusMidpointB)
    Return
    End
};

EvtScript EVS_BattleCam_FocusActorPart = {
    Call(BattleCam_Update_FocusActorPart)
    Return
    End
};

EvtScript EVS_BattleCam_FocusActor = {
    Call(BattleCam_Update_FocusActor)
    Return
    End
};

EvtScript EVS_BattleCam_FocusGoal = {
    Call(BattleCam_Update_FocusGoal)
    Return
    End
};

EvtScript EVS_BattleCam_SimpleLerp_Unskippable = {
    Call(BattleCam_Update_SimpleLerp_Unskippable)
    Return
    End
};

EvtScript EVS_BattleCam_ResetNeutral = {
    Call(BattleCam_Update_ResetToNeutral_Skippable)
    Return
    End
};

EvtScript EVS_BattleCam_ViewEnemies = {
    Call(BattleCam_Update_ViewAllEnemies)
    Return
    End
};

EvtScript EVS_BattleCam_ViewEnemies_MaintainY = {
    Call(BattleCam_Update_ViewAllEnemies_MaintainY)
    Return
    End
};

EvtScript EVS_BattleCam_SimpleLerp_Skippable = {
    Call(BattleCam_Update_SimpleLerp_Skippable)
    Return
    End
};

EvtScript EVS_BattleCam_FollowActorY = {
    Call(BattleCam_Update_FollowActorY)
    Return
    End
};

EvtScript EVS_BattleCam_FollowActorPos = {
    Call(BattleCam_Update_FollowActorPos)
    Return
    End
};

EvtScript EVS_BattleCam_Reset = {
    Call(ForceBattleCamTarget, 0, 15, 0)
    Call(SetBattleCamParam, CAM_PARAM_BOOM_LENGTH, 550)
    Call(SetBattleCamParam, CAM_PARAM_FOV_SCALE, 100)
    Call(SetBattleCamParam, CAM_PARAM_BOOM_PITCH, 8)
    Return
    End
};

EvtScript EVS_OnBattleInit = {
    Call(SetCamPerspective, CAM_BATTLE, CAM_UPDATE_NO_INTERP, 25, 16, 1024)
    Call(SetCamViewport, CAM_BATTLE, 12, 20, 296, 200)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Call(SetCamEnabled, CAM_BATTLE, TRUE)
    Wait(1)
    Call(InitVirtualEntityList)
    Call(InitAnimatedModels)
    Call(SetNoInterpCamParams, CAM_BATTLE, FALSE, 240, 100, 8)
    Call(SetCamLookTarget, CAM_BATTLE, -75, 35, 0)
    Call(BattleCamTargetActor, 0)
    Call(BattleCam_Init)
    Return
    End
};

void btl_cam_use_preset_impl(s32 id) {
    EvtScript* preset = NULL;
    Evt* newScript;

    if (BattleCam_IsFrozen) {
        return;
    }

    BattleCam_ClampPosX = TRUE;
    BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_NONE;
    BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_NONE;
    BattleCam_UseLinearInterp = FALSE;
    BattleCam_ExtraOffsetX = 0;

    switch (id) {
        case BTL_CAM_RESET:
            preset = &EVS_BattleCam_Reset;
            break;
        case BTL_CAM_INTERRUPT:
            preset = &EVS_BattleCam_Interrupt;
            break;
        case BTL_CAM_DEFAULT:
            if (BattleCam_CurrentPresetID == id) {
                return;
            }
            BattleCam_BoomLength = 500;
            BattleCam_MoveTimeLeft = 30;
            preset = &EVS_BattleCam_ResetNeutral;
            break;
        case BTL_CAM_VIEW_ENEMIES:
            if (BattleCam_CurrentPresetID == id) {
                return;
            }
            BattleCam_BoomLength = 480;
            BattleCam_BoomOffsetY = 0;
            BattleCam_MoveTimeLeft = 20;
            preset = &EVS_BattleCam_ViewEnemies;
            break;
        case BTL_CAM_RETURN_HOME:
            if (BattleCam_CurrentPresetID == id) {
                return;
            }
            BattleCam_BoomLength = 500;
            BattleCam_BoomOffsetY = 0;
            BattleCam_MoveTimeLeft = 10;
            preset = &EVS_BattleCam_ViewEnemies_MaintainY;
            break;
        case BTL_CAM_ACTOR_TARGET_MIDPOINT:
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_AVG;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_AVG;
            BattleCam_BoomLength = 300;
            BattleCam_MoveTimeLeft = 20;
            preset = &EVS_BattleCam_FocusMidpointA;
            break;
        case BTL_CAM_ACTOR_PART:
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_AVG;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_AVG;
            BattleCam_BoomLength = 300;
            BattleCam_MoveTimeLeft = 20;
            preset = &EVS_BattleCam_FocusActorPart;
            break;
        case BTL_CAM_ACTOR_GOAL_SIMPLE:
            BattleCam_BoomLength = 300;
            BattleCam_MoveTimeLeft = 20;
            preset = &EVS_BattleCam_FocusGoal;
            break;
        case BTL_CAM_ACTOR_SIMPLE:
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_AVG;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_AVG;
            BattleCam_BoomLength = 300;
            BattleCam_MoveTimeLeft = 20;
            preset = &EVS_BattleCam_FocusActor;
            break;
        case BTL_CAM_SLOW_DEFAULT:
            if (BattleCam_ControlScript == &EVS_BattleCam_ResetNeutral) {
                return;
            }
            BattleCam_BoomLength = 500;
            BattleCam_MoveTimeLeft = 120;
            preset = &EVS_BattleCam_ResetNeutral;
            break;
        case BTL_CAM_MIDPOINT_CLOSE:
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_AVG;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_AVG;
            BattleCam_BoomLength = 200;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = 15;
            BattleCam_MoveTimeLeft = 20;
            preset = &EVS_BattleCam_FocusMidpointA;
            break;
        case BTL_CAM_MIDPOINT_NORMAL:
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_AVG;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_AVG;
            BattleCam_BoomLength = 300;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = 16;
            BattleCam_MoveTimeLeft = 20;
            preset = &EVS_BattleCam_FocusMidpointA;
            break;
        case BTL_CAM_MIDPOINT_FAR:
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_AVG;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_AVG;
            BattleCam_BoomLength = 400;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = 30;
            BattleCam_MoveTimeLeft = 20;
            preset = &EVS_BattleCam_FocusMidpointA;
            break;
        case BTL_CAM_ACTOR_CLOSE:
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_AVG;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_AVG;
            BattleCam_BoomLength = 200;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = 15;
            BattleCam_MoveTimeLeft = 20;
            preset = &EVS_BattleCam_FocusActor;
            break;
        case BTL_CAM_ACTOR:
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_AVG;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_AVG;
            BattleCam_BoomLength = 300;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = 16;
            BattleCam_MoveTimeLeft = 20;
            preset = &EVS_BattleCam_FocusActor;
            break;
        case BTL_CAM_ACTOR_FAR:
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_AVG;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_AVG;
            BattleCam_BoomLength = 400;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = 30;
            BattleCam_MoveTimeLeft = 20;
            preset = &EVS_BattleCam_FocusActor;
            break;
        case BTL_CAM_ACTOR_GOAL_NEAR:
            BattleCam_BoomLength = 267;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = 23;
            BattleCam_MoveTimeLeft = 20;
            preset = &EVS_BattleCam_FocusGoal;
            break;
        case BTL_CAM_ACTOR_GOAL:
            BattleCam_BoomLength = 300;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = 8;
            BattleCam_MoveTimeLeft = 20;
            preset = &EVS_BattleCam_FocusGoal;
            break;
        case BTL_CAM_ACTOR_GOAL_FAR:
            BattleCam_BoomLength = 400;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = 0;
            BattleCam_MoveTimeLeft = 20;
            preset = &EVS_BattleCam_FocusGoal;
            break;
        case BTL_CAM_REPOSITION:
            BattleCam_MoveTimeLeft = 20;
            preset = &EVS_BattleCam_SimpleLerp_Skippable;
            break;
        case BTL_CAM_FOLLOW_ACTOR_Y:
            BattleCam_BoomOffsetY = 0;
            BattleCam_MoveTimeLeft = 20;
            preset = &EVS_BattleCam_FollowActorY;
            break;
        case BTL_CAM_FOLLOW_ACTOR_POS:
            BattleCam_BoomOffsetY = 0;
            BattleCam_MoveTimeLeft = 20;
            preset = &EVS_BattleCam_FollowActorPos;
            break;
        case BTL_CAM_PLAYER_FLEE:
            BattleCam_SubjectActor = ACTOR_PLAYER;
            BattleCam_BoomLength = 266;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = 40;
            btl_cam_set_target_pos(-80.0f, 0.0f, 0.0f);
            BattleCam_MoveTimeLeft = 20;
            preset = &EVS_BattleCam_SimpleLerp_Skippable;
            break;
        case BTL_CAM_PLAYER_DIES:
            BattleCam_SubjectActor = ACTOR_PLAYER;
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_AVG;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_AVG;
            BattleCam_BoomLength = 250;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = 14;
            BattleCam_ClampPosX = FALSE;
            BattleCam_IsFrozen = TRUE;
            BattleCam_MoveTimeLeft = 20;
            preset = &EVS_BattleCam_FocusActor;
            break;
        case BTL_CAM_VICTORY:
            BattleCam_SubjectActor = ACTOR_PLAYER;
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_NONE;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_NONE;
            BattleCam_BoomLength = 255;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = 29;
            btl_cam_set_target_pos(-95.0f, 18.0f, 10.0f);
            BattleCam_MoveTimeLeft = 20;
            preset = &EVS_BattleCam_SimpleLerp_Skippable;
            break;
        case BTL_CAM_PLAYER_ENTRY:
            BattleCam_SubjectActor = ACTOR_PLAYER;
            BattleCam_BoomLength = 230;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = 0;
            BattleCam_MoveTimeLeft = 20;
            preset = &EVS_BattleCam_SimpleLerp_Skippable;
            break;
        case BTL_CAM_PLAYER_ATTACK_APPROACH:
            BattleCam_SubjectActor = ACTOR_PLAYER;
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_AVG;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_AVG;
            BattleCam_BoomLength = 310;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = 16;
            BattleCam_ClampPosX = FALSE;
            BattleCam_MoveTimeLeft = 30;
            preset = &EVS_BattleCam_FocusMidpointB;
            break;
        case BTL_CAM_PLAYER_PRE_JUMP_FINISH:
            BattleCam_SubjectActor = ACTOR_PLAYER;
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_NONE;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_AVG;
            BattleCam_BoomLength = 320;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = 0;
            BattleCam_ClampPosX = FALSE;
            BattleCam_MoveTimeLeft = 5;
            preset = &EVS_BattleCam_FocusMidpointB;
            break;
        case BTL_CAM_PLAYER_PRE_ULTRA_JUMP_FINISH:
            BattleCam_SubjectActor = ACTOR_PLAYER;
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_NONE;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_AVG;
            BattleCam_BoomLength = 340;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = 0;
            BattleCam_ClampPosX = FALSE;
            BattleCam_MoveTimeLeft = 5;
            preset = &EVS_BattleCam_FocusMidpointB;
            break;
        case BTL_CAM_PLAYER_HIT_SPIKE:
        case BTL_CAM_PLAYER_HIT_HAZARD:
            BattleCam_SubjectActor = ACTOR_PLAYER;
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_AVG;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_AVG;
            BattleCam_BoomLength = 300;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = -32;
            BattleCam_ExtraOffsetX = 20;
            BattleCam_MoveTimeLeft = 15;
            preset = &EVS_BattleCam_FocusActor;
            break;
        case BTL_CAM_PLAYER_CHARGE_UP:
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_NONE;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_NONE;
            BattleCam_PosX = -65.0f;
            BattleCam_PosY = 30.0f;
            BattleCam_PosZ = 0.0f;
            BattleCam_BoomLength = 300;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = 10;
            BattleCam_MoveTimeLeft = 10;
            preset = &EVS_BattleCam_SimpleLerp_Unskippable;
            break;
        case BTL_CAM_PLAYER_STATUS_AFFLICTED:
            BattleCam_SubjectActor = ACTOR_PLAYER;
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_AVG;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_AVG;
            BattleCam_BoomLength = 220;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = 24;
            BattleCam_ClampPosX = FALSE;
            BattleCam_MoveTimeLeft = 30;
            preset = &EVS_BattleCam_FocusActor;
            break;
        case BTL_CAM_PLAYER_JUMP_MIDAIR:
            BattleCam_SubjectActor = ACTOR_PLAYER;
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_NONE;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_AVG;
            BattleCam_BoomLength = 280;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = -4;
            BattleCam_ClampPosX = FALSE;
            BattleCam_MoveTimeLeft = 30;
            preset = &EVS_BattleCam_FocusMidpointB;
            break;
        case BTL_CAM_PLAYER_JUMP_FINISH:
            BattleCam_SubjectActor = ACTOR_PLAYER;
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_NONE;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_AVG;
            BattleCam_BoomLength = 380;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = 0;
            BattleCam_ClampPosX = FALSE;
            BattleCam_UseLinearInterp = TRUE;
            BattleCam_MoveTimeLeft = 60;
            preset = &EVS_BattleCam_FocusMidpointB;
            break;
        case BTL_CAM_PLAYER_JUMP_FINISH_CLOSE:
            BattleCam_SubjectActor = ACTOR_PLAYER;
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_NONE;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_AVG;
            BattleCam_BoomLength = 300;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = 0;
            BattleCam_ClampPosX = FALSE;
            BattleCam_UseLinearInterp = TRUE;
            BattleCam_MoveTimeLeft = 60;
            preset = &EVS_BattleCam_FocusMidpointB;
            break;
        case BTL_CAM_PLAYER_SUPER_JUMP_MIDAIR:
        case BTL_CAM_PLAYER_ULTRA_JUMP_MIDAIR:
            BattleCam_SubjectActor = ACTOR_PLAYER;
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_NONE;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_AVG;
            BattleCam_BoomLength = 320;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = -4;
            BattleCam_ClampPosX = FALSE;
            BattleCam_MoveTimeLeft = 30;
            preset = &EVS_BattleCam_FocusMidpointB;
            break;
        case BTL_CAM_PLAYER_UNUSED_ULTRA_JUMP:
            BattleCam_SubjectActor = ACTOR_PLAYER;
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_NONE;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_AVG;
            BattleCam_BoomLength = 320;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = 0;
            BattleCam_ClampPosX = FALSE;
            BattleCam_MoveTimeLeft = 30;
            preset = &EVS_BattleCam_FocusMidpointB;
            break;
        case BTL_CAM_PLAYER_MULTIBOUNCE:
            BattleCam_SubjectActor = ACTOR_PLAYER;
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_AVG;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_AVG;
            BattleCam_BoomLength = 360;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = -4;
            BattleCam_ClampPosX = FALSE;
            BattleCam_MoveTimeLeft = 20;
            preset = &EVS_BattleCam_FocusMidpointB;
            break;
        case BTL_CAM_PRESET_UNUSED_29:
        case BTL_CAM_PRESET_UNUSED_2A:
            BattleCam_BoomLength = 200;
            BattleCam_MoveTimeTotal = 7;
            BattleCam_DoneMoving = FALSE;
            BattleCam_ClampPosX = FALSE;
            BattleCam_MoveTimeLeft = 7;
            preset = BattleCam_ControlScript;
            break;
        case BTL_CAM_PLAYER_AIM_HAMMER:
            BattleCam_SubjectActor = ACTOR_PLAYER;
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_AVG;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_SLIGHT;
            BattleCam_BoomLength = 214;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = 16;
            BattleCam_ClampPosX = FALSE;
            BattleCam_MoveTimeLeft = 20;
            preset = &EVS_BattleCam_FocusMidpointB;
            break;
        case BTL_CAM_PLAYER_HAMMER_STRIKE:
            BattleCam_SubjectActor = ACTOR_PLAYER;
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_AVG;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_NONE;
            BattleCam_BoomLength = 300;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = 16;
            BattleCam_ClampPosX = FALSE;
            BattleCam_MoveTimeLeft = 8;
            preset = &EVS_BattleCam_FocusMidpointB;
            break;
        case BTL_CAM_PRESET_UNUSED_2D:
            BattleCam_SubjectActor = ACTOR_PLAYER;
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_NONE;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_NONE;
            BattleCam_PosX = 60.0f;
            BattleCam_PosY = 40.0f;
            BattleCam_PosZ = 0.0f;
            BattleCam_BoomLength = 430;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = 16;
            BattleCam_MoveTimeLeft = 10;
            preset = &EVS_BattleCam_SimpleLerp_Unskippable;
            break;
        case BTL_CAM_PLAYER_HAMMER_QUAKE:
            BattleCam_SubjectActor = ACTOR_PLAYER;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_NONE;
            BattleCam_PosX = 60.0f;
            BattleCam_PosY = 40.0f;
            BattleCam_PosZ = 0.0f;
            BattleCam_BoomLength = 460;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = 27;
            BattleCam_MoveTimeLeft = 10;
            preset = &EVS_BattleCam_SimpleLerp_Unskippable;
            break;
        case BTL_CAM_PRESET_UNUSED_46:
            BattleCam_BoomLength = 390;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = 45;
            btl_cam_set_target_pos(-70.0f, 0.0f, 0.0f);
            BattleCam_ClampPosX = FALSE;
            BattleCam_MoveTimeLeft = 10;
            preset = &EVS_BattleCam_SimpleLerp_Skippable;
            break;
        case BTL_CAM_PRESET_UNUSED_47:
            BattleCam_BoomLength = 500;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = 45;
            btl_cam_set_target_pos(0.0f, 0.0f, 0.0f);
            BattleCam_ClampPosX = FALSE;
            BattleCam_MoveTimeLeft = 40;
            preset = &EVS_BattleCam_SimpleLerp_Skippable;
            break;
        case BTL_CAM_PLAYER_WISH:
        case BTL_CAM_PRESET_UNUSED_48:
            BattleCam_BoomLength = 300;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = 45;
            btl_cam_set_target_pos(-50.0f, 0.0f, 0.0f);
            BattleCam_ClampPosX = FALSE;
            BattleCam_MoveTimeLeft = 20;
            preset = &EVS_BattleCam_SimpleLerp_Skippable;
            break;
        case BTL_CAM_STAR_SPIRIT:
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_NONE;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_NONE;
            BattleCam_PosX = -75.0f;
            BattleCam_PosY = 150.0f;
            BattleCam_PosZ = 0.0f;
            BattleCam_BoomLength = 166;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = 17;
            BattleCam_MoveTimeLeft = 1;
            preset = &EVS_BattleCam_SimpleLerp_Unskippable;
            break;
        case BTL_CAM_PARTNER_APPROACH:
            BattleCam_SubjectActor = ACTOR_PARTNER;
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_AVG;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_AVG;
            BattleCam_BoomLength = 310;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = 16;
            BattleCam_ClampPosX = FALSE;
            BattleCam_MoveTimeLeft = 30;
            preset = &EVS_BattleCam_FocusMidpointB;
            break;
        case BTL_CAM_CLOSER_PARTNER_APPROACH:
            BattleCam_SubjectActor = ACTOR_PARTNER;
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_AVG;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_AVG;
            BattleCam_BoomLength = 250;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = 16;
            BattleCam_ClampPosX = FALSE;
            BattleCam_UseLinearInterp = TRUE;
            BattleCam_MoveTimeLeft = 120;
            preset = &EVS_BattleCam_FocusMidpointB;
            break;
        case BTL_CAM_PRESET_UNUSED_31:
            BattleCam_SubjectActor = ACTOR_PARTNER;
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_AVG;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_AVG;
            BattleCam_BoomLength = 300;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = 16;
            BattleCam_ClampPosX = FALSE;
            BattleCam_UseLinearInterp = TRUE;
            BattleCam_MoveTimeLeft = 120;
            preset = &EVS_BattleCam_FocusActor;
            break;
        case BTL_CAM_GOOMBARIO_BONK_FOLLOWUP_1:
            BattleCam_SubjectActor = ACTOR_PARTNER;
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_NONE;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_AVG;
            BattleCam_BoomLength = 320;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = 0;
            BattleCam_ClampPosX = FALSE;
            BattleCam_MoveTimeLeft = 5;
            preset = &EVS_BattleCam_FocusMidpointB;
            break;
        case BTL_CAM_PLAYER_MISTAKE:
        case BTL_CAM_PARTNER_MISTAKE:
            BattleCam_BoomLength = 500;
            BattleCam_BoomOffsetY = 0;
            BattleCam_MoveTimeLeft = 50;
            preset = &EVS_BattleCam_ViewEnemies;
            break;
        case BTL_CAM_PARTNER_MIDAIR:
            BattleCam_SubjectActor = ACTOR_PARTNER;
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_NONE;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_AVG;
            BattleCam_BoomLength = 280;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = -4;
            BattleCam_ClampPosX = FALSE;
            BattleCam_MoveTimeLeft = 30;
            preset = &EVS_BattleCam_FocusMidpointB;
            break;
        case BTL_CAM_GOOMBARIO_BONK_FOLLOWUP_2:
            BattleCam_SubjectActor = ACTOR_PARTNER;
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_NONE;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_AVG;
            BattleCam_BoomLength = 380;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = 0;
            BattleCam_ClampPosX = FALSE;
            BattleCam_UseLinearInterp = TRUE;
            BattleCam_MoveTimeLeft = 60;
            preset = &EVS_BattleCam_FocusMidpointB;
            break;
        case BTL_CAM_PARTNER_INJURED:
            BattleCam_SubjectActor = ACTOR_PARTNER;
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_AVG;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_AVG;
            BattleCam_BoomLength = 220;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = 24;
            BattleCam_ClampPosX = FALSE;
            BattleCam_MoveTimeLeft = 30;
            preset = &EVS_BattleCam_FocusActor;
            break;
        case BTL_CAM_PARTNER_GOOMPA:
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_NONE;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_NONE;
            BattleCam_PosX = -95.0f;
            BattleCam_PosY = 22.0f;
            BattleCam_PosZ = 0.0f;
            BattleCam_BoomLength = 210;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = 10;
            BattleCam_MoveTimeLeft = 20;
            preset = &EVS_BattleCam_SimpleLerp_Unskippable;
            break;
        case BTL_CAM_PRESET_UNUSED_38:
            BattleCam_SubjectActor = ACTOR_PARTNER;
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_NONE;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_AVG;
            BattleCam_BoomLength = 320;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = -4;
            BattleCam_MoveTimeLeft = 30;
            preset = &EVS_BattleCam_FocusMidpointB;
            break;
        case BTL_CAM_PRESET_UNUSED_39:
            BattleCam_SubjectActor = ACTOR_PARTNER;
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_NONE;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_AVG;
            BattleCam_BoomLength = 320;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = 0;
            BattleCam_MoveTimeLeft = 30;
            preset = &EVS_BattleCam_FocusMidpointB;
            break;
        case BTL_CAM_PRESET_UNUSED_3A:
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_NONE;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_NONE;
            BattleCam_PosX = 25.0f;
            BattleCam_PosY = 60.0f;
            BattleCam_PosZ = 0.0f;
            BattleCam_BoomLength = 400;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = 10;
            BattleCam_MoveTimeLeft = 30;
            preset = &EVS_BattleCam_SimpleLerp_Unskippable;
            break;
        case BTL_CAM_PARTNER_CLOSE_UP:
            BattleCam_SubjectActor = ACTOR_PARTNER;
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_AVG;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_AVG;
            BattleCam_BoomLength = 200;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = 11;
            BattleCam_ClampPosX = FALSE;
            BattleCam_UseLinearInterp = TRUE;
            BattleCam_MoveTimeLeft = 60;
            preset = &EVS_BattleCam_FocusActor;
            break;
        case BTL_CAM_PRESET_UNUSED_3C:
            BattleCam_SubjectActor = ACTOR_PARTNER;
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_NONE;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_NONE;
            BattleCam_BoomLength = 300;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = 16;
            BattleCam_MoveTimeLeft = 8;
            preset = &EVS_BattleCam_FocusActor;
            break;
        case BTL_CAM_PARTNER_HIT_SPIKE:
        case BTL_CAM_PARTNER_HIT_HAZARD:
            BattleCam_SubjectActor = ACTOR_PARTNER;
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_AVG;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_AVG;
            BattleCam_BoomLength = 300;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = -32;
            BattleCam_ExtraOffsetX = 20;
            BattleCam_MoveTimeLeft = 15;
            preset = &EVS_BattleCam_FocusActor;
            break;
        case BTL_CAM_ENEMY_APPROACH:
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_AVG;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_AVG;
            BattleCam_BoomLength = 400;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = 27;
            BattleCam_MoveTimeLeft = 20;
            preset = &EVS_BattleCam_FocusMidpointA;
            break;
        case BTL_CAM_PRESET_UNUSED_40:
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_NONE;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_AVG;
            BattleCam_BoomLength = 358;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = 16;
            BattleCam_MoveTimeLeft = 10;
            preset = &EVS_BattleCam_FocusMidpointA;
            break;
        case BTL_CAM_SLOWER_DEFAULT:
            BattleCam_BoomLength = 500;
            BattleCam_MoveTimeLeft = 50;
            preset = &EVS_BattleCam_ResetNeutral;
            break;
        case BTL_CAM_ENEMY_DIVE:
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_NONE;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_AVG;
            BattleCam_BoomLength = 267;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = 16;
            BattleCam_MoveTimeLeft = 20;
            preset = &EVS_BattleCam_FocusMidpointA;
            break;
        case BTL_CAM_PRESET_UNUSED_43:
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_AVG;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_AVG;
            BattleCam_BoomLength = 214;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomYaw = 0;
            BattleCam_BoomOffsetY = 16;
            BattleCam_MoveTimeLeft = 20;
            preset = &EVS_BattleCam_FocusMidpointA;
            break;
        case BTL_CAM_PRESET_UNUSED_44:
            BattleCam_AdjustTargetXMode = BTL_CAM_XADJ_AVG;
            BattleCam_AdjustTargetYMode = BTL_CAM_YADJ_AVG;
            BattleCam_BoomLength = 300;
            BattleCam_BoomPitch = 8;
            BattleCam_BoomOffsetY = 16;
            BattleCam_BoomYaw = 0;
            BattleCam_MoveTimeLeft = 4;
            preset = &EVS_BattleCam_FocusMidpointA;
            break;
    }

    BattleCam_CurrentPresetID = id;

    if (gBattleStatus.camMovementScript != NULL) {
        kill_script_by_ID(gBattleStatus.camMovementScriptID);
    }

    BattleCam_ControlScript = preset;
    newScript = start_script(preset, EVT_PRIORITY_A, EVT_FLAG_RUN_IMMEDIATELY);
    gBattleStatus.camMovementScript = newScript;
    gBattleStatus.camMovementScriptID = newScript->id;
    BattleCam_DoneMoving = FALSE;
}

void btl_cam_use_preset_immediately(s32 preset) {
    if (!BattleCam_IsFrozen) {
        BattleCam_SetImmediately = TRUE;
        btl_cam_use_preset_impl(preset);
    }
}

void btl_cam_use_preset(s32 preset) {
    if (!BattleCam_IsFrozen) {
        BattleCam_SetImmediately = FALSE;
        btl_cam_use_preset_impl(preset);
    }
}

void btl_cam_target_actor(s32 actorID) {
    if (!BattleCam_IsFrozen) {
        BattleCam_SubjectActor = actorID;
    }
}

void btl_cam_target_actor_part(s32 actorID, s32 actorPartIndex) {
    if (!BattleCam_IsFrozen) {
        BattleCam_SubjectActor = actorID;
        BattleCam_SubjectActorPart = actorPartIndex;
    }
}

void btl_cam_set_params(b16 skipRecalc, s16 boomLength, s16 vfovScale, s16 boomPitch, s32 boomYaw, s32 boomZOffset, s32 zoomPercent) {
    Camera* camera = &gCameras[CAM_BATTLE];

    if (!BattleCam_IsFrozen) {
        camera->params.basic.skipRecalc = skipRecalc;
        camera->params.basic.dist = boomLength;
        camera->params.basic.fovScale = vfovScale;
        camera->params.basic.pitch = boomPitch;
        camera->params.basic.yaw = boomYaw;
        camera->params.basic.offsetY = boomZOffset * 256;
        camera->params.basic.zoomPercent = zoomPercent;
    }
}

void btl_cam_move(s16 moveTime) {
    if (!BattleCam_IsFrozen) {
        BattleCam_MoveTimeLeft = moveTime;
        if (gBattleStatus.camMovementScript != NULL) {
            restart_script(gBattleStatus.camMovementScript);
        }
    }
}

void btl_cam_set_target_pos(f32 x, f32 y, f32 z) {
    if (!BattleCam_IsFrozen) {
        BattleCam_PosX = x;
        BattleCam_PosY = y;
        BattleCam_PosZ = z;
    }
}

void btl_cam_set_pos(f32 x, f32 y, f32 z) {
    Camera* camera = &gCameras[CAM_BATTLE];

    if (!BattleCam_IsFrozen) {
        camera->lookAt_obj_target.x = x;
        camera->lookAt_obj_target.y = y;
        camera->lookAt_obj_target.z = z;
    }
}

s32 btl_cam_is_moving_done(void) {
    return BattleCam_DoneMoving;
}

void btl_cam_set_zoom(s16 zoom) {
    if (!BattleCam_IsFrozen) {
        BattleCam_BoomLength = zoom;
    }
}

void btl_cam_add_zoom(s32 zoom) {
    if (!BattleCam_IsFrozen) {
        BattleCam_BoomLength += zoom;
    }
}

void btl_cam_set_zoffset(s16 zOffset) {
    if (!BattleCam_IsFrozen) {
        BattleCam_BoomOffsetY = zOffset;
    }
}

void btl_cam_unfreeze(void) {
    BattleCam_IsFrozen = FALSE;
}

void btl_cam_disable_clamp_x(void) {
    BattleCam_ClampPosX = FALSE;
}

API_CALLABLE(UseBattleCamPreset) {
    Bytecode* args = script->ptrReadPos;
    s32 preset;

    if (BattleCam_IsFrozen) {
        return ApiStatus_DONE2;
    }

    preset = evt_get_variable(script, *args++);
    BattleCam_SetImmediately = FALSE;
    btl_cam_use_preset_impl(preset);

    return ApiStatus_DONE2;
}

API_CALLABLE(UseBattleCamPresetImmediately) {
    Bytecode* args = script->ptrReadPos;
    s32 preset;

    if (BattleCam_IsFrozen) {
        return ApiStatus_DONE2;
    }

    preset = evt_get_variable(script, *args++);
    BattleCam_SetImmediately = TRUE;
    btl_cam_use_preset_impl(preset);

    return ApiStatus_DONE2;
}

API_CALLABLE(UseBattleCamPresetWait) {
    Bytecode* args = script->ptrReadPos;

    if (BattleCam_IsFrozen) {
        return ApiStatus_DONE2;
    }

    if (isInitialCall) {
        s32 preset = evt_get_variable(script, *args++);
        btl_cam_use_preset(preset);
        return ApiStatus_BLOCK;
    }

    if (btl_cam_is_moving_done()) {
        return ApiStatus_DONE2;
    } else {
        return ApiStatus_BLOCK;
    }
}

API_CALLABLE(SetBattleCamParam) {
    Camera* camera = &gCameras[CAM_BATTLE];
    Bytecode* args = script->ptrReadPos;
    s32 mode;
    s32 val;

    if (BattleCam_IsFrozen) {
        return ApiStatus_DONE2;
    }

    mode = evt_get_variable(script, *args++);
    val = evt_get_variable(script, *args++);

    switch (mode) {
        case CAM_PARAM_SKIP_RECALC:
            camera->params.basic.skipRecalc = val;
            break;
        case CAM_PARAM_BOOM_LENGTH:
            camera->params.basic.dist = val;
            break;
        case CAM_PARAM_FOV_SCALE:
            camera->params.basic.fovScale = val;
            break;
        case CAM_PARAM_BOOM_PITCH:
            camera->params.basic.pitch = val;
            break;
        case CAM_PARAM_BOOM_YAW:
            camera->params.basic.yaw = val;
            break;
        case CAM_PARAM_BOOM_Y_OFFSET:
            camera->params.basic.offsetY = val * 256;
            break;
        case CAM_PARAM_ZOOM_PERCENT:
            camera->params.basic.zoomPercent = val;
            break;
    }
    return ApiStatus_DONE2;
}

API_CALLABLE(SetBattleCamParams) {
    Bytecode* args = script->ptrReadPos;
    Camera* camera = &gCameras[CAM_BATTLE];

    if (BattleCam_IsFrozen) {
        return ApiStatus_DONE2;
    }

    camera->params.basic.skipRecalc = evt_get_variable(script, *args++);
    camera->params.basic.dist = evt_get_variable(script, *args++);
    camera->params.basic.fovScale = evt_get_variable(script, *args++);
    camera->params.basic.pitch = evt_get_variable(script, *args++);
    camera->params.basic.yaw = evt_get_variable(script, *args++);
    camera->params.basic.offsetY = evt_get_variable(script, *args++) * 256;
    camera->params.basic.zoomPercent = evt_get_variable(script, *args++);

    return ApiStatus_DONE2;
}

API_CALLABLE(SetBattleCamTarget) {
    Bytecode* args = script->ptrReadPos;

    if (BattleCam_IsFrozen) {
        return ApiStatus_DONE2;
    }

    BattleCam_PosX = evt_get_variable(script, *args++);
    BattleCam_PosY = evt_get_variable(script, *args++);
    BattleCam_PosZ = evt_get_variable(script, *args++);
    return ApiStatus_DONE2;
}

API_CALLABLE(ForceBattleCamTarget) {
    Bytecode* args = script->ptrReadPos;
    Camera* camera = &gCameras[CAM_BATTLE];

    if (BattleCam_IsFrozen) {
        return ApiStatus_DONE2;
    }

    camera->lookAt_obj_target.x = evt_get_variable(script, *args++);
    camera->lookAt_obj_target.y = evt_get_variable(script, *args++);
    camera->lookAt_obj_target.z = evt_get_variable(script, *args++);

    return ApiStatus_DONE2;
}

API_CALLABLE(SetBattleCamOffsetY) {
    Bytecode* args = script->ptrReadPos;

    if (BattleCam_IsFrozen) {
        return ApiStatus_DONE2;
    }

    BattleCam_BoomOffsetY = evt_get_variable(script, *args++);
    return ApiStatus_DONE2;
}

API_CALLABLE(AddBattleCamOffsetY) {
    Bytecode* args = script->ptrReadPos;

    if (BattleCam_IsFrozen) {
        return ApiStatus_DONE2;
    }

    BattleCam_BoomOffsetY += evt_get_variable(script, *args++);
    return ApiStatus_DONE2;
}

API_CALLABLE(SetBattleCamYaw) {
    Bytecode* args = script->ptrReadPos;

    if (BattleCam_IsFrozen) {
        return ApiStatus_DONE2;
    }

    BattleCam_BoomYaw = evt_get_variable(script, *args++);
    return ApiStatus_DONE2;
}

API_CALLABLE(BattleCamTargetActor) {
    Bytecode* args = script->ptrReadPos;
    s32 actorID;

    if (BattleCam_IsFrozen) {
        return ApiStatus_DONE2;
    }

    actorID = evt_get_variable(script, *args++);

    if (actorID == ACTOR_SELF) {
        actorID = script->owner1.actorID;
    }

    btl_cam_target_actor(actorID);

    return ApiStatus_DONE2;
}

API_CALLABLE(BattleCamTargetActorPart) {
    Bytecode* args = script->ptrReadPos;
    s32 actorID;

    if (BattleCam_IsFrozen) {
        return ApiStatus_DONE2;
    }

    actorID = evt_get_variable(script, *args++);

    if (actorID == ACTOR_SELF) {
        actorID = script->owner1.actorID;
    }

    btl_cam_target_actor_part(actorID, evt_get_variable(script, *args++));

    return ApiStatus_DONE2;
}

API_CALLABLE(MoveBattleCamOver) {
    Bytecode* args = script->ptrReadPos;

    if (BattleCam_IsFrozen) {
        return ApiStatus_DONE2;
    }

    BattleCam_MoveTimeLeft = evt_get_variable(script, *args++);
    BattleCam_CurrentPresetID = BTL_CAM_RESET;

    if (gBattleStatus.camMovementScript != NULL) {
        restart_script(gBattleStatus.camMovementScript);
    }

    return ApiStatus_DONE2;
}

API_CALLABLE(SetBattleCamDist) {
    Bytecode* args = script->ptrReadPos;

    if (BattleCam_IsFrozen) {
        return ApiStatus_DONE2;
    }

    BattleCam_BoomLength = evt_get_variable(script, *args++);
    return ApiStatus_DONE2;
}

API_CALLABLE(AddBattleCamDist) {
    Bytecode* args = script->ptrReadPos;

    if (BattleCam_IsFrozen) {
        return ApiStatus_DONE2;
    }

    BattleCam_BoomLength += evt_get_variable(script, *args++);
    return ApiStatus_DONE2;
}

API_CALLABLE(SetBattleCamTargetingModes) {
    Bytecode* args = script->ptrReadPos;

    if (BattleCam_IsFrozen) {
        return ApiStatus_DONE2;
    }

    BattleCam_AdjustTargetYMode = evt_get_variable(script, *args++);
    BattleCam_AdjustTargetXMode = evt_get_variable(script, *args++);
    BattleCam_UseLinearInterp = evt_get_variable(script, *args++);
    return ApiStatus_DONE2;
}

API_CALLABLE(FreezeBattleCam) {
    BattleCam_IsFrozen = evt_get_variable(script, *script->ptrReadPos);
    return ApiStatus_DONE2;
}

API_CALLABLE(DisableBattleCamClampX) {
    BattleCam_ClampPosX = FALSE;
    return ApiStatus_DONE2;
}
