#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/kgr_bt01_shape.h"

#include "battle/stage/common/WaterEffects.inc.c"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Thread
        Set(LVar0, MODEL_bin1)
        Exec(EVS_AnimateFlotsam)
        Wait(4)
        Set(LVar0, MODEL_bin2)
        Exec(EVS_AnimateFlotsam)
        Wait(4)
        Set(LVar0, MODEL_bin3)
        Exec(EVS_AnimateFlotsam)
        Wait(4)
        Set(LVar0, MODEL_bin4)
        Exec(EVS_AnimateFlotsam)
    EndThread
    Thread
        Set(LVar0, MODEL_hako1)
        Exec(EVS_AnimateFlotsam)
        Wait(4)
        Set(LVar0, MODEL_hako2)
        Exec(EVS_AnimateFlotsam)
        Wait(4)
        Set(LVar0, MODEL_hako4)
        Exec(EVS_AnimateFlotsam)
        Wait(4)
        Set(LVar0, MODEL_hako5)
        Exec(EVS_AnimateFlotsam)
        Wait(4)
        Set(LVar0, MODEL_hako6)
        Exec(EVS_AnimateFlotsam)
    EndThread
    Set(LVar0, MODEL_fune2)
    Exec(EVS_AnimateFlotsam)
    Set(LVar0, MODEL_fune1)
    Exec(EVS_AnimateFlotsam)
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

s32 ForegroundModels[] = {
    MODEL_hone,
    MODEL_hako4,
    STAGE_MODEL_LIST_END
};

BATTLE_STAGE_ENTRY = {
    .texture = "kgr_tex",
    .shape = "kgr_bt01_shape",
    .hit = "kgr_bt01_hit",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
