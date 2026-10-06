#include "kzn_09.h"

EvtScript EVS_ExitWalk_kzn_03_2 = EVT_EXIT_WALK(60, kzn_09_ENTRY_0, "kzn_03", kzn_03_ENTRY_2);
EvtScript EVS_ExitWalk_kzn_10_0 = EVT_EXIT_WALK(60, kzn_09_ENTRY_1, "kzn_10", kzn_10_ENTRY_0);
EvtScript EVS_ExitWalk_kzn_03_4 = EVT_EXIT_WALK(60, kzn_09_ENTRY_2, "kzn_03", kzn_03_ENTRY_4);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_kzn_03_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    BindTrigger(EVS_ExitWalk_kzn_10_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deili2, 1, 0)
    BindTrigger(EVS_ExitWalk_kzn_03_4, TRIGGER_FLOOR_ABOVE, COLLIDER_deili3, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_MT_LAVALAVA)
    Call(SetSpriteShading, SHADING_KZN_09)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Call(MakeNpcs, true, Ref(DefaultNPCs))
    ExecWait(EVS_MakeEntities)
    Call(SetMusic, 0, SONG_MT_LAVALAVA, 0, VOL_LEVEL_FULL)
    Call(PlayAmbientSounds, AMBIENT_LAVA_1)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Wait(1)
    ExecWait(EVS_SetupZipline)
    Return
    End
};
