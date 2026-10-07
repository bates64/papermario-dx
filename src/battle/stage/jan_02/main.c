#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/stage/jan_02_shape.h"

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
    MODEL_o64,
    MODEL_o65,
    MODEL_o66,
    STAGE_MODEL_LIST_END
};

OVL_DEF_STAGE() = {
    .texture = "jan_tex",
    .bg = "yos_bg",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
