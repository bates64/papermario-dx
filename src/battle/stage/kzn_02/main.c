#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/kzn_bt02_shape.h"

#include "battle/stage/common/LavaDecorations.inc.c"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Set(LVar0, MODEL_yougan)
    Set(LVar1, TEX_PANNER_0)
    Exec(EVS_TexPan_Lava)
    Set(LVar0, MODEL_y1_1)
    Set(LVar1, TEX_PANNER_1)
    Exec(EVS_TexPan_Lava)
    Set(LVar0, MODEL_y1_2)
    Set(LVar1, TEX_PANNER_2)
    Exec(EVS_TexPan_Lava)
    Set(LVar0, MODEL_y2_1)
    Set(LVar1, TEX_PANNER_3)
    Exec(EVS_TexPan_Lava)
    Set(LVar0, MODEL_y2_2)
    Set(LVar1, TEX_PANNER_4)
    Exec(EVS_TexPan_Lava)
    Set(LVar0, MODEL_y3_1)
    Set(LVar1, TEX_PANNER_5)
    Exec(EVS_TexPan_Lava)
    Set(LVar0, MODEL_y3_2)
    Set(LVar1, TEX_PANNER_6)
    Exec(EVS_TexPan_Lava)
    Set(LVar0, MODEL_move)
    Set(LVar1, 180)
    Set(LVar2, 0)
    Set(LVar3, 200)
    Exec(EVS_MovingPlatform)
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

s32 ForegroundModels[] = {
    MODEL_iwa3,
    MODEL_sita1,
    MODEL_ue3,
    STAGE_MODEL_LIST_END
};

OVL_DEF_STAGE() = {
    .texture = "kzn_tex",
    .shape = "kzn_bt02_shape",
    .hit = "kzn_bt02_hit",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
