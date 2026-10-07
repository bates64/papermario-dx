#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/stage/isk_06_shape.h"
#include "effects.h"

BSS EffectInstance* TorchFlame;

API_CALLABLE(CreateTorchFX) {
    fx_flame(FX_FLAME_RED, -110.0f, 80.0f, -146.0f, 0.3f, &TorchFlame);
    return ApiStatus_DONE2;
}

API_CALLABLE(DeleteTorchFX) {
    remove_effect(TorchFlame);
    return ApiStatus_DONE2;
}

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Call(CreateTorchFX)
    Return
    End
};

EvtScript EVS_PostBattle = {
    Call(DeleteTorchFX)
    Return
    End
};

OVL_DEF_STAGE() = {
    .texture = "isk_tex",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
};

// isk_06:b

API_CALLABLE(CreateTorchFX_b) {
    fx_flame(FX_FLAME_RED, -110.0f, 80.0f, -146.0, 0.3f, &TorchFlame);
    return ApiStatus_DONE2;
}

EvtScript EVS_PreBattle_b = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Call(CreateTorchFX_b)
    Call(EnableModel, MODEL_kesu, false)
    Return
    End
};

OVL_DEF_STAGE(b) = {
    .texture = "isk_tex",
    .preBattle = &EVS_PreBattle_b,
    .postBattle = &EVS_PostBattle,
};
