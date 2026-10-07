#include "battle/battle.h"
#include "script_api/battle.h"
#include "stage.xml.h"
#include "battle/stage/common/TexturePanner.inc.c"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Set(LVar0, MODEL_kemu2)
    Set(LVar1, TEX_PANNER_0)
    Set(LVar2, -200)
    Set(LVar3, 0)
    Exec(EVS_TexturePanMain)
    Set(LVar0, MODEL_kemu1)
    Set(LVar1, TEX_PANNER_1)
    Set(LVar2, -120)
    Set(LVar3, 0)
    Exec(EVS_TexturePanMain)
    Set(LVar0, MODEL_kemu3)
    Set(LVar1, TEX_PANNER_2)
    Set(LVar2, -100)
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
    MODEL_kemu1,
    STAGE_MODEL_LIST_END
};

OVL_DEF_STAGE() = {
    .texture = "kpa_tex",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
