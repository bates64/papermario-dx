#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/jan_bt00_shape.h"
#include "effects.h"

#include "battle/stage/common/BeachEffects.inc.c"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Set(LVar0, MODEL_g88)
    Exec(EVS_AnimatePalmLeaves)
    Set(LVar0, MODEL_g89)
    Exec(EVS_AnimatePalmLeaves)
    Set(LVar0, MODEL_g86)
    Exec(EVS_AnimateWave)
    PlayEffect(EFFECT_SUN, FX_SUN_FROM_LEFT, 0, 0, 0, 0, 0)
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

OVL_DEF_STAGE() = {
    .texture = "jan_tex",
    .shape = "jan_bt00_shape",
    .hit = "jan_bt00_hit",
    .bg = "yos_bg",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
};
