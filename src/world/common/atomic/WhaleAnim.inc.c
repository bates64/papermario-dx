#include "common.h"
#include "effects.h"
#include "sprite/npc/Kolorado.h"

#ifndef WHALE_SHOUT_FIN_PERIOD
#define WHALE_SHOUT_FIN_PERIOD 30
#endif

#ifndef WHALE_WALK_ANGLE
#define WHALE_WALK_ANGLE 8
#endif

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

API_CALLABLE(N(GetWhaleHeadPos)) {
    Npc* whale = get_npc_safe(NPC_Whale);
    f32 yaw = -whale->yaw;
    f32 x = whale->pos.x + 30.0f + (sin_deg(yaw) * WHALE_HEAD_OFFSET);
    f32 z = whale->pos.z + (cos_deg(yaw) * WHALE_HEAD_OFFSET);
    f32 y = whale->pos.y + 50.0f;

    evt_set_float_variable(script, LVar0, x);
    evt_set_float_variable(script, LVar1, y);
    evt_set_float_variable(script, LVar2, z);
    return ApiStatus_DONE2;
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

EvtScript N(EVS_WhaleState_Still) = {
    Call(CosInterpMinMax, LVarC, LVar0, 30, 60, 30, 0, 0)
    Call(RotateModel, WHALE_MODEL_LFIN, LVar0, 1, 0, 0)
    Call(RotateModel, WHALE_MODEL_RFIN, LVar0, -1, 0, 0)
    Return
    End
};

EvtScript N(EVS_WhaleState_Yell) = {
    Call(CosInterpMinMax, LVarC, LVar0, 0, 30, 30, 1, 0)
    SetF(LVar1, LVar0)
    DivF(LVar1, Float(3.0))
    Call(RotateModel, WHALE_MODEL_JAW, LVar0, 0, 0, 1)
    Call(RotateGroup, WHALE_MODEL_GROUP_BODY, LVar1, 0, 0, -1)
    Call(TranslateModel, WHALE_MODEL_EYES_OPEN, -5, -68, 0)
    Call(TranslateModel, WHALE_MODEL_EYES_SHUT, -5, -68, 0)
    Call(TranslateModel, WHALE_MODEL_LFIN, 60, 29, -51)
    Call(TranslateModel, WHALE_MODEL_RFIN, 60, 29, 51)
    Call(RotateModel, WHALE_MODEL_EYES_OPEN, LVar1, 0, 0, -1)
    Call(RotateModel, WHALE_MODEL_EYES_SHUT, LVar1, 0, 0, -1)
    Call(RotateModel, WHALE_MODEL_LFIN, LVar1, 0, 0, -1)
    Call(RotateModel, WHALE_MODEL_RFIN, LVar1, 0, 0, -1)
    Call(TranslateModel, WHALE_MODEL_EYES_OPEN, 5, 68, 0)
    Call(TranslateModel, WHALE_MODEL_EYES_SHUT, 5, 68, 0)
    Call(TranslateModel, WHALE_MODEL_LFIN, -60, -29, 51)
    Call(TranslateModel, WHALE_MODEL_RFIN, -60, -29, -51)
    Call(CosInterpMinMax, LVarC, LVar0, 0, -40, 30, 1, 0)
    Call(TranslateModel, WHALE_MODEL_TONGUE, LVar0, 0, 0)
#ifdef WHALE_COLLIDER_INTERACT
    IfGe(LVarC, 30)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, WHALE_COLLIDER_INTERACT, COLLIDER_FLAGS_UPPER_MASK)
        Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_CLEAR_BITS, WHALE_COLLIDER_SIDES, COLLIDER_FLAGS_UPPER_MASK)
    EndIf
#endif
    Return
    End
};

