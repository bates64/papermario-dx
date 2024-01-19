#include "battle/battle.h"
#include "mapfs/dgb_bt04_shape.h"

#define NAMESPACE A(dgb_04)

EvtScript N(EVS_PreBattle) = {
    Call(SetSpriteShading, SHADING_NONE)
    Return
    End
};

EvtScript N(EVS_PostBattle) = {
    Return
    End
};

s32 N(ForegroundModels)[] = {
    MODEL_kumo1,
    STAGE_MODEL_LIST_END
};

Stage NAMESPACE = {
    .texture = "dgb_tex",
    .module = "areas/dgb/dgb_bt04",
    .preBattle = &N(EVS_PreBattle),
    .postBattle = &N(EVS_PostBattle),
    .foregroundModelList = N(ForegroundModels),
};
