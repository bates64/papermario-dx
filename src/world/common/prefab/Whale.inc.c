#include "common.h"
#include "effects.h"
#include "world/common/prefab/Whale.h"

#ifndef WHALE_NPC_ID
#define WHALE_NPC_ID 0
#error "WHALE_NPC_ID must be defined"
#endif

#ifndef WHALE_MODEL_TONGUE
#define WHALE_MODEL_TONGUE 0
#error "WHALE_MODEL_TONGUE must be defined"
#endif

#ifndef WHALE_MODEL_EYES_OPEN
#define WHALE_MODEL_EYES_OPEN 0
#error "WHALE_MODEL_EYES_OPEN must be defined"
#endif

#ifndef WHALE_MODEL_EYES_SHUT
#define WHALE_MODEL_EYES_SHUT 0
#error "WHALE_MODEL_EYES_SHUT must be defined"
#endif

#ifndef WHALE_MODEL_JAW
#define WHALE_MODEL_JAW 0
#error "WHALE_MODEL_JAW must be defined"
#endif

#ifndef WHALE_MODEL_LFIN
#define WHALE_MODEL_LFIN 0
#error "WHALE_MODEL_LFIN must be defined"
#endif

#ifndef WHALE_MODEL_RFIN
#define WHALE_MODEL_RFIN 0
#error "WHALE_MODEL_RFIN must be defined"
#endif

#ifndef WHALE_MODEL_GROUP_BODY
#define WHALE_MODEL_GROUP_BODY 0
#error "WHALE_MODEL_GROUP_BODY must be defined"
#endif

#ifndef WHALE_MODEL_BODY
#define WHALE_MODEL_BODY 0
#error "WHALE_MODEL_BODY must be defined"
#endif

#ifndef WHALE_MODEL_BELLY
#define WHALE_MODEL_BELLY 0
#error "WHALE_MODEL_BELLY must be defined"
#endif

#ifndef WHALE_HEAD_OFFSET
#define WHALE_HEAD_OFFSET 0
#error "WHALE_HEAD_OFFSET must be defined"
#endif

#ifndef WHALE_ROOT_OFFSET_X
#define WHALE_ROOT_OFFSET_X 0
#error "WHALE_ROOT_OFFSET_X must be defined"
#endif

#ifndef WHALE_COLLIDER_SPEAK
#define WHALE_COLLIDER_SPEAK 0
#error "WHALE_COLLIDER_SPEAK must be defined"
#endif

#ifndef WHALE_COLLIDER_SIDES
#define WHALE_COLLIDER_SIDES 0
#error "WHALE_COLLIDER_SIDES must be defined"
#endif

// pointer to spout effect is stored in this NPC var
#define NPC_VAR_SPOUT_PTR 0

API_CALLABLE(N(CreateWhaleGeyser)) {
    Bytecode* args = script->ptrReadPos;
    s32 var1 = evt_get_variable(script, *args++);
    f32 var2 = evt_get_float_variable(script, *args++);
    f32 var3 = evt_get_float_variable(script, *args++);
    f32 var4 = evt_get_float_variable(script, *args++);
    f32 var5 = evt_get_float_variable(script, *args++);
    f32 var6 = evt_get_float_variable(script, *args++);
    f32 var7 = evt_get_float_variable(script, *args++);
    s32 var8 = evt_get_variable(script, *args++);
    EffectInstance* outVal;

    fx_effect_3D(var1, var2, var3, var4, var5, var6, var7, var8, &outVal);
    script->varTablePtr[0] = outVal;
    return ApiStatus_DONE2;
}

API_CALLABLE(N(SetWhaleGeyserPos)) {
    Bytecode* args = script->ptrReadPos;
    EffectInstance* effect = (EffectInstance*) evt_get_variable(script, *args++);
    f32 x = evt_get_float_variable(script, *args++);
    f32 y = evt_get_float_variable(script, *args++);
    f32 z = evt_get_float_variable(script, *args++);

    effect->data.whaleSpout->pos.x = x;
    effect->data.whaleSpout->pos.y = y;
    effect->data.whaleSpout->pos.z = z;
    return ApiStatus_DONE2;
}

