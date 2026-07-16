#include "common.h"
#include "effects.h"

void show_start_recovery_shimmer(f32 x, f32 y, f32 z, s32 amt) {
    fx_stars_shimmer(1, x, y, z, amt + 30, amt + 30, (amt / 2) + 10, 30);
}

void show_recovery_shimmer(f32 x, f32 y, f32 z, s32 amt) {
    fx_stars_shimmer(2, x, y, z, amt + 30, amt + 30, (amt / 2) + 10, 30);
}

API_CALLABLE(ShowStartRecoveryShimmer) {
    Bytecode* args = script->ptrReadPos;
    f32 x = evt_get_float_variable(script, *args++);
    f32 y = evt_get_float_variable(script, *args++);
    f32 z = evt_get_float_variable(script, *args++);

    show_start_recovery_shimmer(x, y, z, evt_get_variable(script, *args++));
    sfx_play_sound_at_position(SOUND_START_RECOVERY, SOUND_SPACE_DEFAULT, x, y, z);
    return ApiStatus_DONE2;
}

API_CALLABLE(ShowRecoveryShimmer) {
    Bytecode* args = script->ptrReadPos;
    f32 x = evt_get_float_variable(script, *args++);
    f32 y = evt_get_float_variable(script, *args++);
    f32 z = evt_get_float_variable(script, *args++);

    show_recovery_shimmer(x, y, z, evt_get_variable(script, *args++));
    sfx_play_sound_at_position(SOUND_RECOVERY_SHMMER, SOUND_SPACE_DEFAULT, x, y, z);
    return ApiStatus_DONE2;
}

API_CALLABLE(func_802D7690) {
    Bytecode* args = script->ptrReadPos;
    f32 posX = evt_get_float_variable(script, *args++);
    f32 posY = evt_get_float_variable(script, *args++);
    f32 posZ = evt_get_float_variable(script, *args++);
    f32 angle = evt_get_float_variable(script, *args++);
    f32 magnitude = evt_get_float_variable(script, *args++);
    s32 duration = evt_get_variable(script, *args++);
    f32 offsetX, offsetY, offsetZ;
    f32 sinA, cosA;

    if (isInitialCall) {
        script->functionTemp[0] = 0;
    }

    offsetX = rand_int(10) - 5;
    offsetZ = rand_int(10) - 5;
    offsetY = -2.0f - ((SQ(offsetX) + SQ(offsetZ)) / 5.0f);
    sinA = sin_rad(DEG_TO_RAD(angle));
    cosA = cos_rad(DEG_TO_RAD(angle));
    fx_cloud_trail(
        posX + ((sinA * magnitude * script->functionTemp[0]) / duration) + offsetX,
        posY + 15.5f + offsetY,
        posZ + ((-cosA * magnitude * script->functionTemp[0]) / duration) + offsetZ,
        0.0f
    );

    script->functionTemp[0]++;
    if (script->functionTemp[0] < duration) {
        return ApiStatus_BLOCK;
    } else {
        return ApiStatus_DONE2;
    }
}

API_CALLABLE(ShowEmote) {
    Bytecode* args = script->ptrReadPos;
    s32 npcID = evt_get_variable(script, *args++);
    s32 emoteType = evt_get_variable(script, *args++);
    f32 pitch = evt_get_float_variable(script, *args++);
    s32 duration = evt_get_variable(script, *args++);
    s32 emoterType = evt_get_variable(script, *args++);
    f32 dX = evt_get_float_variable(script, *args++);
    f32 dY = evt_get_float_variable(script, *args++);
    f32 dZ = evt_get_float_variable(script, *args++);
    f32 radius = evt_get_float_variable(script, *args++);

    Npc* npc;
    EffectInstance* emoteHandle;
    f32 x, y, z, r;

    switch (emoterType) {
        case EMOTER_PLAYER:
            // show emote from player
            npc = (Npc*)-1;
            x = 0.0f;
            y = (gPlayerStatus.colliderHeight * 2) / 3;
            z = 0.0f;
            r = gPlayerStatus.colliderHeight / 3;
            break;
        case EMOTER_NPC:
            // show emote from NPC
            npc = resolve_npc(script, npcID);
            if (npc == nullptr) {
                return ApiStatus_DONE2;
            }
            x = 0.0f;
            y = (npc->collisionHeight * 4) / 5;
            z = 0.0f;
            r = npc->collisionHeight / 3;
            break;
        default:
            // show emote at arbitrary position
            x = dX;
            y = dY;
            z = dZ;
            r = radius;
            npc = nullptr;
            break;
    }

    fx_emote(emoteType, npc, x, y, z, r, pitch, duration, &emoteHandle);
    return ApiStatus_DONE2;
}

