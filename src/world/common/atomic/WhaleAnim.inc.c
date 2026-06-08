#include "common.h"
#include "sprite/npc/Kolorado.h"

u32 N(WhaleRootAnimPhase) = 0;
s32 N(WhaleBodyAnimPhase) = -1;
s32 N(WhaleBellyAnimPhase) = -1;

Npc* N(resolve_npc)(Evt* script, s32 npcIdOrPtr) {
    if (npcIdOrPtr == NPC_SELF) {
        return get_npc_safe(script->owner2.npcID);
    } else if (npcIdOrPtr >= EVT_LIMIT) {
        return get_npc_safe(npcIdOrPtr);
    } else {
        return (Npc*) npcIdOrPtr;
    }
}

API_CALLABLE(N(MakeWhaleRootPos)) {
    Bytecode* args = script->ptrReadPos;
    s32 npcID = evt_get_variable(script, *args++);
    s32 outX = *args++;
    s32 outY = *args++;
    s32 outZ = *args++;
    Npc* npc = N(resolve_npc)(script, npcID);
    f32 y;

    if (npc == nullptr) {
        return ApiStatus_DONE2;
    }

    N(WhaleRootAnimPhase) += 4;
    if (N(WhaleRootAnimPhase) >= 360) {
        N(WhaleRootAnimPhase) -= 360;
    }

    y = npc->pos.y;
    if (npc->curAnim == ANIM_Kolorado_Still ||
        npc->curAnim == ANIM_Kolorado_Walk ||
        npc->curAnim == ANIM_Kolorado_Talk ||
        npc->curAnim == ANIM_Kolorado_HurtStill)
    {
        y += 2.0f * sin_deg(N(WhaleRootAnimPhase));
    }

    evt_set_float_variable(script, outX, npc->pos.x);
    evt_set_float_variable(script, outY, y);
    evt_set_float_variable(script, outZ, npc->pos.z);
    return ApiStatus_DONE2;
}

/// Applies a bend to the copied whale vertices based on their local X position,
/// starting at x = 30 (in local space), and increasing further along the tail.
void N(BendWhaleBody)(Vtx* referenceVertices, Vtx* copiedVertices, s32 numVertices, s32* wagPhasePtr) {
    s32 wagPhase;
    s32 bendPow, bendFrac;
    s32 i, j;
    s16* vtxPos;
    f32 newX, newY;
    f32 angle;
    s32 offset;

    switch (get_npc_safe(NPC_Whale)->curAnim) {
        case ANIM_Kolorado_Still:
        case ANIM_Kolorado_Yell:
        case ANIM_Kolorado_IdleSad:
        case ANIM_Kolorado_Walk:
        case ANIM_Kolorado_WalkSad:
        case ANIM_Kolorado_Run:
        case ANIM_Kolorado_Panic:
        case ANIM_Kolorado_Talk:
        case ANIM_Kolorado_TalkSad:
        case ANIM_Kolorado_Fallen:
        case ANIM_Kolorado_HurtStill:
            break;
        case ANIM_Kolorado_Idle:
        case ANIM_Kolorado_Shout:
            if (*wagPhasePtr < 0) {
                *wagPhasePtr = 0;
            }
            break;
    }

    wagPhase = *wagPhasePtr;

    for (i = 0; i < numVertices; i++) {
        vtxPos = referenceVertices[i].v.ob;
        offset = 30;

        if (vtxPos[0] > 30) {
            newX = 0.0f;
            newY = 0.0f;
            // determine number of bend stages to apply
            bendPow = (vtxPos[0] - offset) / 10;
            bendFrac = vtxPos[0] - ((bendPow * 10) + offset);
            // apply formula once per 10 unit interval from X = 30
            for (j = 0; j < bendPow; j++) {
                angle = (j / 15.0f) + ((j / 40.0f) * sin_deg(wagPhase));
                newX += cos_rad(angle) * 10.0f;
                newY += sin_rad(angle) * 10.0f;
            }
            // add fractional part between current and next interval
            angle = (j / 15.0f) + ((j / 40.0f) * sin_deg(wagPhase));
            newX += bendFrac * cos_rad(angle);
            newY += bendFrac * sin_rad(angle);

            copiedVertices[i].v.ob[0] = newX;
            copiedVertices[i].v.ob[1] = vtxPos[1] + newY;
        }
    }
}

void N(build_gfx_whale_body)(void) {
    Vtx* firstVertex;
    Vtx* copiedVertices;
    s32 numVertices;

    mdl_get_copied_vertices(VTX_COPY_1, &firstVertex, &copiedVertices, &numVertices);
    N(BendWhaleBody)(firstVertex, copiedVertices, numVertices, &N(WhaleBodyAnimPhase));

    gSPDisplayList(gMainGfxPos++, mdl_get_copied_gfx(VTX_COPY_1));
    if (N(WhaleBodyAnimPhase) >= 0) {
        N(WhaleBodyAnimPhase) += 4;
    }
    if (N(WhaleBodyAnimPhase) >= 360) {
        N(WhaleBodyAnimPhase) = -1;
    }
}

void N(build_gfx_whale_belly)(void) {
    Vtx* firstVertex;
    Vtx* copiedVertices;
    s32 numVertices;

    mdl_get_copied_vertices(VTX_COPY_2, &firstVertex, &copiedVertices, &numVertices);
    N(BendWhaleBody)(firstVertex, copiedVertices, numVertices, &N(WhaleBellyAnimPhase));

    gSPDisplayList(gMainGfxPos++, mdl_get_copied_gfx(VTX_COPY_2));
    if (N(WhaleBellyAnimPhase) >= 0) {
        N(WhaleBellyAnimPhase) += 4;
    }
    if (N(WhaleBellyAnimPhase) >= 360) {
        N(WhaleBellyAnimPhase) = -1;
    }
}
