#include "battle/battle.h"
#include "script_api/battle.h"
#include "stage.xml.h"
#include "battle/stage/common/Snowflakes.inc.c"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetGroupVisibility, MODEL_p2, MODEL_GROUP_HIDDEN)
    Call(SetGroupVisibility, MODEL_p3, MODEL_GROUP_HIDDEN)
    Thread
        Set(LVar0, MODEL_o253)
        Set(LVar1, 0)
        Exec(EVS_AnimateHangingSnowflake_RandomSpin)
        Wait(5)
        Set(LVar0, MODEL_o283)
        Set(LVar1, 0)
        Exec(EVS_AnimateHangingSnowflake_RandomSpin)
        Wait(5)
        Set(LVar0, MODEL_o284)
        Set(LVar1, 0)
        Exec(EVS_AnimateHangingSnowflake_RandomSpin)
        Wait(5)
        Set(LVar0, MODEL_o285)
        Set(LVar1, 0)
        Exec(EVS_AnimateHangingSnowflake_RandomSpin)
    EndThread
    Exec(EVS_SpawnSnowfall)
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

s32 ForegroundModels[] = {
    -1,
    MODEL_kouri1,
    STAGE_MODEL_LIST_END
};

OVL_DEF_STAGE() = {
    .texture = "sam_tex",
    .bg = "yki_bg",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};

// sam_02:b

EvtScript EVS_PreBattle_b = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetGroupVisibility, MODEL_p1, MODEL_GROUP_HIDDEN)
    Call(SetGroupVisibility, MODEL_yuki, MODEL_GROUP_HIDDEN)
    Exec(EVS_SpawnSnowfall)
    Return
    End
};

OVL_DEF_STAGE(b) = {
    .texture = "sam_tex",
    .bg = "yki_bg",
    .preBattle = &EVS_PreBattle_b,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};

// sam_02:c

EvtScript EVS_PreBattle_c = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetGroupVisibility, MODEL_p1, MODEL_GROUP_HIDDEN)
    Call(SetGroupVisibility, MODEL_p2, MODEL_GROUP_HIDDEN)
    Call(SetGroupVisibility, MODEL_yuki, MODEL_GROUP_HIDDEN)
    Exec(EVS_SpawnSnowfall)
    Return
    End
};

OVL_DEF_STAGE(c) = {
    .texture = "sam_tex",
    .bg = "yki_bg",
    .preBattle = &EVS_PreBattle_c,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};

// sam_02:d

EvtScript EVS_PreBattle_d = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetGroupVisibility, MODEL_p1, MODEL_GROUP_HIDDEN)
    Call(SetGroupVisibility, MODEL_p2, MODEL_GROUP_HIDDEN)
    Call(SetGroupVisibility, MODEL_p3, MODEL_GROUP_HIDDEN)
    Call(SetGroupVisibility, MODEL_yuki, MODEL_GROUP_HIDDEN)
    Exec(EVS_SpawnSnowfall)
    Return
    End
};

OVL_DEF_STAGE(d) = {
    .texture = "sam_tex",
    .bg = "yki_bg",
    .preBattle = &EVS_PreBattle_d,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
