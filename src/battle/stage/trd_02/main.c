#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/stage/trd_02_shape.h"
#include "battle/stage/common/BeachEffects.inc.c"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Call(EnableModel, MODEL_kabe2_2, false)
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

s32 ForegroundModels[] = {
    MODEL_saku,
    STAGE_MODEL_LIST_END
};

OVL_DEF_STAGE() = {
    .texture = "trd_tex",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};

// trd_02:b

EvtScript EVS_PreBattle_b = {
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

OVL_DEF_STAGE(b) = {
    .texture = "trd_tex",
    .preBattle = &EVS_PreBattle_b,
    .postBattle = &EVS_PostBattle,
};

// trd_02:c

EvtScript EVS_PreBattle_c = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Call(EnableModel, MODEL_dai, false)
    Call(EnableModel, MODEL_kusari1, false)
    Return
    End
};

OVL_DEF_STAGE(c) = {
    .texture = "trd_tex",
    .preBattle = &EVS_PreBattle_c,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};

// trd_02:d

EvtScript EVS_PreBattle_d = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Call(EnableModel, MODEL_mizu, false)
    Call(EnableModel, MODEL_mizu2, false)
    Call(EnableModel, MODEL_o298, false)
    Call(EnableModel, MODEL_o297, false)
    Call(EnableModel, MODEL_kiwa, false)
    Call(EnableModel, MODEL_tyuu, false)
    Return
    End
};

OVL_DEF_STAGE(d) = {
    .texture = "trd_tex",
    .preBattle = &EVS_PreBattle_d,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
