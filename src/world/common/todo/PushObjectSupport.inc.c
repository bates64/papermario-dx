#include "common.h"
#include "npc.h"

API_CALLABLE(N(IsPlayerPushingCollider)) {
    s32 colliderID = evt_get_variable(script, *script->ptrReadPos);
    PlayerStatus* playerStatus = &gPlayerStatus;
    CollisionStatus* collisionStatus = &gCollisionStatus;

    if ((collisionStatus->pushingAgainstWall != colliderID && playerStatus->actionState == ACTION_STATE_PUSHING_BLOCK)
        || playerStatus->enableCollisionOverlapsCheck != 0
        || playerStatus->inputDisabledCount != 0
    ) {
        set_action_state(ACTION_STATE_IDLE);
        script->varTable[0] = false;
        return ApiStatus_DONE2;
    }

    if (collisionStatus->pushingAgainstWall != colliderID) {
        script->varTable[0] = false;
    } else if (
        (playerStatus->actionState != ACTION_STATE_PUSHING_BLOCK) &&
        (playerStatus->actionState != ACTION_STATE_WALK) &&
        (playerStatus->actionState != ACTION_STATE_RUN))
    {
        script->varTable[0] = false;
    } else if (playerStatus->animFlags & PA_FLAG_USING_WATT) {
        script->varTable[0] = false;
    } else {
        script->varTable[0] = true;
    }

    return ApiStatus_DONE2;
}

API_CALLABLE(N(UpdatePlayerPushPosition)) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    f32 posX, posY, posZ, hitDepth;

    if (script->varTable[5] == 0) {
        playerStatus->pos.x = script->varTable[0];
    } else {
        playerStatus->pos.z = script->varTable[0];
    }

    posX = playerStatus->pos.x;
    posY = playerStatus->pos.y + 10.0f;
    posZ = playerStatus->pos.z;
    hitDepth = 40.0f;

    npc_raycast_down_sides(0, &posX, &posY, &posZ, &hitDepth);

    playerStatus->pos.x = posX;
    playerStatus->pos.y = posY;
    playerStatus->pos.z = posZ;

    return ApiStatus_DONE2;
}
