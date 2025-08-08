#include "../area.hpp"

#include "mapfs/kmr_bt03_shape.h"

namespace battle::area::kmr_part_1 {

#include "battle/common/stage/lib/MovingClouds.inc.c"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Set(LVar0, MODEL_g59)
    Set(LVar2, 0)
    Exec(N(EVS_AnimateCloud))
    Set(LVar0, MODEL_g60)
    Set(LVar2, 70)
    Exec(N(EVS_AnimateCloud))
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

Stage PleasantPath3 = {
    .texture = "kmr_tex",
    .shape = "kmr_bt03_shape",
    .hit = "kmr_bt03_hit",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .bg = "kmr_bg",
    .foregroundModelList = ForegroundModels,
};

} // namespace battle::area::kmr_part_1
