#include "kzn_01.h"

#include "world/common/atomic/TexturePan.inc.c"

EvtScript N(EVS_ExitWalk_jan_22_2) = EVT_EXIT_WALK(60, kzn_01_ENTRY_0, "jan_22", jan_22_ENTRY_2);
EvtScript N(EVS_ExitWalk_kzn_02_0) = EVT_EXIT_WALK(60, kzn_01_ENTRY_1, "kzn_02", kzn_02_ENTRY_0);

EvtScript N(EVS_BindExitTriggers) = {
    BindTrigger(N(EVS_ExitWalk_jan_22_2), TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    BindTrigger(N(EVS_ExitWalk_kzn_02_0), TRIGGER_FLOOR_ABOVE, COLLIDER_deili2, 1, 0)
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
    Call(SetSpriteShading, SHADING_KZN_01)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Set(GF_MAP_MtLavalava, TRUE)
    IfLt(GB_StoryProgress, STORY_CH5_ENTERED_MT_LAVA_LAVA)
        Set(GB_StoryProgress, STORY_CH5_ENTERED_MT_LAVA_LAVA)
    EndIf
    Call(MakeNpcs, TRUE, Ref(N(DefaultNPCs)))
    Set(LVar0, N(EVS_BindExitTriggers))
    Exec(EnterWalk)
    Wait(1)
    Call(SetMusic, 0, SONG_MT_LAVALAVA, 0, VOL_LEVEL_FULL)
    Call(ClearAmbientSounds, 250)
    Exec(N(EVS_StartTexPanners))
    Return
    End
};
