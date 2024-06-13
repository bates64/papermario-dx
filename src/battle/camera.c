#include "common.h"
#include "script_api/battle.h"
#include "dx/debug_menu.h"

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
static s16 BattleCam_BoomZOffset;
static f32 BattleCam_InitialBoomLength;
static f32 BattleCam_InitialBoomYaw;
static f32 BattleCam_InitialBoomPitch;
static f32 BattleCam_InitialBoomZOffset;
static b8 BattleCam_DoneMoving;
static s16 BattleCam_MoveTimeLeft;
static s16 BattleCam_MoveTimeTotal;
static s8 BattleCam_ModeX;
static s8 BattleCam_ModeY;
static b8 BattleCam_SetImmediately;
static b8 BattleCam_UseLinearInterp;
static b8 BattleCam_ClampPosX;
static s8 BattleCam_SpecialOffsetX;
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
            switch (BattleCam_ModeY) {
                case BTL_CAM_MODEY_MINUS_2:
                    subjects->avgPos.y = subjects->actorPos.y - deltaY / 4;
                    break;
                case BTL_CAM_MODEY_MINUS_1:
                    subjects->avgPos.y = subjects->targetPos.y;
                    break;
                case BTL_CAM_MODEY_0:
                    subjects->avgPos.y = subjects->actorPos.y;
                    break;
                case BTL_CAM_MODEY_1:
                    subjects->avgPos.y = subjects->targetPos.y + deltaY / 2 + deltaY / 6;
                    break;
            }
            break;
        case ACTOR_CLASS_PARTNER:
            switch (BattleCam_ModeY) {
                case BTL_CAM_MODEY_MINUS_1:
                    subjects->avgPos.y = subjects->targetPos.y;
                    break;
                case BTL_CAM_MODEY_0:
                    subjects->avgPos.y = subjects->actorPos.y;
                    break;
                case BTL_CAM_MODEY_1:
                    subjects->avgPos.y = subjects->targetPos.y + deltaY / 2 + deltaY / 6;
                    break;
            }
            break;
        case ACTOR_CLASS_ENEMY:
            switch (BattleCam_ModeY) {
                case BTL_CAM_MODEY_MINUS_2:
                    subjects->avgPos.y = subjects->actorPos.y;
                    break;
                case BTL_CAM_MODEY_MINUS_1:
                    subjects->avgPos.y = subjects->targetPos.y;
                    break;
                case BTL_CAM_MODEY_0:
                    subjects->avgPos.y = subjects->actorPos.y;
                    break;
                case BTL_CAM_MODEY_1:
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

API_CALLABLE(CamPresetUpdate_F) {
    Camera* camera = &gCameras[CAM_BATTLE];
    CamSubjects subjects;
    Vec3f prevPos;
    f32 alpha;
    f32 distToTarget;
    f32 adjustedSize;
    f32 boomLength;
    f32 extraLength;
    f32 dist;

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

            camera->battle.auxBoomLength = BattleCam_BoomLength;
            camera->battle.auxBoomPitch = BattleCam_BoomPitch;
            camera->battle.auxBoomYaw = BattleCam_BoomYaw;
            camera->battle.auxBoomZOffset = BattleCam_BoomZOffset * 256;
        }

        BattleCam_InitialPosX = camera->lookAt_obj_target.x;
        BattleCam_InitialPosY = camera->lookAt_obj_target.y;
        BattleCam_InitialPosZ = camera->lookAt_obj_target.z;

        BattleCam_InitialBoomLength = camera->battle.auxBoomLength;
        BattleCam_InitialBoomPitch = camera->battle.auxBoomPitch;
        BattleCam_InitialBoomYaw = camera->battle.auxBoomYaw;
        BattleCam_InitialBoomZOffset = camera->battle.auxBoomZOffset / 256;

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

    dist = dist2D(camera->lookAt_obj_target.x, camera->lookAt_obj_target.z, subjects.avgPos.x, subjects.avgPos.z);
    //NOTE division by 8 here is only difference between this and CamPresetUpdate_M
    adjustedSize = (subjects.actorSizeAvg + subjects.targetSizeAvg) / 8;
    extraLength = dist + adjustedSize - 64.0f;
    distToTarget = dist3D(prevPos.z, prevPos.y, prevPos.z, subjects.targetPos.x, subjects.targetPos.y, subjects.targetPos.z);
    boomLength = BattleCam_BoomLength + extraLength + distToTarget * 0.5f;

    camera->battle.auxBoomLength = LERP(BattleCam_InitialBoomLength, boomLength, alpha);
    camera->battle.auxBoomYaw = LERP(BattleCam_InitialBoomYaw, BattleCam_BoomYaw, alpha);
    camera->battle.auxBoomPitch = LERP(BattleCam_InitialBoomPitch, BattleCam_BoomPitch, alpha);
    camera->battle.auxBoomZOffset = LERP(BattleCam_InitialBoomZOffset, BattleCam_BoomZOffset, alpha) * 256.0f;

    if (BattleCam_MoveTimeLeft == 0) {
        BattleCam_DoneMoving = TRUE;
    } else {
        BattleCam_MoveTimeLeft--;
    }

    return ApiStatus_BLOCK;
}

API_CALLABLE(CamPresetUpdate_M) {
    Camera* camera = &gCameras[CAM_BATTLE];
    CamSubjects subjects;
    Vec3f prevPos;
    f32 alpha;
    f32 distToTarget;
    f32 boomLength;
    f32 extraLength;
    f32 dist;

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

            camera->battle.auxBoomLength = BattleCam_BoomLength;
            camera->battle.auxBoomPitch = BattleCam_BoomPitch;
            camera->battle.auxBoomYaw = BattleCam_BoomYaw;
            camera->battle.auxBoomZOffset = BattleCam_BoomZOffset * 256;
        }

        BattleCam_InitialPosX = camera->lookAt_obj_target.x;
        BattleCam_InitialPosY = camera->lookAt_obj_target.y;
        BattleCam_InitialPosZ = camera->lookAt_obj_target.z;

        BattleCam_InitialBoomLength = camera->battle.auxBoomLength;
        BattleCam_InitialBoomPitch = camera->battle.auxBoomPitch;
        BattleCam_InitialBoomYaw = camera->battle.auxBoomYaw;
        BattleCam_InitialBoomZOffset = camera->battle.auxBoomZOffset / 256;

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

    dist = dist2D(camera->lookAt_obj_target.x, camera->lookAt_obj_target.z, subjects.avgPos.x, subjects.avgPos.z);
    extraLength = dist + subjects.actorSizeAvg + subjects.targetSizeAvg - 64.0f;
    distToTarget = dist3D(prevPos.z, prevPos.y, prevPos.z, subjects.targetPos.x, subjects.targetPos.y, subjects.targetPos.z);
    boomLength = BattleCam_BoomLength + extraLength + distToTarget * 0.5f;

    camera->battle.auxBoomLength = LERP(BattleCam_InitialBoomLength, boomLength, alpha);
    camera->battle.auxBoomYaw = LERP(BattleCam_InitialBoomYaw, BattleCam_BoomYaw, alpha);
    camera->battle.auxBoomPitch = LERP(BattleCam_InitialBoomPitch, BattleCam_BoomPitch, alpha);
    camera->battle.auxBoomZOffset = LERP(BattleCam_InitialBoomZOffset, BattleCam_BoomZOffset, alpha) * 256.0f;

    if (BattleCam_MoveTimeLeft == 0) {
        BattleCam_DoneMoving = TRUE;
    } else {
        BattleCam_MoveTimeLeft--;
    }

    return ApiStatus_BLOCK;
}

