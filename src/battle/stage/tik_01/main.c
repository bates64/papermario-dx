#include "battle/battle.h"
#include "script_api/battle.h"
#include "mapfs/tik_bt01_shape.h"

#include "battle/stage/common/TexturePanner.inc.c"

#include "battle/stage/common/DripVolumes.inc.c"

DripVolumeList DripVolumes = {
    .count = 1,
    .volumes = {
        {
            .minPos = { -100,  -50 },
            .maxPos = {  200,  100 },
            .startY = 200,
            .endY   = 0,
            .duration = 60,
            .density  = 4,
        }
    }
};

EvtScript EVS_PreBattle = {
    Call(SetSpriteShading, SHADING_NONE)
    Call(SetCamBGColor, CAM_BATTLE, 0, 0, 0)
    Set(LVar0, MODEL_misu)
    Set(LVar1, TEX_PANNER_0)
    Set(LVar2, 0)
    Set(LVar3, -500)
    Exec(EVS_TexturePanMain)
    Set(LVar0, Ref(DripVolumes))
    Set(LVar1, MODEL_o351)
    Exec(EVS_CreateDripVolumes)
    Return
    End
};

EvtScript EVS_PostBattle = {
    Return
    End
};

OVL_DEF_STAGE() = {
    .texture = "tik_tex",
    .shape = "tik_bt01_shape",
    .hit = "tik_bt01_hit",
    .preBattle = &EVS_PreBattle,
    .postBattle = &EVS_PostBattle,
};
