#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/trd_bt00_shape.h"

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
    MODEL_p1,
    STAGE_MODEL_LIST_END
};

BATTLE_STAGE_ENTRY = {
    .texture = "trd_tex",
    .shape = "trd_bt00_shape",
    .hit = "trd_bt00_hit",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
