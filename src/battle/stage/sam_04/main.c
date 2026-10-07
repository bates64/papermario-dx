#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/sam_bt04_shape.h"

#include "battle/stage/common/Snowflakes.inc.c"

void EnableBackgroundWave(void) {
    enable_background_wave();
}

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Exec(EVS_SpawnSnowfall)
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

OVL_DEF_STAGE() = {
    .texture = "sam_tex",
    .shape = "sam_bt04_shape",
    .hit = "sam_bt04_hit",
    .bg = "sam_bg",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
};
