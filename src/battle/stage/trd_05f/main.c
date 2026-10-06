#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/trd_bt05_shape.h"

#include "battle/stage/common/BeachEffects.inc.c"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Set(LVar0, MODEL_o318)
    Exec(EVS_AnimateWave)
    Call(EnableModel, MODEL_mizu1, false)
    Call(EnableModel, MODEL_mizu2, false)
    Call(EnableModel, MODEL_mizu3, false)
    Call(EnableModel, MODEL_ori, false)
    Call(EnableModel, MODEL_saku1, false)
    Call(EnableModel, MODEL_saku2, false)
    Call(EnableModel, MODEL_mizu4, false)
    Call(EnableModel, MODEL_hako, false)
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

BATTLE_STAGE_ENTRY = {
    .texture = "trd_tex",
    .shape = "trd_bt05_shape",
    .hit = "trd_bt05_hit",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
};
