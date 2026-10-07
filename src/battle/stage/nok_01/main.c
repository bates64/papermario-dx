#include "battle/battle.h"
#include "script_api/battle.h"
#include "stage.xml.h"

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
    Set(LVar0, MODEL_h1)
    Exec(EVS_AnimateFlower)
    Set(LVar0, MODEL_h2)
    Exec(EVS_AnimateFlower)
    Set(LVar0, MODEL_h3)
    Exec(EVS_AnimateFlower)
    Set(LVar0, MODEL_h5)
    Exec(EVS_AnimateFlower)
    Set(LVar0, MODEL_h7)
    Exec(EVS_AnimateFlower)
    Set(LVar0, MODEL_h8)
    Exec(EVS_AnimateFlower)
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

OVL_DEF_STAGE() = {
    .texture = "nok_tex",
    .bg = "nok_bg",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
