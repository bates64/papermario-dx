#include "common.h"
#include "npc.h"

/// Computes the closest position to Peach at a specified radius.
/// @evtapi
/// @param npcID
/// @param radius
/// @param outShouldMove
/// @param outX
/// @param outZ
API_CALLABLE(N(GetApproachPeachPos)) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    Bytecode* args = script->ptrReadPos;
    s32 npcID = evt_get_variable(script, *args++);
    f32 radius = evt_get_float_variable(script, *args++);
    s32 outShouldMove = *args++;
    s32 outX = *args++;
    s32 outZ = *args++;
    Npc* npc = resolve_npc(script, npcID);
    f32 dist, angle;
    f32 posX, posZ;

    if (npc == nullptr) {
        return ApiStatus_DONE2;
    }

    dist = dist2D(playerStatus->pos.x, playerStatus->pos.z, npc->pos.x, npc->pos.z);
    angle = clamp_angle(atan2(playerStatus->pos.x, playerStatus->pos.z, npc->pos.x, npc->pos.z));

    evt_set_variable(script, outShouldMove, dist >= radius);

    posX = playerStatus->pos.x + (sin_deg(angle) * radius);
    posZ = playerStatus->pos.z - (cos_deg(angle) * radius);
    evt_set_variable(script, outX, posX);
    evt_set_variable(script, outZ, posZ);
    return ApiStatus_DONE2;
}
