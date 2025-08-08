#include "../area.hpp"

#include "mapfs/kmr_bt04_shape.h"

namespace battle::area::kmr_part_1 {

namespace kmr_04 {

#include "battle/common/stage/lib/MovingClouds.inc.c"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Set(LVar0, MODEL_g60)
    Set(LVar2, 0)
    Exec(N(EVS_AnimateCloud))
    Set(LVar0, MODEL_g61)
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
    MODEL_m4,
    MODEL_n2,
    STAGE_MODEL_LIST_END
};

} // namespace kmr_04

Stage PleasantPath4 = {
    .texture = "kmr_tex",
    .shape = "kmr_bt04_shape",
    .hit = "kmr_bt04_hit",
    .preBattle = &kmr_04::EVS_PreBattle,
    .postBattle = &kmr_04::EVS_PostBattle,
    .bg = "kmr_bg",
    .foregroundModelList = kmr_04::ForegroundModels,
};

} // namespace battle::area::kmr_part_1
