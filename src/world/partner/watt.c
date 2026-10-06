#include "common.h"
#include "effects.h"
#include "world/partners.h"
#include "npc.h"
#include "sprite/npc/WorldWatt.h"
#include "sprite.h"
#include "sprite/player.h"

void force_player_anim(AnimID);
void sync_held_position(void);
void update_player_carry_anim(void);

BSS b32 D_802BE300;
BSS s32 AbilityState;
BSS b32 D_802BE308;
BSS b32 IsPlayerHolding;
BSS EffectInstance* StaticEffect;

enum {
    // next two states lock input for a few frames, during which the ability can be canceled
    SHINING_STATE_INIT      = 40,
    SHINING_STATE_DELAY     = 41,
    SHINING_STATE_BEGIN     = 20,
    SHINING_STATE_GATHER    = 21,
    SHINING_STATE_HOLDING   = 1,
    SHINING_STATE_RELEASE   = 2,
};

void create_static_effect(Npc* npc) {
    if (!(npc->flags & NPC_FLAG_INVISIBLE)) {
        if (StaticEffect == nullptr) {
            StaticEffect = fx_static_status(0, npc->pos.x, npc->pos.y + 13.0f, npc->pos.z, 0.9f, 5, 0);
        }
    }
}

void dispose_static_effect(void) {
    if (StaticEffect != nullptr) {
        StaticEffect->data.staticStatus->timeLeft = 1;
        StaticEffect = nullptr;
    }
}

s32 EffectAnimLengths[] = { 24, 6 }; // second type is different from length in static_status.c (6 vs 12)

void reset_static_effect(s32 type) {
    EffectInstance* effect = StaticEffect;
    StaticStatusFXData* part = effect->data.staticStatus;
    f32 invisTime;
    s32 count;
    s32 i;

    part->type = type;
    invisTime = EffectAnimLengths[type] * 0.5f;
    count = effect->numParts - 1;

    part++;
    for (i = 1; i < count; i++, part++) {
        part->frame = -1.0f - (invisTime * (i & 1));
    }
}

void init(Npc* npc) {
    npc->collisionHeight = 24;
    npc->collisionDiameter = 24;
    D_802BE308 = false;
    D_802BE300 = false;
    IsPlayerHolding = false;
    AbilityState = SHINING_STATE_BEGIN;
    StaticEffect = nullptr;
}

API_CALLABLE(TakeOut) {
    Npc* watt = script->owner2.npc;

    if (isInitialCall) {
        partner_init_get_out(watt);
    }

    if (partner_get_out(watt)) {
        return ApiStatus_DONE1;
    } else {
        return ApiStatus_BLOCK;
    }
}

EvtScript EVS_WorldWatt_TakeOut = {
    Call(TakeOut)
    Return
    End
};

BSS TweesterPhysics TweesterPhysicsData;
TweesterPhysics* TweesterPhysicsPtr = &TweesterPhysicsData;

b32 WattIsMoving = false;

