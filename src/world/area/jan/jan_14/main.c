#include "jan_14.h"
#include "world/area/jan/jan_13.h"
#include "world/area/jan/jan_15.h"

EvtScript EVS_ExitWalk_jan_15_0 = EVT_EXIT_WALK(60, $Jan15, $jan_15.Jan14);
EvtScript EVS_ExitWalk_jan_13_1 = EVT_EXIT_WALK(60, $Jan13, $jan_13.Jan14);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_jan_13_1, TRIGGER_FLOOR_ABOVE, COLLIDER_deilis, 1, 0)
    BindTrigger(EVS_ExitWalk_jan_15_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilin, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Set(GB_WorldLocation, LOCATION_JADE_JUNGLE)
    EVT_SETUP_CAMERA_DEFAULT(0, 0, 0)
    Call(MakeNpcs, false, DefaultNPCs)
    Exec(EVS_SetupVines)
    Exec(EVS_SetupTrees)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilits, COLLIDER_FLAGS_UPPER_MASK)
    Call(ModifyColliderFlags, MODIFY_COLLIDER_FLAGS_SET_BITS, COLLIDER_deilitn, COLLIDER_FLAGS_UPPER_MASK)
    Set(LVar0, EVS_BindExitTriggers)
    Exec(EnterWalk)
    Call(SetMusic, 0, SONG_DEEP_JUNGLE, 0, VOL_LEVEL_FULL)
    Call(PlayAmbientSounds, AMBIENT_JUNGLE)
    Return
    End
};
