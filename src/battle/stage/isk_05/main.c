#include "battle/battle.h"
#include "script_api/battle.h"
#include "stage.xml.h"
#include "effects.h"

BSS EffectInstance* TorchFlameL;
API_CALLABLE(CreateTorchFX) {
    fx_flame(FX_FLAME_RED, -90.0f, 45.0f, -146.0f, 0.25f, &TorchFlameL);
    fx_flame(FX_FLAME_RED, 80.0f, 45.0f, -146.0f, 0.25f, &TorchFlameL);
    return ApiStatus_DONE2;
}

API_CALLABLE(DeleteTorchFX) {
    remove_effect(TorchFlameL);
    remove_effect(TorchFlameL);
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