API_CALLABLE(Update) {
    PlayerData* playerData = &gPlayerData;
    Npc* watt = script->owner2.npc;
    f32 sinAngle, cosAngle, liftoffVelocity;
    Entity* entity;

    if (!gPartnerStatus.shouldResumeAbility) {
        if (isInitialCall) {
            partner_flying_enable(watt, true);
            mem_clear(TweesterPhysicsPtr, sizeof(TweesterPhysics));
            TweesterTouchingPartner = nullptr;
        }

        entity = TweesterTouchingPartner;
        playerData->partnerUsedTime[PARTNER_WATT]++;

        if (entity == nullptr) {
            create_static_effect(watt);
            partner_flying_update_player_tracking(watt);
            partner_flying_update_motion(watt);
            if (watt->moveSpeed != 0.0f) {
                if (!WattIsMoving) {
                    WattIsMoving = true;
                    reset_static_effect(1);
                    watt->curAnim = ANIM_WorldWatt_Run;
                }
            } else {
                if (WattIsMoving) {
                    WattIsMoving = false;
                    reset_static_effect(0);
                    watt->curAnim = ANIM_WorldWatt_Idle;
                }
            }
            if (StaticEffect != nullptr) {
                StaticEffect->data.staticStatus->pos.x = watt->pos.x;
                StaticEffect->data.staticStatus->pos.y = watt->pos.y + 13.0f;
                StaticEffect->data.staticStatus->pos.z = watt->pos.z;
            }
            return ApiStatus_BLOCK;
        }

        switch (TweesterPhysicsPtr->state) {
            case TWEESTER_PARTNER_INIT:
                TweesterPhysicsPtr->state = TWEESTER_PARTNER_ATTRACT;
                TweesterPhysicsPtr->prevFlags = watt->flags;
                TweesterPhysicsPtr->radius = fabsf(dist2D(watt->pos.x, watt->pos.z, entity->pos.x, entity->pos.z));
                TweesterPhysicsPtr->angle = atan2(entity->pos.x, entity->pos.z, watt->pos.x, watt->pos.z);
                TweesterPhysicsPtr->angularVel = 6.0f;
                TweesterPhysicsPtr->liftoffVelPhase = 50.0f;
                TweesterPhysicsPtr->countdown = 120;
                watt->flags |= NPC_FLAG_IGNORE_CAMERA_FOR_YAW | NPC_FLAG_IGNORE_CHAR_COLLISION | NPC_FLAG_IGNORE_WORLD_COLLISION | NPC_FLAG_FLYING;
                watt->flags &= ~NPC_FLAG_GRAVITY;
            case TWEESTER_PARTNER_ATTRACT:
                sin_cos_rad(DEG_TO_RAD(TweesterPhysicsPtr->angle), &sinAngle, &cosAngle);
                watt->pos.x = entity->pos.x + (sinAngle * TweesterPhysicsPtr->radius);
                watt->pos.z = entity->pos.z - (cosAngle * TweesterPhysicsPtr->radius);
                TweesterPhysicsPtr->angle = clamp_angle(TweesterPhysicsPtr->angle - TweesterPhysicsPtr->angularVel);

                if (TweesterPhysicsPtr->radius > 20.0f) {
                    TweesterPhysicsPtr->radius--;
                } else if (TweesterPhysicsPtr->radius < 19.0f) {
                    TweesterPhysicsPtr->radius++;
                }

                liftoffVelocity = sin_rad(DEG_TO_RAD(TweesterPhysicsPtr->liftoffVelPhase)) * 3.0f;
                TweesterPhysicsPtr->liftoffVelPhase += 3.0f;

                if (TweesterPhysicsPtr->liftoffVelPhase > 150.0f) {
                    TweesterPhysicsPtr->liftoffVelPhase = 150.0f;
                }

                watt->pos.y += liftoffVelocity;
                watt->renderYaw = clamp_angle(360.0f - TweesterPhysicsPtr->angle);
                TweesterPhysicsPtr->angularVel += 0.8;

                if (TweesterPhysicsPtr->angularVel > 40.0f) {
                    TweesterPhysicsPtr->angularVel = 40.0f;
                }

                TweesterPhysicsPtr->countdown--;
                if (TweesterPhysicsPtr->countdown == 0) {
                    TweesterPhysicsPtr->state = TWEESTER_PARTNER_HOLD;
                }
                break;
            case TWEESTER_PARTNER_HOLD:
                watt->flags = TweesterPhysicsPtr->prevFlags;
                TweesterPhysicsPtr->countdown = 30;
                TweesterPhysicsPtr->state = TWEESTER_PARTNER_RELEASE;
                break;
            case TWEESTER_PARTNER_RELEASE:
                partner_flying_update_player_tracking(watt);
                partner_flying_update_motion(watt);
                TweesterPhysicsPtr->countdown--;
                if (TweesterPhysicsPtr->countdown == 0) {
                    TweesterPhysicsPtr->state = TWEESTER_PARTNER_INIT;
                    TweesterTouchingPartner = nullptr;
                }
                break;
        }

        if (StaticEffect != nullptr) {
            StaticEffect->data.staticStatus->pos.x = watt->pos.x;
            StaticEffect->data.staticStatus->pos.y = watt->pos.y + 13.0f;
            StaticEffect->data.staticStatus->pos.z = watt->pos.z;
        }
    }
    return ApiStatus_BLOCK;
}

EvtScript EVS_WorldWatt_Update = {
    Call(Update)
    Return
    End
};

