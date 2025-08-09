#include "../area.hpp"

namespace battle::area::kmr_part_1 {

namespace {

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

} // blank namespace

Stage PleasantPath2 = {
    .texture = "kmr_tex",
    .shape = "kmr_bt02_shape", //@bug does not exist
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .bg = "kmr_bg",
};

} // namespace battle::area::kmr_part_1
