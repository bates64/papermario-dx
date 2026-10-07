#include "battle/battle.h"
#include "script_api/battle.h"
#include "stage.xml.h"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Call(SetGroupVisibility, MODEL_g2, MODEL_GROUP_HIDDEN)
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

s32 ForegroundModels[] = {
    MODEL_o91,
    MODEL_o90,
    MODEL_o86,
    STAGE_MODEL_LIST_END
};

OVL_DEF_STAGE() = {
    .texture = "jan_tex",
    .bg = "jan_bg",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};

// jan_03:b

EvtScript EVS_PreBattle_b = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Call(SetGroupVisibility, MODEL_g39, MODEL_GROUP_HIDDEN)
    Return
    End
};

OVL_DEF_STAGE(b) = {
    .texture = "jan_tex",
    .bg = "jan_bg",
    .preBattle = &EVS_PreBattle_b,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
