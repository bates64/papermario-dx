
/*
#include "battle/battle.h"
#include "mapfs/mod_bt00_shape.h"
#include "mapfs/mod_bt00_hit.h"

#define NAMESPACE A(mod_00)

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
    .texture = "aaa_tex",
    .shape = "mod_bt00_shape",
    .hit = "mod_bt00_hit",
    .preBattle = &N(EVS_PreBattle),
    .postBattle = &N(EVS_PostBattle),
    .foregroundModelList = N(ForegroundModels),
};
*/
