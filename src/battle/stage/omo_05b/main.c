#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/omo_bt05_shape.h"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Call(SetGroupVisibility, MODEL_g2, MODEL_GROUP_HIDDEN)
    Call(SetGroupVisibility, MODEL_dai2, MODEL_GROUP_HIDDEN)
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

s32 ForegroundModels[] = {
    MODEL_mae2,
    STAGE_MODEL_LIST_END
};

OVL_DEF_STAGE() = {
    .texture = "omo_tex",
    .shape = "omo_bt05_shape",
    .hit = "omo_bt05_hit",
    .bg = "omo_bg",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
