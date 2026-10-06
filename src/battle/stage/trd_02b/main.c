#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/trd_bt02_shape.h"

#include "battle/stage/common/BeachEffects.inc.c"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Call(EnableModel, MODEL_saku, false)
    Call(EnableModel, MODEL_kiwa, false)
    Call(EnableModel, MODEL_tyuu, false)
    Thread
        Set(LVar0, MODEL_mizu)
        Exec(EVS_AnimateWave)
        Wait(5)
        Set(LVar0, MODEL_mizu2)
        Exec(EVS_AnimateWave)
        Wait(5)
        Set(LVar0, MODEL_o298)
        Exec(EVS_AnimateWave)
        Wait(5)
        Set(LVar0, MODEL_o297)
        Exec(EVS_AnimateWave)
    EndThread
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

OVL_DEF_STAGE() = {
    .texture = "trd_tex",
    .shape = "trd_bt02_shape",
    .hit = "trd_bt02_hit",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
};
