#include "isk_01.h"

#include "world/common/atomic/TexturePan.inc.c"

Gfx N(HazePreGfx)[] = {
    gsDPSetAlphaDither(G_AD_NOISE),
    gsSPEndDisplayList(),
};

EvtScript N(EVS_SetupHaze) = {
    Call(SetCustomGfx, CUSTOM_GFX_0, Ref(N(HazePreGfx)), nullptr)
    Call(SetModelFlags, MODEL_o99, MODEL_FLAG_USES_CUSTOM_GFX, true)
    Call(SetTexPanner, MODEL_o99, TEX_PANNER_2)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_2)
        TEX_PAN_PARAMS_STEP(   70,    0,    0,    0)
        TEX_PAN_PARAMS_FREQ(    1,    0,    0,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    Return
    End
};
