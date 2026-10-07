#include "battle/battle.h"
#include "script_api/battle.h"
#include "battle/stage/isk_06/stage.xml.h"
#include "effects.h"

BSS EffectInstance* TorchFlame;

API_CALLABLE(CreateTorchFX) {
    fx_flame(FX_FLAME_RED, 0, 72.0f, -146.0, 0.3f, &TorchFlame);
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
