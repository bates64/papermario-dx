#include "common.h"
#include "npc.h"
#include "effects.h"

// seems to be a macro in the original based on usage
#define EVT_SPIRIT_ADJUST_CAM(pitch) \
    Call(GetCamDistance, CAM_DEFAULT, LVar1) \
    Sub(LVar1, 100) \
    Call(SetCamDistance, CAM_DEFAULT, LVar1) \
    IfNe(pitch, 10000) \
        Call(GetCamPitch, CAM_DEFAULT, LVar2, LVar3) \
        Call(SetCamPitch, CAM_DEFAULT, LVar2, pitch) \
    EndIf

enum SpiritCardState {
    SPIRIT_CARD_STATE_ORB_RISE      = 0, // rising light
    SPIRIT_CARD_STATE_ORB_HOLD      = 1, // steady light
    SPIRIT_CARD_STATE_ORB_SHATTER   = 2, // burst and regather
    SPIRIT_CARD_STATE_SPAWNED       = 3, // card spins in place
    SPIRIT_CARD_STATE_IDLE          = 4, // descending card
};

enum SpiritCardSpinMode {
    SPIRIT_CARD_SPIN_OFF            = 0,
    SPIRIT_CARD_SPIN_ON             = 1,
    SPIRIT_CARD_SPIN_HOLD           = 2,
};

enum SpiritCardFloatMode {
    SPIRIT_CARD_FLOAT_INIT          = 0,
    SPIRIT_CARD_FLOAT_FALL          = 1,
    SPIRIT_CARD_FLOAT_HOVER         = 2,
};

enum SpiritCardNotifyValue {
    SPIRIT_CARD_NOTIFY_NONE             = 0,
    SPIRIT_CARD_NOTIFY_FALLING          = 1,
    SPIRIT_CARD_NOTIFY_DONE_FALLING     = 2,
    SPIRIT_CARD_NOTIFY_PLAYER_TOUCH     = 3,
};

typedef struct StarSpiritData {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ Vec3f lowPos;
    /* 0x18 */ Vec3f highPos;
    /* 0x24 */ f32 cardHoverY;
    /* 0x28 */ f32 shadowY;
    /* 0x2C */ f32 cardYaw;
    /* 0x30 */ f32 cardYawVel;
    /* 0x34 */ f32 cardStartYaw;
    /* 0x38 */ s32 chapter;
    /* 0x3C */ s32 riseTime;
    /* 0x40 */ s32 shadowID;
    /* 0x44 */ s16 state;
    /* 0x46 */ s16 stateTime;
    /* 0x48 */ s16 spinMode;
    /* 0x4A */ s16 cardFloatState;
    /* 0x4C */ s16 cardFloatTime;
    /* 0x4E */ s16 notifyValue; // user scripts can watch this to monitor animation progress, see: SpiritCardNotifyValues
    /* 0x50 */ EffectInstance* energyEffect;
    /* 0x54 */ EffectInstance* cardEffect;
} StarSpiritData; // size = 0x58

API_CALLABLE(N(AwaitSpiritOrbBurst)) {
    StarSpiritData* ptr = script->varTablePtr[0];

    sfx_adjust_env_sound_pos(SOUND_LRAW_STAR_ORB_RISING, SOUND_SPACE_DEFAULT, ptr->pos.x, ptr->pos.y, ptr->pos.z);

    if (ptr->state < SPIRIT_CARD_STATE_ORB_SHATTER) {
        return ApiStatus_BLOCK;
    } else {
        return ApiStatus_DONE2;
    }
}

API_CALLABLE(N(InitSpiritCardSpawn)) {
    StarSpiritData* ptr = heap_malloc(sizeof(*ptr));
    Bytecode* args = script->ptrReadPos;

    evt_set_variable(script, *args++, script->varTable[0]);
    ptr->chapter = evt_get_variable(script, *args++);
    ptr->riseTime = evt_get_variable(script, *args++);
    ptr->lowPos.x = evt_get_float_variable(script, *args++);
    ptr->lowPos.y = evt_get_float_variable(script, *args++);
    ptr->lowPos.z = evt_get_float_variable(script, *args++);
    ptr->highPos.x = evt_get_float_variable(script, *args++);
    ptr->highPos.y = evt_get_float_variable(script, *args++);
    ptr->highPos.z = evt_get_float_variable(script, *args++);
    ptr->cardHoverY = evt_get_float_variable(script, *args++);
    ptr->shadowY = evt_get_float_variable(script, *args++);

    ptr->energyEffect = fx_star_spirits_energy(2, ptr->lowPos.x, ptr->lowPos.y, ptr->lowPos.z, 1.0f, 0);
    ptr->state = SPIRIT_CARD_STATE_ORB_RISE;
    ptr->spinMode = SPIRIT_CARD_SPIN_OFF;
    ptr->cardFloatState = SPIRIT_CARD_FLOAT_INIT;
    ptr->notifyValue = SPIRIT_CARD_NOTIFY_NONE;
    ptr->stateTime = 0;

    script->varTablePtr[0] = ptr;

    return ApiStatus_DONE2;
}

