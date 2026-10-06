#include "common.h"
#include "goompa.h"
#include "world/partners.h"
#include "sprite/npc/Goompa.h"

void init(Npc* partner) {
    partner->collisionHeight = 24;
    partner->collisionDiameter = 20;
}

API_CALLABLE(TakeOut) {
    Npc* goompa = script->owner2.npc;

    if (isInitialCall) {
        partner_init_get_out(goompa);
    }

    if (partner_get_out(goompa)) {
        return ApiStatus_DONE1;
    } else {
        return ApiStatus_BLOCK;
    }
}

EvtScript EVS_WorldGoompa_TakeOut = {
    Call(TakeOut)
    Return
    End
};

BSS TweesterPhysics TweesterPhysicsData;
TweesterPhysics* TweesterPhysicsPtr = &TweesterPhysicsData;

API_CALLABLE(Update) {
    PlayerData* playerData = &gPlayerData;
    Npc* goompa = script->owner2.npc;
    f32 sinAngle, cosAngle, liftoffVelocity;
    Entity* entity;

    if (isInitialCall) {
        partner_walking_enable(goompa, true);
        mem_clear(TweesterPhysicsPtr, sizeof(TweesterPhysics));
        TweesterTouchingPartner = nullptr;
    }

    playerData->partnerUsedTime[PARTNER_GOOMPA]++;
    entity = TweesterTouchingPartner;

    if (entity == nullptr) {
        partner_walking_update_player_tracking(goompa);
        partner_walking_update_motion(goompa);
        return ApiStatus_BLOCK;
    }

    switch (TweesterPhysicsPtr->state) {
        case TWEESTER_PARTNER_INIT:
            TweesterPhysicsPtr->state = TWEESTER_PARTNER_ATTRACT;
            TweesterPhysicsPtr->prevFlags = goompa->flags;
            TweesterPhysicsPtr->radius = fabsf(dist2D(goompa->pos.x, goompa->pos.z,
                                                    entity->pos.x, entity->pos.z));
            TweesterPhysicsPtr->angle = atan2(entity->pos.x, entity->pos.z, goompa->pos.x, goompa->pos.z);
            TweesterPhysicsPtr->angularVel = 6.0f;
            TweesterPhysicsPtr->liftoffVelPhase = 50.0f;
            TweesterPhysicsPtr->countdown = 120;
            goompa->flags |= NPC_FLAG_FLYING | NPC_FLAG_IGNORE_WORLD_COLLISION | NPC_FLAG_IGNORE_CHAR_COLLISION | NPC_FLAG_IGNORE_CAMERA_FOR_YAW;
            goompa->flags &= ~NPC_FLAG_GRAVITY;
        case TWEESTER_PARTNER_ATTRACT:
            sin_cos_rad(DEG_TO_RAD(TweesterPhysicsPtr->angle), &sinAngle, &cosAngle);
            goompa->pos.x = entity->pos.x + (sinAngle * TweesterPhysicsPtr->radius);
            goompa->pos.z = entity->pos.z - (cosAngle * TweesterPhysicsPtr->radius);
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

            goompa->pos.y += liftoffVelocity;
            goompa->renderYaw = clamp_angle(360.0f - TweesterPhysicsPtr->angle);
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
            goompa->flags = TweesterPhysicsPtr->prevFlags;
            TweesterPhysicsPtr->countdown = 30;
            TweesterPhysicsPtr->state = TWEESTER_PARTNER_RELEASE;
            break;
        case TWEESTER_PARTNER_RELEASE:
            partner_walking_update_player_tracking(goompa);
            partner_walking_update_motion(goompa);

            TweesterPhysicsPtr->countdown--;
            if (TweesterPhysicsPtr->countdown == 0) {
                TweesterPhysicsPtr->state = TWEESTER_PARTNER_INIT;
                TweesterTouchingPartner = nullptr;
            }
            break;
    }
    return ApiStatus_BLOCK;
}

EvtScript EVS_WorldGoompa_Update = {
    Call(Update)
    Return
    End
};

void try_cancel_tweester(Npc* goompa) {
    if (TweesterTouchingPartner != nullptr) {
        TweesterTouchingPartner = nullptr;
        goompa->flags = TweesterPhysicsPtr->prevFlags;
        TweesterPhysicsPtr->state = TWEESTER_PARTNER_INIT;
        partner_clear_player_tracking(goompa);
    }
}

API_CALLABLE(UseAbility) {
    return ApiStatus_DONE2;
}

EvtScript EVS_WorldGoompa_UseAbility = {
    Call(UseAbility)
    Return
    End
};

API_CALLABLE(PutAway) {
    Npc* goompa = script->owner2.npc;

    if (isInitialCall) {
        partner_init_put_away(goompa);
    }

    if (partner_put_away(goompa)) {
        return ApiStatus_DONE1;
    } else {
        return ApiStatus_BLOCK;
    }
}

EvtScript EVS_WorldGoompa_PutAway = {
    Call(PutAway)
    Return
    End
};

WORLD_PARTNER_ENTRY = {
    .isFlying = false,
    .init = init,
    .takeOut = &EVS_WorldGoompa_TakeOut,
    .update = &EVS_WorldGoompa_Update,
    .useAbility = &EVS_WorldGoompa_UseAbility,
    .putAway = &EVS_WorldGoompa_PutAway,
    .idle = ANIM_Goompa_Idle,
};
