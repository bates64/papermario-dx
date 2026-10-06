#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/arn_bt05_shape.h"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

s32 ForegroundModels[] = {
    MODEL_o354,
    STAGE_MODEL_LIST_END
};

OVL_DEF_STAGE() = {
    .texture = "arn_tex",
    .shape = "arn_bt05_shape",
    .hit = "arn_bt05_hit",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