void try_cancel_tweester(Npc* watt) {
    if (TweesterTouchingPartner != nullptr) {
        TweesterTouchingPartner = nullptr;
        watt->flags = TweesterPhysicsPtr->prevFlags;
        TweesterPhysicsPtr->state = TWEESTER_PARTNER_INIT;
        partner_clear_player_tracking(watt);
    }
}

API_CALLABLE(UseAbility) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    PartnerStatus* partnerStatus = &gPartnerStatus;
    Npc* npc = script->owner2.npc;
    s32 actionState;

    if (isInitialCall) {
        try_cancel_tweester(npc);
        if ((playerStatus->animFlags & PA_FLAG_CHANGING_MAP)) {
            return ApiStatus_DONE2;
        }
        if (!partnerStatus->shouldResumeAbility) {
            if (partnerStatus->partnerActionState == ACTION_STATE_IDLE
                && (!partner_can_continue_ability(PARTNER_WATT) || is_starting_conversation()))
            {
                return ApiStatus_DONE2;
            }

            if (gGameStatusPtr->keepUsingPartnerOnMapChange) {
                if (playerStatus->animFlags & (PA_FLAG_USING_WATT | PA_FLAG_WATT_IN_HANDS)) {
                    AbilityState = SHINING_STATE_BEGIN;
                } else {
                    AbilityState = SHINING_STATE_INIT;
                }
            } else if (playerStatus->animFlags & PA_FLAG_USING_WATT) {
                AbilityState = SHINING_STATE_RELEASE;
            } else {
                AbilityState = SHINING_STATE_INIT;
            }
        } else {
            partnerStatus->shouldResumeAbility = false;
            playerStatus->animFlags |= (PA_FLAG_USING_WATT | PA_FLAG_WATT_IN_HANDS);
            update_player_carry_anim();
            npc->curAnim = ANIM_WorldWatt_Idle;
            AbilityState = SHINING_STATE_HOLDING;
            script->functionTemp[1] = 2;
        }
    }

    switch (AbilityState) {
        case SHINING_STATE_INIT:
            if (playerStatus->inputDisabledCount != 0) {
                return ApiStatus_DONE2;
            }
            script->functionTemp[1] = 3;
            AbilityState = SHINING_STATE_DELAY;
            script->functionTemp[2] = playerStatus->inputDisabledCount;
            break;
        case SHINING_STATE_DELAY:
            if (script->functionTemp[1] == 0) {
                if (script->functionTemp[2] < playerStatus->inputDisabledCount
                    || playerStatus->animFlags & PA_FLAG_CHANGING_MAP
                    || !partner_can_continue_ability(PARTNER_WATT)
                    || is_starting_conversation()
                ) {
                    return ApiStatus_DONE2;
                }
                AbilityState = SHINING_STATE_BEGIN;
                break;
            }
            script->functionTemp[1]--;
            break;
    }

    switch (AbilityState) {
        case SHINING_STATE_BEGIN:
            if (gGameStatusPtr->keepUsingPartnerOnMapChange) {
                playerStatus->animFlags |= PA_FLAG_USING_WATT;
                IsPlayerHolding = true;
                npc->flags |= NPC_FLAG_IGNORE_CHAR_COLLISION | NPC_FLAG_FLYING;
                npc->flags &= ~(NPC_FLAG_JUMPING | NPC_FLAG_GRAVITY);
                gGameStatusPtr->keepUsingPartnerOnMapChange = false;
                partnerStatus->partnerActionState = PARTNER_ACTION_USE;
                partnerStatus->actingPartner = PARTNER_WATT;
                npc->moveToPos.x = playerStatus->pos.x;
                npc->moveToPos.y = playerStatus->pos.y + 5.0f;
                npc->moveToPos.z = playerStatus->pos.z;
                npc->curAnim = ANIM_WorldWatt_Walk;
                add_vec2D_polar(&npc->moveToPos.x, &npc->moveToPos.z, 15.0f, playerStatus->targetYaw);
                npc->yaw = playerStatus->targetYaw;
                npc->curAnim = ANIM_WorldWatt_Idle;
                playerStatus->animFlags |= PA_FLAG_WATT_IN_HANDS;
                update_player_carry_anim();
                npc_set_palswap_mode_A(npc, NPC_PAL_ADJUST_WATT_IDLE);
                script->functionTemp[1] = 2;
                AbilityState = SHINING_STATE_HOLDING;
            } else {
                playerStatus->animFlags |= PA_FLAG_USING_WATT;
                IsPlayerHolding = true;
                npc->flags &= ~(NPC_FLAG_JUMPING | NPC_FLAG_GRAVITY);
                gGameStatusPtr->keepUsingPartnerOnMapChange = false;
                partnerStatus->partnerActionState = PARTNER_ACTION_USE;
                partnerStatus->actingPartner = PARTNER_WATT;
                partner_force_player_flip_done();
                npc->moveToPos.x = playerStatus->pos.x;
                npc->moveToPos.y = playerStatus->pos.y + 5.0f;
                npc->moveToPos.z = playerStatus->pos.z;
                npc->curAnim = ANIM_WorldWatt_Walk;
                add_vec2D_polar(&npc->moveToPos.x, &npc->moveToPos.z, 15.0f, playerStatus->targetYaw);
                npc->duration = 8;
                npc->yaw = atan2(npc->pos.x, npc->pos.z, playerStatus->pos.x, playerStatus->pos.z);
                AbilityState++; // SHINING_STATE_GATHER
            }
            break;
        case SHINING_STATE_GATHER:
            npc->pos.x += (npc->moveToPos.x - npc->pos.x) / npc->duration;
            npc->pos.y += (npc->moveToPos.y - npc->pos.y) / npc->duration;
            npc->pos.z += (npc->moveToPos.z - npc->pos.z) / npc->duration;
            npc->duration--;
            if (npc->duration == 0) {
                npc->yaw = playerStatus->targetYaw;
                npc->curAnim = ANIM_WorldWatt_Idle;
                partnerStatus->actingPartner = PARTNER_WATT;
                playerStatus->animFlags |= PA_FLAG_WATT_IN_HANDS;
                update_player_carry_anim();
                script->functionTemp[1] = 2;
                AbilityState = SHINING_STATE_HOLDING;
            }
            break;
        case SHINING_STATE_HOLDING:
            sync_held_position();
#if VERSION_JP
            // wait for begin holding cooldown
            if (script->functionTemp[1] != 0) {
                script->functionTemp[1]--;
                break;
            }
            if (playerStatus->actionState == ACTION_STATE_USE_SPINNING_FLOWER) {
                break;
            }
            // allow stop-holding input
            actionState = playerStatus->actionState;
            if ((actionState == ACTION_STATE_IDLE
                    || actionState == ACTION_STATE_WALK
                    || actionState == ACTION_STATE_RUN
                    || actionState == ACTION_STATE_LAND)
                && partnerStatus->pressedButtons & BUTTON_B
                || playerStatus->flags & PS_FLAG_HIT_FIRE
            ) {
        case SHINING_STATE_RELEASE:
                playerStatus->animFlags &= ~(PA_FLAG_WATT_IN_HANDS | PA_FLAG_USING_WATT);
                npc->curAnim = ANIM_WorldWatt_Idle;
                partner_clear_player_tracking(npc);
                IsPlayerHolding = false;
                partnerStatus->actingPartner = PARTNER_NONE;
                partnerStatus->partnerActionState = PARTNER_ACTION_NONE;
                gGameStatusPtr->keepUsingPartnerOnMapChange = false;
                AbilityState = SHINING_STATE_BEGIN;
                npc_set_palswap_mode_A(npc, NPC_PAL_ADJUST_NONE);
                if (!(playerStatus->flags & PS_FLAG_HIT_FIRE)) {
                    set_action_state(ACTION_STATE_IDLE);
                } else {
                    set_action_state(ACTION_STATE_HIT_LAVA);
                }
                return ApiStatus_DONE1;
            }
#else
            // immediately cancel state on touching fire
            if ((playerStatus->flags & PS_FLAG_HIT_FIRE)) {
                AbilityState = SHINING_STATE_RELEASE;
                break;
            }
            if (playerStatus->actionState == ACTION_STATE_USE_SPINNING_FLOWER) {
                break;
            }
            // wait for begin holding cooldown
            if (script->functionTemp[1] != 0) {
                script->functionTemp[1]--;
                break;
            }
            // allow stop-holding input
            actionState = playerStatus->actionState;
            if ((actionState == ACTION_STATE_IDLE
                    || actionState == ACTION_STATE_WALK
                    || actionState == ACTION_STATE_RUN
                    || actionState == ACTION_STATE_LAND)
                && partnerStatus->pressedButtons & BUTTON_B
            ) {
                AbilityState = SHINING_STATE_RELEASE;
            }
#endif
            break;
    }

