#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/sam_bt01_shape.h"

#include "battle/stage/common/Snowflakes.inc.c"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Exec(EVS_SpawnSnowfall)
    Thread
        Set(LVar0, MODEL_o262)
        Set(LVar1, 1)
        Exec(EVS_AnimateHangingSnowflake_RandomSpin)
        Wait(5)
        Set(LVar0, MODEL_o261)
        Set(LVar1, 3)
        Exec(EVS_AnimateHangingSnowflake_RandomSpin)
        Wait(5)
        Set(LVar0, MODEL_o260)
        Set(LVar1, 4)
        Exec(EVS_AnimateHangingSnowflake_RandomSpin)
        Wait(5)
        Set(LVar0, MODEL_o253)
        Set(LVar1, 2)
        Exec(EVS_AnimateHangingSnowflake_RandomSpin)
    EndThread
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

s32 ForegroundModels[] = {
    -1,
    MODEL_saku,
    STAGE_MODEL_LIST_END
};

BATTLE_STAGE_ENTRY = {
    .texture = "sam_tex",
    .shape = "sam_bt01_shape",
    .hit = "sam_bt01_hit",
    .bg = "yki_bg",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
