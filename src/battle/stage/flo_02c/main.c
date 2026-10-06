#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/flo_bt02_shape.h"
#include "effects.h"

#include "battle/stage/common/RandomFlowers.inc.c"
#include "battle/stage/common/MakeSun.inc.c"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Call(SetGroupVisibility, MODEL_dai_05, MODEL_GROUP_VISIBLE)
    Call(SetGroupVisibility, MODEL_0809, MODEL_GROUP_HIDDEN)
    Call(SetGroupVisibility, MODEL_g90, MODEL_GROUP_HIDDEN)
    Call(SetGroupVisibility, MODEL_16, MODEL_GROUP_VISIBLE)
    Exec(EVS_RandomFlowers_FarBack)
    ExecWait(MakeSun)
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

s32 ForegroundModels[] = {
    -1,
    MODEL_o403,
    MODEL_o404,
    STAGE_MODEL_LIST_END
};

OVL_DEF_STAGE() = {
    .texture = "flo_tex",
    .shape = "flo_bt02_shape",
    .hit = "flo_bt02_hit",
    .bg = "fla_bg",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
