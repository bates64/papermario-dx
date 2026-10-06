#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/tik_bt04_shape.h"

#include "battle/stage/common/WaterEffects.inc.c"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Thread
        Set(LVar0, MODEL_mizu2)
        Exec(EVS_AnimateWaveModel)
        Wait(5)
        Set(LVar0, MODEL_mizu3)
        Exec(EVS_AnimateWaveModel)
        Wait(5)
        Set(LVar0, MODEL_mizu4)
        Exec(EVS_AnimateWaveModel)
    EndThread
    Thread
        Wait(5)
        Set(LVar0, MODEL_o357)
        Set(LVar1, 145)
        Exec(EVS_AnimateDrifting)
        Set(LVar0, MODEL_o361)
        Set(LVar1, 145)
        Exec(EVS_AnimateDrifting)
    EndThread
    Set(LVar0, MODEL_o358)
    Set(LVar1, 60)
    Exec(EVS_AnimateDrifting)
    Set(LVar0, MODEL_o360)
    Set(LVar1, 60)
    Exec(EVS_AnimateDrifting)
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

BATTLE_STAGE_ENTRY = {
    .texture = "tik_tex",
    .shape = "tik_bt04_shape",
    .hit = "tik_bt04_hit",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
};
