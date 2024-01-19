#include "battle/battle.h"
#include "mapfs/omo_bt02_shape.h"

#define NAMESPACE A(omo_02)

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

Stage NAMESPACE = {
    .texture = "omo_tex",
    .module = "areas/omo/omo_bt02",
    .bg = "omo_bg",
    .preBattle = &N(EVS_PreBattle),
    .postBattle = &N(EVS_PostBattle),
};