EvtScript N(EVS_WhaleState_IdleSad) = {
    Call(CosInterpMinMax, LVarC, LVar0, 0, -30, 8, 1, 0)
    AddF(LVar0, Float(30.0))
    SetF(LVar1, LVar0)
    DivF(LVar1, Float(3.0))
    Call(RotateModel, WHALE_MODEL_JAW, LVar0, 0, 0, 1)
    Call(RotateGroup, WHALE_MODEL_GROUP_BODY, LVar1, 0, 0, -1)
    Call(TranslateModel, WHALE_MODEL_EYES_OPEN, -5, -68, 0)
    Call(TranslateModel, WHALE_MODEL_EYES_SHUT, -5, -68, 0)
    Call(TranslateModel, WHALE_MODEL_LFIN, 60, 29, -51)
    Call(TranslateModel, WHALE_MODEL_RFIN, 60, 29, 51)
    Call(RotateModel, WHALE_MODEL_EYES_OPEN, LVar1, 0, 0, -1)
    Call(RotateModel, WHALE_MODEL_EYES_SHUT, LVar1, 0, 0, -1)
    Call(RotateModel, WHALE_MODEL_LFIN, LVar1, 0, 0, -1)
    Call(RotateModel, WHALE_MODEL_RFIN, LVar1, 0, 0, -1)
    Call(TranslateModel, WHALE_MODEL_EYES_OPEN, 5, 68, 0)
    Call(TranslateModel, WHALE_MODEL_EYES_SHUT, 5, 68, 0)
    Call(TranslateModel, WHALE_MODEL_LFIN, -60, -29, 51)
    Call(TranslateModel, WHALE_MODEL_RFIN, -60, -29, -51)
    Call(CosInterpMinMax, LVarC, LVar0, 0, -40, 120, 1, 0)
    Call(TranslateModel, WHALE_MODEL_TONGUE, LVar0, 0, 0)
    Return
    End
};

EvtScript N(EVS_WhaleState_WalkSad) = {
    Return
    End
};

EvtScript N(EVS_WhaleState_Shout) = {
#ifdef WHALE_SHOUT_USES_DAMAGE_STARS
    Set(LVar1, LVarC)
    Mod(LVar1, 4)
    IfEq(LVar1, 0)
        Call(N(GetWhaleHeadPos))
        PlayEffect(EFFECT_DAMAGE_STARS, FX_DAMAGE_STARS_2, LVar0, LVar1, LVar2, 0, -1, 0, 5)
    EndIf
#else
    Call(GetNpcVar, NPC_Whale, 0, LVar3)
    IfEq(LVar3, 0)
        Call(N(GetWhaleHeadPos))
        Call(PlaySoundAt, SOUND_LOOP_WHALE_GEYSER, SOUND_SPACE_DEFAULT, LVar0, LVar1, LVar2)
        Call(N(CreateWhaleGeyser), 0, LVar0, LVar1, LVar2, 0, -1, 0, 30)
        Call(SetNpcVar, NPC_Whale, 0, LVar0)
    EndIf
    Call(GetNpcVar, NPC_Whale, 0, LVar3)
    Call(N(GetWhaleHeadPos))
    Call(N(SetWhaleGeyserPos), LVar3, LVar0, LVar1, LVar2)
#endif
    Call(CosInterpMinMax, LVarC, LVar0, 30, 60, WHALE_SHOUT_FIN_PERIOD, 0, 0)
    Call(RotateModel, WHALE_MODEL_LFIN, LVar0, 1, 0, 0)
    Call(RotateModel, WHALE_MODEL_RFIN, LVar0, -1, 0, 0)
    Return
    End
};

EvtScript N(EVS_WhaleState_TalkSad) = {
    Return
    End
};

EvtScript N(EVS_WhaleState_HurtStill) = {
    IfGe(LVarC, 0)
        IfLe(LVarC, 2)
            Call(EnableModel, WHALE_MODEL_EYES_OPEN, false)
            Call(EnableModel, WHALE_MODEL_EYES_SHUT, true)
            Return
        EndIf
    EndIf
    IfEq(LVarC, 15)
        Call(EnableModel, WHALE_MODEL_EYES_OPEN, false)
        Call(EnableModel, WHALE_MODEL_EYES_SHUT, true)
        Return
    EndIf
    IfEq(LVarC, 22)
        Call(EnableModel, WHALE_MODEL_EYES_OPEN, false)
        Call(EnableModel, WHALE_MODEL_EYES_SHUT, true)
        Return
    EndIf
    Call(EnableModel, WHALE_MODEL_EYES_OPEN, true)
    Call(EnableModel, WHALE_MODEL_EYES_SHUT, false)
    Return
    End
};

