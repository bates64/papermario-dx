#include "battle/battle.h"
#include "mapfs/dgb_bt05_shape.h"

#define NAMESPACE A(dgb_05)

EvtScript N(EVS_PreBattle) = {
    Call(SetSpriteShading, SHADING_NONE)
    Return
    End
};

EvtScript N(EVS_PostBattle) = {
    Return
    End
};

Stage NAMESPACE = {
    .texture = "dgb_tex",
    .module = "areas/dgb/dgb_bt05",
    .preBattle = &N(EVS_PreBattle),
    .postBattle = &N(EVS_PostBattle),
};
