#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/stage/flo_01_shape.h"
#include "effects.h"
#include "battle/stage/common/RandomFlowers.inc.c"
#include "battle/stage/common/MakeSun.inc.c"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Call(SetGroupVisibility, MODEL_dai_03, MODEL_GROUP_VISIBLE)
    Call(SetGroupVisibility, MODEL_dai_04, MODEL_GROUP_HIDDEN)
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
    MODEL_o400,
    MODEL_o401,
    MODEL_o407,
    MODEL_o411,
    MODEL_o422,
    MODEL_o423,
    MODEL_o424,
    STAGE_MODEL_LIST_END
};

OVL_DEF_STAGE() = {
    .texture = "flo_tex",
    .bg = "fla_bg",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};

// flo_01:b

EvtScript EVS_PreBattle_b = {
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

s32 ForegroundModels_b[] = {
    -1,
    MODEL_kuki,
    MODEL_hana1,
    MODEL_mae1,
    MODEL_mae2,
    MODEL_mae3,
    STAGE_MODEL_LIST_END
};

OVL_DEF_STAGE(b) = {
    .texture = "flo_tex",
    .bg = "fla_bg",
    .preBattle = &EVS_PreBattle_b,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels_b,
};

// flo_01:c

EvtScript EVS_PreBattle_c = {
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

s32 ForegroundModels_c[] = {
    -1,
    MODEL_o381,
    MODEL_o382,
    MODEL_o388,
    MODEL_o389,
    MODEL_o390,
    MODEL_o383,
    STAGE_MODEL_LIST_END
};

OVL_DEF_STAGE(c) = {
    .texture = "flo_tex",
    .bg = "fla_bg",
    .preBattle = &EVS_PreBattle_c,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels_c,
};
