#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/nok_bt02_shape.h"

EvtScript EVS_AnimateFlower = {
    Set(LVarA, LVar0)
    Label(0)
        Call(TranslateModel, LVarA, 0, 2, 0)
        Wait(5)
        Call(TranslateModel, LVarA, 0, 0, 0)
        Wait(5)
        Call(TranslateModel, LVarA, 0, 2, 0)
        Wait(5)
        Call(TranslateModel, LVarA, 0, 0, 0)
        Wait(5)
        Call(RandInt, 30, LVar0)
        Add(LVar0, 30)
        Wait(LVar0)
        Goto(0)
    Return
    End
};

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Thread
        Set(LVar0, MODEL_h1)
        Exec(EVS_AnimateFlower)
        Wait(5)
        Set(LVar0, MODEL_h3)
        Exec(EVS_AnimateFlower)
        Wait(5)
        Set(LVar0, MODEL_h4)
        Exec(EVS_AnimateFlower)
        Wait(5)
        Set(LVar0, MODEL_h5)
        Exec(EVS_AnimateFlower)
        Wait(5)
        Set(LVar0, MODEL_h6)
        Exec(EVS_AnimateFlower)
        Wait(5)
        Set(LVar0, MODEL_h7)
        Exec(EVS_AnimateFlower)
        Wait(5)
        Set(LVar0, MODEL_h9)
        Exec(EVS_AnimateFlower)
        Wait(5)
        Set(LVar0, MODEL_h10)
        Exec(EVS_AnimateFlower)
        Wait(5)
        Set(LVar0, MODEL_h11)
        Exec(EVS_AnimateFlower)
        Wait(5)
        Set(LVar0, MODEL_h12)
        Exec(EVS_AnimateFlower)
    EndThread
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

s32 ForegroundModels[] = {
    MODEL_ha3,
    MODEL_hap,
    MODEL_kusa3,
    STAGE_MODEL_LIST_END
};

BATTLE_STAGE_ENTRY = {
    .texture = "nok_tex",
    .shape = "nok_bt02_shape",
    .hit = "nok_bt02_hit",
    .bg = "nok_bg",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
