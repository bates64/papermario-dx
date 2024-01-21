/*
#include "battle/battle.h"
#include "mapfs/lmn_bt00_shape.h"
#include "mapfs/lmn_bt00_hit.h"

#define NAMESPACE A(lmn_00)

EvtScript N(EVS_PreBattle) = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Return
    End
};

EvtScript N(EVS_PostBattle) = {
    Return
    End
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
