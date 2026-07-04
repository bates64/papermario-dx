#include "common.h"
#include "effects.h"

API_CALLABLE(N(SpitInk)) {
    Bytecode* args = script->ptrReadPos;
    EffectInstance* effect;
    f32 targetX, targetY, targetZ;
    f32 startX, startY, startZ;
    f32 yaw;

    targetX = evt_get_variable(script, *args++);
    targetY = evt_get_variable(script, *args++);
    targetZ = evt_get_variable(script, *args++);
    startX = evt_get_variable(script, *args++);
    startY = evt_get_variable(script, *args++);
    startZ = evt_get_variable(script, *args++);
    yaw = atan2(targetX, targetY, startX, startY + 40.0f);

    effect = fx_water_fountain(FX_FOUNTAIN_TYPE_INK, startX - 10.0f, startY + 60.0f, startZ + 20.0f, 2.5f, 40);
    effect->data.waterFountain->angle = yaw;
    effect->data.waterFountain->primColor.r = 2;
    effect->data.waterFountain->primColor.g = 2;
    effect->data.waterFountain->primColor.b = 2;
    effect->data.waterFountain->envColor.r = 80;
    effect->data.waterFountain->envColor.g = 80;
    effect->data.waterFountain->envColor.b = 80;
    return ApiStatus_DONE2;
}
