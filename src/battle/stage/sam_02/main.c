#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/sam_bt02_shape.h"

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
    .shape = "sam_bt02_shape",
    .hit = "sam_bt02_hit",
    .bg = "yki_bg",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
