#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/flo_bt05_shape.h"

#include "battle/stage/common/MakeSun.inc.c"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    ExecWait(MakeSun)
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

BATTLE_STAGE_ENTRY = {
    .texture = "flo_tex",
    .shape = "flo_bt05_shape",
    .hit = "flo_bt05_hit",
    .bg = "fla_bg",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
};
