#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/kpa_bt02_shape.h"

#include "battle/stage/common/TexturePanner.inc.c"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Set(LVar0, MODEL_2)
    Set(LVar1, TEX_PANNER_1)
    Set(LVar2, -400)
    Set(LVar3, -800)
    Exec(EVS_TexturePanBothU)
    Set(LVar0, MODEL_4)
    Set(LVar1, TEX_PANNER_3)
    Set(LVar2, -400)
    Set(LVar3, -800)
    Exec(EVS_TexturePanBothU)
    Set(LVar0, MODEL_1)
    Set(LVar1, TEX_PANNER_0)
    Set(LVar2, -400)
    Set(LVar3, -800)
    Exec(EVS_TexturePanBothV)
    Set(LVar0, MODEL_3)
    Set(LVar1, TEX_PANNER_2)
    Set(LVar2, -400)
    Set(LVar3, -800)
    Exec(EVS_TexturePanBothV)
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

BATTLE_STAGE_ENTRY = {
    .texture = "kpa_tex",
    .shape = "kpa_bt02_shape",
    .hit = "kpa_bt02_hit",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
