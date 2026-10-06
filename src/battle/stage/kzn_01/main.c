#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/kzn_bt01_shape.h"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Call(SetGroupVisibility, MODEL_o363, MODEL_GROUP_HIDDEN)
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

s32 ForegroundModels[] = {
    MODEL_ue2,
    MODEL_ue1,
    MODEL_iwa3,
    MODEL_sita1,
    MODEL_ue3,
    STAGE_MODEL_LIST_END
};

OVL_DEF_STAGE() = {
    .texture = "kzn_tex",
    .shape = "kzn_bt01_shape",
    .hit = "kzn_bt01_hit",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
