#pragma once
#include "base.h"
#include "world/ai.h"

// Supposed to fired when the player enters a narrow cone, signaling the Bullet Bill at NPC ID + 1.
// Requires an adjacent Bullet Bill whose AI consumes var 0 and resets it after firing.
// ... but the Bullet Bill AI is empty, its spawn position is discarded, and the wait exits immediately.

// waits for the player to enter a cone extending from the NPC
// LVar0: max distance (out: true)
// LVar1: dist metric: 0 = 3D distance, 1 = planar distance
// LVar2: cone yaw, or -1 to track NPC yaw
// LVar3: full cone width
// LVarA: waiting animation
API_CALLABLE(N(BetaBlasterAI_AwaitPlayerAhead)) {
    Npc* npc;
    f32 playerDirection, facingDirection;
    PlayerStatus* playerStatus;
    PartnerStatus* partnerStatus;

    npc = get_npc_unsafe(script->owner1.enemy->npcID);
    playerStatus = &gPlayerStatus;
    partnerStatus = &gPartnerStatus;

    if (isInitialCall) {
        script->functionTemp[0] = 0;
    }

    switch (script->functionTemp[0]) {
        case 0:
            // initialize detection
            npc->planarFlyDist = evt_get_float_variable(script, LVar0);
            npc->duration = evt_get_variable(script, LVar1); // bad npc name
            script->functionTemp[1] = evt_get_variable(script, LVar2);
            script->functionTemp[2] = evt_get_variable(script, LVar3) / 2;
            npc->curAnim = script->varTable[10];
            script->functionTemp[0] = 1;
            break;
        case 1:
            if (partnerStatus->actingPartner == PARTNER_BOW) {
                break;
            }

            // only distance modes 0 and 1 are valid
            if (npc->duration != 0 && npc->duration != 1) {
                break;
            }

            if (npc->duration == 0) {
                // use 3D distance
                if (sqrtf(SQ((playerStatus->pos.x - npc->pos.x)) +
                        SQ((playerStatus->pos.y - npc->pos.y)) +
                        SQ((playerStatus->pos.z - npc->pos.z))) <= npc->planarFlyDist) {
                    playerDirection = atan2(npc->pos.x, npc->pos.z,
                        playerStatus->pos.x, playerStatus->pos.z);
                    facingDirection = script->functionTemp[1] == -1 ? npc->yaw : script->functionTemp[1];

                    if (fabsf(get_clamped_angle_diff(facingDirection, playerDirection)) < script->functionTemp[2]) {
                        script->varTable[0] = 1;
                        return ApiStatus_DONE2;
                    }
                }
            } else {
                // use planar distance
                if (dist2D(npc->pos.x, npc->pos.z, playerStatus->pos.x, playerStatus->pos.z) <= npc->planarFlyDist) {
                    playerDirection = atan2(npc->pos.x, npc->pos.z,
                        playerStatus->pos.x, playerStatus->pos.z);
                    facingDirection = script->functionTemp[1] == -1 ? npc->yaw : script->functionTemp[1];

                    if (fabsf(get_clamped_angle_diff(facingDirection, playerDirection)) < script->functionTemp[2]) {
                        script->varTable[0] = 1;
                        return ApiStatus_DONE2;
                    }
                }
            }
            break;
    }
    return ApiStatus_BLOCK;
}

EvtScript N(EVS_BetaBlasterAI_AwaitPlayerAhead) = {
    Call(N(BetaBlasterAI_AwaitPlayerAhead))
    Return
    End
};

