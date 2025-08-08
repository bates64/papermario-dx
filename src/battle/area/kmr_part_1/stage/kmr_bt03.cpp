#include "../area.hpp"

#include "mapfs/kmr_bt03_shape.h"

namespace battle::area::kmr_part_1 {

namespace kmr_03 {

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

} // namespace kmr_03

Stage PleasantPath3 = {
    .texture = "kmr_tex",
    .shape = "kmr_bt03_shape",
    .hit = "kmr_bt03_hit",
    .preBattle = &kmr_03::EVS_PreBattle,
    .postBattle = &kmr_03::EVS_PostBattle,
    .bg = "kmr_bg",
    .foregroundModelList = kmr_03::ForegroundModels,
};

} // namespace battle::area::kmr_part_1
