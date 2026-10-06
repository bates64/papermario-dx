#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/kpa_bt08_shape.h"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

s32 ForegroundModels[] = {
    MODEL_o478,
    STAGE_MODEL_LIST_END
};

OVL_DEF_STAGE() = {
    .texture = "kpa_tex",
    .shape = "kpa_bt08_shape",
    .hit = "kpa_bt08_hit",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
