#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/stage/trd_04_shape.h"
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

OVL_DEF_STAGE() = {
    .texture = "trd_tex",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
