#include "battle/battle.h"
#include "mapfs/pra_bt03_shape.h"

#define NAMESPACE A(pra_03b)

EvtScript N(EVS_PreBattle) = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Call(SetGroupVisibility, MODEL_g115, MODEL_GROUP_HIDDEN)
    Return
    End
};

EvtScript N(EVS_PostBattle) = {
    Return
    End
};

Stage NAMESPACE = {
    .texture = "pra_tex",
    .module = "areas/pra/pra_bt03",
    .preBattle = &N(EVS_PreBattle),
    .postBattle = &N(EVS_PostBattle),
};
