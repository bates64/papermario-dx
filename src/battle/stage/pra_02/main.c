#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/stage/pra_02_shape.h"
#include "battle/stage/common/TexturePanner.inc.c"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Call(EnableBattleFloorReflections, true)
    Set(LVar0, MODEL_o412)
    Set(LVar1, TEX_PANNER_0)
    Set(LVar2, 3000)
    Set(LVar3, 0)
    Exec(EVS_TexturePanMain)
    Set(LVar0, MODEL_o413)
    Set(LVar1, TEX_PANNER_0)
    Set(LVar2, 3000)
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
    MODEL_o383,
    MODEL_o384,
    MODEL_o385,
    STAGE_MODEL_LIST_END
};

OVL_DEF_STAGE() = {
    .texture = "pra_tex",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
