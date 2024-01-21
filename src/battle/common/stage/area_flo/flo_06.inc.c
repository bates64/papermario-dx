#include "battle/battle.h"
#include "mapfs/flo_bt06_shape.h"

#define NAMESPACE A(flo_06)

#include "common/MakeSun.inc.c"

EvtScript N(EVS_PreBattle) = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    ExecWait(N(MakeSun))
    Return
    End
};

EvtScript N(EVS_PostBattle) = {
    Return
    End
};

Stage NAMESPACE = {
    .texture = "flo_tex",
    .shape = "flo_bt06_shape",
    .hit = "flo_bt06_hit",
    .bg = "fla_bg",
    .preBattle = &N(EVS_PreBattle),
    .postBattle = &N(EVS_PostBattle),
};
