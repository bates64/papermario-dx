#include "../area.hpp"

#include "mapfs/kmr_bt06_shape.h"

namespace battle::area::kmr_part_1 {

namespace kmr_06 {

#include "battle/common/stage/lib/MovingClouds.inc.c"

API_CALLABLE(SetupFog) {
    set_world_fog_dist(980, 1000);
    set_world_fog_color(15, 5, 55, 255);
    enable_world_fog();
    return ApiStatus_DONE2;
}

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetupFog)
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
    MODEL_o303,
    MODEL_ha3,
    STAGE_MODEL_LIST_END
};

} // namespace kmr_06

Stage PleasantPath6 = {
    .texture = "kmr_tex",
    .shape = "kmr_bt06_shape",
    .hit = "kmr_bt06_hit",
    .preBattle = &kmr_06::EVS_PreBattle,
    .postBattle = &kmr_06::EVS_PostBattle,
    .bg = "kmr_bg",
    .foregroundModelList = kmr_06::ForegroundModels,
};

} // namespace battle::area::kmr_part_1