API_CALLABLE(N(UpdateSpiritCardSpawn)) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    StarSpiritData* ptr = script->varTablePtr[0];

    switch (ptr->state) {
        case SPIRIT_CARD_STATE_ORB_RISE:
            ptr->pos.y = update_lerp(EASING_CUBIC_OUT, ptr->lowPos.y, ptr->highPos.y, ptr->stateTime, ptr->riseTime);
            ptr->pos.x = update_lerp(EASING_LINEAR, ptr->lowPos.x, ptr->highPos.x, ptr->stateTime, ptr->riseTime);
            ptr->pos.z = update_lerp(EASING_LINEAR, ptr->lowPos.z, ptr->highPos.z, ptr->stateTime, ptr->riseTime);
            ptr->energyEffect->data.starSpiritsEnergy->pos.x = ptr->pos.x;
            ptr->energyEffect->data.starSpiritsEnergy->pos.y = ptr->pos.y;
            ptr->energyEffect->data.starSpiritsEnergy->pos.z = ptr->pos.z;
            ptr->stateTime++;
            if (ptr->stateTime >= ptr->riseTime) {
                ptr->state = SPIRIT_CARD_STATE_ORB_HOLD;
                ptr->stateTime = 0;
            }
            break;
        case SPIRIT_CARD_STATE_ORB_HOLD:
            ptr->stateTime++;
            if (ptr->stateTime >= 60) {
                ptr->state = SPIRIT_CARD_STATE_ORB_SHATTER;
                ptr->stateTime = 0;
                ptr->energyEffect->data.starSpiritsEnergy->state = STAR_SPIRITS_ENERGY_STATE_EXPAND;
                ptr->energyEffect->data.starSpiritsEnergy->stateTime = 0;
            }
            break;
        case SPIRIT_CARD_STATE_ORB_SHATTER:
            ptr->stateTime++;
            if (ptr->stateTime >= 60) {
                ptr->cardEffect = fx_spirit_card(1, ptr->highPos.x, ptr->highPos.y, ptr->highPos.z, 1.0f, 0);
                ptr->cardEffect->data.spiritCard->chapter = ptr->chapter;
                ptr->cardEffect->data.spiritCard->unk_20 = 0;
                ptr->shadowID = create_shadow_type(SHADOW_VARYING_CIRCLE, ptr->highPos.x, ptr->shadowY, ptr->highPos.z);
                ptr->state = SPIRIT_CARD_STATE_SPAWNED;
                ptr->stateTime = 0;
                ptr->cardYaw = 0.0f;
                ptr->spinMode = SPIRIT_CARD_SPIN_ON;
                ptr->cardYawVel = 36.0f;
            }
            break;
        case SPIRIT_CARD_STATE_SPAWNED:
            ptr->cardYawVel = update_lerp(EASING_LINEAR, 36.0f, 19.0f, ptr->stateTime, 120);
            ptr->stateTime++;
            if (ptr->stateTime >= 120) {
                ptr->cardFloatTime = 0;
                ptr->cardFloatState = SPIRIT_CARD_FLOAT_FALL;
                ptr->spinMode = SPIRIT_CARD_SPIN_HOLD;
                ptr->notifyValue = SPIRIT_CARD_NOTIFY_FALLING;
                ptr->state = SPIRIT_CARD_STATE_IDLE;
                ptr->stateTime = 0;
                ptr->cardStartYaw = ptr->cardYaw;
            }
            break;
        case SPIRIT_CARD_STATE_IDLE:
            break;
    }

    switch (ptr->cardFloatState) {
        case SPIRIT_CARD_FLOAT_FALL:
            ptr->cardYaw = update_lerp(EASING_QUADRATIC_OUT, ptr->cardStartYaw, 1440.0f, ptr->cardFloatTime, 120);
            ptr->pos.y = update_lerp(EASING_COS_IN_OUT, ptr->highPos.y, ptr->cardHoverY, ptr->cardFloatTime, 120);
            ptr->cardFloatTime++;
            if (ptr->cardFloatTime >= 120) {
                ptr->cardFloatTime = 270; // time reused as angle in next state...
                ptr->cardFloatState = SPIRIT_CARD_FLOAT_HOVER;
                ptr->notifyValue = SPIRIT_CARD_NOTIFY_DONE_FALLING;
            }
            break;
        case SPIRIT_CARD_FLOAT_HOVER:
            ptr->pos.y = ptr->cardHoverY + (2.0f * (sin_deg(ptr->cardFloatTime) + 1.0f));
            ptr->cardFloatTime = clamp_angle(ptr->cardFloatTime + 8);
            if (!(dist3D(playerStatus->pos.x, playerStatus->pos.y + 20.0f, playerStatus->pos.z,
                         ptr->pos.x, ptr->pos.y, ptr->pos.z) > 30.0f)) {
                ptr->notifyValue = SPIRIT_CARD_NOTIFY_PLAYER_TOUCH;
            }
            break;
    }

    switch (ptr->spinMode) {
        case SPIRIT_CARD_SPIN_OFF:
            break;
        case SPIRIT_CARD_SPIN_ON:
            ptr->cardYaw = clamp_angle(ptr->cardYaw + ptr->cardYawVel);
        case SPIRIT_CARD_SPIN_HOLD:
            ptr->cardEffect->data.spiritCard->yaw = ptr->cardYaw;
            ptr->cardEffect->data.spiritCard->pos.x = ptr->highPos.x;
            ptr->cardEffect->data.spiritCard->pos.y = ptr->pos.y;
            ptr->cardEffect->data.spiritCard->pos.z = ptr->highPos.z;
            break;
    }

    return ApiStatus_BLOCK;
}

