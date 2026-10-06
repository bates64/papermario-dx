#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/isk_bt02_shape.h"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Call(EnableModel, MODEL_kai2, false)
    Call(EnableModel, MODEL_kai1, false)
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

OVL_DEF_STAGE() = {
    .texture = "isk_tex",
    .shape = "isk_bt02_shape",
    .hit = "isk_bt02_hit",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
