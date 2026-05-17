#include "kzn_05.h"

#include "world/common/atomic/TexturePan.inc.c"

EvtScript N(EVS_ExitWalk_kzn_06_0) = EVT_EXIT_WALK(60, kzn_05_ENTRY_0, "kzn_06", kzn_06_ENTRY_0);
EvtScript N(EVS_ExitWalk_kzn_03_1) = EVT_EXIT_WALK(60, kzn_05_ENTRY_1, "kzn_03", kzn_03_ENTRY_3);

EvtScript N(EVS_BindExitTriggers) = {
    BindTrigger(N(EVS_ExitWalk_kzn_06_0), TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    BindTrigger(N(EVS_ExitWalk_kzn_03_1), TRIGGER_FLOOR_ABOVE, COLLIDER_deili2, 1, 0)
    Return
    End
};

EvtScript N(EVS_StartTexPanners) = {
    // smoke
    Call(SetTexPanner, MODEL_kem1, TEX_PANNER_3)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_3)
        TEX_PAN_PARAMS_STEP( -200,    0,  600, -400)
        TEX_PAN_PARAMS_FREQ(    1,    0,    1,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    Return
    End
};

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_MT_LAVALAVA)
    Call(SetSpriteShading, SHADING_KZN_05)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Set(LVar0, Ref(N(EVS_BindExitTriggers)))
    Exec(EnterWalk)
    Wait(1)
    Call(SetMusic, 0, SONG_MT_LAVALAVA, 0, VOL_LEVEL_FULL)
    Call(PlayAmbientSounds, AMBIENT_LAVA_1)
    Exec(N(EVS_StartTexPanners))
    Return
    End
};
