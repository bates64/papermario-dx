#include "battle/battle.h"
#include "script_api/battle.h"
#include "stage.xml.h"
#include "effects.h"
#include "battle/stage/common/RandomFlowers.inc.c"
#include "battle/stage/common/MakeSun.inc.c"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Call(SetGroupVisibility, MODEL_dai_05, MODEL_GROUP_VISIBLE)
    Call(SetGroupVisibility, MODEL_0809, MODEL_GROUP_HIDDEN)
    Call(SetGroupVisibility, MODEL_16, MODEL_GROUP_HIDDEN)
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
    .bg = "fla_bg",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};

// flo_02:b

EvtScript EVS_PreBattle_b = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Call(SetGroupVisibility, MODEL_dai_05, MODEL_GROUP_HIDDEN)
    Call(SetGroupVisibility, MODEL_0809, MODEL_GROUP_VISIBLE)
    Call(SetGroupVisibility, MODEL_16, MODEL_GROUP_HIDDEN)
    Exec(EVS_RandomFlowers_FarBack)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_SURFACE, 0, SURFACE_TYPE_FLOWERS)
    ExecWait(MakeSun)
    Return
    End
};

s32 ForegroundModels_b[] = {
    -1,
    MODEL_8hana4,
    MODEL_8hana5,
    MODEL_8hana6,
    MODEL_8hana1,
    MODEL_8hana1,
    MODEL_8hana3,
    STAGE_MODEL_LIST_END
};

OVL_DEF_STAGE(b) = {
    .texture = "flo_tex",
    .bg = "fla_bg",
    .preBattle = &EVS_PreBattle_b,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels_b,
};

// flo_02:c

EvtScript EVS_PreBattle_c = {
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

OVL_DEF_STAGE(c) = {
    .texture = "flo_tex",
    .bg = "fla_bg",
    .preBattle = &EVS_PreBattle_c,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