EvtScript N(EVS_WhaleState_Run) = {
    Set(LVar0, LVarC)
    Div(LVar0, 20)
    Mod(LVar0, 2)
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(CosInterpMinMax, LVarC, LVar0, Float(-1.0), Float(1.0), 3, 0, 0)
    Call(TranslateModel, WHALE_MODEL_JAW, LVar0, 0, 0)
    Call(TranslateGroup, WHALE_MODEL_GROUP_BODY, LVar0, 0, 0)
    Call(TranslateModel, WHALE_MODEL_EYES_OPEN, LVar0, 0, 0)
    Call(TranslateModel, WHALE_MODEL_EYES_SHUT, LVar0, 0, 0)
    Call(TranslateModel, WHALE_MODEL_LFIN, LVar0, 0, 0)
    Call(TranslateModel, WHALE_MODEL_RFIN, LVar0, 0, 0)
    Call(TranslateModel, WHALE_MODEL_LFIN, LVar0, 0, 0)
    Call(TranslateModel, WHALE_MODEL_RFIN, LVar0, 0, 0)
    Return
    End
};

EvtScript N(EVS_WhaleState_Panic) = {
    Call(CosInterpMinMax, LVarC, LVar0, Float(-6.0), Float(6.0), 3, 0, 0)
    Call(CosInterpMinMax, LVarC, LVar1, Float(6.0), Float(-6.0), 2, 0, 0)
    Call(TranslateModel, WHALE_MODEL_JAW, LVar0, LVar1, 0)
    Call(TranslateGroup, WHALE_MODEL_GROUP_BODY, LVar0, LVar1, 0)
    Call(TranslateModel, WHALE_MODEL_EYES_OPEN, LVar0, LVar1, 0)
    Call(TranslateModel, WHALE_MODEL_EYES_SHUT, LVar0, LVar1, 0)
    Call(TranslateModel, WHALE_MODEL_LFIN, LVar0, LVar1, 0)
    Call(TranslateModel, WHALE_MODEL_RFIN, LVar0, LVar1, 0)
    Call(TranslateModel, WHALE_MODEL_LFIN, LVar0, LVar1, 0)
    Call(TranslateModel, WHALE_MODEL_RFIN, LVar0, LVar1, 0)
    Return
    End
};

EvtScript N(EVS_WhaleState_Talk) = {
    Set(LVar0, LVarC)
    Div(LVar0, 20)
    Mod(LVar0, 2)
    IfEq(LVar0, 0)
        Return
    EndIf
    Call(CosInterpMinMax, LVarC, LVar0, Float(-1.0), Float(1.0), 3, 0, 0)
    Call(TranslateModel, WHALE_MODEL_JAW, LVar0, 0, 0)
    Call(TranslateGroup, WHALE_MODEL_GROUP_BODY, LVar0, 0, 0)
    Call(TranslateModel, WHALE_MODEL_EYES_OPEN, LVar0, 0, 0)
    Call(TranslateModel, WHALE_MODEL_EYES_SHUT, LVar0, 0, 0)
    Call(TranslateModel, WHALE_MODEL_LFIN, LVar0, 0, 0)
    Call(TranslateModel, WHALE_MODEL_RFIN, LVar0, 0, 0)
    Call(TranslateModel, WHALE_MODEL_LFIN, LVar0, 0, 0)
    Call(TranslateModel, WHALE_MODEL_RFIN, LVar0, 0, 0)
    Return
    End
};

EvtScript N(EVS_WhaleState_Idle) = {
    Call(CosInterpMinMax, LVarC, LVar0, 30, 60, 30, 0, 0)
    Call(RotateModel, WHALE_MODEL_LFIN, LVar0, 1, 0, 0)
    Call(RotateModel, WHALE_MODEL_RFIN, LVar0, -1, 0, 0)
    Return
    End
};

