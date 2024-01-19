#include "battle/battle.h"
#include "mapfs/kpa_bt08_shape.h"

#define NAMESPACE A(kpa_08)

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
    MODEL_o478,
    STAGE_MODEL_LIST_END
};

Stage NAMESPACE = {
    .texture = "kpa_tex",
    .module = "areas/kpa/kpa_bt08",
    .preBattle = &N(EVS_PreBattle),
    .postBattle = &N(EVS_PostBattle),
    .foregroundModelList = N(ForegroundModels),
};
