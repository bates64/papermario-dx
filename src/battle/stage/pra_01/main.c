#include "battle/battle.h"
#include "script_api/battle.h"
#include "stage.xml.h"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Call(EnableBattleFloorReflections, true)
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