API_CALLABLE(RemoveEffect) {
    Bytecode* args = script->ptrReadPos;

    remove_effect((EffectInstance*)evt_get_variable(script, *args++));
    return ApiStatus_DONE2;
}

API_CALLABLE(DismissEffect) {
    Bytecode* args = script->ptrReadPos;
    EffectInstance* effect = (EffectInstance*)evt_get_variable(script, *args++);

    effect->flags |= FX_INSTANCE_FLAG_DISMISS;
    return ApiStatus_DONE2;
}

API_CALLABLE(DismissItemOutline) {
    Bytecode* args = script->ptrReadPos;
    EffectInstance* effect = (EffectInstance*)evt_get_variable(script, *args++);

    effect->data.gotItemOutline->timeLeft = 10;
    return ApiStatus_DONE2;
}

API_CALLABLE(SpawnSunEffect) {
    Bytecode* args = script->ptrReadPos;
    s32 direction = evt_get_variable(script, *args++);

    fx_sun(direction, 0.0f, 0.0f, 0.0f, 0.0f, 0);
    return ApiStatus_DONE2;
}

API_CALLABLE(InterpMotionBlurParams) {
    s32 centerX0 = script->varTable[1];
    s32 centerY0 = script->varTable[2];
    s32 centerX1 = script->varTable[3];
    s32 centerY1 = script->varTable[4];
    s32 finalAmt = script->varTable[5];
    s32 duration = script->varTable[6];
    s32 delta;
    u8 overlayType;
    f32 initialAmt;

    if (isInitialCall) {
        script->functionTemp[0] = duration;
        get_screen_overlay_params(SCREEN_LAYER_BACK, &overlayType, &initialAmt);
        script->functionTemp[1] = initialAmt;
        set_screen_overlay_center(SCREEN_LAYER_BACK, 0, centerX0, centerY0);
        set_screen_overlay_center(SCREEN_LAYER_BACK, 1, centerX1, centerY1);
    }

    get_screen_overlay_params(SCREEN_LAYER_BACK, &overlayType, &initialAmt);
    // lerp from initialAmt (stored in functionTemp[1]) to finalAmt (stored in varTable[5])
    delta = (script->functionTemp[1] - finalAmt);
    set_screen_overlay_params_back(OVERLAY_BLUR, (delta * script->functionTemp[0] / duration) + finalAmt);

    script->functionTemp[0]--;
    if (script->functionTemp[0] < 0) {
        set_screen_overlay_params_back(OVERLAY_BLUR, finalAmt);
        return ApiStatus_DONE2;
    }
    return ApiStatus_BLOCK;
}

EvtScript EVS_UpdateMotionBlurParams = {
    Call(InterpMotionBlurParams)
    Return
    End
};

API_CALLABLE(SetMotionBlurParams) {
    Bytecode* args = script->ptrReadPos;
    s32 var0 = evt_get_variable(script, *args++);
    s32 centerX0 = evt_get_variable(script, *args++);
    s32 centerY0 = evt_get_variable(script, *args++);
    s32 centerX1 = evt_get_variable(script, *args++);
    s32 centerY1 = evt_get_variable(script, *args++);
    s32 finalAmt = evt_get_variable(script, *args++);
    s32 duration = evt_get_variable(script, *args++);

    Evt* blurEvt = start_script(&EVS_UpdateMotionBlurParams, EVT_PRIORITY_1, 0);
    blurEvt->varTable[0] = var0;
    blurEvt->varTable[1] = centerX0;
    blurEvt->varTable[2] = centerY0;
    blurEvt->varTable[3] = centerX1;
    blurEvt->varTable[4] = centerY1;
    blurEvt->varTable[5] = finalAmt;
    blurEvt->varTable[6] = duration;

    return ApiStatus_DONE2;
}