EvtScript N(EVS_NpcAI_BillBlaster_Beta) = {
    Label(0)
        // wait until the player is within 400 units and 5 degrees of the firing angle
        SetF(LVar0, Float(400.0))
        Set(LVar1, 1)
        Call(GetNpcYaw, NPC_SELF, LVar2)
        Set(LVar3, 10)
        Set(LVarA, ANIM_BillBlaster_Idle)
        Set(LVarB, ANIM_BillBlaster_Idle)
        ExecWait(N(EVS_BetaBlasterAI_AwaitPlayerAhead))
        Call(SetNpcAnimation, NPC_SELF, ANIM_BillBlaster_Fire)
        Wait(15)
        // calculate the muzzle position, but do not use it (?)
        Call(GetNpcPos, NPC_SELF, LVar0, LVar1, LVar2)
        Call(GetNpcYaw, NPC_SELF, LVar3)
        Call(AddVectorPolar, LVar0, LVar2, Float(20.0), LVar3)
        Add(LVar1, 12)
        Call(SetNpcAnimation, NPC_SELF, ANIM_BillBlaster_Idle)
        // signal the Bullet Bill at the next NPC ID
        Call(GetSelfNpcID, LVar0)
        Add(LVar0, 1)
        Call(SetNpcVar, LVar0, 0, 1)
        // wait for the Bullet Bill variable to be nonzero
        Label(1)
            Call(GetSelfNpcID, LVar0)
            Add(LVar0, 1)
            Call(GetNpcVar, LVar0, 0, LVar1)
            IfEq(LVar1, 0)
                Wait(1)
                Goto(1)
            EndIf
        // wait 30-60 frames before firing again
        Call(RandInt, 30, LVar0)
        Add(LVar0, 30)
        Wait(LVar0)
        Goto(0)
    Return
    End
};

EvtScript N(EVS_NpcCreate_BillBlaster_Beta) = {
    Call(SetSelfEnemyFlagBits, ENEMY_FLAG_ACTIVE_WHILE_OFFSCREEN, true)
    Return
    End
};

EvtScript N(EVS_NpcHit_BillBlaster_Beta) = {
    Call(SetBattleMusic, SONG_SPECIAL_BATTLE)
    Call(GetOwnerEncounterTrigger, LVar0)
    Switch(LVar0)
        CaseEq(ENCOUNTER_TRIGGER_NONE)
        CaseOrEq(ENCOUNTER_TRIGGER_JUMP)
        CaseOrEq(ENCOUNTER_TRIGGER_HAMMER)
        CaseOrEq(ENCOUNTER_TRIGGER_PARTNER)
            Set(LVar0, ANIM_BillBlaster_Hurt)
            ExecWait(EVS_NpcHitRecoil)
        CaseEq(ENCOUNTER_TRIGGER_SPIN)
            Thread
                Call(EnemyHasNoSpinReaction, LVar0)
                IfEq(LVar0, 0)
                    Set(LVarA, 0)
                    Loop(30)
                        Add(LVarA, 40)
                        Call(SetNpcRotation, NPC_SELF, 0, LVarA, 0)
                        Wait(1)
                    EndLoop
                EndIf
            EndThread
        EndCaseGroup
    EndSwitch
    Return
    End
};

EvtScript N(EVS_NpcDefeat_BillBlaster_Beta) = {
    Call(GetBattleOutcome, LVar0)
    Switch(LVar0)
        CaseEq(OUTCOME_PLAYER_WON)
            Call(DoNpcDefeat)
        CaseEq(OUTCOME_PLAYER_FLED)
        CaseEq(OUTCOME_ENEMY_FLED)
            Call(SetEnemyFlagBits, NPC_SELF, ENEMY_FLAG_FLED, true)
            Call(RemoveNpc, NPC_SELF)
    EndSwitch
    Return
    End
};

NpcSettings N(NpcSettings_BillBlaster_Beta) = {
    .defaultAnim = ANIM_BillBlaster_Idle,
    .height = 26,
    .radius = 32,
    .level = ACTOR_LEVEL_BILL_BLASTER,
    .doAI = &N(EVS_NpcAI_BillBlaster_Beta),
    .onCreate = &N(EVS_NpcCreate_BillBlaster_Beta),
    .onHit = &N(EVS_NpcHit_BillBlaster_Beta),
    .onDefeat = &N(EVS_NpcDefeat_BillBlaster_Beta),
};
