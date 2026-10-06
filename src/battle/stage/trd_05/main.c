#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/trd_bt05_shape.h"

#include "battle/stage/common/BeachEffects.inc.c"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Thread
        Set(LVar0, MODEL_o318)
        Exec(EVS_AnimateWave)
        Wait(5)
        Set(LVar0, MODEL_mizu4)
        Exec(EVS_AnimateWave)
    EndThread
    Thread
        Set(LVar0, MODEL_mizu3)
        Exec(EVS_AnimateWave)
        Wait(5)
        Set(LVar0, MODEL_mizu2)
        Exec(EVS_AnimateWave)
        Wait(5)
        Set(LVar0, MODEL_mizu1)
        Exec(EVS_AnimateWave)
    EndThread
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

BATTLE_STAGE_ENTRY = {
    .texture = "trd_tex",
    .shape = "trd_bt05_shape",
    .hit = "trd_bt05_hit",
    .bg = "nok_bg",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
};
