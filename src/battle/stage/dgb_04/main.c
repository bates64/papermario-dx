#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/dgb_bt04_shape.h"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

s32 ForegroundModels[] = {
    MODEL_kumo1,
    STAGE_MODEL_LIST_END
};

OVL_DEF_STAGE() = {
    .texture = "dgb_tex",
    .shape = "dgb_bt04_shape",
    .hit = "dgb_bt04_hit",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
