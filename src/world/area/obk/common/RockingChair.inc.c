#include "common.h"
#include "model.h"

/*
 *  Nonphysical rocking-chair oscillator state.
 *
 *  The chair does not compute real torque, inertia, or damping. Instead,
 *  leftAccum and rightAccum are opposing accumulators. Their difference is used
 *  as the per-frame angular velocity:
 *
 *      rockAngle += (leftAccum - rightAccum);
 *
 *  thresholdAngle is a switching threshold, not a true physical equilibrium.
 *  Once rockAngle crosses it, the opposite accumulator is advanced more strongly
 *  by counterWeight to reverse the rocking direction.
 */
typedef struct RockingChairPhysics {
    /* 0x00 */ f32 angularVel;
    /* 0x04 */ f32 accumRate;
    /* 0x08 */ f32 rockAngle;
    /* 0x0C */ f32 verticalOffset;
    /* 0x10 */ f32 leftAccum;
    /* 0x14 */ f32 rightAccum;
    /* 0x18 */ f32 counterWeight;
    /* 0x1C */ f32 thresholdAngle;
} RockingChairPhysics; // size = 0x20

enum RockingChairState {
    CHAIR_STATE_INITIAL             = 0,
    CHAIR_STATE_PLAYER_TOUCHING     = 1,
    CHAIR_STATE_PLAYER_NOT_TOUCHING = 2
};

