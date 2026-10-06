#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/trd_bt04_shape.h"

#include "battle/stage/common/TexturePanner.inc.c"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Set(LVar0, MODEL_hikari1)
    Set(LVar1, TEX_PANNER_0)
    Set(LVar2, 40)
    Set(LVar3, 0)
    Exec(EVS_TexturePanMain)
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

s32 ForegroundModels[] = {
    MODEL_hikari1,
    STAGE_MODEL_LIST_END
};

BATTLE_STAGE_ENTRY = {
    .texture = "trd_tex",
    .shape = "trd_bt04_shape",
    .hit = "trd_bt04_hit",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
