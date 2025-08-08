#include "../area.hpp"

namespace battle::area::kmr_part_1 {

namespace kmr_02 {

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

} // namespace kmr_02

Stage PleasantPath2 = {
    .texture = "kmr_tex",
    .shape = "kmr_bt02_shape", //@bug does not exist
    .preBattle = &kmr_02::EVS_PreBattle,
    .postBattle = &kmr_02::EVS_PostBattle,
    .bg = "kmr_bg",
};

} // namespace battle::area::kmr_part_1
