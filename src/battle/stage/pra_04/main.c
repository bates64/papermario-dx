#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/pra_bt04_shape.h"

#include "battle/stage/common/TexturePanner.inc.c"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Set(LVar0, MODEL_kira1)
    Set(LVar1, TEX_PANNER_0)
    Set(LVar2, 3000)
    Set(LVar3, 0)
    Exec(EVS_TexturePanMain)
    Set(LVar0, MODEL_kira2)
    Set(LVar1, TEX_PANNER_1)
    Set(LVar2, 3000)
    Set(LVar3, 0)
    Exec(EVS_TexturePanMain)
    Call(EnableBattleFloorReflections, true)
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

OVL_DEF_STAGE() = {
    .texture = "pra_tex",
    .shape = "pra_bt04_shape",
    .hit = "pra_bt04_hit",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
};