API_CALLABLE(CamPresetUpdate_G) {
    Camera* camera = &gCameras[CAM_BATTLE];
    CamSubjects subjects;
    ActorPart* actorPart;
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

            camera->battle.auxBoomLength = BattleCam_BoomLength;
            camera->battle.auxBoomPitch = BattleCam_BoomPitch;
            camera->battle.auxBoomYaw = BattleCam_BoomYaw;
            camera->battle.auxBoomZOffset = BattleCam_BoomZOffset * 256;
        }

        BattleCam_InitialPosX = camera->lookAt_obj_target.x;
        BattleCam_InitialPosY = camera->lookAt_obj_target.y;
        BattleCam_InitialPosZ = camera->lookAt_obj_target.z;

        BattleCam_InitialBoomLength = camera->battle.auxBoomLength;
        BattleCam_InitialBoomPitch = camera->battle.auxBoomPitch;
        BattleCam_InitialBoomYaw = camera->battle.auxBoomYaw;
        BattleCam_InitialBoomZOffset = camera->battle.auxBoomZOffset / 256;

        BattleCam_MoveTimeTotal = BattleCam_MoveTimeLeft;
    }

    alpha = (f32) BattleCam_MoveTimeLeft / BattleCam_MoveTimeTotal;
    if (!BattleCam_UseLinearInterp) {
        alpha = CUBIC_SINE_INTERP(alpha);
    }

    camera->lookAt_obj_target.x = LERP(BattleCam_InitialPosX, subjects.avgPos.x, alpha);
    camera->lookAt_obj_target.y = LERP(BattleCam_InitialPosY, subjects.avgPos.y, alpha);
    camera->lookAt_obj_target.z = LERP(BattleCam_InitialPosZ, subjects.avgPos.z, alpha);

    camera->battle.auxBoomLength = LERP(BattleCam_InitialBoomLength, BattleCam_BoomLength, alpha);
    camera->battle.auxBoomPitch = LERP(BattleCam_InitialBoomPitch, BattleCam_BoomPitch, alpha);
    camera->battle.auxBoomYaw = LERP(BattleCam_InitialBoomYaw, BattleCam_BoomYaw, alpha);
    camera->battle.auxBoomZOffset = LERP(BattleCam_InitialBoomZOffset, BattleCam_BoomZOffset, alpha) * 256.0f;

    if (BattleCam_MoveTimeLeft == 0) {
        BattleCam_DoneMoving = TRUE;
    } else {
        BattleCam_MoveTimeLeft--;
    }

    return ApiStatus_BLOCK;
}

/// Updates the battle camera to focus on BattleCam_SubjectActor.
API_CALLABLE(BattleCam_Update_FocusActor) {
    Camera* camera = &gCameras[CAM_BATTLE];
    Actor* actor;
    f32 actorX, actorY, actorZ;
    f32 actorSize;
    f32 alpha;
    f32 extraLength;
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

        BattleCam_InitialBoomLength = camera->battle.auxBoomLength;
        BattleCam_InitialBoomPitch = camera->battle.auxBoomPitch;
        BattleCam_InitialBoomYaw = camera->battle.auxBoomYaw;
        BattleCam_InitialBoomZOffset = camera->battle.auxBoomZOffset / 256;

        BattleCam_MoveTimeTotal = BattleCam_MoveTimeLeft;
    }

    alpha = (f32) BattleCam_MoveTimeLeft / BattleCam_MoveTimeTotal;
    if (!BattleCam_UseLinearInterp) {
        alpha = CUBIC_SINE_INTERP(alpha);
    }

    if (BattleCam_ModeX != BTL_CAM_MODEX_0) {
        camera->lookAt_obj_target.x = LERP(BattleCam_InitialPosX, actorX + BattleCam_SpecialOffsetX, alpha);
    }
    if (BattleCam_ModeY != BTL_CAM_MODEY_0) {
        camera->lookAt_obj_target.y = LERP(BattleCam_InitialPosY, actorY, alpha);
    }
    camera->lookAt_obj_target.z = LERP(BattleCam_InitialPosZ, actorZ, alpha);

    extraLength = actorSize - 32.0f;
    camera->battle.auxBoomLength = LERP(BattleCam_InitialBoomLength, BattleCam_BoomLength + extraLength, alpha);
    camera->battle.auxBoomYaw = LERP(BattleCam_InitialBoomYaw, BattleCam_BoomYaw, alpha);
    camera->battle.auxBoomPitch = LERP(BattleCam_InitialBoomPitch, BattleCam_BoomPitch, alpha);
    camera->battle.auxBoomZOffset = LERP(BattleCam_InitialBoomZOffset, BattleCam_BoomZOffset, alpha) * 256.0f;

    if (BattleCam_MoveTimeLeft == 0) {
        BattleCam_DoneMoving = TRUE;
    } else {
        BattleCam_MoveTimeLeft--;
    }

    return ApiStatus_BLOCK;
}

/// Updates the battle camera to focus on midpoint between BattleCam_SubjectActor and its goal position.
API_CALLABLE(BattleCam_Update_FocusGoal) {
    Camera* camera = &gCameras[CAM_BATTLE];
    s32 actorClass = BattleCam_SubjectActor & ACTOR_CLASS_MASK;
    s32 actorID = BattleCam_SubjectActor & 0xFF;
    Actor* actor;
    f32 goalX, goalY, goalZ;
    f32 averageX;
    f32 actorX, actorY;
    f32 actorSizeAvg;
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

    if (BattleCam_ModeY != BTL_CAM_MODEY_0) {
        f32 delta = actorY - goalY;
        goalY += delta / 2 + delta / 6.0f;
    }

    if (BattleCam_ModeX != BTL_CAM_MODEX_0) {
        averageX = (actorX + goalX) / 2;
        if (averageX > 75.0f) {
            averageX -= fabsf(75.0f - averageX);
        }
    }

    averageX = clamp_edge_pos_x(averageX);

    if (isInitialCall) {
        BattleCam_InitialPosX = camera->lookAt_obj_target.x;
        BattleCam_InitialPosY = camera->lookAt_obj_target.y;
        BattleCam_InitialPosZ = camera->lookAt_obj_target.z;

        BattleCam_InitialBoomLength = camera->battle.auxBoomLength;
        BattleCam_InitialBoomPitch = camera->battle.auxBoomPitch;
        BattleCam_InitialBoomYaw = camera->battle.auxBoomYaw;
        BattleCam_InitialBoomZOffset = camera->battle.auxBoomZOffset / 256;

        BattleCam_MoveTimeTotal = BattleCam_MoveTimeLeft;
    }

    alpha = (f32) BattleCam_MoveTimeLeft / BattleCam_MoveTimeTotal;
    if (!BattleCam_UseLinearInterp) {
        alpha = CUBIC_SINE_INTERP(alpha);
    }

    camera->lookAt_obj_target.x = LERP(BattleCam_InitialPosX, averageX, alpha);
    camera->lookAt_obj_target.y = LERP(BattleCam_InitialPosY, goalY, alpha);
    camera->lookAt_obj_target.z = LERP(BattleCam_InitialPosZ, goalZ, alpha);

    camera->battle.auxBoomLength = LERP(BattleCam_InitialBoomLength, BattleCam_BoomLength + actorSizeAvg - 32, alpha);
    camera->battle.auxBoomPitch = LERP(BattleCam_InitialBoomPitch, BattleCam_BoomPitch, alpha);
    camera->battle.auxBoomYaw = LERP(BattleCam_InitialBoomYaw, BattleCam_BoomYaw, alpha);
    camera->battle.auxBoomZOffset = LERP(BattleCam_InitialBoomZOffset, BattleCam_BoomZOffset, alpha) * 256.0f;

    if (BattleCam_MoveTimeLeft == 0) {
        BattleCam_DoneMoving = TRUE;
    } else {
        BattleCam_MoveTimeLeft--;
    }

    return ApiStatus_BLOCK;
}

