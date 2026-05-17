#include "kzn_23.h"

#include "world/common/atomic/TexturePan.inc.c"

// should add to zero over a full cycle
s32 N(LavaFluctuationOffsets)[] = {
     1,  2,  3,  3,  2,  1,
    -1, -2, -3, -3, -2, -1,
};

// overlay a sinusoidal offset to the lava level
EvtScript N(EVS_ModulateLavaLevel) = {
    Loop(0)
        UseBuf(N(LavaFluctuationOffsets))
        Loop(ARRAY_COUNT(N(LavaFluctuationOffsets)))
            BufRead1(LVar1)
            Add(MV_LavaLevel, LVar1)
            Wait(3)
        EndLoop
    EndLoop
    Return
    End
};

EvtScript N(EVS_StartTexPanners) = {
    // lava surface
    Call(SetTexPanner, MODEL_yu, TEX_PANNER_0)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_0)
        TEX_PAN_PARAMS_STEP( -700,  700,  200, -300)
        TEX_PAN_PARAMS_FREQ(    1,    1,    1,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    // smoke
    Call(SetTexPanner, MODEL_kem1, TEX_PANNER_3)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_3)
        TEX_PAN_PARAMS_STEP( -200,    0,  600, -400)
        TEX_PAN_PARAMS_FREQ(    1,    0,    1,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    Call(SetTexPanner, MODEL_kem2, TEX_PANNER_4)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_4)
        TEX_PAN_PARAMS_STEP( 500,    0,    0, -400)
        TEX_PAN_PARAMS_FREQ(   1,    0,    0,    1)
        TEX_PAN_PARAMS_INIT(   0,    0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    Return
    End
};

EvtScript N(EVS_RaiseLava) = {
    Exec(N(EVS_ModulateLavaLevel))
    SetGroup(EVT_GROUP_NEVER_PAUSE)
    Set(MV_LavaLevel, -105)
    Set(LVar5, 40)
    Call(TranslateModel, MODEL_yu, 0, MV_LavaLevel, 0)
    Wait(6)
    Label(10)
        IfEq(LVar5, 40)
            IfLt(MV_LavaLevel, 2700)
                Add(MV_LavaLevel, 20)
            Else
                Sub(LVar5, 1)
            EndIf
        Else
            IfNe(LVar5, 0)
                Sub(LVar5, 1)
                Sub(MV_LavaLevel, 1)
            EndIf
        EndIf
        Call(TranslateModel, MODEL_yu, 0, MV_LavaLevel, 0)
        Wait(1)
        Goto(10)
    Return
    End
};

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_MT_LAVALAVA)
    Call(SetSpriteShading, SHADING_KZN_23)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Call(MakeNpcs, true, Ref(N(DefaultNPCs)))
    Exec(N(EVS_SetupMusic))
    Exec(N(EVS_RaiseLava))
    Exec(N(EVS_StartTexPanners))
    Return
    End
};
