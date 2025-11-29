#include "hos_06.h"

#include "world/common/atomic/TexturePan.inc.c"

EvtScript N(EVS_Animate_MysticPyramid) = {
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_C)
        TEX_PAN_PARAMS_STEP( 0x4000,    0,    0,    0)
        TEX_PAN_PARAMS_FREQ(      3,    0,    0,    0)
        TEX_PAN_PARAMS_INIT(      0,    0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    Call(SetTexPanner, MODEL_o185, TEX_PANNER_C)
    Set(LVar0, 0)
    Loop(0)
        Call(RotateGroup, MODEL_g87, LVar0, 0, 1, 0)
        Call(RotateGroup, MODEL_g88, LVar0, 0, 1, 0)
        Add(LVar0, 6)
        Wait(1)
    EndLoop
    Return
    End
};

EvtScript N(EVS_ExitWalk_hos_00_2) = EVT_EXIT_WALK(60, hos_06_ENTRY_0, "hos_00", hos_00_ENTRY_2);

EvtScript N(EVS_BindExitTriggers) = {
    BindTrigger(Ref(N(EVS_ExitWalk_hos_00_2)), TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    Return
    End
};

EvtScript N(EVS_TexPan_Stars) = {
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_3)
        TEX_PAN_PARAMS_STEP( -100,    0,   40,    0)
        TEX_PAN_PARAMS_FREQ(    1,    0,    1,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    Call(SetTexPanner, MODEL_o103, TEX_PANNER_3)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_1)
        TEX_PAN_PARAMS_STEP( -200,    0,  100,    0)
        TEX_PAN_PARAMS_FREQ(    1,    0,    1,    0)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    Call(SetTexPanner, MODEL_o105, TEX_PANNER_1)
    Return
    End
};

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_SHOOTING_STAR_SUMMIT)
    Call(SetSpriteShading, SHADING_NONE)
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    Set(AF_HOS06_SpokeWithMerluvlee, FALSE)
    Call(MakeNpcs, FALSE, Ref(N(DefaultNPCs)))
    ExecWait(N(EVS_MakeEntities))
    Exec(N(EVS_SetupMagicChest))
    Exec(N(EVS_Animate_MysticPyramid))
    Set(LVar0, Ref(N(EVS_BindExitTriggers)))
    Exec(EnterWalk)
    Wait(1)
    Call(SetMusic, 0, SONG_SHOOTING_STAR_SUMMIT, 0, VOL_LEVEL_FULL)
    Exec(N(EVS_SetupRooms))
    Exec(N(EVS_TexPan_Stars))
    BindTrigger(Ref(N(EVS_AskForHint)), TRIGGER_WALL_PRESS_A, COLLIDER_o224, 1, 0)
    Return
    End
};