EvtScript N(EVS_WhaleState_Walk) = {
    Call(CosInterpMinMax, LVarC, LVar0, 0, WHALE_WALK_ANGLE, 3, 0, 0)
    Set(LVar1, LVar0)
    Div(LVar1, 3)
    Call(RotateModel, WHALE_MODEL_JAW, LVar0, 0, 0, 1)
    Call(RotateGroup, WHALE_MODEL_GROUP_BODY, LVar1, 0, 0, -1)
    Call(TranslateModel, WHALE_MODEL_EYES_OPEN, -5, -68, 0)
    Call(TranslateModel, WHALE_MODEL_EYES_SHUT, -5, -68, 0)
    Call(TranslateModel, WHALE_MODEL_LFIN, 60, 29, -51)
    Call(TranslateModel, WHALE_MODEL_RFIN, 60, 29, 51)
    Call(RotateModel, WHALE_MODEL_EYES_OPEN, LVar1, 0, 0, -1)
    Call(RotateModel, WHALE_MODEL_EYES_SHUT, LVar1, 0, 0, -1)
    Call(RotateModel, WHALE_MODEL_LFIN, LVar1, 0, 0, -1)
    Call(RotateModel, WHALE_MODEL_RFIN, LVar1, 0, 0, -1)
    Call(TranslateModel, WHALE_MODEL_EYES_OPEN, 5, 68, 0)
    Call(TranslateModel, WHALE_MODEL_EYES_SHUT, 5, 68, 0)
    Call(TranslateModel, WHALE_MODEL_LFIN, -60, -29, 51)
    Call(TranslateModel, WHALE_MODEL_RFIN, -60, -29, -51)
    Set(LVar0, LVarC)
    Mul(LVar0, 2)
    Call(CosInterpMinMax, LVar0, LVar0, 30, 60, 3, 0, 0)
    Call(RotateModel, WHALE_MODEL_LFIN, LVar0, 1, 0, 0)
    Call(RotateModel, WHALE_MODEL_RFIN, LVar0, -1, 0, 0)
    Return
    End
};

