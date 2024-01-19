#include "battle/battle.h"
#include "mapfs/dgb_bt01_shape.h"

#define NAMESPACE A(dgb_01)

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
    .module = "areas/dgb/dgb_bt01",
    .preBattle = &N(EVS_PreBattle),
    .postBattle = &N(EVS_PostBattle),
};
