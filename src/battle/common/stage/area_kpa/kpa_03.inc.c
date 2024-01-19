#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/kpa_bt03_shape.h"

#define NAMESPACE A(kpa_03)

EvtScript N(EVS_PreBattle) = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Call(SetDarknessMode, BTL_DARKNESS_MODE_1)
    Return
    End
};

EvtScript N(EVS_PostBattle) = {
    Return
    End
};

s32 N(ForegroundModels)[] = {
    MODEL_tar1,
    STAGE_MODEL_LIST_END
};

Stage NAMESPACE = {
    .texture = "kpa_tex",
    .module = "areas/kpa/kpa_bt03",
    .preBattle = &N(EVS_PreBattle),
    .postBattle = &N(EVS_PostBattle),
    .foregroundModelList = N(ForegroundModels),
};