API_CALLABLE(N(AwaitSpiritCardProgress)) {
    Bytecode* args = script->ptrReadPos;
    s32 awaitValue = evt_get_variable(script, *args++);
    StarSpiritData* ptr = script->varTablePtr[0];

    if (ptr->notifyValue == awaitValue) {
        return ApiStatus_DONE2;
    } else {
        return ApiStatus_BLOCK;
    }
}

API_CALLABLE(N(SpawnExistingSpiritCard)) {
    Bytecode* args = script->ptrReadPos;

    if (isInitialCall) {
        StarSpiritData* ptr = heap_malloc(sizeof(*ptr));
        script->varTablePtr[0] = ptr;
        ptr->chapter = evt_get_variable(script, *args++);
        ptr->highPos.x = evt_get_float_variable(script, *args++);
        ptr->cardHoverY = evt_get_float_variable(script, *args++);
        ptr->highPos.z = evt_get_float_variable(script, *args++);
        ptr->shadowY = evt_get_float_variable(script, *args++);
        ptr->cardEffect = fx_spirit_card(1, ptr->highPos.x, ptr->cardHoverY, ptr->highPos.z, 1.0f, 0);
        ptr->cardEffect->data.spiritCard->chapter = ptr->chapter;
        ptr->cardEffect->data.spiritCard->unk_20 = 0;
        ptr->shadowID = create_shadow_type(SHADOW_VARYING_CIRCLE, ptr->highPos.x, ptr->shadowY, ptr->highPos.z);
        ptr->cardFloatTime = 270;
    }

    return ApiStatus_DONE2;
}

API_CALLABLE(N(UpdateExistingSpiritCard)) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    StarSpiritData* ptr = script->varTablePtr[0];

    ptr->pos.y = ptr->cardHoverY + (2.0f * (sin_deg(ptr->cardFloatTime) + 1.0f));
    ptr->cardFloatTime = clamp_angle(ptr->cardFloatTime + 8);
    if (dist2D(playerStatus->pos.x, playerStatus->pos.z, ptr->highPos.x, ptr->highPos.z) <= 30.0f) {
        ptr->notifyValue = SPIRIT_CARD_NOTIFY_PLAYER_TOUCH;
    }
    ptr->cardEffect->data.spiritCard->pos.x = ptr->highPos.x;
    ptr->cardEffect->data.spiritCard->pos.y = ptr->pos.y;
    ptr->cardEffect->data.spiritCard->pos.z = ptr->highPos.z;

    return ApiStatus_BLOCK;
}
