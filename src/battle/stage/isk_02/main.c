#include "battle/battle.h"
#include "script_api/battle.h"
#include "stage.xml.h"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_BTL_ISK)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

s32 ForegroundModels[] = {
    MODEL_o398,
    MODEL_o397,
    MODEL_o399,
    STAGE_MODEL_LIST_END
};

OVL_DEF_STAGE() = {
    .texture = "isk_tex",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};

// isk_02:b

EvtScript EVS_PreBattle_b = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Call(EnableModel, MODEL_o365, false)
    Call(EnableModel, MODEL_o366, false)
    Call(EnableModel, MODEL_o367, false)
    Call(EnableModel, MODEL_o389, false)
    Call(EnableModel, MODEL_o390, false)
    Call(EnableModel, MODEL_o391, false)
    Return
    End
};

OVL_DEF_STAGE(b) = {
    .texture = "isk_tex",
    .preBattle = &EVS_PreBattle_b,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};

// isk_02:c

EvtScript EVS_PreBattle_c = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Call(EnableModel, MODEL_kai2, false)
    Call(EnableModel, MODEL_kai1, false)
    Return
    End
};

OVL_DEF_STAGE(c) = {
    .texture = "isk_tex",
    .preBattle = &EVS_PreBattle_c,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
