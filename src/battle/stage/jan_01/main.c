#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/stage/jan_01_shape.h"
#include "battle/stage/common/BeachEffects.inc.c"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Call(SetGroupVisibility, MODEL_g18, MODEL_GROUP_HIDDEN)
    Thread
        Wait(5)
        Set(LVar0, MODEL_o55)
        Exec(EVS_AnimateWave)
        Wait(5)
        Set(LVar0, MODEL_o54)
        Exec(EVS_AnimateWave)
        Wait(5)
        Set(LVar0, MODEL_o53)
        Exec(EVS_AnimateWave)
    EndThread
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

s32 ForegroundModels[] = {
    MODEL_o85,
    STAGE_MODEL_LIST_END
};

OVL_DEF_STAGE() = {
    .texture = "jan_tex",
    .bg = "yos_bg",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};

// jan_01:b

EvtScript EVS_PreBattle_b = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Call(SetGroupVisibility, MODEL_g17, MODEL_GROUP_HIDDEN)
    Thread
        Wait(5)
        Set(LVar0, MODEL_o55)
        Exec(EVS_AnimateWave)
        Wait(5)
        Set(LVar0, MODEL_o54)
        Exec(EVS_AnimateWave)
        Wait(5)
        Set(LVar0, MODEL_o53)
        Exec(EVS_AnimateWave)
    EndThread
    Return
    End
};

OVL_DEF_STAGE(b) = {
    .texture = "jan_tex",
    .bg = "yos_bg",
    .preBattle = &EVS_PreBattle_b,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