API_CALLABLE(ShowSweat) {
    Bytecode* args = script->ptrReadPos;
    s32 npcID = evt_get_variable(script, *args++);
    s32 type = evt_get_variable(script, *args++);
    f32 pitch = evt_get_float_variable(script, *args++);
    s32 emoterType = evt_get_variable(script, *args++);
    f32 posX = evt_get_float_variable(script, *args++);
    f32 posY = evt_get_float_variable(script, *args++);
    f32 posZ = evt_get_float_variable(script, *args++);
    f32 radius = evt_get_float_variable(script, *args++);
    s32 duration = evt_get_variable(script, *args++);

    Npc* npc;
    f32 x, y, z, r;

    switch (emoterType) {
        case EMOTER_PLAYER:
            x = gPlayerStatus.pos.x;
            y = gPlayerStatus.pos.y + (gPlayerStatus.colliderHeight * 2) / 3;
            z = gPlayerStatus.pos.z;
            r = gPlayerStatus.colliderHeight / 3;
            break;
        case EMOTER_NPC:
            npc = resolve_npc(script, npcID);
            if (npc == nullptr) {
                return ApiStatus_DONE2;
            }
            x = npc->pos.x;
            y = npc->pos.y + (npc->collisionHeight * 2) / 3;
            z = npc->pos.z;
            r = npc->collisionHeight / 3;
            break;
        default:
            x = posX;
            y = posY;
            z = posZ;
            r = radius;
            break;
    }

    fx_sweat(type, x, y, z, r, pitch, duration);
    return ApiStatus_DONE2;
}

API_CALLABLE(ShowSleepBubble) {
    Bytecode* args = script->ptrReadPos;
    s32 npcID = evt_get_variable(script, *args++);
    s32 type = evt_get_variable(script, *args++);
    f32 pitch = evt_get_float_variable(script, *args++);
    s32 emoterType = evt_get_variable(script, *args++);
    f32 posX = evt_get_float_variable(script, *args++);
    f32 posY = evt_get_float_variable(script, *args++);
    f32 posZ = evt_get_float_variable(script, *args++);
    f32 radius = evt_get_float_variable(script, *args++);
    s32 outVar = *args++;

    Npc* npc;
    f32 x, y, z, r;
    EffectInstance* effectHandle;

    switch (emoterType) {
        case EMOTER_PLAYER:
            x = gPlayerStatus.pos.x;
            y = gPlayerStatus.pos.y + (gPlayerStatus.colliderHeight * 2) / 3;
            z = gPlayerStatus.pos.z;
            r = gPlayerStatus.colliderHeight / 3;
            break;
        case EMOTER_NPC:
            npc = resolve_npc(script, npcID);
            if (npc == nullptr) {
                return ApiStatus_DONE2;
            }
            x = npc->pos.x;
            y = npc->pos.y + (npc->collisionHeight * 2) / 3;
            z = npc->pos.z;
            r = npc->collisionHeight / 3;
            break;
        default:
            x = posX;
            y = posY;
            z = posZ;
            r = radius;
            break;
    }

    fx_sleep_bubble(type, x, y, z, r, pitch, &effectHandle);
    evt_set_variable(script, outVar, (s32)effectHandle);
    return ApiStatus_DONE2;
}

API_CALLABLE(SetSleepBubbleTimeLeft) {
    Bytecode* args = script->ptrReadPos;
    EffectInstance* effect = (EffectInstance*)evt_get_variable(script, *args++);
    s32 value = evt_get_variable(script, *args++);

    effect->data.sleepBubble->timeLeft = value;
    return ApiStatus_DONE2;
}