#if !VERSION_JP
    if (AbilityState == SHINING_STATE_RELEASE) {
        playerStatus->animFlags &= ~(PA_FLAG_WATT_IN_HANDS | PA_FLAG_USING_WATT);
        npc->curAnim = ANIM_WorldWatt_Idle;
        partner_clear_player_tracking(npc);
        IsPlayerHolding = false;
        partnerStatus->actingPartner = PARTNER_NONE;
        partnerStatus->partnerActionState = PARTNER_ACTION_NONE;
        gGameStatusPtr->keepUsingPartnerOnMapChange = false;
        AbilityState = SHINING_STATE_BEGIN;
        npc_set_palswap_mode_A(npc, NPC_PAL_ADJUST_NONE);
        if (!(playerStatus->flags & PS_FLAG_HIT_FIRE)) {
            set_action_state(ACTION_STATE_IDLE);
        }
        return ApiStatus_DONE1;
    }
#endif

    if (StaticEffect != nullptr) {
        StaticEffect->data.staticStatus->pos.x = npc->pos.x;
        StaticEffect->data.staticStatus->pos.y = npc->pos.y + 13.0f;
        StaticEffect->data.staticStatus->pos.z = npc->pos.z;
    }
    return ApiStatus_BLOCK;
}

EvtScript EVS_WorldWatt_UseAbility = {
    Call(UseAbility)
    Return
    End
};

