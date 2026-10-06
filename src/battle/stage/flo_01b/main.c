#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/flo_bt01_shape.h"
#include "effects.h"

#include "battle/stage/common/RandomFlowers.inc.c"
#include "battle/stage/common/MakeSun.inc.c"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Call(SetGroupVisibility, MODEL_dai_03, MODEL_GROUP_HIDDEN)
    Call(SetGroupVisibility, MODEL_dai_04, MODEL_GROUP_VISIBLE)
    Call(SetGroupVisibility, MODEL_dai_05, MODEL_GROUP_HIDDEN)
    Exec(EVS_RandomFlowers_Background)
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
    MODEL_kuki,
    MODEL_hana1,
    MODEL_mae1,
    MODEL_mae2,
    MODEL_mae3,
    STAGE_MODEL_LIST_END
};

BATTLE_STAGE_ENTRY = {
    .texture = "flo_tex",
    .shape = "flo_bt01_shape",
    .hit = "flo_bt01_hit",
    .bg = "fla_bg",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