API_CALLABLE(N(DisposeWhaleGeyser)) {
    Bytecode* args = script->ptrReadPos;
    EffectInstance* effect = (EffectInstance*) evt_get_variable(script, *args++);

    effect->data.whaleSpout->unk_04 = 1;
    return ApiStatus_DONE2;
}

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
    Npc* whale = get_npc_safe(WHALE_NPC_ID);
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
    Npc* whale = N(resolve_npc)(script, npcID);
    f32 y;

    if (whale == nullptr) {
        return ApiStatus_DONE2;
    }

    N(WhaleRootAnimPhase) += 4;
    if (N(WhaleRootAnimPhase) >= 360) {
        N(WhaleRootAnimPhase) -= 360;
    }

    y = whale->pos.y;

    switch (whale->curAnim) {
        case XNIM_Whale_Idle:
        case XNIM_Whale_Talk:
        case XNIM_Whale_Sick:
        case XNIM_Whale_WakeUp:
            y += 2.0f * sin_deg(N(WhaleRootAnimPhase));
            break;
        case XNIM_Whale_OpenMouth:
        case XNIM_Whale_CloseMouth:
        case XNIM_Whale_Sleep:
        case XNIM_Whale_Shiver:
        case XNIM_Whale_Shake:
        case XNIM_Whale_Still:
        case XNIM_Whale_Swim:
        case XNIM_Whale_Spout:
             break;
    }

    evt_set_float_variable(script, outX, whale->pos.x);
    evt_set_float_variable(script, outY, y);
    evt_set_float_variable(script, outZ, whale->pos.z);
    return ApiStatus_DONE2;
}

/// Applies a bend to the copied whale vertices based on their local X position,
/// starting at x = 30 (in local space), and increasing further along the tail.
void N(BendWhaleBody)(Vtx* referenceVertices, Vtx* copiedVertices, s32 numVertices, s32* wagPhasePtr) {
    s16* vtxPos;
    s32 wagPhase;
    s32 bendPow, bendFrac;
    s32 i, j;
    f32 newX, newY;
    f32 angle;
    s32 offset;

    switch (get_npc_safe(WHALE_NPC_ID)->curAnim) {
        case XNIM_Whale_Idle:
        case XNIM_Whale_OpenMouth:
        case XNIM_Whale_CloseMouth:
        case XNIM_Whale_Talk:
        case XNIM_Whale_Sleep:
        case XNIM_Whale_Shiver:
        case XNIM_Whale_Shake:
        case XNIM_Whale_Sick:
        case XNIM_Whale_Still:
        case XNIM_Whale_WakeUp:
            break;
        case XNIM_Whale_Swim:
        case XNIM_Whale_Spout:
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

EvtScript N(EVS_WhaleState_Idle) = {
    Call(CosInterpMinMax, LVarC, LVar0, 30, 60, 30, 0, 0)
    Call(RotateModel, WHALE_MODEL_LFIN, LVar0, 1, 0, 0)
    Call(RotateModel, WHALE_MODEL_RFIN, LVar0, -1, 0, 0)
    Return
    End
};

EvtScript N(EVS_WhaleState_OpenMouth) = {
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
    IfGe(LVarC, 30)
        IfNe(WHALE_COLLIDER_SPEAK, NO_COLLIDER)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, WHALE_COLLIDER_SPEAK, COLLIDER_FLAGS_UPPER_MASK)
        EndIf
        IfNe(WHALE_COLLIDER_SIDES, NO_COLLIDER)
            Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_CLEAR_BITS, WHALE_COLLIDER_SIDES, COLLIDER_FLAGS_UPPER_MASK)
        EndIf
    EndIf
    Return
    End
};