API_CALLABLE(PutAway) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    PartnerStatus* partnerStatus = &gPartnerStatus;
    Npc* watt = script->owner2.npc;

    if (isInitialCall) {
        dispose_static_effect();
        partner_init_put_away(watt);
        force_player_anim(ANIM_Mario1_Idle);
        partnerStatus->actingPartner = PARTNER_NONE;
        partnerStatus->partnerActionState = PARTNER_ACTION_NONE;
        playerStatus->animFlags &= ~(PA_FLAG_WATT_IN_HANDS | PA_FLAG_USING_WATT);
        gGameStatusPtr->keepUsingPartnerOnMapChange = false;
    }

    if (partner_put_away(watt)) {
        return ApiStatus_DONE1;
    } else {
        return ApiStatus_BLOCK;
    }
}

EvtScript EVS_WorldWatt_PutAway = {
    Call(PutAway)
    Return
    End
};

void pre_battle(Npc* watt) {
    PartnerStatus* partnerStatus = &gPartnerStatus;

    if (IsPlayerHolding) {
        partnerStatus->npc = *watt;
        partnerStatus->shouldResumeAbility = true;
        partner_clear_player_tracking(watt);
    }

    dispose_static_effect();
}

void post_battle(Npc* watt) {
    PartnerStatus* partnerStatus = &gPartnerStatus;

    if (partnerStatus->shouldResumeAbility) {
        *watt = partnerStatus->npc;
        partner_use_ability();
        create_static_effect(watt);
    }
}

