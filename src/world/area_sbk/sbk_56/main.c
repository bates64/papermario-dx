
#include "sbk_56.h"

extern EvtScript N(EVS_Main);
extern EvtScript N(EVS_MakeEntities);
extern EvtScript N(EVS_SetupFoliage);

#include "world/common/atomic/TexturePan.inc.c"

EntryList N(Entrances) = {
    [sbk_56_ENTRY_0]    { -475.0,    0.0,    0.0,   90.0 },
    [sbk_56_ENTRY_1]    {  475.0,    0.0,    0.0,  270.0 },
    [sbk_56_ENTRY_2]    {    0.0,    0.0, -475.0,  180.0 },
    [sbk_56_ENTRY_3]    {    0.0,    0.0,  475.0,    0.0 },
};

MapSettings N(settings) = {
    .main = &N(EVS_Main),
    .entryList = &N(Entrances),
    .entryCount = ENTRY_COUNT(N(Entrances)),
    .background = &gBackgroundImage,
    .tattle = { MSG_MapTattle_sbk_56 },
};

#include "world/common/todo/SpawnSunEffect.inc.c"

API_CALLABLE(N(StartOasisSongVariation)) {
    bgm_set_variation(0, 1);
    return ApiStatus_DONE2;
}

API_CALLABLE(N(StopOasisSongVariation)) {
    bgm_set_variation(0, 0);
    return ApiStatus_DONE2;
}

EvtScript N(EVS_ExitWalk_sbk_55_1) = {
    SetGroup(EVT_GROUP_1B)
    Call(UseExitHeading, 60, sbk_56_ENTRY_0)
    Exec(ExitWalk)
    Call(N(StopOasisSongVariation))
    Call(GotoMap, Ref("sbk_55"), sbk_55_ENTRY_1)
    Wait(100)
    Return
    End
};

EvtScript N(EVS_ExitWalk_sbk_46_3) = {
    SetGroup(EVT_GROUP_1B)
    Call(UseExitHeading, 60, sbk_56_ENTRY_2)
    Exec(ExitWalk)
    Call(N(StopOasisSongVariation))
    Call(GotoMap, Ref("sbk_46"), sbk_46_ENTRY_3)
    Wait(100)
    Return
    End
};

EvtScript N(EVS_ExitWalk_sbk_66_2) = {
    SetGroup(EVT_GROUP_1B)
    Call(UseExitHeading, 60, sbk_56_ENTRY_3)
    Exec(ExitWalk)
    Call(N(StopOasisSongVariation))
    Call(GotoMap, Ref("sbk_66"), sbk_66_ENTRY_2)
    Wait(100)
    Return
    End
};

EvtScript N(EVS_BindExitTriggers) = {
    BindTrigger(Ref(N(EVS_ExitWalk_sbk_55_1)), TRIGGER_FLOOR_ABOVE, COLLIDER_deiliw, 1, 0)
    BindTrigger(Ref(N(EVS_ExitWalk_sbk_46_3)), TRIGGER_FLOOR_ABOVE, COLLIDER_deilin, 1, 0)
    BindTrigger(Ref(N(EVS_ExitWalk_sbk_66_2)), TRIGGER_FLOOR_ABOVE, COLLIDER_deilis, 1, 0)
    Return
    End
};

EvtScript N(EVS_Main) = {
    Set(GB_WorldLocation, LOCATION_DRY_DRY_DESERT)
    Call(SetSpriteShading, SHADING_NONE)
    IfEq(GB_StoryProgress, STORY_CH2_GOT_PULSE_STONE)
        Call(DisablePulseStone, FALSE)
    EndIf
    EVT_SETUP_CAMERA_NO_LEAD(0, 0, 0)
    ExecWait(N(EVS_MakeEntities))
    Call(N(SpawnSunEffect))
    Call(MakeTransformGroup, MODEL_sui)
    Call(SetMusicTrack, 0, SONG_DRY_DRY_DESERT, 0, 8)
    Call(N(StartOasisSongVariation))
    Call(PlaySound, SOUND_LOOP_SBK_OASIS_WATER)
    Set(LVar0, Ref(N(EVS_BindExitTriggers)))
    Exec(EnterWalk)
    Exec(N(EVS_SetupFoliage))
    Call(SetTexPanner, MODEL_o49, TEX_PANNER_1)
    Thread
        TEX_PAN_PARAMS_ID(TEX_PANNER_1)
        TEX_PAN_PARAMS_STEP(   80,   80,  -80,  -80)
        TEX_PAN_PARAMS_FREQ(    1,    1,    1,    1)
        TEX_PAN_PARAMS_INIT(    0,    0,    0,    0)
        Exec(N(EVS_UpdateTexturePan))
    EndThread
    Return
    End
};
