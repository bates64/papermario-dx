#include "battle/battle.h"
#include "script_api/battle.h"
#include "stage.xml.h"
#include "effects.h"

BSS EffectInstance* TorchFlameL;
API_CALLABLE(CreateTorchFX) {
    fx_flame(FX_FLAME_RED, -133.0f, 72.0f, -143.0f, 0.3f, &TorchFlameL);
    fx_flame(FX_FLAME_RED,  129.0f, 72.0f, -143.0f, 0.3f, &TorchFlameL);
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

s32 ForegroundModels[] = {
    MODEL_o500,
    MODEL_o501,
    STAGE_MODEL_LIST_END
};

OVL_DEF_STAGE() = {
    .texture = "isk_tex",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
