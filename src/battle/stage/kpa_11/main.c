#include "battle/battle.h"
#include "script_api/battle.h"
#include "stage.xml.h"

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
    MODEL_h2,
    STAGE_MODEL_LIST_END
};

OVL_DEF_STAGE() = {
    .texture = "kpa_tex",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
