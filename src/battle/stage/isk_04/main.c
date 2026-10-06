#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/isk_bt04_shape.h"
#include "effects.h"

BSS EffectInstance* TorchFlameL;
BSS EffectInstance* TorchFlameR;

API_CALLABLE(CreateTorchFX) {
    fx_flame(FX_FLAME_RED, -133.0f, 72.0f, -143.0f, 0.3f, &TorchFlameL);
    fx_flame(FX_FLAME_RED,  129.0f, 72.0f, -143.0f, 0.3f, &TorchFlameR);
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

s32 ForegroundModels[] = {
    MODEL_o500,
    MODEL_o501,
    STAGE_MODEL_LIST_END
};

BATTLE_STAGE_ENTRY = {
    .texture = "isk_tex",
    .shape = "isk_bt04_shape",
    .hit = "isk_bt04_hit",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