/// lerp all parameters from current to target values
API_CALLABLE(BattleCam_Update_SimpleLerp) {
    Camera* camera = &gCameras[CAM_BATTLE];
    f32 alpha;

    if (isInitialCall) {
        BattleCam_InitialBoomLength = camera->battle.auxBoomLength;
        BattleCam_InitialBoomPitch = camera->battle.auxBoomPitch;
        BattleCam_InitialBoomYaw = camera->battle.auxBoomYaw;
        BattleCam_InitialBoomZOffset = camera->battle.auxBoomZOffset / 256;

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

    camera->battle.auxBoomLength = LERP(BattleCam_InitialBoomLength, BattleCam_BoomLength, alpha);
    camera->battle.auxBoomYaw = LERP(BattleCam_InitialBoomYaw, BattleCam_BoomYaw, alpha);
    camera->battle.auxBoomPitch = LERP(BattleCam_InitialBoomPitch, BattleCam_BoomPitch, alpha);
    camera->battle.auxBoomZOffset = LERP(BattleCam_InitialBoomZOffset, BattleCam_BoomZOffset, alpha) * 256.0f;

    if (BattleCam_MoveTimeLeft == 0) {
        BattleCam_DoneMoving = TRUE;
    } else {
        BattleCam_MoveTimeLeft--;
    }

    return ApiStatus_BLOCK;
}

/// lerp all parameters from current to default 'neutral position' values
API_CALLABLE(BattleCam_Update_ResetToNeutral) {
    Camera* camera = &gCameras[CAM_BATTLE];
    f32 alpha;

    if (isInitialCall) {
        BattleCam_PosX = 0.0f;
        BattleCam_PosY = 60.0f;
        BattleCam_PosZ = 0.0f;

        BattleCam_BoomYaw = 0;
        BattleCam_BoomPitch = 8;
        BattleCam_BoomZOffset = 0;

        if (BattleCam_SetImmediately) {
            camera->lookAt_obj_target.x = BattleCam_PosX;
            camera->lookAt_obj_target.y = BattleCam_PosY;
            camera->lookAt_obj_target.z = BattleCam_PosZ;

            camera->battle.auxBoomLength = BattleCam_BoomLength;
            camera->battle.auxBoomPitch = BattleCam_BoomPitch;
            camera->battle.auxBoomYaw = BattleCam_BoomYaw;
            camera->battle.auxBoomZOffset = BattleCam_BoomZOffset;
        }

        BattleCam_InitialBoomLength = camera->battle.auxBoomLength;
        BattleCam_InitialBoomPitch = camera->battle.auxBoomPitch;
        BattleCam_InitialBoomYaw = camera->battle.auxBoomYaw;
        BattleCam_InitialBoomZOffset = camera->battle.auxBoomZOffset / 256;

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

    camera->battle.auxBoomLength = LERP(BattleCam_InitialBoomLength, BattleCam_BoomLength, alpha);
    camera->battle.auxBoomPitch = LERP(BattleCam_InitialBoomPitch, BattleCam_BoomPitch, alpha);
    camera->battle.auxBoomYaw = LERP(BattleCam_InitialBoomYaw, BattleCam_BoomYaw, alpha);
    camera->battle.auxBoomZOffset = LERP(BattleCam_InitialBoomZOffset, BattleCam_BoomZOffset, alpha) * 256.0f;

    if (BattleCam_MoveTimeLeft == 0) {
        BattleCam_DoneMoving = TRUE;
    } else {
        BattleCam_MoveTimeLeft--;
    }

    return ApiStatus_BLOCK;
}

/// lerp all parameters from current to preset position focusing on the enemy side of the field
/// free parameters: BattleCam_BoomLength, BattleCam_BoomZOffset, BattleCam_MoveTimeLeft
API_CALLABLE(BattleCam_Update_ViewAllEnemies) {
    Camera* camera = &gCameras[CAM_BATTLE];
    f32 alpha;

    if (isInitialCall) {
        BattleCam_PosX = 35.0f;
        BattleCam_PosY = 60.0f;
        BattleCam_PosZ = 0.0f;

        BattleCam_BoomYaw = 0;
        BattleCam_BoomPitch = 8;

        BattleCam_InitialBoomLength = camera->battle.auxBoomLength;
        BattleCam_InitialBoomPitch = camera->battle.auxBoomPitch;
        BattleCam_InitialBoomYaw = camera->battle.auxBoomYaw;
        BattleCam_InitialBoomZOffset = camera->battle.auxBoomZOffset / 256;

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

    camera->battle.auxBoomLength = LERP(BattleCam_InitialBoomLength, BattleCam_BoomLength, alpha);
    camera->battle.auxBoomYaw = LERP(BattleCam_InitialBoomYaw, BattleCam_BoomYaw, alpha);
    camera->battle.auxBoomPitch = LERP(BattleCam_InitialBoomPitch, BattleCam_BoomPitch, alpha);
    camera->battle.auxBoomZOffset = LERP(BattleCam_InitialBoomZOffset, BattleCam_BoomZOffset, alpha) * 256.0f;

    if (BattleCam_MoveTimeLeft == 0) {
        BattleCam_DoneMoving = TRUE;
    } else {
        BattleCam_MoveTimeLeft--;
    }

    return ApiStatus_BLOCK;
}

/// lerp all parameters from current to preset position focusing on the enemy side of the field
/// does not set a fixed y-position, but does clamp its minimum to 60
/// free parameters: BattleCam_BoomLength, BattleCam_BoomZOffset, BattleCam_MoveTimeLeft
API_CALLABLE(BattleCam_Update_ViewAllEnemies_MaintainY) {
    Camera* camera = &gCameras[CAM_BATTLE];
    f32 alpha;

    if (isInitialCall) {
        BattleCam_PosX = 35.0f;
        BattleCam_PosY = MAX(camera->lookAt_obj_target.y, 60.0f);
        BattleCam_PosZ = 0.0f;

        BattleCam_BoomYaw = 0;
        BattleCam_BoomPitch = 8;

        BattleCam_InitialBoomLength = camera->battle.auxBoomLength;
        BattleCam_InitialBoomPitch = camera->battle.auxBoomPitch;
        BattleCam_InitialBoomYaw = camera->battle.auxBoomYaw;
        BattleCam_InitialBoomZOffset = camera->battle.auxBoomZOffset / 256;

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

    camera->battle.auxBoomLength = LERP(BattleCam_InitialBoomLength, BattleCam_BoomLength, alpha);
    camera->battle.auxBoomYaw = LERP(BattleCam_InitialBoomYaw, BattleCam_BoomYaw, alpha);
    camera->battle.auxBoomPitch = LERP(BattleCam_InitialBoomPitch, BattleCam_BoomPitch, alpha);
    camera->battle.auxBoomZOffset = LERP(BattleCam_InitialBoomZOffset, BattleCam_BoomZOffset, alpha) * 256.0f;

    if (BattleCam_MoveTimeLeft == 0) {
        BattleCam_DoneMoving = TRUE;
    } else {
        BattleCam_MoveTimeLeft--;
    }

    return ApiStatus_BLOCK;
}

API_CALLABLE(CamPresetUpdate_J) {
    Camera* camera = &gCameras[CAM_BATTLE];
    f32 alpha;

    if (isInitialCall) {
        if (BattleCam_SetImmediately) {
            BattleCam_PosX = camera->lookAt_obj_target.x;
            BattleCam_PosY = camera->lookAt_obj_target.y;
            BattleCam_PosZ = camera->lookAt_obj_target.z;
        }

        BattleCam_InitialBoomLength = camera->battle.auxBoomLength;
        BattleCam_InitialBoomPitch = camera->battle.auxBoomPitch;
        BattleCam_InitialBoomYaw = camera->battle.auxBoomYaw;
        BattleCam_InitialBoomZOffset = camera->battle.auxBoomZOffset / 256;

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

    camera->battle.auxBoomLength = LERP(BattleCam_InitialBoomLength, BattleCam_BoomLength, alpha);
    camera->battle.auxBoomYaw = LERP(BattleCam_InitialBoomYaw, BattleCam_BoomYaw, alpha);
    camera->battle.auxBoomPitch = LERP(BattleCam_InitialBoomPitch, BattleCam_BoomPitch, alpha);
    camera->battle.auxBoomZOffset = LERP(BattleCam_InitialBoomZOffset, BattleCam_BoomZOffset, alpha) * 256.0f;

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

        BattleCam_InitialBoomYaw = camera->battle.auxBoomYaw;
        BattleCam_InitialBoomPitch = camera->battle.auxBoomPitch;
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

        BattleCam_InitialBoomYaw = camera->battle.auxBoomYaw;
        BattleCam_InitialBoomPitch = camera->battle.auxBoomPitch;
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
    camera->battle.auxBoomYaw = 0;
    camera->battle.auxBoomZOffset = 0;

    BattleCam_BoomPitch = 8;
    BattleCam_BoomYaw = 0;
    BattleCam_BoomZOffset = 0;

    BattleCam_IsFrozen = FALSE;

    BattleCam_InitialBoomLength = camera->battle.auxBoomLength;
    BattleCam_InitialBoomPitch = camera->battle.auxBoomPitch;
    BattleCam_InitialBoomZOffset = BattleCam_InitialBoomYaw = 0.0f;
    return ApiStatus_DONE2;
}

EvtScript EVS_BattleCam_Interrupt = {
    Call(BattleCam_Update_Interrupt)
    Return
    End
};

EvtScript CamPreset_F = {
    Call(CamPresetUpdate_F)
    Return
    End
};

EvtScript CamPreset_M = {
    Call(CamPresetUpdate_M)
    Return
    End
};

EvtScript CamPreset_G = {
    Call(CamPresetUpdate_G)
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

EvtScript EVS_BattleCam_SimpleLerp = {
    Call(BattleCam_Update_SimpleLerp)
    Return
    End
};

EvtScript EVS_BattleCam_ResetNeutral = {
    Call(BattleCam_Update_ResetToNeutral)
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

EvtScript CamPreset_J = {
    Call(CamPresetUpdate_J)
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
    Call(SetBattleCamPos, 0, 15, 0)
    Call(SetBattleCamParam, AUX_CAM_BOOM_LENGTH, 550)
    Call(SetBattleCamParam, AUX_CAM_FOV_SCALE, 100)
    Call(SetBattleCamParam, AUX_CAM_BOOM_PITCH, 8)
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
    Call(func_802CABE8, CAM_BATTLE, 0, 240, 100, 8)
    Call(SetCamLookTarget, CAM_BATTLE, -75, 35, 0)
    Call(BattleCamTargetActor, 0)
    Call(BattleCam_Init)
    Return
    End
};

void btl_cam_use_preset_impl(s32 id) {
    EvtScript* preset = NULL;
    Evt* newScript;

    debug_printf("CAM: %X", id);

    if (!BattleCam_IsFrozen) {
        BattleCam_ClampPosX = TRUE;
        BattleCam_ModeX = BTL_CAM_MODEX_0;
        BattleCam_ModeY = BTL_CAM_MODEY_0;
        BattleCam_UseLinearInterp = FALSE;
        BattleCam_SpecialOffsetX = 0;

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
            case BTL_CAM_PRESET_03:
                if (BattleCam_CurrentPresetID == id) {
                    return;
                }
                BattleCam_BoomLength = 480;
                BattleCam_BoomZOffset = 0;
                BattleCam_MoveTimeLeft = 20;
                preset = &EVS_BattleCam_ViewEnemies;
                break;
            case BTL_CAM_PRESET_04:
                if (BattleCam_CurrentPresetID == id) {
                    return;
                }
                BattleCam_BoomLength = 500;
                BattleCam_BoomZOffset = 0;
                BattleCam_MoveTimeLeft = 10;
                preset = &EVS_BattleCam_ViewEnemies_MaintainY;
                break;
            case BTL_CAM_PRESET_05:
                BattleCam_ModeX = BTL_CAM_MODEX_1;
                BattleCam_ModeY = BTL_CAM_MODEY_1;
                BattleCam_BoomLength = 300;
                BattleCam_MoveTimeLeft = 20;
                preset = &CamPreset_F;
                break;
            case BTL_CAM_PRESET_06:
                BattleCam_ModeX = BTL_CAM_MODEX_1;
                BattleCam_ModeY = BTL_CAM_MODEY_1;
                BattleCam_BoomLength = 300;
                BattleCam_MoveTimeLeft = 20;
                preset = &CamPreset_G;
                break;
            case BTL_CAM_ACTOR_GOAL:
                BattleCam_BoomLength = 300;
                BattleCam_MoveTimeLeft = 20;
                preset = &EVS_BattleCam_FocusGoal;
                break;
            case BTL_CAM_PRESET_08:
                BattleCam_ModeX = BTL_CAM_MODEX_1;
                BattleCam_ModeY = BTL_CAM_MODEY_1;
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
            case BTL_CAM_PRESET_10:
                BattleCam_ModeX = BTL_CAM_MODEX_1;
                BattleCam_ModeY = BTL_CAM_MODEY_1;
                BattleCam_BoomLength = 200;
                BattleCam_BoomPitch = 8;
                BattleCam_BoomYaw = 0;
                BattleCam_BoomZOffset = 15;
                BattleCam_MoveTimeLeft = 20;
                preset = &CamPreset_F;
                break;
            case BTL_CAM_PRESET_11:
                BattleCam_ModeX = BTL_CAM_MODEX_1;
                BattleCam_ModeY = BTL_CAM_MODEY_1;
                BattleCam_BoomLength = 300;
                BattleCam_BoomPitch = 8;
                BattleCam_BoomYaw = 0;
                BattleCam_BoomZOffset = 16;
                BattleCam_MoveTimeLeft = 20;
                preset = &CamPreset_F;
                break;
            case BTL_CAM_PRESET_12:
                BattleCam_ModeX = BTL_CAM_MODEX_1;
                BattleCam_ModeY = BTL_CAM_MODEY_1;
                BattleCam_BoomLength = 400;
                BattleCam_BoomPitch = 8;
                BattleCam_BoomYaw = 0;
                BattleCam_BoomZOffset = 30;
                BattleCam_MoveTimeLeft = 20;
                preset = &CamPreset_F;
                break;
            case BTL_CAM_PRESET_13:
                BattleCam_BoomLength = 200;
                BattleCam_BoomPitch = 8;
                BattleCam_MoveTimeLeft = 20;
                BattleCam_BoomZOffset = 15;
                BattleCam_BoomYaw = 0;
                BattleCam_ModeY = BTL_CAM_MODEY_1;
                BattleCam_ModeX = BTL_CAM_MODEX_1;
                preset = &EVS_BattleCam_FocusActor;
                break;
            case BTL_CAM_PRESET_14:
                BattleCam_BoomLength = 300;
                BattleCam_BoomPitch = 8;
                BattleCam_MoveTimeLeft = 20;
                BattleCam_BoomZOffset = 16;
                BattleCam_BoomYaw = 0;
                BattleCam_ModeY = BTL_CAM_MODEY_1;
                BattleCam_ModeX = BTL_CAM_MODEX_1;
                preset = &EVS_BattleCam_FocusActor;
                break;
            case BTL_CAM_PRESET_15:
                BattleCam_BoomLength = 400;
                BattleCam_BoomPitch = 8;
                BattleCam_MoveTimeLeft = 20;
                BattleCam_BoomZOffset = 30;
                BattleCam_BoomYaw = 0;
                BattleCam_ModeY = BTL_CAM_MODEY_1;
                BattleCam_ModeX = BTL_CAM_MODEX_1;
                preset = &EVS_BattleCam_FocusActor;
                break;
            case BTL_CAM_PRESET_16:
                BattleCam_BoomLength = 267;
                BattleCam_BoomPitch = 8;
                BattleCam_BoomYaw = 0;
                BattleCam_BoomZOffset = 23;
                BattleCam_MoveTimeLeft = 20;
                preset = &EVS_BattleCam_FocusGoal;
                break;
            case BTL_CAM_PRESET_17:
                BattleCam_BoomLength = 300;
                BattleCam_BoomPitch = 8;
                BattleCam_BoomYaw = 0;
                BattleCam_BoomZOffset = 8;
                BattleCam_MoveTimeLeft = 20;
                preset = &EVS_BattleCam_FocusGoal;
                break;
            case BTL_CAM_PRESET_18:
                BattleCam_BoomLength = 400;
                BattleCam_BoomPitch = 8;
                BattleCam_BoomYaw = 0;
                BattleCam_BoomZOffset = 0;
                BattleCam_MoveTimeLeft = 20;
                preset = &EVS_BattleCam_FocusGoal;
                break;
            case BTL_CAM_PRESET_19:
                BattleCam_MoveTimeLeft = 20;
                preset = &CamPreset_J;
                break;
            case BTL_CAM_PRESET_20:
                BattleCam_MoveTimeLeft = 20;
                BattleCam_BoomZOffset = 0;
                preset = &EVS_BattleCam_FollowActorY;
                break;
            case BTL_CAM_PRESET_21:
                BattleCam_MoveTimeLeft = 20;
                BattleCam_BoomZOffset = 0;
                preset = &EVS_BattleCam_FollowActorPos;
                break;
            case BTL_CAM_PRESET_25:
                BattleCam_BoomLength = 266;
                BattleCam_BoomPitch = 8;
                BattleCam_BoomYaw = 0;
                BattleCam_BoomZOffset = 40;
                btl_cam_set_target_pos(-80.0f, 0.0f, 0.0f);
                BattleCam_MoveTimeLeft = 20;
                BattleCam_SubjectActor = ACTOR_PLAYER;
                preset = &CamPreset_J;
                break;
            case BTL_CAM_PRESET_24:
                BattleCam_BoomLength = 250;
                BattleCam_BoomPitch = 8;
                BattleCam_MoveTimeLeft = 20;
                BattleCam_BoomZOffset = 14;
                BattleCam_BoomYaw = 0;
                BattleCam_ModeY = BTL_CAM_MODEY_1;
                BattleCam_ModeX = BTL_CAM_MODEX_1;
                BattleCam_ClampPosX = FALSE;
                BattleCam_SubjectActor = ACTOR_PLAYER;
                BattleCam_IsFrozen = TRUE;
                preset = &EVS_BattleCam_FocusActor;
                break;
            case BTL_CAM_VICTORY:
                BattleCam_BoomLength = 255;
                BattleCam_BoomPitch = 8;
                BattleCam_MoveTimeLeft = 20;
                BattleCam_BoomYaw = 0;
                BattleCam_BoomZOffset = 29;
                BattleCam_ModeY = BTL_CAM_MODEY_0;
                BattleCam_ModeX = BTL_CAM_MODEX_0;
                btl_cam_set_target_pos(-95.0f, 18.0f, 10.0f);
                BattleCam_SubjectActor = ACTOR_PLAYER;
                preset = &CamPreset_J;
                break;
            case BTL_CAM_PLAYER_ENTRY:
                BattleCam_BoomLength = 230;
                BattleCam_BoomPitch = 8;
                BattleCam_BoomYaw = 0;
                BattleCam_MoveTimeLeft = 20;
                BattleCam_BoomZOffset = 0;
                BattleCam_SubjectActor = ACTOR_PLAYER;
                preset = &CamPreset_J;
                break;
            case BTL_CAM_PLAYER_ATTACK_APPROACH:
                BattleCam_BoomLength = 310;
                BattleCam_BoomPitch = 8;
                BattleCam_MoveTimeLeft = 30;
                BattleCam_BoomZOffset = 16;
                BattleCam_BoomYaw = 0;
                BattleCam_SubjectActor = ACTOR_PLAYER;
                BattleCam_ModeY = BTL_CAM_MODEY_1;
                BattleCam_ModeX = BTL_CAM_MODEX_1;
                BattleCam_ClampPosX = FALSE;
                preset = &CamPreset_M;
                break;
            case BTL_CAM_PRESET_27:
                BattleCam_MoveTimeLeft = 5;
                BattleCam_BoomLength = 320;
                BattleCam_BoomPitch = 8;
                BattleCam_BoomYaw = 0;
                BattleCam_BoomZOffset = 0;
                BattleCam_ModeX = BTL_CAM_MODEX_0;
                BattleCam_ModeY = BTL_CAM_MODEY_1;
                BattleCam_ClampPosX = FALSE;
                BattleCam_SubjectActor = ACTOR_PLAYER;
                preset = &CamPreset_M;
                break;
            case BTL_CAM_PRESET_28:
                BattleCam_MoveTimeLeft = 5;
                BattleCam_BoomLength = 340;
                BattleCam_BoomPitch = 8;
                BattleCam_BoomYaw = 0;
                BattleCam_BoomZOffset = 0;
                BattleCam_ModeX = BTL_CAM_MODEX_0;
                BattleCam_ModeY = BTL_CAM_MODEY_1;
                BattleCam_SubjectActor = ACTOR_PLAYER;
                BattleCam_ClampPosX = FALSE;
                preset = &CamPreset_M;
                break;
            case BTL_CAM_PLAYER_HIT_SPIKE:
            case BTL_CAM_PLAYER_HIT_HAZARD:
                BattleCam_SubjectActor = ACTOR_PLAYER;
                BattleCam_ModeX = BTL_CAM_MODEX_1;
                BattleCam_ModeY = BTL_CAM_MODEY_1;
                BattleCam_BoomLength = 300;
                BattleCam_BoomPitch = 8;
                BattleCam_BoomYaw = 0;
                BattleCam_BoomZOffset = -32;
                BattleCam_SpecialOffsetX = 20;
                BattleCam_MoveTimeLeft = 15;
                preset = &EVS_BattleCam_FocusActor;
                break;
            case BTL_CAM_PLAYER_CHARGE_UP:
                BattleCam_PosX = -65.0f;
                BattleCam_PosY = 30.0f;
                BattleCam_PosZ = 0.0f;
                BattleCam_ModeX = BTL_CAM_MODEX_0;
                BattleCam_ModeY = BTL_CAM_MODEY_0;
                BattleCam_BoomLength = 300;
                BattleCam_BoomPitch = 8;
                BattleCam_BoomYaw = 0;
                BattleCam_BoomZOffset = 10;
                BattleCam_MoveTimeLeft = 10;
                preset = &EVS_BattleCam_SimpleLerp;
                break;
            case BTL_CAM_PLAYER_STATUS_AFFLICTED:
                BattleCam_SubjectActor = ACTOR_PLAYER;
                BattleCam_ModeX = BTL_CAM_MODEX_1;
                BattleCam_ModeY = BTL_CAM_MODEY_1;
                BattleCam_ClampPosX = FALSE;
                BattleCam_BoomLength = 220;
                BattleCam_BoomPitch = 8;
                BattleCam_BoomYaw = 0;
                BattleCam_BoomZOffset = 24;
                BattleCam_MoveTimeLeft = 30;
                preset = &EVS_BattleCam_FocusActor;
                break;
            case BTL_CAM_PRESET_34:
                BattleCam_BoomLength = 280;
                BattleCam_BoomPitch = 8;
                BattleCam_MoveTimeLeft = 30;
                BattleCam_BoomZOffset = -4;
                BattleCam_BoomYaw = 0;
                BattleCam_ModeY = BTL_CAM_MODEY_1;
                BattleCam_ModeX = BTL_CAM_MODEX_0;
                BattleCam_SubjectActor = ACTOR_PLAYER;
                BattleCam_ClampPosX = FALSE;
                preset = &CamPreset_M;
                break;
            case BTL_CAM_PRESET_35:
                BattleCam_BoomLength = 380;
                BattleCam_BoomPitch = 8;
                BattleCam_MoveTimeLeft = 60;
                BattleCam_BoomYaw = 0;
                BattleCam_BoomZOffset = 0;
                BattleCam_ModeY = BTL_CAM_MODEY_1;
                BattleCam_ModeX = BTL_CAM_MODEX_0;
                BattleCam_UseLinearInterp = TRUE;
                BattleCam_ClampPosX = FALSE;
                BattleCam_SubjectActor = ACTOR_PLAYER;
                preset = &CamPreset_M;
                break;
            case BTL_CAM_PRESET_37:
                BattleCam_BoomLength = 320;
                BattleCam_BoomPitch = 8;
                BattleCam_MoveTimeLeft = 30;
                BattleCam_BoomZOffset = -4;
                BattleCam_BoomYaw = 0;
                BattleCam_ModeY = BTL_CAM_MODEY_1;
                BattleCam_ModeX = BTL_CAM_MODEX_0;
                BattleCam_ClampPosX = FALSE;
                BattleCam_SubjectActor = ACTOR_PLAYER;
                preset = &CamPreset_M;
                break;
            case BTL_CAM_PRESET_36:
                BattleCam_BoomLength = 300;
                BattleCam_BoomPitch = 8;
                BattleCam_MoveTimeLeft = 60;
                BattleCam_BoomYaw = 0;
                BattleCam_BoomZOffset = 0;
                BattleCam_ModeY = BTL_CAM_MODEY_1;
                BattleCam_ModeX = BTL_CAM_MODEX_0;
                BattleCam_UseLinearInterp = TRUE;
                BattleCam_ClampPosX = FALSE;
                BattleCam_SubjectActor = ACTOR_PLAYER;
                preset = &CamPreset_M;
                break;
            case BTL_CAM_PRESET_38:
                BattleCam_BoomLength = 320;
                BattleCam_BoomPitch = 8;
                BattleCam_MoveTimeLeft = 30;
                BattleCam_BoomZOffset = -4;
                BattleCam_BoomYaw = 0;
                BattleCam_ModeY = BTL_CAM_MODEY_1;
                BattleCam_ModeX = BTL_CAM_MODEX_0;
                BattleCam_ClampPosX = FALSE;
                BattleCam_SubjectActor = ACTOR_PLAYER;
                preset = &CamPreset_M;
                break;
            case BTL_CAM_PRESET_39:
                BattleCam_BoomLength = 320;
                BattleCam_BoomPitch = 8;
                BattleCam_MoveTimeLeft = 30;
                BattleCam_BoomYaw = 0;
                BattleCam_BoomZOffset = 0;
                BattleCam_ModeY = BTL_CAM_MODEY_1;
                BattleCam_ModeX = BTL_CAM_MODEX_0;
                BattleCam_ClampPosX = FALSE;
                BattleCam_SubjectActor = ACTOR_PLAYER;
                preset = &CamPreset_M;
                break;
            case BTL_CAM_PRESET_40:
                BattleCam_BoomLength = 360;
                BattleCam_BoomPitch = 8;
                BattleCam_MoveTimeLeft = 20;
                BattleCam_BoomZOffset = -4;
                BattleCam_BoomYaw = 0;
                BattleCam_ModeY = BTL_CAM_MODEY_1;
                BattleCam_ModeX = BTL_CAM_MODEX_1;
                BattleCam_ClampPosX = FALSE;
                BattleCam_SubjectActor = ACTOR_PLAYER;
                preset = &CamPreset_M;
                break;
            case BTL_CAM_PRESET_41:
            case BTL_CAM_PRESET_42:
                BattleCam_BoomLength = 200;
                BattleCam_MoveTimeLeft = 7;
                BattleCam_MoveTimeTotal = 7;
                BattleCam_DoneMoving = FALSE;
                BattleCam_ClampPosX = FALSE;
                preset = BattleCam_ControlScript;
                break;
            case BTL_CAM_PLAYER_AIM_HAMMER:
                BattleCam_BoomLength = 214;
                BattleCam_BoomPitch = 8;
                BattleCam_MoveTimeLeft = 20;
                BattleCam_BoomZOffset = 16;
                BattleCam_ModeY = BTL_CAM_MODEY_MINUS_2;
                BattleCam_BoomYaw = 0;
                BattleCam_SubjectActor = ACTOR_PLAYER;
                BattleCam_ModeX = BTL_CAM_MODEX_1;
                BattleCam_ClampPosX = FALSE;
                preset = &CamPreset_M;
                break;
            case BTL_CAM_PLAYER_HAMMER_STRIKE:
                BattleCam_BoomLength = 300;
                BattleCam_BoomPitch = 8;
                BattleCam_MoveTimeLeft = 8;
                BattleCam_BoomZOffset = 16;
                BattleCam_BoomYaw = 0;
                BattleCam_SubjectActor = ACTOR_PLAYER;
                BattleCam_ModeY = BTL_CAM_MODEY_0;
                BattleCam_ModeX = BTL_CAM_MODEX_1;
                BattleCam_ClampPosX = FALSE;
                preset = &CamPreset_M;
                break;
            case BTL_CAM_PRESET_45:
                BattleCam_BoomLength = 430;
                BattleCam_BoomPitch = 8;
                BattleCam_MoveTimeLeft = 10;
                BattleCam_BoomYaw = 0;
                BattleCam_BoomZOffset = 16;
                BattleCam_SubjectActor = ACTOR_PLAYER;
                BattleCam_ModeY = BTL_CAM_MODEY_0;
                BattleCam_ModeX = BTL_CAM_MODEX_0;
                BattleCam_PosZ = 0.0f;
                BattleCam_PosX = 60.0f;
                BattleCam_PosY = 40.0f;
                preset = &EVS_BattleCam_SimpleLerp;
                break;
            case BTL_CAM_PRESET_46:
                BattleCam_BoomLength = 460;
                BattleCam_BoomPitch = 8;
                BattleCam_MoveTimeLeft = 10;
                BattleCam_BoomYaw = 0;
                BattleCam_BoomZOffset = 27;
                BattleCam_SubjectActor = ACTOR_PLAYER;
                BattleCam_ModeY = BTL_CAM_MODEY_0;
                BattleCam_PosZ = 0.0f;
                BattleCam_PosX = 60.0f;
                BattleCam_PosY = 40.0f;
                preset = &EVS_BattleCam_SimpleLerp;
                break;
            case BTL_CAM_PRESET_70:
                BattleCam_BoomLength = 390;
                BattleCam_BoomPitch = 8;
                BattleCam_BoomYaw = 0;
                BattleCam_BoomZOffset = 45;
                btl_cam_set_target_pos(-70.0f, 0.0f, 0.0f);
                BattleCam_MoveTimeLeft = 10;
                BattleCam_ClampPosX = FALSE;
                preset = &CamPreset_J;
                break;
            case BTL_CAM_PRESET_71:
                BattleCam_BoomLength = 500;
                BattleCam_BoomPitch = 8;
                BattleCam_BoomYaw = 0;
                BattleCam_BoomZOffset = 45;
                btl_cam_set_target_pos(0.0f, 0.0f, 0.0f);
                BattleCam_MoveTimeLeft = 40;
                BattleCam_ClampPosX = FALSE;
                preset = &CamPreset_J;
                break;
            case BTL_CAM_PRESET_69:
            case BTL_CAM_PRESET_72:
                BattleCam_BoomLength = 300;
                BattleCam_BoomPitch = 8;
                BattleCam_BoomYaw = 0;
                BattleCam_BoomZOffset = 45;
                btl_cam_set_target_pos(-50.0f, 0.0f, 0.0f);
                BattleCam_MoveTimeLeft = 20;
                BattleCam_ClampPosX = FALSE;
                preset = &CamPreset_J;
                break;
            case BTL_CAM_PRESET_73:
                BattleCam_BoomLength = 166;
                BattleCam_BoomPitch = 8;
                BattleCam_MoveTimeLeft = 1;
                BattleCam_BoomYaw = 0;
                BattleCam_BoomZOffset = 17;
                BattleCam_ModeY = BTL_CAM_MODEY_0;
                BattleCam_ModeX = BTL_CAM_MODEX_0;
                BattleCam_PosX = -75.0f;
                BattleCam_PosY = 150.0f;
                BattleCam_PosZ = 0.0f;
                preset = &EVS_BattleCam_SimpleLerp;
                break;
            case BTL_CAM_PARTNER_APPROACH:
                BattleCam_BoomLength = 310;
                BattleCam_BoomPitch = 8;
                BattleCam_MoveTimeLeft = 30;
                BattleCam_BoomZOffset = 16;
                BattleCam_BoomYaw = 0;
                BattleCam_ModeY = BTL_CAM_MODEY_1;
                BattleCam_ModeX = BTL_CAM_MODEX_1;
                BattleCam_SubjectActor = ACTOR_PARTNER;
                BattleCam_ClampPosX = FALSE;
                preset = &CamPreset_M;
                break;
            case BTL_CAM_PRESET_48:
                BattleCam_BoomLength = 250;
                BattleCam_BoomPitch = 8;
                BattleCam_MoveTimeLeft = 120;
                BattleCam_BoomZOffset = 16;
                BattleCam_ModeY = BTL_CAM_MODEY_1;
                BattleCam_ModeX = BTL_CAM_MODEX_1;
                BattleCam_UseLinearInterp = TRUE;
                BattleCam_BoomYaw = 0;
                BattleCam_ClampPosX = FALSE;
                BattleCam_SubjectActor = ACTOR_PARTNER;
                preset = &CamPreset_M;
                break;
            case BTL_CAM_PRESET_49:
                BattleCam_BoomLength = 300;
                BattleCam_BoomPitch = 8;
                BattleCam_MoveTimeLeft = 120;
                BattleCam_BoomZOffset = 16;
                BattleCam_ModeY = BTL_CAM_MODEY_1;
                BattleCam_ModeX = BTL_CAM_MODEX_1;
                BattleCam_UseLinearInterp = TRUE;
                BattleCam_BoomYaw = 0;
                BattleCam_ClampPosX = FALSE;
                BattleCam_SubjectActor = ACTOR_PARTNER;
                preset = &EVS_BattleCam_FocusActor;
                break;
            case BTL_CAM_PRESET_50:
                BattleCam_BoomLength = 320;
                BattleCam_BoomPitch = 8;
                BattleCam_MoveTimeLeft = 5;
                BattleCam_ModeY = BTL_CAM_MODEY_1;
                BattleCam_BoomYaw = 0;
                BattleCam_BoomZOffset = 0;
                BattleCam_ModeX = BTL_CAM_MODEX_0;
                BattleCam_SubjectActor = ACTOR_PARTNER;
                BattleCam_ClampPosX = FALSE;
                preset = &CamPreset_M;
                break;
            case BTL_CAM_PRESET_29:
            case BTL_CAM_PRESET_51:
                BattleCam_BoomLength = 500;
                BattleCam_BoomZOffset = 0;
                BattleCam_MoveTimeLeft = 50;
                preset = &EVS_BattleCam_ViewEnemies;
                break;
            case BTL_CAM_PRESET_52:
                BattleCam_BoomLength = 280;
                BattleCam_BoomPitch = 8;
                BattleCam_MoveTimeLeft = 30;
                BattleCam_BoomZOffset = -4;
                BattleCam_ModeY = BTL_CAM_MODEY_1;
                BattleCam_BoomYaw = 0;
                BattleCam_ModeX = BTL_CAM_MODEX_0;
                BattleCam_ClampPosX = FALSE;
                BattleCam_SubjectActor = ACTOR_PARTNER;
                preset = &CamPreset_M;
                break;
            case BTL_CAM_PRESET_53:
                BattleCam_BoomLength = 380;
                BattleCam_BoomPitch = 8;
                BattleCam_MoveTimeLeft = 60;
                BattleCam_ModeY = BTL_CAM_MODEY_1;
                BattleCam_UseLinearInterp = TRUE;
                BattleCam_BoomYaw = 0;
                BattleCam_BoomZOffset = 0;
                BattleCam_ModeX = BTL_CAM_MODEX_0;
                BattleCam_ClampPosX = FALSE;
                BattleCam_SubjectActor = ACTOR_PARTNER;
                preset = &CamPreset_M;
                break;
            case BTL_CAM_PARTNER_INJURED:
                BattleCam_BoomLength = 220;
                BattleCam_BoomPitch = 8;
                BattleCam_MoveTimeLeft = 30;
                BattleCam_BoomZOffset = 24;
                BattleCam_ModeY = BTL_CAM_MODEY_1;
                BattleCam_ModeX = BTL_CAM_MODEX_1;
                BattleCam_BoomYaw = 0;
                BattleCam_ClampPosX = FALSE;
                BattleCam_SubjectActor = ACTOR_PARTNER;
                preset = &EVS_BattleCam_FocusActor;
                break;
            case BTL_CAM_PRESET_55:
                BattleCam_BoomLength = 210;
                BattleCam_BoomPitch = 8;
                BattleCam_MoveTimeLeft = 20;
                BattleCam_BoomYaw = 0;
                BattleCam_BoomZOffset = 10;
                BattleCam_ModeY = BTL_CAM_MODEY_0;
                BattleCam_ModeX = BTL_CAM_MODEX_0;
                BattleCam_PosZ = 0.0f;
                BattleCam_PosX = -95.0f;
                BattleCam_PosY = 22.0f;
                preset = &EVS_BattleCam_SimpleLerp;
                break;
            case BTL_CAM_PRESET_56:
                BattleCam_BoomLength = 320;
                BattleCam_BoomPitch = 8;
                BattleCam_MoveTimeLeft = 30;
                BattleCam_BoomZOffset = -4;
                BattleCam_ModeY = BTL_CAM_MODEY_1;
                BattleCam_BoomYaw = 0;
                BattleCam_ModeX = BTL_CAM_MODEX_0;
                BattleCam_SubjectActor = ACTOR_PARTNER;
                preset = &CamPreset_M;
                break;
            case BTL_CAM_PRESET_57:
                BattleCam_BoomLength = 320;
                BattleCam_BoomPitch = 8;
                BattleCam_MoveTimeLeft = 30;
                BattleCam_ModeY = BTL_CAM_MODEY_1;
                BattleCam_BoomYaw = 0;
                BattleCam_BoomZOffset = 0;
                BattleCam_ModeX = BTL_CAM_MODEX_0;
                BattleCam_SubjectActor = ACTOR_PARTNER;
                preset = &CamPreset_M;
                break;
            case BTL_CAM_PRESET_58:
                BattleCam_BoomLength = 400;
                BattleCam_BoomPitch = 8;
                BattleCam_MoveTimeLeft = 30;
                BattleCam_BoomYaw = 0;
                BattleCam_BoomZOffset = 10;
                BattleCam_ModeY = BTL_CAM_MODEY_0;
                BattleCam_ModeX = BTL_CAM_MODEX_0;
                BattleCam_PosZ = 0.0f;
                BattleCam_PosX = 25.0f;
                BattleCam_PosY = 60.0f;
                preset = &EVS_BattleCam_SimpleLerp;
                break;
            case BTL_CAM_PRESET_59:
                BattleCam_BoomLength = 200;
                BattleCam_BoomPitch = 8;
                BattleCam_MoveTimeLeft = 60;
                BattleCam_BoomZOffset = 11;
                BattleCam_ModeY = BTL_CAM_MODEY_1;
                BattleCam_ModeX = BTL_CAM_MODEX_1;
                BattleCam_UseLinearInterp = TRUE;
                BattleCam_BoomYaw = 0;
                BattleCam_SubjectActor = ACTOR_PARTNER;
                BattleCam_ClampPosX = FALSE;
                preset = &EVS_BattleCam_FocusActor;
                break;
            case BTL_CAM_PRESET_60:
                BattleCam_BoomLength = 300;
                BattleCam_BoomPitch = 8;
                BattleCam_MoveTimeLeft = 8;
                BattleCam_BoomZOffset = 16;
                BattleCam_BoomYaw = 0;
                BattleCam_SubjectActor = ACTOR_PARTNER;
                BattleCam_ModeY = BTL_CAM_MODEY_0;
                BattleCam_ModeX = BTL_CAM_MODEX_0;
                preset = &EVS_BattleCam_FocusActor;
                break;
            case BTL_CAM_PRESET_61:
            case BTL_CAM_PRESET_62:
                BattleCam_BoomLength = 300;
                BattleCam_BoomPitch = 8;
                BattleCam_MoveTimeLeft = 15;
                BattleCam_BoomZOffset = -32;
                BattleCam_SpecialOffsetX = 20;
                BattleCam_ModeY = BTL_CAM_MODEY_1;
                BattleCam_ModeX = BTL_CAM_MODEX_1;
                BattleCam_BoomYaw = 0;
                BattleCam_SubjectActor = ACTOR_PARTNER;
                preset = &EVS_BattleCam_FocusActor;
                break;
            case BTL_CAM_ENEMY_APPROACH:
                BattleCam_BoomLength = 400;
                BattleCam_BoomPitch = 8;
                BattleCam_MoveTimeLeft = 20;
                BattleCam_BoomZOffset = 27;
                BattleCam_BoomYaw = 0;
                BattleCam_ModeY = BTL_CAM_MODEY_1;
                BattleCam_ModeX = BTL_CAM_MODEX_1;
                preset = &CamPreset_F;
                break;
            case BTL_CAM_PRESET_64:
                BattleCam_BoomLength = 358;
                BattleCam_BoomPitch = 8;
                BattleCam_MoveTimeLeft = 10;
                BattleCam_BoomZOffset = 16;
                BattleCam_BoomYaw = 0;
                BattleCam_ModeY = BTL_CAM_MODEY_1;
                BattleCam_ModeX = BTL_CAM_MODEX_0;
                preset = &CamPreset_F;
                break;
            case BTL_CAM_DEFAULT_UNUSED:
                BattleCam_BoomLength = 500;
                BattleCam_MoveTimeLeft = 50;
                preset = &EVS_BattleCam_ResetNeutral;
                break;
            case BTL_CAM_PRESET_66:
                BattleCam_BoomLength = 267;
                BattleCam_BoomPitch = 8;
                BattleCam_MoveTimeLeft = 20;
                BattleCam_BoomZOffset = 16;
                BattleCam_BoomYaw = 0;
                BattleCam_ModeY = BTL_CAM_MODEY_1;
                BattleCam_ModeX = BTL_CAM_MODEX_0;
                preset = &CamPreset_F;
                break;
            case BTL_CAM_PRESET_67:
                BattleCam_BoomLength = 214;
                BattleCam_BoomPitch = 8;
                BattleCam_MoveTimeLeft = 20;
                BattleCam_BoomZOffset = 16;
                BattleCam_BoomYaw = 0;
                BattleCam_ModeY = BTL_CAM_MODEY_1;
                BattleCam_ModeX = BTL_CAM_MODEX_1;
                preset = &CamPreset_F;
                break;
            case BTL_CAM_PRESET_68:
                BattleCam_BoomLength = 300;
                BattleCam_BoomPitch = 8;
                BattleCam_MoveTimeLeft = 4;
                BattleCam_BoomZOffset = 16;
                BattleCam_BoomYaw = 0;
                BattleCam_ModeY = BTL_CAM_MODEY_1;
                BattleCam_ModeX = BTL_CAM_MODEX_1;
                preset = &CamPreset_F;
                break;
        }

        BattleCam_CurrentPresetID = id;

        if (gBattleStatus.camMovementScript != NULL) {
            kill_script_by_ID(gBattleStatus.camMovementScriptID);
        }

        BattleCam_ControlScript = preset;
        newScript = start_script(preset, EVT_PRIORITY_A, EVT_FLAG_RUN_IMMEDIATELY);
        BattleCam_DoneMoving = FALSE;
        gBattleStatus.camMovementScript = newScript;
        gBattleStatus.camMovementScriptID = newScript->id;
    }
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

void btl_cam_set_params(b16 skipRecalc, s16 boomLength, s16 vfovScale, s16 boomPitch, s32 boomYaw, s32 boomZOffset, s32 arg6, s32 zoomPercent) {
    Camera* camera = &gCameras[CAM_BATTLE];

    if (!BattleCam_IsFrozen) {
        camera->battle.skipRecalc = skipRecalc;
        camera->battle.auxBoomLength = boomLength;
        camera->battle.auxFovScale = vfovScale;
        camera->battle.auxBoomPitch = boomPitch;
        camera->battle.auxBoomYaw = boomYaw;
        camera->battle.auxBoomZOffset = boomZOffset * 256;
        camera->battle.unk_28 = arg6;
        camera->battle.zoomPercent = zoomPercent;
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
        BattleCam_BoomZOffset = zOffset;
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
        script->functionTemp[0] = 0;
    }

    switch (script->functionTemp[0]) {
        case 0:
            btl_cam_use_preset(evt_get_variable(script, *args++));
            script->functionTemp[0] = 1;
            break;
        case 1:
            if (btl_cam_is_moving_done()) {
                return ApiStatus_DONE2;
            }
            break;
    }
    return ApiStatus_BLOCK;
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
        case AUX_CAM_SKIP_RECALC:
            camera->battle.skipRecalc = val;
            break;
        case AUX_CAM_BOOM_LENGTH:
            camera->battle.auxBoomLength = val;
            break;
        case AUX_CAM_FOV_SCALE:
            camera->battle.auxFovScale = val;
            break;
        case AUX_CAM_BOOM_PITCH:
            camera->battle.auxBoomPitch = val;
            break;
        case AUX_CAM_BOOM_YAW:
            camera->battle.auxBoomYaw = val;
            break;
        case AUX_CAM_BOOM_ZOFFSET:
            camera->battle.auxBoomZOffset = val * 256;
            break;
        case AUX_CAM_PARAM_7:
            camera->battle.unk_28 = val;
            break;
        case AUX_CAM_ZOOM_PERCENT:
            camera->battle.zoomPercent = val;
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

    camera->battle.skipRecalc = evt_get_variable(script, *args++);
    camera->battle.auxBoomLength = evt_get_variable(script, *args++);
    camera->battle.auxFovScale = evt_get_variable(script, *args++);
    camera->battle.auxBoomPitch = evt_get_variable(script, *args++);
    camera->battle.auxBoomYaw = evt_get_variable(script, *args++);
    camera->battle.auxBoomZOffset = evt_get_variable(script, *args++) * 256;
    camera->battle.unk_28 = evt_get_variable(script, *args++);
    camera->battle.zoomPercent = evt_get_variable(script, *args++);

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

API_CALLABLE(SetBattleCamPos) {
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

API_CALLABLE(SetBattleCamOffsetZ) {
    Bytecode* args = script->ptrReadPos;

    if (BattleCam_IsFrozen) {
        return ApiStatus_DONE2;
    }

    BattleCam_BoomZOffset = evt_get_variable(script, *args++);
    return ApiStatus_DONE2;
}

API_CALLABLE(AddBattleCamOffsetZ) {
    Bytecode* args = script->ptrReadPos;

    if (BattleCam_IsFrozen) {
        return ApiStatus_DONE2;
    }

    BattleCam_BoomZOffset += evt_get_variable(script, *args++);
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
    BattleCam_CurrentPresetID = 0;

    if (gBattleStatus.camMovementScript != NULL) {
        restart_script(gBattleStatus.camMovementScript);
    }

    return ApiStatus_DONE2;
}

API_CALLABLE(SetBattleCamZoom) {
    Bytecode* args = script->ptrReadPos;

    if (BattleCam_IsFrozen) {
        return ApiStatus_DONE2;
    }

    BattleCam_BoomLength = evt_get_variable(script, *args++);
    return ApiStatus_DONE2;
}

API_CALLABLE(AddBattleCamZoom) {
    Bytecode* args = script->ptrReadPos;

    if (BattleCam_IsFrozen) {
        return ApiStatus_DONE2;
    }

    BattleCam_BoomLength += evt_get_variable(script, *args++);
    return ApiStatus_DONE2;
}

API_CALLABLE(func_8024ECF8) {
    Bytecode* args = script->ptrReadPos;

    if (BattleCam_IsFrozen) {
        return ApiStatus_DONE2;
    }

    BattleCam_ModeY = evt_get_variable(script, *args++);
    BattleCam_ModeX = evt_get_variable(script, *args++);
    BattleCam_UseLinearInterp = evt_get_variable(script, *args++);
    return ApiStatus_DONE2;
}

API_CALLABLE(FreezeBattleCam) {
    BattleCam_IsFrozen = evt_get_variable(script, *script->ptrReadPos);
    return ApiStatus_DONE2;
}

API_CALLABLE(func_8024EDA4) {
    BattleCam_ClampPosX = FALSE;
    return ApiStatus_DONE2;
}
