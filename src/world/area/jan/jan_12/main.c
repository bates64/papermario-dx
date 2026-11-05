#include "jan_12.h"
#include "world/area/jan/jan_06.h"
#include "world/area/jan/jan_13.h"

EvtScript EVS_ExitWalk_jan_13_0 = EVT_EXIT_WALK(60, $Jan13, $jan_13.Jan12);
EvtScript EVS_ExitWalk_jan_06_2 = EVT_EXIT_WALK(60, $Jan06, $jan_06.Jan12);

EvtScript EVS_BindExitTriggers = {
    BindTrigger(EVS_ExitWalk_jan_06_2, TRIGGER_FLOOR_ABOVE, COLLIDER_deilis, 1, 0)
    BindTrigger(EVS_ExitWalk_jan_13_0, TRIGGER_FLOOR_ABOVE, COLLIDER_deilin, 1, 0)
    Return
    End
};

EvtScript EVS_Main = {
    Call(MakeNpcs, false, DefaultNPCs)
    ExecWait(EVS_MakeEntities)
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
