#include "common.h"
#include "npc.h"

enum {
    FAKE_GOOMBARIO_JUMP_INIT         = 0,
    FAKE_GOOMBARIO_JUMP_TRAVEL       = 1,
    FAKE_GOOMBARIO_JUMP_BOUNCE_INIT  = 2,
    FAKE_GOOMBARIO_JUMP_BOUNCE       = 3,
};

enum {
    FAKE_GOOMBARIO_ARC_STANDARD      = 0,
    FAKE_GOOMBARIO_ARC_BOUNCE_ONLY   = 1,
    FAKE_GOOMBARIO_ARC_HIGHER        = 2,
    FAKE_GOOMBARIO_ARC_HEADBONK      = 3,
    FAKE_GOOMBARIO_ARC_HEADBONK_HIGH = 4,
};

API_CALLABLE(N(FakeGoombarioJumpOnTarget)) {
    Bytecode* args = script->ptrReadPos;
    Actor* actor = get_actor(script->owner1.actorID);
    ActorState* state = &actor->state;
    f32 oldActorX;
    f32 oldActorY;
    f32 remainingDist;
    f32 phaseScale;

    if (isInitialCall) {
        actor->state.moveTime = evt_get_variable(script, *args++);
        actor->state.moveArcAmplitude = evt_get_variable(script, *args++);
        script->functionTemp[1] = 0;
        script->functionTemp[0] = FAKE_GOOMBARIO_JUMP_INIT;
        if (actor->state.moveArcAmplitude == FAKE_GOOMBARIO_ARC_BOUNCE_ONLY) {
            script->functionTemp[0] = FAKE_GOOMBARIO_JUMP_BOUNCE_INIT;
        }
    }

    if (script->functionTemp[0] == FAKE_GOOMBARIO_JUMP_INIT) {
        state->curPos.x = actor->curPos.x;
        state->curPos.y = actor->curPos.y;
        state->curPos.z = actor->curPos.z;
        state->angle = atan2(state->curPos.x, state->curPos.z, state->goalPos.x, state->goalPos.z);
        state->dist = dist2D(state->curPos.x, state->curPos.z, state->goalPos.x, state->goalPos.z);

        if (state->moveTime == 0) {
            state->moveTime = state->dist / state->speed;
            remainingDist = state->dist - (state->moveTime * state->speed);
        } else {
            state->speed = state->dist / state->moveTime;
            remainingDist = state->dist - (state->moveTime * state->speed);
        }

        if (state->moveTime == 0) {
            return ApiStatus_DONE2;
        }

        state->velStep.x = (state->goalPos.x - state->curPos.x) / state->moveTime;
        state->velStep.y = (state->goalPos.y - state->curPos.y) / state->moveTime;
        state->velStep.z = (state->goalPos.z - state->curPos.z) / state->moveTime;
        state->acceleration = PI_S / state->moveTime;
        state->vel = 0.0f;
        state->speed += remainingDist / state->moveTime;

        state->unk_24 = 90.0f; // sine phase
        state->unk_28 = 360 / state->moveTime; // phase step
        state->bounceDivisor = ((state->dist - 20.0f) / 6.0f) + 47.0f;
        if (state->moveArcAmplitude == FAKE_GOOMBARIO_ARC_HIGHER) {
            state->bounceDivisor *= 1.12;
        }
        if (state->moveArcAmplitude == FAKE_GOOMBARIO_ARC_HEADBONK_HIGH) {
            state->bounceDivisor *= 1.25;
        }
        state->unk_18.x = 0.0f; // previous Y before sine arc
        state->unk_18.y = 0.0f; // current Y after sine arc
        phaseScale = (state->moveArcAmplitude < FAKE_GOOMBARIO_ARC_HEADBONK) ? 0.53f : 0.8f;
        state->vel += (sin_rad(DEG_TO_RAD(state->unk_24)) * phaseScale * state->acceleration) + state->acceleration;

        set_actor_anim(ACTOR_SELF, 1, state->animJumpRise);
        sfx_play_sound(SOUND_QUICK_PLAYER_JUMP);
        script->functionTemp[0] = FAKE_GOOMBARIO_JUMP_TRAVEL;
    }

    switch (script->functionTemp[0]) {
        case FAKE_GOOMBARIO_JUMP_TRAVEL:
            if (state->vel > PI_S / 2) {
                set_actor_anim(ACTOR_SELF, 1, state->animJumpFall);
            }
            oldActorX = actor->curPos.x;
            oldActorY = actor->curPos.y;
            state->curPos.x += state->velStep.x;
            state->curPos.y = state->curPos.y + state->velStep.y;
            state->curPos.z = state->curPos.z + state->velStep.z;
            state->unk_18.x = actor->curPos.y;
            actor->curPos.x = state->curPos.x;
            actor->curPos.y = state->curPos.y + (state->bounceDivisor * sin_rad(state->vel));
            actor->curPos.z = state->curPos.z;
            if (state->goalPos.y > actor->curPos.y && state->moveTime < 3) {
                actor->curPos.y = state->goalPos.y;
            }

            actor->rot.z = -atan2(oldActorX, -oldActorY, actor->curPos.x, -actor->curPos.y);
            state->unk_18.y = actor->curPos.y;
            phaseScale = (state->moveArcAmplitude < FAKE_GOOMBARIO_ARC_HEADBONK) ? 0.53f : 0.8f;
            state->vel += (sin_rad(DEG_TO_RAD(state->unk_24)) * phaseScale * state->acceleration) + state->acceleration;

            state->unk_24 += state->unk_28;
            state->unk_24 = clamp_angle(state->unk_24);
            state->moveTime--;
            if (state->moveTime == 0) {
                actor->curPos.y = state->goalPos.y;
                state->acceleration = 1.8f;
                state->vel = -(state->unk_18.x - state->unk_18.y);
                set_actor_anim(ACTOR_SELF, 1, state->animJumpLand);
                return ApiStatus_DONE1;
            }
            break;
        case FAKE_GOOMBARIO_JUMP_BOUNCE_INIT:
            state->moveTime = 1;
            state->acceleration = 1.8f;
            state->unk_24 = 90.0f;
            state->vel = -(state->unk_18.x - state->unk_18.y);
            state->bounceDivisor = fabsf(state->unk_18.x - state->unk_18.y) / 16.5;
            state->unk_28 = 360 / state->moveTime;
            state->curPos.x = actor->curPos.x;
            state->curPos.y = actor->curPos.y;
            state->curPos.z = actor->curPos.z;
            script->functionTemp[0] = FAKE_GOOMBARIO_JUMP_BOUNCE;
            // fallthrough
        case FAKE_GOOMBARIO_JUMP_BOUNCE:
            state->curPos.x += state->bounceDivisor * sin_rad(DEG_TO_RAD(state->unk_24)) / 33.0;
            state->curPos.y -= state->bounceDivisor * sin_rad(DEG_TO_RAD(state->unk_24));
            state->unk_24 += state->unk_28;
            state->unk_24 = clamp_angle(state->unk_24);
            actor->curPos.x = state->curPos.x;
            actor->curPos.y = state->curPos.y;
            actor->curPos.z = state->curPos.z;

            state->moveTime--;
            if (state->moveTime == 0) {
                return ApiStatus_DONE1;
            }
            break;
    }

    return ApiStatus_BLOCK;
}