API_CALLABLE(N(UpdateRockingChair)) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    CollisionStatus* collisionStatus = &gCollisionStatus;
    Bytecode* args = script->ptrReadPos;
    f32 chairCenterX = evt_get_float_variable(script, *args++);
    s32 modelA = evt_get_variable(script, *args++);
    s32 modelB = evt_get_variable(script, *args++);
    s32 modelC = evt_get_variable(script, *args++);
    s32 colliderA = evt_get_variable(script, *args++);
    s32 colliderB = evt_get_variable(script, *args++);
    s32 colliderC = evt_get_variable(script, *args++);
    RockingChairPhysics* physics;
    f32 centerX, centerY, centerZ;
    Matrix4f tempMtx;
    Model* model;

    if (isInitialCall) {
        physics = heap_malloc(sizeof(*physics));
        script->functionTempPtr[1] = physics;
        physics->angularVel = 0;
        physics->verticalOffset = 0;
        physics->rockAngle = 0;
        physics->leftAccum = 0;
        physics->rightAccum = 0;
        physics->accumRate = 0.1f;
        physics->counterWeight = 3.0f;
        script->functionTemp[0] = CHAIR_STATE_INITIAL;
        script->functionTemp[2] = 0;
        script->functionTemp[3] = 0;
    }

    physics = script->functionTempPtr[1];
    switch (script->functionTemp[0]) {
        case CHAIR_STATE_INITIAL:
            if (collisionStatus->curFloor == colliderC) {
                script->functionTemp[0] = CHAIR_STATE_PLAYER_TOUCHING;
            }
            if (collisionStatus->curFloor == colliderB) {
                script->functionTemp[0] = CHAIR_STATE_PLAYER_TOUCHING;
            }
            physics->angularVel = 0.0f;
            physics->verticalOffset = 0.0f;
            physics->leftAccum = 0.0f;
            physics->rightAccum = 0.0f;
            physics->rockAngle = 0.0f;
            physics->accumRate = 0.1f;
            physics->counterWeight = 3.0f;
            physics->thresholdAngle = 20.0f;
            break;
        case CHAIR_STATE_PLAYER_TOUCHING:
            if (collisionStatus->curFloor != colliderC && collisionStatus->curFloor != colliderB) {
                script->functionTemp[3] = 120; // settle time
                script->functionTemp[0] = CHAIR_STATE_PLAYER_NOT_TOUCHING;
            }
            if (fabsf(physics->rockAngle) < 5.0f) {
                physics->accumRate = fabsf(chairCenterX - playerStatus->pos.x) / 200.0f;
            } else {
                physics->accumRate = 0.1f;
            }
            if (playerStatus->pos.x <= chairCenterX) {
                // increase accumulator
                physics->leftAccum += physics->accumRate;
                // calculate player position dependent threshold angle
                physics->thresholdAngle = SQ(fabsf(chairCenterX - playerStatus->pos.x)) / 50.0f;
                if (physics->thresholdAngle > 15.0f) {
                    physics->thresholdAngle = 15.0f;
                }
                // when over threshold, increase the OTHER accumulator
                if (physics->rockAngle > physics->thresholdAngle) {
                    physics->rightAccum += physics->accumRate * physics->counterWeight;
                }
            } else {
                // increase accumulator
                physics->rightAccum += physics->accumRate;
                // calculate player position dependent threshold angle
                physics->thresholdAngle = -SQ(fabsf(chairCenterX - playerStatus->pos.x)) / 200.0f;
                if (physics->thresholdAngle < -5.0f) {
                    physics->thresholdAngle = -5.0f;
                }
                // when under threshold, increase the OTHER accumulator
                if (physics->rockAngle < physics->thresholdAngle) {
                    physics->leftAccum += physics->accumRate * physics->counterWeight;
                }
            }
            // mitigate accumulator secular drift
            if ((physics->leftAccum > 100.0f) && (physics->rightAccum > 100.0f)) {
                physics->leftAccum -= 100.0f;
                physics->rightAccum -= 100.0f;
            }
            // clamp accumulator difference to 1.5
            if (fabsf(physics->leftAccum - physics->rightAccum) > 1.5f) {
                if (physics->rightAccum > physics->leftAccum) {
                    physics->rightAccum = physics->leftAccum + 1.5f;
                } else {
                    physics->leftAccum = physics->rightAccum + 1.5f;
                }
            }
            physics->angularVel = physics->leftAccum - physics->rightAccum;
            physics->rockAngle += physics->angularVel;
            break;
        case CHAIR_STATE_PLAYER_NOT_TOUCHING:
            if (collisionStatus->curFloor == colliderC) {
                script->functionTemp[0] = CHAIR_STATE_PLAYER_TOUCHING;
            }
            if (collisionStatus->curFloor == colliderB) {
                script->functionTemp[0] = CHAIR_STATE_PLAYER_TOUCHING;
            }
            // accumulate slowly
            physics->accumRate = 0.1f;
            physics->leftAccum += physics->accumRate;
            // add counter-accumulation when above threshold
            physics->thresholdAngle = 0.0f;
            if (physics->rockAngle > physics->thresholdAngle) {
                physics->rightAccum += physics->accumRate * physics->counterWeight;
            }
            // mitigate accumulator secular drift
            if ((physics->leftAccum > 100.0f) && ( physics->rightAccum > 100.0f)) {
                physics->leftAccum -= 100.0f;
                physics->rightAccum -= 100.0f;
            }
            // clamp accumulator difference to 0.5
            if (fabsf(physics->leftAccum - physics->rightAccum) > 0.5f) {
                if (physics->rightAccum > physics->leftAccum) {
                    physics->rightAccum = physics->leftAccum + 0.5f;
                } else {
                    physics->leftAccum = physics->rightAccum + 0.5f;
                }
            }
            if (script->functionTemp[3] < 0) {
                // snap to neutral after settling period
                physics->rightAccum = 0.0f;
                physics->leftAccum = 0.0f;
                physics->angularVel = 0.0f;
                physics->rockAngle = 0.0f;
            } else {
                script->functionTemp[3]--;
            }
            physics->angularVel = physics->leftAccum - physics->rightAccum;
            physics->rockAngle += physics->angularVel;
            break;
    }

    // play creak sound once per cycle
    if (physics->rockAngle <= -7.0f) {
        if (script->functionTemp[2] != -1) {
            get_collider_center(colliderC, &centerX, &centerY, &centerZ);
            sfx_play_sound_at_position(SOUND_CREAKY_ROCKING, SOUND_SPACE_DEFAULT, centerX, centerY, centerZ);
            script->functionTemp[2] = -1;
        }
    } else {
        script->functionTemp[2] = 0;
    }

    physics->verticalOffset = SQ(physics->rockAngle) / 90.0f;

    model = get_model_from_list_index(get_model_list_index_from_tree_index(modelC));
    model->flags |= (MODEL_FLAG_MATRIX_DIRTY | MODEL_FLAG_HAS_TRANSFORM);
    guTranslateF(model->userTransformMtx, 0.0f, physics->verticalOffset, 0.0f);
    guRotateF(tempMtx, physics->rockAngle, 0.0f, 0.0f, 1.0f);
    guMtxCatF(model->userTransformMtx, tempMtx, model->userTransformMtx);
    update_collider_transform(colliderC);
    update_collider_transform(colliderB);

    model = get_model_from_list_index(get_model_list_index_from_tree_index(modelB));
    model->flags |= (MODEL_FLAG_MATRIX_DIRTY | MODEL_FLAG_HAS_TRANSFORM);
    guTranslateF(model->userTransformMtx, 0.0f, physics->verticalOffset, 0.0f);
    guRotateF(tempMtx, physics->rockAngle, 0.0f, 0.0f, 1.0f);
    guMtxCatF(model->userTransformMtx, tempMtx, model->userTransformMtx);

    model = get_model_from_list_index(get_model_list_index_from_tree_index(modelA));
    model->flags |= (MODEL_FLAG_MATRIX_DIRTY | MODEL_FLAG_HAS_TRANSFORM);
    guTranslateF(model->userTransformMtx, 0.0f, physics->verticalOffset, 0.0f);
    guRotateF(tempMtx, physics->rockAngle, 0.0f, 0.0f, 1.0f);
    guMtxCatF(model->userTransformMtx, tempMtx, model->userTransformMtx);
    update_collider_transform(colliderA);

    return ApiStatus_BLOCK;
}