API_CALLABLE(EnterMap) {
    PartnerStatus* partnerStatus = &gPartnerStatus;
    PlayerStatus* playerStatus = &gPlayerStatus;
    Npc* watt = get_npc_unsafe(NPC_PARTNER);

    if (isInitialCall) {
        script->functionTemp[0] = 0;
    }

    switch (script->functionTemp[0]) {
        case 0:
            if (script->varTable[12] == 0) {
                partner_kill_ability_script();
                dispose_static_effect();
            } else {
                create_static_effect(watt);
            }

            script->functionTemp[1] = script->varTable[4];
            playerStatus->targetYaw = atan2(playerStatus->pos.x, playerStatus->pos.z,
                    script->varTable[1], script->varTable[3]);
            playerStatus->heading = playerStatus->targetYaw;
            move_player(script->functionTemp[1], playerStatus->heading, script->varTableF[5]);
            sync_held_position();
            watt->flags &= ~NPC_FLAG_GRAVITY;
            watt->flags |= NPC_FLAG_IGNORE_CHAR_COLLISION;
            playerStatus->animFlags |= (PA_FLAG_WATT_IN_HANDS | PA_FLAG_USING_WATT);
            gGameStatusPtr->keepUsingPartnerOnMapChange = true;
            partnerStatus->partnerActionState = PARTNER_ACTION_WATT_SHINE;
            partnerStatus->actingPartner = PARTNER_WATT;
            D_802BE308 = false;
            script->functionTemp[0]++;
            break;
        case 1:
            sync_held_position();
            script->functionTemp[1]--;
            if (script->functionTemp[1] == 0) {
                if (script->varTable[12]) {
                    partner_use_ability();
                }
                return ApiStatus_DONE2;
            }
            break;
    }

    return ApiStatus_BLOCK;
}

void update_player_carry_anim(void) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    f32 currentSpeed = playerStatus->curSpeed;
    AnimID anim;

    if (playerStatus->runSpeed <= currentSpeed) {
        anim = ANIM_MarioW1_CarryRun;
    } else if (playerStatus->walkSpeed <= currentSpeed) {
        anim = ANIM_MarioW1_CarryWalk;
    } else {
        anim = ANIM_MarioW1_CarryIdle;
    }
    suggest_player_anim_allow_backward(anim);
}

void sync_held_position(void) {
    Npc* partnerNPC;
    Npc* newVar2;
    Camera* camera = gCameras;
    PlayerStatus* playerStatus;
    f32 offsetScale, angle;
    f32 spriteFacingAngle;
    s32 angleOffset;

    if (gPartnerStatus.partnerActionState != PARTNER_ACTION_NONE) {
        spriteFacingAngle = gPlayerStatusPtr->spriteFacingAngle;
        if ((spriteFacingAngle < 90.0f) || (spriteFacingAngle > 270.0f)) {
            if (!(gPlayerStatusPtr->trueAnimation & SPRITE_ID_BACK_FACING)) {
                angleOffset = -5;
                offsetScale = 0.6f;
            } else {
                angleOffset = 5;
                offsetScale = 0.6f;
            }
        } else {
            if (!(gPlayerStatusPtr->trueAnimation & SPRITE_ID_BACK_FACING)) {
                angleOffset = 5;
                offsetScale = 0.6f;
            } else {
                angleOffset = -5;
                offsetScale = 0.6f;
            }
        }

        angle = DEG_TO_RAD(camera->curYaw + 270.0f - gPlayerStatusPtr->spriteFacingAngle + angleOffset);

        playerStatus = gPlayerStatusPtr;
        partnerNPC = gPartnerNpc;
        partnerNPC->pos.x = playerStatus->pos.x + (sin_rad(angle) * gPlayerStatusPtr->colliderDiameter * offsetScale);

        newVar2 = gPartnerNpc;
        playerStatus = gPlayerStatusPtr;
        partnerNPC = newVar2;
        partnerNPC->pos.z = playerStatus->pos.z - (cos_rad(angle) * gPlayerStatusPtr->colliderDiameter * offsetScale);

        gPartnerNpc->yaw = gPlayerStatusPtr->targetYaw;
        gPartnerNpc->pos.y = gPlayerStatusPtr->pos.y + 5.0f;
    }
}

EvtScript EVS_WorldWatt_EnterMap = {
    Call(EnterMap)
    Return
    End
};

OVL_DEF_PARTNER() = {
    .isFlying = true,
    .init = init,
    .takeOut = &EVS_WorldWatt_TakeOut,
    .update = &EVS_WorldWatt_Update,
    .useAbility = &EVS_WorldWatt_UseAbility,
    .putAway = &EVS_WorldWatt_PutAway,
    .idle = ANIM_WorldWatt_Idle,
    .canPlayerOpenMenus = world_partner_can_open_menus_default,
    .preBattle = pre_battle,
    .postBattle = post_battle,
    .onEnterMap = &EVS_WorldWatt_EnterMap,
    .syncPlayerPosition = sync_held_position,
};
