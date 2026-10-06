#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/sam_bt03_shape.h"

#include "battle/stage/common/Snowflakes.inc.c"

void EnableBackgroundWave(void) {
    enable_background_wave();
}

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Thread
        Set(LVar0, MODEL_Default)
        Set(LVar1, 0)
        Exec(EVS_AnimateHangingSnowflake_RandomSpin)
        Wait(5)
        Set(LVar0, MODEL_g62)
        Set(LVar1, 0)
        Exec(EVS_AnimateHangingSnowflake_NoSpin)
        Wait(5)
        Set(LVar0, MODEL_g60)
        Set(LVar1, 0)
        Exec(EVS_AnimateHangingSnowflake_NoSpin)
        Wait(5)
        Set(LVar0, MODEL_g58)
        Set(LVar1, 0)
        Exec(EVS_AnimateHangingSnowflake_NoSpin)
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
    MODEL_o278,
    STAGE_MODEL_LIST_END
};

OVL_DEF_STAGE() = {
    .texture = "sam_tex",
    .shape = "sam_bt03_shape",
    .hit = "sam_bt03_hit",
    .bg = "sam_bg",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
