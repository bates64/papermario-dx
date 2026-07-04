#include "common.h"
#include "functions.h"
#include "game_modes.h"

API_CALLABLE(GetAngleBetweenNPCs) {
    Bytecode* args = script->ptrReadPos;

    s32 aID = evt_get_variable(script, *args++);
    s32 bID = evt_get_variable(script, *args++);
    Bytecode outVar = *args++;

    Npc* a = resolve_npc(script, aID);
    Npc* b = resolve_npc(script, bID);
    evt_set_variable(script, outVar, atan2(a->pos.x, a->pos.z, b->pos.x, b->pos.z));

    return ApiStatus_DONE2;
}

API_CALLABLE(GetAngleToNPC) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    Bytecode* args = script->ptrReadPos;

    s32 npcID = evt_get_variable(script, *args++);
    Bytecode outVar = *args++;

    Npc* npc = resolve_npc(script, npcID);
    evt_set_variable(script, outVar, atan2(playerStatus->pos.x, playerStatus->pos.z, npc->pos.x, npc->pos.z));

    return ApiStatus_DONE2;
}

API_CALLABLE(GetAngleToPlayer) {
    PlayerStatus* playerStatus = &gPlayerStatus;
    Bytecode* args = script->ptrReadPos;

    s32 npcID = evt_get_variable(script, *args++);
    Bytecode outVar = *args++;

    Npc* npc = resolve_npc(script, npcID);
    evt_set_variable(script, outVar, atan2(npc->pos.x, npc->pos.z, playerStatus->pos.x, playerStatus->pos.z));

    return ApiStatus_DONE2;
}

API_CALLABLE(AwaitPlayerApproach) {
    Bytecode* args = script->ptrReadPos;
    PlayerStatus* playerStatus = &gPlayerStatus;

    s32* targetX = &script->functionTemp[0];
    s32* targetZ = &script->functionTemp[1];
    s32* distanceRequired = &script->functionTemp[2];

    f32 distance;

    if (isInitialCall) {
        *targetX = evt_get_variable(script, *args++);
        *targetZ = evt_get_variable(script, *args++);
        *distanceRequired = evt_get_variable(script, *args++);
    }

    distance = dist2D(
        playerStatus->pos.x, playerStatus->pos.z,
        *targetX, *targetZ
    );

    if (distance < *distanceRequired) {
        return ApiStatus_DONE2;
    } else {
        return ApiStatus_BLOCK;
    }
}

API_CALLABLE(IsPlayerWithin) {
    Bytecode* args = script->ptrReadPos;
    PlayerStatus* playerStatus = &gPlayerStatus;

    s32* targetX = &script->functionTemp[0];
    s32* targetZ = &script->functionTemp[1];
    s32* distanceRequired = &script->functionTemp[2];

    f32 distance;
    Bytecode outVar = LVar0;

    if (isInitialCall) {
        *targetX = evt_get_variable(script, *args++);
        *targetZ = evt_get_variable(script, *args++);
        *distanceRequired = evt_get_variable(script, *args++);
        outVar = *args++;
    }

    distance = dist2D(
        playerStatus->pos.x, playerStatus->pos.z,
        *targetX, *targetZ
    );

    evt_set_variable(script, outVar, 0);
    if (distance < *distanceRequired) {
        evt_set_variable(script, outVar, 1);
    }

    return ApiStatus_DONE2;
}

API_CALLABLE(AwaitPlayerLeave) {
    Bytecode* ptrReadPos = script->ptrReadPos;
    PlayerStatus* playerStatus = &gPlayerStatus;

    s32* targetX = &script->functionTemp[0];
    s32* targetZ = &script->functionTemp[1];
    s32* distanceRequired = &script->functionTemp[2];

    f32 distance;

    if (isInitialCall) {
        *targetX = evt_get_variable(script, *ptrReadPos++);
        *targetZ = evt_get_variable(script, *ptrReadPos++);
        *distanceRequired = evt_get_variable(script, *ptrReadPos++);
    }

    distance = dist2D(
        playerStatus->pos.x, playerStatus->pos.z,
        *targetX, *targetZ
    );

    if (distance > *distanceRequired) {
        return ApiStatus_DONE2;
    } else {
        return ApiStatus_BLOCK;
    }
}

API_CALLABLE(EnableScreenMotionBlur) {
    Bytecode* args = script->ptrReadPos;
    s32 value = evt_get_float_variable(script, *args++);

    set_screen_overlay_center(SCREEN_LAYER_FRONT, 0, 12, 20);
    set_screen_overlay_center(SCREEN_LAYER_FRONT, 1, 308, 220);
    set_screen_overlay_params_front(OVERLAY_BLUR, value);

    return ApiStatus_DONE2;
}

API_CALLABLE(DisableScreenMotionBlur) {
    set_screen_overlay_params_front(OVERLAY_BLUR, 0);
    return ApiStatus_DONE2;
}

API_CALLABLE(SetTimeFreezeMode) {
    Bytecode* args = script->ptrReadPos;

    set_time_freeze_mode(evt_get_variable(script, *args++));
    return ApiStatus_DONE2;
}

API_CALLABLE(ModifyGlobalOverrideFlags) {
    Bytecode* args = script->ptrReadPos;
    s32 setMode = evt_get_variable(script, *args++);
    s32 flags = evt_get_variable(script, *args++);

    if (setMode) {
        gOverrideFlags |= flags;
    } else {
        gOverrideFlags &= ~flags;
    }

    return ApiStatus_DONE2;
}

API_CALLABLE(SetValueByRef) {
    Bytecode* args = script->ptrReadPos;

    s32 dest = evt_get_variable(script, *args++); // reference
    s32 src = evt_get_variable(script, *args++);
    evt_set_variable(script, dest, src);

    return ApiStatus_DONE2;
}

API_CALLABLE(GetValueByRef) {
    Bytecode* args = script->ptrReadPos;
    s32 src = evt_get_variable(script, *args++); // reference
    Bytecode dest = *args++;

    evt_set_variable(script, dest, evt_get_variable(script, src));

    return ApiStatus_DONE2;
}

API_CALLABLE(EnableWorldStatusBar) {
    Bytecode* args = script->ptrReadPos;
    b32 shouldEnable = evt_get_variable(script, *args++);

    if (shouldEnable) {
        decrement_status_bar_disabled();
    } else {
        increment_status_bar_disabled();
    }

    return ApiStatus_DONE2;
}

API_CALLABLE(ShowWorldStatusBar) {
    Bytecode* args = script->ptrReadPos;
    b32 shouldShow = evt_get_variable(script, *args++);

    if (shouldShow) {
        status_bar_ignore_changes();
        close_status_bar();
    } else {
        status_bar_respond_to_changes();
    }

    return ApiStatus_DONE2;
}

API_CALLABLE(SetGameMode) {
    Bytecode* args = script->ptrReadPos;
    s16 mode = evt_get_variable(script, *args++);

    set_game_mode(mode);

    return ApiStatus_DONE2;
}

#if VERSION_PAL
API_CALLABLE(GetLanguage) {
    Bytecode* args = script->ptrReadPos;

    evt_set_variable(script, *args++, gCurrentLanguage);
    return ApiStatus_DONE2;
}
#endif

API_CALLABLE(GetGameContext) {
    Bytecode* args = script->ptrReadPos;

    evt_set_variable(script, *args++, gGameStatusPtr->context);
    return ApiStatus_DONE2;
}
