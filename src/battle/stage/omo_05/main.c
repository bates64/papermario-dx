#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/stage/omo_05_shape.h"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Call(SetGroupVisibility, MODEL_g1, MODEL_GROUP_HIDDEN)
    Call(SetGroupVisibility, MODEL_dai1, MODEL_GROUP_HIDDEN)
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

s32 ForegroundModels[] = {
    MODEL_itigo,
    MODEL_kisya,
    STAGE_MODEL_LIST_END
};

OVL_DEF_STAGE() = {
    .texture = "omo_tex",
    .bg = "omo_bg",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};

// omo_05:b

EvtScript EVS_PreBattle_b = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Call(SetGroupVisibility, MODEL_g2, MODEL_GROUP_HIDDEN)
    Call(SetGroupVisibility, MODEL_dai2, MODEL_GROUP_HIDDEN)
    Return
    End
};

s32 ForegroundModels_b[] = {
    MODEL_mae2,
    STAGE_MODEL_LIST_END
};

OVL_DEF_STAGE(b) = {
    .texture = "omo_tex",
    .bg = "omo_bg",
    .preBattle = &EVS_PreBattle_b,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels_b,
};