// main script
EvtScript N(EVS_SetupWhale) = {
    SetGroup(EVT_GROUP_NEVER_PAUSE)
    Call(MakeLocalVertexCopy, VTX_COPY_1, WHALE_MODEL_BODY, true)
    Call(SetCustomGfxBuilders, CUSTOM_GFX_1, Ref(N(build_gfx_whale_body)), nullptr)
    Call(SetModelCustomGfx, WHALE_MODEL_BODY, CUSTOM_GFX_1, -1)
    Call(MakeLocalVertexCopy, VTX_COPY_2, WHALE_MODEL_BELLY, true)
    Call(SetCustomGfxBuilders, CUSTOM_GFX_2, Ref(N(build_gfx_whale_belly)), nullptr)
    Call(SetModelCustomGfx, WHALE_MODEL_BELLY, CUSTOM_GFX_2, -1)
#ifdef WHALE_RESET_GEYSER_VAR
    Call(SetNpcVar, NPC_Whale, 0, 0)
#endif
    Thread
        Label(0)
        Call(N(MakeWhaleRootPos), NPC_Whale, LVar0, LVar1, LVar2)
        SubF(LVar0, -80)
        SubF(LVar1, -18)
        SubF(LVar2, 420)
        AddF(LVar0, WHALE_ROOT_OFFSET_X)
        AddF(LVar1, -20)
        AddF(LVar2, 0)
        Call(TranslateModel, WHALE_MODEL_TONGUE, LVar0, LVar1, LVar2)
        Call(TranslateModel, WHALE_MODEL_EYES_OPEN, LVar0, LVar1, LVar2)
        Call(TranslateModel, WHALE_MODEL_EYES_SHUT, LVar0, LVar1, LVar2)
        Call(TranslateModel, WHALE_MODEL_JAW, LVar0, LVar1, LVar2)
        Call(TranslateModel, WHALE_MODEL_LFIN, LVar0, LVar1, LVar2)
        Call(TranslateModel, WHALE_MODEL_RFIN, LVar0, LVar1, LVar2)
        Call(TranslateGroup, WHALE_MODEL_GROUP_BODY, LVar0, LVar1, LVar2)
        Call(GetNpcYaw, NPC_Whale, LVar0)
        MulF(LVar0, -1)
        AddF(LVar0, -90)
        Call(TranslateModel, WHALE_MODEL_TONGUE, -100, 0, 0)
        Call(TranslateModel, WHALE_MODEL_EYES_OPEN, -100, 0, 0)
        Call(TranslateModel, WHALE_MODEL_EYES_SHUT, -100, 0, 0)
        Call(TranslateModel, WHALE_MODEL_JAW, -100, 0, 0)
        Call(TranslateModel, WHALE_MODEL_LFIN, -100, 0, 0)
        Call(TranslateModel, WHALE_MODEL_RFIN, -100, 0, 0)
        Call(TranslateGroup, WHALE_MODEL_GROUP_BODY, -100, 0, 0)
        Call(TranslateModel, WHALE_MODEL_TONGUE, 100, -1, 0)
        Call(TranslateModel, WHALE_MODEL_EYES_OPEN, -5, -68, 0)
        Call(TranslateModel, WHALE_MODEL_EYES_SHUT, -5, -68, 0)
        Call(TranslateModel, WHALE_MODEL_JAW, 102, 4, 0)
        Call(TranslateModel, WHALE_MODEL_LFIN, 60, 29, -51)
        Call(TranslateModel, WHALE_MODEL_RFIN, 60, 29, 51)
        Call(RotateModel, WHALE_MODEL_TONGUE, LVar0, 0, 1, 0)
        Call(RotateModel, WHALE_MODEL_EYES_OPEN, LVar0, 0, 1, 0)
        Call(RotateModel, WHALE_MODEL_EYES_SHUT, LVar0, 0, 1, 0)
        Call(RotateModel, WHALE_MODEL_JAW, LVar0, 0, 1, 0)
        Call(RotateModel, WHALE_MODEL_LFIN, LVar0, 0, 1, 0)
        Call(RotateModel, WHALE_MODEL_RFIN, LVar0, 0, 1, 0)
        Call(RotateGroup, WHALE_MODEL_GROUP_BODY, LVar0, 0, 1, 0)
        Call(TranslateModel, WHALE_MODEL_TONGUE, -100, 1, 0)
        Call(TranslateModel, WHALE_MODEL_EYES_OPEN, 5, 68, 0)
        Call(TranslateModel, WHALE_MODEL_EYES_SHUT, 5, 68, 0)
        Call(TranslateModel, WHALE_MODEL_JAW, -102, -4, 0)
        Call(TranslateModel, WHALE_MODEL_LFIN, -60, -29, 51)
        Call(TranslateModel, WHALE_MODEL_RFIN, -60, -29, -51)
        Call(TranslateModel, WHALE_MODEL_TONGUE, 100, 0, 0)
        Call(TranslateModel, WHALE_MODEL_EYES_OPEN, 100, 0, 0)
        Call(TranslateModel, WHALE_MODEL_EYES_SHUT, 100, 0, 0)
        Call(TranslateModel, WHALE_MODEL_JAW, 100, 0, 0)
        Call(TranslateModel, WHALE_MODEL_LFIN, 100, 0, 0)
        Call(TranslateModel, WHALE_MODEL_RFIN, 100, 0, 0)
        Call(TranslateGroup, WHALE_MODEL_GROUP_BODY, 100, 0, 0)
        Call(GetNpcAnimation, NPC_Whale, LVar0)
        IfNe(LVar0, LVarB)
            Set(LVarB, LVar0)
            Set(LVarC, 0)
#ifdef WHALE_COLLIDER_INTERACT
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_CLEAR_BITS, WHALE_COLLIDER_INTERACT, COLLIDER_FLAGS_UPPER_MASK)
#endif
            Call(EnableModel, WHALE_MODEL_EYES_OPEN, true)
            Call(EnableModel, WHALE_MODEL_EYES_SHUT, false)
#ifndef WHALE_SHOUT_USES_DAMAGE_STARS
            IfNe(LVarB, ANIM_Kolorado_Shout)
                Call(GetNpcVar, NPC_Whale, 0, LVar0)
                IfNe(LVar0, 0)
                    Call(PlaySound, SOUND_LRAW_WHALE_GEYSER | SOUND_ID_TRIGGER_CHANGE_SOUND)
                    Call(StopTrackingSoundPos, SOUND_LRAW_WHALE_GEYSER)
                    Call(N(DisposeWhaleGeyser), LVar0)
                    Call(SetNpcVar, NPC_Whale, 0, 0)
                EndIf
            EndIf
