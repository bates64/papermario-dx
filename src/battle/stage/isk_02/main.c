#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/isk_bt02_shape.h"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_BTL_ISK)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

s32 ForegroundModels[] = {
    MODEL_o398,
    MODEL_o397,
    MODEL_o399,
    STAGE_MODEL_LIST_END
};

BATTLE_STAGE_ENTRY = {
    .texture = "isk_tex",
    .shape = "isk_bt02_shape",
    .hit = "isk_bt02_hit",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
