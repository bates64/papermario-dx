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
    Call(SetGroupVisibility, MODEL_dai_04, MODEL_GROUP_HIDDEN)
    Call(SetGroupVisibility, MODEL_dai_05, MODEL_GROUP_VISIBLE)
    Exec(EVS_RandomFlowers_Background)
    Exec(EVS_RandomFlowers_Foreground)
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
    MODEL_o381,
    MODEL_o382,
    MODEL_o388,
    MODEL_o389,
    MODEL_o390,
    MODEL_o383,
    STAGE_MODEL_LIST_END
};

OVL_DEF_STAGE() = {
    .texture = "flo_tex",
    .shape = "flo_bt01_shape",
    .hit = "flo_bt01_hit",
    .bg = "fla_bg",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
