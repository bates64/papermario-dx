#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/stage/trd_05_shape.h"
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

OVL_DEF_STAGE() = {
    .texture = "trd_tex",
    .bg = "nok_bg",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
};

// trd_05:b

EvtScript EVS_PreBattle_b = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Call(EnableModel, MODEL_kai, false)
    Call(EnableModel, MODEL_kusari1, false)
    Call(EnableModel, MODEL_mizu1, false)
    Call(EnableModel, MODEL_mizu2, false)
    Call(EnableModel, MODEL_mizu3, false)
    Call(EnableModel, MODEL_ori, false)
    Call(EnableModel, MODEL_saku1, false)
    Call(EnableModel, MODEL_saku2, false)
    Call(EnableModel, MODEL_mizu4, false)
    Call(EnableModel, MODEL_o318, false)
    Return
    End
};

OVL_DEF_STAGE(b) = {
    .texture = "trd_tex",
    .preBattle = &EVS_PreBattle_b,
    .postBattle = &EVS_PostBattle,
};

// trd_05:c

EvtScript EVS_PreBattle_c = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Call(EnableModel, MODEL_yuka3, false)
    Call(EnableModel, MODEL_hako, false)
    Call(EnableModel, MODEL_ori, false)
    Call(EnableModel, MODEL_saku1, false)
    Call(EnableModel, MODEL_saku2, false)
    Call(EnableModel, MODEL_mizu4, false)
    Set(LVar0, MODEL_o318)
    Exec(EVS_AnimateWave)
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

OVL_DEF_STAGE(c) = {
    .texture = "trd_tex",
    .preBattle = &EVS_PreBattle_c,
    .postBattle = &EVS_PostBattle,
};

// trd_05:d

EvtScript EVS_PreBattle_d = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Call(EnableModel, MODEL_yuka3, false)
    Call(EnableModel, MODEL_hako, false)
    Call(EnableModel, MODEL_kai, false)
    Call(EnableModel, MODEL_kusari1, false)
    Call(EnableModel, MODEL_mizu4, false)
    Call(EnableModel, MODEL_hikari2, false)
    Call(EnableModel, MODEL_o318, false)
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

OVL_DEF_STAGE(d) = {
    .texture = "trd_tex",
    .preBattle = &EVS_PreBattle_d,
    .postBattle = &EVS_PostBattle,
};

// trd_05:e

EvtScript EVS_PreBattle_e = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Call(EnableModel, MODEL_o318, false)
    Call(EnableModel, MODEL_mizu1, false)
    Call(EnableModel, MODEL_mizu2, false)
    Call(EnableModel, MODEL_mizu3, false)
    Call(EnableModel, MODEL_ori, false)
    Call(EnableModel, MODEL_saku1, false)
    Call(EnableModel, MODEL_saku2, false)
    Call(EnableModel, MODEL_mizu4, false)
    Return
    End
};

OVL_DEF_STAGE(e) = {
    .texture = "trd_tex",
    .preBattle = &EVS_PreBattle_e,
    .postBattle = &EVS_PostBattle,
};

// trd_05:f

EvtScript EVS_PreBattle_f = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Set(LVar0, MODEL_o318)
    Exec(EVS_AnimateWave)
    Call(EnableModel, MODEL_mizu1, false)
    Call(EnableModel, MODEL_mizu2, false)
    Call(EnableModel, MODEL_mizu3, false)
    Call(EnableModel, MODEL_ori, false)
    Call(EnableModel, MODEL_saku1, false)
    Call(EnableModel, MODEL_saku2, false)
    Call(EnableModel, MODEL_mizu4, false)
    Call(EnableModel, MODEL_hako, false)
    Return
    End
};

OVL_DEF_STAGE(f) = {
    .texture = "trd_tex",
    .preBattle = &EVS_PreBattle_f,
    .postBattle = &EVS_PostBattle,
};