EvtScript N(EVS_WhaleState_CloseMouth) = {
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

EvtScript N(EVS_WhaleState_Sleep) = {
    Return
    End
};

EvtScript N(EVS_WhaleState_Spout) = {
    Call(GetNpcVar, WHALE_NPC_ID, NPC_VAR_SPOUT_PTR, LVar3)
    IfEq(LVar3, nullptr)
        Call(N(GetWhaleHeadPos))
        Call(PlaySoundAt, SOUND_LOOP_WHALE_GEYSER, SOUND_SPACE_DEFAULT, LVar0, LVar1, LVar2)
        Call(N(CreateWhaleGeyser), 0, LVar0, LVar1, LVar2, 0, -1, 0, 30)
        Call(SetNpcVar, WHALE_NPC_ID, NPC_VAR_SPOUT_PTR, LVar0)
    EndIf
    Call(GetNpcVar, WHALE_NPC_ID, NPC_VAR_SPOUT_PTR, LVar3)
    Call(N(GetWhaleHeadPos))
    Call(N(SetWhaleGeyserPos), LVar3, LVar0, LVar1, LVar2)
    Call(CosInterpMinMax, LVarC, LVar0, 30, 60, 30, 0, 0)
    Call(RotateModel, WHALE_MODEL_LFIN, LVar0, 1, 0, 0)
    Call(RotateModel, WHALE_MODEL_RFIN, LVar0, -1, 0, 0)
    Return
    End
};

EvtScript N(EVS_WhaleState_Still) = {
    Return
    End
};

EvtScript N(EVS_WhaleState_WakeUp) = {
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

EvtScript N(EVS_WhaleState_Shiver) = {
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

EvtScript N(EVS_WhaleState_Shake) = {
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

EvtScript N(EVS_WhaleState_QuietTalk) = {
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

EvtScript N(EVS_WhaleState_Swim) = {
    Call(CosInterpMinMax, LVarC, LVar0, 30, 60, 30, 0, 0)
    Call(RotateModel, WHALE_MODEL_LFIN, LVar0, 1, 0, 0)
    Call(RotateModel, WHALE_MODEL_RFIN, LVar0, -1, 0, 0)
    Return
    End
};

EvtScript N(EVS_WhaleState_Talk) = {
    Call(CosInterpMinMax, LVarC, LVar0, 0, 8, 3, 0, 0)
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
    Call(SetNpcVar, WHALE_NPC_ID, NPC_VAR_SPOUT_PTR, nullptr)
    Thread
        Label(0)
        Call(N(MakeWhaleRootPos), WHALE_NPC_ID, LVar0, LVar1, LVar2)
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
        Call(GetNpcYaw, WHALE_NPC_ID, LVar0)
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
        Call(GetNpcAnimation, WHALE_NPC_ID, LVar0)
        IfNe(LVar0, LVarB)
            Set(LVarB, LVar0)
            Set(LVarC, 0)
            IfNe(WHALE_COLLIDER_SPEAK, NO_COLLIDER)
                Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_CLEAR_BITS, WHALE_COLLIDER_SPEAK, COLLIDER_FLAGS_UPPER_MASK)
            EndIf
            Call(EnableModel, WHALE_MODEL_EYES_OPEN, true)
            Call(EnableModel, WHALE_MODEL_EYES_SHUT, false)
            IfNe(LVarB, XNIM_Whale_Spout)
                Call(GetNpcVar, WHALE_NPC_ID, NPC_VAR_SPOUT_PTR, LVar0)
                IfNe(LVar0, nullptr)
                    Call(PlaySound, SOUND_LRAW_WHALE_GEYSER | SOUND_ID_TRIGGER_CHANGE_SOUND)
                    Call(StopTrackingSoundPos, SOUND_LRAW_WHALE_GEYSER)
                    Call(N(DisposeWhaleGeyser), LVar0)
                    Call(SetNpcVar, WHALE_NPC_ID, NPC_VAR_SPOUT_PTR, nullptr)
                EndIf
            EndIf
            Switch(LVarB)
                CaseEq(XNIM_Whale_CloseMouth)
                    Call(PlaySoundAtNpc, WHALE_NPC_ID, SOUND_WHALE_CLOSE_MOUTH, SOUND_SPACE_DEFAULT)
                    Set(LVarD, Ref(N(EVS_WhaleState_CloseMouth)))
                CaseEq(XNIM_Whale_Idle)
                    Set(LVarD, Ref(N(EVS_WhaleState_Idle)))
                CaseEq(XNIM_Whale_OpenMouth)
                    Call(PlaySoundAtNpc, WHALE_NPC_ID, SOUND_WHALE_OPEN_MOUTH, SOUND_SPACE_DEFAULT)
                    Set(LVarD, Ref(N(EVS_WhaleState_OpenMouth)))
                CaseEq(XNIM_Whale_Swim)
                    Set(LVarD, Ref(N(EVS_WhaleState_Swim)))
                CaseEq(XNIM_Whale_Talk)
                    Set(LVarD, Ref(N(EVS_WhaleState_Talk)))
                CaseEq(XNIM_Whale_Sleep)
                    Set(LVarD, Ref(N(EVS_WhaleState_Sleep)))
                    Call(EnableModel, WHALE_MODEL_EYES_OPEN, false)
                    Call(EnableModel, WHALE_MODEL_EYES_SHUT, false)
                CaseEq(XNIM_Whale_Shiver)
                    Set(LVarD, Ref(N(EVS_WhaleState_Shiver)))
                    Call(EnableModel, WHALE_MODEL_EYES_OPEN, false)
                    Call(EnableModel, WHALE_MODEL_EYES_SHUT, false)
                CaseEq(XNIM_Whale_Shake)
                    Set(LVarD, Ref(N(EVS_WhaleState_Shake)))
                    Call(EnableModel, WHALE_MODEL_EYES_OPEN, false)
                    Call(EnableModel, WHALE_MODEL_EYES_SHUT, false)
                CaseEq(XNIM_Whale_Sick)
                    Set(LVarD, Ref(N(EVS_WhaleState_QuietTalk)))
                CaseEq(XNIM_Whale_Spout)
                    Set(LVarD, Ref(N(EVS_WhaleState_Spout)))
                CaseEq(XNIM_Whale_Still)
                    Set(LVarD, Ref(N(EVS_WhaleState_Still)))
                CaseEq(XNIM_Whale_WakeUp)
                    Set(LVarD, Ref(N(EVS_WhaleState_WakeUp)))
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
#undef WHALE_SPOUT_FIN_PERIOD
#undef WHALE_COLLIDER_SPEAK
#undef WHALE_COLLIDER_SIDES
