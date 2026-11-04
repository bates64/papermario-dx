#include "common.h"

API_CALLABLE(SetSpriteShading) {
    apply_sprite_shading((const SpriteShadingProfile*) evt_get_variable(script, *script->ptrReadPos));
    return ApiStatus_DONE2;
}

API_CALLABLE(EnableSpriteShading) {
    Bytecode* args = script->ptrReadPos;
    s32 enabled = evt_get_variable(script, *args++);

    if (enabled) {
        gSpriteShadingProfile->flags |= SPR_SHADING_FLAG_ENABLED;
    } else {
        gSpriteShadingProfile->flags &= ~SPR_SHADING_FLAG_ENABLED;
    }
    return ApiStatus_DONE2;
}

API_CALLABLE(GetDemoState) {
    evt_set_variable(script, *script->ptrReadPos, gGameStatusPtr->demoState);
    return ApiStatus_DONE2;
}

API_CALLABLE(DemoPressButton) {
    gGameStatusPtr->demoButtonInput |= evt_get_variable(script, *script->ptrReadPos);
    return ApiStatus_DONE2;
}

API_CALLABLE(DemoReleaseButton) {
    gGameStatusPtr->demoButtonInput &= ~evt_get_variable(script, *script->ptrReadPos);
    return ApiStatus_DONE2;
}

API_CALLABLE(DemoSetButtons) {
    gGameStatusPtr->demoButtonInput = evt_get_variable(script, *script->ptrReadPos);
    return ApiStatus_DONE2;
}

API_CALLABLE(DemoJoystickRadial) {
    Bytecode* args = script->ptrReadPos;
    f32 mag = evt_get_float_variable(script, *args++);
    f32 ang = evt_get_float_variable(script, *args++);

    gGameStatus.demoStickX = mag * sin_deg(ang);
    gGameStatus.demoStickY = mag * cos_deg(ang);

    return ApiStatus_DONE2;
}

API_CALLABLE(DemoJoystickXY) {
    Bytecode* args = script->ptrReadPos;
    f32 x = evt_get_float_variable(script, *args++);
    f32 y = evt_get_float_variable(script, *args++);

    gGameStatus.demoStickX = x;
    gGameStatus.demoStickY = y;

    return ApiStatus_DONE2;
}
