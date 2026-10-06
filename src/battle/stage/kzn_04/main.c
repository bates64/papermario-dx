#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/kzn_bt04_shape.h"

#include "battle/stage/common/LavaDecorations.inc.c"

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Call(SetGroupVisibility, MODEL_08, MODEL_GROUP_HIDDEN)
    Call(SetGroupVisibility, MODEL_16, MODEL_GROUP_HIDDEN)
    Set(LVar0, MODEL_y2_1)
    Set(LVar1, TEX_PANNER_0)
    Exec(EVS_TexPan_Lava)
    Set(LVar0, MODEL_y2_2)
    Set(LVar1, TEX_PANNER_1)
    Exec(EVS_TexPan_Lava)
    Set(LVar0, MODEL_y3_1)
    Set(LVar1, TEX_PANNER_2)
    Exec(EVS_TexPan_Lava)
    Set(LVar0, MODEL_y3_2)
    Set(LVar1, TEX_PANNER_3)
    Exec(EVS_TexPan_Lava)
    Set(LVar0, MODEL_yougan)
    Set(LVar1, TEX_PANNER_4)
    Exec(EVS_TexPan_Lava)
    Set(LVar0, MODEL_6_you1)
    Set(LVar1, TEX_PANNER_5)
    Exec(EVS_TexPan_Lava)
    Set(LVar0, MODEL_6_you2)
    Set(LVar1, TEX_PANNER_6)
    Exec(EVS_TexPan_Lava)
    Set(LVar0, MODEL_tri)
    Set(LVar1, TEX_PANNER_7)
    Exec(EVS_TexPan_Lava)
    Set(LVar0, MODEL_awa1)
    Set(LVar1, TEX_PANNER_8)
    Exec(EVS_TexAnim_LavaBubble)
    Set(LVar0, MODEL_awa2)
    Set(LVar1, TEX_PANNER_9)
    Exec(EVS_TexAnim_LavaBubble)
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
    .shape = "kzn_bt04_shape",
    .hit = "kzn_bt04_hit",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
    .foregroundModelList = ForegroundModels,
};
