#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/isk_bt05_shape.h"
#include "effects.h"

BSS EffectInstance* TorchFlameL;
BSS EffectInstance* TorchFlameR;

API_CALLABLE(CreateTorchFX) {
    fx_flame(FX_FLAME_RED, -90.0f, 45.0f, -146.0f, 0.25f, &TorchFlameL);
    fx_flame(FX_FLAME_RED, 80.0f, 45.0f, -146.0f, 0.25f, &TorchFlameR);
    return ApiStatus_DONE2;
}

API_CALLABLE(DeleteTorchFX) {
    remove_effect(TorchFlameL);
    remove_effect(TorchFlameR);
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
    .shape = "isk_bt05_shape",
    .hit = "isk_bt05_hit",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
};
