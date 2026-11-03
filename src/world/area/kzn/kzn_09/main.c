#include "kzn_09.h"
#include "world/area/kzn/kzn_03.h"
#include "world/area/kzn/kzn_10.h"

EvtScript EVS_ExitWalk_kzn_03_2 = EVT_EXIT_WALK(60, $Kzn03Upper, $kzn_03.Kzn09Upper);
EvtScript EVS_ExitWalk_kzn_10_0 = EVT_EXIT_WALK(60, $Kzn10, $kzn_10.Kzn09);
EvtScript EVS_ExitWalk_kzn_03_4 = EVT_EXIT_WALK(60, $Kzn03Lower, $kzn_03.Kzn09Lower);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_kzn_03_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deili1, 1, 0)
    BindTrigger(EVS_ExitWalk_kzn_10_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deili2, 1, 0)
    BindTrigger(EVS_ExitWalk_kzn_03_4, TRIGGER_FLOOR_ABOVE, COLLIDER_deili3, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_MT_LAVALAVA)
    Call(SetSpriteShading, $SpriteShading)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Call(MakeNpcs, true, DefaultNPCs)
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
