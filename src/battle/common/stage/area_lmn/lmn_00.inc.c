/*
#include "battle/battle.h"
#include "mapfs/lmn_bt00_shape.h"
#include "mapfs/lmn_bt00_hit.h"

#define NAMESPACE A(lmn_00)

EvtScript N(EVS_PreBattle) = {
    EVT_CALL(SetSpriteShading, SHADING_NONE)
    EVT_CALL(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_PostBattle) = {
    EVT_RETURN
    EVT_END
};

s32 N(ForegroundModels)[] = {
    STAGE_MODEL_LIST_END
};

Stage NAMESPACE = {
    .texture = "lmn_tex",
    .shape = "lmn_bt00_shape",
    .hit = "lmn_bt00_hit",
    .bg = "lmn_bg",
    .preBattle = &N(EVS_PreBattle),
    .postBattle = &N(EVS_PostBattle),
    .foregroundModelList = N(ForegroundModels),
};
*/