#endif
            Switch(LVarB)
                CaseEq(ANIM_Kolorado_IdleSad)
#ifndef WHALE_DISABLE_MOUTH_SOUNDS
                    Call(PlaySoundAtNpc, NPC_Whale, SOUND_WHALE_CLOSE_MOUTH, SOUND_SPACE_DEFAULT)
#endif
                    Set(LVarD, Ref(N(EVS_WhaleState_IdleSad)))
                CaseEq(ANIM_Kolorado_Still)
                    Set(LVarD, Ref(N(EVS_WhaleState_Still)))
                CaseEq(ANIM_Kolorado_Yell)
#ifndef WHALE_DISABLE_MOUTH_SOUNDS
                    Call(PlaySoundAtNpc, NPC_Whale, SOUND_WHALE_OPEN_MOUTH, SOUND_SPACE_DEFAULT)
#endif
                    Set(LVarD, Ref(N(EVS_WhaleState_Yell)))
                CaseEq(ANIM_Kolorado_Idle)
                    Set(LVarD, Ref(N(EVS_WhaleState_Idle)))
                CaseEq(ANIM_Kolorado_Walk)
                    Set(LVarD, Ref(N(EVS_WhaleState_Walk)))
                CaseEq(ANIM_Kolorado_WalkSad)
                    Set(LVarD, Ref(N(EVS_WhaleState_WalkSad)))
                    Call(EnableModel, WHALE_MODEL_EYES_OPEN, false)
                    Call(EnableModel, WHALE_MODEL_EYES_SHUT, false)
                CaseEq(ANIM_Kolorado_Run)
                    Set(LVarD, Ref(N(EVS_WhaleState_Run)))
                    Call(EnableModel, WHALE_MODEL_EYES_OPEN, false)
                    Call(EnableModel, WHALE_MODEL_EYES_SHUT, false)
                CaseEq(ANIM_Kolorado_Panic)
                    Set(LVarD, Ref(N(EVS_WhaleState_Panic)))
                    Call(EnableModel, WHALE_MODEL_EYES_OPEN, false)
                    Call(EnableModel, WHALE_MODEL_EYES_SHUT, false)
                CaseEq(ANIM_Kolorado_Talk)
                    Set(LVarD, Ref(N(EVS_WhaleState_Talk)))
                CaseEq(ANIM_Kolorado_Shout)
                    Set(LVarD, Ref(N(EVS_WhaleState_Shout)))
                CaseEq(ANIM_Kolorado_TalkSad)
                    Set(LVarD, Ref(N(EVS_WhaleState_TalkSad)))
                CaseEq(ANIM_Kolorado_HurtStill)
                    Set(LVarD, Ref(N(EVS_WhaleState_HurtStill)))
            EndSwitch
        EndIf
        ExecWait(LVarD)
        Add(LVarC, 1)
        IfGt(LVarC, 1000)
            Set(LVarC, 0)
        EndIf
        Goto(0)
    EndThread
    Return
    End
};

EvtScript N(EVS_SetWhaleIdleSad) = {
    Call(SetNpcAnimation, NPC_Whale, ANIM_Kolorado_IdleSad)
    Return
    End
};

#undef WHALE_MODEL_TONGUE
#undef WHALE_MODEL_EYES_OPEN
#undef WHALE_MODEL_EYES_SHUT
#undef WHALE_MODEL_JAW
#undef WHALE_MODEL_LFIN
#undef WHALE_MODEL_RFIN
#undef WHALE_MODEL_GROUP_BODY
#undef WHALE_MODEL_BODY
#undef WHALE_MODEL_BELLY
#undef WHALE_HEAD_OFFSET
#undef WHALE_ROOT_OFFSET_X
#undef WHALE_SHOUT_FIN_PERIOD
#undef WHALE_WALK_ANGLE
#undef WHALE_COLLIDER_INTERACT
#undef WHALE_COLLIDER_SIDES
#undef WHALE_SHOUT_USES_DAMAGE_STARS
#undef WHALE_DISABLE_MOUTH_SOUNDS
#undef WHALE_RESET_GEYSER_VAR
