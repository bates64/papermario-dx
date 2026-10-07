#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/stage/mac_01_shape.h"
#include "battle/stage/common/WaterEffects.inc.c"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Thread
        Set(LVar0, MODEL_nami4)
        Exec(EVS_AnimateWaveModel)
        Wait(5)
        Set(LVar0, MODEL_nami3)
        Exec(EVS_AnimateWaveModel)
        Wait(5)
        Set(LVar0, MODEL_nami2)
        Exec(EVS_AnimateWaveModel)
        Wait(5)
        Set(LVar0, MODEL_nami1)
        Exec(EVS_AnimateWaveModel)
    EndThread
    Set(LVar0, MODEL_o391)
    Exec(EVS_AnimateFishModel)
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

OVL_DEF_STAGE() = {
    .texture = "mac_tex",
    .bg = "nok_bg",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
};