API_CALLABLE(PlayEffect_impl) {
    Bytecode* args = script->ptrReadPos;
    Bytecode rawVars[EFFECT_MAX_ARGS + 1];
    s32 iVars[EFFECT_MAX_ARGS + 1];
    f32 fVars[EFFECT_MAX_ARGS + 1];
    EffectInstance* effectRet = nullptr;
    EffectInstance* effectOut;
    s32 effectIndex;
    s32 expectedArgCount;

    ASSERT_MSG(script->curArgc >= 1, "PlayEffect missing effect ID");
    effectIndex = evt_get_variable(script, args[0]);
    ASSERT_MSG((u32) effectIndex < EFFECT_COUNT, "Invalid effect ID %lX", effectIndex);
    expectedArgCount = gEffectArgCounts[effectIndex];
    ASSERT_MSG(
        script->curArgc == expectedArgCount + 1,
        "PlayEffect %lX argc %d != %ld",
        effectIndex,
        script->curArgc - 1,
        expectedArgCount
    );

    for (s32 i = 0; i < script->curArgc; i++) {
        rawVars[i] = args[i];
        iVars[i] = evt_get_variable(script, rawVars[i]);
        fVars[i] = evt_get_float_variable(script, rawVars[i]);
    }

    switch (iVars[0]) {
        case EFFECT_BIG_SMOKE_PUFF:
            fx_big_smoke_puff(fVars[1], fVars[2], fVars[3]);
            break;
        case EFFECT_LANDING_DUST:
            fx_landing_dust(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5]);
            break;
        case EFFECT_WALKING_DUST:
            fx_walking_dust(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], fVars[6]);
            break;
        case EFFECT_FLOWER_SPLASH:
            fx_flower_splash(fVars[1], fVars[2], fVars[3], fVars[4]);
            break;
        case EFFECT_FLOWER_TRAIL:
            fx_flower_trail(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], fVars[6]);
            break;
        case EFFECT_CLOUD_PUFF:
            fx_cloud_puff(fVars[1], fVars[2], fVars[3], fVars[4]);
            break;
        case EFFECT_CLOUD_TRAIL:
            fx_cloud_trail(iVars[1], fVars[2], fVars[3], fVars[4]);
            break;
        case EFFECT_FOOTPRINT:
            fx_footprint(fVars[1], fVars[2], fVars[3], fVars[4], fVars[5]);
            break;
        case EFFECT_FLOATING_FLOWER:
            fx_floating_flower(iVars[1], fVars[2], fVars[3], fVars[4], iVars[5]);
            break;
        case EFFECT_SNOWFLAKE:
            fx_snowflake(fVars[1], fVars[2], fVars[3], iVars[4]);
            break;
        case EFFECT_STAR:
            fx_star(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], fVars[6], fVars[7], fVars[8]);
            break;
        case EFFECT_EMOTE:
            fx_emote(iVars[1], (Npc*) rawVars[2], fVars[3], fVars[4], fVars[5], fVars[6], fVars[7], iVars[8], &effectOut);
            evt_set_variable(script, rawVars[9], (s32) effectOut);
            break;
        case EFFECT_SPARKLES:
            fx_sparkles(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5]);
            break;
        case EFFECT_SHAPE_SPELL:
            fx_shape_spell(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], fVars[6], fVars[7], iVars[8]);
            break;
        case EFFECT_GATHER_ENERGY_PINK:
            fx_gather_energy_pink(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_DROP_LEAVES:
            fx_drop_leaves(iVars[1], fVars[2], fVars[3], fVars[4], iVars[5]);
            break;
        case EFFECT_DUST:
            fx_dust(iVars[1], fVars[2], fVars[3], fVars[4], iVars[5]);
            break;
        case EFFECT_SHATTERING_STONES:
            fx_shattering_stones(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5]);
            break;
        case EFFECT_SMOKE_RING:
            fx_smoke_ring(iVars[1], fVars[2], fVars[3], fVars[4]);
            break;
        case EFFECT_DAMAGE_STARS:
            fx_damage_stars(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], fVars[6], fVars[7], iVars[8]);
            break;
        case EFFECT_EXPLOSION:
            fx_explosion(iVars[1], fVars[2], fVars[3], fVars[4]);
            break;
        case EFFECT_LENS_FLARE:
            fx_lens_flare(iVars[1], fVars[2], fVars[3], fVars[4], iVars[5]);
            break;
        case EFFECT_GOT_ITEM_OUTLINE:
            fx_got_item_outline(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], &effectOut);
            evt_set_variable(script, rawVars[6], (s32) effectOut);
            break;
        case EFFECT_SPIKY_WHITE_AURA:
            fx_spiky_white_aura(iVars[1], fVars[2], fVars[3], fVars[4], iVars[5]);
            break;
        case EFFECT_SMOKE_IMPACT:
            fx_smoke_impact(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6], fVars[7], iVars[8]);
            break;
        case EFFECT_DAMAGE_INDICATOR:
            fx_damage_indicator(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], fVars[6], iVars[7], &effectOut);
            evt_set_variable(script, rawVars[8], (s32) effectOut);
            break;
        case EFFECT_PURPLE_RING:
            fx_purple_ring(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], fVars[6], fVars[7], fVars[8]);
            break;
        case EFFECT_STARS_BURST:
            fx_stars_burst(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], fVars[6], iVars[7]);
            break;
        case EFFECT_STARS_SHIMMER:
            fx_stars_shimmer(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], fVars[6], iVars[7], iVars[8]);
            break;
        case EFFECT_RISING_BUBBLE:
            fx_rising_bubble(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5]);
            break;
        case EFFECT_RING_BLAST:
            fx_ring_blast(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_SHOCKWAVE:
            fx_shockwave(iVars[1], fVars[2], fVars[3], fVars[4]);
            break;
        case EFFECT_MUSIC_NOTE:
            fx_music_note(iVars[1], fVars[2], fVars[3], fVars[4]);
            break;
        case EFFECT_SMOKE_BURST:
            fx_smoke_burst(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_SWEAT:
            fx_sweat(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], fVars[6], iVars[7]);
            break;
        case EFFECT_SLEEP_BUBBLE:
            fx_sleep_bubble(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], fVars[6], &effectOut);
            evt_set_variable(script, rawVars[7], (s32) effectOut);
            break;
        case EFFECT_WINDY_LEAVES:
            fx_windy_leaves(iVars[1], fVars[2], fVars[3], fVars[4]);
            break;
        case EFFECT_FLAME:
            fx_flame(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], &effectOut);
            evt_set_variable(script, rawVars[6], (s32) effectOut);
            break;
        case EFFECT_FALLING_LEAVES:
            fx_falling_leaves(iVars[1], fVars[2], fVars[3], fVars[4]);
            break;
        case EFFECT_STARS_SPREAD:
            fx_stars_spread(iVars[1], fVars[2], fVars[3], fVars[4], iVars[5], iVars[6]);
            break;
        case EFFECT_STEAM_BURST:
            fx_steam_burst(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_STARS_ORBITING:
            fx_stars_orbiting(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6], &effectOut);
            evt_set_variable(script, rawVars[7], (s32) effectOut);
            break;
        case EFFECT_BIG_SNOWFLAKES:
            fx_big_snowflakes(iVars[1], fVars[2], fVars[3], fVars[4]);
            break;
        case EFFECT_DEBUFF:
            fx_debuff(iVars[1], fVars[2], fVars[3], fVars[4]);
            break;
        case EFFECT_GREEN_IMPACT:
            fx_green_impact(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5]);
            break;
        case EFFECT_RADIAL_SHIMMER:
            fx_radial_shimmer(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_ENDING_DECALS:
            fx_ending_decals(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], &effectOut);
            evt_set_variable(script, rawVars[6], (s32) effectOut);
            break;
        case EFFECT_LIGHT_RAYS:
            fx_light_rays(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], &effectOut);
            evt_set_variable(script, rawVars[6], (s32) effectOut);
            break;
        case EFFECT_LIGHTNING:
            effectRet = fx_lightning(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], fVars[6]);
            break;
        case EFFECT_FIRE_BREATH:
            effectRet = fx_fire_breath(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], fVars[6], fVars[7], iVars[8], iVars[9], iVars[10]);
            break;
        case EFFECT_SHIMMER_BURST:
            fx_shimmer_burst(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_ENERGY_SHOCKWAVE:
            fx_energy_shockwave(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_SHIMMER_WAVE:
            fx_shimmer_wave(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], fVars[6], iVars[7], iVars[8]);
            break;
        case EFFECT_AURA:
            fx_aura(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], &effectOut);
            evt_set_variable(script, rawVars[6], (s32) effectOut);
            break;
        case EFFECT_BULB_GLOW:
            fx_bulb_glow(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], &effectOut);
            evt_set_variable(script, rawVars[6], (s32) effectOut);
            break;
        case EFFECT_3D:
            fx_effect_3D(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], fVars[6], fVars[7], iVars[8], &effectOut);
            evt_set_variable(script, rawVars[9], (s32) effectOut);
            break;
        case EFFECT_BLAST:
            fx_blast(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_FIRE_FLOWER:
            effectRet = fx_fire_flower(iVars[1], fVars[2], fVars[3], fVars[4], iVars[5]);
            break;
        case EFFECT_RECOVER:
            effectRet = fx_recover(iVars[1], fVars[2], fVars[3], fVars[4], iVars[5]);
            break;
        case EFFECT_DISABLE_X:
            effectRet = fx_disable_x(iVars[1], fVars[2], fVars[3], fVars[4], iVars[5]);
            break;
        case EFFECT_BOMBETTE_BREAKING:
            effectRet = fx_bombette_breaking(iVars[1], iVars[2], iVars[3], fVars[4], iVars[5], iVars[6]);
            break;
        case EFFECT_FIREWORK:
            effectRet = fx_firework(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_CONFETTI:
            effectRet = fx_confetti(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_SNOWFALL:
            effectRet = fx_snowfall(iVars[1], iVars[2]);
            break;
        case EFFECT_46:
            effectRet = fx_effect_46(iVars[1], (PlayerStatus*) rawVars[2], fVars[3], iVars[4]);
            break;
        case EFFECT_GATHER_MAGIC:
            effectRet = fx_gather_magic(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_ATTACK_RESULT_TEXT:
            effectRet = fx_attack_result_text(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_SMALL_GOLD_SPARKLE:
            effectRet = fx_small_gold_sparkle(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_FLASHING_BOX_SHOCKWAVE:
            effectRet = fx_flashing_box_shockwave(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], fVars[6]);
            break;
        case EFFECT_BALLOON:
            effectRet = fx_balloon(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_FLOATING_ROCK:
            effectRet = fx_floating_rock(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], fVars[6], fVars[7], fVars[8], iVars[9]);
            break;
        case EFFECT_CHOMP_DROP:
            effectRet = fx_chomp_drop(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], fVars[6], fVars[7], fVars[8], fVars[9], iVars[10]);
            break;
        case EFFECT_QUIZMO_STAGE:
            effectRet = fx_quizmo_stage(iVars[1], fVars[2], fVars[3], fVars[4]);
            break;
        case EFFECT_RADIATING_ENERGY_ORB:
            effectRet = fx_radiating_energy_orb(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_ENERGY_ORB_WAVE:
            effectRet = fx_energy_orb_wave(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_MERLIN_HOUSE_STARS:
            effectRet = fx_merlin_house_stars(iVars[1], fVars[2], fVars[3], fVars[4]);
            break;
        case EFFECT_MOTION_BLUR_FLAME:
            effectRet = fx_motion_blur_flame(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_STAT_CHANGE:
            effectRet = fx_stat_change(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_SNAKING_STATIC:
            effectRet = fx_snaking_static(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_THUNDERBOLT_RING:
            effectRet = fx_thunderbolt_ring(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_SQUIRT:
            effectRet = fx_squirt(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], fVars[6], fVars[7], fVars[8], iVars[9]);
            break;
        case EFFECT_WATER_BLOCK:
            effectRet = fx_water_block(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_WATERFALL:
            effectRet = fx_waterfall(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_WATER_FOUNTAIN:
            effectRet = fx_water_fountain(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_UNDERWATER:
            effectRet = fx_underwater(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_LIGHTNING_BOLT:
            effectRet = fx_lightning_bolt(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], fVars[6], fVars[7], fVars[8], iVars[9]);
            break;
        case EFFECT_WATER_SPLASH:
            effectRet = fx_water_splash(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_SNOWMAN_DOLL:
            effectRet = fx_snowman_doll(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_FRIGHT_JAR:
            effectRet = fx_fright_jar(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_STOP_WATCH:
            effectRet = fx_stop_watch(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_63:
            effectRet = fx_effect_63(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], fVars[6], fVars[7], fVars[8], iVars[9], iVars[10]);
            break;
        case EFFECT_THROW_SPINY:
            effectRet = fx_throw_spiny(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], fVars[6], fVars[7], fVars[8], iVars[9]);
            break;
        case EFFECT_65:
            effectRet = fx_effect_65(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_TUBBA_HEART_ATTACK:
            effectRet = fx_tubba_heart_attack(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_WHIRLWIND:
            effectRet = fx_whirlwind(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_RED_IMPACT:
            effectRet = fx_red_impact(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_FLOATING_CLOUD_PUFF:
            effectRet = fx_floating_cloud_puff(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_ENERGY_IN_OUT:
            effectRet = fx_energy_in_out(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_TATTLE_WINDOW:
            effectRet = fx_tattle_window(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_SHINY_FLARE:
            effectRet = fx_shiny_flare(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_HUFF_PUFF_BREATH:
            effectRet = fx_huff_puff_breath(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], fVars[6], fVars[7], iVars[8]);
            break;
        case EFFECT_COLD_BREATH:
            effectRet = fx_cold_breath(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_EMBERS:
            effectRet = fx_embers(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], fVars[6], fVars[7], iVars[8], iVars[9], fVars[10], fVars[11]);
            break;
        case EFFECT_HIEROGLYPHS:
            effectRet = fx_hieroglyphs(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_MISC_PARTICLES:
            effectRet = fx_misc_particles(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], fVars[6], fVars[7], iVars[8], iVars[9]);
            break;
        case EFFECT_STATIC_STATUS:
            effectRet = fx_static_status(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6], iVars[7]);
            break;
        case EFFECT_MOVING_CLOUD:
            effectRet = fx_moving_cloud(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], fVars[6], fVars[7], fVars[8], fVars[9]);
            break;
        case EFFECT_75:
            effectRet = fx_effect_75(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_FIREWORK_ROCKET:
            effectRet = fx_firework_rocket(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], fVars[6], fVars[7], fVars[8], iVars[9]);
            break;
        case EFFECT_PEACH_STAR_BEAM:
            effectRet = fx_peach_star_beam(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_BUTTERFLIES:
            effectRet = fx_butterflies(iVars[1], fVars[2], fVars[3], fVars[4]);
            break;
        case EFFECT_CHAPTER_CHANGE:
            effectRet = fx_chapter_change(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_ICE_SHARD:
            effectRet = fx_ice_shard(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_SPIRIT_CARD:
            effectRet = fx_spirit_card(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_LIL_OINK:
            effectRet = fx_lil_oink(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_SOMETHING_ROTATING:
            effectRet = fx_something_rotating(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_BREAKING_JUNK:
            effectRet = fx_breaking_junk(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_PARTNER_BUFF:
            effectRet = fx_partner_buff(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_QUIZMO_ASSISTANT:
            effectRet = fx_quizmo_assistant(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_ICE_PILLAR:
            effectRet = fx_ice_pillar(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_SUN:
            effectRet = fx_sun(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_STAR_SPIRITS_ENERGY:
            effectRet = fx_star_spirits_energy(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_PINK_SPARKLES:
            effectRet = fx_pink_sparkles(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_STAR_OUTLINE:
            effectRet = fx_star_outline(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        case EFFECT_86:
            effectRet = fx_effect_86(iVars[1], fVars[2], fVars[3], fVars[4], fVars[5], iVars[6]);
            break;
        default:
            PANIC();
    }

    if (effectRet != nullptr) {
        evt_set_variable(script, LVarF, (s32) effectRet);
    }

    return ApiStatus_DONE2;
}
