#include "../area.hpp"

#include "mapfs/kmr_bt05_shape.h"

namespace battle::area::kmr_part_1 {

namespace {

#include "battle/common/stage/lib/MovingClouds.inc.c"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(EnableModel, MODEL_o302, FALSE)
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

s32 ForegroundModels[] = {
    MODEL_n2,
    MODEL_m4,
    STAGE_MODEL_LIST_END
};

} // blank namespace

Stage PleasantPath5 = {
    .texture = "kmr_tex",
    .shape = "kmr_bt05_shape",
    .hit = "kmr_bt05_hit",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .bg = "kmr_bg",
    .foregroundModelList = ForegroundModels,
};

} // namespace battle::area::kmr_part_1
