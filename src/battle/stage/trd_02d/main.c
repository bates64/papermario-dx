#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/trd_bt02_shape.h"

#include "battle/stage/common/BeachEffects.inc.c"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Call(EnableModel, MODEL_mizu, false)
    Call(EnableModel, MODEL_mizu2, false)
    Call(EnableModel, MODEL_o298, false)
    Call(EnableModel, MODEL_o297, false)
    Call(EnableModel, MODEL_kiwa, false)
    Call(EnableModel, MODEL_tyuu, false)
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

s32 ForegroundModels[] = {
    MODEL_saku,
    STAGE_MODEL_LIST_END
};

OVL_DEF_STAGE() = {
    .texture = "trd_tex",
    .shape = "trd_bt02_shape",
    .hit = "trd_bt02_hit",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
